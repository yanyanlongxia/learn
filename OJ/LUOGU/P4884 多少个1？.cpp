#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef __int128 ll;

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

inline ll Quick_Power(ll a, ll b, ll p)
{
	ll ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}

inline ll BSGS(ll a, ll b, ll p)//跟着 yyb 学 BSGS！
{
	std::map<ll, ll> M;
	M.clear();
	b %= p;
	ll t = (ll)std::sqrt((double)p) + 1;//m 有 10^11 这么大，大概率会爆 long long，所以开 __int128
	for (ll i = 0; i < t; ++ i)
	{
		ll val = b * Quick_Power(a, i, p) % p;
		M[val] = i;
	}
	a = Quick_Power(a, t, p);
	if (!a) return !b ? 1 : -1;
	for (ll i = 0; i <= t; ++ i)
	{
		ll val = Quick_Power(a, i, p);
		ll j = M.find(val) == M.end() ? -1 : M[val];
		if (j >= 0 && i * t >= j) return i * t - j;
	}
	return -1;
}

int main()//也没想到自己可以数论题目思路 AC 的：就是把 111...11 转化成 10^n - 1 / 9
{
	ll k, m; read(k, m);
	write(BSGS(10, (9 * k + 1) % m, m), '\n');//这样一来，根绝同余方程的可乘（加）性
	IO::flush();//同余方程两边是可以乘（加）上一个自然数的，所以式子变成了：10^n \equiv 9*k+1 (\mod m)
	return 0;//解高阶同余方程，m 是质数，所以套一个 BSGS 即可
}
