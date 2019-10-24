#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e5 + 10;

namespace IO
{
	#define G ch = getchar()
	char buf[1<<15], *fs, *ft;
	inline char getc() { return ft == fs && (ft = (fs = buf) + fread(buf, 1, 1 << 15, stdin), ft == fs) ? 0 : *fs ++; }
	template <typename T> inline void read(T &x)
	{
		x = 0;
		T f = 1, G;
		while (!isdigit(ch) && ch ^ '-') G;
		if (ch == '-') f = -1, G;
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), G;
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

namespace SGT
{
	int tag[MaxN << 2]; ll t[MaxN << 2][21];//t[x][i] 代表当前节点 x，二进制位 i 上是 1 的数有多少个
	inline void build(int x, int l, int r)//为什么只需要开 20 位，以为 2^20 > 10^6
	{
		if (l == r)
		{
			int a; read(a);
			for (int i = 20; i >= 0; -- i)
				if ((a >> i) & 1) ++ t[x][i];//因为异或不具有叠加性，所以利用二进制拆位
			return ;
		}
		int mid = (l + r) >> 1;
		build(x << 1, l, mid);
		build(x << 1 | 1, mid + 1, r);
		for (int i = 20; i >= 0; -- i) t[x][i] = t[x << 1][i] + t[x << 1 | 1][i];
	}

	inline void pushdown(int x, int l, int r)
	{
		tag[x << 1] ^= tag[x], tag[x << 1 | 1] ^= tag[x];
		int mid = (l + r) >> 1;
		for (int i = 20; i >= 0; -- i)
			if ((tag[x] >> i) & 1) t[x << 1][i] = mid - l + 1 - t[x << 1][i], t[x << 1 | 1][i] = r - mid - t[x << 1 | 1][i];
		tag[x] = 0;
	}

	inline void Change(int x, int l, int r, int tl, int tr, int k)
	{
		if (tl <= l && r <= tr)
		{
			tag[x] ^= k;
			for (int i = 20; i >= 0; -- i)
				if ((k >> i) & 1) t[x][i] = r - l + 1 - t[x][i];//如果某一二进制位上原来为 1 ，且当前异或的数 k，当前二进制位上也有 1
			return ;//那么当前 t[x][i]=r-l+1-t[x][i]，可以理解为 01 交换
		}
		if (tag[x]) pushdown(x, l, r);
		int mid = (l + r) >> 1;
		if (tl <= mid) Change(x << 1, l, mid, tl, tr, k);
		if (tr > mid) Change(x << 1 | 1, mid + 1, r, tl, tr, k);
		for (int i = 20; i >= 0; -- i) t[x][i] = t[x << 1][i] + t[x << 1 | 1][i];
	}

	inline ll Query(int x, int l, int r, int tl, int tr)
	{
		if (tl <= l && r <= tr)
		{
			ll ans = 0;
			for (int i = 20; i >= 0; -- i) ans += t[x][i] * (1 << i);
			return ans;
		}
		if (tag[x]) pushdown(x, l, r);
		int mid = (l + r) >> 1;
		ll ans = 0;
		if (tl <= mid) ans += Query(x << 1, l, mid, tl, tr);
		if (tr > mid) ans += Query(x << 1 | 1, mid + 1, r, tl, tr);
		return ans;
	}
}

using SGT::build;
using SGT::Change;
using SGT::Query;

int main()
{
	int n; read(n);
	build(1, 1, n);
	int m; read(m);
	for (int i = 1, opt, l, r, x; i <= m; ++ i)
	{
		read(opt, l, r);
		if (opt == 1) write(Query(1, 1, n, l, r), '\n', true);//求 sum[l,r]
		else read(x), Change(1, 1, n, l, r, x);//:对 [l,r] 中的所有数和 x 异或
	}
    IO::flush();
	return 0;
}
