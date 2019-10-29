#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e3 + 10;

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

ll ans[MaxN * 10];
int len = 1;
std::map<int, int> vis;
inline void add(int x)//然后把所有约数乘起来，需要化成十六进制，像高精度那样，无奈
{
	if (vis[x]) return ;
	vis[x] = 1;
	for (int i = 1; i <= len; ++ i) ans[i] *= x;
	len += 10;
	for (int i = 1; i <= len; ++ i) ans[i + 1] += ans[i] / 16, ans[i] %= 16;
	while (!ans[len]) -- len;
}

inline void Appro(ll x)//处理约数
{
	for (ll i = 2; i * i <= x; ++ i) if (x % i == 0)
	{
		add(i);
		while (x % i == 0) x /= i;
	}
	if (x) add(x);
}

int main()//思路很巧啊，那个证明过程还得看看，再理解理解
{
	ans[1] = 1;
	int n; read(n);
	for (int i = 1, a, b; i <= n; ++ i)	read(a, b), b /= gcd(a, b),	Appro(b);
	for (int i = len; i >= 1; -- i)
		if (ans[i] <= 9) write(ans[i], ' ', false);
		else *IO::fe++ = ans[i] - 10 + 'A';
	IO::flush();
	return 0;
}
