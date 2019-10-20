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
inline bool check(int l, int r)
{
    int mid = (l + r ) >> 1;
    for (int i = 1; i <= mid - l + 1 ; ++ i) if (s[l + i - 1] != s[mid + i]) return 0;
    return 1;
}

int f[MaxN][MaxN][2];
//f[l][r][1] 表示子串 [l,r]，压缩的第一个字符必须为 M，并且不再含有其它任何 M
//f[l][r][0] 表示子串 [l,r]，压缩的第一个字符必须为 M，且压缩串中 M 的个数必须大于 1
int main()//区间 Dp，与字符串折叠好相似
{
    scanf("%s",s + 1);
    int n = strlen(s + 1);
    for (int l = n; l >= 1; -- l)
		for (int r = l; r <= n; ++ r)
        {
            f[l][r][1] = f[l][r][0] = r - l + 1;
            for (int k = l; k < r; ++ k) chkMin(f[l][r][0], min(f[l][k][1], f[l][k][0]) + 1 + min(f[k + 1][r][0], f[k + 1][r][1]));
            for (int k = l; k < r; ++ k) chkMin(f[l][r][1], f[l][k][1] + r - k);//压缩串中仅含一个 M 的情况下，后缀 [k+1,r] 有可能不参加循环（后面没有任何一个R）。
            if ((r - l + 1) % 2 == 0 && check(l, r)) f[l][r][1] = f[l][(l + r) >> 1][1] + 1;//子串 [l,r] 可以拆分成两个相等的子串 [l,mid] 和 [mid+1,r] 的情况，这样转移避免了子串 [l,mid] 的压缩中 M 个数和位置的影响
        }
    write(min(f[1][n][0], f[1][n][1]), '\n', true);
    IO::flush();
    return 0;
}
