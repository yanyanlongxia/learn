#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

#define fi first
#define se second
#define mp std::make_pair
typedef std::pair<int, int> pii;
typedef long long ll;
const int MaxN = 1e6 + 10;

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

std::priority_queue<pii, std::vector<pii>, std::greater<pii> > a;//定义一个事件集合 a 储存 <t,id> 表示：在 t 时刻，第 id 个人会想接水
std::queue<int> b;//当前在队列中的人
std::set<int> s;//想进队列的人（等待状态 want）
ll ans[MaxN];
int main()
{
	int n, p; read(n, p);
	for (int i = 1, x; i <= n; ++ i) read(x), a.push(mp(x, i));
	ll now = 0;//当前时间
	for (int i = 1; i <= n; ++ i)//每一次处理事件时（以 p 为梯度的处理）
        {
            if (b.empty() && s.empty()) now = a.top().fi;
            now += p;
            while (!a.empty() && a.top().fi <= now)
            {
                if (b.empty() || a.top().se < b.back()) b.push(a.top().se);//或者当前事件的 id 小于队列末尾的人的 id ，则 push 进队列（编号比队列末尾的人小，说明上一次等待状态的人延续下来，他们的编号一定小于当前编号，所以当前第一个接水的是当前编号）
                else s.insert(a.top().se);//否则 insert 到 want 中
                a.pop();
            }
            ans[b.front()] = now, b.pop();
            if (b.empty() && !s.empty()) b.push(*s.begin()), s.erase(s.begin());//若队列为空，则 push 进队列
        }
        for (int i = 1; i <= n; ++ i) write(ans[i], ' ', true);
        IO::flush();
	return 0;
}
