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
double dist[MaxN * 10][MaxN];
int num[MaxN], n, m, t, S, T;
bool vis[MaxN * 10][MaxN];
inline void spfa(int S)
{
	for (int i = 0; i <= 300; ++ i)
			for (int j = 0; j < 33; ++ j) dist[i][j] = inf;//初始化
	memset(vis, 0, sizeof(vis));
	std::queue<pii> q; q.push(mp(0, S));
	dist[0][S] = 0, vis[0][S] = 1;
	while (!q.empty())
	{
		int s = q.front().fi, x = q.front().se;
		q.pop();
		vis[s][x] = 0;//其实跟普通 spfa 一样
		for (int k = 0; k < t; ++ k)//枚举车票（马票）？
		{
			if ((s >> k) & 1) continue;//用过就跳过这个车票
			for (int i = 0; i < (int)e[x].size(); ++ i)
			{
				int y = e[x][i].fi, z = e[x][i].se;
				if (chkMin(dist[s | (1 << k)][y], dist[s][x] + (double)z / num[k]))//正常转移
					if (!vis[s | (1 << k)][y]) q.push(mp(s | (1 << k), y)), vis[s | (1 << k)][y] = 1;//毕竟是 spfa 丫
			}
		}
	}
}

int main()
{
	read(t, n, m, S, T);
	while (true)
	{
		if (!t && !n && !m && !S && !T) break;
		for (int i = 0; i < t; ++ i) read(num[i]);
		for (int i = 0; i <= n; ++ i) e[i].clear();
		for (int i = 1, x, y, z; i <= m; ++ i) read(x, y, z), e[x].push_back(mp(y, z)), e[y].push_back(mp(x, z));
		spfa(S);//跑个最短路，说实在的，不想写 Dijkstra，太伤我心了
		double ans = inf;
		for (int i = 0; i < (1 << t); ++ i) chkMin(ans, dist[i][T]);//选出最小的，废话
		if (ans == inf) puts("Impossible");
		else printf("%.4lf\n", ans);
		read(t, n, m, S, T);//多组数据真坑
	}
	return 0;
}
