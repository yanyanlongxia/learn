[TOC]

# A. 最长01子序列

## title

[zhengruioi](http://zhengruioi.com/problem/960)

题意：

> 给定一个 $01$ 序列，请你找到一个最长的子序列，使得第一个 $1$ 到开头的距离、相邻两个 $1$ 之间的距离、最后一个 $1$ 到结尾的距离都相同。例如 `00100100` 和 `0001000` 就是符合要求的子序列， `0` 和 `10101` 和 `100100` 不是符合要求的子序列。输出最长长度。

## analysis

现在来看这道题，就是在匹配，对于每个 $1$ ，计算出它前面有几个 $0$ ，对于每个 $0$ ，都把它与它之后的第一个 $1$ 所匹配。

对于答案的贡献，首先所有的 $1$ 必定组成答案，所以在上一步中可以顺势求出 $0$ 的个数，然后就可以求出 $1$ 的个数了。

然后就开始 $O(n)$ 扫一遍，二分找出下一个 $1$ 的匹配位置（但是好像这个没用二分？但好像是类似于倍增的算法），然后只要这个匹配的位置小于 $m$ ，就参与答案贡献。

## code

```cpp
#include<bits/stdc++.h>

const int maxn=1e5+10;
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

template<typename T>inline bool chkMin(T &a,const T &b) { return a>b ? (a=b, true) : false; }
template<typename T>inline bool chkMax(T &a,const T &b) { return a<b ? (a=b, true) : false; }

char str[maxn];
iarr pos, nxt, sum;
inline int pre(int n)
{
	int cnt=0;
	for (int i=1; i<=n; ++i)
		if (str[i]=='0') pos[++cnt]=i;
		else sum[i]=cnt;//1 的前面有几个 0
	int last=n+1;
	for (int i=n; i>=1; --i)
		if (str[i]=='1') last=i;
		else nxt[i]=last;//将每个 0 都与他之后最近的 1 匹配
	return cnt;
}

int main()
{
	scanf("%s",str+1);
	int n=strlen(str+1);
	int m=pre(n);//0 的个数
	int ans=n-m;//1 的个数
	for (int i=1; 2*i<=m; ++i)
	{
		int cur=0, s=0;
		while (1)
		{
			cur+=i;
			if (cur>m || nxt[pos[cur]]>n) break;
			int x=nxt[pos[cur]];
			cur=sum[x];
			++s;
			if (cur+i<=m) chkMax(ans,(s+1)*i+s);
		}
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
```

# B. 路径长度

## title

[zhengruioi](http://zhengruioi.com/problem/961)

题意：

> 给定一张 $n$ 个点 $m$ 条边的 $DAG$ （有向无环图），边有长度。 $Q$ 次询问，每次给定 $K,dis$ ，询问 $1$ 号点到 $K$ 号点是否存在一条长度在 $[dis,1.1dis]$ 中的路径。

## analysis

$60pts$ ：

因为这是一个 $DAG$ ，且每次询问都与 $1$ 号节点有关，所以考虑拓扑，在拓扑中做一个背包。

状态为： $f[i][j]$ 表示 $1$ 号节点到第 $i$ 个节点的路径长度能否达到。

分析一下复杂度（这里主要进行空间复杂度分析，因为时间复杂度对于 $60\%$ 是够的）：

对于其中 $20\%$ 个数据，空间复杂度大概要有 $O(m^2d)$ ，也就是 $O(10^7)$ ，能够通过；

对于另外 $20\%$ 个数据，空间复杂度也是 $O(m^2d)$ ，也就是 $O(1.25\times10^9)$ ，所以要加个 `bitset` 优化一下才能通过。

$100pts$ ：

这里的优化便是因为并不需要把一个点的所有距离都求出来，这是因为考虑三个距离 $x,y,z$ ，如果 $\frac{1}{1.1}z\leqslant x\leqslant y\leqslant z$ ，那么 $y$ 这个距离是不需要记录的，因为：

1. 若 $dis\leqslant\frac{1}{1.1}z$ ，那么 $z$ 不符合条件，但是 $x$ 要比 $y$ 更有可能符合条件；
2. 若 $\frac{1}{1.1}z\leqslant dis\leqslant y$ ，那么 $z$ 符合条件， $y$ 就不需要了；
3. 若 $dis>y$ ，那么 $y$ 就不符合条件；（这个证明参考了 $duyi$ 的 $blog$ ，下面有链接）

所以，总的来说，对于每个点，在 $\frac{1}{1.1}z\sim z$ 中，至多会记录 $1$ 个距离，那么每个点只会记录一个 $\log$ 级别的距离。

然后合并两个距离集合 $A、B$ 时，可以使用归并排序做到 $O(|A|+|B|)=O(\log M)$ ，$M$ 是距离的值域。

对于每次询问，多数人是在询问的点的距离集合中二分一下，找到那个 $k$ 点的距离，比较一下。

而我是在归并排序时记录每个点的距离集合的大小，然后查询的时候扫一遍，复杂度会稍高些，但是懒。

## code

$60pts$

```cpp
#include<bits/stdc++.h>

typedef long long ll;
const int maxn=2510;

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
}

using IO::read;

int ver[maxn],Next[maxn],head[maxn],len,deg[maxn];
ll edge[maxn];
inline void add(int x,int y,ll z)
{
	ver[++len]=y,edge[len]=z,Next[len]=head[x],head[x]=len;
}

std::map<ll,bool> f[maxn];
std::map<ll,bool>::iterator it;
inline void bfs()
{
	f[1][0]=1;
	std::queue<int>q;
	q.push(1);
	while (!q.empty())
	{
		int x=q.front();
		q.pop();
		for (int i=head[x]; i; i=Next[i])
		{
			int y=ver[i];
			for (it=f[x].begin(); it!=f[x].end(); ++it) f[y][(*it).first+edge[i]]=1;
			if (!--deg[y]) q.push(y);
		}
	}
}

int main()
{
	int n, m, Q;read(n), read(m), read(Q);
	for (int i=1, x, y, z; i<=m; ++i) read(x), read(y), read(z), add(x,y,z), ++deg[y];
	bfs();
	while (Q--)
	{
		int k; ll dis; bool flag=0;
		read(k), read(dis);
		for (it=f[k].begin(); it!=f[k].end(); ++it)
			if (dis<=(*it).first && (*it).first<=dis*1.1)
			{
				flag=1, puts("YES");
				break;
			}
		if (!flag) puts("NO");
	}
	return 0;
}
```

$100pts$

```cpp
#include<bits/stdc++.h>

typedef long long ll;
const int maxn=2e5+10;

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
}

using IO::read;

int ver[maxn],Next[maxn],head[maxn],len=1;
ll edge[maxn];
inline void add(int x,int y,ll z)
{
	ver[++len]=y,edge[len]=z,Next[len]=head[x],head[x]=len;
}

int siz[maxn];
ll *f[maxn];
inline void merge(int x,int y,int z)//归并排序
{
	ll cur[2000], tmp[2000];
	ll *p=f[x], *q=f[y];
	int r1=1, r2=1, cnt=0, tot=0;

	while (r1<=siz[x] && r2<=siz[y])
		if (p[r1]<=q[r2]+z) cur[++cnt]=p[r1], ++r1;
		else cur[++cnt]=q[r2]+z, ++r2;
	while (r1<=siz[x]) cur[++cnt]=p[r1], ++r1;
	while (r2<=siz[y]) cur[++cnt]=q[r2]+z, ++r2;

	if (cnt) tmp[++tot]=cur[1];
	for (int i=2; i<cnt; ++i)
		if (cur[i]<cur[i+1] && tmp[tot]*1.1<cur[i+1]) tmp[++tot]=cur[i];
	if (cnt>1) tmp[++tot]=cur[cnt];
	delete f[x];
	f[x]=new ll [tot+1];
	memcpy(f[x],tmp,sizeof(ll)*(tot+1));
	siz[x]=tot;
}

int main()
{
	int n, m, Q;read(n), read(m), read(Q);
	for (int i=1,x,y,z; i<=m; ++i) read(x), read(y), read(z), add(x,y,z);
	f[1]=new ll [2];
	f[1][1]=0;
	siz[1]=1;
	for (int x=1; x<n; ++x)
		for (int i=head[x]; i; i=Next[i]) merge(ver[i],x,edge[i]);
	while (Q--)
	{
		int x; ll y;
		read(x), read(y);
		ll l=y, r=1.1*y, *p=f[x];
		bool flag=0;
		for (int i=1; i<=siz[x]; ++i)
			if (l<=p[i] && p[i]<=r)
			{
				flag=1;
				break;
			}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
```

# C. 动态矩阵最短路

## title

[zhengruioi](http://zhengruioi.com/problem/962)

题意：

>一个 $n$ 行 $m$ 列的矩阵，初始所有位置都是 $0$ 。有 $Q$ 次操作。操作有三种：
>
>- `1 x` 将矩阵第 $x$ 行设为 $0$ 。$(1\leqslant x\leqslant n)$ ；
>- `2 x` 将矩阵第 $x$ 列设为 $0$ 。$(1\leqslant x\leqslant m)$ ；
>- `3 a b c d v` 只考虑值小于等于 $v$ 的位置，询问这些位置是否将 $(a,b)$ 与 $(c,d)$ 四联通，若不联通输出 `-1` ，否则输出它们之间的最短距离。（四联通即只通过上下左右移动就可以互相到达，且每次只能从一个小于等于 $v$ 的位置移到另一个小于等于 $v$ 的位置） $(1\leqslant a,c\leqslant n,1\leqslant b,d\leqslant m,0\leqslant v\leqslant Q)$ 。
>
>每次操作前矩阵中的所有数字都会增加 $1$ 。

## analysis

三个操作的处理：

1. 维护一颗行的线段树，同时维护一个 $row[i]$ 表示第 $i$ 行最晚被消除的时间；
2. 维护一颗列的线段树，同时维护一个 $col[i]$ 表示第 $i$ 列最晚被消除的时间；
3. 上述操作的作用都是为了这个查询所做的，为何要用线段树？因为对于一个询问，这个行列在询问中出现当且仅当它的值大于等于某个数（不一定是询问中的 $v$ ，为了配合上面的操作，是需要一定变化的，这个详细看代码），所以要找到在 $k$ 位置后的第一个大于等于 $v$ 的位置，在 $k$ 位置前的最后一个大于等于 $v$ 的位置，这两个操作可以用线段树树上二分解决。然后因为答案是曼哈顿距离，所以这些线段树还需要支持单点修改区间查询极值的操作。

## code

```cpp
#include<bits/stdc++.h>

const int maxn=1e5+10, inf=0x3f3f3f3f;

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

struct SGT
{
	int Max[maxn<<2],Min[maxn<<2];
	inline void pushup(int x)//上传标记
	{
		Max[x]=max(Max[x<<1],Max[x<<1|1]);
		Min[x]=min(Min[x<<1],Min[x<<1|1]);//颇字面意思
	}

	inline void Change(int x,int l,int r,int k,int v)//权值为当前行列最后一次被消除的时间
	{
		if (l==r)
		{
			Max[x]=Min[x]=v;
			return ;
		}
		int mid=(l+r)>>1;
		if (k<=mid) Change(x<<1,l,mid,k,v);
		else Change(x<<1|1,mid+1,r,k,v);
		pushup(x);
	}

	inline int QueryL(int x,int l,int r,int v)
	{
		if (l==r) return Max[x]>=v ? l : 0;
		int mid=(l+r)>>1;
		if (Max[x<<1|1]>=v) return QueryL(x<<1|1,mid+1,r,v);//因为要找到前方最后一个合法的位置，所以要尽量靠右边些
		else return QueryL(x<<1,l,mid,v);//所以条件为右儿子的权值是否合法
	}

	inline int queryl(int x,int l,int r,int k,int v)//找到在 k 位置前的最后一个大于等于 v 的位置
	{
		if (l==r) return Max[x]>=v ? l : 0;
		int mid=(l+r)>>1;
		if (k<=mid) return queryl(x<<1,l,mid,k,v);//注意判断条件，找前方，即左边
		else
		{
			int t=queryl(x<<1|1,mid+1,r,k,v);
			if (t) return t;
			return QueryL(x<<1,l,mid,v);//在左区间进行线段树树上二分
		}
	}

	inline int QueryR(int x,int l,int r,int v)
	{
		if (l==r) return Max[x]>=v ? l : 0;
		int mid=(l+r)>>1;
		if (Max[x<<1]>=v) return QueryR(x<<1,l,mid,v);//因为要找到后方第一个合法的位置，所以要尽量靠左边些
		else return QueryR(x<<1|1,mid+1,r,v);//所以条件为左儿子的权值是否合法
	}

	inline int queryr(int x,int l,int r,int k,int v)//找到在 k 位置后的第一个大于等于 v 的位置
	{
		if (l==r) return Max[x]>=v ? l : 0;
		int mid=(l+r)>>1;
		if (k>mid) return queryr(x<<1|1,mid+1,r,k,v);//注意判断条件，找后方，即右边
		else
		{
			int t=queryr(x<<1,l,mid,k,v);
			if (t) return t;
			return QueryR(x<<1|1,mid+1,r,v);//在右区间进行线段树树上二分
		}
	}

	inline int querymin(int x,int l,int r,int tl,int tr)//查询 [tl,tr] 区间的最小值
	{
		if (tl<=l && r<=tr) return Min[x];
		int mid=(l+r)>>1;
		int ans=inf;
		if (tl<=mid) chkMin(ans,querymin(x<<1,l,mid,tl,tr));
		if (tr>mid) chkMin(ans,querymin(x<<1|1,mid+1,r,tl,tr));//这个写法就比较常规了，下次要大胆写出来
		return ans;
	}
} R, C;//row，col 各建一颗线段树以便查询区间极值

int row[maxn], col[maxn], n, m, Q;
inline int ask(int a,int b,int c,int d,int v)
{
	if (a==c && b==d) return 0;//同一个点，0 步到达
	if ( (row[a]<v && col[b]<v) || (row[c]<v && col[d]<v) ) return -1;//其中一个点的行列都被 ban
	if ( (row[a]>=v && col[b]>=v) || (row[c]>=v && col[d]>=v) ) return abs(a-c)+abs(b-d);//只要一个点的所在行列均没有被 ban，答案为曼哈顿距离
	//上面的两种情况都不符合，那么现在两个点情况都是：行和列中有一个被 ban
	bool v1=(row[a]>=v), v2=(row[c]>=v);//这里确定两个点的行列中那一个元素被 ban
	if (v1^v2) return abs(a-c)+abs(b-d);//一个点的行是好的，一个点的列是好的，所以存在一条曼哈顿距离路径，画图可知
	//下面就是说两个点情况一样的，要么是行被 ban，要么是列被 ban
	if (v1)//列被 ban
	{
		if (a>c) std::swap(a,c);
		if (R.querymin(1,1,n,a,c)>=v) return abs(a-c)+abs(b-d);//[a,c] 中最早的被消除的时间也合法的话，就一定有解

		if (b>d) std::swap(b,d);
		if (C.Max[1]<v) return -1;////所有列最晚被消除的时间不合法，说明没有一个完整的合法列，旨在查看中转列是否存在

		int t=C.queryr(1,1,m,b,v);//找到在 b 位置后的第一个大于等于 v 的位置
		if (t && t<=d) return abs(a-c)+abs(b-d);//且这个位置在合法区间内
		int ans=inf;
		t=C.queryl(1,1,m,b,v);//向左找中转点
		if (t) chkMin(ans,abs(a-c)+abs(b-t)+abs(d-t));
		t=C.queryr(1,1,m,d,v);//向右找中转点
		if (t) chkMin(ans,abs(a-c)+abs(b-t)+abs(d-t));
		return ans<inf ? ans : -1;
	}
	else//行被 ban
	{
		if (b>d) std::swap(b,d);
		if (C.querymin(1,1,m,b,d)>=v) return abs(a-c)+abs(b-d);//[b,d] 中最早的被消除的时间也合法的话，就一定有解

		if (a>c) std::swap(a,c);
		if (R.Max[1]<v) return -1;//所有行最晚被消除的时间不合法，说明没有一个完整的合法行，旨在查看中转行是否存在

		int t=R.queryr(1,1,n,a,v);//找到在 a 位置后的第一个大于等于 v 的位置
		if (t && t<=c) return abs(a-c)+abs(b-d);//且这个位置在合法区间内
		int ans=inf;
		t=R.queryl(1,1,n,a,v);//向左找中转点
		if (t) chkMin(ans,abs(b-d)+abs(a-t)+abs(c-t));
		t=R.queryr(1,1,n,c,v);//向右找中转点
		if (t) chkMin(ans,abs(b-d)+abs(a-t)+abs(c-t));
		return ans<inf ? ans : -1;
	}
}

int main()
{
	read(n), read(m), read(Q);
	for (int i=1,opt; i<=Q; ++i)
	{
		read(opt);
		if (opt==1)//行的修改
		{
			int x;read(x);
			row[x]=i;
			R.Change(1,1,n,x,i);
		}
		else if (opt==2)//列的修改
		{
			int x;read(x);
			col[x]=i;
			C.Change(1,1,m,x,i);
		}
		else//查询答案
		{
			int a,b,c,d,v;
			read(a), read(b), read(c), read(d), read(v);
			write(ask(a,b,c,d,max(0,i-v)),'\n');//为何这个传递的值为 max(0,(i-v))
		}//缘由：当前 row 的值 = 当前时间 i -它最后一次被消除的时间 row[x]，题目要求：i-row[x]<=v，即 rox[x]>=i-v
	}
	IO::flush();
	return 0;
}
```

# summary

1. 一些其他的参考资料：[duyi](https://www.luogu.org/blog/top-oier/zheng-rui-19csp-s-mu-ni-sai-shi-lian-ce-day3-ti-xie?tdsourcetag=s_pcqq_aiomsg) ；
2. 这场模拟赛的题目都出的很好，学到了一些新东西，并且利用这个上午，我基本上清楚了 $T3$ 的细节，感觉挺好的。
3. 继续加油吧，下午可以搞一下对拍了；
4. 说一下刚刚结束的文化课月考吧，班里 $44$ ，级里 $595$ ，没有差到天际，多少是一些安慰，现在也要开始搞文化课了，恢复两条腿走路吧。