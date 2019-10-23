#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef std::pair<int, int> pii;
const int MaxN = 2e5 + 10;

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

std::vector<pii> v[MaxN];
std::set<pii> s;
int main()
{
	int n, k; read(n, k);
	for (int i = 1, l, r; i <= n; ++ i) read(l, r), v[l].push_back(pii(r, i));
	std::vector<int> ans;
	for (int i = 1; i <= MaxN - 10; ++ i)
	{
		for (int j = 0; j < (int)v[i].size(); ++ j) s.insert(v[i][j]);
		while (s.size() > k) ans.push_back(s.rbegin() -> second), s.erase(--s.end());
		while (!s.empty() && s.begin() -> first == i) s.erase(s.begin());
	}
	write((int)ans.size(), '\n', true);
	for (int i = 0; i < (int)ans.size(); ++ i) write(ans[i], ' ', true);
	IO::flush();
	return 0;
}
