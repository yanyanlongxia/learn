#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 20, MaxS = 1 << 20;
const double eps = 1e-8;

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

inline void Function(double &x, double &y, double a1, double b1, double c1, double a2, double b2, double c2)
{//a_1x + b_1y = c_1, a_2x + b_2y = c_2→a_1a_2x + b_1a_2y = c_1a_2, a_2a_1x + b_2a_1y = c_2a_1
	y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1), x = (c1 - b1 * y) / a1;//→(a_1b_2 - a_2b_1)y = (a_1c_2 - a_2c_1)
}

double X[MaxN], Y[MaxN];
int f[MaxS], lowbit[MaxS], line[MaxN][MaxN];
int main()
{
	for (int s = 0; s < (1 << 18); ++ s)
	{
		int i = 1;
		for ( ; i <= 18 && (s & (1 << (i - 1))); ++ i);
		lowbit[s] = i;
	}

	int T; read(T);
	while (T --)
	{
		memset(line, 0, sizeof(line));
		memset(f, 0x3f, sizeof(f));
		f[0] = 0;//初始化
		int n, m; read(n, m);
		for (int i = 1; i <= n; ++ i) scanf("%lf%lf", X + i, Y + i);
		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= n; ++ j)
			{
				if (std::fabs(X[i] - X[j]) < eps) continue;//x 坐标相同，不可能有解
				double a, b;
				Function(a, b, X[i] * X[i], X[i], Y[i], X[j] * X[j], X[j], Y[j]);//解出 a 和 b
				if (a > -eps) continue;
				for (int k = 1; k <= n; ++ k)//看这条抛物线最多能够打掉几头猪
					if (std::fabs(a * X[k] * X[k] + b * X[k] - Y[k]) < eps) line[i][j] |= (1 << (k - 1));//这个地方写成了 (1 << k) - 1，我服了
			}
		for (int s = 0; s < (1 << n); ++ s)
		{
			int i = lowbit[s];//i 为满足 S \& (1<<(i-1)) = 0 的最小正整数，则由 S 扩展的转移的所有线都要经过 x
			chkMin(f[s | (1 << (i - 1))], f[s] + 1);
			for (int k = 1; k <= n; ++ k) chkMin(f[s | line[i][k]], f[s] + 1);//然后枚举抛物线
		}
		write(f[(1 << n) - 1], '\n', true);
	}
	IO::flush();
	return 0;
}
