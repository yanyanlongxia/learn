#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e4 + 10, MaxM = 2e3 + 10, inf = 0x3f3f3f3f;

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

int X[MaxN], Y[MaxN];//i 位置，上升 X[i] ，下降 Y[i]
int low[MaxN], high[MaxN];////i位置能通过的范围是low[i]-high[i]
int f[MaxN][MaxM];//到(i,j)的最少点击次数
bool e[MaxN];//e[i]表示i位置有没有管道
int main()
{
	int n, m, k; read(n, m, k);
	for (int i = 1; i <= n; ++ i) read(X[i], Y[i]), low[i] = 1, high[i] = m;
	for (int i = 1, a, b, c; i <= k; ++ i) read(a, b, c), e[a] = 1, low[a] = b + 1, high[a] = c - 1;

	memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= m; ++ i) f[0][i] = 0;
	for (int i = 1; i <= n; ++ i)
	{
		for (int j = X[i] + 1; j <= X[i] + m; ++ j) f[i][j] = min(f[i][j - X[i]] + 1, f[i - 1][j - X[i]] + 1);//上升 ——完全背包
		for (int j = m + 1; j <= m + X[i]; ++ j) chkMin(f[i][m], f[i][j]);//超过 m 变为 m ——特判
		for (int j = 1; j <= m - Y[i]; ++ j) chkMin(f[i][j], f[i - 1][j + Y[i]]);//下降 ——01背包
		for (int j = 1; j < low[i]; ++ j) f[i][j] = inf;
		for (int j = high[i] + 1; j <= m; ++ j) f[i][j] = inf;//管道都不能通过
	}
	int ans = inf;
	for (int i = 1; i <= m; ++ i) chkMin(ans, f[n][i]);//最终状态下的最优值
	if (ans < inf) write(1, '\n', true), write(ans, '\n', true);
	else
	{
		int i, j;
		for (i = n; i >= 1; -- i)//从后枚举，看最多能到哪个横坐标
		{
			for (j = 1; j <= m; ++ j)
				if (f[i][j] < inf) break;
			if (j <= m) break;
		}
		ans = 0;
		for (int j = 1; j <= i; ++ j)//从 1~i 中看有多少管道
			if (e[j]) ++ ans;
		write(0, '\n', true), write(ans, '\n', true);
	}
	IO::flush();
	return 0;
}
