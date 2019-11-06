#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e5 + 10, MaxM = 21, mod = 1e9 + 7;

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

int n, m;
namespace SGT
{
	ll sum[MaxN << 2][21], tag[MaxN << 2];
	inline void pushup(int x)
	{
		for (int i = 0; i <= m; ++ i) sum[x][i] = (sum[x << 1][i] + sum[x << 1 | 1][i]) % mod;
	}

	inline void build(int x, int l, int r)
	{
		tag[x] = 1;
		if (l == r) return ;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid);
		build(x << 1 | 1, mid + 1, r);
		pushup(x);
	}

	inline void Add(int x, int v)
	{
		for (int i = 0; i <= m; ++ i) (sum[x][i] *= v) %= mod;
		(tag[x] *= v) %= mod;
	}

	inline void pushdown(int x)
	{
		Add(x << 1, tag[x]), Add(x << 1 | 1, tag[x]);
		tag[x] = 1;
	}

	inline void Change(int x, int l, int r, int *v, int k)
	{
		if (l == r)
		{
			for (int i = 0; i <= m; ++ i) (sum[x][i] += v[i]) %= mod;
			return ;
		}
		if (tag[x] ^ 1) pushdown(x);
		int mid = (l + r) >> 1;
		if (k <= mid) Change(x << 1, l, mid, v, k);
		else Change(x << 1 | 1, mid + 1, r, v, k);
		pushup(x);
	}

	inline void Multiply(int x, int l, int r, int tl, int tr, int v)
	{
		if (tl <= l && r <= tr) return Add(x, v);
		if (tag[x] ^ 1) pushdown(x);
		int mid = (l + r) >> 1;
		if (tl <= mid) Multiply(x << 1, l, mid, tl, tr, v);
		if (tr > mid) Multiply(x << 1 | 1, mid + 1, r, tl, tr, v);
		pushup(x);
	}

	inline void Query(int x, int l, int r, int tl, int tr, int *v)
	{
		if (tl <= l && r <= tr)
		{
			for (int i = 0; i <= m; ++ i) (v[i] += sum[x][i]) %= mod;
			return ;
		}
		if (tag[x] ^ 1) pushdown(x);
		int mid = (l + r) >> 1;
		if (tl <= mid) Query(x << 1, l, mid, tl, tr, v);
		if (tr > mid) Query(x << 1 | 1, mid + 1, r, tl, tr, v);
	}
}

using SGT::build;
using SGT::Change;
using SGT::Multiply;
using SGT::Query;

int C[MaxM][MaxM], tmp[MaxM], adder[MaxM], a[MaxN];
int main()
{
	read(n, m);
	for (int i = 1; i <= n; ++ i) read(a[i]);
	for (int i = 0; i <= m; ++ i)
	{
		C[i][0] = 1;
		for (int j = 1; j <= i; ++ j) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}
	build(1, 1, n);
	tmp[0] = 1;
	Change(1, 1, n, tmp, 1);
	for (int i = 1; i <= n; ++ i)
	{
		for (int j = 0; j <= m; ++ j) tmp[j] = 0;
		Query(1, 1, n, 1, a[i], tmp);
		for (int j = 0; j <= m; ++ j)
		{
			ll v = 0;
			for (int k = 0; k <= j; ++ k) (v += 1ll * C[j][k] * tmp[k]) %= mod;
			adder[j] = v;
		}
		Change(1, 1, n, adder, a[i]);
		if (a[i] < n) Multiply(1, 1, n, a[i] + 1, n, 2);
	}
	for (int i = 0; i <= m; ++ i) tmp[i] = 0;
	Query(1, 1, n, 1, n, tmp);
	write(tmp[m], '\n', true);
	IO::flush();
	return 0;
}
