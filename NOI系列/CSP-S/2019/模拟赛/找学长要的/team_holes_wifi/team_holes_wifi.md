[TOC]

# A. 分队问题 (team)

## title

[team](https://www.luogu.org/problem/U88318)

题意：

>![](https://img2018.cnblogs.com/blog/1587478/201909/1587478-20190923164414226-162512384.png)

## analysis

$CEOI$ 改编题目。

不得不说，欧洲出的题的思路是很好的。

本题检测了贪心，动态规划，前缀和等知识点，不得不说，这次出题人的结题报告写的不错，走心（逃。

不说贪心地写法了，直接引入 $Dp$ ：

将所有队员按要求从低到高排序，用 $f[i]$ 表示前 $i$ 名队员最多分成的队伍数量，枚举最后一队的人数：
$$
f[i]=\max_{j\in[0,i-a[i]]}f[j]+1
$$


设 $g[i]$ 表示前 $i$ 名队员分成 $f[i]$ 队，人数最多的队伍的最小人数，由于枚举了最后一队的人数，因此有：
$$
g[i]=\max\{g[j-1],i-j+1\}
$$


在考虑转移 $j$ 时，不仅在 $f[j]+1>f[i]$ 时需要转移给 $i$ ，在 $f[j]+1==f[i]$ 且能令 $g[i]$ 变小时也需更新。

答案即为 $f[n]$ 和 $g[n]$ ，时间复杂度： $O(n^2)$ 。

所以考虑一下优化，可以知道， $f$ 的转移可以通过前缀和来加速为 $O(1)$ ，那么 $g$ 的转移能否也通过前缀和来加速为 $O(1)$ ？尝试一下。

那就需要发掘出一些性质了：

正难则反，我们从高到低排序每位队员，必然有 $f[i+1] == f[i]$ 或 $f[i+1]== f[i]+1$ 。

在考虑队员 $i+1$ 时，由于 $a[i+1]$ 比 $a[1]\sim a[i]$ 都小，因此队员 $i+1$ 可以加入 $1\sim i$ 已安排好的任意一个队伍。这就意味着，只要 $f[i] * g[i] >= i+1$ ，队员 $i+1$ 肯定可以加入 $f[i]$ 队中人数最少的一队，使得队员人数仍不超过 $g[i]$ 。反之，若 $f[i] * g[i] == i$ ，则在 $f[i+1]==f[i]$ 的情况下，必然有 $g[i+1] = g[i]+1$ 。 

因此，我们就得到了一个基本转移： 
$$
f[i+1]=f[i]\\
g[i+1]=\Big\{\begin{array}{}
g[i],f[i]*g[i]>i\\
g[i]+1,f[i]*g[i]==i
\end{array}
$$


现在再考虑 $f[i+1]== f[i]+1$ 的情况。

事实上，在有上面这个基本转移的基础上，我们只需要考虑最小的队伍安排即可（基本转移在不改变队伍数的情况下，会自由增加每队的人数到上限）。 

由于我们从高到低排序了每位队员，因此，最左边的队员即代表了最高的人数限制。因此，对于队员 $i$ ，只需考虑从 $i$ 转移到 $i+a[i]-1$ 即可。

也就是说， $n$ 个队员总共最多只有 $n$ 个这样的转移可能，而基本转移也是 $O(n)$ 的，因此整个动态规划的总复杂度为 $O(n)$ 。

**复杂度下降的整体思路在于把枚举一队的可能人数，分为一队的最优人数和自由增加一队人数至上限这两部分。**

（照着 $solution$ 抄真是好累，不过再顺一遍一遍思路还是好的。）

## code

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

const int maxn=1e6+10;
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

std::vector<int> e[maxn];
iarr a, f, g; int tot;
int main()
{
//	file("team");

	int n; read(n);
	for (int i=1, x; i<=n; ++i) read(x), e[x].push_back(i);
	for (int x=n; x>=1; --x)
	{
		for (int i=0; i<(int)e[x].size(); ++i) a[++tot]=x;
		e[x].clear();
	}
	f[a[1]]=1, g[a[1]]=a[1];
	for (int i=a[1]+1; i<=n; ++i)
    {
    	if (a[i]+i-1<=n) e[a[i]+i-1].push_back(i-1);

		f[i]=f[i-1], g[i]=g[i-1];
        if (f[i]*g[i]<i) ++g[i];
        for (int j=0; j<(int)e[i].size(); ++j)
        {
			int k=e[i][j];
			if (f[k]+1>f[i] || (f[k]+1==f[i] && g[k]<g[i])) f[i]=f[k]+1, g[i]=g[k];
		}
    }
    write(f[n],' '), write(g[n],'\n');
    IO::flush();
	return 0;
}
```

# B. 虫洞跃迁 (holes)

## title

[holes](https://www.luogu.org/problem/U88319)

题意：

>![](https://img2018.cnblogs.com/blog/1587478/201909/1587478-20190923164340215-1585852112.png)
>
>![](https://img2018.cnblogs.com/blog/1587478/201909/1587478-20190923164346738-64491171.png)
>
>![](https://img2018.cnblogs.com/blog/1587478/201909/1587478-20190923164358442-1661146527.png)

## analysis

这道题就稍微简单了些，只是最短路题目加强了建图而已。

所以这道题要根据三种情况来进行建图：

- 首先，由于每个虫洞有黑白洞之分，所以用 $2n$ 个点来表示 $n$ 个虫洞的黑洞状态与白洞状态。

- 在一个虫洞停留 $1$ 个单位时间，如果当前为白洞，则不消耗燃料，否则消耗 $s[i]$ 的燃料。
  	
* 所以在每个虫洞的黑洞与白洞之间连 $2$ 条单向边，其中白洞连向黑洞的边的长度（燃料，下同）为 $0$ ，从黑洞连向白洞的边长度为 $s[i]$ 。
  	
- 从白洞跃迁到黑洞，所需的跃迁燃料值减少 $delta$ ，若该条路径消耗的燃料值变为负数的话，取为 $0$ 。 从黑洞跃迁到白洞，所需的跃迁燃料值增加 $delta$ 。

   * 这个连边就有个坑了，举个例子就懂了，比如当前在白洞，要跃迁到黑洞，但是，注意，等跃迁到黑洞的时候，已经花费了 $1$ 个单位时间，这个黑洞也就变成了白洞了，所以上面两句话翻译成建图就是：

   * $$
     x.0\stackrel{\max\{k-delta,0\}}{\longrightarrow}y.0\\
     x.1\stackrel{k+delta}{\longrightarrow}y.1
     $$



- 路径两端均为黑洞或白洞，所需的跃迁燃料值不变化:

  * $$
    x.0\stackrel{k}{\longrightarrow}y.1\\
    x.1\stackrel{k}{\longrightarrow}y.0
    $$



建图完成后，由于这张图没有负环，所以使用任意最短路算法即可，最终答案为虫洞 $n$ 的黑白洞状态两者的最短路的最小值。

## code

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

const int maxn=1e4+10, maxm=3e4+10;
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

template<typename T>inline bool chkMin(T &a,const T &b) { return a>b ? (a=b, true) : false; }
template<typename T>inline bool chkMax(T &a,const T &b) { return a<b ? (a=b, true) : false; }
template<typename T>inline T min(T a,T b) { return a<b ? a : b; }
template<typename T>inline T max(T a,T b) { return a>b ? a : b; }

int spot[maxm*10], ver[maxm*10], edge[maxm*10], Next[maxm*10], head[maxn][2], len=1;
inline void add(int Xx,int Xy,int Yx,int Yy,int z)
{
	spot[++len]=Yx, ver[len]=Yy, edge[len]=z, Next[len]=head[Xx][Xy], head[Xx][Xy]=len;
}

struct Orz
{
	int x, y, v;
	Orz(int X,int Y,int V) { x=X, y=Y, v=V; }
	inline bool operator > (const Orz a) const { return v>a.v; }
};
int dist[maxn][2], a[maxn], w[maxn];
bool vis[maxn][2];
inline void Dijkstra(int S)
{
	memset(dist,0x3f,sizeof(dist));
	memset(vis,0,sizeof(vis));
	std::priority_queue<Orz, std::vector<Orz>, std::greater<Orz> >q;
	q.push(Orz(S,a[S],0)), dist[S][a[S]]=0;
	while (!q.empty())
	{
		Orz u=q.top();
		q.pop();
		if (vis[u.x][u.y]) continue;
		vis[u.x][u.y]=1;
		for (int i=head[u.x][u.y]; i; i=Next[i])
		{
			int x=spot[i], y=ver[i], z=edge[i];
			if (chkMin(dist[x][y], dist[u.x][u.y]+z)) q.push(Orz(x,y,dist[x][y]));
		}
	}
}

int main()
{
//	file("holes");

	int n, m; read(n), read(m);
	for (int i=1; i<=n; ++i) read(a[i]);
	for (int i=1; i<=n; ++i) read(w[i]);
	for (int i=1, k; i<=n; ++i)
	{
		read(k);
		add(i, 0, i, 1, 0), add(i, 1, i, 0, k);//0 white 1 black
	}
	for (int i=1, x, y, z; i<=m; ++i)
	{
		read(x), read(y), read(z);
		if (a[x]==a[y]) add(x, 0, y, 1, z), add(x, 1, y, 0, z);
		else
		{
			int delta=abs(w[x]-w[y]);
			add(x, 0, y, 0, max(z-delta, 0)), add(x, 1, y, 1, z+delta);
		}
	}
	Dijkstra(1);
	write(min(dist[n][1], dist[n][0]),'\n');
	IO::flush();
	return 0;
}
```

# C. 信号强度 (wifi)

## title

[wifi](https://www.luogu.org/problem/U88320)

题意：

>![](https://img2018.cnblogs.com/blog/1587478/201909/1587478-20190923164240690-1290820718.png)
>
>![](https://img2018.cnblogs.com/blog/1587478/201909/1587478-20190923164300979-1511604102.png)
>
>![](https://img2018.cnblogs.com/blog/1587478/201909/1587478-20190923164309707-1389479928.png)

## analysis

这题太神仙，数据做的真是挺坑的，竟然还需要读入换行符。

好，从简入繁，从最特殊的情况开始入手这道题。

-----

首先，考虑没有光纤，且只有一组 $a$ 存在。将所有边按权重从小到大的顺序排序，依次插入图中，直到所有点 $a$ 都属于同一个连通块为止。输出这条边的边（最大边权）权即为答案。 

使用并查集来维护连通情况，插入一条边使边的两个端点所属的并查集并集。维护每个并查集中点a 的个数，一旦有一个并查集的点 $a$ 的个数等于图中点 $a$ 的总数，就意味着所有点 $a$ 已属于同一个连通块，此时输出答案即可。

-----

然后，考虑不止一组的情况。同样的，让同一组的点都属于各自的某一连通块即可。每个并查集维护各组点的个数，一旦有一个并查集的某一组的点的个数等于该组点的总数，则意味着该组所有点已属于同一个连通块。等每一组都完成后，输出答案即可。 

-----

然后就该考虑加入光纤了，加入光线的实质是什么？

就是把之前的问题（<font color=red>让同一组的点属于同一个并查集</font>）放宽为<font color=blue>允许有（某一组或某几组同在的） $2$ 个并查集之间可以通过一条还未插入的边直接连接，其他组仍属于各自的并查集，`#` 所属的并查集不做考察</font>。 

当只剩 $2$ 个并查集 $A,B$ 需要合并的时候 （意味着除了这 $2$ 个并查集所拥有一组/多组点之外，其他同一组的点已经属于各自的并查集了），立刻检查是否有直接相连 $2$ 个并查集的一条边，若存在则直接输出答案，否则继续插入边。

每次插入边之后，做同样的检查。

使用 $DFS$ 或 $BFS$ 来做检查：每次某个并查集 $A$ （或 $B$ ）与另一个并查集 $C$ 合并后， $DFS$ 或 $BFS$ 遍历 $C$ 内的点，检查是否存在直接相连 $B$ （或 $A$ ）的边，之后再将并查集 $C$ 并入 $A$ （或 $B$ ）。对于已经检查过的点进行标记，以避免重复检查。

## code

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

#define mp std::make_pair
typedef std::pair<int,int> pii;
const int maxn=1e5+10, maxm=4e5+10;
typedef int iarr[maxm];

namespace IO
{
	char buf[1<<15], *fs, *ft;
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

	char Out[1<<24], *fe=Out;
	inline void flush() { fwrite(Out,1,fe-Out,stdout); fe=Out; }
	template<typename T>inline void write(T x, char str)
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

iarr u, v, d, id;
inline bool cmp(int x, int y)
{
	return d[x]<d[y];
}

int fa[maxn];
inline int get(int x)
{
	return fa[x]==x ? x : fa[x]=get(fa[x]);
}

int cnt[maxn][27], full[27], uni;
inline void link(int x, int y)
{
	int fx=get(x), fy=get(y);
	if (fx==fy) return ;
	if (!cnt[fx][0]) std::swap(fx,fy);
	bool comb=false;
	for (int i=0; i<=26; ++i)
		if (cnt[fy][i]>0)
		{
			cnt[fx][i]+=cnt[fy][i];
			comb=true;
		}
	if (comb) --uni;

	bool dec=false;
	for (int i=1; i<=26; ++i)
		if (cnt[fx][i]==full[i] && full[i])
		{
			cnt[fx][0]-=full[i];
			cnt[fx][i]=0;
			dec=true;
		}
	if (!cnt[fx][0] && dec) --uni;
	fa[fy]=fx;
}

int p, c[maxn];
std::vector<pii> E[maxn];
inline bool bfs(int x, int color)
{
	std::queue<int>q; q.push(x);
	c[x]=color;
	while (!q.empty())
	{
		int x=q.front();
		q.pop();
		for (int i=0; i<(int)E[x].size(); ++i)
		{
			int y=E[x][i].first, z=E[x][i].second;
			if (c[y]==(color^1)) return true;
			if (z<=p && !c[y]) c[y]=color, q.push(y);
		}
	}
	return false;
}

int n, m;
inline void solve()
{
	if (uni<=1) { write(0, '\n'); return ; }

	p=-1;
	while (uni>2) ++p, link(u[id[p]], v[id[p]]);

	int color=2;
	for (int i=0; i< n; ++i)
	{
		int ff=get(i);
		if (!c[ff] && cnt[ff][0])
		{
			if (bfs(ff, color)) { write(d[id[p]], '\n'); return ; }
			++color;
		}
	}

	while (1)
	{
		++p;
		int fx=get(u[id[p]]), fy=get(v[id[p]]);
		if (fx==fy) continue;
		if (!c[fx]) std::swap(fx,fy);
		else if (bfs(fy, c[fx])) { write(d[id[p]], '\n'); return ; }
		link(fx,fy);
	}
}

int main()
{
//	file("wifi");

	read(n), read(m); scanf("\n");//造数据的问题了
	for (int i=0; i< n; ++i)
	{
		char ch; scanf("%c\n",&ch);//同上
		if (ch!='#')
		{
			cnt[i][0]=1;
			cnt[i][ch-'a'+1]=1;
			++uni;
			++full[ch-'a'+1];
		}
		fa[i]=i;
	}
	for (int col=1; col<=26; ++col) if (full[col]==1)
		for (int i=0; i< n; ++i) if (cnt[i][col])
		{
			cnt[i][0]=cnt[i][col]=0;
			--uni;
			break;
		}

	for (int i=0; i< m; ++i) read(u[i]), read(v[i]), read(d[i]), id[i]=i;
	std::sort(id, id+m, cmp);
	for (int i=0; i< m; ++i)
	{
		E[ u[id[i]] ].push_back( mp(v[id[i]], i) );
		E[ v[id[i]] ].push_back( mp(u[id[i]], i) );
	}

	solve();
	IO::flush();
	return 0;
}
```

# summary

这套题的确是挺有难度的，不过呢，

 $T2$ 对于我来说，是必须得 $A$ 掉的；

 $T1$ 呢，就需要在能想到贪心的时候，看看 $Dp$ 能不能使用，然后就是要注意 $Dp$ 的状态描述，这样才能发现一些性质，从而优化转移，当然也要类比同一题中的转移，说不定优化方式一样呢；

 $T3$ 和 $zhengruioi$ 出的 $T2$ 挺像的，不过太过神仙，比赛的时候，我估计我不一定能拿到分，所以随便了。