[TOC]

# Write in the front

这套题目由于学长当时忘了存数据，所以我所存放的代码都是与 $std$ 对拍来验证正确性的（当然还有瞪眼法）。

# A. 中间值（median）

## title

![](https://img2018.cnblogs.com/blog/1587478/201909/1587478-20190920170613362-896865570.png)

## analysis

出题人懒，写的题解是个什么东西。

对于此题，我第一眼就在想这不会 $T1$ 就来个数据结构吧，有点恶心人啊。

不过，我不会正解，所以写了个 $30\%$ 的暴力，修改 $O(1)$ ，查询 $O(n\log n)$ ，查询便是直接把这两个区间里的数组成一个新的数组，排序一下，输出中间数即可。

其实这个时候正解已经呼之欲出（即将想出来之意）了，修改 $O(1)$ ，说实在的，已经不需要任何数据结构来优化了，数组就够了（笑；那么优化的地方便是这个合并加查询的操作了，不用多说，这个序列最终是非严格单调递增的（题目中也说了，所以出题人说这题是送分题），那么二分答案。

二分一个答案，对于比它大的数，放在右边，比它小的数，放在左边，这是一个比较基础的思路了，不过对于这题来说，不够简便，复杂度仍然不够优。

不过还好，还有一种较为简便，而且普适性更强的方法（因为这题其实可以搞成问第 $K$ 大数，出题人这货懒，不愿意费劲儿，结果我还是死的很惨）。

假设当前要取的是区间的第 $K$ 大，将 $K$ 折半，放在两个区间的对应位置 $s,t$ 上，比较 $a[s],b[t]$ ，不妨设 $a[s]<b[t]$ ，那么答案可以化归至区间 $[l_1,s-1],[l_2,r_2]$ 的第 $\frac{K}{2}$ 大数 （因为 $a$ 序列比 $a[s]$ 小的那些数一定可以全部舍去），递归即可。

## code

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

const int maxn=5e5+10;
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

inline int cal(int l,int r,int *a,int s,int t,int *b)
{
	int len=(r-l+1 + t-s+1)>>1, L=l, R=r;
	while (L<=R)
	{
		int m=(L+R)>>1, c=s + len-(m-l+1);//a[mid] b[center]
		if (c==s-1 && m-l==len && a[m]<=b[s]) return a[m];//样例 1 的第一个询问

		if (c<s) { R=m-1; continue; }
		else if (c>t) { L=m+1; continue; }

		if (a[m]>=b[c] && (a[m]<=b[c+1] || c==t)) return a[m];
		if (a[m]>=b[c]) R=m-1;
		else L=m+1;
	}
	return 0;
}

iarr a, b;
int main()
{
	file("median");

	int n, m; read(n), read(m);
	for (int i=1; i<=n; ++i) read(a[i]);
	for (int i=1; i<=n; ++i) read(b[i]);
	while (m--)
	{
		int opt; read(opt);
		if (opt==1)
		{
			int x, y, z;
			read(x), read(y), read(z);
			!x ? a[y]=z : b[y]=z;
		}
		else
		{
			int l, r, s, t, x;//left right start end
			read(l), read(r), read(s), read(t);
			if (x=cal(l,r,a,s,t,b)) write(x,'\n');
			else write(cal(s,t,b,l,r,a),'\n');
		}
	}
	IO::flush();
	return 0;
}
```

# B. 最小值（min）

## title

![](https://img2018.cnblogs.com/blog/1587478/201909/1587478-20190920170602089-5258099.png)

## analysis

这题吧，刚看的时候看错了，以为最高项为二次，就想着斜率优化用上派场了，然后往下看数据范围，回头再确认一眼题面的时候，发现是三次，顿时懵。

经昕泽学长提醒过后，发现这题 $30\%$ 可以用 $ST$ 表优化 $Dp$ 干掉，其实是比较简单的。

设 $g[i]$ 表示分割 $[1,i]$ 所能得到的最大价值，那么状态转移方程就是：
$$
g[i]=\max_{j=0}^{i-1}\{g[j]+f(\min_{x=j+1}^ia_x)\},g[0]=0
$$


吼吼， $30pts$ 到手了。

正解怎么办哩？（当然，还有那 $20pts$ 的 $A=B=0$ 的，我最终没写出来，哭）

我没想出来，看 $solution$ 了：

吼，首先，上面那个状态转移方程中的 $Max_x=\min_{x=j+1}^ia_x$ 可以用单调栈来维护，体地，单调栈中的元素 $l_1,l_2···l_m$表示 $Max_{l_i}\neq Max_{l_i-1}$ 的每个 $l_i$ （就是最小值变化的转折点），那么有 $\forall x\in[l_i,l_{i+1}-1],Max_x$ 相同，此时 $f$ 值最大的那个点一定最优秀，于是维护 $h_i=\max_{x=l_i}^{l_i+1}g[x]$ ，表示每个取到最小值元素对应区间的最优答案。 

这样的话，每一次的答案就是 $\max h_i+f(Max_{l_i})$ ，采用一棵线段树或者可删除堆维护单调栈即可。

## code

$30pts$

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

typedef long long ll;
const int maxn=2e5+10;
typedef ll larr[maxn];

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

template<typename T>inline bool chkMin(T &a,const T &b) { return a>b ? (a=b, true) : false; }
template<typename T>inline bool chkMax(T &a,const T &b) { return a<b ? (a=b, true) : false; }
template<typename T>inline T min(T a,T b) { return a<b ? a : b; }
template<typename T>inline T max(T a,T b) { return a>b ? a : b; }

larr a, g;
int n, A, B, C, D;
ll f[maxn][20];
inline void pre()
{
	for (int i=1; i<=n; ++i) f[i][0]=a[i];
	int t=log2(n)+1;
	for (int j=1; j<t; ++j)
		for (int i=1; i<=n-(1<<j)+1; ++i) f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}

inline ll query(int l,int r)
{
	int k=log2(r-l+1);
	return min(f[l][k],f[r-(1<<k)+1][k]);
}

inline ll F(ll x)
{
	return ((A*x+B)*x+C)*x+D;
}

int sum;
int main()
{
	file("min");

	read(n), read(A), read(B), read(C), read(D);
	for (int i=1; i<=n; ++i) read(a[i]);
	if (n<=1000)
	{
		pre();
		memset(g,0xcf,sizeof(g));
		g[0]=0;
		for (int i=1; i<=n; ++i)
			for (int j=0; j<i; ++j)
			{
				ll pos=query(j+1,i);
				chkMax(g[i],g[j]+F(pos));
			}
		write(g[n],'\n');
		IO::flush();
		exit(0);
	}
	else write(-1,'\n');
	IO::flush();
	return 0;
}
```

$100pts$

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

typedef long long ll;
const int maxn=(1<<19)-1;
const ll inf=0x3f3f3f3f3f3f3f3fll;

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

template<typename T>inline bool chkMin(T &a,const T &b) { a>b ? (a=b, true) : false; }
template<typename T>inline bool chkMax(T &a,const T &b) { a<b ? (a=b, true) : false; }
template<typename T>inline T min(T a,T b) { return a<b ? a : b; }
template<typename T>inline T max(T a,T b) { return a>b ? a : b; }

int a[maxn], Stack[maxn], top;
ll tree[maxn<<1], f[maxn], Max[maxn];
inline void Up(int i,ll x)
{
	for (tree[i+=maxn]=x; i>>=1; ) tree[i]=max(tree[i<<1],tree[i<<1|1]);
}

int n, A, B, C, D;
inline ll Cal(ll x)
{
	return ((A*x+B)*x+C)*x+D;
}

int main()
{
	file("min");

	read(n), read(A), read(B), read(C), read(D);
	for (int i=1; i<=n; ++i) read(a[i]);

	memset(tree,-0x3f,sizeof(tree)), f[0]=0;
	Stack[++top]=a[1], Max[top]=0, Up(top,Cal(a[top]));
	for (int i=1; i<=n; ++i)
	{
		ll x=f[i]=tree[1];
		while (top && Stack[top]>a[i+1]) chkMax(x,Max[top]), Up(top--,-inf);
		Stack[++top]=a[i+1], Max[top]=x, Up(top,x+Cal(Stack[top]));
	}
	write(f[n],'\n');
	IO::flush();
	return 0;
}
```

# C. 最大值（max）

## title

![](https://img2018.cnblogs.com/blog/1587478/201909/1587478-20190920170545353-156446352.png)

## analysis

这题期望线段树神仙题，滚了滚了。

额，我又滚回来了，好歹说一下现在理解的。

首先呢，把这题用人话说一遍：

> $n$ 个位置，每个位置上有若干个有一定概率出现的数， 给定若干个询问区间，每次询问区间内每个位置上所有数最小值的最大值的期望之和。 

偷个懒，只说 $100pts$ 的做法了，其他的好杂，回来再好好看看 $solution$ 。

按区间左端点排序（出题人比较懒并没有打乱顺序），可以得到每个点被包含的区间也是一个区间。

这样可以实现点和区间的转化。

于是问题被转化为将一个区间乘上某一个数。

采用线段树打标记维护，每次加上全局的答案即可，复杂度 $O(m\log q)$ ，可以通过全部数据。 

## code

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

const int maxn=1e5+10, maxm=2e5+10, mod=1e9+7;

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

struct Orz{int x,y,p;} o[maxm];
inline bool cmp1(Orz a,Orz b)
{
	return a.y<b.y;
}

struct QwQ{int l,r;} q[maxn];
inline bool cmp2(QwQ a,QwQ b)
{
	return a.l<b.l || (a.l==b.l && a.r<b.r);
}

inline int Quick_power(int a,int b)
{
	int ans=1;
	while (b)
	{
		if (b&1) ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return ans;
}

int ver[maxm<<1], Next[maxm<<1], head[maxm], len;
inline void add(int x,int p)
{
	ver[++len]=1ll*ver[head[x]]*(1-p)%mod, Next[len]=head[x], head[x]=len;
}

int l[maxm], r[maxm], b[maxm], n, m, Q;
struct SGT
{
	int tree[maxn<<2], atag[maxn<<2];
	inline void pushdown(int x,int v)
	{
		atag[x]=1ll*atag[x]*v%mod;
		tree[x]=1ll*tree[x]*v%mod;
	}

	inline void build(int x,int l,int r)
	{
		atag[x]=1;
		if (l==r) { tree[x]=1; return ; }
		int mid=(l+r)>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
		tree[x]=(tree[x<<1]+tree[x<<1|1])%mod;
	}

	inline void Modify(int x,int l,int r,int tl,int tr,int v)
	{
		if (tl==l && r==tr) { pushdown(x,v); return ; }
		if (atag[x]^1) pushdown(x<<1,atag[x]), pushdown(x<<1|1,atag[x]), atag[x]=1;
		int mid=(l+r)>>1;
		if (tl<=mid) Modify(x<<1,l,mid,tl,min(tr,mid),v);
		if (tr>mid) Modify(x<<1|1,mid+1,r,max(tl,mid+1),tr,v);
		tree[x]=(tree[x<<1]+tree[x<<1|1])%mod;
	}

	inline void Change(int x)
	{
		if (l[x]>r[x]) return ;
		int inv=Quick_power(1-(ver[head[x]]-b[x])%mod,mod-2);
		head[x]=Next[head[x]];
		Modify(1,1,Q,l[x],r[x],1ll*(1-(ver[head[x]]-b[x])%mod)*inv%mod);
	}
} sgt;

int main()
{
	file("max");

	read(n), read(m), read(Q);

	int top=0;
	for (int i=1, x, y, p; i<=m; ++i)
	{
		read(x), read(y), read(p);
		if (!p || !y) continue;
		o[++top].x=x, o[top].y=y, o[top].p=p;
	}
	std::sort(o+1,o+top+1,cmp1);

	for (int i=1; i<=n; ++i) ver[++len]=1, head[i]=len;
	for (int i=1; i<=top; ++i) add(o[i].x,o[i].p);
	for (int i=1; i<=n; ++i) b[i]=ver[head[i]];

	for (int i=1; i<=Q; ++i) read(q[i].l), read(q[i].r);
	std::sort(q+1,q+Q+1,cmp2);

	int L=1, R=0;
	for (int i=1; i<=n; ++i)
	{
		while (L<=R && q[L].r<i) ++L;
		while (q[R+1].l<=i && R<Q) ++R;
		l[i]=L, r[i]=R;
	}

	sgt.build(1,1,Q);
	int ans=0;
	o[0].y=0;
	for (int i=top, j; i; i=j)
	{
		for (j=i; o[j].y==o[i].y && j; --j) sgt.Change(o[j].x);
		ans=(ans+1ll*sgt.tree[1]*(o[i].y-o[j].y))%mod;
	}
	ans=(1ll*o[top].y*Q-ans)%mod;
	write((ans+mod)%mod,'\n');
	IO::flush();
	return 0;
}
```

# summary

这套题没啥可总结的吧，写下来也就 $60pts$ ，真的是只写了暴力， $T3$ 是真的比较懵了，不过这种题到最后也要学会去拿个 $30pts$ 左右的，现在更多的是想着怎么把前两道题目打出高分，下面还有昕泽给的另一套题，要好好写一次，估计难度应该比这套小一些。