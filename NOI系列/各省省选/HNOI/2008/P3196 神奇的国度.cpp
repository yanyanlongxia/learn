#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 1e4 + 10, MaxM = 1e6 + 10;

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

int ver[MaxM << 1], Next[MaxM << 1], head[MaxN], len;
inline void add(int x, int y)
{
	ver[++ len] = y, Next[len] = head[x], head[x] = len;
}

int label[MaxN], vis[MaxN], Q[MaxN], tot;
std::vector<int> V[MaxN];
int main()//求出完美消除序列，从后往前依次给每个点染上可以染的最小的颜色
{
	int n, m; read(n, m);
	for (int i = 1, x, y; i <= m; ++ i) read(x, y), add(x, y), add(y, x);
	for (int i = 1; i <= n; ++ i) V[0].push_back(i);
	int best = 0;
	for (int x = 1, now = 0; x <= n; ++ x)
	{
		int flag = 0;
		while (!flag)
		{
			for (int i = V[best].size() - 1; i >= 0; -- i)
			{
				if (vis[V[best][i]]) V[best].pop_back();
				else { flag = 1, now = V[best][i]; break; }
			}
			if (!flag) -- best;
		}
		Q[++ tot] = now, vis[now] = 1;
		for (int i = head[now]; i; i = Next[i])
		{
			int y = ver[i];
			if (!vis[y]) V[++ label[y]].push_back(y), chkMax(best, label[y]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++ i) chkMax(ans, label[i] + 1);//本题只要求出颜色个数，可以证明答案为此式
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
