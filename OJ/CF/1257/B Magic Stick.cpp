#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 3e5 + 10;

namespace IO
{
	#define Grt ch = getchar()
	char buf[1 << 15], *fs, *ft;
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

	char Out[1 << 24], *fe = Out;
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

int main()
{
	int T; read(T);
	while (T --)
	{
		ll x, y; read(x, y);
		if (x >= y) { puts("YES"); continue; }//分类讨论一波，x \geqslant y 时，仅凭借 a - 1 就可以
		bool flag = true;//x \leqslant y 时
		if (x == 1) flag = false;//明显 x = 1 时什么也干不了
		else if (x <= 3 && y > 3) flag = false;//这里 x \in (1, 3]，x = 2 时，只能变成 3，就不能操作了；x = 3，不能操作
		puts(flag ? "YES" : "NO");//所以此时如果 y \geq 3，就失败。其他的一定是可以成功的，yy 一下好了，不用证明
	}
	return 0;
}
