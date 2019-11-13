#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 5e4 + 10;

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
		if (!x) *fe ++ = 48;
		if (x < 0) *fe ++ = '-', x = -x;
		T num = 0, ch[20];
		while (x) ch[++ num] = x % 10 + 48, x /= 10;
		while (num) *fe ++ = ch[num --];
		if (fl) *fe ++ = str;
	}
}

using IO::read;
using IO::write;

template <typename T> inline bool chkMin(T &a, const T &b) { return a > b ? (a = b, true) : false; }
template <typename T> inline bool chkMax(T &a, const T &b) { return a < b ? (a = b, true) : false; }
template <typename T> inline T min(T a, T b) { return a < b ? a : b; }
template <typename T> inline T max(T a, T b) { return a > b ? a : b; }

int ver[MaxN << 1], Next[MaxN << 1], head[MaxN], len;
inline void add(int x, int y)
{
	ver[++ len] = y, Next[len] = head[x], head[x] = len;
}

int f[MaxN];//f[i] 表示 i ( i 是叶子) 能够删掉的最远的节点，按 f[i] 和编号排序即可
inline bool cmp(int &a, int &b)
{
	return f[a] > f[b] || (f[a] == f[b] && a < b);
}

int dist[MaxN], lef[MaxN];
inline void dfs(int x, int fa)
{
	dist[x] = 1, lef[x] = x;
	for (int i = head[x]; i; i = Next[i])
	{
		int y = ver[i];
		if (y == fa) continue;
		dfs(y, x);
		if (dist[x] < dist[y] + 1 || (dist[x] == dist[y] + 1 && lef[x] > lef[y])) dist[x] = dist[y] + 1, lef[x] = lef[y];
	}
	chkMax(f[lef[x]], dist[x]);
}

int id[MaxN];
int main()//以 K 为根，每一次取一个叶子到根的路径，可以反着考虑每个点是被哪个叶子删掉的 (一定是子树里最远的那个)
{
	int n, k; read(n, k), ++ k;
	if (n == 1) return puts("0"), 0;

	for (int i = 2, x; i <= n; ++ i) read(x), ++ x, add(i, x), add(x, i);
	dfs(k, 0);
	for (int i = 1; i <= n; ++ i) id[i] = i;
	std::sort(id + 1, id + n + 1, cmp);
	write(k - 1, '\n', true);
	for (int i = 1; i <= n; ++ i)
		if (f[id[i]]) write(id[i] - 1, '\n', true);
	IO::flush();
	return 0;
}

/*
7 2
0
1
2
2
1
4

2
0
6
3
5
------
8 1
0
0
1
3
0
3
1

1
2
4
5
6
7
---
4 2
0
0
1

2
3
*/
