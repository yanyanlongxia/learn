#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 5e3 + 10, mod = 998244353;

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

int inv[MaxN], cnt[MaxN], f[MaxN][MaxN];
int main()//https://www.luogu.org/blog/m-sea/solution-cf1156f
{
    int n; read(n);
    inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; ++ i) inv[i] = (mod - 1ll * (mod / i)) * inv[mod % i] % mod;
    for (int i = 1, x; i <= n; ++ i) read(x), ++ cnt[x];
    for (int i = 1; i <= n; ++ i)
		if (cnt[i]) f[1][i] = 1ll * cnt[i] * inv[n] % mod;
	for (int i = 2; i <= n; ++ i)
	{
		int sum = 0;
		for (int j = 1; j <= n; ++ j) f[i][j] = 1ll * cnt[j] * sum % mod, sum = (sum + 1ll * f[i - 1][j] * inv[n - i + 1] % mod) % mod;
	}
	int ans = 0;
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= n; ++ j)
			if (cnt[j] > 1) ans = (ans + 1ll * f[i][j] * inv[n - i] % mod * (cnt[j] - 1) % mod) % mod;
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
