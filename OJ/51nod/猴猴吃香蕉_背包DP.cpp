#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int mod = 1e9 + 7;

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
		if (!x) *fe ++ = 48;
		if (x < 0) *fe ++ = '-', x = -x;
		T num = 0, ch[20];
		while (x) ch[++ num] = x % 10 + 48, x /= 10;
		while (num) *fe ++ = ch[num --];
		if (fl) *fe ++ = str;
	}
}

using IO::read;
using IO::write;

template <typename T> inline bool chkMin(T &a, const T &b) { return a > b ? (a = b, true) : false; }
template <typename T> inline bool chkMax(T &a, const T &b) { return a < b ? (a = b, true) : false; }
template <typename T> inline T min(T a, T b) { return a < b ? a : b; }
template <typename T> inline T max(T a, T b) { return a > b ? a : b; }

std::map<int, int> f;
std::map<int, int>::reverse_iterator it;//实现时可以用 map，倒序遍历体积时可用 STL 的反向迭代器 reverse_iterator
int main()//设 f[i][j] 选完第 i 个物品时，乘积为 j 的方案数
{
	int T; read(T);
	while (T --)
	{
		f.clear();
		int n, k; read(n, k);
		for (int i = 1; i * i <= k; ++ i)//然后可以发现能组成 k 的数一定是 k 的约数，所以这个背包的体积就是 k 的约数这个集合，这样就可以避免碰 k 导致 TLE 了，这是本题最关键的一点
			if (k % i == 0) f[i] = f[k / i] = 0;
		f[1] = 1;
		for (int i = 1, x; i <= n; ++ i)
		{
			read(x);
			if (k % x) continue;
			for (it = f.rbegin(); it != f.rend(); ++ it)
				if (it -> first >= x && it -> first % x == 0) it -> second = (it -> second + f[it -> first / x]) % mod;
		}
		write(f[k], '\n', true);
	}
	IO::flush();
	return 0;
}

/*
3
3 3
1 1 3
3 6
2 3 6
3 5
1 5 1

4
2
4
*/
