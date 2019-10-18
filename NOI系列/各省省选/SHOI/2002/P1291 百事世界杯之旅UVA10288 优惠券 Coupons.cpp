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

template <typename T> inline T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }

inline int cal(ll x)
{
	int len = 0;
	while (x) x /= 10, ++ len;
	return len;
}

int main()//如果手里已经有了 k 种 那么买到另外一种的概率就是 1 / (n - k) ，就需要买 n * (1 / n - k) 次
{//所以一共就要买 n * ( 1 / 1 + 1 / 2 + ...+ 1 / (n - 1) + 1 / n) 次
//    int n; read(n);
	int n;
	while (~scanf("%d", &n))
	{
		ll p = n, q = 1;//p 分子，q 分母
	    for (int i = 2; i <= n; ++ i)//处理分子分母，及时约分
	    {
	        ll fm = q * i, fz = p * i + n * q, k = gcd(fz, fm);
	        q = fm / k, p = fz / k;
	    }
	    ll r = p / q, len = cal(r);
	    if (q == 1) write(p, '\n');
	    else
	    {
	    	for (ll i = len + 1; i >= 1; -- i) *IO::fe++ = ' ';//这里也是多个空格
	    	write(p % q, '\n');
	    	if (r > 0) write(r, ' ');//UVA 这里有个空格，而 SHOI 里没有
	        for (ll i = cal(q); i >= 1; -- i) *IO::fe++ = '-';
	        *IO::fe++ = '\n';
	        for (ll i = len + 1; i >= 1; -- i) *IO::fe++ = ' ';//这里也是多个空格
	        write(q, '\n');
	    }
	}
    IO::flush();
    return 0;
}
