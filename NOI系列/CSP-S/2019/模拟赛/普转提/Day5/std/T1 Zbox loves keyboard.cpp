#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e6 + 2e3, inf = 0x3f3f3f3f;

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

int f[MaxN];
int main()
{
	int x, n; read(x, n);
	memset(f, 0x3f, sizeof(f));
	f[x] = 0, f[0] = min(x, 3);
	for (int i = 0; i <= n; ++ i)
	{
		if (i > 0) chkMin(f[i], f[i - 1] + 1);
		chkMin(f[i], f[i + 1] + 1);
		for (int j = 1, t; j <= 10; ++ j)
		{
			t = i * (j + 1);
			if (t > n + 150) break;
			chkMin(f[t], f[i] + (j << 1) + 4);
		}
	}
	int ans = inf;
	for (int i = 0 ; i <= n + 150; ++ i) chkMin(ans, f[i] + abs(n - i));
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
