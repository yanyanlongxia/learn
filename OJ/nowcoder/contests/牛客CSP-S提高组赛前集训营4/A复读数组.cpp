#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e5 + 10, mod = 1e9 + 7, inv2 = (mod + 1) >> 1;

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

inline ll Cn2(int x)
{
	return 1ll * x * (x + 1) % mod * inv2 % mod;
}

int a[MaxN], last[MaxN];
bool Mark[MaxN];
std::map<int, int> M;
int main()
{
	int n, k; read(n, k);
	for (int i = 1; i <= n; ++ i) read(a[i]);
	int tot = 0;
	for (int i = 1; i <= n; ++ i)
	{
		if (!M[a[i]]) M[a[i]] = ++ tot;
		a[i] = M[a[i]];
	}

	ll ans = Cn2(1ll * n * k % mod) * tot % mod;
	for (int i = 1; i <= n; ++ i)
	{
		if (!last[a[i]]) Mark[i] = true;
		else (ans -= Cn2(i - last[a[i]] - 1) * k) %= mod;
		last[a[i]] = i;
	}
	for (int i = 1; i <= n; ++ i)
		if (Mark[i]) (ans -= Cn2(i - 1 + n - last[a[i]]) * (k - 1) + Cn2(i - 1) + Cn2(n - last[a[i]])) %= mod;
	write((ans + mod) % mod, '\n', true);
	IO::flush();
	return 0;
}
