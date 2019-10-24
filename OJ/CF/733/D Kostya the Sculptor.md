# title

[CF733D](https://www.luogu.org/problem/CF733D)

简化题意：

> 给定 $n$ 个长方体，求一个最大的内切球的半径，可以是两块石头将两个完全匹配的面合起来的或者就用一块石头，输出切出最大内切球的那 $1$ 或 $2$ 个石头是哪些。

# analysis

讲真，老师拿这道题是想说一下 $STL$ 写法的，结果现在却搞出了一个其他写法。

一个明显的结论，最终内切球的半径为 $\displaystyle\frac{\min(a,b,c)}{2}$ ，所以目标便是想办法让最小边最大。

那么分两步：

1. 假设都不能拼接，那么就是找到这些长方体中三边的最短边。那么将长方体三边按照 $x$ 最长边， $y$ 次长边， $z$ 最短边，然后按照 $x,y,z$ 的优先级排序，找到这种情况下的答案，记录下标。
2. 尝试拼接，并且拼接一定是将最短边拼到一起，就是说两个长方体的最长边和次长边一样，不然就对答案没有贡献，然后得出这种情况下的答案，记录下标。
3. 然后比较一下就好了，那个大输出那个。
4. 综上所述，这是道降智题。

# code

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

const int MaxN=1e5+10;

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

struct Orz{int x, y, z, id;} o[MaxN];
inline bool cmp(const Orz a, const Orz b)
{
	if (a.x==b.x)
	{
		if (a.y==b.y) return a.z>b.z;
		else return a.y>b.y;
	}
	else return a.x>b.x;
}

int main()
{
	int n, t[4], ans1=0, ans2=0, pos1=0, pos2=0;
	read(n);
	for (int i=1; i<=n; ++i)
	{
		read(t[1]), read(t[2]), read(t[3]);
		std::sort(t+1, t+4);
		o[i].x=t[3], o[i].y=t[2], o[i].z=t[1], o[i].id=i;
		if (chkMax(ans1, o[i].z)) pos1=i;
	}
	std::sort(o+1, o+n+1, cmp);
	for (int i=1; i<=n; ++i)
		if (o[i].x==o[i+1].x && o[i].y==o[i+1].y)
		{
			int t=min(o[i].y, o[i].z+o[i+1].z);
			if (chkMax(ans2, t)) pos2=i;
		}
	if (ans1>ans2) write(1, '\n'), write(pos1, '\n');
	else write(2, '\n'), write(o[pos2].id, ' '), write(o[pos2+1].id, '\n');
	IO::flush();
	return 0;
}
```
