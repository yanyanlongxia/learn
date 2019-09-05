# title

[BZOJ 3110](https://lydsy.com/JudgeOnline/problem.php?id=3110)

[LUOGU 3332](https://www.luogu.org/problem/P3332)

题意：

>有 $N$ 个位置， $M$ 个操作。操作有两种，每次操作如果是：
>
>- `1 a b c`：表示在第 $a$ 个位置到第 $b$ 个位置，每个位置加上一个数 $c$ ；
>- `2 a b c`：表示询问从第 $a$ 个位置到第 $b$ 个位置，第 $c$ 大的数是多少。

# analysis

看到题后就想到应该是要用主席树的，吼吼吼，没想到特么的是个树套树（所以，其中一种写法就是树状数组套主席树），哎呀，我不会，学。

这种写法是权值线段树套区间线段树（到现在我才知道线段树也分类）。

外层权值线段树，实质就是一个二分答案的过程，然后呢？

运用主席树的思想，设询问区间为 $[tl,tr]$ ，答案区间为 $[l,r]$ ，取其 $mid$ ，然后计算在左儿子 $[l,mid]$ 和询问区间 $[tl,tr]$ 中的数的个数，那么我们就可以判断答案是大于 $mid$ 还是小于 $mid$ 的了。

而在权值线段树的每一个节点上都建一个区间线段树，来维护该权值在 $[1,n]$ 所有区间上的出现次数，然后维护一个区间和就好了。

为了防止 $MLE$ ，区间线段树上搞一个动态开点就好了。

-----

上面的其实就是个伪装大暴力，正解是一个叫整体二分的鬼东东，第一次接触到哈。

额，毫无疑问，这是一道比较基础的整体二分的题目（就是不说那两个字，怕）。

这是大佬解释的整体二分：

> $Q$ ：何谓整体二分？
>
> $A$ ：就是直接一起二分所有的询问操作的答案，然后暴力扫描当前操作区间，将其划分为答案的左子区间与右子区间两个部分。
>
> $Q$ ：那么以什么为划分依据呢？
>
> $A$ ：看看这个操作对于左子区间有没有贡献。如果没有，那么就划分到右子区间中，然后将这个操作的权值更改为这个贡献减去所需的贡献，反之，则划分到左子区间中，同时将这个操作的贡献加入某一个容器，为询问操作服务。

我们设尚未解决的操作区间为 $[tl,tr]$ ，答案区间为 $[l,r]$ ，令当前答案为 $mid$ 。

则若该操作是添加操作，如果其添加的  $c\leqslant mid$ ，这此次操作对于左子区间有贡献，加入左子区间中，并将区间线段树中的区间 $[q[i].l,q[i].r]$ 整体加 $1$ 。

反之，则将操作加入到右子区间中。

若该操作是询问操作，如果当前的 $mid$ 在线段树中查询到的，比它大的数的个数 $query()>=q[i].k$ ，则证明该询问操作应该在右子区间内可以找到答案。反之，则将 $query()-=q[i].k$，减去此次查询的贡献，然后将询问操作添加到左子区间中。

哈哈，感觉和 [IAmHellWord](https://www.luogu.org/blog/IAmHellWord/solution-p3332) 好像，我就是照着人家的 $blog$ 学的，所以没办法了，加强思考吧。

# code

~~树套树套树套树套树套树...（滑稽）~~

```cpp
#include<bits/stdc++.h>

#define G ch=getc()
typedef long long ll;
const int maxn=5e4+10;

namespace IO
{
	char buf[1<<15],*fs,*ft;
	inline char getc() { return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++; }
	template<typename T>inline void read(T &x)
	{
		x=0;
		T f=1, G;
		while (!isdigit(ch) && ch^'-') G;
		if (ch=='-') f=-1, G;
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), G;
		x*=f;
	}

	char Out[1<<24],*fe=Out;
	inline void flush() { fwrite(Out,1,fe-Out,stdout); fe=Out; }
	template<typename T>inline void write(T x,char str)
	{
		if (!x) *fe++=48;
		if (x<0) *fe++='-', x=-x;
		T num=0, ch[20];
		while (x) ch[++num]=x%10+48, x/=10;
		while (num) *fe++=ch[num--];
		*fe++=str;
	}
}

using IO::read;
using IO::write;

template<typename T>inline T min(T a,T b) { return a<b ? a : b; }
template<typename T>inline T max(T a,T b) { return a>b ? a : b; }

int n,m;
struct Position_Segment_Tree
{
	struct Orz{int l,r,atag; ll z;}c[maxn*400];
	int cnt;
	inline void pushdown(int x,int l,int r)
	{
		int &v=c[x].atag, mid=(l+r)>>1;
		if (!c[x].l) c[x].l=++cnt;
		if (!c[x].r) c[x].r=++cnt;
		c[c[x].l].atag+=v, c[c[x].r].atag+=v;
		c[c[x].l].z+=v*(mid-l+1), c[c[x].r].z+=v*(r-mid);
		v=0;
	}

	inline void add(int &x,int tl,int tr,int l=1,int r=n)
	{
		if (!x) x=++cnt;//动态开点
		if (tl<=l && r<=tr) { ++c[x].atag, c[x].z+=r-l+1; return ; }
		if (c[x].atag) pushdown(x,l,r);
		int mid=(l+r)>>1;
		if (tl<=mid) add(c[x].l,tl,tr,l,mid);
		if (tr>mid) add(c[x].r,tl,tr,mid+1,r);
		c[x].z=c[c[x].l].z+c[c[x].r].z;
	}

	inline ll ask(int &x,int tl,int tr,int l=1,int r=n)
	{
		if (!x) return 0;
		if (tl<=l && r<=tr) return c[x].z;
		if (c[x].atag) pushdown(x,l,r);
		int mid=(l+r)>>1;
		ll ans=0;
		if (tl<=mid) ans+=ask(c[x].l,tl,tr,l,mid);
		if (tr>mid) ans+=ask(c[x].r,tl,tr,mid+1,r);
		return ans;
	}
}pst;

int b[maxn],tot;
struct Data_Segment_Tree
{
	int rt[maxn<<2];
	inline void insert(int tl,int tr,int k,int x=1,int l=1,int r=tot)
	{
		pst.add(rt[x],tl,tr);
		if (l==r) return ;
		int mid=(l+r)>>1;
		if (k<=mid) insert(tl,tr,k,x<<1,l,mid);
		else insert(tl,tr,k,x<<1|1,mid+1,r);
	}

	inline int ask(int tl,int tr,ll k,int x=1,int l=1,int r=tot)
	{
		if (l==r) return b[l];
		int mid=(l+r)>>1;
		ll sum=pst.ask(rt[x<<1|1],tl,tr);
		if (sum<k) return ask(tl,tr,k-sum,x<<1,l,mid);
		else return ask(tl,tr,k,x<<1|1,mid+1,r);
	}
}dst;

int opt[maxn],ql[maxn],qr[maxn],k[maxn];
int main()
{
	read(n);read(m);
	for (int i=1; i<=m; ++i)
	{
		read(opt[i]),read(ql[i]),read(qr[i]),read(k[i]);
		if (opt[i]==1) b[++tot]=k[i];
	}
	std::sort(b+1,b+tot+1);
	tot=std::unique(b+1,b+tot+1)-b-1;
	for (int i=1; i<=m; ++i)
		if (opt[i]==1) k[i]=std::lower_bound(b+1,b+tot+1,k[i])-b;
	for (int i=1; i<=m; ++i)
		if (opt[i]==1) dst.insert(ql[i],qr[i],k[i]);
		else write(dst.ask(ql[i],qr[i],k[i]),'\n');
	IO::flush();
	return 0;
}
```

~~整体二分~~

```cpp
#include<bits/stdc++.h>

#define G ch=getchar()
typedef long long ll;
const int maxn=5e4+10;

namespace IO
{
	char buf[1<<15],*fs,*ft;
	inline char getc() { return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++; }
	template<typename T>inline void read(T &x)
	{
		x=0;
		T f=1, G;
		while (!isdigit(ch) && ch^'-') G;
		if (ch=='-') f=-1, G;
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), G;
		x*=f;
	}

	char Out[1<<24],*fe=Out;
	inline void flush() { fwrite(Out,1,fe-Out,stdout); fe=Out; }
	template<typename T>inline void write(T x,char str)
	{
		if (!x) *fe++=48;
		if (x<0) *fe++='-', x=-x;
		T num=0, ch[20];
		while (x) ch[++num]=x%10+48, x/=10;
		while (num) *fe++=ch[num--];
		*fe++=str;
	}
}

using IO::read;
using IO::write;

template<typename T>inline T min(T a,T b) { return a<b ? a : b; }
template<typename T>inline T max(T a,T b) { return a>b ? a : b; }

int rec[maxn<<2],tag[maxn<<2];
ll sum[maxn<<2];
inline void pushdown(int x,int l,int r)
{
	if (rec[x])
	{
		rec[x]=0;
		tag[x<<1]=tag[x<<1|1]=sum[x<<1]=sum[x<<1|1]=0;
		rec[x<<1]=rec[x<<1|1]=1;
	}
	if (tag[x])
	{
		int mid=(l+r)>>1;
		tag[x<<1]+=tag[x], tag[x<<1|1]+=tag[x];
		sum[x<<1]+=tag[x]*(mid-l+1);
		sum[x<<1|1]+=tag[x]*(r-mid);
		tag[x]=0;
	}
}

int n,m;
inline void add(int tl,int tr,int k,int x=1,int l=1,int r=n)
{
	if (tl<=l && r<=tr)
	{
		tag[x]+=k, sum[x]+=k*(r-l+1);
		return ;
	}
	if (tag[x] || rec[x]) pushdown(x,l,r);
	int mid=(l+r)>>1;
	if (tl<=mid) add(tl,tr,k,x<<1,l,mid);
	if (tr>mid) add(tl,tr,k,x<<1|1,mid+1,r);
	sum[x]=sum[x<<1]+sum[x<<1|1];
}

inline ll ask(int tl,int tr,int x=1,int l=1,int r=n)
{
	if (tl<=l && r<=tr) return sum[x];
	int mid=(l+r)>>1;
	ll ans=0;
	if (tag[x] || rec[x]) pushdown(x,l,r);
	if (tl<=mid) ans+=ask(tl,tr,x<<1,l,mid);
	if (tr>mid) ans+=ask(tl,tr,x<<1|1,mid+1,r);
	return ans;
}

int ans[maxn],cnt;
struct Orz{int opt,l,r,id; ll k;}q[maxn],tl[maxn],tr[maxn];
inline void solve(int st,int en,int l,int r)
{
	if (l==r)
	{
		for (int i=st; i<=en; ++i)
			if (q[i].opt==2) ans[q[i].id]=l;
		return ;
	}
	int mid=(l+r)>>1;
	bool fl=0, fr=0;
	int L=0, R=0;
	rec[1]=1, tag[1]=sum[1]=0;
	for (int i=st; i<=en; ++i)
		if (q[i].opt==1)
		{
			if (q[i].k>mid) add(q[i].l,q[i].r,1), tr[++R]=q[i];
			else tl[++L]=q[i];
		}
		else
		{
			ll val=ask(q[i].l,q[i].r);
			if (val<q[i].k) q[i].k-=val, fl=1, tl[++L]=q[i];
			else fr=1, tr[++R]=q[i];
		}
	for (int i=1; i<=L; ++i) q[st+i-1]=tl[i];
	for (int i=L+1; i<=L+R; ++i) q[st+i-1]=tr[i-L];
	if (fl) solve(st,st+L-1,l,mid);
	if (fr) solve(st+L,en,mid+1,r);
}

int main()
{
	read(n);read(m);
	for (int i=1; i<=m; ++i)
	{
		read(q[i].opt),read(q[i].l),read(q[i].r),read(q[i].k);
		if (q[i].opt==2) q[i].id=++cnt;
	}
	solve(1,m,-n,n);
	for (int i=1; i<=cnt; ++i) write(ans[i],'\n');
	IO::flush();
	return 0;
}
```