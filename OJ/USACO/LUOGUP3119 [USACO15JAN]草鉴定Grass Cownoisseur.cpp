#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e5 + 10;

namespace IO
{
	#define Grt ch = getchar()
	char buf[1<<15], *fs, *ft;
	inline char getc() { return ft == fs && (ft = (fs = buf) + fread(buf, 1, 1 << 15, stdin), ft == fs) ? 0 : *fs ++; }
	template <typename T> inline void read(T &x)
	{
		x = 0;
		T f = 1, Grt;
		while (!isdigit(ch) && ch ^ '-') Grt;
		if (ch == '-') f = -1, Grt;
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), Grt;
		x *= f;
	}

	template <typename T, typename... Args>
	inline void read(T &x, Args &...args) { read(x); read(args...); }

	char Out[1<<24], *fe = Out;
	inline void flush() { fwrite(Out, 1, fe - Out, stdout); fe = Out; }
	template <typename T> inline void write(T x, char str, bool fl)
	{
		if (!x) *fe++ = 48;
		if (x < 0) *fe++ = '-', x = -x;
		T num = 0, ch[20];
		while (x) ch[++ num] = x % 10 + 48, x /= 10;
		while (num) *fe++ = ch[num --];
		if (fl) *fe++ = str;
	}
}

using IO::read;
using IO::write;

template <typename T> inline bool chkMin(T &a, const T &b) { return a > b ? (a = b, true) : false; }
template <typename T> inline bool chkMax(T &a, const T &b) { return a < b ? (a = b, true) : false; }
template <typename T> inline T min(T a, T b) { return a < b ? a : b; }
template <typename T> inline T max(T a, T b) { return a > b ? a : b; }

struct Graph
{
	int ver[MaxN << 1], Next[MaxN << 1], head[MaxN], len;
	inline void Clear()
	{
		memset(head, 0, sizeof(head));
		len = 0;
	}

	inline void add(int x, int y)
	{
		ver[++ len] = y, Next[len] = head[x], head[x] = len;
	}
} G, A;//方便写罢了，其实可能别人还觉得这样不方便

int dfn[MaxN], low[MaxN], id;
int Stack[MaxN], top;
int belong[MaxN], siz[MaxN], tot;
bool instack[MaxN];
inline void tarjan(int x)//普普通通的 tarjan 求 scc（强连通分量）
{
	dfn[x] = low[x] = ++ id;
	Stack[++ top] = x;
	instack[x] = 1;
	for (int i = G.head[x]; i; i = G.Next[i])
	{
		int y = G.ver[i];
		if (!dfn[y])
		{
			tarjan(y);
			chkMin(low[x], low[y]);
		}
		else if (instack[y]) chkMin(low[x], dfn[y]);
	}
	if (low[x] == dfn[x])
	{
		int k;
		++ tot;
		do
		{
			k = Stack[top --];
			belong[k] = tot;
			++ siz[tot];
			instack[k] = 0;
		} while (k != x);
	}
}

int distS[MaxN], distT[MaxN];
bool vis[MaxN];
inline void spfa(int *dist)
{
	memset(dist, 0xcf, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	std::queue<int> q; q.push(belong[1]);
	dist[belong[1]] = siz[belong[1]], vis[belong[1]] = 1;//是以每个连通块为点跑最长路，且 dist 定义为所能到达的最多点数
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		vis[x] = 0;
		for (int i = A.head[x]; i; i = A.Next[i])
		{
			int y = A.ver[i], z = siz[y];
			if (chkMax(dist[y], dist[x] + z))
				if (!vis[y]) q.push(y), vis[y] = 1;
		}
	}
}

int main()//求 scc 后缩点建图，之后正反图跑最长点数，调整 ans 即可，不错的题目！
{
	int n, m; read(n, m);
	for (int i = 1, x, y; i <= m; ++ i) read(x, y), G.add(x, y);//有向图
	for (int i = 1; i <= n; ++ i)//缩点前操作，因为同属一个连通块的草地是过一个，就全过得
		if (!dfn[i]) tarjan(i);
	for (int x = 1; x <= n; ++ x)
		for (int i = G.head[x]; i; i  = G.Next[i])
		{
			int y = G.ver[i];
			if (belong[x] ^ belong[y]) A.add(belong[x], belong[y]);//缩点后建正向图
		}
	spfa(distS);//求出从 1 出发到每个点的最长路
	int ans = distS[belong[1]];
	A.Clear();//只是一个节省空间的写法罢了
	for (int x = 1; x <= n; ++ x)
		for (int i = G.head[x]; i; i  = G.Next[i])
		{
			int y = G.ver[i];
			if (belong[x] ^ belong[y]) A.add(belong[y], belong[x]);//建反向图
		}
	spfa(distT);//跑出每个点到 1 的最长路

	for (int x = 1; x <= n; ++ x)
		for (int i = G.head[x]; i; i  = G.Next[i])//进行调整转移
		{
			int y = G.ver[i];
			if (belong[x] == belong[y]) continue;
			if (distS[belong[x]] > 0 && distT[belong[y]] > 0) chkMax(ans, distS[belong[x]] + distT[belong[y]] - siz[belong[1]]);//这其实就比较显然了
			if (distS[belong[y]] > 0 && distT[belong[x]] > 0) chkMax(ans, distS[belong[y]] + distT[belong[x]] - siz[belong[1]]);//两个 dist 中其实都有 siz[belong[1]]，所以减掉一个
		}
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
