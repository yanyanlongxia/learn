#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 16e3 + 10;

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

int f[MaxN], a[MaxN], ans;//表示以 x 为根且包含 x 的最大权联通块
inline void dfs(int x, int fa)
{
	f[x] = a[x];
	for (int i = head[x]; i; i = Next[i])
	{
		int y = ver[i];
		if (y == fa) continue;
		dfs(y, x);
		f[x] += max(0, f[y]);
	}
	chkMax(ans, f[x]);
}

int main()//子树型，给一棵 n 个点的树，以 1 号点为根，求以每个点为根的子树大小
{
	int n; read(n);
	for (int i = 1; i <= n; ++ i) read(a[i]);//简单写写树形 Dp，哎，这几天很自闭，发现自己很难独立写出来一道题，哎
	for (int i = 1, x, y; i < n; ++ i) read(x, y), add(x, y), add(y, x);
	dfs(1, 0), write(ans, '\n', true);
	IO::flush();
	return 0;
}
