#include<bits/stdc++.h>

typedef long long ll;
const int maxn=1<<20,mod=1e9+7;

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

inline int lowbit(int x)
{
	return x & -x;
}

inline ll popcount(ll x)
{
	ll ans=0;
	while (x) ++ans, x-=lowbit(x);
	return ans;
}

ll c[maxn],p[maxn];
int main()
{
	int n,m;read(n);read(m);
	for (int i=1,k; i<=n; ++i)
	{
		read(k); ll tmp=0;
		for (int j=1,t; j<=k; ++j) read(t), --t, tmp|=1<<t;
		++c[tmp];
	}
	p[0]=1;
	for (int i=1; i<=n; ++i) p[i]=p[i-1]*2%mod;
	for (int i=0; i<m; ++i)
		for (int j=0; j<(1<<m); ++j)
		{
			if (j>>i&1) continue;
			c[j|(1<<i)]+=c[j];
		}
	ll ans=0;
	for (int i=0; i<(1<<m); ++i)
	{
		if (popcount(i)%2==m%2) ans+=p[c[i]];
		else ans-=p[c[i]];
		ans=(ans+mod)%mod;
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
