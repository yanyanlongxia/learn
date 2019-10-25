#include <bits/stdc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

#define DeBug(x) std::cout << #x << " = " << x << std::endl

const int MaxN = 5e2 + 10;

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

char s[MaxN];
int main()//这道题的思路是绝对能想得到的，结果被卡到了自己的思路上面，好不甘心啊，但只能多多历练了
{
	int T; read(T);
	while (T --)
	{
		scanf("%s", s + 1);
		int n = strlen(s + 1);
		bool good[27] = {};
		for (int i = 0; i <= n;)
		{
			int j = i;
			while (j <= n && s[i] == s[j]) ++ j;
			if ((j - i) & 1) good[s[i] - 'a' + 1] = true;//判断连续的元素数量是奇还是偶，比较稳妥了，像我之前的思路真 sb
			i = j;
		}
		for (int i = 1; i <= 26; ++ i)
			if (good[i]) *IO::fe++ = i + 'a' - 1;
		*IO::fe++ = '\n';
	}
	IO::flush();
	return 0;
}
//hack： aaabaaa，所以我完美死掉
//char s[MaxN];
//int cnt[27];
//int main()
//{
//	int T; read(T);
//	while (T --)
//	{
//		scanf("%s", s + 1);
//		int n = strlen(s + 1);
//		for (int i = 1; i <= 26; ++ i) cnt[i] = 0;
//		for (int i = 1; i <= n; ++ i) ++ cnt[s[i] - 'a' + 1];
//		for (int i = 1; i <= 26; ++ i)
//			if (cnt[i] & 1) *IO::fe++ = i + 'a' - 1;//猜想了一个结论：出现次数为奇数次的字母一定是答案集合里的
//			else//然后26个字母一个一个判断，如果出现次数为偶数次的，我查看一下这个字母是否有连续两个相同
//			{
//				bool flag = 1;
//				for (int j = 1; j < n; ++ j)
//					if ((s[j] - 'a' + 1 == i) && (s[j + 1] - 'a' + 1 == i)) flag = 0;
//				if (flag && cnt[i] > 0) *IO::fe++ = i + 'a' - 1;
//			}
//		*IO::fe++ = '\n';
//	}
//	IO::flush();
//	return 0;
//}
