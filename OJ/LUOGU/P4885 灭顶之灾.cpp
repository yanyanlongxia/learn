#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e6 + 10;

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

struct Orz
{
	ll x; int y;
	inline bool operator < (const Orz &a) const
	{
		return x < a.x;
	}
} o[MaxN];

ll cnt;
inline ll check()
{
	ll sum = 0, tl = -2, tg = 0, k = 0, i = 1;
	while (i <= cnt)
	{
		if (tg <= 0) sum += o[i].x - 1 - tl, k = tl;
		tl = o[i].x;
		while (i <= cnt && o[i].x == tl) tg += o[i].y, ++ i;
	}
	if (!sum) { puts("Impossible!"); exit(0); }
	else if (sum > 1) { puts("Uncertain!"); exit(0); }
	else return k + 1;
}

int main()//题解：https://www.luogu.org/blog/fusu2333/solution-p4885
{
	ll n, m, s, q; read(n, m, s, q);
	ll ans = 0, l1 = 0, r1 = m - 1;
	__int128 uc = (n - 1), top = 0; uc *= m;
	while (s --)
	{
		ll a, b; read(a, b);
		if (1.0 * b / n > 1.0 * m) { puts("Impossible!"); exit(0); }
		a %= m;
		ll tl = ((1ll - a) % m + m) % m, tr = ((m - b) % m + m) % m;
		if (tl <= tr) chkMax(l1, tl), chkMin(r1, tr);
		else o[++ cnt] = (Orz){tr + 1, 1}, o[++ cnt] = (Orz){tl - 1, -1};
		top = b;
		if (top > uc) o[++ cnt] = (Orz){m - (int)(top - uc) + 1, 1}, o[++ cnt] = (Orz){m + 1, -1};
	}
	o[++ cnt] = (Orz){-1, 1}, o[++ cnt] = (Orz){l1 - 1, -1}, o[++ cnt] = (Orz){r1 + 1, 1}, o[++ cnt] = (Orz){m + 1, -1};
	std::sort(o + 1, o + cnt + 1);
	ll k = check();
	while (q --)
	{
		ll a; read(a), a += k;
		if (1.0 * a / n > 1.0 * m) continue;
		ll tmp = (a - 1) / m + 1; ans ^= tmp;
		tmp = (a - 1) % m + 1, ans ^= tmp;
	}
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
