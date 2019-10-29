#include<bits/stdc++.h>

const int maxn=2e5+10,maxk=1e6;

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

std::vector<int>E[maxn], W[maxn], V[maxk+10];
inline void add(int x,int y,int z)
{
	E[x].push_back(y), W[x].push_back(z);
}

int dep[maxn],fa[maxn][21],gg[maxn][21];
inline void dfs(int x,int f)
{
	dep[x]=dep[f]+1, fa[x][0]=f;
	for (int i=0; i<(int)E[x].size(); ++i)
	{
		int y=E[x][i];
		if (y==f) continue;
		gg[y][0]=W[x][i];//y 到 其父亲的边的 gcd 只能是边权了
		dfs(y,x);
	}
}

inline int getd(int x,int d)//就是把 x 往上跳的那一步拿出来了
{
	for (int i=20; i>=0; --i)
		if (d>>i&1) x=fa[x][i];
	return x;
}

inline int LCA(int x,int y)
{
	if (dep[x]<dep[y]) std::swap(x,y);
	x=getd(x,dep[x]-dep[y]);
	if (x==y) return x;
	for (int i=20; i>=0; --i)
		if (fa[x][i]^fa[y][i]) x=fa[x][i], y=fa[y][i];
	return fa[x][0];
}

inline int gcd(int a,int b)
{
	return b ? gcd(b,a%b) : a;
}

inline int getgcd(int x,int d)//倍增求gcd
{
	int r=0;
	for (int i=20; i>=0; --i)
		if (d>>i&1) r=gcd(r,gg[x][i]), x=fa[x][i];
	return r;
}

inline int pre(int x,int fa)
{
	int d=0;
	for (int i=0; i<(int)E[x].size(); ++i)
	{
		int y=E[x][i];
		if (y==fa) continue;
		chkMax(d,pre(y,x)+1);
	}
	return d;
}

inline int solve(int x,int fa,int pr)
{
	int d=0;
	for (int i=0; i<(int)E[x].size(); ++i)
	{
		int y=E[x][i];
		if (y^fa && (W[x][i]%pr==0)) chkMax(d,solve(y,x,pr)+1);
	}
	return d;
}

bool vis[maxk+10];
int main()
{
	int n,q;read(n);read(q);
	for (int i=1,x,y,z; i<n; ++i) read(x),read(y),read(z),add(x,y,z),add(y,x,z);

	vis[1]=1;
	for (int i=2; i<=maxk; ++i)
		if (!vis[i])
			for (int j=i; j<=maxk; j+=i)//分解质因子
			{
				if (i^j) vis[j]=1;
				V[j].push_back(i);
			}

	dfs(1,0);
	for (int i=1; i<=20; ++i)
		for (int x=1; x<=n; ++x) fa[x][i]=fa[fa[x][i-1]][i-1];
	for (int i=1; i<=20; ++i)
		for (int x=1; x<=n; ++x) gg[x][i]=gcd(gg[x][i-1],gg[fa[x][i-1]][i-1]);//统一放在后面处理了
	for (int i=1,x,y,fx,fy; i<=q; ++i)
	{
		read(x),read(y);
		int z=LCA(x,y), dist=dep[x]+dep[y]-(dep[z]<<1), g=gcd(getgcd(x,dep[x]-dep[z]),getgcd(y,dep[y]-dep[z]));

		if (z==y) fy=getd(x,dep[x]-dep[z]-1), fx=fa[x][0];
		else if (z==x) fx=getd(y,dep[y]-dep[z]-1), fy=fa[y][0];
		else fx=fa[x][0], fy=fa[y][0];

		if (g==1) { write(dist,'\n'); continue;	}
		int res=pre(x,fx)+pre(y,fy), ans=0;
		for (int i=0; i<(int)V[g].size(); ++i) chkMax(ans,solve(x,fx,V[g][i])+solve(y,fy,V[g][i]));//最长的不满条件的 l
		write(ans==res ? -1 : ans+dist+1,'\n');
	}
	IO::flush();
	return 0;
}
