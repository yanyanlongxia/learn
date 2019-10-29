#include<bits/stdc++.h>

const int maxn=1e5+10;
typedef int iarr[maxn];

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

char str[maxn];
iarr pos, nxt, sum;
inline int pre(int n)
{
	int cnt=0;
	for (int i=1; i<=n; ++i)
		if (str[i]=='0') pos[++cnt]=i;
		else sum[i]=cnt;//1 的前面有几个 0
	int last=n+1;
	for (int i=n; i>=1; --i)
		if (str[i]=='1') last=i;
		else nxt[i]=last;//将每个 0 都与他之后最近的 1 匹配
	return cnt;
}

int main()
{
	scanf("%s",str+1);
	int n=strlen(str+1);
	int m=pre(n);//0 的个数
	int ans=n-m;//1 的个数
	for (int i=1; 2*i<=m; ++i)
	{
		int cur=0, s=0;
		while (1)
		{
			cur+=i;
			if (cur>m || nxt[pos[cur]]>n) break;
			int x=nxt[pos[cur]];
			cur=sum[x];
			++s;
			if (cur+i<=m) chkMax(ans,(s+1)*i+s);
		}
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
