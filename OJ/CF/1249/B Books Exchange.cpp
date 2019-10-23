#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

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

int fa[MaxN], siz[MaxN];
inline int get(int x)
{
	return fa[x] == x ? x : fa[x] = get(fa[x]);
}

inline void merge(int i, int j)
{
	int x = get(i), y = get(j);
	if (x == y) return ;
	fa[x] = y, siz[y] += siz[x];
}

int a[MaxN];
int main()//好题啊，每次把两个人合并，问多长时间书重回主人手上，其实转化一下，就是这本书传了几个人，也就是主人的子树大小了
{
	int Q; read(Q);
	while (Q --)
	{
		int n; read(n);
		for (int i = 1; i <= n; ++ i) fa[i] = i, siz[i] = 1;
		for (int i = 1; i <= n; ++ i) read(a[i]), merge(i, a[i]);
		for (int i = 1; i <= n; ++ i) write(siz[get(i)], i == n ? '\n' : ' ', true);
	}
	IO::flush();
	return 0;
}
