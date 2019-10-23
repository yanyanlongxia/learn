#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;

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

inline ll gcd(ll a, ll b)
{
	return b ? gcd(b, a % b) : a;
}

int main()//https://www.luogu.org/blog/user47136/solution-p3166
{
	ll n, m; read(n, m), ++ n, ++ m;//因为是一个网格，所以真正的坐标系其实有 (n + 1, m + 1)
    ll go = n * m, ans = go * (go - 1) * (go - 2) / 6 - n * m * (m - 1) * (m - 2) / 6 - m * n * (n - 1) * (n - 2) / 6;//记得除掉取出数列的全排列
    for (int i = 1; i < n; ++ i)//因为是取了原点，所以相当于坐标系是从 0 开始了
        for (int j = 1; j < m; ++ j) ans -= (ll)2 * (ll)(gcd(i, j) - 1) * (ll)(n - i) * (ll)(m - j);//枚举这个点，ans = 所有情况 - 平行坐标轴的三点共线 - 斜线三点共线
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
