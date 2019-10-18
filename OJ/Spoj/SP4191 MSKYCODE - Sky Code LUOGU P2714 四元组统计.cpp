#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e4 + 10, MaxM = 1e4;

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

ll f[MaxN];
int main()//第一步想对了，开桶记录即可，没有想到第二步可以直接让每个数的倍数组成四元组，再减去他的约数的倍数组成的四元组就好了，真妙！
{
	int n;
	while (~scanf("%d", &n))
	{
		memset(f, 0, sizeof(f)); ll ans = 0;
		for (int i = 1, x; i <= n; ++ i) read(x), ++ f[x];
		for (int i = 1; i <= MaxM; ++ i)
			for (int j = i << 1; j <= MaxM; j += i) f[i] += f[j];//开一个桶 f 记录 i 的倍数的个数
		for (int i = MaxM; i >= 1; -- i)
		{
			f[i] = f[i] * (f[i] - 1) * (f[i] - 2) * (f[i] - 3) / 24;//i 的倍数能组成多少四元组
			for (int j = i << 1; j <= MaxM; j += i) f[i] -= f[j];////减去 gcd 是 2i,3i,... 的四元组
		}
		write(f[1], '\n');
	}
	IO::flush();
	return 0;
}
