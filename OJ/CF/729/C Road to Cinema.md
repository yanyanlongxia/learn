# title

[CF729C](https://www.luogu.org/problem/CF729C)

简化题意：

> 某人在起点处，到终点的距离为 $s$ 。
>
>  汽车租赁公司提供 $n$ 种车型，每种车型有属性 $c_i$ （租车费用）， $v_i$（油箱容量）。 
>
> 车子有两种前进方式 ：
>
> ①. 慢速： $1km$ 消耗 $1L$ 汽油，花费 $2$ 分钟。 
>
> ②. 快速： $1km$ 消耗 $2L$ 汽油，花费 $1$ 分钟。
>
>  路上有 $k$ 个加油站，加油不需要花费时间，且直接给油箱加满。 
>
> 问在 $t$ 分钟内到达终点的最小花费是多少？（租车子的费用） 若无法到达终点，输出 $-1$ 。

# analysis

其实也是比较 ~~简单~~ （降低智商）的题目。

由于洛谷上的翻译实在是考研语文水平，我又很长时间没学文化课了，所以搞懂题意费了很长时间。

然后我和昕泽乱讨论了点儿什么奇奇怪怪的东西？（绝对保证和 $OI$ 有关）

然后得出了一个结论：二分。

然后就不会了，哈，翻题解吧，咦？这题降智商！竟然还需要数学知识。

其实有一个比较明显的想法，就是检测每一个车能否满足条件，这样的话，就可以 $O(n)$ 扫一遍来得出最终的最小花费。

那么怎么知道一辆车满不满足条件呢？

我们设 $x$ 为快走的路程， $y$ 为慢走的路程， $V$ 为汽油总量，  $s$ 为当前加油站与下一个加油站的距离，则有：
$$
\left\{\begin{array}{lcl}
2x+y=V\\
x+y=s\\
x+2y=t
\end{array}
\right.
$$


解得：
$$
\left\{\begin{array}{lcl}
x=V-s\\
y=2s-V
\end{array}
\right.
$$


如果想当然地认为这就万事大吉了，那么等待着的结果就是 $WA$ 。

为什么，因为 $x,y$ 可能是负数，那讨论一下吧。

- 如果 $x<0$ ，不管跑的多快，都肯定不可能到下一个点了，直接退掉。
- 如果 $y<0$ ，说明跑的太快，油桶没用完就快走到了，那此时的 $t$ 加上 $x$ 即可（对应花费的 $x\sim min$ ）。
- 除此之外均套用以上的式子算 $t$ 。

大概复杂度 $O(n)$ 的样子。

那下面就是怎样二分了，二分什么作为答案？

题上说使最小花费最大，所以一个显然的想法便是二分花费，在这个题中就是二分车了，问题是这车的价值有单调性吗？那还玩什么呀。

所以这是这是在玩儿人，真正决定车子到目的地的唯一标准是汽油容量，所以直接二分容量得了，看最小满足条件的 $V$ 是多少，搜一遍找一下满足 $v[i]>V$ 且 $\min(w[i])$ 即可。

# code

```cpp
#include<bits/stdc++.h>
 
#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)
 
#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl
 
typedef long long ll;
const int MaxN=3e5+10, inf=2e9;
 
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
 
template<typename T>inline bool chkMin(T &a,const T &b) { return a>b ? (a=b, true) : false; }
template<typename T>inline bool chkMax(T &a,const T &b) { return a<b ? (a=b, true) : false; }
template<typename T>inline T min(T a,T b) { return a<b ? a : b; }
template<typename T>inline T max(T a,T b) { return a>b ? a : b; }
 
int n, k, s, t;
int c[MaxN], v[MaxN], d[MaxN];
inline bool check(int v)
{
	ll sum=0;
	for (int i=1; i<=k; ++i)
	{
		int s=d[i]-d[i-1];
		ll x=v-s, y=(s<<1)-v;
		if (x<0) return 0;
		if (y<0) sum+=s;
		else sum+=x+(y<<1);
	}
	return sum<=t;
}
 
int main()
{
	read(n), read(k), read(s), read(t);
	for (int i=1; i<=n; ++i) read(c[i]), read(v[i]);
	for (int i=1; i<=k; ++i) read(d[i]);
	d[++k]=s;
	std::sort(d+1,d+k+1);
	ll l=0, r=inf, V=inf;
	while (l<=r)
	{
		ll mid=(l+r)>>1;
		if (check(mid)) r=mid-1, V=mid;
		else l=mid+1;
	}
	ll ans=inf;
	for (int i=1; i<=n; ++i)
		if (v[i]>=V) chkMin(ans, (ll)c[i]);
	write(ans==inf ? -1 : ans, '\n');
	IO::flush();
	return 0;
}
```
