#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 60;

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

int a[MaxN], b[MaxN], sum[MaxN], f[MaxN][MaxN][2];
int main()
{
	int n, c; read(n, c);
	for (int i = 1; i <= n; ++ i) read(a[i], b[i]), sum[i] = sum[i - 1] + b[i];
	memset(f, 0x3f, sizeof(f));
	f[c][c][0] = f[c][c][1] = 0;//瞬间被关（初始化）
	for (int len = 2; len <= n; ++ len)//长度为 1 的区间不用管了
		for (int l = 1; l + len - 1 <= n; ++ l)
		{
			int r = l + len - 1;//要注意的一点是 sum[n]-(sum[j]-sum[i]) 是包括了i这一点的电能的，因为走过来的过程中灯 i 也会耗电
			f[l][r][0] = min(f[l + 1][r][0] + (a[l + 1] - a[l]) * (sum[l] + sum[n] - sum[r]),//继续走下去会更快吗？
							f[l + 1][r][1] + (a[r] - a[l]) * (sum[l] + sum[n] - sum[r]));//还是从 j 点折返回来会更快？（此时假设 [i+1,j] 被关，i 亮，从 j 端点往回赶去关 i ）
			f[l][r][1] = min(f[l][r - 1][0] + (a[r] - a[l]) * (sum[l - 1] + sum[n] - sum[r - 1]), f[l][r - 1][1] + (a[r] - a[r - 1]) * (sum[l - 1] + sum[n] - sum[r - 1]));//同上
		}
	write(min(f[1][n][0], f[1][n][1]), '\n', true);
	IO::flush();
	return 0;
}
