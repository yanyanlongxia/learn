# title

[BZOJ 4756](https://www.lydsy.com/JudgeOnline/problem.php?id=4756)

[LUOGU 3605](https://www.luogu.org/problem/P3605)

简化题意：

>$n$ 只奶牛构成了一个树形的公司，每个奶牛有一个能力值 $p_i$，$1$ 号奶牛为树根。 
>问对于每个奶牛来说，它的子树中有几个能力值比它大的。

# analysis

线段树合并裸题，所以学习一下，算是放出了个恶魔。

参考资料：[Mychael](https://www.cnblogs.com/Mychael/p/8665589.html)。

# code

```cpp
#include<bits/stdc++.h>

const int maxn=1e5+10;

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

namespace SGT
{
	struct Orz{int l,r,z;}c[maxn*30];
	int cnt=0;
	inline void Change(int &x,int l,int r,int k)
	{
		if (!x) x=++cnt;
		++c[x].z;
		if (l==r) return ;
		int mid=(l+r)>>1;
		if (k<=mid) Change(c[x].l,l,mid,k);
		else Change(c[x].r,mid+1,r,k);
		c[x].z=c[c[x].l].z+c[c[x].r].z;
	}

	inline int query(int x,int l,int r,int tl,int tr)
	{
		if (!x || tr<tl) return 0;
		if (tl<=l && r<=tr) return c[x].z;
		int mid=(l+r)>>1, ans=0;
		if (tl<=mid) ans+=query(c[x].l,l,mid,tl,tr);
		if (tr>mid) ans+=query(c[x].r,mid+1,r,tl,tr);
		return ans;
	}

	inline int merge(int x,int y)
	{
		if (!x) return y;
		if (!y) return x;
		c[x].l=merge(c[x].l,c[y].l);
		c[x].r=merge(c[x].r,c[y].r);
		c[x].z=c[c[x].l].z+c[c[x].r].z;
		return x;
	}
}

using SGT::Change;
using SGT::query;
using SGT::merge;

int ver[maxn],Next[maxn],head[maxn],len;
inline void add(int x,int y)
{
	ver[++len]=y,Next[len]=head[x],head[x]=len;
}

int tot,n;
int ans[maxn],val[maxn],rt[maxn];
inline void dfs(int x)
{
	for (int i=head[x]; i; i=Next[i])
	{
		int y=ver[i];
		dfs(y);
		rt[x]=merge(rt[x],rt[y]);
	}
	ans[x]=query(rt[x],1,n,val[x]+1,tot);
}

int a[maxn];
int main()
{
	read(n);
	for (int i=1; i<=n; ++i) read(val[i]),a[i]=val[i];
	for (int i=2,x; i<=n; ++i) read(x),add(x,i);
	std::sort(a+1,a+n+1);
	tot=std::unique(a+1,a+n+1)-a-1;
	for (int i=1; i<=n; ++i) val[i]=std::lower_bound(a+1,a+tot+1,val[i])-a;
	for (int i=1; i<=n; ++i) Change(rt[i],1,n,val[i]);
	dfs(1);
	for (int i=1; i<=n; ++i) write(ans[i],'\n');
	IO::flush();
	return 0;
}
```