#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 2e4 + 10, W = 2e4;

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

int prime[MaxN], cnt;
bool isnopr[MaxN];
inline void Pre()
{
	isnopr[1] = 1;
	for (int i = 2; i <= W; ++ i)
	{
		if (!isnopr[i]) prime[++ cnt] = i;
		for (int j = 1, x; j <= cnt && (x = i * prime[j]) <= W; ++ j)
		{
			isnopr[x] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

int f[MaxN];
bool vis[MaxN];
int main()
{
	Pre();
	f[0] = f[1] = 0, f[2] = f[3] = 1;
    vis[0] = vis[1] = 0, vis[2] = vis[3] = 1;//递归的初始化条件
    //如果只有 0 或 1 个那就不用取了，0 步，必胜
    for (int i = 4; i <= W; ++ i)
    {
        bool flag = false;//判断是不是必胜方案
        for (int j = 1; j <= cnt && prime[j] <= i; ++ j)
			if (!vis[i - prime[j]]) { vis[i] = flag = true; break; }//寻找必胜方案
        if (!flag) vis[i] = 0;
        if (vis[i])
        {
        	int Mn = 1 << 30;
        	for (int j = 1; j <= cnt && prime[j] <= i; ++ j)
				if (!vis[i - prime[j]]) chkMin(Mn, f[i - prime[j]]);
			f[i] = Mn + 1;//如果必胜，在每种符合条件的情况里找一种步数最少的
		}
        else
        {
        	int Mx = 0;//若必败，则每一种情况都必败，无需判断
        	for (int j = 1; j <= cnt && prime[j] <= i; ++ j) chkMax(Mx, f[i - prime[j]]);
			f[i] = Mx + 1;//如果必败，直接找最多的
		}
    }
	int n; read(n);
	for (int i = 1, x; i <= n; ++ i) read(x), write(!vis[x] ? -1 : f[x], '\n', true);
	IO::flush();
	return 0;
}
