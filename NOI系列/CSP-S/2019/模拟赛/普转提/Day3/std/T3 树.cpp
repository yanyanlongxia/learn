#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

typedef long long ll;
const int maxn=2e5+10;

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

int fa[maxn];
inline int get(int x)
{
	return fa[x]==x ? x : fa[x]=get(fa[x]);
}

int main()
{
	int n, ans=0, cnt=0; read(n);
	for (int i=1; i<=n; ++i) fa[i]=i;
	for (int i=1, a; i<=n; ++i)
	{
		read(a);
		int x=get(a), y=get(i);
		if (x^y || a==i) fa[x]=y;
		else ++cnt;
	}
	for (int i=1; i<=n; ++i) if (fa[i]==i) ++ans;
	cnt==ans ? write(ans,'\n') : write(ans-1,'\n');
	IO::flush();
	return 0;
}
