#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 2e3 + 10;
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

iiarr a, l, r, Up;
int main()//悬线法
{
	int n, m, ans1 = 0, ans2 = 0; read(n, m);
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j)
		{
			read(a[i][j]);
			l[i][j] = r[i][j] = j;//先都处理成右边
			Up[i][j] = 1;//高度为 1
		}
	for (int i = 1; i <= n; ++ i)//l[i][j]，r[i][j] 即（i，j）点向左/右的最大宽度
		for (int j = 2; j <= m; ++ j)
			if (a[i][j] ^ a[i][j - 1]) l[i][j] = l[i][j - 1];//预处理左边界
	for (int i = 1; i <= n; ++ i)
		for (int j = m - 1; j >= 1; -- j)
			if (a[i][j] ^ a[i][j + 1]) r[i][j] = r[i][j + 1];//预处理右边界
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j)
		{
			if (i > 1 && a[i][j] != a[i - 1][j])
			{
				chkMax(l[i][j], l[i - 1][j]);
				chkMin(r[i][j], r[i - 1][j]);//区间收束
				Up[i][j] = Up[i - 1][j] + 1;
			}
			int a = r[i][j] - l[i][j] + 1;//横向长度
			int b = min(a, Up[i][j]);//竖向长度，因为是正方形所以必须保证长宽相等
			chkMax(ans1, b * b);//正方形
			chkMax(ans2, a * Up[i][j]);//长方形
		}
	write(ans1, '\n', true);
	write(ans2, '\n', true);
	IO::flush();
	return 0;
}
