# title

[BZOJ 5109](https://www.lydsy.com/JudgeOnline/problem.php?id=5109)

[LUOGU 4061](https://www.luogu.org/problem/P4061)

题意：

>一张 $n$ 个点 $m$ 条无向边的图，节点编号为 $1$ 到 $n$ ，每条边具有一个正整数的长度。
>
>假定大魔王都会从 $S$ 点出发到达 $T$ 点（ $S$ 和 $T$ 已知），并且只会走最短路，皮皮和毛毛会在 $A$ 点和 $B$ 点埋伏大魔王。
>
>为了保证一定能埋伏到大魔王，同时又想留大魔王一条生路，皮皮和毛毛约定 $A$ 点和 $B$ 点必须满足：
>
>1. 大魔王所有可能路径中，必定会经过 $A$ 点和 $B$ 点中的任意一点；
>2. 大魔王所有可能路径中，不存在一条路径同时经过 $A$ 点和 $B$ 点；
>
> $K$ 博士想知道，满足上面两个条件的 $A,B$ 点对有多少个，交换 $A,B$ 的顺序算相同的方案。

# analysis

这道题有个梗，网友 $blog$ 说：

>所有图都是随机的，所有数据中从 $S$ 到 $T$ 的最短路最多只有 1 条，
>
>所以呢，本题其实只需要先特判 $S$ 和 $T$ 是否连通，若不连通则输出 $C^2_n$ ，否则随便找一条 $S$ 到 $T$ 的最短路，设路径上的点数为 $len$ ，输出 $len*(n-len)$ 即能得到满分。

然而我也没有去试，所以对真伪不知情，只是当个笑话放在这里（现在看来是真的）。

正解的思路真的是很好的。

因为大魔王（话说他是谁？）一定走最短路，所以处理出以 $S$ 为源点的最短路和以 $T$ 为源点的最短路，这是很显然的（毕竟我看题后，马上就赶紧敲了这个函数，因为怕后面啥都想不到了）。

这里迎来第一个分界点（其实也比较显然了）：

- 从 $S$ 到 $T$ 根本就不联通，这时候答案为 $C^2_n$ （其实就是上面的话重说一遍，逃。
- 否则（开始正解的道路，不要再看上面的骗分了），
	* 随便找出一条最短路（怎么还一样？），那么最终的 $A$ 或者 $B$ 一定有一个点在这条最短路上面（可不一样了吧），我们设在路径上的是 $A$ 。
	* 于是我们枚举所有点 $B$ ，考虑它可以搭配哪些合法的点 $A$ 。
	* 为了满足条件 $2$ ，可以选择的点 $A$ 一定在一段区间中（如果能从 $B$ 走到 $A$ ，那么 $B$ 也一定能走到 $A$ 后面的点；如果 $A$ 能走到 $B$ ，那么 $A$ 前面的点也一定能走到 $B$ ），我们可以先求出最短路径图，然后在正图和反图上分别跑拓扑排序 $+DP$ ，就能得出每个 $B$ 的合法 $A$ 区间。
	* 这时候再去考虑去满足条件 $1$ ，可以用拓扑排序求出经过点 $i$ 的最短路径条数 $f[i]$ ，那么如果 $A$ 和 $B$ 满足条件 $1$ ，等价于 $f[A]+f[B]=f[T]$ ，所以可以采用差分的方式，将每个 $B$ 的 $f[i]$ 都扔到 $A$ 区间，枚举所有的 $A$ ，然后用 $map$ 当前有多少个点的 $f[i]$ 等于一个数，每枚举到一个 $A$ ，就查询一下有多少个点的 $f[i]$ 等于 $f[T]-f[A]$ 即可。

这题被 [CQzhangyu](https://www.cnblogs.com/CQzhangyu/p/7905974.html) 测出来所有的图都是随机的，才有了那个梗（当然，这个梗最初也是人家提出来的），真的很厉害！

# code

```cpp
#include<bits/stdc++.h>

#define mp std::make_pair
typedef long long ll;
typedef std::pair<ll,int> pli;
const int maxn=1e5+10;
typedef int iarr[maxn];
typedef ll larr[maxn];
const ll inf=0x3f3f3f3f3f3f3f3fll;

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

int ver[maxn<<1],Next[maxn<<1],head[maxn],len=1;
ll edge[maxn<<1];
inline void add(int x,int y,ll z)
{
	ver[++len]=y,edge[len]=z,Next[len]=head[x],head[x]=len;
}

int n,m,s,t,pre[maxn];//s~t 最短路上的点的前驱
larr dist,d;//dist s为源点的最短路，d t为源点的最短路
bool vis[maxn];
inline void Dijkstra()//分别跑出以 s、t 为源点的最短路
{
	memset(dist,0x3f,sizeof(dist));
	memset(vis,0,sizeof(vis));
	std::priority_queue<pli,std::vector<pli>,std::greater<pli> >q;
	q.push(mp(0,s)), dist[s]=0;
	while (!q.empty())
	{
		int x=q.top().second;
		q.pop();
		if (vis[x]) continue;
		vis[x]=1;
		for (int i=head[x]; i; i=Next[i])
		{
			int y=ver[i], z=edge[i];
			if (chkMin(dist[y],dist[x]+z)) q.push(mp(dist[y],y));
		}
	}

	memset(d,0x3f,sizeof(d));
	memset(vis,0,sizeof(vis));
	q.push(mp(0,t)), d[t]=0;
	while (!q.empty())
	{
		int x=q.top().second;
		q.pop();
		if (vis[x]) continue;
		vis[x]=1;
		for (int i=head[x]; i; i=Next[i])
		{
			int y=ver[i], z=edge[i];
			if (chkMin(d[y],d[x]+z)) pre[y]=x, q.push(mp(d[y],y));
		}
	}
}

iarr deg,lm,rm;
larr f,f1,f2;
inline void Topsort()//拓扑排序
{
	std::queue<int>q;
	f1[s]=1, f2[t]=1;//
	for (int i=1; i<=n; ++i)
		if (!deg[i]) q.push(i);
	while (!q.empty())
	{
		int x=q.front();
		q.pop();
		for (int i=head[x]; i; i=Next[i]) if (edge[i]==-1)
		{
			int y=ver[i];
			f1[y]+=f1[x], chkMax(lm[y],lm[x]);
			if (!--deg[y]) q.push(y);
		}
	}

	for (int x=1; x<=n; ++x)
		for (int i=head[x]; i; i=Next[i]) if (edge[i]==-2)
		{
			int y=ver[i];
			++deg[y];
		}
	for (int i=1; i<=n; ++i)
		if (!deg[i]) q.push(i);
	while (!q.empty())
	{
		int x=q.front();
		q.pop();
		for (int i=head[x]; i; i=Next[i]) if (edge[i]==-2)
		{
			int y=ver[i];
			f2[y]+=f2[x], chkMin(rm[y],rm[x]);
			if (!--deg[y]) q.push(y);
		}
	}
}

std::vector<int> lp[maxn], rp[maxn];
std::vector<int>::iterator it;
std::map<ll,int>M;
int path[maxn],cnt;ll ans;
int main()
{
	read(n);read(m);read(s);read(t);
	for (int i=1; i<=m; ++i)
	{
		int x,y; ll z;
		read(x), read(y), read(z);
		add(x,y,z), add(y,x,z);
	}
	Dijkstra();
	if (dist[t]>=inf) ans=1ll*n*(n-1)/2ll, write(ans,'\n');
	else
	{
		for (int i=s; i; i=pre[i]) path[++cnt]=i, lm[i]=cnt+1, rm[i]=cnt-1;
		for (int i=1; i<=n; ++i) if (!lm[i]) lm[i]=1, rm[i]=cnt;
		for (int x=1; x<=n; ++x)
			for (int i=head[x]; i; i=Next[i])
			{
				int y=ver[i];
				if (edge[i]>0 && dist[t]==dist[x]+d[y]+edge[i]) edge[i]=-1, edge[i^1]=-2, ++deg[y];
			}
		Topsort();
		for (int i=1; i<=n; ++i)
		{
			f[i]=f1[i]*f2[i];
			if (lm[i]<=rm[i]) lp[lm[i]].push_back(f[i]), rp[rm[i]].push_back(f[i]);
		}
		for (int i=1; i<=cnt; ++i)
		{
			for (it=lp[i].begin(); it!=lp[i].end(); ++it) ++M[*it];
        	ans+=1ll*M[f[t]-f[path[i]]];
        	for (it=rp[i].begin(); it!=rp[i].end(); ++it) --M[*it];
		}
		write(ans,'\n');
	}
	IO::flush();
	return 0;
}
```