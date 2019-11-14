#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 3e2 + 10;

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

int sum[MaxN][MaxN];
int main()
{
	int d, n; read(d, n);
	for (int i = 1, x, y, k; i <= n; ++ i) read(x, y, k), sum[x + 1][y + 1] = k;
	for (int i = 1; i <= 129; ++ i)
		for (int j = 1; j <= 129; ++ j) sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
	ll Max = 0, cnt = 0;
	for (int i = 1; i <= 129; ++ i)
		for (int j = 1; j <= 129; ++ j)//改为枚举每个正方形的中心点，于是左下角为 (i - d, j - d)，右上角为 (i + d, j + d)
		{
			int xl = i - d >= 1 ? (i - d) : 1, yl = j - d >= 1 ? (j - d) : 1;
			int xr = i + d <= 129 ? (i + d) : 129, yr = j + d <= 129 ? (j + d) : 129;//说实在话，挺无语的，非要这样才能避免边界问题
			int tmp = sum[xr][yr] - sum[xl - 1][yr] - sum[xr][yl - 1] + sum[xl - 1][yl - 1];//所以以后遇到这种边界问题，还是老老实实写上原始边界，然后判断这个点是否在这个边界里好了
			if (Max < tmp) Max = tmp, cnt = 1;//真烦
			else if (Max == tmp) ++ cnt;
		}
	write(cnt, ' ', true), write(Max, '\n', true), IO::flush();
	return 0;
}
