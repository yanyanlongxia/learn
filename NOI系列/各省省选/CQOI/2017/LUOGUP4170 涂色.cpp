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

char s[MaxN];
int f[MaxN][MaxN];//设 f[l][r] 为字符串的子串 s[l]~s[r] 的最少染色次数
int main()
{
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= n; ++ i) f[i][i] = 1;//当 l == r 时，子串只需要涂色一次
	for (int len = 2; len <= n; ++ len)
		for (int l = 1; l + len - 1 <= n; ++ l)
		{
			int r = l + len - 1;
			if (s[l] == s[r]) f[l][r] = min(f[l + 1][r], f[l][r - 1]);//当 l ^ r 且 s[l] == s[r] 时，可以想到只需要在首次涂色时多涂一格即可
			else for (int k = l; k <= r; ++ k) chkMin(f[l][r], f[l][k] + f[k + 1][r]);//当 l ^ r 且 s[l] ^ s[r] 时，我们需要考虑将子串断成两部分来涂色，于是需要枚举子串的断点 k
		}
	write(f[1][n], '\n', true);
	IO::flush();
	return 0;
}
