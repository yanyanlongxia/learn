#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
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

ll s;
int n, L[MaxN], R[MaxN];
inline bool check(int x)
{
	int k = (n + 1) >> 1;
	std::vector<int> v;
	for (int i = 1; i <= n; ++ i)
	{
		int t = max(L[i], x);
		if (R[i] < t) continue;
		v.push_back(t - L[i]);
	}
	if ((int)v.size() < k) return false;
	std::sort(v.begin(), v.end());
	ll sum = 0;
	for (int i = 0; i < k; ++ i) sum += v[i];
	return sum <= s;
}

int main()
{
	int T; read(T);
	while (T --)
	{
		read(n, s);
		for (int i = 1; i <= n; ++ i) read(L[i], R[i]), s -= L[i];
		int l = 0, r = 1e9, ans = 0;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (check(mid)) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		write(ans, '\n', true);
	}
	IO::flush();
	return 0;
}
