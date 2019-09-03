# title

[BZOJ 5486](https://lydsy.com/JudgeOnline/problem.php?id=5486)

[LUOGU 5122](https://www.luogu.org/problem/P5122)

Description

> 漫长的一天结束了，饥困交加的奶牛们准备返回牛棚。农场由 $N$ 片牧场组成（$2\leqslant N\leqslant 50,000$），方便起见编号为 $1…N$ 。
>
> 所有奶牛都要前往位于牧场 $N$ 的牛棚。其他 $N-1$ 片牧场中每片有一头奶牛。
>
> 奶牛们可以通过 $M$ 条无向的小路在牧场之间移动（$1≤M≤100,000$）。第 $i$ 条小路连接牧场 $a_i$ 和 $b_i $，通过需要时间 $t_i$ 。
>
> 每头奶牛都可以经过一些小路回到牛棚。由于饥饿，奶牛们很乐于在他们回家的路上停留一段时间觅食。
>
> 农场里有 $K$ 个有美味的干草捆，第 $i$ 个干草捆的美味值为 $y_i$ 。每头奶牛都想要在她回牛棚的路上在某一个干草捆处停留，但是她这样做仅当经过这个干草捆使她回牛棚的时间增加不超过这个干草捆的美味值。
>
> 注意一头奶牛仅仅“正式地”在一个干草捆处因进食而停留，即使她的路径上经过其他放有干草捆的牧场；她会简单地无视其他的干草捆。

Input

> 第一行包含三个空格分隔的整数 $N,M,K$ 。
>
> 以下 $M$ 行每行包含三个整数 $a_i,b_i,t_i$，表示牧场 $a_i$ 和 $b_i$ 之间有一条需要 $t_i$ 时间通过的小路（ $a_i$ 不等于 $b_i,t_i$ 为不超过 $10^4$ 的正整数）。
>
> 以下 $K$ 行，每行以两个整数描述了一个干草捆：该干草捆所在牧场的编号，以及它的美味值（一个不超过 $10^9$ 的正整数）。同一片牧场中可能会有多个干草捆。

Output

> 输出包含 $N-1$ 行。如果牧场 $i$ 里的奶牛可以在回牛棚的路上前往某一个干草捆并且在此进食，则第 $i$ 行为一个整数 $1$ ，否则为一个整数 $0$ 。

Sample Input

> 
> 4 5 1
> 1 4 10
> 2 1 20
> 4 2 3
> 2 3 5
> 4 3 2
> 2 7
>

Sample Output

> 1
> 1
> 1

# analysis

很自然地想到以 $N$ 为源点跑最短路。当然，这仅仅是第一步。

怎么处理这个干草堆的美味值 $y$ ？不难想到建立一个超级源，向这些有干草堆的牧场 $i$ 连一条长度为 $d[i]-y$ 的有向边（其中 $d[i]$ 为 $N$ 到 $i$ 的最短路）。

然后以超级源跑最短路，如果超级源到 $i$ 的最短时间（最短路） $<=$ $N$ 到 $i$ 的最短时间（最短路），那就合法了。

# code

```cpp
#include<bits/stdc++.h>

#define mp std::make_pair
typedef std::pair<int,int> pii;
const int maxn=5e4+10,maxm=1e5+10;

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

int ver[maxm<<1],edge[maxm<<1],Next[maxm<<1],head[maxn],len;
inline void add(int x,int y,int z)
{
	ver[++len]=y,edge[len]=z,Next[len]=head[x],head[x]=len;
}

int dist[maxn];
bool vis[maxn];
inline void Dijkstra(int s)
{
	memset(dist,0x3f,sizeof(dist));
	memset(vis,0,sizeof(vis));
	std::priority_queue<pii,std::vector<pii>,std::greater<pii> >q;
	q.push(mp(0,s)), dist[s]=0;
	while (!q.empty())
	{
		int x=q.top().second;
		q.pop();
		if (vis[x]) continue;
		vis[x]=1;
		for (int i=head[x]; i; i=Next[i])
		{
			int y=ver[i],z=edge[i];
			if (dist[y]>dist[x]+z)
			{
				dist[y]=dist[x]+z;
				q.push(mp(dist[y],y));
			}
		}
	}
}

int d[maxn];
int main()
{
	int n,m,k;
	read(n);read(m);read(k);
	for (int i=1,x,y,z; i<=m; ++i) read(x),read(y),read(z),add(x,y,z),add(y,x,z);
	Dijkstra(n);
	for (int i=1; i<=n; ++i) d[i]=dist[i];
	for (int i=1,x,y; i<=k; ++i) read(x),read(y),add(n+1,x,d[x]-y);
	Dijkstra(n+1);
	for (int i=1; i<n; ++i) write(d[i]>=dist[i] ? 1 : 0,'\n');
	IO::flush();
	return 0;
}
```