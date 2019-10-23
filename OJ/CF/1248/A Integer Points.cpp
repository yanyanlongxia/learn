#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e5 + 10;

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

int a[MaxN], b[MaxN];//思路清奇，本来以为是计算几何，想着这怎么写啊？
int main()//然后心情极烦，点开了题解，估计智商问题，实在想不到；看完了第一行，我就懵逼了，原来是这样
{
	int Q; read(Q);//联立直线方程，得出 2x = b - a，x 是整数，所以 a,b 奇偶性必须相同，小学知识可证，嘻嘻
	while (Q --)//所以这是一道 sb 题？算了，对于我这种低智商选手，估计是道松命题
	{
		int n, a1 = 0, a0 = 0; read(n);
		for (int i = 1; i <= n; ++ i) read(a[i]), (a[i] & 1) ? ++ a1 : ++ a0;
		int m, b1 = 0, b0 = 0; read(m);
		for (int i = 1; i <= m; ++ i) read(b[i]), (b[i] & 1) ? ++ b1 : ++ b0;
		write(1ll * a1 * b1 + 1ll * a0 * b0, '\n', true);
	}
	IO::flush();
	return 0;
}
