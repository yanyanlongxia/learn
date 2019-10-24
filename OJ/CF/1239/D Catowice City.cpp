#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 2e6 + 10;

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

#define YES (*IO::fe++ = 'Y', *IO::fe++ = 'E', *IO::fe++ = 'S', *IO::fe++ = '\n')
#define NO (*IO::fe++ = 'N', *IO::fe++ = 'O', *IO::fe++ = '\n')

int dfn[MaxN], low[MaxN], id;
int Stack[MaxN], top;
int belong[MaxN], siz[MaxN], deg[MaxN], tot;
bool instack[MaxN];
std::vector<int> e[MaxN];
inline void tarjan(int x)
{
	dfn[x] = low[x] = ++ id;
	Stack[++ top] = x;
	instack[x] = 1;
	for (int i = 0; i < (int)e[x].size(); ++ i)
	{
		int y = e[x][i];
		if (!dfn[y]) tarjan(y), chkMin(low[x], low[y]);
		else if (instack[y]) chkMin(low[x], dfn[y]);
	}
	if (low[x] == dfn[x])
	{
		int k;
		++ tot;
		do
		{
			k = Stack[top --];
			belong[k] = tot;
			++ siz[tot];
			instack[k] = 0;
		} while (k != x);
	}
}

int main()
{
	int T; read(T);
	while (T --)
	{
		int n, m; read(n, m);
		id = tot = 0;
		for (int i = 1; i <= n; ++ i) e[i].clear();//memset 时间复杂度是数组大小/字长，所以这题会 T ，还是手动初始化吧
		for (int i = 1, x, y; i <= m; ++ i)
		{
			read(x, y);//第 x 个人认识第 y 只猫 → 连一条 x→y 的有向边
			if (x ^ y) e[x].push_back(y);//去除自环
		}
		for (int i = 1; i <= n; ++ i) belong[i] = siz[i] = dfn[i] = low[i] = deg[i] = instack[i] = 0;//手动清空
		for (int i = 1; i <= n; ++ i)
			if (!dfn[i]) tarjan(i);//求 scc
		for (int x = 1; x <= n; ++ x)
			for (int i = 0; i < (int)e[x].size(); ++ i)
			{
				int y = e[x][i];
				if (belong[x] ^ belong[y]) ++deg[belong[y]];//求出入度，原因后面解释
			}
		if (siz[belong[1]] == n) { NO; continue; }// 如果整个图就是一个强连通分量则退出
		bool flag = 0;//如果图中出现了环 (强连通分量), 那么该环中必须全部选人或者全部选猫，不然就会出现人指向猫的边，不满足题意
		for (int i = 1; i <= tot; ++ i) if (!deg[i] && siz[i])//如果能找到符合题意的答案, 那么必须有一个强连通分量的入度为 0
		{
			YES, flag = 1;//该强连通分量中所有的点都选人，因为入度为 0 所以无需担心强连通分量外的点连向里面从而导致最终出现人指向猫的边
			std::vector<int> ans[2];
			for (int j = 1; j <= n; ++ j) ans[belong[j] == i].push_back(j);// 属于该强连通分量的全选猫 (1)，否则选人 (0)
			int human = ans[0].size(), cat = ans[1].size();
			write(human, ' ', true), write(cat, '\n', true);
			for (int j = 0; j < human; ++ j) write(ans[0][j], j == human - 1 ? '\n' : ' ', true);
			for (int j = 0; j < cat; ++ j) write(ans[1][j], j == cat - 1 ? '\n' : ' ', true);
			break;
		}
		if (!flag) NO;
	}
	IO::flush();
	return 0;
}
