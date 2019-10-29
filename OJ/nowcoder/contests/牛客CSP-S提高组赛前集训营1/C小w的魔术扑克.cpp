#include <bits/stdc++.h>
 
#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)
 
#define DeBug(x) std::cout << #x << " = " << x << std::endl
 
#define mp std::make_pair
typedef std::pair<int, int> pii;
const int MaxN = 1e5 + 10;
 
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
 
int fa[MaxN];
inline int get(int x)
{
    return fa[x] == x ? x : fa[x] = get(fa[x]);
}
 
int flag[MaxN], Min[MaxN], Max[MaxN];
inline void merge(int x, int y)
{
    x = get(x), y = get(y);
    if (x == y)
    {
        flag[x] = 1;
        return ;
    }
    fa[x] = y;
    chkMin(Min[y], Min[x]);
    chkMax(Max[y], Max[x]);
}
 
int lim[MaxN], ans[MaxN];
std::vector<pii> Q[MaxN];
int main()
{
    int n, m; read(n, m);
    for (int i = 1; i <= n; ++ i) Max[i] = Min[i] = fa[i] = i, flag[i] = 0;
    for (int i = 1, x, y; i <= m; ++ i) read(x, y), merge(x, y);
    for (int i = 1; i <= n; ++ i) lim[i] = n + 1;
    for (int i = 1; i <= n; ++ i)
        if (get(i) == i && !flag[i]) chkMin(lim[Min[i]], Max[i]);
    int q; read(q);
    for (int i = 1, l, r; i <= q; ++ i) read(l, r), Q[l].push_back(mp(r, i));
    int nowlim = n + 1;
    for (int i = n; i >= 1; -- i)
    {
        chkMin(nowlim, lim[i]);
        for (int j = 0; j < (int)Q[i].size(); ++ j) ans[Q[i][j].second] = Q[i][j].first < nowlim;
    }
    for (int i = 1; i <= q; ++ i)
        if (ans[i]) puts("Yes");
        else puts("No");
    return 0;
}
