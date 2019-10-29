#include<bits/stdc++.h>

#define mp std::make_pair
typedef std::pair<int,int> pii;
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

int fa[maxn][2],dist[maxn][2];
inline int get(int x,int t)//type
{
	if (x==fa[x][t]) return x;
	int ans=get(fa[x][t],t);
	dist[x][t]+=dist[fa[x][t]][t];//带权并查集
	return fa[x][t]=ans;
}

int n,to[maxn][2];
bool vis[maxn][2];
inline bool check(int k)
{
	for (int i=1; i<=n; ++i) fa[i][0]=fa[i][1]=i,dist[i][0]=dist[i][1]=vis[i][0]=vis[i][1]=0;
	std::queue<pii>q;
	q.push(mp(1,0)),q.push(mp(1,1));
	vis[1][0]=vis[1][1]=1;
	while (!q.empty())
	{
		int x=q.front().first, t=q.front().second;
		q.pop();
		x=to[x][t];
		int rt=x;
		while (1)
		{
			rt=get(rt,t);
			if (vis[rt][t^1]) break;
			get(x,t);
			if (dist[x][t]>=k) break;
			vis[rt][t^1]=1;
			q.push(mp(rt,t^1));
			if (rt==get(to[rt][t],t)) break;//自环
			fa[rt][t]=to[rt][t];//
			++dist[rt][t];
		}
	}
	return vis[n][0] | vis[n][1];
}

int main()
{
	read(n);
	for (int i=1; i<=n; ++i) read(to[i][0]),read(to[i][1]);
	int l=0,r=n,ans=-1;
	while (l<=r)//最小化最大，二分答案
	{
		int mid=(l+r)>>1;
		if (check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
