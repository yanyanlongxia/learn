# title

[LUOGU AT2266](https://www.luogu.org/problem/AT2266)

简化题意：

> 给你一个长度为 $N$ 的整数序列 $X$，请判断是否存在一个满足下列条件的整数序列 $a$，如果存在，请构造一种方案
>
> 条件如下：
>
> 1.  $a$ 的长度为 $N^2$ ，并且满足数字 $1,2,3...N$ 都各出现恰好 $N$ 次；
> 2. 对于 $1\leqslant i\leqslant N$，数字 $i$ 在 $a$ 中第 $i$ 次出现的位置是 $X_i$；
>    

# analysis



直接把 $1\sim N$ 按照 $x$ （$code$ 中为 $c$）从小到大排序，对于每个 $i$，把前 $i$ 个 $i$ 填进去。 
然后再从小到大把剩下的位置补完即可，较新的模拟题目。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=510;

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
    *fe++=' ';
}

int c[maxn],b[maxn],a[maxn*maxn+maxn];
inline bool cmp(int a,int b)
{
	return c[a]<c[b];
}

int main()
{
	int n;read(n);
	for (int i=1; i<=n; ++i) read(c[i]),b[i]=i;
	sort(b+1,b+n+1,cmp);
	int x=1;
	for (int i=1; i<=n; ++i)
	{
		int w=b[i];
		a[c[w]]=w;
		for (int j=1; j<w; ++j)
		{
			while (a[x]) ++x;
			a[x]=w;
		}
		if (x>c[w]) return puts("No"),0;
	}
	for (int i=1; i<=n; ++i)
	{
		int w=b[i];
		for (int j=1; j<=n-w; ++j)
		{
			while (a[x]) ++x;
			if (x<c[w]) return puts("No"),0;
			a[x]=w;
		}
	}
	puts("Yes");
	for (int i=1; i<=n*n; ++i) write(a[i]);
	flush();
	return 0;
}
```