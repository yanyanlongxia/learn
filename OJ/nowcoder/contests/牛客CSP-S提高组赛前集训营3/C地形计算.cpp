#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e5 + 10, mod = 1e9 + 7;

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

int ver[MaxN << 1], Next[MaxN << 1], head[MaxN], len, deg[MaxN];
inline void add(int x, int y)
{
	ver[++ len] = y, Next[len] = head[x], head[x] = len, ++ deg[y];
}

inline bool cmp(int x, int y)
{
	return deg[x] > deg[y] || (deg[x] == deg[y] && x > y);
}

ll cir[MaxN], tot[MaxN];
int a[MaxN];
int main()
{
	int n, m; read(n, m);
	for (int i = 1; i <= n; ++ i) read(a[i]);
	for (int i = 1, x, y; i <= m; ++ i) read(x, y), add(x, y), add(y, x);
	for (int x = 1; x <= n; ++ x)
	{
		for (int i = head[x]; i; i = Next[i])
		{
			int y = ver[i];
			if (cmp(x, y))
				for (int k = head[y]; k; k = Next[k])
				{
					int v = ver[k];
					if (cmp(x, v)) cir[x] += tot[v], cir[y] += tot[v], cir[v] += tot[v], ++ tot[v];
				}
		}
		for (int i = head[x]; i; i = Next[i])
		{
			int y = ver[i];
			if (cmp(x, y))
				for (int k = head[y]; k; k = Next[k])
				{
					int v = ver[k];
					if (cmp(x, v)) cir[y] += (-- tot[v]);
				}
		}
	}

	ll ans = 0;
	for (int i = 1; i <= n; ++ i) (ans += 1ll * a[i] * cir[i] % mod) %= mod;
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
