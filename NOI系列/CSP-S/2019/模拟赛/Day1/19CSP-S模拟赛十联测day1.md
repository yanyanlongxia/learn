[TOC]

# A. 分组

## title

[zhengruiOJ](http://zhengruioi.com/problem/954)

~~好像一般人看不到哈，贴个题面吧~~

Problem Statement

> 小 $D$ 正在招聘员工。
>
> 共有 $n$ 人报名了招聘，这些人被依次编号为 $1,2,···,n$ 。其中，第 $i$ 个人的工作经验为 $w_i$，薪水为 $s_i$ 。
>
> 小 $D$ 想要招聘 $2k$ 个人，并将这些人分为 k 组，每组两个人。
>
> 每组的两个人中，会有一个人为组长，而另一个人为组员。对于每个组而言，小 $D$ 都要求组长的工作经验不小于组员的工作经验。
>
> 此外，每个应聘者会有一个意愿 $p_i$ ，表示他应聘的岗位。若 $p_i=1$ ，则该应聘者应聘的是组长；若 $p_i=2$ ，则他应聘的是组员；若 $p_i=3$ ，则他既可以当组长又可以当组员。
>
> 小 $D$ 想要知道，在不改变意愿的情况下，是否可以招聘满足条件的 $2k$ 个人。如果可以，小 $D$ 还想要知道招聘的人薪水和的最小值。
>
> 但是小 $D$ 并不会，请你帮帮他。

Input Format
> 从标准输入读入数据。
>
> 第一行两个整数 $n,k$ ，表示应聘者个数以及小组个数。
>
> 接下来 $n$ 行，每行三个整数 $w_i,s_i,p_i$ ，依次表示每个人的工作经验，薪水，以及意愿。

Output Format
> 向标准输出输出答案。
> 如果无法做到，则输出一行一个整数 $-1$，否则输出最小总薪水。

Input
> 6 2
> 20 6 1
> 6 7 2
> 4 8 3
> 3 10 2
> 8 5 3
> 2
> 4 3 1

Output
> 22

Explanation
> 选择如下两组即可：
>
> - 组长：1号应聘者，组员：5号应聘者；
> - 组长：6号应聘者，组员：3号应聘者。

Constraints
> 对于所有测试数据，$1\leqslant n×k\leqslant 10^5,1\leqslant w_i,s_i\leqslant 10^9,1\leqslant p_i\leqslant 3$ 。
>
> - 子任务1（20分）：$n,k\leqslant10$；
> - 子任务2（20分）：$n,k\leqslant20$；
> - 子任务3（20分）：$n,k\leqslant500$；
> - 子任务4（20分）：$n,k\leqslant5000$；
> - 子任务5（20分）：无特殊限制。

## analysis

刚开始感觉是个贪心，那就开始想贪心策略了：排个序， 将 $p=1$ 和 $p=2$ 的分开，然后 $p=3$ 的都加入前面的那两个集合，之后进行匹配，检验是不是符合组长经验 $>$ 组员经验。

这是一个比较直观的思路，然而对于实现上，会有个问题，很困扰我，那就是转移比较困难，具体就体现在匹配的那一块儿。

然后，因为想到了匹配，我就想到了网络流，分类完之后，$源点s$ 连向 $i$ 容量为 $p_i$ ，$i+n$ 连向 $汇点t$ 容量为 $p_i$ ，然后组长集合中 $i$ 只要经验值大于组员集合中的 $j$ ，那么就从 $i$ 连向 $j+n$ ，容量为 $INF$ 。

感觉好像还行，样例挂了，分析一下发现，我没有办法保证我的最大流一定过了 $2k$ 条容量不为 $INF$ 的边，所以就 $gg$ 。

最后的结果是没交，爆零滚粗。

-----

~~划个分界线，开始正解啦~~

麻叶，意料之中，意料之外，是 $Dp$ 。

排序是必要的，但是怎么排，看自己的，我的排序是：以经验值 $w_i$ 为第一关键字从大到小，以意愿 $p_i$ 为第二关键字从小到大（和题解好像正好反了）。

然后我们设 $f[i][a][b]$ 示考虑了排序后的前 $i$ 个人，目前已经有 $a$ 个组配好了，还有 $b$ 个组只有组长的最小代价，然后按照意愿分三类进行状态转移，考虑当前的人是作为组长，加入一个已经有组员的组，还是作为组员新建一个组即可。

这样就完了？

好像忘了如果要招聘的人超过了来应聘的人（即 $2k>n$ ），必定无解。（该特判的时候一定要特判啊，省复杂度啊）

总复杂度为 $O(nk\sqrt{nk})$ 。

贴一下官方题解：


![](https://img2018.cnblogs.com/blog/1587478/201909/1587478-20190901105511733-425500241.png)

## code

```cpp
#include<bits/stdc++.h>

typedef long long ll;
const int maxn=1e5+10;
const ll INF=0x3f3f3f3f3f3f3f3fll;

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

struct Orz{int w,s,p;}o[maxn];
inline bool cmp(Orz a,Orz b)//和题解正好相反，无所谓了
{
	return a.w>b.w || (a.w==b.w && a.p<b.p);
}

ll f[2][250][250];//f[i][a][b]表示考虑了排序后的前 i 个人，目前已经有 a 个组配好了，还有 b 个组只有组长的最小代价
int main()
{
	int n,kk;read(n);read(kk);
	for (int i=1; i<=n; ++i) read(o[i].w),read(o[i].s),read(o[i].p);
	if (kk<<1>n) return puts("-1"),0;//需要招聘的人超过了来应聘的人，无解

	for (int i=1; i<=n; ++i)
	{
		if (o[i].p==2) o[i].p=3;
		else if (o[i].p==3) o[i].p=2;
	}
	std::sort(o+1,o+n+1,cmp);//按照经验值从大到小，先组长后组员的顺序排序
	memset(f,0x3f,sizeof(f));//初值
	f[0][0][0]=0;
	int x=1;//滚动数组
	for (int i=1; i<=n; ++i)
	{
		int lim1=min(i>>1,kk);//已经配好组的边界（赋初值）
		for (int j=0; j<=lim1; ++j)
		{
			int lim2=min(i-(j<<1),kk-j);//将要配好的组的边界（赋初值）
			for (int k=0; k<=lim2; ++k) f[x][j][k]=INF;
		}
		lim1=min((i-1)>>1,kk);//已经配好组的边界（转移）
		for (int j=0; j<=lim1; ++j)
		{
			int lim2=min(i-1-(j<<1),kk-j);//将要配好的组的边界（转移）
			for (int k=0; k<=lim2; ++k)
			{
				if (o[i].p==1 && j+k+1<=kk) chkMin(f[x][j][k+1],f[x^1][j][k]+o[i].s);//组长嘛，只能多开一组了
				else if (o[i].p==2)
				{
					if (j+k+1<=kk) chkMin(f[x][j][k+1],f[x^1][j][k]+o[i].s);//组员，这就考虑是多开一组给他
					if (k>0) chkMin(f[x][j+1][k-1],f[x^1][j][k]+o[i].s);//还是去填补以前没有配好的组
				}
				else if (o[i].p==3 && k>0) chkMin(f[x][j+1][k-1],f[x^1][j][k]+o[i].s);//通配符，就填补以前没有配好的组
				chkMin(f[x][j][k],f[x^1][j][k]);//也可能你试着配了一次，还没有原先的方案的代价小
			}
		}
		x^=1;
	}
	if (f[x^1][kk][0]==INF) f[x^1][kk][0]=-1;//无解
	write(f[x^1][kk][0],'\n');
	IO::flush();
	return 0;
}
```

# B. 折纸

## title

[zhengruiOJ](http://zhengruioi.com/problem/955)

Problem Statement

> 小 $D$ 正在折纸。
>
> 小 $D$ 现在有一张 $n\times m$ 的方格纸，每个方格有一个颜色，用小写字母表示。具体地，位于第 $i$ 行第 $j$ 列的方格颜色为 $c_{i,j}$ 。
>
> 小 $D$ 想要进行折纸。具体地，他可以选择一个水平或竖直的不穿过任何小方格内部的直线，并将整张纸沿这条线对折。并且在对折时，小 $D$ 要求在下面的那部分必须不小于上面的那部分。也就是说，我们把较小的那部分折到较大的那部分上面。但如果两部分一样大，那么向两个方向折都是允许的。
>
> 为了最终结果的美观，小 $D$ 要求每次折纸时，对应位置的颜色必须一样。
>
> 小 $D$ 想要知道，在若干次对折后，他最终可以折出多少种本质不同的结果。
>
> 我们认为两个结果是本质不同的，当且仅当他们的最下层在原方格纸中对应的区域不同。也就是说，颜色一样的两个结果可能是不同的。
>
> 但是小 $D$ 并不会，请你帮帮他。
>
> 注：你可以认为在一次折纸后，上下两部分会合成一张纸，即你不用考虑上面的部分在之后的折纸过程中，被折到下面那部分之间导致的不合法情况。

Input Format

> 从标准输入读入数据。
>
> 第一行两个整数 $n,m$，表示方格纸的大小。
>
> 接下来 $n$ 行，每行一个长度为 $m$ 的小写字母组成的字符串，表示第 $i$ 行所有方格的颜色。

Output Format

> 向标准输出输出答案。
>
> 输出一行一个整数表示答案。

Input

> 5 7
> baabbaa
> cbbccbb
> 4
> ababbab
> cabccba
> bccaacc

Output

> 2

Explanation

> 第一种结果是不折，第二种结果是沿第四、第五列之间对折。

Constraints

> 对于所有测试数据，$1\leqslant n\times m\leqslant 10^6$ 。
>
> - 子任务1（30分）：$n,m\leqslant 30$；
> - 子任务2（20分）：$n=1$；
> - 子任务3（20分）：$n,m\leqslant 1000$；
> - 子任务4（30分）：无特殊限制。

## analysis

二维 $manacher$ ？其实是一行一行处理，然后一列一列处理了，这道题实际上我没什么可以说的，因为比赛时我不会写，所以直接放掉了。

贴题解吧：

![](https://img2018.cnblogs.com/blog/1587478/201909/1587478-20190901105603051-1563819899.png)

## code

```cpp
#include<bits/stdc++.h>

typedef long long ll;
const int maxn=2e6+10;

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

char s[maxn],tt[maxn];
std::string o[maxn];
inline int manacher(int *P,char *c,int L)
{
	int len=0;
	s[0]='(';
	for (int i=1; i<=L; ++i)
	{
		s[++len]='#';
		s[++len]=c[i];
	}
	s[++len]='#', s[++len]=')';
	int mx=0, id=0;
	for (int i=1; i<len; ++i)
	{
		if (i<mx) P[i]=min(mx-i,P[(id<<1)-i]);
		else P[i]=1;
		while (s[i+P[i]]==s[i-P[i]]) ++P[i];
		if (i+P[i]>mx) mx=i+P[i], id=i;
	}
	return len;
}

int HL[maxn],HR[maxn],WL[maxn],WR[maxn],t[maxn];
int main()
{
	int n,m;read(n);read(m);
	for (int i=1; i<=n; ++i) std::cin>>o[i];

	for (int i=1; i<=n-1; ++i) HL[i]=HR[i]=1;
	for (int i=1; i<=m-1; ++i) WL[i]=WR[i]=1;

	for (int i=1; i<=n; ++i)
	{
		for (int j=1; j<=m; ++j) tt[j]=o[i][j-1];
		int len=manacher(t,tt,m)-3;
		int mx=1;
		for (int j=3; j<=len; j+=2)
		{
			if (j-t[j]+1<=mx) mx=j;
			else WL[j>>1]=0;
		}
		int mn=len+2;
		for (int j=len; j>=3; j-=2)
		{
			if (j+t[j]-1>=mn) mn=j;
			else WR[j>>1]=0;
		}
	}
	ll ansW=0;
	int sum=0;
	WL[0]=1, WR[m]=1;
	for (int i=0; i<=m; ++i) sum+=WR[i];
	for (int i=0; i<=m; ++i)
	{
		if (WR[i]) --sum;
		if (WL[i]) ansW+=sum;
	}

	std::swap(n,m);

	for (int i=1; i<=n; ++i)
	{
		for (int j=1; j<=m; ++j) tt[j]=o[j][i-1];
		int len=manacher(t,tt,m)-3;
		int mx=1;
		for (int j=3; j<=len; j+=2)
		{
			if (j-t[j]+1<=mx) mx=j;
			else HL[j>>1]=0;
		}
		int mn=len+2;
		for (int j=len; j>=3; j-=2)
		{
			if (j+t[j]-1>=mn) mn=j;
			else HR[j>>1]=0;
		}
	}
	ll ansH=0;
	sum=0;
	HL[0]=1, HR[m]=1;
	for (int i=0; i<=m; ++i) sum+=HR[i];
	for (int i=0; i<=m; ++i)
	{
		if (HR[i]) --sum;
		if (HL[i]) ansH+=sum;
	}

	write(ansW*ansH,'\n');
	IO::flush();
	return 0;
}
```

# C. 集合

## title

[zhengruiOJ](http://zhengruioi.com/problem/956)

Problem Statement

> 小 $D$ 正在研究集合。
>
> 小 $D$ 想要维护一个可重集合 $S$ 。
>
> 小 $D$ 想要支持如下四种操作：
>
> - 在 $S$ 中插入一个元素 $x$ ；
> - 删除 $S$ 中某个元素 $x$ 的一次出现，保证 $x\in S$；
> - 给S中的所有元素加上 $1$；为了避免整数溢出，小 $D$ 在每次加法后会将所有数字对 $2^{30}$ 取模。
> - 给S中的所有元素异或上 $x$。
>
> 小 $D$ 想要知道，所有操作都进行完后 $S$ 中的所有元素。
>
> 但是小 $D$ 并不会，请你帮帮他。

Input Format

> 从标准输入读入数据。
>
> 第一行两个整数 $n,q$，表示 $S$ 中初始的元素个数，以及小 $D$ 的操作次数。
>
> 第二行 $n$ 个空格隔开的整数 $a_1,a_2,···,a_n$ ，表示 $S$ 中的初始元素。
>
> 接下来 $q$ 行每行 1 或 2 个整数，表示一次操作：
>
> - 1 x：插入一个元素 $x$ ；
> - 2 x：删除元素 $x$ 的一次出现
> - 3：给所有元素 $+1$；
> - 4 x：给所有元素异或上 $x$ 。

Output Format
>向标准输出输出答案。
>
>输出一行若干个空格隔开的整数，表示最终 $S$ 中的元素。你需要按照从小到大的顺序进行输出。

Input
>2 4
>5 10
>6
>3
>1 6
>4 2
>2 4

Output
>4 9

Explanation
>集合S的变化如下：
>
>初始时，$S=\{5,10\}$ 。
>
>- 第一次操作后，$S=\{6,11\}$；
>- 第二次操作后，$S=\{6,6,11\}$；
>- 第三次操作后，$S=\{4,4,9\}$；
>- 第四次操作后，$S=\{4,9\}$；


Constraints
>对于所有测试数据，$1\leqslant n,q\leqslant 3×10^5，0\leqslant a_i,x <2^{30}$。
>
>- 子任务1（25分）：$n,q\leqslant 5000$；
>- 子任务2（15分）：没有操作 3；
>- 子任务3（15分）：没有操作 4；
>- 子任务4（25分）：$n,q\leqslant 10^5$；
>- 子任务5（20分）：无特殊限制。

## analysis

子任务 $1$ ：

大暴力，模拟即可。

子任务 $2\& 3$ ：

![](https://img2018.cnblogs.com/blog/1587478/201909/1587478-20190901105316989-1116156743.png)

满分做法：

看到异或的时候，就想到要不要用 $Trie$ 啊，然而脑子真蠢，最后没写，哎。

![](https://img2018.cnblogs.com/blog/1587478/201909/1587478-20190901105334035-1158693605.png)

## code

~~先放一下我水了 $25pts$ 的大模拟吧~~

```cpp
#include<bits/stdc++.h>

typedef long long ll;
const int maxn=3e5+10;
const ll mod=1ll<<30;

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

ll a[maxn];
int main()
{
	int n,q;read(n);read(q);
	for (int i=1; i<=n; ++i) read(a[i]);
	int cnt=n;
	while (q--)
	{
		int opt;read(opt);
		ll x;
		if (opt==1)
		{
			read(x);a[++cnt]=x;
		}
		else if (opt==2)
		{
			read(x);
			for (int i=1; i<=cnt; ++i)
				if (a[i]==x)
				{
					for (int j=i; j<=cnt; ++j) a[j]=a[j+1];
					--cnt;
					break;
				}
		}
		else if (opt==3)
		{
			for (int i=1; i<=cnt; ++i) a[i]=(a[i]+1)%mod;
		}
		else
		{
			read(x);
			for (int i=1; i<=cnt; ++i) a[i]^=x;
		}
	}
	std::sort(a+1,a+cnt+1);
	for (int i=1; i<=cnt; ++i) write(a[i],' ');
	IO::flush();
	return 0;
}
```

~~正解~~

```cpp
#include<bits/stdc++.h>

const int maxn=1e6+10,maxm=2e7+10;

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

int son[maxm][2],num[maxm],cnt;//num[i] 表示节点 i 出现的次数
inline void add(int x,int k)
{
	int now=0;
	for (int i=0; i<30; ++i)
	{
		int c=x>>i&1;
		if (!son[now][c]) son[now][c]=++cnt;
		now=son[now][c];
	}
	num[now]+=k;//是当前这个节点的次数
}

int seq[35],lazy;
inline void Change()
{
	int now=0, len=0, full=(1u<<30)-1^lazy;
	for (int i=0; i<30; ++i)//找到一条全为 1 的链
	{
		seq[len++]=now;
		now=son[now][full>>i&1];
		if (!now) break;
	}
	for (int i=0; i<len; ++i) std::swap(son[seq[i]][0],son[seq[i]][1]);//然后把他们的左右儿子翻转，相当于 +1 了
}

int ans[maxn],tot;
inline void dfs(int x,int val,int deep)
{
	for (int i=0; i<num[x]; ++i) ans[++tot]=val^lazy;
	for (int i=0; i<2; ++i)
		if (son[x][i]) dfs(son[x][i],val|(i<<deep),deep+1);
}

int main()
{
	int n,q;read(n);read(q);
	for (int i=1,x; i<=n; ++i) read(x), add(x,1);
	for (int i=1,opt,x; i<=q; ++i)
	{
		read(opt);
		if (opt==1) read(x), add(x^lazy,1);
		else if (opt==2) read(x), add(x^lazy,-1);
		else if (opt==3) Change();
		else read(x), lazy^=x;
	}
	dfs(0,0,0);
	std::sort(ans+1,ans+tot+1);
	for (int i=1; i<=tot; ++i) write(ans[i],' ');
	IO::flush();
	return 0;
}
```

# summary

1. 学会对拍。
2. 比赛时间规律化：前半小时看题，想算法；两个小时写暴力，写正解；一个小时对拍。希望在 $CSP$ 之前可以养成。
3. 暴力有时候还是挺顶事儿的，嘻嘻。