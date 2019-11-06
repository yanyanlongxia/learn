#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 3e3 + 10;

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

int n, p[2]; ll ans;
int ld[MaxN], f[MaxN][MaxN], g[MaxN][MaxN], cf[MaxN][2], cg[MaxN][2], scf[MaxN][2];
inline void dfs1(int x, int fa)
{
	f[x][0] = 1;
	if (!p[0]) ++ cf[x][0];
	if (!p[1]) ++ cf[x][1];
	for (int i = head[x]; i; i = Next[i])
	{
		int y = ver[i];
		if (y == fa) continue;
		dfs1(y, x);
		ans += 1ll * scf[y][0] * scf[x][1] + 1ll * scf[x][0] * scf[y][1];
		scf[x][0] += scf[y][0], scf[x][1] += scf[y][1];
		for (int j = 0; j <= ld[y]; ++ j)
			for (int k = 0; k < 2; ++ k)
				if (p[k] >= j + 1) cf[x][k] += f[y][j] * f[x][p[k] - j - 1];
		for (int j = 0; j <= ld[y]; ++ j) f[x][j + 1] += f[y][j];
		chkMax(ld[x], ld[y] + 1);
	}
    scf[x][0] += cf[x][0] , scf[x][1] += cf[x][1];
}

inline void dfs2(int x, int fa)
{
	if(fa) ans += 1ll * cf[x][0] * cg[x][1] + 1ll * cg[x][0] * cf[x][1];
	for (int i = 0; i <= ld[x]; ++ i)
		for (int k = 0; k < 2; ++ k)
			if (p[k] >= i) cg[x][k] += f[x][i] * g[x][p[k] - i];
    for (int i = head[x]; i; i = Next[i])
    {
    	int y = ver[i];
    	if (y == fa) continue;
    	cg[y][0] = cg[x][0] + cf[x][0] , cg[y][1] = cg[x][1] + cf[x][1];
    	for (int j = 0; j <= n - ld[y]; ++ j) g[y][j + 1] = g[x][j] + f[x][j] - (j ? f[y][j - 1] : 0);
		for (int j = 0; j <= n; ++ j)
			for (int k = 0; k < 2; ++ k)
				if (p[k] >= j + 1) cg[y][k] -= ( g[x][j] + (f[x][j] - (j ? f[y][j - 1] : 0))) * f[y][p[k] - j - 1];
    	dfs2(y, x);
	}
}

int main()
{
	read(n, p[0], p[1]);
	for (int i = 1, x, y; i < n; ++ i) read(x, y), add(x, y), add(y, x);
	dfs1(1, 0);
	dfs2(1, 0);
	write((ans << 2), '\n', true);
	IO::flush();
	return 0;
}
