#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;
const int MaxN = 1e5 + 10, mod = 1e9 + 7;

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

inline int Quick_Power(int a, int b)
{
    int ans = 1;
    while (b)
    {
        if (b & 1) ans = 1ll * ans * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return ans;
}

int ver[MaxN << 1], Next[MaxN << 1], head[MaxN], len;
inline void add(int x, int y)
{
    ver[++ len] = y, Next[len] = head[x], head[x] = len;
}

int siz[MaxN][15], n, k;
ll sum[MaxN][15], ans1[MaxN];
inline void dfs(int x, int fa)
{
    for (int i = 0; i <= k; ++ i) siz[x][i] = sum[x][i] = 1;
    for (int i = head[x]; i; i = Next[i])
    {
        int y = ver[i];
        if (y == fa) continue;
        dfs(y, x);
        for (int j = 1; j <= k; ++ j)
        {
            siz[x][j] += siz[y][j - 1];
            sum[x][j] = sum[x][j] * sum[y][j - 1] % mod * siz[y][j - 1] % mod;
        }
    }
}

int rsiz[MaxN][15];
ll rsum[MaxN][15], ans2[MaxN];
inline void redfs(int x, int fa)
{
    for (int i = 0; i <= k; ++i) rsiz[x][i] = siz[x][i], rsum[x][i] = sum[x][i];
    if (x ^ 1)
    {
        for (int i = 1; i <= k; ++i)
        {
            rsiz[x][i] += rsiz[fa][i - 1];
            rsum[x][i] = rsum[x][i] * rsum[fa][i - 1] % mod * rsiz[fa][i - 1] % mod;
        }
    }
    ans1[x] = rsiz[x][k];
    ans2[x] = rsum[x][k] * rsiz[x][k] % mod;

    for (int i = head[x]; i; i = Next[i])
    {
        int y = ver[i];
        if (y == fa) continue;
        for (int j = 1; j <= k; ++ j)
        {
            rsiz[x][j] -= siz[y][j - 1];
            rsum[x][j] = rsum[x][j] * Quick_Power(sum[y][j - 1] * siz[y][j - 1] % mod, mod - 2) % mod;
        }
        redfs(y, x);
        for (int j = 1; j <= k; ++ j)
        {
            rsiz[x][j] += siz[y][j - 1];
            rsum[x][j] = rsum[x][j] * sum[y][j - 1] % mod * siz[y][j - 1] % mod;
        }
    }
}

int main()
{
    read(n, k);
    for (int i = 1, x, y; i < n; ++ i) read(x, y), add(x, y), add(y, x);
    dfs(1, 0), redfs(1, 0);
    for (int i = 1; i <= n; ++ i) write(ans1[i], i == n ? '\n' : ' ', true);
    for (int i = 1; i <= n; ++ i) write(ans2[i], i == n ? '\n' : ' ', true);
    IO::flush();
    return 0;
}
