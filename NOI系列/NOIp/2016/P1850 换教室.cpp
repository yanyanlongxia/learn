#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 2e3 + 10;
const double inf = 1e17 + 10;

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

int c[MaxN][2], d[305][305];
double K[MaxN], f[MaxN][MaxN][2];
int main()
{
	int n, m, v, e; read(n, m, v, e);
	for (int i = 1; i <= n; ++ i) read(c[i][0]);
	for (int i = 1; i <= n; ++ i) read(c[i][1]);
	for (int i = 1; i <= n; ++ i) scanf("%lf", &K[i]);
	memset(d, 0x3f, sizeof(d));
	for (int i = 1, x, y, z; i <= e; ++ i) read(x, y, z), d[x][y] = d[y][x] = min(d[x][y], z);
	for (int k = 1; k <= v; ++ k)
		for (int i = 1; i <= v; ++ i)
			for (int j = 1; j <= v; ++ j) chkMin(d[i][j], d[i][k] + d[k][j]);//Floyed 处理最短路
	for (int i = 1; i <= v; ++ i) d[i][i] = d[i][0] = d[0][i] = 0;
    for (int i = 0; i <= n; ++ i)
        for (int j = 0; j <= m; ++ j) f[i][j][0] = f[i][j][1] = inf;

	f[1][0][0] = f[1][1][1] = 0;
    for (int i = 2; i <= n; ++ i)
	{
        f[i][0][0] = f[i - 1][0][0] + d[c[i - 1][0]][c[i][0]];
        for (int j = 1; j <= min(i, m); ++ j)
		{
            int C1 = c[i - 1][0], C2 = c[i - 1][1], C3 = c[i][0], C4 = c[i][1];//分类讨论，巨长
            chkMin(f[i][j][0], min(f[i - 1][j][0] + d[C1][C3], f[i - 1][j][1] + d[C1][C3] * (1 - K[i - 1]) + d[C2][C3] * K[i - 1]));
            chkMin(f[i][j][1], min(f[i - 1][j - 1][0] + d[C1][C3] * (1 - K[i]) + d[C1][C4] * K[i], f[i - 1][j - 1][1] + d[C2][C4] * K[i] * K[i - 1] + d[C2][C3] * K[i - 1] * (1 - K[i]) + d[C1][C4] * (1 - K[i - 1]) * K[i] + d[C1][C3] * (1 - K[i - 1]) * (1 - K[i])));
		}
    }
	double ans = inf;
	for (int i = 0; i <= m; ++ i) chkMin(ans, min(f[n][i][0], f[n][i][1]));
	printf("%.2f\n", ans);
	return 0;
}
