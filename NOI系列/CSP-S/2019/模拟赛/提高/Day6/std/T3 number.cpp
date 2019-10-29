#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define Grt ch = getchar()
#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 5e3 + 10, mod = 998244353;
typedef int iarr[MaxN];

namespace IO
{
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
	template <typename T> inline void write(T x, char str)
	{
		if (!x) *fe++ = 48;
		if (x < 0) *fe++ = '-', x = -x;
		T num = 0, ch[20];
		while (x) ch[++ num] = x % 10 + 48, x /= 10;
		while (num) *fe++ = ch[num --];
		*fe++ = str;
	}
}

using IO::read;
using IO::write;

template <typename T> inline bool chkMin(T &a, const T &b) { return a > b ? (a = b, true) : false; }
template <typename T> inline bool chkMax(T &a, const T &b) { return a < b ? (a = b, true) : false; }
template <typename T> inline T min(T a, T b) { return a < b ? a : b; }
template <typename T> inline T max(T a, T b) { return a > b ? a : b; }

iarr a, b, ra, rb, al, bl, lst, f, suf, pr1, pr2, pr3, pr4;
ll s1[MaxN][MaxN], s2[MaxN][MaxN];
int main()
{
	int n, m; read(n, m);
	for (int i = 1; i <= n; ++ i) read(a[i]), ra[n - i + 1] = a[i];
	for (int i = 1; i <= m; ++ i) read(b[i]), rb[m - i + 1] = b[i];

	for (int i = 1; i <= n; ++ i) lst[i] = 0;
	for (int i = 1; i <= n; ++ i) pr1[i] = lst[a[i]], lst[a[i]] = i;
	for (int i = 1; i <= m; ++ i) lst[i] = 0;
	for (int i = 1; i <= m; ++ i) pr2[i] = lst[b[i]], lst[b[i]] = i;

	for (int i = 1; i <= n; ++ i) f[i] = pr1[i] ? 0 : 1;
	for (int i = 1; i <= n; ++ i) suf[i] = (suf[i - 1] + f[i]) % mod;
	al[1] = suf[n];
	for (int i = 2; i <= n; ++ i)
	{
		for (int j = 1; j <= n; ++ j) f[j] = (suf[j - 1] - suf[max(0, pr1[j] - 1)] + mod) % mod;
		for (int j = 1; j <= n; ++ j) suf[j] = (suf[j - 1] + f[j]) % mod;
		al[i] = suf[n];
	}
	for (int i = 1; i <= m; ++ i) f[i] = pr2[i] ? 0 : 1;
	for (int i = 1; i <= m; ++ i) suf[i] = (suf[i - 1] + f[i]) % mod;
	bl[1] = suf[m];
	for (int i = 2; i <= m; ++ i)
	{
		for (int j = 1; j <= m; ++ j) f[j] = (suf[j - 1] - suf[max(0, pr2[j] - 1)] + mod) % mod;
		for (int j = 1; j <= m; ++ j) suf[j] = (suf[j - 1] + f[j]) % mod;
		bl[i] = suf[m];
	}

	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j)
		{
			s1[i][j] = (s1[i - 1][j] + s1[i][j - 1] - s1[i - 1][j - 1] + mod) % mod;
			if (a[i] == b[j])
			{
				int p1 = max(0, pr1[i] - 1), p2 = max(0, pr2[j] - 1);
				s1[i][j] = (s1[i][j] + s1[i - 1][j - 1] - s1[i - 1][p2] - s1[p1][j - 1] + s1[p1][p2] + mod + mod) % mod;
				if (!pr1[i] && !pr2[j]) ++ s1[i][j];
			}
		}

	for (int i = 1; i <= n; ++ i) lst[i] = 0;
	for (int i = 1; i <= n; ++ i) pr3[i] = lst[ra[i]], lst[ra[i]] = i;
	for (int i = 1; i <= m; ++ i) lst[i] = 0;
	for (int i = 1; i <= m; ++ i) pr4[i] = lst[rb[i]], lst[rb[i]] = i;
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j)
		{
			s2[i][j] = (s2[i - 1][j] + s2[i][j - 1] - s2[i - 1][j - 1] + mod) % mod;
			int p1 = max(0, pr3[i] - 1), p2 = max(0, pr4[j] - 1);
			s2[i][j] = (s2[i][j] + s2[i - 1][j - 1] - s2[i - 1][p2] - s2[p1][j - 1] + s2[p1][p2] + mod + mod) % mod;
			if (!pr3[i] && !pr4[j]) ++ s2[i][j];
		}
	int ans = 0;
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j) if (i > j) ans = (ans + 1ll * al[i] * bl[j]) % mod;
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j) if (a[i] > b[j])
		{
			int p1 = max(0, pr1[i] - 1), p2 = max(0, pr2[j] - 1);
			ll t = (s1[i - 1][j - 1] - s1[i - 1][p2] - s1[p1][j - 1] +s1[p1][p2] + mod + mod) % mod;
			if (!pr1[i] && !pr2[j]) ++ t;
			ans = (ans + 1ll * t * (s2[n - i][m - j] + 1)) % mod;
		}
	write(ans, '\n');
	IO::flush();
	return 0;
}
