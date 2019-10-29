#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define Grt ch = getchar()
#define DeBug(x) std::cout << #x << " = " << x << std::endl

#define fi first
#define se second
#define mp std::make_pair
typedef long long ll;
typedef std::pair<ll, int> pli;
const int MaxN = 2e5 + 10, MaxT = 1e3 + 10;

namespace IO
{
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
	template <typename T> inline void write(T x, char str)
	{
		if (!x) *fe++ = 48;
		if (x < 0) *fe++ = '-', x = -x;
		T num = 0, ch[20];
		while (x) ch[++ num] = x % 10 + 48, x /= 10;
		while (num) *fe++ = ch[num --];
		*fe++ = str;
	}
}

using IO::read;
using IO::write;

template <typename T> inline bool chkMin(T &a, const T &b) { return a > b ? (a = b, true) : false; }
template <typename T> inline bool chkMax(T &a, const T &b) { return a < b ? (a = b, true) : false; }
template <typename T> inline T min(T a, T b) { return a < b ? a : b; }
template <typename T> inline T max(T a, T b) { return a > b ? a : b; }

int T[MaxN], Tn[MaxN];
int cnt[MaxT], s[MaxT], t[MaxT][MaxT];
int main()
{
	int n, m; read(n, m);
	for (int i = 1; i <= n; ++ i) read(T[i]), ++ cnt[T[i]];
	std::priority_queue<pli, std::vector<pli>, std::greater<pli> > q;
	q.push(mp(T[1], 1));
	for (int i = 1; i < n; ++ i)
	{
		pli x = q.top();
		q.pop();
		Tn[i] = x.fi;
		q.push(mp(x.fi + T[x.se], x.se)), q.push(mp(x.fi + T[i + 1], i + 1));
	}
	for (int i = 1; i <= n; ++ i) s[T[i]] += Tn[i - 1] / T[i], ++ t[T[i]][Tn[i - 1] % T[i]];
	for (int i = 0; i <= 1000; ++ i)
		for (int j = i; j >= 0; -- j) t[i][j] += t[i][j + 1];
	for (int i = 1, a; i <= m; ++ i)
	{
		read(a);
		if (a <= n - 1) write(Tn[a], ' ');
		else
		{
			ll l = Tn[n - 1] - 1, r = (ll)T[1] * a, ans = 0;
			while (l <= r)
			{
				ll sum = 0, mid = (l + r) >> 1;
				for (int j = 1; j <= 1000; ++ j) sum += cnt[j] * (mid / j) - s[j] - t[j][mid % j + 1];
				if (sum >= a) ans = mid, r = mid - 1;
				else l = mid + 1;
			}
			write(ans, ' ');
		}
	}
	IO::flush();
	return 0;
}
