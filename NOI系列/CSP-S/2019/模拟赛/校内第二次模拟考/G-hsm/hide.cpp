#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

const int maxn=1e6+10;
typedef int iarr[maxn];

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

int n, tmp;
iarr a, toup, todn, ans, siz;
std::vector<int> E[maxn];
inline void dfs(int x,int fa)
{
	siz[x]=1;
	for (int i=0; i<(int)E[x].size(); ++i)
	{
		int y=E[x][i];
		if (y^fa) dfs(y,x), siz[x]+=siz[y];
	}
	if (!a[x])
	{
		for (int i=0; i<(int)E[x].size(); ++i)
		{
			int y=E[x][i];
			if (y^fa) chkMax(todn[y],siz[y]);
		}
		chkMax(toup[x],n-siz[x]);
	}
}

inline void dfs_up(int x,int fa)
{
	for (int i=0; i<(int)E[x].size(); ++i)
	{
		int y=E[x][i];
		if (y^fa) dfs_up(y,x), chkMax(toup[x],toup[y]), chkMax(ans[x], toup[y]);
	}
	int p=0, q=0;
	for (int i=0; i<(int)E[x].size(); ++i)
	{
		int y=E[x][i];
		if (y^fa) chkMax(todn[y],p), chkMax(p,toup[y]);
	}
	std::reverse(E[x].begin(),E[x].end());
	for (int i=0; i<(int)E[x].size(); ++i)
	{
		int y=E[x][i];
		if (y^fa) chkMax(todn[y],q), chkMax(q,toup[y]);
	}
}

inline void dfs_dn(int x,int fa)
{
	chkMax(ans[x],todn[x]);
	for (int i=0; i<(int)E[x].size(); ++i)
	{
		int y=E[x][i];
		if (y^fa) chkMax(todn[y],todn[x]), dfs_dn(y,x);
	}
}

int main()
{
//	file("hide");

	read(n);
	for (int i=1; i<=n; ++i) read(a[i]), tmp+=(a[i]==0);
	for (int i=1, x, y; i<n; ++i) read(x), read(y), E[x].push_back(y), E[y].push_back(x);

	if (tmp%2==0)
		for (int i=1; i<=n; ++i) write(n,'\n');
	else
	{
		dfs(1,0), dfs_up(1,0), dfs_dn(1,0);
		for (int i=1; i<=n; ++i) write(ans[i],'\n');
	}
	IO::flush();
	return 0;
}
