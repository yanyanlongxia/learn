#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

typedef long long ll;
const int maxn=3e5+10, inf=0x3f3f3f3f;

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

template<typename T>inline T min(T a,T b) { return a<b ? a : b; }
template<typename T>inline T max(T a,T b) { return a>b ? a : b; }

int a[maxn], n;
struct SGT
{
	struct Orz{int l,r,z;}c[maxn<<2];
	inline void build(int x,int l,int r)
	{
		c[x].l=l, c[x].r=r;
		if (l==r) { c[x].z=a[l]; return ; }
		int mid=(l+r)>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
		c[x].z=min(c[x<<1].z,c[x<<1|1].z);
	}

	inline void Change(int x,int k)
	{
		int l=c[x].l, r=c[x].r;
		if (l==r) { c[x].z=inf; return ; }
		int mid=(l+r)>>1;
		if (k<=mid) Change(x<<1,k);
		else Change(x<<1|1,k);
		c[x].z=min(c[x<<1].z,c[x<<1|1].z);
	}

	inline int query(int x,int v)
	{
		int l=c[x].l, r=c[x].r;
		if (l==r) return l;
		if (c[x].z>v) return n+1;
		if (c[x<<1].z<=v) return query(x<<1,v);
		return query(x<<1|1,v);
	}
} sgt;

int main()
{
//	file("sequence");

	read(n);
	for (int i=1; i<=n; ++i) read(a[i]);
	ll ans=0;
	sgt.build(1,1,n);
	for (int i=1; i<=n; ++i)
	{
		sgt.Change(1,i);
		ans+=a[i];
		ll last=a[i];
		for (int j=i+1, t; j<=n; j=t)
		{
			t=sgt.query(1,last), ans+=last*(t-j);
			if (t<=n) last%=a[t];
		}
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
