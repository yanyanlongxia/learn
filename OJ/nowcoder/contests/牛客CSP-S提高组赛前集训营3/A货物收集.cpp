#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e6 + 10;

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

ll sum, a[MaxN];
inline void dfs(int x, int fa, ll mid)
{
    sum += a[x];
    for (int i = head[x]; i; i = Next[i])
    {
        int y = ver[i];
        if (y == fa) continue;
        if (mid >= edge[i]) dfs(y, x, mid);
    }
}

inline ll check(ll mid)
{
    sum = 0;
    dfs(1, 0, mid);
    return sum;
}

int main()
{
    int n, W; read(n, W);
    for (int i = 2; i <= n; ++ i) read(a[i]);
    int Mx = 0;
    for (int i = 1, x, y, z; i < n; ++ i) read(x, y, z), add(x, y, z), add(y, x, z), chkMax(Mx, z);
    ll l = 1, r = Mx, ans = 0;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid) >= W) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    write(ans, '\n', true);
    IO::flush();
    return 0;
}
