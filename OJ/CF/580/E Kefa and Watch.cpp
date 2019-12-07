#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
typedef unsigned long long ull;
const int b = 17, MaxN = 1e5 + 10, mod = 1e9 + 9;

namespace IO
{
	#define Grt ch = getchar()
	char buf[1 << 15], *fs, *ft;
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

	char Out[1 << 24], *fe = Out;
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

char s[MaxN];
ull Pow[MaxN], Pow2[MaxN];
struct Orz{int l, r, tag; ull sum;} tr[MaxN * 6];
inline void pushup(int x)
{
	tr[x].sum = ((tr[x << 1].sum * Pow[tr[x << 1 | 1].r - tr[x << 1 | 1].l + 1] + tr[x << 1 | 1].sum) % mod + mod) % mod;
}

inline void pushdown(int x)
{
	tr[x << 1].tag = tr[x << 1 | 1].tag = tr[x].tag;
	tr[x << 1].sum = Pow2[tr[x << 1].r - tr[x << 1].l] * tr[x].tag % mod;
	tr[x << 1 | 1].sum = Pow2[tr[x << 1 | 1].r - tr[x << 1 | 1].l] * tr[x].tag % mod;
	tr[x].tag = -1;
}

inline void build(int x, int l, int r)
{
	tr[x].l = l, tr[x].r = r, tr[x].tag = -1;
	if (l == r)
	{
		tr[x].sum = s[l] - '0' + 1;
		return ;
	}
	int mid = (l + r) >> 1;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
	pushup(x);
}

inline void Change(int x, int l, int r, int k)
{
	if (l == tr[x].l && tr[x].r == r)
	{
		tr[x].tag = k, tr[x].sum = Pow2[tr[x].r - tr[x].l] * k % mod;
		return ;
	}
	if (tr[x].tag != -1) pushdown(x);
	int mid = (tr[x].l + tr[x].r) >> 1;
	if (r <= mid) Change(x << 1, l, r, k);
	else if (l > mid) Change(x << 1 | 1, l, r, k);
	else Change(x << 1, l, mid, k), Change(x << 1 | 1, mid + 1, r, k);
	pushup(x);
}

inline ull Query(int x, int l, int r)
{
	if (l > r) return 0;
	if (l == tr[x].l && tr[x].r == r) return tr[x].sum;
	if (tr[x].tag != -1) pushdown(x);
	int mid = (tr[x].l + tr[x].r) >> 1;
	if (r <= mid) return Query(x << 1, l, r);
	else if (l > mid) return Query(x << 1 | 1, l, r);
	else return (Query(x << 1, l, mid) * Pow[r - mid] + Query(x << 1 | 1, mid + 1, r)) % mod;
}

int main()//https://www.luogu.com.cn/blog/xiaozhusheng/solution-cf580e
{
	int n, m, k; read(n, m, k), m += k;
	scanf("%s", s + 1);
	Pow[0] = Pow2[0] = 1;
	for (int i = 1; i <= n; ++ i) Pow[i] = Pow[i - 1] * b % mod, Pow2[i] = (Pow2[i - 1] * b + 1) % mod;
	build(1, 1, n);
	for (int i = 1, opt, l, r, k; i <= m; ++ i)
	{
		read(opt, l, r, k);
		if (opt == 1) Change(1, l, r, k + 1);
		else puts(Query(1, l, r - k) == Query(1, l + k, r) ? "YES" : "NO");
	}
	return 0;
}
