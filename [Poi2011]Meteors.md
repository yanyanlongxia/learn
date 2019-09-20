# title

[BZOJ 2527](https://lydsy.com/JudgeOnline/problem.php?id=2527)

[LUOGU 3527](https://www.luogu.org/problem/P3527)

简化题意：

> 给定一个环，有 $M$ 个节点， $N$ 个国家，每个节点有一个所属国家， $K$ 次事件，每次对 $[l,r]$ 区间上的每个点点权加上一个值，求每个国家最早多少次操作之后所有点的点权和能达到一个值 $P_i$ 。

# analysis

在刚刚看到每次对 $[l,r]$ 区间上的每个点点权加上一个值时，我想到这可以用 $BIT$ 来维护。

然后对于询问，我有些疑惑，有一个很暴力的写法，即每次用 $BIT$ 区间差分完成对区间累加（这个仍需要分情况，毕竟是个环，不过处理的没有我想象的那么复杂）之后， $O(NM)$ 扫一遍，看这些节点所属于的国家的值 $P_i$ 是否达到，总复杂度稍高，但是也算是一种暴力了。

不过当时这题读的有些迷，没搞清楚环上的节点和国家的关系，没有去处理，所以上面才那样做了，后来看了题解，懂了题意，知道了这个关系记录一下，差不多上面的暴力会好写一些，复杂度基本仍是一样。

不过这个暴力和正解是真的一点关系都没有的了，我在前期思考的时候，因为看过标签中有二分答案，所以试着用此种方法分析了一下，但是不知道安放何处。

看过题解后，方明白，整体二分，将所有 $K$ 个事件放在一起处理，因为对于每个点（也可以说是每个国家）来说，它的值总是递增的，因此满足整体二分的条件：有单调性。

剩下的就是一些整体二分的基本东西，不过这道题目是在 $[L,R]$ 的国家区间里去搞一个二分的答案区间 $[l,r]$ ，其他的应该都差不多了。

这道题也差不多被别人当做入门整体二分的题目来讲解了，无需赘述，代码可说明一切（当然，讲解资料还是要有的：[OI-wiki parallel-binsearch](https://oi-wiki.org/misc/parallel-binsearch/)）。

（插曲：此题累加过程中一个点的值可能会爆 `long long` ，所以要适时 `break` 。）

# code

```cpp
#include<bits/stdc++.h>

#define G ch=getchar()

typedef long long ll;
const int maxn=3e5+10;
typedef int iarr[maxn];

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

int n, m;
namespace BIT
{
	ll c[maxn];
	inline int lowbit(int x) { return x & -x; }
	inline void add(int x,int k) { while (x<=m)	c[x]+=k, x+=lowbit(x); }
	inline ll ask(int x) { ll ans=0; while (x) ans+=c[x], x-=lowbit(x); return ans; }
}

using BIT::add;
using BIT::ask;

struct Orz{ll x; int id;} q[maxn], q1[maxn], q2[maxn];
std::vector<int> a[maxn];

iarr st, ed, val, ans;
inline void Change(int x,int f)//区间差分
{
	if (st[x]<=ed[x]) add(st[x],val[x]*f), add(ed[x]+1,-val[x]*f);
	else add(st[x],val[x]*f), add(ed[x]+1,-val[x]*f), add(1,val[x]*f);
}

inline void solve(int L,int R,int l,int r)//[L,R] 国家区间 [l,r] 二分答案区间
{
	if (L>R) return ;
	if (l==r)
	{
		for (int i=L; i<=R; ++i) ans[q[i].id]=l;
		return ;
	}

	int mid=(l+r)>>1;
	int t1=0, t2=0; ll tmp=0;
	for (int i=l; i<=mid; ++i) Change(i,1);
	for (int i=L; i<=R; ++i)
	{
		tmp=0;
		for (int j=0; j<(int)a[q[i].id].size(); ++j)
		{
			tmp+=ask(a[q[i].id][j]);
			if (tmp>=q[i].x) break;
		}
		if (tmp>=q[i].x) q1[++t1]=q[i];
		else q[i].x-=tmp, q2[++t2]=q[i];
	}
	for (int i=l; i<=mid; ++i) Change(i,-1);

	for (int i=L, j=1; j<=t1; ++i, ++j) q[i]=q1[j];
	for (int i=L+t1, j=1; j<=t2; ++i, ++j) q[i]=q2[j];

	solve(L,L+t1-1,l,mid), solve(L+t1,R,mid+1,r);
}

int main()
{
	read(n), read(m);
	for (int i=1, x; i<=m; ++i) read(x), a[x].push_back(i);
	for (int i=1, x; i<=n; ++i) read(x), q[i]=(Orz){x,i};

	int k;read(k);
	for (int i=1; i<=k; ++i) read(st[i]), read(ed[i]), read(val[i]);
	st[++k]=1, ed[k]=m, val[k]=1e9;

	solve(1,n,1,k);
	for (int i=1; i<=n; ++i)
		if (ans[i]==k) *IO::fe++='N', *IO::fe++='I', *IO::fe++='E', *IO::fe++='\n';
		else write(ans[i],'\n');
	IO::flush();
	return 0;
}
```