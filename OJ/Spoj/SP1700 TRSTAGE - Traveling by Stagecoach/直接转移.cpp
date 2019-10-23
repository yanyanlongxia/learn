#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

#define fi first
#define se second
#define mp std::make_pair
typedef std::pair<int, int> pii;
const int MaxN = 33, inf = 0x3f3f3f3f;

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

std::vector<pii> e[MaxN];
double f[MaxN * 10][MaxN];
int num[MaxN];
int main()//为什么可以直接转移呢？由于剩余的车票的集合 s 随着移动元素个数不断减小，因此这个图实际上是一个 DAG
{
	int t, n, m, S, T;
	read(t, n, m, S, T);
	while (true)
	{
		if (!t && !n && !m && !S && !T) break;
		for (int i = 0; i < t; ++ i) read(num[i]);
		for (int i = 0; i <= n; ++ i) e[i].clear();
		for (int i = 1, x, y, z; i <= m; ++ i) read(x, y, z), e[x].push_back(mp(y, z)), e[y].push_back(mp(x, z));
		for (int i = 0; i <= 300; ++ i)
			for (int j = 0; j < 33; ++ j) f[i][j] = inf;//初始化
		f[0][S] = 0;
		double ans = inf;
		for (int s = 0; s < (1 << t); ++ s)//枚举状态
		{
			for (int x = 1; x <= n; ++ x)//枚举每个点
				for (int k = 0; k < t; ++ k)//枚举所有车票（马票）？
				{
					if ((s >> k) & 1) continue;//如果这个车票被用过了，就跳过
					for (int i = 0; i < (int)e[x].size(); ++ i)//枚举出边
					{
						int y = e[x][i].fi, z = e[x][i].se;
						chkMin(f[s | (1 << k)][y], f[s][x] + (double)z / num[k]);//看起来很明显的状态转移
					}
				}
			chkMin(ans, f[s][T]);//到达终点的最短时间
		}
		if (ans == inf) puts("Impossible");
		else printf("%.4lf\n", ans);
		read(t, n, m, S, T);//多组数据真坑
	}
	return 0;
}
