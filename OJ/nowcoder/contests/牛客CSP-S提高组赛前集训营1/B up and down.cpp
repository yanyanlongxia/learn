#include <bits/stdc++.h>
 
using namespace std;
 
#define MS(a, b) memset(a, b, sizeof(a))
#define REP(a, b, c) for (register int a = b; a <= c; ++a)
#define DREP(a, b, c) for (register int a = b; a >= c; --a)
#define FOR(a, b, c) for (register int a = b; a < c; ++a)
#define EREP(a, b) for (register int a = head[b]; a; a = edge[a].nxt)
 
inline int rd () {
    int x = 0; bool f = 0; char c = getchar();
    while ((c < '0' || c > '9') && c != '-') c = getchar();
    if (c == '-') f = 1, c = getchar();
    while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return f ? -x : x;
}
 
const int Mod = 1e9 + 7;
const int SIZE = 100005;
 
int n, k;
 
int head[SIZE], ecnt;
struct Edge {
    int v, nxt;
} edge[SIZE << 1];
void Add_Edge (int u, int v) {
    ++ecnt;
    edge[ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u] = ecnt;
}
 
int Inv (int a) {
    int res = 1, b = Mod - 2;
    while (b) {
        if (b & 1) res = 1LL * res * a % Mod;
        b >>= 1;
        a = 1LL * a * a % Mod;
    }
    return res;
}
 
int dp[SIZE][11], f[SIZE][11];
int num[SIZE][11], cnt[SIZE][11];
void dfs (int u, int fa) {
    REP (i, 0, k) dp[u][i] = f[u][i] = 1;
    EREP (i, u) {
        Edge& e = edge[i];
        if (e.v == fa) continue;
        dfs(e.v, u);
        REP (j, 1, k) {
            dp[u][j] = 1LL * dp[u][j] * dp[e.v][j - 1] % Mod * (num[e.v][j - 1] + 1) % Mod;
            num[u][j] += num[e.v][j - 1] + 1;
        }
    }
    //printf ("%d: %d\n", u, num[u][k]);
}
 
int ans[SIZE];
void DFS (int u, int fa) {
    if (u == 1) {
        ans[u] = 1LL * dp[u][k] * (num[u][k] + 1) % Mod;
    } else {
        REP (i, 1, k) {
            f[u][i] = 1LL * f[fa][i - 1] * dp[fa][i - 1] % Mod * (cnt[fa][i - 1] + 1 + num[fa][i - 1] - (i >= 2 ? num[u][i - 2] + 1 : 0)) % Mod;
            if (i >= 2) f[u][i] = 1LL * f[u][i] * Inv(num[u][i - 2] + 1) % Mod * Inv(dp[u][i - 2]) % Mod;
            cnt[u][i] = cnt[fa][i - 1] + num[fa][i - 1] + 1;
            if (i >= 2) cnt[u][i] -= num[u][i - 2] + 1;
        }
        ans[u] = 1LL * dp[u][k] * f[u][k] % Mod * (num[u][k] + cnt[u][k] + 1) % Mod;
    }
    EREP (i, u) {
        Edge& e = edge[i];
        if (e.v == fa) continue;
        DFS(e.v, u);
    }
}
 
int main () {
    n = rd(), k = rd();
    FOR (i, 1, n) {
        int u = rd(), v = rd();
        Add_Edge(u, v);
        Add_Edge(v, u);
    }
    dfs(1, 0);
    DFS(1, 0);
    REP (i, 1, n) {
        printf ("%d", num[i][k] + 1 + cnt[i][k]);
        if (i == n) puts("");
        else putchar(' ');
    }
    REP (i, 1, n) {
        printf ("%d", ans[i]);
        if (i == n) puts("");
        else putchar(' ');
    }
    return 0;
}
