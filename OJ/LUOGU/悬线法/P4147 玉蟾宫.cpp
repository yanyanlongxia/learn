#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e3 + 10;//看数据范围呀，痛失 1A
typedef int iiarr[MaxN][MaxN];

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

char a[MaxN][MaxN];
iiarr l, r, Up;
int main()//找一块只有 'R' 或 'F' 的矩形土地，要求这片土地都标着 'F'并且面积最大，于是悬线法出世
{
	int n, m, ans = 0; read(n, m);
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j)
		{
			std::cin >> a[i][j];
			l[i][j] = r[i][j] = j;
			Up[i][j] = 1;
		}
	for (int i = 1; i <= n; ++ i)
		for (int j = 2; j <= m; ++ j)
			if (a[i][j] == 'F' && a[i][j - 1] == 'F') l[i][j] = l[i][j - 1];
	for (int i = 1; i <= n; ++ i)
		for (int j = m - 1; j >= 1; -- j)
			if (a[i][j] == 'F' && a[i][j + 1] == 'F') r[i][j] = r[i][j + 1];//希望不会忘掉，呵呵

	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j)
		{
			if (i > 1 && a[i][j] == 'F' && a[i - 1][j] == 'F')
			{
				chkMax(l[i][j], l[i - 1][j]);
				chkMin(r[i][j], r[i - 1][j]);
				Up[i][j] = Up[i - 1][j] + 1;
			}
			chkMax(ans, 3 * Up[i][j] * (r[i][j] - l[i][j] + 1));//题目要求乘 3 的，我也不明白为什么
		}
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
