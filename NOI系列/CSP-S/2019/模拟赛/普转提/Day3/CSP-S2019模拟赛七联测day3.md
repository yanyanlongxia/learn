[TOC]

# A. 序列

## title

[zhengruioi](http://zhengruioi.com/problem/1004)

题意：

>给出一个长度为 $n$ 的整数序列， $a_1,a_2,⋯,a_n$ ，序列中的数互不相同。
>
>给出质数 $p$ 。
>
>请问有多少序列中的有序数对 $(x,y)$ 满足 $(x^2+y)^2\equiv(x^2−y)^2+1(\mod p)$ 。

## analysis

$30pts$ 的 $O(N^2)$ 暴力是很明显的，只不过，取模真是捉弄死我了，交了七八遍，才过了这个部分分。

$100pts$ 的算法便是把这式子化简：
$$
(x^2+y)^2\equiv(x^2−y)^2+1(\mod p)\\
4x^2y\equiv1(\mod p)
$$


说明只需要 $4x^2$ 和 $y$ 互为逆元即可，当然还要特判没有逆元的情况。

开 `long long` 是必须的。

## code

$30pts$

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

typedef long long ll;
const int maxn=1e5+10;

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

#define sq(x) (x*x)

ll a[maxn], p;
int main()
{
	int n; read(n), read(p);
	for (int i=1; i<=n; ++i) read(a[i]);

	ll ans=0;
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=n; ++j)
		{
			if (i==j) continue;
			ll x=a[i], y=a[j];
			ll l=sq( (sq(x)%p+y)%p )%p;
			ll r=( sq( (sq(x)%p-y+p)%p)+1 )%p;
			if (l==r) ++ans;
		}
	write(ans,'\n');
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
const int maxn=1e5+10;

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

inline ll Quick_Power(ll a,ll b,ll p)
{
	ll ans=1;
	while (b)
	{
		if (b&1) ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}

ll a[maxn], p;
std::map<ll,ll> mark;

int main()
{
	int n; read(n), read(p);
	for (int i=1; i<=n; ++i)
	{
		read(a[i]);
		if (!4*a[i]%p*a[i]%p) continue;
		else ++mark[4*a[i]%p*a[i]%p];
	}
	ll ans=0;
	for (int i=1; i<=n; ++i)
	{
		ll inv=Quick_Power(a[i],p-2,p);
		if (!inv) continue;
		ans+=mark[inv];
		if (4*a[i]%p*a[i]%p==inv) --ans;
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
```

# B. 汽水

## title

[zhengruioi](http://zhengruioi.com/problem/1005)

题意：

>现在有 $K$ 种浓度的糖浆，浓度分别为
>$$
>\frac{a_1}{M},\frac{a_2}{M},⋯,\frac{a_k}{M}
>$$
>
>
>这 $K$ 种原料的数量是无限的。
>
>每次可以将整数毫升的几种糖浆勾兑到一起，就可以得到新的浓度的糖浆。
>
>问：想要得到浓度为 $\frac{N}{M}$ 的糖浆 ，至少要用多少毫升的糖浆原料。
>
>如果得不到，输出 $-1$ 。

## analysis

哈哈， $-1$ 有 $10pts$ 。

还是看看 $100pts$ 怎么拿吧， $Dp+$ 图论。

所以说这道小题还挺好的。

将每种糖浆都减去 $N$ ，那么问题就变成了凑 $0$ ，不妨设每种糖浆使用了 $K_i$ 升，那么就是要求让 $\sum K_i*(a_i-N)$ 的最小的 $\sum K_i$ 。

那么这个就可以转化成一个图论模型，点 $i$ 表示当前的和为 $i$ 。那么利用不同的糖浆连边，本质是要找一个从 $0$ 开始的最小的环，用 $BFS$ 即可。

那么一个点 $x$ 可以向哪些点连边？

假设有浓度（已经减去平均值的浓度）为 $a$ 的糖浆，那么所有 点 $x$ 向点 $x+a$ 连边，然后更新 $x+a$ 的要用的糖浆原料的毫升数。


注意到我们只需要开到 $[-M,M]$ 这个区间即可。

## code

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

typedef long long ll;
const int maxn=1e5+10;
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

const int M=1e3;
iarr s, d; int K, n, m;
std::queue<int>q;

inline int bfs()
{
	while (!q.empty())
	{
		int x=q.front();
		q.pop();
		if (!x) return d[x+M];
		for (int i=-M; i<=M; ++i) if (s[i+M])
		{
			int y=i+x;
			if (-m<=y && y<=m && !d[y+M]) d[y+M]=d[x+M]+1, q.push(y);
		}
	}
 return -1;
}

int main()
{
	read(K), read(n), read(m);
	for (int i=1, x; i<=K; ++i)
	{
		read(x);
		x-=n;
		s[x+M]=d[x+M]=1, q.push(x);
	}
	write(bfs(),'\n');
	IO::flush();
	return 0;
}
```

# C. 树

## title

[zhengruioi](http://zhengruioi.com/problem/1006)

题意：

>对于一棵树，我们可以用邻接表存储，也可以直接存储每个点的父亲是谁。
>
>不妨用 $fa_i$ 数组来存储。对于根节点，他的父亲是他本身。
>
>现在给出一个数组 $fa_i$ ，但是它有点问题，不能表示一棵树。
>
>你能否尽可能少的修改 $fa_i$ 中的元素，使其表示的结构是一棵树。
>
>请问最少修改的元素个数是多少。

## analysis

看到题后，我的想法便是找根，然后搞联通块，多个连通块的话，就把其中一个联通块当做根，剩下的联通块跟它连一下，这样答案就是连通块大小 $-1$ ，不过我这个好像只是正解中的一部分。

另一部分便是只有一个连通块的时候，只需要断一条边即可。

这个题的实现也是有些好玩的，看看代码吧。

## code

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

typedef long long ll;
const int maxn=2e5+10;

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

int fa[maxn];
inline int get(int x)
{
	return fa[x]==x ? x : fa[x]=get(fa[x]);
}

int main()
{
	int n, ans=0, cnt=0; read(n);
	for (int i=1; i<=n; ++i) fa[i]=i;
	for (int i=1, a; i<=n; ++i)
	{
		read(a);
		int x=get(a), y=get(i);
		if (x^y || a==i) fa[x]=y;
		else ++cnt;
	}
	for (int i=1; i<=n; ++i) if (fa[i]==i) ++ans;
	cnt==ans ? write(ans,'\n') : write(ans-1,'\n');
	IO::flush();
	return 0;
}
```

# D. DAG

## title

[zhengruioi](http://zhengruioi.com/problem/1007)

题意：

>给出一个无向图，请你给边定向成为一个有向无环图（DAG），使得最长路最短。
>
>这里的最长路指经过的边的数量。

## analysis

答案为最小染色数或最小独立集覆盖 $-1$ 。

这是为什么呢？

首先如果有个染色方案的话 你就可以构造出对应的分层图，就是假设 $i$ 的染色是 $c_i$ ，那么 $(i,j)$ 的边就定向成从编号小的往编号大的走。

然后其次是，如果最长路是 $x$ ，那么就会有 $x+1$ 的染色方案，因为 $d_i$ 表示点 $i$ 的最长路，然后每个点染色成 $d_i$ 就可以了。

做法就是 $O(n^22^n)$ 预处理出子图中的所有独立集，然后状压 $Dp$ ，设 $f_s$ 表示子图点集为 $s$ 时的最小独立集覆盖，然后枚举子集中的独立集进行转移。时间复杂度为 $\sum^n_{i=0} C^i_n 2_i=O(3^n)$ 。

## code

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

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

int a[20][20], f[1<<20];
bool ok[1<<20];
int main()
{
	int n, m; read(n), read(m);
	for (int i=1, x, y; i<=m; ++i) read(x), read(y), a[x-1][y-1]=a[y-1][x-1]=1;

	for (int s=1; s<(1<<n); ++s)
	{
		ok[s]=1;
		for (int j=0; j<n; ++j) if (s>>j&1)
			for (int k=0; k<n; ++k) if (s>>k&1)
				if (a[k][j] || a[j][k]) ok[s]=0;
	}

	for (int s=1; s<(1<<n); ++s)
	{
		f[s]=1e9;
		if (ok[s]) { f[s]=1; continue; }
		for (int t=(s-1)&s; t; t=(t-1)&s)
			if (ok[t]) chkMin(f[s],f[s^t]+1);
	}
	write(f[(1<<n)-1]-1,'\n');
	IO::flush();
	return 0;
}
```

# summary

这一场没有参加，所以其实也没有什么好感慨的。

唯一一个想说的，可能是比赛里的题尽量要多复盘。