#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 60, mod = 1e9 + 7;

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

char s1[MaxN], s2[MaxN];
std::unordered_map<ll, int> f[2];
int main()
{
	scanf("%s", s1 + 1);
	scanf("%s", s2 + 1);
	int n = strlen(s1 + 1);
	int m = strlen(s2 + 1);
	f[0][1] = 1;
	for (int i = 0; i < n + m; ++ i)
	{
		int t1 = i & 1, t2 = t1 ^ 1, st = max(0, i - n), ed = min(i, m);
		f[t2].clear();
		for (std::unordered_map<ll, int>::iterator it = f[t1].begin(); it != f[t1].end(); ++ it)
		{
			ll state = it -> first, m0 = 0, m1 = 0;
			int w = it -> second;
			for (int j = st; j <= ed; ++ j) if ((state >> j) & 1)
			{
				if (i - j < n)
				{
					if (s1[i - j + 1] == '0') m0 |= 1ll << j;
					else m1 |= 1ll << j;
				}
				if (j < m)
				{
					if (s2[j + 1] == '0') m0 |= 1ll << (j + 1);
					else m1 |= 1ll << (j + 1);
				}
			}
			if (m0) (f[t2][m0] += w) %= mod;
			if (m1) (f[t2][m1] += w) %= mod;
		}
	}
	int t = (n + m) & 1, ans = 0;
	for (std::unordered_map<ll, int>::iterator it = f[t].begin(); it != f[t].end(); ++ it) (ans += it -> second) %= mod;
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
