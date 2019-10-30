#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 5e2 + 10;

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

namespace SGT
{
	int Max[1 << 11], tag[1 << 11];//离散化后有2N
	inline void build(int x, int l, int r)
	{
		Max[x] = tag[x] = 0;
		if (l == r) return ;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid);
		build(x << 1 | 1, mid + 1, r);
	}

	inline void pushdown(int x)
	{
		Max[x << 1] += tag[x], Max[x << 1 | 1] += tag[x];
		tag[x << 1] += tag[x], tag[x << 1 | 1] += tag[x];
		tag[x] = 0;
	}

	inline void Change(int x, int l, int r, int tl, int tr, int v)
	{
		if (tl <= l && r <= tr)
		{
			Max[x] += v;
			tag[x] += v;
			return ;
		}
		if (tag[x]) pushdown(x);
		int mid = (l + r) >> 1;
		if (tl <= mid) Change(x << 1, l, mid, tl, tr, v);
		if (tr > mid) Change(x << 1 | 1, mid + 1, r, tl, tr, v);
		Max[x] = max(Max[x << 1], Max[x << 1 | 1]);
	}
}

using SGT::build;
using SGT::Change;

struct event
{
    int x, yl, yr, val;
    inline bool operator < (const event &a) const
    {
        return x < a.x;
    }
} e[MaxN << 1];

int y[MaxN << 1], X[MaxN], Y[MaxN];
int main()
{
	int c, n; read(c, n);
	for (int i = 1; i <= n; ++ i) read(X[i], Y[i]);
	int l = 1, r = 1e4, ans = 0;
	while (l <= r)
	{
		int mid = (l + r) >> 1, en = 0, yn = 0;
		for (int i = 1; i <= n; ++ i)
		{
			e[++ en].x = X[i] - mid + 1;
			y[++ yn] = e[en].yl = Y[i] - mid + 1;//以草场为右下角的正方形
			y[++ yn] = e[en].yr = Y[i];
			e[en].val = 1;
			e[++ en].x = X[i] + 1;
			e[en].yl = Y[i] - mid + 1;
			e[en].yr = Y[i];
			e[en].val = -1;
		}
		std::sort(e + 1, e + en + 1);
		std::sort(y + 1, y + yn + 1);
		build(1, 1, yn);
		int now = 0;
		for (int i = 1; i <= en;  ++ i)
		{
		    if (e[i].x != e[i - 1].x) chkMax(now, SGT::Max[1]);//同一个x都更新再更新答案
		    Change(1, 1, yn, std::lower_bound(y + 1, y + yn + 1, e[i].yl) - y, std::lower_bound(y + 1, y + yn + 1, e[i].yr) - y, e[i].val);
		}
		if (now >= c) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
