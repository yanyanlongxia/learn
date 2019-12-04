#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

#define mp std::make_pair
typedef long long ll;
typedef std::pair<int, int> pii;
const int MaxN = 1e3 + 10, MaxM = 1e6 + 10, mod = 9987, inf = 0x3f3f3f3f;

namespace IO
{
	#define Grt ch = getchar()
	char buf[1 << 15], *fs, *ft;
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

	char Out[1 << 24], *fe = Out;
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

int ver[MaxM], edge[MaxM], Next[MaxM], head[MaxN], len;
inline void add(int x, int y, int z)
{
	ver[++ len] = y, edge[len] = z, Next[len] = head[x], head[x] = len;
}

double dist[MaxN];
int pos[MaxN][2];
bool vis[MaxN];
int n, m;
inline void Dijkstra(int s)
{
	for (int i = 1; i <= n; ++ i) dist[i] = inf, vis[i] = 0;
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
			if (chkMin(dist[y], dist[x] + std::log(z))) pos[y][0] = x, pos[y][1] = z, q.push(mp(dist[y], y));
		}
	}
}

int main()//乘积最短路，转化成 log ，就变成了加法，记录出最短路径，最后相乘即可
{
	read(n, m);
	for (int i = 1, x, y, z; i <= m; ++ i) read(x, y, z), add(x, y, z);
	Dijkstra(1);
	int x = n, ans = 1;
	while (x ^ 1) ans = ans * pos[x][1] % mod, x = pos[x][0];
	write(ans , '\n', true);
	IO::flush();
	return 0;
}
