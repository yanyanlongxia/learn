# title

[BZOJ 2093](https://lydsy.com/JudgeOnline/problem.php?id=2093)

[LUOGU 3509](https://www.luogu.org/problem/P3509)

Description

> 一个条河无限宽，上面有 $n$ 块石头，石头离左边的河岸（无限宽，右边河岸不晓得在哪）距离严格递增，现在 $Zxl$ 想锻炼自己的跳跃能力（谁叫他在班里外号是鸟怪。畸形），他在某一块石头上，想跳到离他这块石头第 $k$ 远的石头上去，假如离他第 $k$ 远的石头不是唯一的，他就选离岸最近的那一个（不然回不去了），他想你让他知道，从每块石头开始跳了 $m$ 次后，自己在哪。

# analysis

首先要预处理出每个位置的第 $k$ 近的数位置，由于 $n\leqslant 10^6$ ，所以算法的时间复杂度必须是线性或者 $O(n\log n)$ 的。

由于这个序列是严格递增的，那么对于第 $i$ 个位置的数，可以构造出一个长度 $k$ 的区间 $[l,r],r-l+1=k$ ，使得 $i\in[l,r]$ （其实是肯定在区间里的），由于单调性，于是答案肯定是 $a[i]−a[l],a[r]−a[i]$ 中较大的一个数的位置。于是不难想到用尺取法去求每个位置所对应的第 $k$ 近的数的位置，这样就是 $O(n)$ 的预处理。

然后再考虑如何去求 $m$ 次后的位置，暴力就是 $1\to m$ 扫一遍，但是这样的时间复杂度就是 $O(nm)$ 了，爆炸。

优化的方法就是倍增了，用类似于快速幂的方法， $m$ 可以转为 $2^{p1}+2^{p2}+…2^{pk}$，先移动到 $2^1$ 次的位置，再移到 $2^2$ 次的位置…若二进制的第 $p_i$ 位为 $1$ 则对答案先移动前面求出的 $p_i+1$ 次（可以类比下快速幂），这样就优化到了 $O(n\log m)$ 了。

挺有意思的。

# code

```cpp
#include<bits/stdc++.h>

typedef long long ll;
const int maxn=1e6+10;
typedef int iarr[maxn];

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

iarr ans,f,g;
ll a[maxn],m;
int main()
{
	int n,k;read(n);read(k);read(m);
	for (int i=1; i<=n; ++i) read(a[i]);
	int l=1, r=k+1;
	f[1]=r;
	for (int i=2; i<=n; ++i)
	{
		while (r<n && a[i]-a[l]>a[r+1]-a[i]) ++r, ++l;
		if (a[i]-a[l]>=a[r]-a[i]) f[i]=l;
		else f[i]=r;
	}
	for (int i=1; i<=n; ++i) ans[i]=i;
	while (m)
	{
		if (m&1) for (int i=1; i<=n; ++i) ans[i]=f[ans[i]];
		for (int i=1; i<=n; ++i) g[i]=f[f[i]];
		for (int i=1; i<=n; ++i) f[i]=g[i];
		m>>=1;
	}
	for (int i=1; i<=n; ++i) write(ans[i],' ');
	IO::flush();
	return 0;
}
```