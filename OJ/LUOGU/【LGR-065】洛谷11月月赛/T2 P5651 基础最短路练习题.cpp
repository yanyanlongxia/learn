#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 2e5 + 10;

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

int ver[MaxN << 1], edge[MaxN << 1], Next[MaxN << 1], head[MaxN], len;
inline void add(int x, int y, int z)
{
	ver[++ len] = y, edge[len] = z, Next[len] = head[x], head[x] = len;
}

int dist[MaxN];
bool vis[MaxN];
inline void dfs(int x)
{
	for (int i = head[x]; i; i = Next[i])
	{
		int y = ver[i], z = edge[i];
		if (vis[y]) continue;
		vis[y] = 1;
		if (!dist[y]) dist[y] = dist[x] ^ z;
		dfs(y);
	}
}

int main()//保证 G 中不存在简单环使得边权异或和不为 0，所以由起点指向一个x有两条路径，那么这两条路径的异或值是等价的
{//因为这两条路径形成了环，环的异或和为 0，即两条路径的异或值相等，所以这张无向图就和树一样了，服了
	int n, m, q;
	read(n, m, q);
	for (int i = 1, x, y, z; i <= m; ++ i) read(x, y, z), add(x, y, z), add(y, x, z);
	vis[1] = 1, dfs(1);
	for (int i = 1, x, y; i <= q; ++ i) read(x, y), write(dist[x] ^ dist[y], '\n', true);
	IO::flush();
	return 0;
}
