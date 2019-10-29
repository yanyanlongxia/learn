#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define Grt ch = getchar()
#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 4e5 + 10, mod = 998244353;

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

template <typename T> inline void Pop(T &x) { if (x < 0) x += mod; }

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

int fac[MaxN], inv[MaxN];
inline int C(int n, int m)
{
	if (n < m) return 0;
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int n, m, k, h[MaxN], c[MaxN];
inline void Pre(int a, int s)
{
	h[k] = Quick_Power(a, k);
	for (int i = k + 1, p = 1; i <= s; ++ i, p = 1ll * p * (a - 1) % mod) Pop(h[i] = (1ll * a * h[i - 1] - 1ll * p * c[i - 1]) % mod);
}

int f[MaxN], s[MaxN];
int main()
{
	read(n, m, k), k = n - k;

	fac[0] = 1;
	for (int i = 1; i <= n; ++ i) fac[i] = 1ll * fac[i - 1] * i % mod;//½×³Ë
	inv[n] = Quick_Power(fac[n], mod - 2);
	for (int i = n - 1; i >= 0; -- i) inv[i] = 1ll * inv[i + 1] * (i + 1) % mod;//ÄæÔª

	for (int i = k; i <= n; ++ i) c[i] = C(i, k);//·½±ã²éÑ¯

	for (int i = 1, a; i <= n; ++ i) read(a), ++ s[a];
	for (int i = 1; i <= m; ++ i)
		for (int j = i << 1; j <= m; j += i) s[i] += s[j];//
	for (int l = 1, r; l <= m; l = r + 1)
	{
		int a = m /l, Max = 0;
		r = m / a;
		for (int t = l; t <= r; ++ t) chkMax(Max, s[t]);
		if (Max > k) Pre(a, Max);
		for (int t = l; t <= r; ++ t)
			if (s[t] <= k) f[t] = Quick_Power(a, n);
			else f[t] = 1ll * h[s[t]] * Quick_Power(a, n - s[t]) % mod;
	}
	for (int i = m; i >= 1; -- i)
		for (int j = i << 1; j <= m; j += i) Pop(f[i] -= f[j]);
	for (int i = 1; i <= m; ++ i) write(f[i], ' ');
	IO::flush();
	return 0;
}
