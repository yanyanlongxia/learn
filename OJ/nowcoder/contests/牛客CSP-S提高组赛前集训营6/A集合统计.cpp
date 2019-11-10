#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e6 + 10, mod = 1e9 + 7;

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

inline ll Quick_Power(ll a, ll b)
{
	ll ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}

ll a[MaxN];
int main()
{
	int n; read(n);
	for (int i = 1; i <= n; ++ i) read(a[i]);
	std::sort(a + 1, a + n + 1);
	ll ans = 0;
	for (int i = 1; i <= n; ++ i) ans = (ans + 1ll * a[i] * Quick_Power(2, i - 1) % mod + mod) % mod;//设小于 a_i 的数共有 j 个，那么 a_i 作为最大值的子集共有 2^j 个，对答案累加上 2^j\times a_i 即可
	std::reverse(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++ i) ans = (ans - 1ll * a[i] * Quick_Power(2, i - 1) % mod + mod) % mod;//a_i 作为最小值同理
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
