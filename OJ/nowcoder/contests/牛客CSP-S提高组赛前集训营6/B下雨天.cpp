#include <bits/stdc++.h>

#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

typedef long long ll;

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

    char Out[1<<26], *fe = Out;
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

int highest;
struct Orz
{
    int l, r;
    int type, h;
    inline int get_right_h() { return highest + h; }

    inline int get_left_h()
    {
        if (!type) return get_right_h();
        else return get_right_h() - (r - l);
    }
};
std::vector<Orz> v;
inline ll S(int l, int r)
{
    return 1ll * (r - l + 1) * (l + r) / 2;
}

ll ans;
int main()//丧心病狂码农题
{
    int n, q; read(n, q);
    v.push_back({1, n, 0, 0});
    for (int i = 1, x; i <= q; ++ i)
    {
        read(x);
        if (x > 0)
        {
            for (int i = (int)v.size() - 1; i >= 0; -- i)
            {
                if (v[i].type == 1)
                {
                    if (v[i].get_left_h() + x <= v[i].l) break;
                    else ans += 1ll * (v[i].l - v[i].get_left_h()) * (v[i].r - v[i].l + 1), v.pop_back();
                }
                else
                {
                    if (v[i].get_right_h() + x <= v[i].r)
                    {
                        ans += S(v[i].l - v[i].get_left_h(),
                                v[i].l - v[i].get_left_h() + (x - (v[i].l - v[i].get_left_h())) - 1);
                        v[i].l += (x - (v[i].l - v[i].get_left_h()));
                        break;
                    }
                    else ans += S(v[i].l - v[i].get_left_h(), v[i].r - v[i].get_right_h()), v.pop_back();
                }
            }
            if (v.empty()) v.push_back({1, n, 1, 0});
            else v.push_back({1, v.back().l - 1, 1, -highest - x + (v.back().l - 1)});
            ans += 1ll * x * (n - v.back().r);
            if (!v.back().r) v.pop_back();
            highest += x;
            if (highest > n) highest = n;
        }
        else
        {
            for (int i = (int)v.size() - 1; i >= 0; -- i)
            {
                if (v[i].type == 0)
                {
                    if (v[i].get_right_h() + x > 0) break;
                    else ans -= 1ll * (highest + v[i].h) * (v[i].r - v[i].l + 1), v.pop_back();
                }
                else// type = 1
                {
                    if (v[i].get_right_h() + x > 0)
                    {
                        ans -= S(v[i].get_left_h(), -x), v[i].l = v[i].r - (highest + v[i].h + x) + 1;
                        break;
                    }
                    else ans -= S(v[i].get_left_h(), v[i].get_right_h()), v.pop_back();
                }
            }
            if (v.empty()) v.push_back({1, n, 0, 0});
            else v.push_back({1, v.back().l - 1, 0, -highest - x});
            ans += 1ll * x * (n - v.back().r);
            highest += x;
            if (highest < 0) highest = 0;
        }
        write(ans, '\n', true);//再次因为输出文件过大导致 Out[1<<24] 不够用而 RE，开了 Out[1<<26] 就过了，考虑
    }
    IO::flush();
    return 0;
}
