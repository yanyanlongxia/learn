#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define Grt ch = getchar()
#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 5e3 + 10;

namespace IO
{
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

char s[MaxN];
int main()
{
	scanf("%s", s + 1);
	int T; read(T);
	int n = strlen(s + 1), x = 0, y = 0;
	for (int i = 1; i <= n; ++ i)//先处理一下这段命令可以走到哪里
		if (s[i] == 'E') ++ x;
		else if (s[i] == 'W') -- x;
		else if (s[i] == 'N') ++ y;
		else -- y;
	x *= (T / n), y *= (T / n);//乘一下有几段这样的命令
	for (int i = 1; i <= T % n; ++ i)//最后处理一下 (T % n) 的部分就好了
		if (s[i] == 'E') ++ x;
		else if (s[i] == 'W') -- x;
		else if (s[i] == 'N') ++ y;
		else -- y;
	write(x, ' '), write(y, '\n');
	IO::flush();
	return 0;
}
