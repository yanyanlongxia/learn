#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e5 + 10;

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

int n;
struct BIT
{
	int c[MaxN];
	inline int lowbit(int x) { return x & -x; }
	inline void add(int x, int k) { while (x <= n) c[x] += k, x += lowbit(x); }
	inline int ask(int x) { int ans = 0; while (x) ans += c[x], x -= lowbit(x); return ans; }
	inline int hsh(int l, int r) { return ask(r) - ask(l - 1); }
} bit;

int dfn[MaxN], edn[MaxN], id;
namespace T1
{
	int ver[MaxN << 1], Next[MaxN << 1], head[MaxN], len;
	inline void add(int x, int y)
	{
		ver[++ len] = y, Next[len] = head[x], head[x] = len;
	}

	inline void dfs(int x, int fa)
	{
		dfn[x] = ++ id;
		for (int i = head[x]; i; i = Next[i])
		{
			int y = ver[i];
			if (y == fa) continue;
			dfs(y, x);
		}
		edn[x] = id;
	}
}

int ans[MaxN];
namespace T2
{
	int ver[MaxN << 1], Next[MaxN << 1], head[MaxN], len;
	inline void add(int x, int y)
	{
		ver[++ len] = y, Next[len] = head[x], head[x] = len;
	}

	inline void dfs(int x, int fa)
	{
		ans[x] = bit.ask(dfn[x] - 1);
		bit.add(dfn[x], 1);
		bit.add(edn[x], -1);
		for (int i = head[x]; i; i = Next[i])
		{
			int y = ver[i];
			if (y == fa) continue;
			dfs(y, x);
		}
		bit.add(dfn[x], -1);
		bit.add(edn[x], 1);
	}
}

int main()//两颗 n 节点的树，不相同，问多少点对 (u,v) 在两棵树上均满足路径 v 在 u 子树中
{
	read(n);
	for (int i = 1, x, y; i < n; ++ i) read(x, y), T1::add(x, y), T1::add(y, x);
	T1::dfs(1, 0);//第一棵树，将其拍成 dfs 序
	for (int i = 1, x, y; i < n; ++ i) read(x, y), T2::add(x, y), T2::add(y, x);
	T2::dfs(1, 0);//跑第二棵树，维护一个下标为dfs序的树状数组，每次第一次遍历到节点i时，我们统计在当前节点的dfs序之前（即满足在第一棵树上节点i在j的子树中）且在当前这第二棵树上已经遍历过的节点（即满足在第二棵树上节点i在j的子树中）的个数，加入到答案。这个过程相当于统计每个(u,v)中的v
	ll sum = 0;
	for (int i = 1; i <= n; ++ i) sum += ans[i];
	write(sum, '\n', true);
	IO::flush();
	return 0;
}

/*
4
1 2
2 3
3 4
1 2
2 3
2 4

5
*/
