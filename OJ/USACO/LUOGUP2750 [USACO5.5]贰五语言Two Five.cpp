#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

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

int vis[30], f[7][7][7][7][7];
inline bool ok(int x, int num)
{
	return !vis[x] || vis[x] == num;//即该位置是否有限制，或者说必须选 num 这个字母
}

inline int dfs(int a, int b, int c, int d, int e, int x)
{
	if (x == 26) return 1;
	int &ans = f[a - 1][b - 1][c - 1][d - 1][e - 1];
	if (ans) return ans;
	if (a <= 5 && ok(a, x)) ans += dfs(a + 1, b, c, d, e, x + 1);//加上字符串小的数量
	if (b < a && ok(b + 5, x)) ans += dfs(a, b + 1, c, d, e, x + 1);//必须前面要有a个字母才行
	if (c < b && ok(c + 10, x)) ans += dfs(a, b, c + 1, d, e, x + 1);
	if (d < c && ok(d + 15, x)) ans += dfs(a, b, c, d + 1, e, x + 1);
	if (e < d && ok(e + 20, x)) ans += dfs(a, b, c, d, e + 1, x + 1);
	return ans;
}

int main()
{
	char opt, s[27];
	scanf("%c", &opt);
	if (opt == 'N')
	{
		int n; read(n);
		for (int i = 1; i <= 25; ++ i)//枚举每一个位置
			for (vis[i] = 1; vis[i] < 25; ++ vis[i])//枚举该位置上应该选什么字母
			{
				memset(f, 0, sizeof(f));
				int tmp = dfs(1, 1, 1, 1, 1, 1);
				if (tmp >= n) break;//如果大于等于了就说明这个位置必须选什么字符，然后不断逼近
				n -= tmp;//减去该个字符在这个位置的方案
			}
		for (int i = 1; i <= 25; ++ i) *IO::fe++ = vis[i] - 1 + 'A';
	}
	else
	{
		int ans = 0;
		scanf("%s", s + 1);
		for (int i = 1; i <= 25; ++ i)
			for (vis[i] = 1; vis[i] < s[i] - 'A' + 1; ++ vis[i])//在前面的方案不能大于当前字符串
			{
				memset(f, 0, sizeof(f));
				ans += dfs(1, 1, 1, 1, 1, 1);//加上这个方案的值
			}
		write(ans + 1, '\n', false);
	}
	IO::flush();
	return 0;
}
