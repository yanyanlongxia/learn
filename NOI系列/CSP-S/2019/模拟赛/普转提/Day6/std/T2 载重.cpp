#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e5 + 10, MaxM = 3e5 + 10, inf = 0x3f3f3f3f;

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

#define Yes (*IO::fe++ = 'Y', *IO::fe++ = 'e', *IO::fe++ = 's', *IO::fe++ = '\n')
#define No (*IO::fe++ = 'N', *IO::fe++ = 'o', *IO::fe++ = '\n')

struct Orz
{
	int x, y, z;
	inline bool operator < (const Orz &a) const//最大生成树
	{
		return z > a.z;
	}
} e[MaxM];

int fa[MaxN];
inline int get(int x)//压缩路径，初赛的一个坑，暴毙
{
	return fa[x] == x ? x : fa[x] = get(fa[x]);
}

int ver[MaxM << 1], edge[MaxM << 1], Next[MaxM << 1], head[MaxN], len;
inline void add(int x, int y, int z)
{
	ver[++ len] = y, edge[len] = z, Next[len] = head[x], head[x] = len;
}

namespace lca//这里是火车运输的 lca，一样的，还记得当时在 hl 调了好长时间，一直写不对，哎，我也只能从这里看出自己成长了
{
	int dep[MaxN], f[MaxN][21], w[MaxN][21];
	bool vis[MaxN];
	inline void dfs(int x)
	{
		vis[x] = 1;//记得标记，要不 O(n) 的复杂度就变成了 O(n^2)，T 掉
		for (int i = 1; i <= 20; ++ i)
		{
			f[x][i] = f[f[x][i - 1]][i - 1];
			w[x][i] = min(w[x][i - 1], w[f[x][i - 1]][i - 1]);
		}
		for (int i = head[x]; i; i = Next[i])
		{
			int y = ver[i];
			if (y == f[x][0]) continue;
			f[y][0] = x;
			w[y][0] = edge[i];
			dep[y] = dep[x] + 1;
			dfs(y);
		}
	}

	inline int LCA(int x, int y)
	{
		int ans = inf;
		if (dep[x] > dep[y]) std::swap(x, y);
		for (int i = 20; i >= 0; -- i)
			if (dep[y] - (1 << i) >= dep[x]) chkMin(ans, w[y][i]), y = f[y][i];
		if (x == y) return ans;
		for (int i = 20; i >= 0; -- i)
			if (f[x][i] ^ f[y][i]) chkMin(ans, min(w[x][i], w[y][i])), x = f[x][i], y = f[y][i];
		chkMin(ans, min(w[x][0], w[y][0]));
		return ans;
	}
}

using lca::vis;
using lca::dfs;
using lca::LCA;

int main()//见到题目的第一眼，觉得是火车运输，然后想了想，正如 IOI 普转提不会出这么显然吧，然后想不到啊，看看题解
{//写的是个啥，感觉没说一样，然后无奈之下点开 duyi 的 code，然后立刻关掉，为啥，因为第一眼就看到这就是火车运输
	int n, m, Q; read(n, m, Q);//然后就是写完后，交上去爆零，懵逼？？打开看看细节，哦，忘了标记 vis[i]，给 w 赋 0x3f
	for (int i = 1; i <= m; ++ i) read(e[i].x, e[i]. y, e[i].z);//然后又爆零了，额，不对吧，应该没问题了丫，然后发现手残
	std::sort(e + 1, e + m + 1);
	for (int i = 1; i <= n; ++ i) fa[i] = i;
	for (int i = 1; i <= m; ++ i)//手残，刚刚写的思路没删，直接改了，结果导致这里写的是 Q，怪不得一直爆零
	{
		int x = get(e[i].x), y = get(e[i].y);
		if (x == y) continue;
		fa[x] = y;
		add(e[i].x, e[i].y, e[i].z), add(e[i].y, e[i].x, e[i].z);
	}
	memset(lca::w, 0x3f, sizeof(lca::w));
	for (int i = 1; i <= n; ++ i)
		if (!vis[i]) dfs(i);
	for (int i = 1, x, y, z; i <= Q; ++ i)
	{
		read(x, y, z);
		if (get(x) != get(y)) { No; continue; }//x 无法到达 y
		if (LCA(x, y) >= z) Yes;//x -> y 的路径上的最小权值大于 z，满足条件
		else No;
	}
	IO::flush();
	return 0;
}
