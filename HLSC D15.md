[TOC]

# 数组

## title

Description

>有一个长度为 $n$ 的数组 $b$ ，以及长度为 $n$ 且初始值为零的数组 $a$ ，每次可以对 $a$ 数组的一个区间 $[l,r] (1≤ l ≤ r ≤ n)$ 进行操作，使得该区间内的 $a_i$ 全部加 1 。问最小的操作次数使得对任意 $1\leqslant i\leqslant n$ ，有 $a_i=b_i$ 。
>
>你会发现这实际上是去年 $NOIP$ 提高组 $Day1T1$，对于你来说过于简单，于是我们稍稍加大了点难度。
>
>在本题中，会给出一个长度为 $n$ 的数组 $b$，并会共有 $m$ 次操作或询问，种类分为两种：
>
>- 1 l r k: 将区间 $[l,r]$ 中的 $b_i$ 加上 $k$ 。
>- 2 l r: 当 $b_1, b_2, ..., b_{l-1}, b_{r+1}, b_{r+2}, ..., b_n$ 的值均为 0 时，询问数组 $b$ 对应的答案并输出。

Input

>第一行两个数 $n,m$ 表示数组的长度以及操作的次数。
>
>第二行 $n$ 个数表示初始状态下数组 $b$ 的值
>
>接下来的 $m$ 行，先给出一个正整数 $op$ 表示操作种类，当 $op=1$ 时会接着给出三个正整数 $l, r, k,op=2$ 时会接着给出两个正整数 $l,r$ 。这里 $l, r, k$ 的意义题目描述中均已给出。

Output

>对于所有 $op=2$ 的操作，输出一行正整数表示这次询问对应的答案并换行。

Sample Input

>5 4
>1 3 1 4 5
>2 1 5
>1 3 4 2
>2 2 4
>2 1 5

Sample Output

>7
>6
>6
>

Hint

>$1\leqslant n, m\leqslant 100000$
>$1\leqslant l \leqslant  r\leqslant n$
>$1\leqslant b_i, k\leqslant 100000$
>对于其中 $30\%$ 的数据保证 $1\leqslant n, m\leqslant 3000$
>对于其中 $70\%$ 的数据保证 $1\leqslant n \ast m\leqslant 2,500,000,000$

## analysis

我也不知道我模拟赛到底多少分，所以就不要管那个 $30pts$ 的大暴力了。

直接正解，看到区间操作，查询，线段树或者 $BIT$ 肯定是要的，只不过要建两颗 $BIT$ （好写）：一颗原数组 $BIT$ ，一颗原数组差分数组的 $BIT$ 。

1. 修改操作就把原数组 $BIT$ 树上差分一下，对于原数组的差分数组所建的那颗 $BIT$ 也树上差分一下；
2. 查询操作的话，直接把第二颗 $BIT$ 前缀和一下，然后要加上原数组 $BIT$ 的 $1\sim l$ 的答案。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+10;

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

template<typename T>inline void write(T x)
{
	if (!x) { putchar('0'); return ; }
	if (x<0) putchar('-'), x=-x;
	T num=0, ch[20];
	while (x) ch[++num]=x%10+48, x/=10;
	while (num) putchar(ch[num--]);
}

int n,m;
ll a[maxn],b[maxn],f[maxn],g[maxn];
inline int lowbit(int x) { return x & -x; }
inline void add(ll *t,int x,ll k) { while (x<=n) t[x]+=k, x+=lowbit(x); }
inline ll sum(ll *t,int x) { ll ans=0; while (x) ans+=t[x], x-=lowbit(x); return ans; }

int main()
{
	read(n);read(m);
	for (int i=1; i<=n; ++i) read(a[i]);
	for (int i=1; i<=n; ++i) b[i]=a[i]-a[i-1];//处理出差分数组
	for (int i=1; i<=n; ++i)
	{
		add(f,i,b[i]);
		if (b[i]>0) add(g,i,b[i]);//用于查询答案
	}
	while (m--)
	{
		int opt,l,r;
		read(opt);read(l);read(r);
		if (opt==1)
		{
			ll k;read(k);++r;//正好修改区间[l,r]
			add(f,l,k),add(f,r,-k);//BIT差分
			if (b[l]>0) add(g,l,-b[l]);
			if (b[r]>0) add(g,r,-b[r]);
			b[l]+=k,b[r]-=k;//在端点处打上标记
			if (b[l]>0) add(g,l,b[l]);
			if (b[r]>0) add(g,r,b[r]);
		}
		else write(sum(f,l)+sum(g,r)-sum(g,l)),puts("");
	}
	return 0;
}
```

# 盒子

## title

Description

>在立体直角坐标系中，有 $n$ 个长为 $d_x$，宽为 $d_y$，高为 $d_z$ 的盒子，盒子的边均与坐标轴平行。对于第$i$个盒子，它的其中一个顶点为 $(x_i, y_i, z_i)$，则他的对角顶点为 $(x_i + d_x, y_i + d_y, z_i + d_z)$ 。
>
>对于两个不同的盒子 $i,j$ ，
>
>它们有公共点当且仅当 $|x_i-x_j|≤d_x, |y_i-y_j |≤d_y ,|z_i-z_j|≤d_z$ 同时成立。
>
>问这 $n$ 个盒子中是否存在两个不同的盒子 $i,j(i \not =j)$ 使得它们有公共点。

Input

>本题有多组数据。
>
>第一行给出一个正整数 $T$，表示数据组数。
>
>对于每组数据，第一行给出四个正整数 $n, d_x, d_y, d_z$ ,盒子个数以及每个盒子的长宽高，接下来的 $n$ 行给出三个正整数 $x_i, y_i, z_i$ 表示第i个盒子的顶点。
>
>由于本题数据量较大，建议使用读入优化。

Output

>共 $T$ 行，每行对应着每组数据的答案。
>
>若存在两个盒子有公共点，则输出”$Yes$”（不含引号），否则输出”$No$”。

Sample Input

>2
>2 2 3 4
>1 1 1
>3 4 5
>2 2 3 4
>1 1 1
>3 4 6

Sample Output

>Yes
>No

HINT

>$1 ≤ T ≤ 1000$
>
>$2 ≤ n ≤ 100000$
>
>$1 ≤ d_x, d_y, d_z ≤ 1e9$
>
>$1 ≤ x_i, y_i, z_i ≤ 1e9$
>
>$\sum n≤1e6$
>
>对于其中$30\%$的数据保证 $2 ≤n ≤ 500$
>
>对于其中$60\%$的数据保证 $n > 10000$ 的数据只出现一次

## analysis

好像赛后被告知此题被好多人暴力过了很多点，额，跟我没关系，反正我的暴力总是只能拿那个点的分，甚至没分，呜呜~

正解是字符串哈希，所以对于我来说，各种迷之操作，看代码，一切尽在不言中。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+10,p=1e6+3;

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

template<typename T>inline void write(T x)
{
	if (!x) { putchar('0'); return ; }
	if (x<0) putchar('-'), x=-x;
	T num=0, ch[20];
	while (x) ch[++num]=x%10+48, x/=10;
	while (num) putchar(ch[num--]);
}

int Case;
struct Orz
{
	int x,y,z;
	Orz(int a=0,int b=0,int c=0) : x(a),y(b),z(c) {}
	inline bool operator == (const Orz &a) const { return x==a.x && y==a.y && z==a.z; }
	inline int hash() { return abs(((((ll)x)<<20)+(((ll)y)<<10)+z))%p; }
};

struct Hash_table
{
	vector<Orz>V[p];
	vector<int>D[p];
	int t[p];

	inline void add(Orz x,int f)
	{
		int h=x.hash();
		if (t[h]!=Case)
		{
			V[h].clear();D[h].clear();
			t[h]=Case;
			V[h].push_back(x);
			D[h].push_back(f);
		}
		else
		{
			vector<Orz>::iterator itx=V[h].begin();
			vector<int>::iterator itd=D[h].begin();
			for ( ; itx!=V[h].end(); ++itx,++itd)
				if (*itx==x) { (*itd)+=f; return ; }
			V[h].push_back(x);
			D[h].push_back(f);
		}
	}

	inline int get(Orz x)
	{
		int h=x.hash();
		if (t[h]!=Case)
		{
			V[h].clear();D[h].clear();
			t[h]=Case;
			return 0;
		}
		else
		{
			vector<Orz>::iterator itx=V[h].begin();
			vector<int>::iterator itd=D[h].begin();
			for ( ; itx!=V[h].end(); ++itx,++itd)
				if (*itx==x) return *itd;
			return 0;
		}
	}
}M;

int n,dx,dy,dz;
int x[maxn],y[maxn],z[maxn];
inline bool check(int a,int b)
{
	if (!a) return 0;
	return abs(x[a]-x[b])<=dx && abs(y[a]-y[b])<=dy && abs(z[a]-z[b])<=dz;
}

int main()
{
	int T;read(T);
	for (Case=1; Case<=T; ++Case)
	{
		read(n);read(dx);read(dy);read(dz);
		for (int i=1; i<=n; ++i) read(x[i]),read(y[i]),read(z[i]);
		bool flag=0;
		for (int i=1; i<=n; ++i)
		{
			Orz now(x[i]/dx,y[i]/dy,z[i]/dz);
			int v=M.get(now);
			if (!v) M.add(now,i);
			else { flag=1; break; }
		}
		if (flag) { puts("Yes"); continue; }
		for (int i=1; i<=n && !flag; ++i)
		{
			int nx=x[i]/dx,ny=y[i]/dy,nz=z[i]/dz;
			for (int ox=-1; ox<=1; ++ox)
				for (int oy=-1; oy<=1; ++oy)
					for (int oz=-1; oz<=1; ++oz) if (ox|oy|oz)
						if (check(M.get(Orz(nx+ox,ny+oy,nz+oz)),i)) { flag=1; break; }
		}
		puts(flag?"Yes":"No");
	}
	return 0;
}
```

# 取模或异或

## title

[HDU 6275](http://acm.hdu.edu.cn/showproblem.php?pid=6275)

Description

> 给定一个数 $n$，求
> $$
> (n~mod~1)~xor~(n~mod~2)~xor~(n~mod~3)~xor~...~xor~(n~mod~ (n-1))~xor~(n~mod~n)
> $$
> 其中`mod`为取模运算，`xor`为异或运算（在C++中用`^`表示）

Input

>一行，一个正整数 $n$。

Output

>一行，一个正整数表示答案

Sample Input

>1 2 3 4 5

Sample Output

>0 0 1 1 2

HINT

>$1\leqslant n\leqslant 1,000,000,000,000$
>
>对于其中$20\%$的数据保证$1\leqslant n\leqslant 1,000,000$
>
>对于其中$50\%$的数据保证$1\leqslant n\leqslant 1,000,000,000$
>
>对于其中$80\%$的数据保证$1\leqslant n\leqslant 100,000,000,000$

## analysis

余数之和 2.0..

于是除了数论分块，还需要一个类欧公式。

为什么会牵扯到类欧公式呢？

因为求异或和有一个思路是：求出每一位分别是什么。

那么从低到高第 $k$ 位（从 0 开始）的答案其实就是
$$
\sum_{i=1}^n\lfloor\frac{n~mod~i}{2^k}\rfloor \pmod{2}=\sum_{i=1}^n\lfloor\frac{n-\lfloor\frac{n}{i}\rfloor i}{2^k}\rfloor \pmod{2}
$$


就很像类欧几里得中的 $f$，具体推导还请到此位大佬 [WorldWide_D](https://blog.csdn.net/WorldWide_D/article/details/54730588) 的 $blog$ 中去观光，代码我就放在下面了。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

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

template<typename T>inline void write(T x)
{
    if (!x) { putchar('0'); return ; }
    if (x<0) putchar('-'), x=-x;
    T num=0, ch[20];
    while (x) ch[++num]=x%10+48, x/=10;
    while (num) putchar(ch[num--]);
}

inline bool f(ll a,ll b,ll c,ll n)//类欧几里得
{
    if (!a) return (( (n+1)&(b/c) )&1ll)>0;
    if (a>=c || b>=c)
    {
        ll tmp=(n&1ll) ? (n+1)/2*n : n/2*(n+1);
        return (( (a/c)*tmp+(b/c)*(n+1)+f(a%c,b%c,c,n) )&1ll)>0;
    }
    else
    {
        ll m=(a*n+b)/c;
        return (( (n*m)^f(c,c-b-1,a,m-1) )&1ll)>0;
    }
}

int main()
{
    // int T;read(T);
    // while (T--)
    // {
        ll n;read(n);
        ll ans=0,t=min(30000000ll,n);
        for (ll i=1; i<=t; ++i) ans^=(n%i);//前lim直接暴力扫
        for (ll l=t+1,r; l<=n; l=r+1)
        {
            r=n/(n/l); ll lim=n/l*(r-l)+n%r,lans=0;
            for(ll k=1; k<=lim; k<<=1) lans+=f(n/l,n%r,k,r-l)*k;//后面用类欧公式搞过去
            ans^=lans;
        }
        write(ans),puts("");
    // }
    return 0;
}
```