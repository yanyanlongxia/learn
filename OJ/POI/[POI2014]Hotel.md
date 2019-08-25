# title

[BZOJ 3522](https://lydsy.com/JudgeOnline/problem.php?id=3522)

[LUOGU 3565](https://www.luogu.org/problem/P3565)

加强版：[BZOJ 4543](https://lydsy.com/JudgeOnline/problem.php?id=4543)

简化题意：

> 有一个树形结构，每条边的长度相同，任意两个节点可以相互到达。
>
> 选 3 个点，两两距离相等，有多少种方案？
>
> $n\leqslant 5000$
>
> 加强版：$n\leqslant 1e5$

# analysis

明显树形 $Dp$，且显然，对于三个点任意两个点的中点一定是重合的，所以可以枚举中间节点。

状态设置如下：

- $f1[j]$ 表示以 $i$ 号节点为根的子树中深度为选出一个深度为 $j$ 的节点的方案数。
- $f2[j]$ 表示以 $i$ 号节点为根的子树中深度为选出两个深度为 $j$ 的节点的方案数。
- $f3[j]$ 表示以 $i$ 号节点为根的子树中深度为选出三个深度为 $j$ 的节点的方案数。

状态转移就用乘法原理相乘，然后将他们累加即可。

-----

加强版：

枚举中点的方式行不通了，需要换一种思路。

想办法 $Dp$ 一下：

设 $f[i][j]$ 表示以 $i$ 为根的子树，到 $i$ 距离为 $j$ 的点的数目。

设 $g[i][j]$ 表示以 $i$ 为根的子树，在其中有多少对点可以与在子树 $i$ 外，且到 $i$ 的距离为 $j$ 的点组成满足题意的三元组的数目。

 $Dp$ 时：每次加入 $i$ 的一个儿 $k$ 子后，先更新答案：
$$
ans=ans+\sum^n_{j=0}f[i][j]∗g[k][j+1]+\sum^n_{j=0}g[i][j]∗f[k]
$$


再更新 $f$ 和 $g$ ：
$$
g[i][j]=g[i][j]+f[i][j]∗f[k]\\
f[i][j]=f[i][j]+f[k]\\
g[i][j]=g[i][j]+f[k]
$$


一定要注意顺序。

然而这样复杂度还是 $O(N^2)$ 的，需要优化转移。

考虑 $i$ 与 $son[i]$ 若 $i$ 只有一个儿子，那么
$$
f[i][j]=f[i][j−1],g[i][j]=g[i][j+1]
$$


所以可以通过指针移动 $O(1)$ 解决。

所以我们想到了一种优化方式：每个节点通过指针移动继承可以延伸最长的的儿子的答案，其他儿子暴力计算。

这个算法的复杂度是：
$$
\sum_{i=1}^n dep[i]−\sum_{i=1}^ndep[i]−1=O(N)
$$



每个儿子往上转移的复杂度是 $dep$ 的，由于一个节点的深度一定是长链所指向的儿子的深度 $+ 1$，所以可以省下 $dep−1$ 次转移。

# code

~~这种写法常数有点大啊，洛谷上第一个点 $T$~~

```cpp
#include<bits/stdc++.h>

typedef long long ll;
const int maxn=5e3+10;

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

int ver[maxn<<1],Next[maxn<<1],head[maxn],len;
inline void add(int x,int y)
{
	ver[++len]=y,Next[len]=head[x],head[x]=len;
}

ll ans;int g[maxn],d[maxn];
inline void dfs1(int x,int fa,int rt)
{
	ans+=g[rt];
	for (int i=head[x]; i; i=Next[i])
	{
		int y=ver[i];
		if (y==fa) continue;
		dfs1(y,x,rt+1);
	}
}

inline void dfs2(int x,int fa,int rt)
{
	g[rt]+=d[rt];
	for (int i=head[x]; i; i=Next[i])
	{
		int y=ver[i];
		if (y==fa) continue;
		dfs2(y,x,rt+1);
	}
}

inline void dfs3(int x,int fa,int rt)
{
	++d[rt];
	for (int i=head[x]; i; i=Next[i])
	{
		int y=ver[i];
		if (y==fa) continue;
		dfs3(y,x,rt+1);
	}
}


int main()
{
	int n;read(n);
	for (int i=1,x,y; i<n; ++i) read(x),read(y),add(x,y),add(y,x);
	for (int x=1; x<=n; ++x)
	{
		memset(d,0,sizeof(d));
		memset(g,0,sizeof(g));
		for (int i=head[x]; i; i=Next[i])
		{
			int y=ver[i];
			dfs1(y,x,1);
			dfs2(y,x,1);
			dfs3(y,x,1);
		}
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
```

~~写的好看些，用乘法原理统计，常数小些~~

```cpp
#include<bits/stdc++.h>

typedef long long ll;
const int maxn=5e3+10;

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

int ver[maxn<<1],Next[maxn<<1],head[maxn],len;
inline void add(int x,int y)
{
	ver[++len]=y,Next[len]=head[x],head[x]=len;
}

int dep[maxn],md,n;
ll g[maxn];
inline void dfs(int x,int fa)
{
	chkMax(md,dep[x]);
	++g[dep[x]];
	for (int i=head[x]; i; i=Next[i])
	{
		int y=ver[i];
		if (y==fa) continue;
		dep[y]=dep[x]+1;
		dfs(y,x);
	}
}

ll f1[maxn];//f1[j]表示以 i 号节点为根的子树中深度为选出一个深度为 j 的节点的方案数
ll f2[maxn];//f2[j]表示以 i 号节点为根的子树中深度为选出两个深度为 j 的节点的方案数
ll f3[maxn];//f3[j]表示以 i 号节点为根的子树中深度为选出三个深度为 j 的节点的方案数
inline ll query(int x)
{
	ll sum=0;
	memset(f1,0,sizeof(f1));
	memset(f2,0,sizeof(f2));
	memset(f3,0,sizeof(f3));
	for (int i=head[x]; i; i=Next[i])
	{
		int y=ver[i];
		dep[y]=md=1;
		dfs(y,x);
		for (int j=md; j; --j) f3[j]+=f2[j]*g[j], f2[j]+=f1[j]*g[j], f1[j]+=g[j], g[j]=0;
	}
	for (int i=1; i<=n; ++i) sum+=f3[i];
	return sum;
}

int main()
{
	read(n); ll ans=0;
	for (int i=1,x,y; i<n; ++i) read(x),read(y),add(x,y),add(y,x);
	for (int i=1; i<=n; ++i) ans+=query(i);
	write(ans,'\n');
	IO::flush();
	return 0;
}
```

~~加强版的长链剖分来啦~~

```cpp
#include<bits/stdc++.h>

typedef long long ll;
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

int ver[maxn<<1],Next[maxn<<1],head[maxn],len;
inline void add(int x,int y)
{
	ver[++len]=y,Next[len]=head[x],head[x]=len;
}

int dep[maxn],son[maxn];
inline void dfs(int x,int fa)
{
	for (int i=head[x]; i; i=Next[i])
	{
		int y=ver[i];
		if (y==fa) continue;
		dfs(y,x);
		if (dep[y]>dep[son[x]]) son[x]=y;
	}
	dep[x]=dep[son[x]]+1;
}

ll space[maxn*10],*now=space+maxn;
ll *f[maxn],*g[maxn], ans;
inline void create(int id)
{
	f[id]=now, now+=dep[id]<<1|1;
	g[id]=now, now+=dep[id]<<1|1;
}

inline void Dp(int x,int fa)
{
	f[x][0]=1;
	if (son[x])
	{
		f[son[x]]=f[x]+1;
		g[son[x]]=g[x]-1;
		Dp(son[x],x);
		ans+=g[son[x]][1];
	}
	for (int i=head[x]; i; i=Next[i])
	{
		int y=ver[i];
		if (y==fa || y==son[x]) continue;
		create(y);
		Dp(y,x);
		for (int j=dep[y]; j>=0; --j)
		{
			if (j) ans+=f[x][j-1]*g[y][j];
			ans+=g[x][j+1]*f[y][j];
			g[x][j+1]+=f[x][j+1]*f[y][j];
		}
		for (int j=0; j<=dep[y]; ++j)
		{
			if (j) g[x][j-1]+=g[y][j];
			f[x][j+1]+=f[y][j];
		}
	}
}
int main()
{
	int n;read(n);
	for (int i=1,x,y; i<n; ++i) read(x),read(y),add(x,y),add(y,x);
	dfs(1,0);
	create(1);
	Dp(1,0);
	write(ans,'\n');
	IO::flush();
	return 0;
}
```