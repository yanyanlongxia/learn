#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e6 + 10;
const ll mod = 1ll << 32;

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

int A, B, C, P;
inline int rnd() { return A = (A * B + C) % P; }

int ver[MaxN], Next[MaxN], head[MaxN], len;
inline void add(int x, int y)
{
	ver[++ len] = y, Next[len] = head[x], head[x] = len;
}

int dfn[MaxN], edn[MaxN], id;
inline void dfs(int x, int fa)
{
	dfn[x] = ++ id;
	for (int i = head[x]; i; i = Next[i])
	{
		int y = ver[i];
		if (y == fa) continue;
		dfs(y, x);
	}
	edn[x] = ++ id;
}

int a[MaxN], fa[MaxN];//fa->这个点前面的第一个必胜转移点
int main()
{
	int n, m, q, type; read(n, m, q, type);
	for (int i = 1; i <= n; ++ i) read(a[i]);
	for (int i = 1; i <= n; ++ i)//处理出每个点倒序第一个必胜转移点
	{
		int L = max(0, i - m - 1);
		if (a[i] & 1)//奇数是必胜点
		{
			if (a[L] & 1) fa[i] = L, add(L, i);
			else fa[i] = fa[L], add(fa[L], i);
		}
		else//偶数，先手必败
		{
			if (a[i - 1] & 1) fa[i] = i - 1, add(i - 1, i);
			else fa[i] = fa[i - 1], add(fa[i - 1], i);
		}
	}
	dfs(0, 0);//dfs序
	ll ans = 0;
	if (type) read(A, B, C, P);
	for (int i = 1, x, y; i <= q; ++ i)
	{
		if (!type) read(x, y);
		else
		{
			x = rnd() % n + 1, y = rnd() % n + 1;
			if (x > y) std::swap(x, y);
		}
		if (x == y)
		{
			if (a[x] & 1);
			else ans = (ans + 1ll * i * i) % mod;
		}
		else
		{
			if (dfn[x] <= dfn[y] && edn[y] <= edn[x]);//x 是 y 的祖先，先手必胜，没有贡献
			else ans = (ans + 1ll * i * i) % mod;
		}
	}
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
