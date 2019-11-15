#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e6 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3fll;

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

ll lim[MaxN];
struct SGT
{
	ll t[MaxN << 2], tag[MaxN << 2];
	inline void pushup(int x)
	{
		t[x] = min(t[x << 1], t[x << 1 | 1]);
	}

	inline void build(int x, int l, int r)
	{
		if (l == r)
		{
			t[x] = lim[l];
			return ;
		}
		int mid = (l + r) >> 1;
		build(x << 1, l, mid);
		build(x << 1 | 1, mid + 1, r);
		pushup(x);
	}

	inline void pushdown(int x)
	{
		t[x << 1] += tag[x], t[x << 1 | 1] += tag[x];
		tag[x << 1] += tag[x], tag[x << 1 | 1] += tag[x];
		tag[x] = 0;
	}

	inline void Change(int x, int l, int r, int tl, int tr, int v)
	{
		if (tl <= l && r <= tr)
		{
			t[x] += v, tag[x] += v;
			return ;
		}
		if (tag[x]) pushdown(x);
		int mid = (l + r) >> 1;
		if (tl <= mid) Change(x << 1, l, mid, tl, tr, v);
		if (tr > mid) Change(x << 1 | 1, mid + 1, r, tl, tr, v);
		pushup(x);
	}

	inline ll Query(int x, int l, int r, int tl, int tr)
	{
		if (tl <= l && r <= tr) return t[x];
		if (tag[x]) pushdown(x);
		int mid = (l + r) >> 1;
		ll ans = INF;
		if (tl <= mid) chkMin(ans, Query(x << 1, l, mid, tl, tr));
		if (tr > mid) chkMin(ans, Query(x << 1 | 1, mid + 1, r, tl, tr));
		return ans;
	}
} sgt;

ll a[MaxN], w[MaxN], suf[MaxN];
int pos[MaxN], Stack[MaxN], top;
int main()
{
	int n, k; read(n, k);
	ll ans = 0;
	for (int i = 1; i <= n; ++ i) read(a[i]), a[i] += 1ll * i * k;
	for (int i = 1; i <= n; ++ i) read(w[i]), ans += (-1ll * i * k) * w[i];
	for (int i = 1; i <= n; ++ i)
	{
		while (top && a[Stack[top]] >= a[i]) -- top;
		Stack[++ top] = i;
	}
	for (int i = 1; i <= top; ++ i)
		for (int j = Stack[i - 1] + 1; j <= Stack[i]; ++ j) lim[j] = a[Stack[i]];
	for (int i = n; i >= 1; -- i) suf[i] = suf[i + 1] + w[i], pos[i] = i;
	std::sort(pos + 1, pos + 1 + n, [](int a, int b)
	{
		return suf[a] > suf[b];
	});
	sgt.build(1, 1, n);
	for (int i = 1; i <= n; ++ i)
	{
		if (suf[pos[i]] <= 0) continue;
		int x = min(sgt.Query(1, 1, n, pos[i], n), 2ll * k);
		ans += suf[pos[i]] * x;
		sgt.Change(1, 1, n, pos[i], n, -x);
	}
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
