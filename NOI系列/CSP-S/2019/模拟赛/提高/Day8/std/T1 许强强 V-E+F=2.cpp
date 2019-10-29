#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

#define mp std::make_pair
typedef std::pair<int, int> pii;
const int MaxN = 5e5 + 10;

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

struct E
{
	int a, b, c, d;
	inline E() {}
	inline E(int a_, int b_, int c_, int d_) : a(a_), b(b_), c(c_), d(d_)
	{
		if (a > c) std::swap(a, c);
		if (b > d) std::swap(b, d);
	}

	inline friend bool operator < (E a, E b)
	{
		if (a.a ^ b.a) return a.a < b.a;
		if (a.b ^ b.b) return a.b < b.b;
		if (a.c ^ b.c) return a.c < b.c;
		return a.d < b.d;
	}

	inline friend bool operator == (E a, E b)
	{
		return !(a < b) && !(b < a);
	}
} e[MaxN];
pii v[MaxN];
char s[MaxN];
int main()//欧拉公式：V-E+F=2
{
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	v[0] = mp(0, 0);
	for (int i = 1, x = 0, y = 0; i <= n; ++ i)
	{
		if (s[i] == 'L') -- x, e[i] = E(x, y, x + 1, y);
		else if (s[i] == 'R') ++ x, e[i] = E(x, y, x - 1, y);
		else if (s[i] == 'U') -- y, e[i] = E(x, y + 1, x, y);
		else if (s[i] == 'D') ++ y, e[i] = E(x, y - 1, x, y);//所以维护一个边集
		v[i] = mp(x, y);//一个点集
	}
	std::sort(v, v + n + 1);
	std::sort(e + 1, e + n + 1);
	int V = std::unique(v, v + n + 1) - v, E = std::unique(e + 1, e + n + 1) - e - 1;//然后搞一下去重
	write(2 - V + E, '\n', true);//根据公式
	IO::flush();
	return 0;
}
