#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define Grt ch = getchar()
#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 8e3 + 10;

namespace IO
{
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
	template <typename T> inline void write(T x, char str)
	{
		if (!x) *fe++ = 48;
		if (x < 0) *fe++ = '-', x = -x;
		T num = 0, ch[20];
		while (x) ch[++ num] = x % 10 + 48, x /= 10;
		while (num) *fe++ = ch[num --];
		*fe++ = str;
	}
}

using IO::read;
using IO::write;

template <typename T> inline bool chkMin(T &a, const T &b) { return a > b ? (a = b, true) : false; }
template <typename T> inline bool chkMax(T &a, const T &b) { return a < b ? (a = b, true) : false; }
template <typename T> inline T min(T a, T b) { return a < b ? a : b; }
template <typename T> inline T max(T a, T b) { return a > b ? a : b; }

int n, q, mod;
inline int FK(int x) { return x < 0 ? x + 256 : x; }
inline int FF(int x) { return x >= mod ? x - mod : (x < 0 ? x + mod : x); }

struct BIT
{
	char c[MaxN][MaxN];
	inline int lowbit(int x) { return x & -x; }
	inline void add2(int x, int y, int k) { while (y <= n) c[x][y] = FF(FK(c[x][y]) + k), y += lowbit(y); }
	inline void add1(int x, int y, int k) { while (x <= n) add2(x, y, k), x += lowbit(x); }
	inline int ask2(int x, int y) { int ans = 0; while (y) ans += FK(c[x][y]), y -= lowbit(y); return ans; }
	inline int ask1(int x, int y) { int ans = 0; while (x) ans += ask2(x, y), x -= lowbit(x); return ans % mod; }
} G, A, T, R;

inline void add(int x, int y, int k)
{
	if (!x || !y) return ;
	G.add1(1, 1, k), G.add1(x + 1, 1, -k), G.add1(1, y + 1, -k), G.add1(x + 1, y + 1, k);
	A.add1(x + 1, 1, x * k % mod), A.add1(x + 1, y + 1, -x * k % mod);
	T.add1(1, y + 1, y * k % mod), T.add1(x + 1, y + 1, -y * k % mod);
	R.add1(x + 1, y + 1, x * y * k % mod);
}

inline int ask(int x, int y)
{
	return G.ask1(x, y) * x % mod * y % mod +
			A.ask1(x, y) * y % mod +
			T.ask1(x, y) * x % mod +
			R.ask1(x, y);
}

int main()
{
	read(n, q, mod);
	int r = 0;
	memset(G.c, 0, sizeof(G.c)), memset(A.c, 0, sizeof(A.c)), memset(T.c, 0, sizeof(T.c)), memset(R.c, 0, sizeof(R.c));
	for (int i = 1, opt, w, x, y, z, a, b, c, d; i <= q; ++ i)
	{
		read(opt, w, x, y, z);
		a = (w + r) % n, b = (x + r) % n, c = (y + r) % n, d = (z + r) % n;
		if (b < a) std::swap(a, b);
		if (d < c) std::swap(c, d);
		++ b, ++ d;
		if (opt == 1) add(b, d, 1), add(a, c, 1), add(a, d, -1), add(b, c, -1);
		else
		{
			int ans = ((ask(b, d) + ask(a, c) - ask(a, d) - ask(b, c)) % mod + mod) % mod;
			r += ans, write(ans, '\n');
		}
	}
	IO::flush();
	return 0;
}
