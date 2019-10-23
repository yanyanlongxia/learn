#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 2e2 + 10;

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

int n, k, ans;
int f[MaxN][MaxN], a[MaxN];
std::vector<int> e[MaxN];
inline void dfs(int x, int fa)
{
	f[x][0] = a[x];
	int tmp[MaxN];
	for (int i = 0; i < (int)e[x].size(); ++ i)
	{
		int y = e[x][i];
		if (y == fa) continue;
		dfs(y, x);
		for (int l = 0; l <= n; ++ l) tmp[l] = f[x][l];
		for (int l = 0; l <= n; ++ l)
			for (int r = 0; r <= n; ++ r)
				if (l + r + 1 > k) chkMax(f[x][min(l, r + 1)], tmp[l] + f[y][r]);
		for (int l = 0; l <= n; ++ l) chkMax(f[x][l + 1], f[y][l]);
	}
	for (int i = 0 ; i <= n; ++ i) chkMax(ans, f[x][i]);
}

int main()
{
	read(n, k);
	for (int i = 1; i <= n; ++ i) read(a[i]);
	for (int i = 1, x, y; i < n; ++ i) read(x, y), e[x].push_back(y), e[y].push_back(x);
	dfs(1, 0);
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
