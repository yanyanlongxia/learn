#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e6 + 10, MaxM = 2e6 + 10;

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

int ver[MaxM << 1], Next[MaxM << 1], head[MaxN], len;
inline void add(int x, int y)
{
	ver[++ len] = y, Next[len] = head[x], head[x] = len;
}

namespace lca
{
	int dep[MaxN], f[MaxN][21];
	inline void dfs(int x)
	{
		for (int i = 1; i <= 20; ++ i) f[x][i] = f[f[x][i - 1]][i - 1];
		for (int i = head[x]; i; i = Next[i])
		{
			int y = ver[i];
			if (y == f[x][0]) continue;
			f[y][0] = x;
			dep[y] = dep[x] + 1;
			dfs(y);
		}
	}

	inline int LCA(int x, int y)
	{
		if (dep[x] > dep[y]) std::swap(x, y);
		for (int i = 20; i >= 0; -- i)
			if (dep[y] - (1 << i) >= dep[x]) y = f[y][i];
		if (x == y) return x;
		for (int i = 20; i >= 0; -- i)
			if (f[x][i] ^ f[y][i]) x = f[x][i], y = f[y][i];
		return f[x][0];
	}
}

using lca::dfs;
using lca::LCA;

int fa[MaxN];
inline int get(int x)
{
	return fa[x] == x ? x : fa[x] = get(fa[x]);
}

int val[MaxN];
inline void dfsval(int x, int fa)
{
	for (int i = head[x]; i; i = Next[i])
	{
		int y = ver[i];
		if (y == fa) continue;
		dfsval(y, x);
		val[x] += val[y];
	}
}

int E[MaxN << 1][2], cnt[MaxN << 1], t;
int main()//没想到这道题实际上连 tarjan 都不需要，又是树上差分，我真服了
{
	int n, m, k; read(n, m, k);
	for (int i = 1; i <= n; ++ i) fa[i] = i;
	for (int i = 1, x, y, fx, fy; i <= m; ++ i)
	{
		read(x, y);
		fx = get(x), fy = get(y);
		if (fx == fy) E[++ t][0] = x, E[t][1] = y;
		else add(x, y), add(y, x), fa[fx] = fy;
	}
	for (int i = 1; i <= n; ++ i)
		if (get(i) == i) dfs(i);
	for (int i = 1; i <= t; ++ i)
	{
		int x = E[i][0], y = E[i][1], l = LCA(x, y);
		++ val[x], ++ val[y], val[l] -= 2;
		cnt[i] = lca::dep[x] + lca::dep[y] - (lca::dep[l] << 1);
	}
	int ans = 0, now = 0;
	for (int i = 1; i <= n; ++ i)
		if (get(i) == i) dfsval(i, 0), ++ ans;
	for (int i = 1; i <= n; ++ i)
		if (get(i) != i) now += (!val[i]);
	std::sort(cnt + 1, cnt + t + 1, std::greater<int>());
	int p = 1;
	while (k)
	{
		int tmp = min(k, now);
		ans += tmp, now -= tmp, k -= tmp;
		if (k && p <= t) -- k, now += cnt[p ++];
	}
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
