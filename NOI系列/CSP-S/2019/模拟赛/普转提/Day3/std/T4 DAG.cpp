#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

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

template<typename T>inline bool chkMin(T &a,const T &b) { a>b ? (a=b, true) : false; }
template<typename T>inline bool chkMax(T &a,const T &b) { a<b ? (a=b, true) : false; }

int a[20][20], f[1<<20];
bool ok[1<<20];
int main()
{
	int n, m; read(n), read(m);
	for (int i=1, x, y; i<=m; ++i) read(x), read(y), a[x-1][y-1]=a[y-1][x-1]=1;

	for (int s=1; s<(1<<n); ++s)
	{
		ok[s]=1;
		for (int j=0; j<n; ++j) if (s>>j&1)
			for (int k=0; k<n; ++k) if (s>>k&1)
				if (a[k][j] || a[j][k]) ok[s]=0;
	}

	for (int s=1; s<(1<<n); ++s)
	{
		f[s]=1e9;
		if (ok[s]) { f[s]=1; continue; }
		for (int t=(s-1)&s; t; t=(t-1)&s)
			if (ok[t]) chkMin(f[s],f[s^t]+1);
	}
	write(f[(1<<n)-1]-1,'\n');
	IO::flush();
	return 0;
}
