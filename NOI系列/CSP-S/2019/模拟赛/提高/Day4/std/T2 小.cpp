#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

typedef long long ll;
const int MaxN=1e6+10;

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

template<typename T>inline bool chkMin(T &a,const T &b) { return a>b ? (a=b, true) : false; }
template<typename T>inline bool chkMax(T &a,const T &b) { return a<b ? (a=b, true) : false; }
template<typename T>inline T min(T a,T b) { return a<b ? a : b; }
template<typename T>inline T max(T a,T b) { return a>b ? a : b; }

int isnopr[MaxN], prime[MaxN], cnt, N;
inline void Pre()
{
	for (int i=2; i<=N; ++i)
		if (!isnopr[i])
		{
			prime[++cnt]=i;
			for (int j=i<<1; j<=N; j+=i) isnopr[j]=1;
		}
}

int a[MaxN], pos[MaxN], n, l, len;
inline void work(int p)
{
	memset(pos, -1, sizeof(pos));
	int x=n;
	pos[n]=0;
	for (int i=1; i<=n; ++i)
	{
		if (a[i]%p) --x;
		else ++x;
		if (pos[x]==-1) pos[x]=i;
		else
		{
			if (len<i-pos[x]) len=i-pos[x], l=pos[x]+1;
			else if (len==i-pos[x]) chkMin(l, pos[x]+1);
		}
	}
	if (x>=n) l=1, len=n;
}

int main()
{
	read(n);
	for (int i=1; i<=n; ++i) read(a[i]), chkMax(N, a[i]);
	Pre();
	for (int i=1; i<=min(40, cnt); ++i)
	{
		work(prime[i]);
		if (len==n) break;
	}
	write(l, ' '), write(max(0, l+len-1), '\n');
	IO::flush();
	return 0;
}
