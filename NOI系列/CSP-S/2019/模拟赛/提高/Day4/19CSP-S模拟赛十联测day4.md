[TOC]

# A. 罗

## title

[zhengruioi](http://zhengruioi.com/problem/963)

题意：

>小E和小F各自想了一个字符串 $S_1$ 和 $S_2$ ，由小写字母、 `*` 和 `?` 组成。为了测试他们是否心有灵犀，他们会设法寻找一个新的串 $T$ ，也由小写字母、 `*` 和 `?` 组成，其中 `*` 可以替换成任意非负长度的小写字母字符串， `?` 可以替换成任意小写字母。一个小写字母字符串 $S$ 能匹配 $T$ 当且仅当可以恰当地进行替换使得  $T$ 和 $S$ 相等。他们寻找的这个 $T$ 需要满足：
>
>- 如果 $S$ 能匹配 $S_1$  **或**  $S_2$ ，那么 $S$ 也能匹配 $T$ 
>- 包含的 `*` 的个数最少
>- 在满足前两个条件的情况下长度最长
>- 在满足前三个条件的情况下 `?` 的个数最少
>- 在满足前四个条件的情况下字典序最小，字符的字典序从小到大为 `*?abcdefghijklmnopqrstuvwxyz` ，也就是 $ASCII$ 码的顺序
>
>不难发现这样的串只有一个，请输出它。

## analysis



## code

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

const int MaxN=2e5+10;

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

int a[MaxN], b[MaxN];
char s1[MaxN], s2[MaxN], s[MaxN];
inline bool chk(char *s, int n)
{
	for (int i=1; i<=n; ++i)
		if (s[i]=='*') return 1;
	return 0;
}

int main()
{
	int T; read(T);
	while (T--)
	{
		scanf("%s%s", s1+1, s2+1);
		int n1=strlen(s1+1), n2=strlen(s2+1);
		if (n1==n2 && !chk(s1,n1) && !chk(s2,n2))
		{
			for (int i=1; i<=n1; ++i)
				if (s1[i]!=s2[i] || s1[i]=='?') *IO::fe++='?';
				else *IO::fe++=s1[i];
			*IO::fe++='\n';
		}
		else
		{
			int x1=0, x2=0, pl, pr;
			for (int i=1; i<=n1; ++i) x1+=s1[i]!='*';
			for (int i=1; i<=n2; ++i) x2+=s2[i]!='*';

			int n=pl=pr=min(x1, x2);
			for (int i=1; i<=n; ++i) a[i]=b[i]=0;

			for (int i=1; i<=n; ++i)
				if (s1[i]=='*' || s2[i]=='*') { pl=i-1; break; }
			for (int i=1; i<=pl; ++i)
				if (s1[i]==s2[i] && s1[i]!='?') a[i]=1;

			for (int i=1; i<=n; ++i)
				if (s1[n1-i+1]=='*' || s2[n2-i+1]=='*') { pr=i-1; break; }
			for (int i=1; i<=pr; ++i)
				if (s1[n1-i+1]==s2[n2-i+1] && s1[n1-i+1]!='?') b[i]=1;

			for (int i=1; i<=n; ++i) a[i]+=a[i-1], b[i]+=b[i-1];

			int Max=0, pos=0; bool flag=0;
			for (int i=0; i<=n; ++i)
				if (chkMax(Max, a[i]+b[n-i])) pos=i;

			for (int i=1; i<=pos; ++i)
			{
				if (s1[i]=='*' || s2[i]=='*') flag=1;
				if (flag || s1[i]!=s2[i]) *IO::fe++='?';
				else *IO::fe++=s1[i];
			}
			*IO::fe++='*';

			flag=0;
			for (int i=1; i<=n-pos; ++i)
			{
				if (s1[n1-i+1]=='*' || s2[n2-i+1]=='*') flag=1;
				if (flag || s1[n1-i+1]!=s2[n2-i+1]) s[i]='?';
				else s[i]=s1[n1-i+1];
			}
			for (int i=1; i<=n-pos; ++i) *IO::fe++=s[n-pos-i+1];
			*IO::fe++='\n';
		}
	}
	IO::flush();
	return 0;
}
```

# B. 小

## title

[zhengruioi](http://zhengruioi.com/problem/964)

题意：

> 小E和小F有一列正整数 $a_1,…,a_n$ 。小E喜欢最大公约数大于 $1$ 的正整数可重集，所以小F希望能够选择 $(l,r)$ ，满足你可以从 $a_l,…,a_r$ 中选出至少 $\lceil\frac{r−l+1}{2}\rceil$ 个数，它们的最大公约数大于 $1$  。如果有多个满足条件的 $(l,r)$ ，小F希望找到 $r−l$ 最大的。如果仍然有多个，小F希望找到 $l$ 最小的。**如果找不到满足条件的，则 $l=r=0$ 。** 

## analysis



## code

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

typedef long long ll;
const int MaxN=1e6+10;

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

int isnopr[MaxN], prime[MaxN], cnt, N;
inline void Pre()
{
	for (int i=2; i<=N; ++i)
		if (!isnopr[i])
		{
			prime[++cnt]=i;
			for (int j=i<<1; j<=N; j+=i) isnopr[j]=1;
		}
}

int a[MaxN], pos[MaxN], n, l, len;
inline void work(int p)
{
	memset(pos, -1, sizeof(pos));
	int x=n;
	pos[n]=0;
	for (int i=1; i<=n; ++i)
	{
		if (a[i]%p) --x;
		else ++x;
		if (pos[x]==-1) pos[x]=i;
		else
		{
			if (len<i-pos[x]) len=i-pos[x], l=pos[x]+1;
			else if (len==i-pos[x]) chkMin(l, pos[x]+1);
		}
	}
	if (x>=n) l=1, len=n;
}

int main()
{
	read(n);
	for (int i=1; i<=n; ++i) read(a[i]), chkMax(N, a[i]);
	Pre();
	for (int i=1; i<=min(40, cnt); ++i)
	{
		work(prime[i]);
		if (len==n) break;
	}
	write(l, ' '), write(max(0, l+len-1), '\n');
	IO::flush();
	return 0;
}
```

# C. 黑

[zhengruioi](http://zhengruioi.com/problem/965)

题意：

>小E和小F编不出故事来了，只好直接把问题丢给了你。
>
>你现在有下面一段代码，小E和小F把输入给了你。
>
>```cpp
>int X, Y, n, a[], b[];
>// input n, X, a[], b[]
>Y=0;
>for (int i=1; i<=n; i++)
>{
>    	X=max(0, X-a[i]);
>    	Y=Y+max(0, b[i]-X);
>}
>// output Y
>```
>
>小E希望执行完这段伪代码之后 $Y$ 的值尽可能大。为了满足这个要求，小F可以对输入进行魔改，方式为把 $a_i,b_i$ 合在一起任意打乱顺序，即选定一个长度为 $n$ 的排列，然后分别作用这个排列到 $a$ 数组和 $b$ 数组上。你需要告诉小F应该怎么魔改，使得最终的 $Y$ 尽可能大。

## analysis



## code

$30pts$

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

const int MaxN=2e3+10;

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

struct Orz{int x, y, z;} a[MaxN];
inline bool cmp(Orz x, Orz y)
{
	if (x.x!=y.x) return x.x>y.x;
	if (x.y!=y.y) return x.y>y.y;
	return x.z>y.z;
}

int sum[MaxN];
int main()
{
	int X, n; read(X), read(n); int m=X, Y=0;
	for (int i=1; i<=n; ++i) read(a[i].x), a[i].z=i;
	for (int i=1; i<=n; ++i) read(a[i].y);

	int pre=0, last=n+1;
	for (int i=n; i>pre; --i)
		if (!a[i].y)
		{
			Orz t=a[i];
			for (int j=i; j>=pre+2; --j) a[j]=a[j-1];
			a[++pre]=t;
			X-=t.y;
			++i;
		}
	for (int i=pre+1; i<last; ++i)
		if (!a[i].x)
		{
			Orz t=a[i];
			for (int j=i; j<=last-2; ++j) a[j]=a[j+1];
			a[--last]=t;
			--i;
		}
	std::sort(a+pre+1, a+last, cmp);
	for (int i=1; i<=n; ++i)
	{
		sum[i]=sum[i-1]+a[i].x;
		X=max(0, X-a[i].x);
		Y+=max(0, a[i].y-X);
	}

	bool flag=1;
	while (flag)
	{
		flag=false;
		for (int i=pre+1; i<=last; ++i)
		{
			if (sum[i]>m) break;
			int expro=max(0, a[i].y-max(0, m-sum[i])) + max(0, a[i+1].y-max(0, m-sum[i+1]));
			int newpro=max(0, a[i+1].y-max(0, m-sum[i-1]-a[i+1].x)) + max(0, a[i].y-max(0, m-sum[i+1]));
			if (newpro>expro)
			{
				flag=true;
				std::swap(a[i], a[i+1]);
				sum[i]=sum[i-1]+a[i].x;
				Y+=newpro-expro;
			}
		}
	}
	write(Y, '\n');
	for (int i=1; i<=n; ++i) write(a[i].z, ' ');
	IO::flush();
	return 0;
}
```

$100pts$

```cpp
#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

#define mp std::make_pair
typedef std::pair<int,int> pii;
const int MaxN=2e3+10, MaxX=4e3+10, inf=0x3f3f3f3f;

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

template<typename T>inline bool chkMin(T &a,const T &b) { return b<a ? (a=b, true) : false; }//重载了<
template<typename T>inline bool chkMax(T &a,const T &b) { return a<b ? (a=b, true) : false; }
template<typename T>inline T min(T a,T b) { return a<b ? a : b; }
template<typename T>inline T max(T a,T b) { return a>b ? a : b; }

struct Orz{int x, y, z;} a[MaxN], pre[MaxN][MaxN*6];
inline bool operator < (const Orz x, const Orz y)
{
	if (x.x!=y.x) return x.x>y.x;
	if (x.y!=y.y) return x.y>y.y;
	return x.z>y.z;
}

int f[2][MaxX][MaxX], vis[MaxN], X, n;
inline void Clear(int cur, int m)
{
	for (int i=0; i<=X; ++i) f[cur][0][i]=f[cur][i][0]=-inf;
	for (int i=0; i<=m; ++i) f[cur][i][m-i]=-inf;
}

inline int getnum(int y, int z)
{
	if (!y) return X+z;
	if (!z) return (X<<1|1)+y;
	return y;
}

int cur;
inline void update(int ax, int ay, int bx, int by, int c, int i, int x)
{
	if (chkMax(f[cur][ax][ay], f[cur^1][bx][by]+c)) pre[i][getnum(ax, ay)]=(Orz){x, bx, by};
}

inline void print(int x, int y, int z)
{
	if (!x)
	{
		for (int i=1; i<=n; ++i)
			if (!vis[i]) write(i, ' ');
		return ;
	}
	Orz t=pre[x][getnum(y, z)];
	vis[t.x]=1;
	print(x-1, t.y, t.z);
	if (t.x) write(t.x, ' ');
}

int main()
{
	read(X), read(n); int m=X;
	for (int i=1; i<=n; ++i) read(a[i].x), a[i].z=i;
	for (int i=1; i<=n; ++i) read(a[i].y);
	std::sort(a+1, a+n+1);

	Clear(cur, m);
	for (int i=0; i<=X; ++i) f[cur][i][X-i]=0;

	for (int i=1; i<=n; ++i)
	{
		cur^=1, Clear(cur, max(0, m-a[i].x));
		for (int j=0; j<=m; ++j) update(max(0, j-a[i].x), m-j, j, m-j, max(0, a[i].y-max(0, j-a[i].x)), i, a[i].z), update(j, max(0, m-j-a[i].x), j, m-j, 0, i, 0);
		for (int j=0; j<=X; ++j) update(0, j, 0, j, a[i].y, i, a[i].z), update(0, max(0, j-a[i].x), 0, j, 0, i, 0);
		for (int j=0; j<=X; ++j) update(max(0, j-a[i].x), 0, j, 0, max(0, a[i].y-max(0, j-a[i].x)), i, a[i].z), update(j, 0, j, 0, 0, i, 0);
		m=max(0, m-a[i].x);
	}

	Orz ans=(Orz){-inf, 0, 0};
	for (int i=0; i<=X; ++i) chkMin(ans, (Orz){f[cur][i][0], i, 0});
	write(ans.x, '\n');
	print(n, ans.y, ans.z), *IO::fe++='\n';
	IO::flush();
	return 0;
}
```

# summary

差不多已经一个星期了，才来写这篇 $blog$ ，再加上比赛时没有参加，所以感受就没有那么强烈了。

$solution$ 写的有点让人看不懂，所以这三道题都是我参照 $xvsuyang$ 的 $code$ 写的，大概在将这些 $code$ 写完，又 $DeBug$ 后，算是对于题目有了更深的了解，但是自己想的话，这些题目怕是连送得分都未必能拿到，所以我做了一个决定，就是：这篇 $blog$ 先不用那么花费大时间来完成，而是等有时间了，在闲杂时间内完成，也算是复盘的一个实践。