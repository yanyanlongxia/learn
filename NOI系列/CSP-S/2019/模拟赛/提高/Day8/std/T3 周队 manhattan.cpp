#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

#define x first
#define y second
#define mp std::make_pair
typedef std::pair<int, int> pii;
const int MaxN = 1e3 + 10;

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

int n, l;
bool a[MaxN][MaxN], ans[MaxN][MaxN], b[MaxN][MaxN];
pii t[MaxN << 2];
inline void work()
{
	memset(b, true, sizeof(b));
	//a.x = b.x
	static int s1[MaxN][MaxN], s[MaxN << 1][MaxN << 1];
	memset(s1, 0, sizeof(s1)), memset(s, 0, sizeof(s));
	for (int i = 1; i <= l; ++ i)
		for (int j = 1; j <= l; ++ j)
			if (i != j && t[i].x + t[i].y == t[j].x + t[j].y && t[i].x < t[j].x)
			{
				++ s1[t[j].x][t[i].y];
				++ s1[1][1], -- s1[1][t[j].y + 1], -- s1[t[i].x + 1][1], ++ s1[t[i].x + 1][t[j].y + 1];
				int y = t[i].x - t[j].y, l = t[i].x + t[j].y, r = t[i].y + t[j].x;
				++ s[y + n][l], -- s[y + n][r + 1];
			}
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= n; ++ j) s1[i][j] += s1[i - 1][j];
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= n; ++ j) s1[i][j] += s1[i][j - 1];
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= n; ++ j)
			if (s1[i][j]) b[i][j] = false;
	//a.x < b.x a.y < b.y
	for (int i = 1; i <= l; ++ i)
	{
		int x = t[i].x, y = t[i].y;
		t[i].x = x + y, t[i].y = x - y;
	}
	static int mx[MaxN << 1], mn[MaxN << 1];
	for (int i = 1; i <= (n << 1); ++ i) mx[i] = -n, mn[i] = n;
	for (int i = 1; i <= l; ++ i)
		for (int j = 1; j <= l; ++ j)
			if (t[i].x < t[j].x && t[i].y < t[j].y && t[j].y - t[i].y >= t[j].x - t[i].x)
			{
				int L = t[j].y - t[i].y;
				if (L % 2 == 0)
				{
					int y = (t[i].y + t[j].y) >> 1;
					int l = t[j].x - (L >> 1), r = t[i].x + (L >> 1);
					++ s[y + n][l], -- s[y + n][r + 1];
				}
				int t1 = t[j].x + t[i].y;
				chkMin(mn[t1], (t[i].y + t[j].y + 4096) / 2 - 2048);
				t1 = t[i].x + t[j].y;
				chkMax(mx[t1], (t[i].y + t[j].y + 1 + 4096) / 2 - 2048);
			}
	for (int i = 1; i <= (n << 1); ++ i)
		for (int j = 1; j <= (n << 1); ++ j) s[i][j] += s[i][j - 1];
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= n; ++ j)
		{
			int x = i + j, y = i - j;
			if (s[y + n][x] || mx[x + y] >= y || mn[x + y] <= y) b[i][j] = false;
		}
}

int main()
{
	read(n);
	int cnt = 0;
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= n; ++ j)
		{
			char Grt;
			while (ch < '0' || ch > '1') Grt;
			cnt += (a[i][j] = ch - '0');
		}
	if (cnt - 1 > 2 * (n - 1))
	{
		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= n; ++ j) *IO::fe++ = 'Y', *IO::fe++ = j == n ? '\n' : ' ';
	}
	else
	{
		memset(ans, true, sizeof(ans));
		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= n; ++ j)
				if (a[i][j]) t[++ l] = mp(i, j);
		work();
		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= n; ++ j) ans[i][j] = ans[i][j] && b[i][j];

		l = 0;
		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= n; ++ j)
				if (a[i][j]) t[++ l] = mp(i, n - j + 1);
		work();
		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= n; ++ j) ans[i][j] = ans[i][j] && b[i][n - j + 1];

		l = 0;
		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= n; ++ j)
				if (a[i][j]) t[++ l] = mp(j, i);
		work();
		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= n; ++ j) ans[i][j] = ans[i][j] && b[j][i];

		l = 0;
		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= n; ++ j)
				if (a[i][j]) t[++ l] = mp(j, n - i + 1);
		work();
		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= n; ++ j) ans[i][j] = ans[i][j] && b[j][n - i + 1];

		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= n; ++ j) *IO::fe++ = ans[i][j] ? 'N' : 'Y', *IO::fe++ = j == n ? '\n' : ' ';
	}
	IO::flush();
	return 0;
}
