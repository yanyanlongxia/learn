# title

[LUOGU AT2304](https://www.luogu.org/problem/AT2304)

简化题意：

> 一棵树，第 $i$ 个节点上有 $a_i$ 个石头，每次选择两个叶子节点（度数为 1 的节点），将路径上经过的（包括起点终点）所有节点上都取走一个石头，如果路径上有一个点上没石头这个操作就不能进行，问能不能取完所有石头。

# analysis

取一非叶节点作为树的根。设节点 $x$ 的点权为 $A[x]$ （根据题意，这个点权可以理解为经过节点 $x$ 的路径总数） 。

对任意非叶节点 $x$ ，设 $x$ 的儿子 $y$ 的 $A[y]$ 之和为 $sum$ ，设 $a$ 为经过 $x$ 且在 其子树 中的路径数，$b$ 为经过 $x$ 且不在 其子树 中的路径数，则有方程组
$$
\begin{cases}2*a+b=sum\\ a+b=A[x]\end{cases}
$$


所以 
$$
\begin{cases}a=sum-A[x]\\ b=2*A[x]-sum\end{cases}
$$


再进行一些必要性的检验，如 
$$
a\geqslant 0、b\geqslant 0、a\leqslant\min\left\{sum-maxpart,sum/2\right\}(maxpart~为~x~的儿子~y~的~A[y]~的最大值)
$$


若 $x$ 为根则 $b=0$。

最后令 $A[x]=b$ 。

以上就是 $dfs$ 的构思过程。

还要特判一下 $n=2$ 的情况（因为无法确定根）：如果两个节点点权相同则合法。

结合起来就可以解决这道题目了。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+10;

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

int ver[maxn<<1],Next[maxn<<1],head[maxn],len,deg[maxn];
inline void add(int x,int y)
{
	ver[++len]=y,Next[len]=head[x],head[x]=len;
}

ll A[maxn];
bool flag=1;
inline void dfs(int x,int fa)
{
	ll sum=0,maxpart=0; int o=0;
	for (int i=head[x]; i; i=Next[i])
	{
		int y=ver[i];
		if (y==fa) continue;
		++o;
		dfs(y,x);
		sum+=A[y];
		maxpart=max(maxpart,A[y]);
	}
	if (!o) return ;
	ll a=sum-A[x],b=(A[x]<<1)-sum;
	if (a<0 || b<0 || a>min(sum-maxpart,sum>>1) || (fa==-1 && b)) flag=0;
	A[x]=b;
}

int main()
{
	int n;read(n);
	for (int i=1; i<=n; ++i) read(A[i]);
	for (int i=1,a,b; i<n; ++i) read(a),read(b),add(a,b),add(b,a),++deg[a],++deg[b];
	int root=0;
	for (int i=1; i<=n; ++i)
		if (deg[i]>1) { root=i; break; }
	if (root) dfs(root,-1);
	else flag=(A[1]==A[2]);
	puts(flag?"YES":"NO");
	return 0;
}
```