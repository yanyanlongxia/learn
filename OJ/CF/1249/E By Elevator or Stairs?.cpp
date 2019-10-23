#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 2e5 + 10;

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

int a[MaxN], b[MaxN];
int main()//没读懂题时不知道这题是个啥，现在一看是 1 楼到其他楼的最短时间，一种走楼梯，一种坐电梯（多加个 c），常规套路
{
	int n, c; read(n, c);
	for (int i = 1; i < n; ++ i) read(a[i]);
	for (int i = 1; i < n; ++ i) read(b[i]);
	int suma = 0, sumb = c;//到当前楼的时候，走楼梯的时间，坐电梯的时间
	for (int i = 1; i <= n; ++ i)
	{
		write(min(suma, sumb), ' ', true);//对于每一层来说，一定是选时间短的了
		int tmpa = suma, tmpb = sumb;
		suma = min(tmpa + a[i], tmpb + a[i]);//这一层走楼梯，但是不知道之前是怎么走的，所以取个 min
		sumb = min(tmpa + c + b[i], tmpb + b[i]);//开始坐电梯：之前没坐的话，现在要交 c ，之前已经是坐电梯了，就不用了
	}
	IO::flush();
	return 0;
}
