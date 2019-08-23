# title

[BZOJ 4896](https://lydsy.com/JudgeOnline/problem.php?id=4896)

[LUOGU 5335](https://www.luogu.org/problem/P5335)

简化题意：

> $n$ 个学生选课。$n$ 个事件为下面的三种之一：
>
> 1. 一个姓名为 $S$ 的学生选了 $X$ 老师的课；
> 2. 一个姓名为 $S$ 的学生退了 $X$ 老师的课；
> 3. 询问最早在第几个事件之后，姓名以 $S$ 为前缀的学生数量超过了 $(a*|ANS|+b)\%c$，$|ANS|$ 表示上次查询事件的答案的绝对值，如果当前是第一次查询，则 $|ANS|=0$；如果任何时刻都没有超过该值，则答案为 $-1$。

# analysis

询问有多少个字符串前缀超过 $tmp$，那么应该要用 $Trie$ 了。

针对于三种操作：

1. 将这个字符串添加到 $Trie$ 中；
2. 将这个字符串从 $Trie$ 中删除；
3. 在 $Trie$ 中暴力扫一遍即可。

好像...没什么难度？

# code

```cpp
#include<bits/stdc++.h>

typedef long long ll;
const int maxn=1e6+10;

namespace IO
{
	char buf[1<<15],*fs,*ft;
	inline char getc() { return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++; }
	template<typename T>inline void read(T &x)
	{
		x=0;
		T f=1, ch=getchar();
		while (!isdigit(ch) && ch^'-') ch=getchar();
		if (ch=='-') f=-1, ch=getchar();
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
		x*=f;
	}

	char Out[1<<24],*fe=Out;
	inline void flush() { fwrite(Out,1,fe-Out,stdout); fe=Out; }
	template<typename T>inline void write(T x)
	{
		if (!x) *fe++=48;
		if (x<0) *fe++='-', x=-x;
		T num=0, ch[20];
		while (x) ch[++num]=x%10+48, x/=10;
		while (num) *fe++=ch[num--];
		*fe++='\n';
	}
}

using IO::read;
using IO::write;

int ans;
namespace Trie
{
	struct Orz
	{
		int son[27];
		int ed;
		std::vector<int>v;
	}a[maxn]; int cnt=0;

	inline void add(char *s,int id)
	{
		int len=strlen(s+1), now=0;
		for (int i=1; i<=len; ++i)
		{
			int c=s[i]-'a';
			if (!a[now].son[c]) a[now].son[c]=++cnt;
			now=a[now].son[c];
			++a[now].ed;
			if (a[now].ed>(int)a[now].v.size()) a[now].v.push_back(id);
		}
	}

	inline void del(char *s)
	{
		int len=strlen(s+1), now=0;
		for (int i=1; i<=len; ++i)
		{
			int c=s[i]-'a';
			now=a[now].son[c];
			--a[now].ed;
		}
	}

	inline ll query(char *s,ll k)
	{
		int len=strlen(s+1), now=0;
		for (int i=1; i<=len; ++i)
		{
			int c=s[i]-'a';
			now=a[now].son[c];
			if ((int)a[now].v.size()<=k) return -1;
		}
		return a[now].v[k];
	}
}
using namespace Trie;

char s[61];
int main()
{
	int n;read(n);
	ll a,b,c;
	for (int i=1,opt; i<=n; ++i)
	{
		read(opt);scanf("%s",s+1);
		if (opt==1) add(s,i);
		if (opt==2) del(s);
		if (opt==3)
		{
			read(a);read(b);read(c);
			ll num=(a*abs(ans)+b)%c;
			ans=query(s,(int)num);
			write(ans);
		}
	}
	IO::flush();
	return 0;
}
```