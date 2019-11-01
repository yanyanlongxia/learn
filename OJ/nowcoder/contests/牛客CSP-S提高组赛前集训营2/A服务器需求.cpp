#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 4e5 + 10;

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

int a[MaxN];
std::multiset<int> s;
int main()//现在想想，当时真是傻，这么简单的结论，要么是最大的 a[i]，要么是平均值，这很显然，所以加上的 m 天可以不连续就是必要的，如果没有这句话，才会牵扯更多的东西
{//但是毕竟不能每次修改一个东西就 sort 吧，所以就要借助一个可以自动排序的 stl ，比如说 priority_queue，multiset之类的，此题完结
	int n, m, q; read(n, m, q);
	ll sum = 0;
	for (int i = 1; i <= n; ++ i) read(a[i]), sum += a[i], s.insert(a[i]);
	write(max((sum + m - 1) / m, (ll)*--s.end()), '\n', true);
	while (q --)
	{
		int x, y; read(x, y);
		s.erase(s.find(a[x])), sum -= a[x], a[x] = y;
		s.insert(a[x]), sum += a[x];
		write(max((sum + m - 1) / m, (ll)*--s.end()), '\n', true);
	}
	IO::flush();
	return 0;
}
