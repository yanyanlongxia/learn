#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
typedef long double ld;
const int MaxN = 1e5 + 10;
const ll INF = 0x3f3f3f3ff3f3f3fll;

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

struct Orz{ll x, y;};
inline Orz operator - (Orz a, Orz b) { return (Orz){a.x - b.x, a.y - b.y}; }
inline bool operator < (Orz a, Orz b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
inline ld crs(Orz a, Orz b) {return (ld)a.x * b.y - (ld)a.y * b.x; }
inline ll gtw(Orz a, int k) { return a.x * k + a.y; }

int Stack[MaxN];
struct SGT1
{
	Orz p[MaxN];
	std::vector<int> h[MaxN << 2];
	inline void gthull(int x)
	{
		int top = 0;
		h[x].resize(h[x << 1].size() + h[x << 1 | 1].size());
		for (int i = 0, r1 = 0, r2 = 0; i < (int)h[x].size(); ++ i)
			if (r1 < h[x << 1].size() && (r2 >= h[x << 1 | 1].size() || p[h[x << 1][r1]] < p[h[x << 1 | 1][r2]])) h[x][i] = h[x << 1][r1 ++];
			else h[x][i] = h[x << 1 | 1][r2 ++];
		for (int i = 0; i < (int)h[x].size(); ++ i)
		{
			while (top > 1 && crs(p[h[x][i]] - p[Stack[top]], p[Stack[top]] - p[Stack[top - 1]]) >= 0) -- top;
			Stack[++ top] = h[x][i];
		}
		h[x].resize(top);
		for (int i = 0; i < (int)h[x].size(); ++ i) h[x][i] = Stack[i + 1];
	}

	inline void build(int x, int l, int r)
	{
		if (l == r)
		{
			h[x].resize(1);
			h[x][0] = l;
			return ;
		}
		int mid = (l + r) >> 1;
		build(x << 1, l, mid);
		build(x << 1 | 1, mid + 1, r);
		gthull(x);
	}

	inline ll ask(int x, int k)
	{
		int l = 0, r = h[x].size() - 1, lm, rm;
		while (l + 10 < r)
			if (gtw(p[h[x][lm = l + (r - l) / 3]], k) < gtw(p[h[x][rm = r - (r - l + 1) / 3]], k)) r = rm;
			else l = lm;
		ll ans = INF;
		for (int i = l; i <= r; ++ i) chkMin(ans, gtw(p[h[x][i]], k));
		return ans;
	}

	inline ll Query(int x, int l, int r, int tl, int tr, int k)
	{
		if (tl <= l && r <= tr) return ask(x, k);
		int mid = (l + r) >> 1;
		ll ans = INF;
		if (tl <= mid) chkMin(ans, Query(x << 1, l, mid, tl, tr, k));
		if (tr > mid) chkMin(ans, Query(x << 1 | 1, mid + 1, r, tl, tr, k));
		return ans;
	}
} T1, T2, T3, T4;

struct SGT2
{
	int Min[MaxN << 2];
	inline void build(int x, int l, int r, int *p)
	{
		if (l == r)
		{
			Min[x] = p[l];
			return ;
		}
		int mid = (l + r) >> 1;
		build(x << 1, l, mid, p);
		build(x << 1 | 1, mid + 1, r, p);
		Min[x] = min(Min[x << 1], Min[x << 1 | 1]);
	}

	inline ll Query(int x, int l, int r, int tl, int tr)
	{
		if (tl <= l && r <= tr) return Min[x];
		int mid = (l + r) >> 1;
		ll ans = INF;
		if (tl <= mid) chkMin(ans, Query(x << 1, l, mid, tl, tr));
		if (tr > mid) chkMin(ans, Query(x << 1 | 1, mid + 1, r, tl, tr));
		return ans;
	}
} T5, T6;

int n, m, q, a[MaxN], b[MaxN];//不要再在主函数中定义 n, m 了，不然蜜汁 RE
ll sa[MaxN], sb[MaxN];
inline void init()
{
	for (int i = 1; i < n; ++ i) read(a[i]), sa[i + 1] = sa[i] + a[i];
	for (int i = 1; i < m; ++ i) read(b[i]), sb[i + 1] = sb[i] + b[i];

	for (int i = 1; i < n; ++ i) T1.p[i] = (Orz){a[i], 1ll * i * a[i] - sa[i]};
	T1.build(1, 1, n);
	for (int i = 1; i < m; ++ i) T2.p[i] = (Orz){b[i], 1ll * i * b[i] - sb[i]};
	T2.build(1, 1, m);
	for (int i = 1; i < n; ++ i) T3.p[i] = (Orz){a[i], -1ll * i * a[i] + sa[i]};
	T3.build(1, 1, n);
	for (int i = 1; i < m; ++ i) T4.p[i] = (Orz){b[i], -1ll * i * b[i] + sb[i]};
	T4.build(1, 1, m);
	T5.build(1, 1, n, a), T6.build(1, 1, m, b);
}

inline ll solve(int sx, int sy, int tx, int ty)
{
	ll s = sa[tx] - sa[sx] + sb[ty] - sb[sy], Min = INF;
	int x = tx - sx, y = ty - sy, t = std::abs(x - y) >> 1;
	if (!t || n == 1 || m == 1) return s;
	if (x < y)
	{
		if (sx < tx) chkMin(Min, T5.Query(1, 1, n, sx, tx - 1) * t);
		if (sx > 1) chkMin(Min, T1.Query(1, 1, n, max(sx - t, 1), sx - 1, t - sx) + sa[sx]);
		if (tx < n) chkMin(Min, T3.Query(1, 1, n, tx, min(tx + t, n - 1), tx + t) - sa[tx]);
	}
	else
	{
		if (sy < ty) chkMin(Min, T6.Query(1, 1, m, sy, ty - 1) * t);
		if (sy > 1) chkMin(Min, T2.Query(1, 1, m, max(sy - t, 1), sy - 1, t - sy) + sb[sy]);
		if (ty < m) chkMin(Min, T4.Query(1, 1, m, ty, min(ty + t, m - 1), ty + t) - sb[ty]);
	}
	return (Min << 1) + s;
}

int main()
{
	read(n, m, q);
	init();
	for (int i = 1, sx, sy, tx, ty; i <= q; ++ i) read(sx, sy,tx, ty), write(solve(sx, sy, tx, ty), '\n', true);
	IO::flush();
	return 0;
}
