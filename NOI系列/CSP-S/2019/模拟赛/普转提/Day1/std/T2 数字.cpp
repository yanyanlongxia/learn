#include<bits/stdc++.h>

typedef long long ll;

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

int main()
{
	int T;read(T);
	while (T--)
	{
		ll n,m;read(n);read(m);
		ll b=n/m, c=b/10, d=b-c*10;//n 中能够整除 m 的数的个数，整块数量，散块大小
		ll ans=0;
		for (int i=1; i<=10; ++i) ans+=i*m%10;
		ans=ans*c;
		for (int i=1; i<=d; ++i) ans+=i*m%10;
		write(ans,'\n');
	}
	IO::flush();
	return 0;
}
