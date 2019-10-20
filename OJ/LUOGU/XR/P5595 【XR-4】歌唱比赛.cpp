#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e6 + 10;

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

char s[MaxN];
int a[MaxN], b[MaxN];
int main()
{
	scanf("%s", s + 1);
	int n = strlen(s + 1); bool flag = 1;//构造题，所以就直接随便赋值了，满足情况即可
	for (int i = n; i >= 1; -- i)//倒序，因为当前位只对后面的位负责
		if (s[i] == 'X') flag = 0, a[i] = 1, b[i] = 0;// X：a[i] > b[i] 且 i~n 位都 a > b
		else if (s[i] == 'Y') flag = 0, b[i] = 1, a[i] = 0;// Y：a[i] < b[i] 且 i~n 位都 a < b
		else
		{
			if (!flag) { puts("-1"); exit(0); }
			a[i] = b[i] = 0;// Z：a[i] == b[i]，且 i~n 位都相等
		}
	for (int i = 1; i <= n; ++ i) write(a[i], '\n', i == n ? true : false);
	for (int i = 1; i <= n; ++ i) write(b[i], '\n', false);
	IO::flush();
	return 0;
}
