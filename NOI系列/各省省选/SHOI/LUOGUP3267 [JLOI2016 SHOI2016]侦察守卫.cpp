#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 5e5 + 10, inf = 0x3f3f3f3f;

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

int ver[MaxN << 1], Next[MaxN << 1], head[MaxN], len;
inline void add(int x, int y)
{
	ver[++ len] = y, Next[len] = head[x], head[x] = len;
}

int n, m, d;
int w[MaxN], f[MaxN][25], g[MaxN][25];//f[i][j] 表示在子树 i 中，向下还有深度 j，没有被覆盖的最小代价
bool vis[MaxN];//g[i][j] 子树 i 已经被完全覆盖，向上已经覆盖了 j 层所需要的最小代价
//第 x 个节点，开始枚举第 y 个子树，我们需要的方程是：
//f[x][j] = min(min(f[x][j] + g[y][j], g[x][j+1] + f[y][j+1]), f[x][j-1])
//g[x][0] = f[x][0]
//g[x][i] = min(g[x][i-1], g[x][i] + g[y][i-1])
inline void dfs(int x, int fa)
{
	if (vis[x]) f[x][0] = g[x][0] = w[x];
	for (int i = 1; i <= d; ++ i) g[x][i] = w[x];
	g[x][d + 1] = inf;
	for (int i = head[x]; i; i = Next[i])
	{
		int y = ver[i];
		if (y == fa) continue;
		dfs(y, x);
		for (int j = d; j >= 0; -- j) g[x][j] = min(g[x][j] + f[y][j], g[y][j + 1] + f[x][j + 1]);
		for (int j = d; j >= 0; -- j) chkMin(g[x][j], g[x][j + 1]);
		f[x][0] = g[x][0];
		for (int j = 1; j <= d + 1; ++ j) f[x][j] += f[y][j - 1];
		for (int j = 1; j <= d + 1; ++ j) chkMin(f[x][j], f[x][j - 1]);
	}
}

int main()
{
	read(n, d);
	for (int i = 1; i <= n; ++ i) read(w[i]);
	read(m);
	for (int i = 1, x; i <= m; ++ i) read(x), vis[x] = true;
	for (int i = 1, x, y; i < n; ++ i) read(x, y), add(x, y), add(y, x);
	dfs(1, 0);
	write(f[1][0], '\n', true);
	IO::flush();
	return 0;
}
