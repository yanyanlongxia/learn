#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e6 + 10, mod = 998244353;

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

struct Orz
{
	int l, r;
	inline bool operator < (const Orz &a) const
	{
		return r < a.r || (r == a.r && l < a.l);
	}
} o[MaxN];

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

int f[MaxN], Stack[MaxN], top;
int main()
{
	int n; read(n);
	for (int i = 1; i <= n; ++ i) read(o[i].l, o[i].r);
	std::sort(o + 1, o + n + 1);
	int now = o[1].l;
	Stack[++ top] = 1;
	for (int i = 2; i <= n; ++ i)
	{
		if (o[i].l <= now && i > 2) { puts("0"); exit(0); }
		while (top > 0 && o[i].l < o[Stack[top]].r) -- top;
		chkMin(now, o[i].l);
		Stack[++ top] = i;
	}
	if (!top) *IO::fe++ = '0';
	else write(Quick_Power(2, top), '\n', true);
	IO::flush();
	return 0;
}
