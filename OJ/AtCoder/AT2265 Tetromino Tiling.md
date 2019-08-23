# title

[LUOGU AT2265](https://www.luogu.org/problem/AT2265)

简化题意：

> 给定 $7$ 种俄罗斯方块的个数，问： 最大能怎样用 $k$ 个这样的方块摆出高度为 $2*k$ 宽度为 $2$ 的矩形，求这个 $k$ 最大。

# analysis

首先手玩一下，不难发现只有 $1,2,4,5$ 这四种方块可以用，那么下面可以分类讨论一波：

- $2$ 号方块都可以用；

- 下面考虑 $1,4,5$ 三种方块的使用：
  * 如果是成双成对地使用的话，这里的成双成对是指从 $1,4,5$ 三种方块各拿出一块，就可以组成一个高度为 6，宽度为 2 的矩形（想一下吧，图片不太好搞），这样我成对地拿，是没有差别的；
  * 如果这个三种方块中有一种数量为 0 的话，就把非 0 的都两两成对取出，计算答案即可；
  * 然后就是如果这三种方块如果数量奇偶性相同的话，这个矩形是一定能搞成的！
  * 但要是不同的话，就要分几类了：
    + 奇偶偶：最后一定只剩下一个拿不出来；
    + 奇奇偶：通过取三个 1 化归到奇偶偶的情况，也就是只剩下一个拿不出来；

好了，这样一道好玩的题目就结束了。

# code

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

int a[8];
int main()
{
	for (int i=1; i<=7; ++i) read(a[i]);
	ll ans=a[2];
	if (!a[1] || !a[4] || !a[5]) ans+=a[1]/2*2+a[4]/2*2+a[5]/2*2;
	else
	{
		ans+=(ll)a[1]+a[4]+a[5];
		if (a[1]%2==a[4]%2 && a[4]%2==a[5]%2);
		else --ans;
	}
	write(ans);
	flush();
	return 0;
}
```