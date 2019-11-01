#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e5 + 10, MaxM = MaxN * 20, inf = 0x3f3f3f3f;

namespace IO
{
	#define Grt ch = getc()
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

int rt[MaxN], Stack[MaxM], top, n, m, f;
struct BIT
{
	int c[MaxN];
	inline int lowbit(int x) { return x & -x; }
	inline void add(int x, int k) { while (x <= n) c[x] += k, x += lowbit(x); }
	inline int ask(int x) { int ans = 0; while (x) ans += c[x], x -= lowbit(x); return ans; }
	inline void upd(int l, int r, int k) { add(l, k), add(r + 1, -k); }
} L, R, C;

namespace SGT
{
	inline void delNode(int &x)
	{
		Stack[++ top] = x;
		x = 0;
	}

	inline int newNode()
	{
		return Stack[top --];
	}

	struct Orz{int l, r, Mx, Mn;} c[MaxM];
	inline void pushup(int x)
	{
		c[x].Mx = -inf, c[x].Mn = inf;
		if (c[x].l) chkMax(c[x].Mx, c[c[x].l].Mx), chkMin(c[x].Mn, c[c[x].l].Mn);
		if (c[x].r) chkMax(c[x].Mx, c[c[x].r].Mx), chkMin(c[x].Mn, c[c[x].r].Mn);
	}

	inline void add(int &x, int l, int r, int tl, int tr)
	{
		if (!x) x = newNode();
		if (tl <= l && r <= tr)
		{
			c[x].Mx = r, c[x].Mn = l;
			return ;
		}
		int mid = (l + r) >> 1;
		if (tl <= mid) add(c[x].l, l, mid, tl, tr);
		if (tr > mid) add(c[x].r, mid + 1, r, tl, tr);
		pushup(x);
	}

	inline void del(int &x, int l, int r, int tl, int tr)
	{
		if (tl <= l && r <= tr) return delNode(x);
		int mid = (l + r) >> 1;
		if (tl <= mid) del(c[x].l, l, mid, tl, tr);
		if (tr > mid) del(c[x].r, mid + 1, r, tl, tr);
		pushup(x);
		if (c[x].Mx < 0) delNode(x);
	}

	inline int Query(int x, int y)
	{
		if (!x || !y) return inf;
		if (x == y) return 0;
		int ans = inf;
		if (c[x].l && c[y].r) chkMin(ans, c[c[y].r].Mn - c[c[x].l].Mx);
		if (ans == 1) return ans;
		if (c[x].r && c[y].l) chkMin(ans, c[c[x].r].Mn - c[c[y].l].Mx);
		if (ans == 1) return ans;
		chkMin(ans, Query(c[x].l, c[y].l));
		if (ans == 1) return ans;
		chkMin(ans, Query(c[x].r, c[y].r));
		return ans;
	}

	inline void Change(int l, int r, int x)
	{
		for (int p = l, tl, tr, tc, nxt; p <= r; p = nxt + 1)
		{
			tl = L.ask(p), tr = R.ask(p), tc = C.ask(p);
			nxt = min(tr, r);
			del(rt[tc], 1, n, tl, tr);
			if (tl ^ p)
			{
				add(rt[tc], 1, n, tl, p - 1);
				R.upd(tl, p - 1, p - 1 - tr);
			}
			if (nxt ^ tr)
			{
				add(rt[tc], 1, n, nxt + 1, tr);
				L.upd(nxt + 1, tr, nxt + 1 - tl);
			}
			L.upd(p, nxt, l - tl), R.upd(p, nxt, r - tr), C.upd(p, nxt, x - tc);
		}
		add(rt[x], 1, n, l, r);
	}
}

using SGT::add;
using SGT::Query;
using SGT::Change;

int a[MaxN];
int main()
{
	read(n, m, f);
	for (int i = 1; i <= n; ++ i) read(a[i]);
	for (int i = 1; i <= MaxM - 5; ++ i) Stack[i] = i;
	top = MaxM - 5;
	for (int i = 1; i <= n; ++ i)
	{
		int j = i;
		while (j < n && a[j + 1] == a[i]) ++ j;
		L.upd(i, j, i), R.upd(i, j, j), C.upd(i, j, a[i]);
		add(rt[a[i]], 1, n, i, j);
		i = j;
	}
	int lastans = 0;
	for (int i = 1, opt, x, y, l, r; i <= m; ++ i)
	{
		read(opt);
		if (opt == 1)
		{
			read(l, r, x);
			if (f == 1 && lastans != -1) l ^= lastans, r ^= lastans, x ^= lastans;
			Change(l, r, x);
		}
		else
		{
			read(x, y);
			if (f == 1 && lastans != -1) x ^= lastans, y ^= lastans;
			lastans = Query(rt[x], rt[y]);
			if (lastans == inf) lastans = -1;
			write(lastans, '\n', true);
		}
	}
	IO::flush();
	return 0;
}
