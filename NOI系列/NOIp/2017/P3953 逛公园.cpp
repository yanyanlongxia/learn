#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

#define mp std::make_pair
typedef long long ll;
typedef std::pair<int, int> pii;
const int MaxN = 1e5 + 10, MaxM = 2e5 + 10;

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

int ver[MaxM], edge[MaxM], Next[MaxM], head[MaxN], len, mod;
inline void add(int x, int y, int z)
{
	ver[++ len] = y, edge[len] = z, Next[len] = head[x], head[x] = len;
}

int dist[MaxN];
bool vis[MaxN];
inline void Dijkstra(int s)
{
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	std::priority_queue<pii, std::vector<pii>, std::greater<pii> >q;
	q.push(mp(0, s)), dist[s] = 0;
	while (!q.empty())
	{
		int x = q.top().second;
		q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		for (int i = head[x]; i; i = Next[i])
		{
			int y = ver[i], z = edge[i];
			if (chkMin(dist[y], dist[x] + z)) q.push(mp(dist[y], y));
		}
	}
}

int f[MaxN][51];
int In[MaxN], Ke[MaxN], flag;//假设在原图中有一条 x->y,z 的边，那么从 x 走到 y 是 dist[x]+z
inline int dfs(int x, int k)//实际上最短路是 dist[y]，那么绕弯路的长度是 dist[x]+z-dist[y]
{//所以 dfs(x,k)表示到达 x 点还剩 k 步可以绕的方案数 f[x][res]=\sum_{y,y->x}f[y][k-(dist[x]+z-dist[y])]
	if (~f[x][k]) return f[x][k];
	f[x][k] = (x == 1);//边界条件是到达 1 返回 1
	for (int i = head[x]; i; i = Next[i])
	{
		int y = ver[i], z = edge[i];
		int t = k - (dist[y] + z - dist[x]);
		if (t < 0) continue;
		if (In[y] && Ke[y] == t) flag = 1;
		else In[y] = 1, Ke[y] = t;
		(f[x][k] += dfs(y, t)) %= mod;
		In[y] = Ke[y] = 0;
	}
	return f[x][k];
}

inline void Clear()
{
	memset(head, 0, sizeof(head));
	len = 0;
}

int x[MaxM], y[MaxM], z[MaxM];
int main()
{
	int T; read(T);
	while (T --)
	{
		Clear();
		int n, m, k; read(n, m, k, mod);
		for (int i = 1; i <= m; ++ i) read(x[i], y[i], z[i]), add(x[i], y[i], z[i]);
		Dijkstra(1);//1. 建出正向图跑出 1~所有点 的最短路
		Clear();
		memset(f, -1, sizeof(f)), flag = 0;
		for (int i = 1; i <= m; ++ i) add(y[i], x[i], z[i]);
		int ans = dfs(n, k);//2. 建出反向图查询方案数
		write(flag ? -1 : ans, '\n', true);
	}
	IO::flush();
	return 0;
}
