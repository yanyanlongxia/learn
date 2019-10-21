#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e4 + 10, MaxM = 1e5 + 10, inf = 0x3f3f3f3f;

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

char s;
double f[2], g[2];//设 f[i] 表示到了第 i 位的总期望 combo， g[i] 表示到了第 i 位结尾的连续 o 的期望长度
int main()
{
	int n, x = 0; read(n);
	for (int i = 1; i <= n; ++ i, x ^= 1)
	{
		std::cin >> s;
		if (s == 'o') f[x ^ 1] = f[x] + g[x] * 2 + 1, g[x ^ 1] = g[x] + 1;
		else if (s == 'x') f[x ^ 1] = f[x], g[x ^ 1] = 0;
		else f[x ^ 1] = f[x] + g[x] + 0.5, g[x ^ 1] = g[x] / 2 + 0.5;
	}
	printf("%.4lf\n", f[x]);
	return 0;
}
