#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e5 + 10, mod = 1e5 + 3;

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

inline int Quick_Power(int a, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = 1ll * ans * a % mod;
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return ans;
}

int n, k, a[MaxN], ans[MaxN], inv[MaxN];
inline int dfs(int x, int s)
{
	if (x <= k) return ans[x] = x;
	s = (1ll * n * inv[x] % mod + 1ll * s * (n - x) % mod * inv[x] % mod) % mod;
	return ans[x] = (dfs(x - 1, s) + s) % mod;
}

int main()//题解：https://www.cnblogs.com/cjyyb/p/8419680.html
{
	int tot = 0; read(n, k);
	for (int i = 1; i <= n; ++ i) read(a[i]);
	for (int i = n; i >= 1; -- i) if (a[i])
	{
		for (int j = 1; j * j <= i; ++ j)
			if (i % j == 0)
			{
				a[j] ^= 1;
				if (j * j != i) a[i / j] ^= 1;
			}
		++ tot;
	}
	if (tot <= k)
	{
		for (int i = 1; i <= n; ++ i) tot = 1ll * tot * i % mod;
		write(tot, '\n', true);
	}
	else
	{
		for (int i = 1; i <= n; ++ i) inv[i] = Quick_Power(i, mod - 2);
		dfs(n, 1);
		for (int i = 1; i <= n; ++ i) ans[tot] = 1ll * ans[tot] * i % mod;
		write(ans[tot], '\n', true);
	}
	IO::flush();
	return 0;
}
