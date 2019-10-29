#include<bits/stdc++.h>

const int maxn=1e6+10,maxm=2e7+10;

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

int son[maxm][2],num[maxm],cnt;//num[i] 表示节点 i 出现的次数
inline void add(int x,int k)
{
	int now=0;
	for (int i=0; i<30; ++i)
	{
		int c=x>>i&1;
		if (!son[now][c]) son[now][c]=++cnt;
		now=son[now][c];
	}
	num[now]+=k;//是当前这个节点的次数
}

int seq[35],lazy;
inline void Change()
{
	int now=0, len=0, full=(1u<<30)-1^lazy;
	for (int i=0; i<30; ++i)//找到一条全为 1 的链
	{
		seq[len++]=now;
		now=son[now][full>>i&1];
		if (!now) break;
	}
	for (int i=0; i<len; ++i) std::swap(son[seq[i]][0],son[seq[i]][1]);//然后把他们的左右儿子翻转，相当于 +1 了
}

int ans[maxn],tot;
inline void dfs(int x,int val,int deep)
{
	for (int i=0; i<num[x]; ++i) ans[++tot]=val^lazy;
	for (int i=0; i<2; ++i)
		if (son[x][i]) dfs(son[x][i],val|(i<<deep),deep+1);
}

int main()
{
	int n,q;read(n);read(q);
	for (int i=1,x; i<=n; ++i) read(x), add(x,1);
	for (int i=1,opt,x; i<=q; ++i)
	{
		read(opt);
		if (opt==1) read(x), add(x^lazy,1);
		else if (opt==2) read(x), add(x^lazy,-1);
		else if (opt==3) Change();
		else read(x), lazy^=x;
	}
	dfs(0,0,0);
	std::sort(ans+1,ans+tot+1);
	for (int i=1; i<=tot; ++i) write(ans[i],' ');
	IO::flush();
	return 0;
}
