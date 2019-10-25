#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 3e5 + 10;

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

char s[MaxN];
int main()
{
	int Q; read(Q);
	while (Q --)
	{
		scanf("%s", s + 1);
		int len = strlen(s + 1);
		std::string odd, even;
		for (int i = 1; i <= len; ++ i)
			if ((s[i] - '0') & 1) odd += s[i];//奇数
			else even += s[i];//偶数
		int n = odd.size(), m = even.size();
		std::string ans;
		for (int i = 0, j = 0; i < n || j < m; )
			if (i == n) ans += even[j++];
			else if (j == m) ans += odd[i++];
			else if (odd[i] < even[j]) ans += odd[i++];
			else ans += even[j++];
		for (int i = 0; i < ans.size(); ++ i) *IO::fe++ = ans[i];
		*IO::fe++ = '\n';
	}
	IO::flush();
	return 0;
}
