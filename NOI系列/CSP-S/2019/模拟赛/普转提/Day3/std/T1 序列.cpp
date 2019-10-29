#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

typedef long long ll;
const int maxn=1e5+10;

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

inline ll Quick_Power(ll a,ll b,ll p)
{
	ll ans=1;
	while (b)
	{
		if (b&1) ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}

ll a[maxn], p;
std::map<ll,ll> mark;

int main()
{
	int n; read(n), read(p);
	for (int i=1; i<=n; ++i)
	{
		read(a[i]);
		if (!4*a[i]%p*a[i]%p) continue;
		else ++mark[4*a[i]%p*a[i]%p];
	}
	ll ans=0;
	for (int i=1; i<=n; ++i)
	{
		ll inv=Quick_Power(a[i],p-2,p);
		if (!inv) continue;
		ans+=mark[inv];
		if (4*a[i]%p*a[i]%p==inv) --ans;
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
