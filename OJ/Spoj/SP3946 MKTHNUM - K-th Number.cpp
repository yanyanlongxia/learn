#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 2e5 + 10;

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

namespace SGT
{
	struct Orz{int l, r, z;} c[MaxN << 5]; int cnt = 0;
	inline void build(int &x, int l, int r)
	{
		if (!x) x = ++ cnt;//动态开点
		if (l == r) return ;
		int mid = (l + r) >> 1;
		build(c[x].l, l, mid);
		build(c[x].r, mid + 1, r);
	}

	inline int Change(int o, int l, int r, int k)
	{
		int x = ++ cnt;
		c[x].z = c[o].z + 1, c[x].l = c[o].l, c[x].r = c[o].r;//开一个新节点，主席树基本操作
		if (l == r) return x;
		int mid = (l + r) >> 1;
		if (k <= mid) c[x].l = Change(c[x].l, l, mid, k);
		else c[x].r = Change(c[x].r, mid + 1, r, k);
		return x;
	}

	inline int Query(int x, int y, int l, int r, int k)
	{
		if (l == r) return l;
		int mid = (l + r) >> 1, v = c[c[y].l].z - c[c[x].l].z, ans = 0;
		if (v >= k) ans = Query(c[x].l, c[y].l, l, mid, k);//树上二分
		else ans = Query(c[x].r, c[y].r, mid + 1, r, k - v);
		return ans;
	}
}

using SGT::build;
using SGT::Change;
using SGT::Query;

int a[MaxN], b[MaxN], rt[MaxN << 5];
int main()//本题模型：区间第 k 小，属于一道主席树模板题目，拿来练练手
{
	int n, m; read(n, m);
	for (int i = 1; i <= n; ++ i) read(a[i]), b[i] = a[i];
	std::sort(b + 1, b + n + 1);
	int tot = std::unique(b + 1, b + n + 1) - b - 1;//数据过大，但又只在意他们的相对关系，所以离散化
	build(rt[0], 1, tot);//下面就基本上是套路了
	for (int i = 1, k; i <= n; ++ i) k = std::lower_bound(b + 1, b + tot + 1, a[i]) - b, rt[i] = Change(rt[i - 1], 1, tot, k);
	while (m --)
	{
		int l, r, k; read(l, r, k);
		int ans = Query(rt[l - 1], rt[r], 1, tot, k);
		write(b[ans], '\n');
	}
	IO::flush();
	return 0;
}
