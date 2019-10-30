#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;

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

template <typename T> inline T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }

int main()//ans=\frac{(a+k)(b+k)}{gcd(a+k,a−b)}
{
	int a, b, maxk = 0; read(a, b);
	ll res = 1e18;
	if (a < b) std::swap(a, b);
	for (int k = 1; k * k <= a - b; ++ k)//枚举 q，规定 q | gcd(a + k , a - b)，则 q | (a - b)
		if ((a - b) % k == 0)//那么 a + k, b + k 就应该是\geq a,\geq b 的数中 q 的倍数中的最小的那个
		{
			int a1 = (a + k - 1) / k * k, b1 = (b + k - 1) / k * k;//然后再对答案取个min就可以了
			if (chkMin(res, (ll)a1 / gcd(a1, b1) * b1)) maxk = a1 - a;
			if (k * k < a - b)
			{
				int kk = (a - b) / k;
				a1 = (a + kk - 1) / kk * kk, b1 = (b + kk - 1) / kk * kk;
				if (chkMin(res, (ll)a1 / gcd(a1, b1) * b1)) maxk = a1 - a;
			}
		}
	write(maxk, '\n', true);
	IO::flush();
	return 0;
}
