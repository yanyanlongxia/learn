#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 2e3 + 10, mod = 1e9 + 7;

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
		T sum = 0, ch[20];
		while (x) ch[++ sum] = x % 10 + 48, x /= 10;
		while (sum) *fe++ = ch[sum --];
		if (fl) *fe++ = str;
	}
}

using IO::read;
using IO::write;

template <typename T> inline bool chkMin(T &a, const T &b) { return a > b ? (a = b, true) : false; }
template <typename T> inline bool chkMax(T &a, const T &b) { return a < b ? (a = b, true) : false; }
template <typename T> inline T min(T a, T b) { return a < b ? a : b; }
template <typename T> inline T max(T a, T b) { return a > b ? a : b; }

template <typename T> inline void Add(T &a, T b) { a += b; if (a > mod) a -= mod; }

namespace BIT
{
	ll c[MaxN][MaxN];
	inline int lowbit(int x) { return x & -x; }
	inline void add(int l, int x, ll k) { while (x < MaxN) Add(c[l][x], k), x += lowbit(x); }
	inline ll ask(int l, int x) { ll ans = 0; while (x) Add(ans, c[l][x]), x -= lowbit(x); return ans; }
}

using BIT::add;
using BIT::ask;

int a[MaxN], b[MaxN];
ll fac[MaxN], f[MaxN][MaxN], sum[MaxN];
int main()
{
	int n; read(n);
	fac[0] = 1;
	for (int i = 1; i <= n; ++ i) read(a[i]), b[i] = a[i], fac[i] = 1ll * fac[i - 1] * i % mod;
	std::sort(b + 1, b + n + 1);
	int tot = std::unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; ++ i) a[i] = std::lower_bound(b + 1, b + tot + 1, a[i]) - b, f[1][i] = 1ll;
	for (int i = 2; i <= n; ++ i)
	{
		add(i - 1, a[i - 1], f[i - 1][i - 1]);
		for (int j = i; j <= n; ++ j) Add(f[i][j], ask(i - 1, a[j])), add(i - 1, a[j], f[i - 1][j]);
	}
	for (int i = 1; i <= n; ++ i)
		for (int j = i; j <= n; ++ j) Add(sum[i], f[i][j]);
    ll ans = 0;
    for (int i = 1; i <= n; ++ i) Add(ans, (sum[i] * fac[n - i] % mod - sum[i + 1] * fac[n - i - 1] % mod * (i + 1) % mod + mod) % mod);
    write(ans, '\n', true);
    IO::flush();
	return 0;
}
