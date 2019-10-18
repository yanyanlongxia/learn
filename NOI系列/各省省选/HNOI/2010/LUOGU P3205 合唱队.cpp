#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e3 + 10, mod = 19650827;

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

int a[MaxN];
int f[MaxN][MaxN], g[MaxN][MaxN];
//设 f[i][j] 为可以排成理想队列中 [i,j] 区间，且以最后一个排进去是第 i 人的初始队列种数
//g[i][j] 为可以排成理想队列中 [i,j] 区间，且以最后一个排进去是第 j 人的初始队列种数
int main()//我可真没看出来这是个区间 Dp 啊！
{
	int n; read(n);
	for (int i = 1; i <= n; ++ i) read(a[i]), f[i][i] = 1;//初始值，只有一个人的区间只有 1 种情况
	for (int len = 1; len <= n; ++ len)
		for (int l = 1; l + len <= n; ++ l)
		{
			int r = l + len;
			f[l][r] = (f[l + 1][r] * (a[l] < a[l + 1]) + g[l + 1][r] * (a[l] < a[r])) % mod;//前一个排进去的人是 i + 1 ，当前人插到最左边；前一个排进去的人是 j ，当前人插到最左边
			g[l][r] = (f[l][r - 1] * (a[r] > a[l]) + g[l][r - 1] * (a[r] > a[r - 1])) % mod;//前一个排进去的人是 i ，当前人插到最右边；前一个排进去的人是 j - 1 ，当前人插到最右边
		}
	write((f[1][n] + g[1][n]) % mod, '\n');
	IO::flush();
	return 0;
}
