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

int ver[maxn],Next[maxn],head[maxn],len=1;
ll edge[maxn];
inline void add(int x,int y,ll z)
{
	ver[++len]=y,edge[len]=z,Next[len]=head[x],head[x]=len;
}

int siz[maxn];
ll *f[maxn];
inline void merge(int x,int y,int z)
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
	int n,m,Q;
	read(n);read(m);read(Q);
	for (int i=1,x,y,z; i<=m; ++i) read(x), read(y), read(z), add(x,y,z);
	f[1]=new ll [2];
	f[1][1]=0;
	siz[1]=1;
	for (int x=1; x<n; ++x)
		for (int i=head[x]; i; i=Next[i]) merge(ver[i],x,edge[i]);
	while (Q--)
	{
		int x;ll y;
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
