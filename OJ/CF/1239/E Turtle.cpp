#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 2e6 + 10;

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

int a[MaxN], d[3][MaxN];
ll f[MaxN][26];//f[i][j] 表示路径和为 i ，到达第 j 列时哪些数字放上去了，是这个数组是个 01 串
int main()//由于左上角和右下角必到，所以分别填最小值和次小值，考虑第一行剩下的值从小到大的填，第二行剩下的值从小到大的填
{//这样的话就可以保证不会在第 1 个和第 n 个位置之外的位置向下走，然后问题就变成把 2n-2 个数分成两组使差最小，背包即可
	int n, sum = 0; read(n);
	for (int i = 1; i <= (n << 1); ++ i) read(a[i]), sum += a[i];
	std::sort(a + 1, a + (n << 1) + 1);//排序
	int s = 0;
	memset(f, -1, sizeof(f));
	f[0][0] = 0;
	sum -= a[1] + a[2], sum >>= 1;//减去左上角和右下角，现在只需要想办法把一半的数字安放好即可
	for (int i = 3; i <= (n << 1); ++ i)
	{
		s += a[i];
		chkMin(s, sum);//走到当前点的最大路径和
		for (int j = s; j >= a[i]; -- j)
			for (int k = min(i - 3, ((n << 1) - 2) >> 1); k >= 0; -- k)
				if (f[j - a[i]][k] >= 0) f[j][k + 1] = f[j - a[i]][k] | (1ll << i);//所以这里依照状态定义就好理解了
	}
	while (f[sum][((n << 1) - 2) >> 1] == -1) --sum;//只是尽可能的对半分，实在达不到，就只能退而求其次
	d[1][1] = a[1];
	int cnt = 1;
	ll k = f[sum][((n << 1) - 2) >> 1];
	for (int i = 3; i <= (n << 1); ++ i)
		if ((k >> i) & 1) d[1][++ cnt] = a[i];//第一行放了这个数
	d[2][n] = a[2];
	cnt = n;
	for (int i = 3; i <= (n << 1); ++ i)
		if (!((k >> i) & 1)) d[2][-- cnt] = a[i];//第一行没放这个数，第二行肯定就放了
	for (int i = 1; i <= 2; ++ i)
		for (int j = 1; j <= n; ++ j) write(d[i][j], j == n ? '\n' : ' ', true);
	IO::flush();
	return 0;
}
