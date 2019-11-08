#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 3e5 + 10;

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

int ver[MaxN << 1], edge[MaxN << 1], Next[MaxN << 1], head[MaxN], len;
inline void add(int x, int y, int z)
{
	ver[++ len] = y, edge[len] = z, Next[len] = head[x], head[x] = len;
}

int fa[MaxN], siz[MaxN], son[MaxN];
ll dep[MaxN], dfa[MaxN];
inline void dfs1(int x, int f)
{
	fa[x] = f;
	siz[x] = 1;
	for (int i = head[x]; i; i = Next[i])
	{
		int y = ver[i];
		if (y == f) continue;
		dep[y] = dep[x] + edge[i];
		dfa[y] = edge[i];
		dfs1(y, x);
		siz[x] += siz[y];
		if (!son[x] || siz[y] > siz[son[x]]) son[x] = y;
	}
}

int dfn[MaxN], id;
int pos[MaxN], top[MaxN];
int f[MaxN][21];
ll w[MaxN][21];
inline void dfs2(int x, int topf)
{
	dfn[x] = ++ id;
	pos[id] = x;
	top[x] = topf;
	if (!son[x]) return ;
	dfs2(son[x], topf);
	for (int i = head[x]; i; i = Next[i])
	{
		int y = ver[i];
		if (y == fa[x] || y == son[x]) continue;
		dfs2(y, y);
	}
	if (top[x] == x)
	{
		int L = dfn[x], R = L;
		while (top[pos[R + 1]] == x) ++ R;
		std::stack<int> s;
		for (int i = R; i >= L; -- i)
		{
			while (!s.empty() && s.top() > pos[i]) s.pop();
			if (!s.empty()) f[pos[i]][0] = s.top(), w[pos[i]][0] = pos[i] * (dep[s.top()] - dep[pos[i]]);
			s.push(pos[i]);
		}
	}
}

int Stx[MaxN], Sty[MaxN], Top;
int main()
{
	int n, m; read(n, m);
	for (int i = 1, x, y, z; i < n; ++ i) read(x, y, z), add(x, y, z), add(y, x, z);
	dfs1(1, 0);
	dfs2(1, 1);
	for (int j = 1; j <= 20; ++ j)
		for (int i = 1; i <= n; ++ i) f[i][j] = f[f[i][j - 1]][j - 1], w[i][j] = w[i][j - 1] + w[f[i][j - 1]][j - 1];
	while (m --)
	{
		int x, y; read(x, y);
		while (y && top[y] ^ top[x]) Stx[Top] = top[y], Sty[Top ++] = y, y = fa[top[y]];
		if (dep[y] < dep[x]) write(-1, '\n', true), Top = 0;
		else
		{
			Stx[Top] = x, Sty[Top ++] = y;
			ll ans = 0;
			int u = x;
			while (Top --)
			{
				int t = Stx[Top], ed = Sty[Top];
				if (t ^ x) ans += 1ll * u * dfa[t];
				for (int i = 20; i >= 0; -- i)
					if (f[t][i] && f[t][i] >= u && dep[f[t][i]] <= dep[ed]) ans += u * (dep[f[t][i]] - dep[t]), t = f[t][i];
				if (f[t][0] && t >= u && dep[f[t][0]] <= dep[ed]) ans += u * (dep[f[t][0]] - dep[t]), t = f[t][0];
				for (int i = 20; i >= 0; -- i)
					if (f[t][i] && dep[f[t][i]] <= dep[ed]) ans += w[t][i], t = f[t][i];
                ans += (u = min(t , u)) * (dep[ed] - dep[t]);
            }
			Top=0;
            write(ans, '\n', true);
		}
	}
	IO::flush();
	return 0;
}
