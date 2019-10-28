#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 4e4 + 10;

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

int A, B, num;
int q[MaxN], head, tail;
inline void dfs(int x, ll y, int p10)
{
	if (y > B) return ;
	if (!x)
	{
		int lst = y / (p10 / 10);
		if (!lst) return ;
		dfs(x, y + (ll)lst * p10, p10 * 10);
		if (y >= A && y <= B) ++ num;
		if (p10 < B) q[tail ++] = y;
		return ;
	}
	int lst = y / (p10 / 10), nxt = x % 10;
	x /= 10;
	if (lst - nxt >= 0) dfs(x, y + p10 * (lst - nxt), p10 * 10);
	if (nxt && lst + nxt <= 9) dfs(x, y + p10 * (lst + nxt), p10 * 10);
}

int main()//题解：https://www.luogu.org/blog/rqy/solution-p1822
{
	read(A, B);
	head = tail = num = 0;
	q[tail ++] = 7;
	if (A <= 7 && B >= 7) ++ num;
	do
	{
		for (int i = 0; i <= 9; ++ i) dfs(q[head], i, 10);
	} while (++ head < tail);
	write(num, '\n', true);
	IO::flush();
	return 0;
}
