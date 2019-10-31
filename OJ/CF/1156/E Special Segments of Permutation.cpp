#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 2e5 + 10;

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

int a[MaxN], id[MaxN], L[MaxN], R[MaxN];
int Stack[MaxN], top;
int main()
{
	int n; read(n);
	for (int i = 1; i <= n; ++ i) read(a[i]), id[a[i]] = i;
	Stack[top = 0] = 0;
	for (int i = 1; i <= n; ++ i)
	{//先预处理出每个 i 左边第一个大于它的位置(记为 L[i])和右边第一个大于它的位置(记为 R[i])。显然可以单调栈 O(n) 求出
		while (top && a[Stack[top]] < a[i]) -- top;
		L[i] = Stack[top], Stack[++ top] = i;
	}
	Stack[top = 0] = n + 1;
	for (int i = n; i >= 1; -- i)
	{
		while (top && a[Stack[top]] < a[i]) -- top;
		R[i] = Stack[top], Stack[++ top] = i;
	}
	ll ans = 0;//枚举最大值的位置，那么左端点只会落在 (L[i],i)，右端点只会落在 (i,R[i])
	for (int i = 1; i <= n; ++ i)
		if (i - L[i] < R[i] - i)
		{
			for (int j = L[i] + 1; j < i; ++ j)//那么在小的那个区间中枚举一个端点，在另外那个区间中查有没有对应的值
			{
				int t = id[a[i] - a[j]];
				if (i < t && t < R[i]) ++ ans;
			}
		}
		else
		{
			for (int j = i + 1; j < R[i]; ++ j)
			{
				int t = id[a[i] - a[j]];
				if (L[i] < t && t < i) ++ ans;
			}
		}//这样子看上去是 O(n^2) 的，实际上是 O(n\log n) 的
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
