[TOC]

# A. 有趣的数

## title

[zhengruioi](http://zhengruioi.com/problem/1000)

题意：

>定义一个有趣的数为：对于一个正整数，对于其所有的数位，**当且仅当它恰好有一位与其他位不同**，则称这个数为有趣的数。
>
>比如：555655，24444，7787，110 都为有趣的数，而 6996，4444 都不是。
>
>想要知道在 $[L,R]$ 中有多少个有趣的数。
>
>对于 $60$ 的数据，$100\leqslant L\leqslant R\leqslant 10^7$ 。
>
>对于 $100$ 的测试点，$100\leqslant L\leqslant R\leqslant 10^{16}$ 。

## analysis

当时和 $czd$ 一起开题，感觉还是挺好的，哈哈。

当时只想打打部分分就可以了，于是瞄准 $60pts$ 就开始暴力判定了。

我的想法：对于 $i(L\leqslant i\leqslant R)$ ，将它的每一位数字提取出来，然后从头遍历到第一个与之前不同的数字，记录它的位置（当时记录的是权值，应该都一样吧），从尾遍历到第一个与之前不同的树子，记录它的位置，如果两个位置相同，那么合法。

然而不知道出什么问题了，挂成了 $10pts$ ，之后也没有再去研究，之后再看看吧。

正解，真的是构造，构造出所有的合法的数字，然后判断是否属于查询区间 $[L,R]$ 。

因为这些合法数字由两部分构成：特殊的数字，其他的数字，枚举这两个部分的话，时间复杂度为 $O(9^2)$ 。

然后枚举这个数字的位数（最多也只有 $17$ 位，所以时间复杂度为 $O(17^2)$，因为这个位上也要判断是特殊数字，还是其他数字，也是需要一层循环的）。

综合起来，总时间复杂度为 $O(17^2\times 9^2)$ ，低的不行。

## code

```cpp
#include<bits/stdc++.h>

typedef long long ll;

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
	template<typename T>inline void write(T x,char str)
	{
		if (!x) *fe++=48;
		if (x<0) *fe++='-', x=-x;
		T num=0, ch[20];
		while (x) ch[++num]=x%10+48, x/=10;
		while (num) *fe++=ch[num--];
		*fe++=str;
	}
}

using IO::read;
using IO::write;

ll bin[20];
int main()
{
	ll l,r; read(l), read(r);
	bin[0]=1;
	for (int i=1; i<=18; ++i) bin[i]=bin[i-1]*10;//10 的阶乘
	ll ans=0;
	for (int i=0; i<=9; ++i)//其他的数字
		for (int j=0; j<=9; ++j)//特殊的数字
		{
			if (i==j) continue;
			for (int k=3; k<=18; ++k)//枚举这个数的位数
				for (int t=1; t<=k; ++t)//特殊数字的位置
				{
					if ((t==k && !j) || (t^k && !i)) continue;
					ll num=0;//构造的数字
					for (int p=1; p<=k; ++p)//特殊数字的位置
						if (p^t) num+=i*bin[p-1];
						else num+=j*bin[p-1];
					if (l<=num && num<=r) ++ans;//如果属于这个区间则合法
				}
		}
	write(ans,'\n');
	IO::flush();
	return 0;
}
```

# B. 欢乐ABC

## title

[zhengruioi](http://zhengruioi.com/problem/1001)

题意：

> 随手在纸上用大写字母 $A−Z$ 写下了一个字符串，问题：在这个字符串中，有多少个**非空连续子串**，其中 $A$ 字符的数量，$B$ 字符的数量和 $C$ 字符的数量三个量相等。

## analysis

又是一道与数位有关的问题。

然后我俩就直接敲 $70pts$ 暴力了，被题目坑了，以为字符串只有 $ABC$ 三个字母，原来是 $A-Z$ 这 $26$ 个字母，坑，要不然我的循环变量范围也不会写错啊， $70pts$ 挂成 $10pts$ 也是没谁了（一会这个代码放一下）。

正解挺神奇的，可以发现当 $S[i..j]$ 是一个合法的非空子串时，当且仅当 $A[i−1]−B[i−1]==A[j] − B[j]$ 且 $B[i−1]−C[i−1]==B[j]−C[j]$ ，那么对于所有的 $i(0\leqslant i\leqslant n)$ ，把 $(A[i]−B[i],B[i]−C[i])$ 看成一个二元组，然后统计有多少对相同的组合即可。

用 $map$ 边加边统计，或者也可以排好序以后看连续相等的，然后算进答案里面。

## code

$70pts$

```cpp
#include<bits/stdc++.h>

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
	template<typename T>inline void write(T x,char str)
	{
		if (!x) *fe++=48;
		if (x<0) *fe++='-', x=-x;
		T num=0, ch[20];
		while (x) ch[++num]=x%10+48, x/=10;
		while (num) *fe++=ch[num--];
		*fe++=str;
	}
}

using IO::read;
using IO::write;

char str[maxn];
int cnt[maxn][3];
int main()
{
	scanf("%s",str+1);
	int n=strlen(str+1);

	for (int i=1; i<=n; ++i)
		if (str[i]=='A') ++cnt[i]['A'-'A'];
		else if (str[i]=='B') ++cnt[i]['B'-'A'];
		else if (str[i]=='C') ++cnt[i]['C'-'A'];
	
	for (int i=1; i<=n; ++i) cnt[i][0]+=cnt[i-1][0], cnt[i][1]+=cnt[i-1][1], cnt[i][2]+=cnt[i-1][2];

	int ans=0;
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=i; ++j)
		{
			if ((cnt[i][0]-cnt[j-1][0]) == (cnt[i][1]-cnt[j-1][1]) && (cnt[i][1]-cnt[j-1][1])== (cnt[i][2]-cnt[j-1][2])) ++ans;//判断三个数相等一定要写成判断两两相等，哭
		}

	write(ans,'\n');
	IO::flush();
	return 0;
}
```

$100pts$

```cpp
#include<bits/stdc++.h>

#define mp std::make_pair
typedef std::pair<int,int> pii;
const int maxn=1e6+10;

namespace IO
{
	char Out[1<<24],*fe=Out;
	inline void flush() { fwrite(Out,1,fe-Out,stdout); fe=Out; }
	template<typename T>inline void write(T x,char str)
	{
		if (!x) *fe++=48;
		if (x<0) *fe++='-', x=-x;
		T num=0, ch[20];
		while (x) ch[++num]=x%10+48, x/=10;
		while (num) *fe++=ch[num--];
		*fe++=str;
	}
}

using IO::write;

char str[maxn];
std::map<pii,int> M;
int main()
{
	scanf("%s",str+1);
	int n=strlen(str+1), B_A=0, C_A=0, ans=0;
	M[mp(0,0)]=1;
	for (int i=1; i<=n; ++i)
	{
		if (str[i]=='A') --B_A, --C_A;
		if (str[i]=='B') ++B_A;
		if (str[i]=='C') ++C_A;
		ans+=M[mp(B_A,C_A)];
		++M[mp(B_A,C_A)];
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
```

# C. 数位问题

## title

[zhengruioi](http://zhengruioi.com/problem/1002)

题意：

>一个有趣的数位问题：
>
>给定一个数由 $d_i$ 个数字 $i(1\leqslant i\leqslant 9)$ 和若干个 $0$（可以没有 $0$ ）组成，数字可以按照任意顺序排列，最终组成一个非负整数。
>
>现在小强想问如果他想让这个数被 $11$ 整除，那这个数**最少**要多少位。

## analysis

呵呵，直接告诉你这是个数位问题，不少小伙伴说：数位 $Dp$ ，一眼正解。

但是我没写这题，因为怎么都感觉不可写，忘了判无解的 $10pts$ 有些亏啊。

正解上的 $Dp$ 好像有些冗余，因为我看的那篇代码的状态是这样定义的：

$f[k][l]$ 表示放了 $k$ 个数，这些数的和除以 $11$ 的余数为 $l$ ，这种情况可行不可行。

然后我感觉这种写法还挺好的，时间复杂度大概也是 $O(T·9·11·(\sum d_i)^2)$ 。

## code

```cpp
#include<bits/stdc++.h>

const int maxn=110;

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
	template<typename T>inline void write(T x,char str)
	{
		if (!x) *fe++=48;
		if (x<0) *fe++='-', x=-x;
		T num=0, ch[20];
		while (x) ch[++num]=x%10+48, x/=10;
		while (num) *fe++=ch[num--];
		*fe++=str;
	}
}

using IO::read;
using IO::write;

template<typename T>inline bool chkMin(T &a,const T &b) { return a>b ? (a=b, true) : false; }
template<typename T>inline bool chkMax(T &a,const T &b) { return a<b ? (a=b, true) : false; }
template<typename T>inline T min(T a,T b) { return a<b ? a : b; }
template<typename T>inline T max(T a,T b) { return a>b ? a : b; }

int d[maxn],g[maxn];
int f[maxn][maxn];
int main()
{
	int T;read(T);
	while (T--)
	{
		memset(f,0,sizeof(f));
		for (int i=1; i<=9; ++i) read(d[i]);
		int cnt=0;
		f[0][0]=1;
		for (int i=1; i<=9; ++i)
			for (int j=1; j<=d[i]; ++j)
			{
				for (int k=cnt; k>=0; --k)
				{
					for (int l=0; l<=10; ++l) g[l]=f[k][l], f[k][l]=0;
					for (int l=0; l<=10; ++l) f[k+1][(l+i)%11]|=g[l], f[k][(l-i+11)%11]|=g[l];
				}
				++cnt;
			}
		int ans=0x3f3f3f3f;
		for (int i=0; i<=cnt; ++i)
			if (f[i][0]) chkMin(ans,max(i,cnt-i)*2-1);
		if (ans==0x3f3f3f3f) ans=-1;
		if (!ans) ans=1;
		write(ans,'\n');
	}
	IO::flush();
	return 0;
}
```

# D. 打游戏

## title

[zhengruioi](http://zhengruioi.com/problem/1003)

题意：

>小强在游戏里打怪。有一次，他一下子遇到了 $n$ 个怪物。 每个怪物有一个生命值，第 $i$ 个怪物的生命值是 $h_i$ 。而小强除了生命值之外，还有一个属性是魔法值 $m$ 。
>
>小强和怪物们依次行动。每一回合，小强先行动，然后怪物们同时行动。小强每次可以选择以下行动之一：
>
>• 普通攻击：令某个怪物的生命值减少 $1$ 。
>
>• 重击：消耗 $1$ 魔法值，令某个怪物的生命值减少 $2$ 。
>
>• 群体攻击：消耗 $1$ 魔法值，令全体怪物的生命值减少 $1$ 。
>
>而每个存活的怪物（生命值严格大于 $0$ ）每次会令小强的生命值减少 $1$ 。假设小强有足够的生命值来维持存活，小强想知道自己至少需要被消耗多少生命值才能击败所有怪物

## analysis

玩过游戏的人都知道（欺负我没玩过这种打怪游戏），先把生命值从小到大排好序，然后依次去打，如果当前怪的生命值为 $1$ 或者场上不止两个怪，必然放群攻，不然放重击。如果魔法值用完了，就只能一个一个用普攻打了。

感觉这好像是打游戏的真理？

所以这道题到底考察了什么？大模拟的能力。

对此，我是死掉了。

## code

```cpp
#include<bits/stdc++.h>

typedef long long ll;
const int maxn=1e5+10;

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
	template<typename T>inline void write(T x,char str)
	{
		if (!x) *fe++=48;
		if (x<0) *fe++='-', x=-x;
		T num=0, ch[20];
		while (x) ch[++num]=x%10+48, x/=10;
		while (num) *fe++=ch[num--];
		*fe++=str;
	}
}

using IO::read;
using IO::write;

ll ans;
int h[maxn];
int main()
{
	int n,m;
	read(n);read(m);
	for (int i=1; i<=n; ++i) read(h[i]);
	std::sort(h+1,h+n+1);//从小到大排序
	int cnt=n;
	for (int i=1; i<=m; ++i)//先放技能
	{
		if (!cnt) break;//没怪了，走人
		if (cnt>2)//如果场上不止两个怪，放群攻
		{
			for (int j=1; j<=n; ++j)
			{
				--h[j];
				if (!h[j]) --cnt;//死了一个
			}
			ans+=cnt;//没死的都攻击
		}
		else//不然就
		{
			h[n-cnt+1]-=2;//魔法攻击
			if (!h[n-cnt+1]) --cnt;
			else if (h[n-cnt+1]<0) --cnt, --i;
			ans+=cnt;//没死的都攻击
		}
	}
	for (int i=1; i<=n; ++i)//然后一个一个普通攻击
		if (h[i]>0) ans+=(1ll*(n-i+1)*(h[i]-1)+n-i);//i 之后的 (n-i+1) 个怪都可以坚持 (h[i]-1) 个回合；然后就是当前回合，在你还没开始打 i 的时候，后面的怪都会先给你伤害（算是上一回合打死 i-1 的时候的伤害）
	write(ans,'\n');
	IO::flush();
	return 0;
}
```

# summary

这场比赛的总结就是暴力别挂，一切好说， $130pts$ 挂成 $20pts$ ，真的很伤心，哎。

之前伤心的事就那样吧，我也确实不想很拘泥于失望之中。