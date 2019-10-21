#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 2e7, mod = 1e9 + 7;
typedef ll larr[MaxN + 10];

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

inline ll Quick_Power(ll a, ll b)
{
	ll ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}

larr fac, inv;
inline ll C(ll n, ll m)
{
	if (n < m || m < 0 || n < 0) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main()
{
	fac[0] = 1;
	for (int i = 1; i <= MaxN; ++ i) fac[i] = fac[i - 1] * i % mod;
	inv[MaxN] = Quick_Power(fac[MaxN], mod - 2);
	for (int i = MaxN - 1; i >= 0; -- i) inv[i] = inv[i + 1] * (i + 1) % mod;
	ll Q; read(Q);
	while (Q --)
	{
		ll n, x, y; read(n, x, y);
		if (x > y) std::swap(x, y);
		ll t1 = (C(x + y - 2, x - 1) - C(x + y - 2, x - 2) + mod) % mod;
		ll t2 = (C(2 * n - x - y, n - y) - C(2 * n - x - y, n - y - 1) + mod) % mod;
		write(t1 * t2 % mod, '\n', true);
	}
	IO::flush();
	return 0;
}
//https://www.cnblogs.com/Ace-MYX/p/11424555.html
//【题目描述】
//定义一个长度为n的正整数序列A是“好”的序列，当且仅当其满足如下条件：
//1.序列中每个数均满足 1≤A[i]≤n
//2.i≠j?A[i]≠A[j]
//3.最长下降子序列长度不超过2
//现在有T组询问，每组询问的形式是：有多少个长度为n的“好”的序列，满足A[x]=y。
//这个答案可能很大，请你求出对10^9+7取模的结果。
//【输入数据】
//第一行一个非负整数T表示询问组数。
//接下来T行，每行三个正整数n、x和y表示询问。
//【输出数据】
//输出T行，每一行输出询问对应的答案对10^9+7取模的结果。
//【数据范围】
//Subtask 1 (3pts)：T=0。
//Subtask 2 (7pts)：T≤10 n≤8。
//Subtask 3 (10pts)：T≤10 n≤15。
//Subtask 4 (10pts)：T≤10 n≤200。
//Subtask 5 (20pts)：T≤10 n≤2000。
//Subtask 6 (20pts)：T≤10 n≤100000。
//Subtask 7 (30pts)：无特殊限制。
//对于全部数据，有0≤T≤1000000 1≤n≤10000000。
//【分析】
//1.(3pts)随便读入输出
//2.(10pts)暴力枚举每种排列进行判断，单次询问复杂度:O(n!)
//3.(20pts)可以推到以下一个重要结论对正解十分重要
//结论：对于任意一个数很容易证明要么所有比它小的数都在它前面，要么满足前面所有的数都比它小
//然后状压DP，定义dp[i][2^n]表示当前第i位，用了集合S中的数，转移直接枚举当前这一位填谁，单次询问复杂度O(2^n*n)
//4.(50pts)观察题意，前面对限制3的应用还不够充分，仔细思考不难发现一种DP，从大到小依次模拟向一个队列中添加数，
//那么就会有一种极其有趣的情况，如果当前正在考虑的数没有被插到队列的最前面，那么它前面必然有几个数比它大，
//于是定义dp[i][j]表示当前填到了i，当前的数要填在第j位之前的方按数。
//那么就有两种转移dp[i][j]->dp[i-1][j+1]即放在队首，另一种dp[i][j]->dp[i-1][k](1<=k<=j)即放在某一个数后面。
//此时发现我们并没有考虑T个询问中对x位的要求，由于前面几种做法并不是很难处理而这里需要进行特殊的分类讨论。
//观察发现，不难得出结论：要么当前位置去掉后现队列依然成立要么就是加上这一位后不存在这两种情况:
//x之前有大于y的(因为x前如果有那么就会有一个小于y的在它后面于是那个大于的与这一个和后面那个小于的就形成了一个长度为3的下降子序列)或者x之后有小于y的(证明与第一种情况类似)。
//所以按照x与y的大小关系分为三类：
//(1)当x=y则按照结论，序列以x为断点分为两个子问题，两段分别符合条件即可。
//(2)当x>y则一定有比y大的数在x之前，那么需要有比y小的数都在x前，后面一定都是比y大的数所以dp在插入y之前是有一定限制的固定转移。按此策略递推即可。
//(3)当x<y与上一情况类似，在此不做赘述。单次询问复杂度O(n^2)
//这个dp十分细节，还是有几分写的必要(因为正解推公式代码没有任何细节)，这里留个 ，以后来填。(懒？)
//5.(70pts)考虑dp的组合意义，实际上是在计数有多少个长度为n+1的正 整数序列P，满足P[i+1] ≤ P[i +1]，
//同时P[1]=P[n+1]=1,设B[i]=P[i]?i，那么对B的限制就是B[i+1] ≤ B[i]，同时B[i]>?i。
//放到平面上可以用翻折法计数。那么枚举走到y时的值就是在枚举走到了平面上哪个点，两边分别计数乘起来即可，单次询问时间复杂度是O(n)。
//6.(100pts)满足最长下降子序列不超过2的排列，一定与一种前缀max序列一一对应，因为考虑把前缀max序列中有用的值（就是单调栈中的值，
//也就是每 一个连续段的开头）插入进序列时，为了使得最长下降子序列不超过2, 就会产生从此处开始小于该数的所有数一定递增排列的限制。
//那么可以观察到，序列是这么一个形状：所有在前缀max上产生贡献 的点形成了一个递增序列，剩下的数也形成了一个递增序列显然一个最长下降子序列不超过2的排列一定对应了其本身的前缀max 序列。
//而一个前缀max序列没有对前缀max产生贡献的位置填的数也是确定的， 唯一对应了一个最长下降子序列不超过2的排列。
//分情况讨论：
//（1）y ≥ x，那么该点一定在前缀max上。考虑反证，若其没有对前缀 max 产生贡献，那么x前面一定有一个大于y的数，同时x后面没有 小于y的数，否则存在长度为3的下降子序列，也就是所有小于y 的数都在x之前，那么至少需要1+y-1 = y个位置，而y ≥x > x-1，x前面的位置不够，矛盾
//（2）y < x，那么该点一定不对前缀max产生贡献。这是显然的
//（3）对于y < x的情况，考虑A的逆置换A-1 A i = i，可以转换成另一 种情况，也就是说只要考虑y ≥ x的情况
//考虑一个合法的前缀max序列满足的条件：
//（1）1 ≤ max[i]≤n max[n]=n
//（2）max[i]≤max[i+1]
//（3）i≤max[i]
//同样放到平面上考虑。
//固定A[x]=y等价于确定了一部分路径，两边分别计数即可。计数也是用翻折法。那
//么预处理复杂度是O(n)，单次询问复杂度是O(1) 。
