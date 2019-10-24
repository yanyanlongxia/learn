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

char c[MaxN], s[MaxN];
int L[MaxN], R[MaxN], Stack[MaxN], fa[MaxN], cnt[MaxN];
int main()//https://www.luogu.org/blog/Kelin/solution-cf1239b
{
	int n; read(n);
	scanf("%s", c + 1);
	int top = 0, Mid = 0, Min = 0;
	for (int i = 1; i <= n; ++ i)
	{
		(c[i] == '(') ? ++ top : -- top;
		if (chkMin(Min, top)) Mid = i;
	}
	if (top) { puts("0\n1 1"); exit(0); }
	for (int i = Mid + 1; i <= n; ++ i) s[i - Mid] = c[i];
	for (int i = 1; i <= Mid - 1; ++ i) s[i + n - Mid] = c[i];
	int num = 0;
	for (int i = 1; i <= n; ++ i)
		if (s[i] == '(') Stack[++ top] = ++ num, L[num] = i;
		else R[Stack[top]] = i, fa[Stack[top]] = Stack[top - 1], ++ cnt[Stack[-- top]];
	int ans = cnt[0], sL = 1, sR = 1;
	for (int i = 1; i <= num; ++ i)
		if (!fa[i] && chkMax(ans, cnt[i] + 1)) sL = L[i], sR = R[i];
		else if (fa[i] && !fa[fa[i]] && chkMax(ans, cnt[0] + cnt[i] + 1)) sL = L[i], sR = R[i];
	if ((sL += Mid) > n) sL -= n;
	if ((sR += Mid) > n) sR -= n;
	write(ans, '\n', true), write(sL, ' ', true), write(sR, ' ', false);
	IO::flush();
	return 0;
}
