[TOC]

# A. 字符串

## title

[zhengruioi](http://zhengruioi.com/problem/957)

## analysis

题目条件有点儿多，总之是要求出一个字典序最小的序列 $\{p_1,p_2,p_3,...,p_m\}$ 满足两个 $p_i$ 是连续的或者两个 $p_i$ 之间的字母都是相同的。

赛场上，说实在的，我没读懂题意，所以就没写。

现在看来应该是字符串匹配方面的东西，先将 $S$ 和 $T$ 进行初步匹配（判断 $T$ 是否是 $S$ 的子串），即每次从 $S$ 中没有匹配的位置中，选择第一个和 $T_i$ 一样的与 $T_i$ 进行匹配，如果将 $S$ 扫了一遍，仍然有 $T_i$ 没有成功匹配，那么就说明 $T$ 不是 $S$ 的子串，无解。

首先，发现刚才的贪心过程中：如果 $p_1$ 是所有可能的位置中最小的， $p_2$ 是在满足 $p_1$ 最小的情况下最小的， $p_3$ 是在满足 $p1, p2$ 都最小的情况下最小的……则这样得到的序列是所有好的下标序列中，字典序最小的那个。

当然这样初步的匹配只是一个 **好的** ，下面将它调整成 **优秀的** 。

考虑从后往前依次考虑 $S$ 中所有满足 **相邻两个字母不同** 的位置，设为 $i$ 和 $i+1$ 。

如果 $i$ 或者 $i+1$ 已经在序列 $p$ 中了，那么已经符合条件了。否则考虑调整：因为 $p$ 已经是字典序最小的序列了，所以我们无法把某个 $p_j$ 变得更小。因此，我们可以移动的位置一定是满足 $p_j<i$ 的一段前缀（既可以把 $p_j$ 调整为原来的 $p_j\sim i$ 中的一个合适的位置，下面要说）。

因为 $S_i \not= S_{i+1}$，所以 $T_j=S_i$ 或 $T_j=S_{i+1}$ 之一一定满足。于是，我们一定可以把 $p_j$ 调整为 $i$ 或 $i+1$ 之一，从而使得 $i$ 满足条件。如果有多个 $j$ 满足这一条件，则我们应当选择最大的那个，因为还有前面的可能需要调整。

## code

```cpp
#include<bits/stdc++.h>

const int maxn=3e5+10;

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

int p[maxn];
char s[maxn],t[maxn];
int main()
{
	int n,m;read(n);read(m);
	scanf("%s",s+1), scanf("%s",t+1);
	for (int i=1, j=1; i<=m; ++i)
	{
		while (j<=n && s[j]!=t[i]) ++j;//选择第一个和 Ti 一样的与 Ti 进行匹配
		if (j==n+1) return puts("-1"),0;//到了末尾都没有，无解
		p[i]=j++;//Ti 的匹配位置为 Sj
	}
	for (int i=m, j=n; j>1; --j)
	{
		if (s[j]==s[j-1]) continue;//从后往前的顺序依次考虑 S 中所有满足相邻两个字母不同的位置
		while (i>0 && p[i]>j) --i;//pj~i 的一段前缀可以移动
		if (!i) return puts("-1"),0;//同上
		p[i]=j;//调整为 i 或 i+1 之一，从而使得 i 满足条件
		if (t[i]==s[j-1]) p[i]=--j;
	}
	for (int i=1; i<=m; ++i) write(p[i],' ');
	IO::flush();
	return 0;
}
```

# B. 散步

## title

[zhengruioi](http://zhengruioi.com/problem/958)

## analysis

大意是让最小化最长连续宽窄路，所以二分答案。

这样问题就转化为了判断是否能找到一条路径，使得连续的 $A$ 或 $B$ 的长度不超过 $T$ 。

可以记忆化搜索，差不多就可以拿到 $50pts$ 。

倍增优化建图不是很懂，以后有机会了学学，没机会就算了。

这题正解是带权并查集，但说实在的，我感觉还是在图上跑 $bfs$ ，用并查集维护一个父子关系，及他们的权值（这个权值，我理解为连续宽或窄路的长度），一旦找到了一个超过 $T$ 的可行解，就中断循环。

因为要求的是最小化，那么应该往小于这个可行解的方向在查找一下是否有更优的可行解，所以如果 $check(mid)=true$ ，就 $r=mid-1$ ，否则 $l=mid+1$ ，直到找到最优解。

要多看看这题，因为总感觉还有不理解的。

## code

```cpp
#include<bits/stdc++.h>

#define mp std::make_pair
typedef std::pair<int,int> pii;
const int maxn=2e5+10;

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

int fa[maxn][2],dist[maxn][2];
inline int get(int x,int t)//type
{
	if (x==fa[x][t]) return x;
	int ans=get(fa[x][t],t);
	dist[x][t]+=dist[fa[x][t]][t];//带权并查集
	return fa[x][t]=ans;
}

int n,to[maxn][2];
bool vis[maxn][2];
inline bool check(int k)
{
	for (int i=1; i<=n; ++i) fa[i][0]=fa[i][1]=i,dist[i][0]=dist[i][1]=vis[i][0]=vis[i][1]=0;
	std::queue<pii>q;
	q.push(mp(1,0)),q.push(mp(1,1));
	vis[1][0]=vis[1][1]=1;
	while (!q.empty())
	{
		int x=q.front().first, t=q.front().second;
		q.pop();
		x=to[x][t];
		int rt=x;
		while (1)
		{
			rt=get(rt,t);
			if (vis[rt][t^1]) break;
			get(x,t);
			if (dist[x][t]>=k) break;
			vis[rt][t^1]=1;
			q.push(mp(rt,t^1));
			if (rt==get(to[rt][t],t)) break;//自环
			fa[rt][t]=to[rt][t];//
			++dist[rt][t];
		}
	}
	return vis[n][0] | vis[n][1];
}

int main()
{
	read(n);
	for (int i=1; i<=n; ++i) read(to[i][0]),read(to[i][1]);
	int l=0,r=n,ans=-1;
	while (l<=r)//最小化最大，二分答案
	{
		int mid=(l+r)>>1;
		if (check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
```

# C. 树

## title

[zhengruioi](http://zhengruioi.com/problem/959)

## analysis

这题是在我基本快放弃的时候，开始看的。

初始的想法，用 $spfa$ 跑出两点间最短距离，然后暴力地判断所有边权是否互质。当然会挂，因为复杂度高不说了，我当时都没信心写下去了。承认这场模拟赛把我打击得够惨了，间接导致第二天早上的模拟赛没有心情打，草草了事。

但是这道题教了我一些东西，倍增求 $gcd$ ，以前只知道倍增求 $LCA$ 。

不过这道题挺复杂的。

对于一个询问，设路径 $(u,v)$ 经过的所有边的 $gcd$ 为 $g$ ，这可以倍增求出。

考虑 $g$ 的所有质因子 $p_1, p_2, · · · , p_k$，因为 $g\leqslant10^6$，所以 $k\leqslant7$ 。（其实就是说搞一个 $vector$ 存一下，不费很大时间）

如果 $g$ 为 $1$ ，那么等价于对于每个 $1\leqslant i\leqslant k$ ，都存在至少一条边的权值不是 $gcd$ 的质因子 $p_i$ 的倍数。（这个我懂了）

求 $l$ 的最小值，等价于于对于每个 $1\leqslant i\leqslant k$ ，计算出最长的不满足条件的 $l′$ ，则最终答案即为所有 $i$ 对应的 $l′$ 的最大值加一（无解的情况除外）。（这个还有点小疑惑。好像懂了，其实他的意思应该是如果经过 $(u,v)$ 的路径的 $gcd$ 不为 $1$ 的话，就把 $gcd$ 质因子分解，找到所有质因子中的最大 $l'$ ，这样不敢加上一条边权为多少，它与之前的边权的 $gcd$ 都为 $1$ 。~~未证明，但是差不多是下面的话的已经理解版，可能刚刚我很傻~~）

考虑对于某个 $p_i$ 而言，我们如何求出这样的 $l′$ 。

我们考虑将所有满足 $p_i|w$ 的边拿出来，并只保留这些边。则 $l′$ 等价于在这样得到的森林中，经过 $(u,v)$ 的最长路径。

使用简单的树形 $DP$ 即可求出某个点向子树方向以及向祖先方向延伸的最长路径，**分类讨论** 即可对于每个 $(u,v)$ 求出对应的 $l′$ 。（这个在代码里的具体体现要好好看看）

接下来考虑无解的情况：事实上，无解等价于刚刚求出的某个 $l′$ 和经过 $(u,v)$ 的最长路径相同。

经过 $(u,v)$ 的最长路径和刚刚是同样的问题，直接对整棵树都做一遍树形 $DP$ 即可。（这篇分析是我在正解上写了写自己的理解，希望日后看时能马上理解）

## code

```cpp
#include<bits/stdc++.h>

const int maxn=2e5+10,maxk=1e6;

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

std::vector<int>E[maxn], W[maxn], V[maxk+10];
inline void add(int x,int y,int z)
{
	E[x].push_back(y), W[x].push_back(z);
}

int dep[maxn],fa[maxn][21],gg[maxn][21];
inline void dfs(int x,int f)
{
	dep[x]=dep[f]+1, fa[x][0]=f;
	for (int i=0; i<(int)E[x].size(); ++i)
	{
		int y=E[x][i];
		if (y==f) continue;
		gg[y][0]=W[x][i];//y 到 其父亲的边的 gcd 只能是边权了
		dfs(y,x);
	}
}

inline int getd(int x,int d)//就是把 x 往上跳的那一步拿出来了
{
	for (int i=20; i>=0; --i)
		if (d>>i&1) x=fa[x][i];
	return x;
}

inline int LCA(int x,int y)
{
	if (dep[x]<dep[y]) std::swap(x,y);
	x=getd(x,dep[x]-dep[y]);
	if (x==y) return x;
	for (int i=20; i>=0; --i)
		if (fa[x][i]^fa[y][i]) x=fa[x][i], y=fa[y][i];
	return fa[x][0];
}

inline int gcd(int a,int b)
{
	return b ? gcd(b,a%b) : a;
}

inline int getgcd(int x,int d)//倍增求gcd
{
	int r=0;
	for (int i=20; i>=0; --i)
		if (d>>i&1) r=gcd(r,gg[x][i]), x=fa[x][i];
	return r;
}

inline int pre(int x,int fa)
{
	int d=0;
	for (int i=0; i<(int)E[x].size(); ++i)
	{
		int y=E[x][i];
		if (y==fa) continue;
		chkMax(d,pre(y,x)+1);
	}
	return d;
}

inline int solve(int x,int fa,int pr)
{
	int d=0;
	for (int i=0; i<(int)E[x].size(); ++i)
	{
		int y=E[x][i];
		if (y^fa && (W[x][i]%pr==0)) chkMax(d,solve(y,x,pr)+1);
	}
	return d;
}

bool vis[maxk+10];
int main()
{
	int n,q;read(n);read(q);
	for (int i=1,x,y,z; i<n; ++i) read(x),read(y),read(z),add(x,y,z),add(y,x,z);

	vis[1]=1;
	for (int i=2; i<=maxk; ++i)
		if (!vis[i])
			for (int j=i; j<=maxk; j+=i)//分解质因子
			{
				if (i^j) vis[j]=1;
				V[j].push_back(i);
			}

	dfs(1,0);
	for (int i=1; i<=20; ++i)
		for (int x=1; x<=n; ++x) fa[x][i]=fa[fa[x][i-1]][i-1];
	for (int i=1; i<=20; ++i)
		for (int x=1; x<=n; ++x) gg[x][i]=gcd(gg[x][i-1],gg[fa[x][i-1]][i-1]);//统一放在后面处理了
	for (int i=1,x,y,fx,fy; i<=q; ++i)
	{
		read(x),read(y);
		int z=LCA(x,y), dist=dep[x]+dep[y]-(dep[z]<<1), g=gcd(getgcd(x,dep[x]-dep[z]),getgcd(y,dep[y]-dep[z]));//(x,y) 的路径上所有边权的 gcd
		
		if (z==y) fy=getd(x,dep[x]-dep[z]-1), fx=fa[x][0];
		else if (z==x) fx=getd(y,dep[y]-dep[z]-1), fy=fa[y][0];
		else fx=fa[x][0], fy=fa[y][0];//分类讨论情况
		
		if (g==1) { write(dist,'\n'); continue;	}//已满足条件
		int res=pre(x,fx)+pre(y,fy), ans=0;//res 经过 (x,y) 的最长路径
		for (int i=0; i<(int)V[g].size(); ++i) chkMax(ans,solve(x,fx,V[g][i])+solve(y,fy,V[g][i]));//最长的不满条件的 l
		write(ans==res ? -1 : ans+dist+1,'\n');
	}
	IO::flush();
	return 0;
}
```

# summary

1. 无论前面打的比赛有多烂，都要认认真真对待下一次的比赛。
2. 遇到一些不会的知识点，由于不是很想学（倍增优化建图），所以更要学会去把握时间打暴力。
3. 多次复盘，争取可以理解关于一道题的所有想法。
