# title

[CF741B](https://www.luogu.org/problem/CF741B)

简化题意：

>有 $n$ 个人 $(1\leqslant n\leqslant 1000)$ ，每个人有一个重量 $w_i(1\leqslant w_i\leqslant 1000)$ 和一个魅力值 $b_i(1\leqslant b_i\leqslant 10^6)$ 。
>
>$n$ 个人之间有 $m(1\leqslant m\leqslant min(\frac{n(n-1)}{2}, 10^5))$ 个关系。第 $i$ 个关系由两个数字 $x_i$ 和 $y_i$ 组成，表示第 $x_i$ 个人和第 $y_i$ 个人是朋友，朋友关系是双向的。
>
>已知若 $a$ 和 $b$ 是朋友， $b$ 和 $c$ 是朋友，则 $a$ 和 $c$ 是朋友。 现在 $Mehrdad$ 要邀请一些人来到派对，使这些人的重量总和不超过 $w_i(1\leqslant w_i\leqslant 1000)$ ，且魅力值总和尽量大。同一个朋友圈里的人，只能邀请其中的一个人，或者全部人，或者一个人也不邀请。

# analysis

1. 确定哪些人在同一组，这样的话就想到了并查集。然后利用 $vector$ 容器将同一组的人存放在一起。
2. 按上面的要求对于每个容器中的人要么全部都取，要么只取一个，要么不取，那么这其实就是一个简单的 $01$ 背包问题了。
3. 所以这道题就解决了，提智商！

# code

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

const int MaxN=1e3+10;

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

namespace Union_Set
{
	int fa[MaxN];
	inline int get(int x)
	{
		return fa[x]==x ? x : fa[x]=get(fa[x]);
	}

	inline void merge(int x, int y)
	{
		int fx=get(x), fy=get(y);
		if (fx^fy) fa[fx]=fy;
	}
}

using Union_Set::get;
using Union_Set::merge;

int w[MaxN], b[MaxN], f[MaxN];
std::vector<int> g[MaxN];
int main()
{
	int n, m, W;
	read(n), read(m), read(W);//总重
	for (int i=1; i<=n; ++i) read(w[i]);//重量
	for (int i=1; i<=n; ++i) read(b[i]);//魅力值

	for (int i=1; i<=n; ++i) Union_Set::fa[i]=i;
	for (int i=1, x, y; i<=m; ++i) read(x), read(y), merge(x, y);

	for (int i=0; i<MaxN; ++i) g[i].clear();
	for (int i=1; i<=n; ++i) g[get(i)].push_back(i);

	memset(f, 0, sizeof(f));
	for (int i=1; i<=n; ++i)
	{
		if (get(i)^i) continue;//一个人也不邀请
		for (int j=W; j>=0; --j)
		{
			int sumw=0, sumb=0;
			for (int k=0; k<(int)g[i].size(); ++k)//或者只能邀请其中的一个人
			{
				sumw+=w[g[i][k]], sumb+=b[g[i][k]];
				if (j>=w[g[i][k]]) chkMax(f[j], f[j-w[g[i][k]]]+b[g[i][k]]);
			}
			if (j>=sumw) chkMax(f[j], f[j-sumw]+sumb);//或者全部人
		}
	}
	write(f[W], '\n');
	IO::flush();
	return 0;
}
```
