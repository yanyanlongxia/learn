#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e6 + 10, MaxK = 26;

namespace IO
{
	#define Grt ch = getchar()
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
	template <typename T> inline void write(T x, char str, bool fl)
	{
		if (!x) *fe++ = 48;
		if (x < 0) *fe++ = '-', x = -x;
		T sum = 0, ch[20];
		while (x) ch[++ sum] = x % 10 + 48, x /= 10;
		while (sum) *fe++ = ch[sum --];
		if (fl) *fe++ = str;
	}
}

using IO::read;
using IO::write;

template <typename T> inline bool chkMin(T &a, const T &b) { return a > b ? (a = b, true) : false; }
template <typename T> inline bool chkMax(T &a, const T &b) { return a < b ? (a = b, true) : false; }
template <typename T> inline T min(T a, T b) { return a < b ? a : b; }
template <typename T> inline T max(T a, T b) { return a > b ? a : b; }

int last[MaxK], p[MaxK][MaxK], Min[MaxK][MaxK], sum[MaxK];//last 表示字符最后出现的位置，p 表示更新维护最小值的位置
char s[MaxN];//Min 表示维护的最小值，sum 表示字符出现的次数
int main()
{
	int n, ans = 0; read(n);
	scanf("%s", s + 1);
	for (int i = 1, t; i <= n; ++ i)
	{
		t = s[i] - 'a', ++ sum[t], last[t] = i;
		for (int j = 0; j < MaxK; ++ j)
			if (j ^ t && sum[j]) chkMax(ans, max(sum[t] - sum[j] - Min[t][j]- (last[j] == p[t][j]),//这个判断：
								sum[j] - sum[t] - Min[j][t] - (last[t] == p[j][t])));//如果成立，那么那个点属于前一段区间
		for (int j = 0; j < MaxK; ++ j)
			if (sum[j] - sum[t] < Min[j][t]) Min[j][t] = sum[j] - sum[t], p[j][t] = i;//更新最小值
	}
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
