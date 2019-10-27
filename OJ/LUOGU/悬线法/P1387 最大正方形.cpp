#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e2 + 10;
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
int main()//本题题意：在一个 n*m 的只包含 0 和 1 的矩阵里找出一个不包含 0 的最大正方形，输出边长
{//这下悬线法的套路就算好了，遇到具体的题具体对待吧
	int n, m, ans = 0; read(n, m);
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j)
		{
			read(a[i][j]);
			l[i][j] = r[i][j] = j;//初始化，左右边界都先赋值为右边
			Up[i][j] = 1;//初值为 1，因为自己就算一个长度
		}
	for (int i = 1; i <= n; ++ i)
		for (int j = 2; j <= m; ++ j)
			if (a[i][j] && a[i][j - 1]) l[i][j] = l[i][j - 1];
	for (int i = 1; i <= n; ++ i)
		for (int j = m - 1; j >= 1; -- j)
			if (a[i][j] && a[i][j + 1]) r[i][j] = r[i][j + 1];//套路，不过注意一下条件符合题目即可
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j)
		{
			if (i > 1 && a[i][j] && a[i - 1][j])
			{
				chkMax(l[i][j], l[i - 1][j]);
				chkMin(r[i][j], r[i - 1][j]);
				Up[i][j] = Up[i - 1][j] + 1;//这个也是普通的悬线法状态转移
			}
			chkMax(ans, min(Up[i][j], (r[i][j] - l[i][j] + 1)));//注意题目要求的是什么
		}
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
