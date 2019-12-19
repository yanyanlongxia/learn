# title

[BZOJ 2321](https://lydsy.com/JudgeOnline/problem.php?id=2321)

[LUOGU 1861](https://www.luogu.org/problem/P1861)

Description

>  $Magic~Land$ 上的时间又过了若干世纪……
>
> 现在，人们谈论着一个传说：从前，他们的祖先来到了一个位于东方的岛屿，那里简直就是另外一个世界。善于分析与构造的 $Magic~Land$ 上的人们总是不明白那里的人们是如何不借助精确的实验与计算驱动和操纵魔法。
>
> 偶然地，一个魔法使（$Magician$）来到了 $Magic~Land$ ，在临走的时候留下了一个神奇的盒子，叫做星器（$Casket~of~star$）。
>
> 虽然不知道这个盒子是做什么的，但是经过了大量的实验和计算后，人们已经清楚它的一些事实：
>
> 1. 星器之中有 $N\times M$ 个区域，可看作分成 $N$ 行和 $M$ 列的格子，每个区域之中有若干单位的称为“星”的对象，这个对象的最小单位已经被确定，所以，这个数量总是整数。
>
> 2. 魔法使可以驱动星器中位于**同一行或同一列**的**不相邻**（有公共边的区域称为相邻的）两个区域中各 $1$ 单位的“星”，使得它们**分别向中心移动 $1$ 格**。
>
> 3. 每一次使用 $2$ 中的方法驱动“星”，将会产生魔力，魔法使会得到这一部分魔力。**魔力的量等于这个两个区域之间所间隔的区域数**。
>
> 这样，我们可以用一个 $N\times M$ 的数表来表示星器的状态，比如 $N=2$ ， $M=3$ 时：
>
> |2|0|1|      |      |1|2|0|
> |--|--|--|--|--|--|--|--|
> |5|1|4|      |      |5|1|4|
>
> 当星为左图的状态时，通过操纵第一行的第 $1$ 和 $3$ 个区域中的“星”（加粗的数字对应的区域），变为右图所示的状态，同时，将产生1单位的魔力（因为这两个区域之间恰好隔了 $1$ 个区域）。
>
> 在经过了进一步的研究之后，人们知道了这个星器最初的状态（$Ini$）以及最终被他们得到时的状态（$Fin$）。
>
> 你希望知道，星器**最多**帮助它的拥有者提供了多少的魔力。即：经过一系列上述操作由初态（$Ini$）变为终态（$Fin$），至多产生多少魔力。
>
> 需要注意的是，显然操作过程中每个区域内“星”的数量**不能是负的**，即：如果那个区域已经没有“星”了，当然就不能继续操作了。

# analysis

- 答案与移动方式无关，只与初态，终态有关。

- ~~这题暴力不可写，所以看题解~~。因为移动的方式比较复杂，所以考虑用别的方法来计算。

  * 观察两个在同一列的星 $(x_1,y),(x_2,y)(x_1\lt x_2)$ 靠近时，获得的魔力为 $x_2-x_1-1$ ，想办法给星一个 **"势能"** ，使得它们靠近时产生的魔力等于势能的减小量（**神仙思路**）；

  * 一颗星 $(x,y)$ 的势能为 $\dfrac{x^2+y^2}{2}$ 。

  * 然后用上面的情况试一下：

  * $$
    \begin{array}{lcl}
    E_0=\dfrac{x_1^2+y_1^2+x_2^2+y_2^2}{2}\\
    E_1=\dfrac{(x_1+1)^2+y_1^2+(x_2-1)^2+y_2^2}{2}\\
    \Delta E=E0-E1=x_2-x_1-1
    \end{array}
    $$

  * 就证明了按 $x^2+y^2$ 定势能满足 **靠近时产生的魔力等于势能的减小量** 。

  * 最后的答案为 **初态总势能减去终态总势能** ，所以此题完结（无奈，逃。

# code

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

typedef long long ll;

namespace IO
{
	char buf[1<<15],*fs,*ft;
	inline char getc() { return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++; }
	template<typename T>inline void read(T &x)
	{
		x=0;
		T f=1, G;
		while (!isdigit(ch) && ch^'-') G;
		if (ch=='-') f=-1, G;
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), G;
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
	int n, m;
	read(n), read(m);
	ll sum1=0, sum2=0;
	for (int i=1; i<=n; ++i)
		for (int j=1, x; j<=m; ++j) read(x), sum1+=(i*i+j*j)*x;
	for (int i=1; i<=n; ++i)
		for (int j=1, x; j<=m; ++j) read(x), sum2+=(i*i+j*j)*x;
	write((sum1-sum2)>>1,'\n');
	IO::flush();
	return 0;
}
```
