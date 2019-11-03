#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e5 + 10;

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

int Mx[MaxN][25], Mn[MaxN][25], Log[MaxN];
inline int getMx(int l, int r)
{
	int k = Log[r - l + 1];
	return max(Mx[l][k], Mx[r - (1 << k) + 1][k]);
}

inline int getMn(int l, int r)
{
	int k = Log[r - l + 1];
	return min(Mn[l][k], Mn[r - (1 << k) + 1][k]);
}

ll f[MaxN], sum[MaxN];
inline ll get(int l, int r)
{
	return f[l] + sum[l + 1] + getMx(l + 1, r) - getMn(l + 1, r);
}

int a[MaxN];
int main()//其实这道题就是一个以石子合并为大模板，进行魔改的题目，我竟然没看出来，真是惭愧
{//f[n][m] 初始状态：表示前 n 个物品，分了 m 组的最小费用：枚举 k 之后，有 f[n][m]=min\{f[k][m-1]+m*(sum(n)-sum(k))+\max(n\sim k+1)-\min(n\sim k+1)\}
	for (int i = 0; (1 << i) < MaxN; ++ i) Log[1 << i] = i;//复杂度 O(N^3)，优化一下状态：f[n] 表示前 n 个分成若干组的最小代价，那么枚举 k 之后
	for (int i = 1; i < MaxN; ++ i) chkMax(Log[i], Log[i - 1]);//有 f[n]=\min\{f[k]+cost(k+1,n)+sum_all-sum(1\sim n)\} 其中 cost(l,r) 表示 [l,r] 的重量和加上其中最大值减最小值

	int n, W; read(n, W);//在转移过程中，可以用一个单调栈来维护最大值和最小值的变换，然后用线段树维护区间最值，就能每次 \mathcal{O}(\log n) 更新答案，总复杂度 O(n\log n)
	for (int i = 1; i <= n; ++ i) read(a[i]), Mx[i][0] = Mn[i][0] = a[i];
	for (int j = 1; j <= 20; ++ j)//然后这个区间最值可以用 ST 表写，至于最值的位置，有个神仙用了玄学版的四边形不等式来写，我，懒了，就写这种了
		for (int i = 1; i <= n; ++ i) Mn[i][j] = min(Mn[i][j - 1], Mn[min(i + (1 << (j - 1)), n)][j - 1]), Mx[i][j] = max(Mx[i][j - 1], Mx[min(i + (1 << (j - 1)), n)][j - 1]);
	for (int i = n; i >= 1; -- i) sum[i] = sum[i + 1] + a[i];

	int pos = 0;
	for (int i = 1; i <= n; ++ i)
	{
		while (sum[pos + 1] - sum[i + 1] > W) ++ pos;
		while (pos < i - 1 && get(pos, i) >= get(pos + 1, i)) ++ pos;
		f[i] = get(pos, i);
		for (int t = 1; t <= 500 && pos - t >= 0 && sum[pos - t + 1] - sum[i + 1] <= W; ++ t) chkMin(f[i], get(pos - t, i));
		for (int t = 1; t <= 500 && pos + t < i; ++ t) chkMin(f[i], get(pos + t, i));
	}
	write(f[n], '\n', true);
	IO::flush();
	return 0;
}
