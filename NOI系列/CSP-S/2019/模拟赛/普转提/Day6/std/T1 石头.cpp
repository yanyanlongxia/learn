#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e3 + 10, MaxW = 1e6 + 10, mod = 987654321;//这个模数很有意思

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

int a[MaxN], f[MaxN], n;
int prime[MaxW], sum[MaxN], cnt;
bool isnopr[MaxW];
inline void Pre()
{
	isnopr[1] = 1;//线性筛不要忘了把 1 给剔除掉
	for (int i = 2; i <= sum[n]; ++ i)//值域上界：1e6，很好想，只是写出来罢了
	{
		if (!isnopr[i]) prime[++ cnt] = i;
		for (int j = 1, x; j <= cnt && (x = i * prime[j]) <= sum[n]; ++ j)
		{
			isnopr[x] = 1;
			if (i % prime[j] == 0) break;//当前素数集合进行到 i 的约数的时候，就说明 x 已经不是素数了，停止这一层循环
		}//到下一个数，开始新一轮的判断
	}
}

int main()//设 f[i] 表示前 i 个石头能组成的合法序列的方案数
{//想想怎么转移？数是可以合并的，一个合法的序列中的数都是素数，那等于说只要前 i 个数的和是素数，f[i] 肯定加...
	read(n);//区间不止 1~i 这一种，那么可以枚举左端点 j ，只要 j-1~i 这一段区间的数之和为素数，那么 f[i]=Σf[j]
	for (int i = 1; i <= n; ++ i) read(a[i]), sum[i] = sum[i - 1] + a[i];//区间的和想要 O(1) 判断，理所当然前缀和
	Pre(), f[0] = 1;
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= i; ++ j)//然后 O(n^2) 枚举左右端点了，想要达到 O(1) 判断素数，只能实现线性筛
			if (!isnopr[sum[i] - sum[j - 1]]) (f[i] += f[j - 1]) %= mod;
	write(f[n], '\n', true);//于是总复杂度是 O(n^2)
	IO::flush();
	return 0;
}
