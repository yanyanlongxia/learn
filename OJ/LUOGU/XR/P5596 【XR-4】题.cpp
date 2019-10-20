#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;

namespace IO
{
	#define G ch = getchar()
	char buf[1<<15], *fs, *ft;
	inline char getc() { return ft == fs && (ft = (fs = buf) + fread(buf, 1, 1 << 15, stdin), ft == fs) ? 0 : *fs ++; }
	template <typename T> inline void read(T &x)
	{
		x = 0;
		T f = 1, G;
		while (!isdigit(ch) && ch ^ '-') G;
		if (ch == '-') f = -1, G;
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), G;
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

inline bool check(ll a, ll b)
{
	if (((a + b) & 1) || ((b - a) & 1)) return 0;
	ll x = (a + b) >> 1, y = (b - a) >> 1;
	return (x < 0 || y < 0) ? 0 : 1;
}

int main()//完全平方公式补全，然后根据式子枚举
{
	ll a, b, ans = 0; read(a, b);
	ll xx = (b << 2) - a * a;
	if (!xx) { puts("inf"); exit(0); }
	else if (xx >= 0)
	{
		for (ll i = 1; i <= sqrt(xx); ++ i)
			if (xx % i == 0)
			{
				if (((i + a) & 1) || ((xx / i - a) & 1)) continue;
				ll x = (i + a) >> 1, y = (xx / i - a) >> 1;
				if (check(x, y)) ++ ans;
			}
	}
	else
	{
		xx = -xx;
		for (ll i = 1; i <= sqrt(xx); ++ i)
			if (xx % i == 0)
			{
				if (((i - a) & 1) || ((xx / i - a) & 1)) continue;
				ll x = (i - a) >> 1, y = (xx / i - a) >> 1;
				if (check(x, y)) ++ ans;
			}
	}
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
