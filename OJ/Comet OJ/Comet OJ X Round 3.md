[TOC]

# A. 等差数列

## title

[【XR-3】等差数列](https://cometoj.com/contest/64/problem/A)

简化题意：

>小 X 给了你一个等差数列的前两项以及项数，请你求出这个等差数列各项之和。
>
>等差数列：对于一个 $n$ 项数列 $a$，如果满足对于任意 $i \in [1,n)$，有 $a_{i+1} - a_i = d$，其中 $d$ 为定值，则称这个数列为一个等差数列。
>
>$|a_1|,|a_2| \le 10^6$。
>
>$3 \le n \le 10^6$。

## analysis

等差数列求和公式：
$$
S_n=na_1+\frac{n*(n-1)}{2}d
$$


注意开 `long long`。

时间复杂度：$O(1)$。

## code

```cpp
#include<bits/stdc++.h>

typedef long long ll;

namespace IO
{
	char buf[1<<15],*fs,*ft;
	inline char getc() { return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++; }
	template<typename T>inline void read(T &x)
	{
		x=0;
		T f=1, ch=getchar();
		while (!isdigit(ch) && ch^'-') ch=getchar();
		if (ch=='-') f=-1, ch=getchar();
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
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

int main()
{
	ll a1,a2,n;read(a1);read(a2);read(n);
	ll d=a2-a1;
	write(n*a1+(n*(n-1)/2)*d,'\n');
	IO::flush();
	return 0;
}
```

# B. 小道消息

## title

[【XR-3】小道消息](https://cometoj.com/contest/64/problem/B)

简化题意：

>小 X 想探究小道消息传播的速度有多快，于是他做了一个社会实验。
>
>有 n*n* 个人，其中第 i*i* 个人的衣服上有一个数 i+1*i*+1。小 X 发现了一个规律：当一个衣服上的数为 i*i* 的人在某一天知道了一条信息，他会在第二天把这条信息告诉衣服上的数为 j*j* 的人，其中 \gcd(i,j)=1gcd(*i*,*j*)=1（即 i,j*i*,*j* 的最大公约数为 11）。在第 00 天，小 X 把一条小道消息告诉了第 k*k* 个人，小 X 想知道第几天时所有人都会知道这条小道消息。
>
>可以证明，一定存在所有人都知道了这条小道消息的那一天。

## analysis

前置技能：[伯特兰-切比雪夫定理](https://baike.baidu.com/item/伯特兰-切比雪夫定理/2053704)。

刚开始也是一头懵，这种题明显属于你要是了解这个定理就写出来了，要是不了解，你就得看半天百度百科，这还怎么写？（都懂得）

比赛时选择放弃，下场后再研究。

看了 [xht](https://www.xht37.com/comet-oj-contest-9-x-round-3-题解/#lwptoc3) 的题解，天，原来是这个意思（百度百科真害人，逃）：

如果 $k+1$ 是质数且 $2(k+1)>n+1$，则答案为 $1$，因为它一定与 $2\sim n+1$ 的数（除了自己本身）互质。

否则答案为 $2$，因为根据伯特兰-切比雪夫定理，$k+1$ 一定与 $2\sim n+1$ 中最大的质数互质，因此第一天衣服上写有这个最大质数的人一定会得到这条小道消息，那么在第二天所有人都会知道。

时间复杂度：$O(\sqrt n)$ （为判断素数的时间复杂度）。

## code

```cpp
#include<bits/stdc++.h>

typedef long long ll;

namespace IO
{
	char buf[1<<15],*fs,*ft;
	inline char getc() { return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++; }
	template<typename T>inline void read(T &x)
	{
		x=0;
		T f=1, ch=getchar();
		while (!isdigit(ch) && ch^'-') ch=getchar();
		if (ch=='-') f=-1, ch=getchar();
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
		x*=f;
	}
}

using IO::read;

inline bool check(ll k)
{
	for (int i=2; i<=sqrt(k); ++i)
		if (k%i==0) return 0;
	return 1;
}

int main()
{
	ll n,k;
	read(n);read(k);
	if (check(k+1) && (k+1)*2>n+1) puts("1");
	else puts("2");
	return 0;
}
```

# C. 核心城市

## title

[【XR-3】核心城市](https://cometoj.com/contest/64/problem/C)

简化题意：

>X 国有 $n$ 座城市，$n − 1$ 条长度为 $1$ 的道路，每条道路连接两座城市，且任意两座城市都能通过若干条道路相互到达，显然，城市和道路形成了一棵树。
>
>X 国国王决定将 $k$ 座城市钦定为 X 国的核心城市，这 $k$ 座城市需满足以下两个条件：
>
>1. 这 $k$ 座城市可以通过道路，在不经过其他城市的情况下两两相互到达。
>2. 定义某个非核心城市与这 $k$ 座核心城市的距离为，这座城市与 $k$ 座核心城市的距离的最小值。那么所有非核心城市中，与核心城市的距离最大的城市，其与核心城市的距离最小。你需要求出这个最小值。

## analysis

很像树网的核，对吧，然而不一样，不过还是能水不少分的。

说一下正解吧：

- $k=1$，很明显，核心城市为整棵树的中心（直径上的中点）。
- $k\not= 1$，先把树的中心当做根，然后依次贪心地把点加进核心城市集合中，直到核心城市的数量$=k$。
  * 关键，怎么贪心？
  * 定义 $F(x)$ 为以根为树的中心时，点 $x$ 离自己子树中叶子的最大距离。
  * 那么图贪心策略就是：每次在与 **当前确定的核心城市** 相连的 **非核心城市** 中选择 $f$ 最大的城市加入到核心城市中。（我使用队列维护的）

- 解决，时间复杂度：$O(n\log n)$。

## code

```cpp
#include<bits/stdc++.h>

const int maxn=1e5+10;

namespace IO
{
	char buf[1<<15],*fs,*ft;
	inline char getc() { return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++; }
	template<typename T>inline void read(T &x)
	{
		x=0;
		T f=1, ch=getchar();
		while (!isdigit(ch) && ch^'-') ch=getchar();
		if (ch=='-') f=-1, ch=getchar();
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
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

int ver[maxn<<1],Next[maxn<<1],head[maxn],len,In[maxn];
inline void add(int x,int y)
{
	ver[++len]=y,Next[len]=head[x],head[x]=len,++In[y];
}

int dep[maxn],cnt[maxn];
int main()
{
	int n,k;read(n);read(k);
	for (int i=1,x,y; i<n; ++i) read(x),read(y),add(x,y),add(y,x);
	std::queue<int>q;
	for (int i=1; i<=n; ++i)
		if (In[i]==1) q.push(i),dep[i]=1;
	while (!q.empty())
	{
		int x=q.front();
		q.pop();
		for (int i=head[x]; i; i=Next[i])
		{
			int y=ver[i];
			if (In[y]==1) continue;
			dep[y]=std::max(dep[y],dep[x]+1);
			if (--In[y]==1) q.push(y);
		}
	}
	for (int i=1; i<=n; ++i) ++cnt[dep[i]];
	int sum=0;
	for (int i=1; i<=n; ++i)
	{
		sum+=cnt[i];
		if (n-sum<=k) { write(i,'\n'); break; }
	}
	IO::flush();
	return 0;
}
```

# D. 系统设计

## title

[【XR-3】系统设计](https://cometoj.com/contest/64/problem/D)

简化题意：

>小 X 需要你设计一个系统。
>
>这个系统首先需要输入一棵 $n$ 个点的有根树和一个长度为 $m$ 的序列 $a$ ，接下来需要实现 $q$ 个操作。
>
>操作分两种：
>
>1. `1 x l r` 表示设定起点为有根树的节点 $x$，接下来依次遍历 $l \sim r$。当遍历到 $i$ 时，从当前节点走向它的编号第 $a_i$ 小的儿子。如果某一时刻当前节点的儿子个数小于 $a_i$ ，或者已经遍历完 $l \sim r$，则在这个点停住，并输出这个点的编号，同时停止遍历。
>
>2. `2 t k` 表示将序列中第 $t$ 个数 $a_t$ 修改为 $k$。

## analysis

前置技能：

- 字符串哈希；
- 树上数组/线段树上二分（鬼才写线段树）。

这道题强烈推荐出题人大爷 [xht](https://www.xht37.com/comet-oj-contest-9-x-round-3-题解/#lwptoc3) 的 $blog$。（不想画图）。

## code

```cpp
#include<bits/stdc++.h>

typedef long long ll;
const int maxn=5e5+10;
typedef int iarr[maxn];

namespace IO
{
	char buf[1<<15],*fs,*ft;
	inline char getc() { return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++; }
	template<typename T>inline void read(T &x)
	{
		x=0;
		T f=1, ch=getchar();
		while (!isdigit(ch) && ch^'-') ch=getchar();
		if (ch=='-') f=-1, ch=getchar();
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
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

ll P[maxn];
int n,m,q,rt,id;
struct Hash_Table
{
	ll c[maxn];
	inline int lowbit(int x) { return x & -x; }
	inline void add(int x,ll y) { y*=P[x]; while (x<=n) c[x]+=y, x+=lowbit(x); }
	inline ll ask(int x) { ll ans=0; while (x) ans+=c[x], x-=lowbit(x); return ans; }
	inline ll hsh(int l,int r) { return (ask(r)-ask(l-1))*P[maxn-1-l]; }
}T1, T2;

std::vector<int>v[maxn];
iarr siz,dfn,top,pos,ed,a,fa;
inline void dfs1(int x)
{
	siz[x]=1;
	sort(v[x].begin(),v[x].end());
	for (int i=0; i<(int)v[x].size(); ++i)
	{
		int y=v[x][i];
		dfs1(y);
		siz[x]+=siz[y];
	}
}

inline void dfs2(int x,int topf)
{
	dfn[x]=++id;
	ed[x]=x;
	top[x]=topf;
	pos[id]=x;
	if (!v[x].size())
	{
		T1.add(dfn[x],-23333);
		return ;
	}
	int t=0;
	for (int i=1; i<(int)v[x].size(); ++i)
		if (siz[v[x][i]]==siz[v[x][t]]) t=i;
	dfs2(v[x][t],topf);
	ed[x]=ed[v[x][t]];
	T1.add(dfn[x],t+1);
	for (int i=0; i<(int)v[x].size(); ++i)
		if (i^t) dfs2(v[x][i],v[x][i]);
}

inline int LCP(int L,int R,int l,int r)
{
	int lp=1, rp=min(R-L+1,r-l+1), ans=0;
	while (lp<=rp)
	{
		int mid=(lp+rp)>>1;
		if (T1.hsh(L,L+mid-1)==T2.hsh(l,l+mid-1)) ans=mid, lp=mid+1;
		else rp=mid-1;
	}
	return ans;
}

inline int solve(int x,int l,int r)
{
	int L=dfn[x], R=dfn[ed[x]];
	while (1)
	{
		int len=LCP(L,R,l,r);
		L+=len, l+=len;
		int x=pos[L];
		if (l>r || v[x].size()<a[l]) return x;
		x=v[x][a[l]-1];
		L=dfn[x], R=dfn[ed[x]];
		++l;
		if (l>r) return x;
	}
}

int main()
{
	P[0]=1;
	for (int i=1; i<maxn; ++i) P[i]=P[i-1]*4238197ll;
	read(n);read(m);read(q);
	for (int i=1; i<=n; ++i)
	{
		read(fa[i]);
		if (!fa[i]) rt=i;
		v[fa[i]].push_back(i);
	}
	dfs1(rt);
	dfs2(rt,rt);
	for (int i=1; i<=m; ++i) read(a[i]), T2.add(i,a[i]);
	while (q--)
	{
		int opt;read(opt);
		if (opt==1)
		{
			int x,l,r;
			read(x);read(l);read(r);
			write(solve(x,l,r),'\n');
		}
		else
		{
			int t,k;read(t);read(k);
			T2.add(t,k-a[t]);
			a[t]=k;
		}
	}
	IO::flush();
	return 0;
}
```

# E. Namid[A]me

## title

[【XR-3】Namid[A]me](https://cometoj.com/contest/64/problem/E)

简化题意：

>小 X 给了你一棵 $n$ 个点的树，点有点权。
>
>你需要求出下列式子模 $786433$ 的值：
>
>$\sum_{1\leq u\leq v\leq n}f(u,v)^{f(u,v)}$
>
>其中 $f(u,v)$ 表示 $u$ 到 $v$ 的最短路径上所有点的点权按位与在一起之后的值。
>
>提示：为了方便你的计算，这里我们认为 $0^0=0$。另外， $786433$ 是一个质数，同时也是一个不常用的 NTT 模数，它的原根为 $10$，如果你不知道什么是 NTT 或者不知道什么是原根，你可以忽略这个提示。

## analysis

如何快速计算 $x^x\mod P$ ？快速幂搞定。

接下来就要考虑树上一条链该如何计算了。

这时候所有链其实相当于一个区间，考虑枚举右端点 $r$ ，那么对于 $[l,r]$ 内所有数的与设为 $x_l$ ，注意到若 $x_l≠x_{l+1}$，由于 $x_l = x_{l+1} \operatorname{\texttt{and}} a_l$，那么必然是至少在 $x_{l+1}$ 中的一个二进制位从 $1$ 变为 $0$ 。

因此，从 $x_l$ 到  $x_1$ ，必然最多只有 $w+1$ 种取值。我们考虑只维护被取到的值分别取到了多少次即可。

处理子树部分：

1. 对于一个有 $d$ 个叶子的子树，在维护时子树内 **每个节点** 到 **子树的根** 的路径上的 **与和** 总共不超过 $d(w+1)$ 种取值，这是因为将 **每个叶子** 到 **根的一条链内** 的取值各自都不超过 $w+1$ ，所以我们只需在 DFS 的过程中维护 <font color=blue>每个子树</font>内 **所有能取到的值的出现次数** 即可。这一部分的复杂度为 $O(ndw)$。
2. 还需计算 **路径两端点** 在 **不同子树的路径** 的答案，这一部分我们暴力枚举，注意到 **两个叶子** 只会在 **它们的 LCA 位置** 为合并的复杂度贡献 $(w+1)^2$，因此计算这一部分答案的总代价为 $O((dw)^2)$。但是也有个上限 $O(n^2)$ ，因为只有这么多条路径。

因为 $O(min(n,dw)^2)\leqslant O(ndw)$ ，所以总时间复杂度为 $O(ndw)$ 。 

这道题的题解基本都是参照 [xht](https://www.xht37.com/comet-oj-contest-9-x-round-3-题解/#lwptoc3) ，人家写的是真详细，思路还清楚。

## code

```cpp
#include<bits/stdc++.h>

const int maxn=2e5+10,mod=786433;

namespace IO
{
	char buf[1<<15],*fs,*ft;
	inline char getc() { return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++; }
	template<typename T>inline void read(T &x)
	{
		x=0;
		T f=1, ch=getchar();
		while (!isdigit(ch) && ch^'-') ch=getchar();
		if (ch=='-') f=-1, ch=getchar();
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
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

inline int Quick_power(int a)
{
	if (!a) return 0;
	int ans=1, b=a;
	while (b)
	{
		if (b&1) ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return ans;
}

int ans;
struct Orz
{
	int a[maxn],b[maxn],c[maxn];
	inline void Clear()
	{
		*a=0;
	}

	inline void insert(int x)
	{
		a[++*a]=x;
	}

	inline void solve(int val)
	{
		std::sort(a+1,a+*a+1);
		int top=0, last=1;
		for (int i=2; i<=(int)(*a)+1; ++i)
			if (i==(*a)+1 || a[i]^a[i-1]) b[++top]=a[i-1], c[top]=i-last, last=i;
		int sum=0;
		for (int i=1; i<=top; ++i)
			for (int j=i; j<=top; ++j)
			{
				int times=( i==j ? 1ll*c[i]*(c[i]+1)/2%mod : 1ll*c[i]*c[j]%mod );
				sum=(sum+1ll*times*Quick_power(b[i]&b[j]))%mod;
			}
		ans=(ans+1ll*val*sum)%mod;
	}
}T1, T2;

int ver[maxn<<1],Next[maxn<<1],head[maxn],len;
inline void add(int x,int y)
{
	ver[++len]=y,Next[len]=head[x],head[x]=len;
}

int siz[maxn],pos,maxv;
bool vis[maxn];
inline void dfs(int x,int fa,int n)//这里的 n 必须做传参一起传过去，不然蜜汁 TLE
{
    siz[x]=1;
    int maxpart=0;
    for (int i=head[x];i;i=Next[i])
    {
    	int y=ver[i];
    	if (vis[y] || y==fa) continue;
		dfs(y,x,n);
        siz[x]+=siz[y];
        maxpart=max(maxpart,siz[y]);
	}
    maxpart=max(maxpart,n-siz[x]);
	if (maxpart<maxv) maxv=maxpart, pos=x;
}

int a[maxn];
inline void get(int x,int fa,int val)
{
	val&=a[x];
	T1.insert(val);
	T2.insert(val);
	for (int i=head[x]; i; i=Next[i])
	{
		int y=ver[i];
		if (y==fa || vis[y]) continue;
		get(y,x,val);
	}
}

inline void divide(int x,int n)
{
	maxv=1<<30;
	dfs(x,0,n);
	vis[x=pos]=1;
	T1.Clear();
	T1.insert(a[x]);
	for (int i=head[x]; i; i=Next[i])
	{
		int y=ver[i];
		if (vis[y]) continue;
		T2.Clear();
		get(y,x,a[x]);
		T2.solve(mod-1);
	}
	T1.solve(1);
	for (int i=head[x]; i; i=Next[i])
	{
		int y=ver[i];
		if (!vis[y]) divide(y,siz[y]>siz[x] ? n-siz[x] : siz[y]);
	}
}

int main()
{
	int n;read(n);
	for (int i=1; i<=n; ++i) read(a[i]);
	for (int i=1,x,y; i<n; ++i) read(x),read(y),add(x,y),add(y,x);
	divide(1,n);
	write(ans,'\n');
	IO::flush();
	return 0;
}
```

# F. Unknown Mother-Goose

## title

[【XR-3】Unknown Mother-Goose](https://cometoj.com/contest/64/problem/F)

简化题意：

>小 X 得到了一个正整数 $n$ 和一个正整数集合 $S$，他想知道有多少个正整数 $x$ 满足以下所有条件：
>
>- $3 \le x \le n$
>- 存在 $a \in S, x \equiv 0 \mod a$
>- 存在 $b \in S,x-1 \equiv 0 \mod b$
>- 存在 $c \in S,x-2 \equiv 0 \mod c$
>
>请你帮小 X 求出来。

## analysis

比赛的时候，看到这题，以为要解同余方程，得嘞，我走了。

看过题解后，这题还能用 $bitset$ 写暴力标算？这也太神仙了吧。

在 $bitset$ 中把是 $S$ 中每一个元素的倍数的下标全部赋值成 $1$，那么，如果 $a_x,a_{x−1},a_{x+1}$ 都是 $1$，$x$ 就是合法的。

那么问题就变成了数 $bitset$ 里有几组三个连续的 $1$ 。

可以每 $64$ 位分一块，块内算一下内部有几组三个连续的 $1$，然后算块和块之间有几组三个连续的 $1$，这个枚举一下即可。

时间复杂度： $O(\frac{n}{8})$ 。

大佬又提出可以用 $S$ 中的元素是否大于 $64$ 来分情况处理，可以跑得更快些（具体的还请看大佬的题解）。

总时间复杂度 $O(\frac{n|S|}{64}+\frac{n}{8})$ （看起来好高，但是处理的地址连续也不会频繁调用系统栈，所以是可以很快通过的）。

好妙。好妙。好妙。

## code

```cpp
#include<bits/stdc++.h>

typedef unsigned long long ull;
const int maxn=1e9+1,maxm=1e5+10,grhsmt=(1<<16)-1;

namespace IO
{
	char buf[1<<15],*fs,*ft;
	inline char getc() { return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++; }
	template<typename T>inline void read(T &x)
	{
		x=0;
		T f=1, ch=getchar();
		while (!isdigit(ch) && ch^'-') ch=getchar();
		if (ch=='-') f=-1, ch=getchar();
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
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

int cnt[maxm],ans;
ull t[maxn/64+555],s[1005];
int main()
{
	int n,S;read(n);read(S);
	for (int i=1,x; i<=S; ++i)
	{
		read(x);
		if (x>100)
			for (int j=0; j<=n; j+=x) t[j>>6]|=1ull<<(j&63);
		else
		{
			for (int j=0; j<x; ++j) s[j]=0;
			for (int j=0; j<=63; ++j)
			{
				int p=j*x;
				s[p>>6]|=1ull<<(p&63);
			}
			int j=0;
			for ( ; j+x*64<=n; j+=x*64)
				for (int k=0, q=j/64; k<x; ++k) t[q+k]|=s[k];
			for ( ; j<=n; j+=x) t[j>>6]|=1ull<<(j&63);
		}
	}
	if (t[0]&1) --t[0];
	for (int i=0; i<=grhsmt; ++i) cnt[i]=cnt[i>>1]+(i&1);
	for (int i=0, l=0; l<=n; l+=64, ++i)
	{
		ull tmp=t[i]&(t[i]>>1)&(t[i]<<1);
		ans+=cnt[tmp & grhsmt], tmp>>=16;
		ans+=cnt[tmp & grhsmt], tmp>>=16;
		ans+=cnt[tmp & grhsmt], tmp>>=16;
		ans+=cnt[tmp & grhsmt];
		if ((t[i]>>63) && (t[i+1]<<63))
		{
			if (t[i]&(1ull<<62)) ++ans;
			if (t[i+1]&2) ++ans;
		}
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
```