[TOC]

# A. 序列

## title

[zhengruioi](http://zhengruioi.com/problem/996)

题意：

> 给出一个长度为 $n$ 的整数序列 ，要求删掉一个连续子串后序列中没有相同元素 ， 请问至少要删掉多长的子串 ？

## analysis

只说一些需要注意的东西了，感冒，精神状态不是很好。

大概这题的定位估计是 $D1T1$ 吧，我没有 $A$ ，虽说精神差导致放弃，但是还是说明我可能思考不够，码力不足。

题解没看懂，找了份代码学习，最后觉得差不多。

一些东西写在注释里了，对于这道题，我更想说的是： **抓住灵光一闪的思路，说不定就 $A$ 了** 。

（缘由：今天上午头沉瞌睡 ~~都是感冒药惹的祸~~ ，又想订正昨天的题，所以就想着瞎打打算了，开 $T1$ 的时候，想着我直接离散去重，然后查原连续区间是否有重复元素好了，然而没写，跑去写了个假 $Dp$ ，爆了。） 

## code

```cpp
#include<bits/stdc++.h>

const int maxn=1e3+10;

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

int a[maxn],b[maxn],m[maxn],tot,ans=0x3f3f3f3f;
int main()
{
	int n;read(n);
	for (int i=1; i<=n; ++i) read(a[i]), b[i]=a[i];

	std::sort(b+1,b+n+1);
	int k=std::unique(b+1,b+n+1)-b-1;//可以先通过离散去重找到目标序列
	for (int i=1; i<=n; ++i)
	{
		a[i]=std::lower_bound(b+1,b+k+1,a[i])-b;
		if (++m[a[i]]==2) ++tot;//标记出现次数大于 1 的元素的数量
	}

	if (!tot) return puts("0"),0;//没有的话就不需要了
	for (int i=1; i<=n; ++i)
	{
		memcpy(b,m,sizeof(b));//原序列元素出现次数不能被改变
		int x=tot;//原出现两次的元素个数不能被改变
		for (int j=i; j<=n; ++j)//查看区间 [i,j] 中是否存在合法情况
			if (--b[a[j]]==1)//即这个元素正好出现两次
				if (!--x) { chkMin(ans,j-i+1); break; }//并且是最后一个，那么这个区间对答案有贡献
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
```

# B. 数字

## title

[zhengruioi](http://zhengruioi.com/problem/997)

题意：

>给出两个整数 $n,m$
>
>求 $1\sim n$ 的所有整数中，能被 $m$ 整除的整数的个位数字之和。

## analysis

数学题？找规律题。

不过我好像没费啥大劲儿就基本搞出了规律，同上面原因，我在处理留下来的不够分成一大块的那一部分忘记了处理，导致样例都挂了，然后瞌睡死了，就赶紧写了个 $20pts$ 暴力交上去，眯了会儿。

然后就不想打了，去订正昨天的题了（更是一次快要...的节奏）。

规律？我以为都知道，不想说了。

要不说一下？其实挺显然的，你会发现个位数字相加，其实到最后也就是 $m$ 的 $1\sim 10$ 倍的个位数的和了，所以只需要处理这个就好了，然后看 $n$ 有几个这样的大块，乘一下，然后处理一下剩下的分成一大块的那一部分（只能暴力扫了）。

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

int main()
{
	int T;read(T);
	while (T--)
	{
		ll n,m;read(n);read(m);
		ll b=n/m, c=b/10, d=b-c*10;//循环块大小，整块数量，散块大小
		ll ans=0;
		for (int i=1; i<=10; ++i) ans+=i*m%10;
		ans=ans*c;
		for (int i=1; i<=d; ++i) ans+=i*m%10;
		write(ans,'\n');
	}
	IO::flush();
	return 0;
}
```

# C. 背包

## title

[zhengruioi](http://zhengruioi.com/problem/998)

题意：

>有一个背包和 $n$ 个物品，要把某些物品彼此压着放在背包里 。
>
>背包最大承重为 $S$ 。
>
>已知第i个物品放上去的时间 $in_i$ ，拿走的时间 $out_i$ ，重量 $w_i$ ，承重 $s_i$ ， 价值 $v_i$ ，$in_i<out_i$
>
>对于同一时刻，有多个物品进出的话，顺序任意。
>
>如果将一个物品放入背包，必须满足以下要求 ：
>
>- 在 $in$ 时间进，放在最上面。
>- $out$ 时间出，出的时候他在最上面并且得到价值 $v$ 。
>- 当他在背包内时，他上方的物品的重量必须时刻小于等于 $s_i$ 。
>
>它也可以不放入背包 ，则得不到价值 $v$
>
>问你可以得到的最大价值。

## analysis

想都不用想，这题 $Dp$ 。

然后愁了，和我学过的背包没一个像的呀？

不由得想起 $xz$ 说过的话，背包是一类很好的 $Dp$ 模型，到后面也许不会有这么明确的有定义的模型，但是你如果理解了它的规则，照样可以用背包思维解决。（不是原话）

这道题中，一个物品有五个信息需要维护，对答案有贡献的则只有当这个物品被拿出去的时候，才会贡献 $v_i$ 。

所以其实统计 $v_i$ 很容易，关键是其它的信息所参与的答案贡献集合。

来想想我们该怎么定义状态，可以比较好的把剩余信息包含在内？（蒟蒻在此滚粗）

**设 $f[i][j]$ 表示 $i$ 以及 $i$ 上面的物品在所有时刻中最大重量为 $j$ 时的最大收益** 。

都包含在内了。然后怎么转移？

这个转移是需要借助些东西的，因为要枚举所有 $i$ 上面的所有物品，计算出时刻 $i$ 之前的物品的最大价值，然后进行转移。

应算不太好，把这个 **时刻 $i$ 之前的物品的最大价值** 定义为 $g[i]$ ，好办多了。

这样转移就有了：
$$
f[i][w]=g[nowtime]+v_i
$$


结合上面的定义，应该很明确了。

$g[i]$ 的转移挺麻烦的，不是很想写，有种贪心的感觉，所以这个地方看下代码。

## code

```cpp
#include<bits/stdc++.h>

const int maxn=505,maxk=1e3+10;

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

struct Orz{int in,out,w,s,v;}o[maxn];
inline bool cmp(Orz a,Orz b)
{
	return a.out<b.out || (a.out==b.out && a.in>b.in);
}

int f[maxn][maxk],g[maxk];//表示 i 以及 i 上面物品在所有时刻中最大重量为 j 时的最大收益
int main()
{
	int n,S,nowt=0,noww=0;
	read(n);read(S);
	for (int i=1; i<=n; ++i) read(o[i].in),read(o[i].out),read(o[i].w),read(o[i].s),read(o[i].v);
	o[++n]=(Orz){0,n<<1,0,S,0};
	std::sort(o+1,o+n+1,cmp);//按照拿走时间从小到大排（相等则放上去时间从大到小排），保证这个物品上方的物品一定在他前面

	for (int i=1; i<=n; ++i)//枚举物品
		for (int w=o[i].w; w<=S; ++w)//枚举空间（已经放进背包里）
		{
			nowt=o[i].in;//现在的时间
			g[nowt]=0;//表示时刻 i 之前物品的最大收益
			noww=min(w-o[i].w,o[i].s);//承重能力，第三条规定
			for (int j=1; j<i; ++j)//枚举 i 上面的物品
				if (o[j].in>=o[i].in)
				{
					while (nowt<o[j].out) ++nowt, g[nowt]=g[nowt-1];
					chkMax(g[nowt],g[o[j].in]+f[j][noww]);//计算出最大收益
				}
			f[i][w]=g[nowt]+o[i].v;//最后把它拿出来，获得价值
		}
	write(f[n][S],'\n');
	IO::flush();
	return 0;
}
```

# D. 玩具

## title

[zhengruioi](http://zhengruioi.com/problem/999)

题意：

>小S有 $N$ 个盒子，每个盒子里都装着若干个玩具。玩具一共有 $M$ 种不同的类型。
>
>现在，小S想要知道有多少种不同的挑选盒子的方式，使得每种种类的玩具都至少在这些盒子里出现了一次。
>
>请输出答案对 $10^9+7$ 取模的值。

## analysis

这题真的有水平，我没看出背后的模型。

> 给若若干个二进制数，问最终有多少种选数的方案使得 `or` 起来全部是 `1` 。

（下面基本都是正解的话了，这题也是唯一一个我不知道该咋写注释的东西）

令 $cnt(S)$ 表示等于 $S$ 的二进制数个数，令  $f(S)=\sum_{S'\subset S}cnt(S')$ ，那么一个显然的容斥有答案为：
$$
\sum_S 2^{f(S)} (-1)^{n-|S|}
$$


难点在于 $f(S)$ 怎么求？

这其实就是一个高维前缀和问题。令 $f_{i,j}$ 为在不考虑前 $i$ 位的情况下， $j$ 的前缀和。

首先有： $f_{n,i}=cnt_i$ ， 然后， $f_{i,j}=f_{i+1,j}+f_{i+1,j|2^i}$ ，其中  $j$ 的第 $i$ 位是 `0` 。

那么做个递推搞定。

## code

```cpp
#include<bits/stdc++.h>

typedef long long ll;
const int maxn=1<<20,mod=1e9+7;

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

inline int lowbit(int x)
{
	return x & -x;
}

inline ll popcount(ll x)
{
	ll ans=0;
	while (x) ++ans, x-=lowbit(x);
	return ans;
}

ll c[maxn],p[maxn];
int main()
{
	int n,m;read(n);read(m);
	for (int i=1,k; i<=n; ++i)
	{
		read(k); ll tmp=0;
		for (int j=1,t; j<=k; ++j) read(t), --t, tmp|=1<<t;
		++c[tmp];
	}
	p[0]=1;
	for (int i=1; i<=n; ++i) p[i]=p[i-1]*2%mod;
	for (int i=0; i<m; ++i)
		for (int j=0; j<(1<<m); ++j)
		{
			if (j>>i&1) continue;
			c[j|(1<<i)]+=c[j];
		}
	ll ans=0;
	for (int i=0; i<(1<<m); ++i)
	{
		if (popcount(i)%2==m%2) ans+=p[c[i]];
		else ans-=p[c[i]];
		ans=(ans+mod)%mod;
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
```

# summary

1. 一天没回班，再次见证了一下一天都在机房的效率的确要高很多，很难的题，有同学解答，有时间苦想，不用分神（今天精神也不是很好，想不了太多东西）；
2. 见证了一下自己有多垃圾， $T2$ 想到了正解，没写出来，好心疼，下一次避免这种情况出现，简单题要 $A$ 。
3. 然后就是 $Dp$ 题目了，下次必须注意自己先写一遍，思路不清晰时在纸上写写步骤，然后再码代码。
4. 学对拍。（我这怕是千年咕了）