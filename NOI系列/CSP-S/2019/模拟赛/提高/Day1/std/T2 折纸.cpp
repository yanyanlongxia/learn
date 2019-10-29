#include<bits/stdc++.h>

typedef long long ll;
const int maxn=2e6+10;

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

char s[maxn],tt[maxn];
std::string o[maxn];
inline int manacher(int *P,char *c,int L)
{
	int len=0;
	s[0]='(';
	for (int i=1; i<=L; ++i)
	{
		s[++len]='#';
		s[++len]=c[i];
	}
	s[++len]='#', s[++len]=')';
	int mx=0, id=0;
	for (int i=1; i<len; ++i)
	{
		if (i<mx) P[i]=min(mx-i,P[(id<<1)-i]);
		else P[i]=1;
		while (s[i+P[i]]==s[i-P[i]]) ++P[i];
		if (i+P[i]>mx) mx=i+P[i], id=i;
	}
	return len;
}

int HL[maxn],HR[maxn],WL[maxn],WR[maxn],t[maxn];
int main()
{
	int n,m;read(n);read(m);
	for (int i=1; i<=n; ++i) std::cin>>o[i];

	for (int i=1; i<=n-1; ++i) HL[i]=HR[i]=1;
	for (int i=1; i<=m-1; ++i) WL[i]=WR[i]=1;

	for (int i=1; i<=n; ++i)
	{
		for (int j=1; j<=m; ++j) tt[j]=o[i][j-1];
		int len=manacher(t,tt,m)-3;
		int mx=1;
		for (int j=3; j<=len; j+=2)
		{
			if (j-t[j]+1<=mx) mx=j;
			else WL[j>>1]=0;
		}
		int mn=len+2;
		for (int j=len; j>=3; j-=2)
		{
			if (j+t[j]-1>=mn) mn=j;
			else WR[j>>1]=0;
		}
	}
	ll ansW=0;
	int sum=0;
	WL[0]=1, WR[m]=1;
	for (int i=0; i<=m; ++i) sum+=WR[i];
	for (int i=0; i<=m; ++i)
	{
		if (WR[i]) --sum;
		if (WL[i]) ansW+=sum;
	}

	std::swap(n,m);

	for (int i=1; i<=n; ++i)
	{
		for (int j=1; j<=m; ++j) tt[j]=o[j][i-1];
		int len=manacher(t,tt,m)-3;
		int mx=1;
		for (int j=3; j<=len; j+=2)
		{
			if (j-t[j]+1<=mx) mx=j;
			else HL[j>>1]=0;
		}
		int mn=len+2;
		for (int j=len; j>=3; j-=2)
		{
			if (j+t[j]-1>=mn) mn=j;
			else HR[j>>1]=0;
		}
	}
	ll ansH=0;
	sum=0;
	HL[0]=1, HR[m]=1;
	for (int i=0; i<=m; ++i) sum+=HR[i];
	for (int i=0; i<=m; ++i)
	{
		if (HR[i]) --sum;
		if (HL[i]) ansH+=sum;
	}

	write(ansW*ansH,'\n');
	IO::flush();
	return 0;
}
