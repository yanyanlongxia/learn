#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

const int MaxN=2e5+10;

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

int a[MaxN], b[MaxN];
char s1[MaxN], s2[MaxN], s[MaxN];
inline bool chk(char *s, int n)
{
	for (int i=1; i<=n; ++i)
		if (s[i]=='*') return 1;
	return 0;
}

int main()
{
	int T; read(T);
	while (T--)
	{
		scanf("%s%s", s1+1, s2+1);
		int n1=strlen(s1+1), n2=strlen(s2+1);
		if (n1==n2 && !chk(s1,n1) && !chk(s2,n2))
		{
			for (int i=1; i<=n1; ++i)
				if (s1[i]!=s2[i] || s1[i]=='?') *IO::fe++='?';
				else *IO::fe++=s1[i];
			*IO::fe++='\n';
		}
		else
		{
			int x1=0, x2=0, pl, pr;
			for (int i=1; i<=n1; ++i) x1+=s1[i]!='*';
			for (int i=1; i<=n2; ++i) x2+=s2[i]!='*';

			int n=pl=pr=min(x1, x2);
			for (int i=1; i<=n; ++i) a[i]=b[i]=0;

			for (int i=1; i<=n; ++i)
				if (s1[i]=='*' || s2[i]=='*') { pl=i-1; break; }
			for (int i=1; i<=pl; ++i)
				if (s1[i]==s2[i] && s1[i]!='?') a[i]=1;

			for (int i=1; i<=n; ++i)
				if (s1[n1-i+1]=='*' || s2[n2-i+1]=='*') { pr=i-1; break; }
			for (int i=1; i<=pr; ++i)
				if (s1[n1-i+1]==s2[n2-i+1] && s1[n1-i+1]!='?') b[i]=1;

			for (int i=1; i<=n; ++i) a[i]+=a[i-1], b[i]+=b[i-1];

			int Max=0, pos=0; bool flag=0;
			for (int i=0; i<=n; ++i)
				if (chkMax(Max, a[i]+b[n-i])) pos=i;

			for (int i=1; i<=pos; ++i)
			{
				if (s1[i]=='*' || s2[i]=='*') flag=1;
				if (flag || s1[i]!=s2[i]) *IO::fe++='?';
				else *IO::fe++=s1[i];
			}
			*IO::fe++='*';

			flag=0;
			for (int i=1; i<=n-pos; ++i)
			{
				if (s1[n1-i+1]=='*' || s2[n2-i+1]=='*') flag=1;
				if (flag || s1[n1-i+1]!=s2[n2-i+1]) s[i]='?';
				else s[i]=s1[n1-i+1];
			}
			for (int i=1; i<=n-pos; ++i) *IO::fe++=s[n-pos-i+1];
			*IO::fe++='\n';
		}
	}
	IO::flush();
	return 0;
}
