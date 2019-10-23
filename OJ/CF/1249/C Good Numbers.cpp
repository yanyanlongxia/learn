#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e2 + 10;

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

int a[MaxN];
int main()
{
	int Q; read(Q);
	while (Q --)
	{
		ll n; read(n);
		memset(a, 0, sizeof(a));
		int len = 0;
		while (n) a[len ++] = n % 3, n /= 3;
		for (int i = 60; i >= 0; -- i) if (a[i] == 2)
        	{
			a[i] = 0;
            		int res = 1;
           		for (int j = i + 1; j <= 60; ++ j)
			{
                		a[j] += res, res = 0;
				if (a[j] == 2) a[j] = 0, res = 1;
            		}
            		for (int j = i - 1; j >= 0; -- j) a[j] = 0;
        	}
        	ll ans = 0, mul = 1;
		for (int i = 0; i <= 60; ++ i)
		{
			if (a[i] == 1) ans += mul;
			mul *= 3;
		}
		write(ans, '\n', true);
	}
	IO::flush();
	return 0;
}
