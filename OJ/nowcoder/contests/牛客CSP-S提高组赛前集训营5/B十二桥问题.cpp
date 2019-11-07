#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

#define mp std::make_pair
typedef long long ll;
typedef std::pair<ll, int> pli;
const int MaxN = 5e4 + 10, MaxM = 4e5 + 10, mod = 998244353;
const ll INF = 0x3f3f3f3f3f3f3f3fll;

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

int ver[MaxM << 1], edge[MaxM << 1], Next[MaxM << 1], head[MaxN], len;
inline void add(int x, int y, int z)
{
	ver[++ len] = y, edge[len] = z, Next[len] = head[x], head[x] = len;
}

ll dist[26][MaxN];
bool vis[MaxN];
inline void Dijkstra(ll dist[MaxN], int s)
{
	memset(vis, 0, sizeof(vis));
	std::priority_queue<pli, std::vector<pli>, std::greater<pli> >q;
	q.push(mp(0, s)), dist[s] = 0;
	while (!q.empty())
	{
		int x = q.top().second;
		q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		for (int i = head[x]; i; i = Next[i])
		{
			int y = ver[i]; ll z = edge[i];
			if (chkMin(dist[y], dist[x] + z)) q.push(mp(dist[y], y));
		}
	}
}

ll f[26][1 << 12];
int Log[MaxM], X[25], Y[25], Z[25], did[MaxN], cnt;
int main()
{
	int n, m, k; read(n, m, k);
	for (int i = 0; i < k; ++ i) Log[1 << i] = i;
	for (int i = 0, x, y, z; i < m; ++ i)
	{
		read(x, y, z), add(x, y, z), add(y, x, z);
		if (i < k) X[i] = x, Y[i] = y, Z[i] = z;
	}
	memset(dist, 0x3f, sizeof(dist));
	Dijkstra(dist[did[1] = ++ cnt], 1);
	memset(f, 0x3f, sizeof(f));
	for (int i = 0; i < k; ++ i)
	{
		if (!did[X[i]]) Dijkstra(dist[did[X[i]] = ++ cnt], X[i]);
		if (!did[Y[i]]) Dijkstra(dist[did[Y[i]] = ++ cnt], Y[i]);
		f[i << 1][1 << i] = dist[did[Y[i]]][1] + Z[i];
		f[i << 1 | 1][1 << i] = dist[did[X[i]]][1] + Z[i];
	}
	for (int s = 1; s < (1 << k); ++ s)
		for (int t = s; t; t -= t & -t)
		{
			int x = Log[t & -t], Rs = s - (t & -t);
			for (int p = Rs; p; p -= p & -p)
			{
				int y = Log[p & -p];
				chkMin(f[x << 1 | 1][s], f[y << 1][Rs] + dist[did[X[x]]][X[y]] + Z[x]);
				chkMin(f[x << 1][s], f[y << 1][Rs] + dist[did[Y[x]]][X[y]] + Z[x]);
				chkMin(f[x << 1 | 1][s], f[y << 1 | 1][Rs] + dist[did[X[x]]][Y[y]] + Z[x]);
				chkMin(f[x << 1][s], f[y << 1 | 1][Rs] + dist[did[Y[x]]][Y[y]] + Z[x]);
			}
		}
    ll ans = INF;
    for (int i = 0; i < k; ++ i)
    {
    	chkMin(ans, f[i << 1][(1 << k) - 1] + dist[did[X[i]]][1]);
    	chkMin(ans, f[i << 1 | 1][(1 << k) - 1] + dist[did[Y[i]]][1]);
	}
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
