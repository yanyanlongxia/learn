#include<bits/stdc++.h>

const int maxn=110;

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

int d[maxn],g[maxn];
int f[maxn][maxn];
int main()
{
	int T;read(T);
	while (T--)
	{
		memset(f,0,sizeof(f));
		for (int i=1; i<=9; ++i) read(d[i]);
		int cnt=0;
		f[0][0]=1;
		for (int i=1; i<=9; ++i)
			for (int j=1; j<=d[i]; ++j)
			{
				for (int k=cnt; k>=0; --k)
				{
					for (int l=0; l<=10; ++l) g[l]=f[k][l], f[k][l]=0;
					for (int l=0; l<=10; ++l) f[k+1][(l+i)%11]|=g[l], f[k][(l-i+11)%11]|=g[l];
				}
				++cnt;
			}
		int ans=0x3f3f3f3f;
		for (int i=0; i<=cnt; ++i)
			if (f[i][0]) chkMin(ans,max(i,cnt-i)*2-1);
		if (ans==0x3f3f3f3f) ans=-1;
		if (!ans) ans=1;
		write(ans,'\n');
	}
	IO::flush();
	return 0;
}
