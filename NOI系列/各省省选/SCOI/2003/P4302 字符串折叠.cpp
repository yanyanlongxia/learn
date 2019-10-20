#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 110;

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
inline bool check(int l, int r, int len)//判断是否是循环节
{
	for (int i = l; i <= l + len - 1; ++ i)
		for (int j = i; j <= r; j += len)
			if (s[j] != s[i]) return false;
	return true;
}

int m[MaxN];//m[i] 表示的是 i 的位数
int f[MaxN][MaxN];//f[i][j] 表示 i 到 j 这个区间内最小的长度
int main()//注释直接粘别人的了，求原谅！
{
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	for (int i = 1; i <= 9; ++ i) m[i] = 1;
	for (int i = 10; i <= 99; ++ i) m[i] = 2;
	m[100] = 3, memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= n; ++ i) f[i][i] = 1;
	for (int len = 1; len <= n; ++ len)
		for (int l = 1; l + len - 1 <= n; ++ l)
		{
			int r = l + len - 1;
			for (int k = l; k < r; ++ k)//枚举哪里切
			{
				chkMin(f[l][r], f[l][k] + f[k + 1][r]);//第一种情况，左区间+右区间
				int t = k - l + 1;//第二种情况，先得到循环节的长度
				if (len % t) continue;//长度不符
				if (check(l, r, t)) chkMin(f[l][r], f[l][k] + 2 + m[len / t]);//是循环节，那么套公式
			}
		}
	write(f[1][n], '\n', true);
	IO::flush();
	return 0;
}
