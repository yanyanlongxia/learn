#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 2e5 + 10;

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

int fa[MaxN][2];
inline int get(int x, int s)
{
	return fa[x][s] == x ? x : fa[x][s] = get(fa[x][s], s);
}

int siz[MaxN][2];
inline void merge(int x, int y, int s)
{
	x = get(x, s), y = get(y, s);
	if (x == y) return ;
	fa[x][s] = y, siz[y][s] += siz[x][s];
	
}

int main()//考虑所有答案点对有哪几种情况：全 0 、全 1 、一段 0 接一段 1
{//只保留树上所有 0 边，形成一个森林，我们把这个森林称为 0 森林
	int n; read(n);//那么对于 0 森林内的每个连通分量，会产生 siz(siz-1) 个全 0 对
	for (int i = 1; i <= n; ++ i) fa[i][0] = fa[i][1] = i, siz[i][0] = siz[i][1] = 1;
	for (int i = 1, x, y, z; i < n; ++ i) read(x, y, z), merge(x, y, z);
	ll ans = 0;//用并查集维护连通分量，这样子就处理完了所有全 0 点对，全 1 点对和全 0 点对是类似的
	for (int i = 1; i <= n; ++ i)
	{
		if (fa[i][0] == i) ans += 1ll * siz[i][0] * (siz[i][0] - 1);
		if (fa[i][1] == i) ans += 1ll * siz[i][1] * (siz[i][1] - 1);
		int x = get(i, 0), y = get(i, 1);//现在考虑一段 0 接一段 1 怎么做，对于一个一段 0 接一段 1 的点对 (u,v)
		ans += 1ll * (siz[x][0] - 1) * (siz[y][1] - 1);//会存在一个点 t ，使得 (u,t) 全 0 、 (t,v) 全 1
	}//那么枚举 t ，它的贡献就是 (siz0-1)(siz1-1)，这里的 siz0 指的是 t 在 0 森林中所属连通分量的大小， siz1 类似。
	write(ans, '\n', true);
	IO::flush();
	return 0;
}
