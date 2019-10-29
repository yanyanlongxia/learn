#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef unsigned long long ull;
const int MaxN = 1e6 + 10;

namespace IO
{
	#define Grt ch = getc()//常数可能过大了，得开 fread 才能过
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
		T sum = 0, ch[20];
		while (x) ch[++ sum] = x % 10 + 48, x /= 10;
		while (sum) *fe++ = ch[sum --];
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

struct Graph
{
	int ver[MaxN], Next[MaxN], head[MaxN], len;
	inline void add(int x, int y)
	{
		ver[++ len] = y, Next[len] = head[x], head[x] = len;
	}
} G, A;

int dfn[MaxN], low[MaxN], id;
int Stack[MaxN], top;
int belong[MaxN], tot;
bool instack[MaxN];
inline void tarjan(int x)
{
	dfn[x] = low[x] = ++ id;
	Stack[++ top] = x;
	instack[x] = 1;
	for (int i = G.head[x]; i; i = G.Next[i])
	{
		int y = G.ver[i];
		if (!dfn[y])
		{
			tarjan(y);
			chkMin(low[x], low[y]);
		}
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
			instack[k] = 0;
		} while (k != x);
	}
}

int L, deg[MaxN];
ull *nw, *bt[MaxN], pool[100000000];//1e8
int main()
{
	int n, m, Q; read(n, m, Q);
	for (int i = 1, x, y; i <= m; ++ i) read(x, y), G.add(x, y);
	for (int i = 1; i <= n; ++ i)
		if (!dfn[i]) tarjan(i);
	for (int x = 1; x <= n; ++ x)
		for (int i = G.head[x]; i; i = G.Next[i])
		{
			int y = G.ver[i];
			if (belong[x] ^ belong[y]) A.add(belong[y], belong[x]), ++ deg[belong[x]];
		}

	nw = pool, L = (tot + 63) / 64;
	for (int i = 1; i <= tot; ++ i) bt[i] = nw, nw += L, bt[i][i >> 6] |= 1ull << (i & 63);

	std::queue<int> q;
	for (int i = 1; i <= tot; ++ i)
		if (!deg[i]) q.push(i);
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		for (int i = A.head[x]; i; i = A.Next[i])
		{
			int y = A.ver[i];
			for (int k = 0; k < L; ++ k) bt[y][k] |= bt[x][k];
			if (!-- deg[y]) q.push(y);
		}
	}
	for (int i = 1, x, y, u, v; i <= Q; ++ i)
	{
		read(u, v);
		x = belong[u], y = belong[v];
		if ((bt[x][y >> 6] >> (y & 63)) & 1) Yes;
		else No;
	}
	IO::flush();
	return 0;
}
