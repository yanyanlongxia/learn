#include<bits/stdc++.h>

typedef long long ll;
const int maxn=1e5+10;

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

ll ans;
int h[maxn];
int main()
{
	int n,m;
	read(n);read(m);
	for (int i=1; i<=n; ++i) read(h[i]);
	std::sort(h+1,h+n+1);
	int cnt=n;
	for (int i=1; i<=m; ++i)
	{
		if (!cnt) break;
		if (cnt>2)
		{
			for (int j=1; j<=n; ++j)
			{
				--h[j];
				if (!h[j]) --cnt;
			}
			ans+=cnt;
		}
		else
		{
			h[n-cnt+1]-=2;
			if (!h[n-cnt+1]) --cnt;
			else if (h[n-cnt+1]<0) --cnt, --i;
			ans+=cnt;
		}
	}
	for (int i=1; i<=n; ++i)
		if (h[i]>0) ans+=(1ll*(n-i+1)*(h[i]-1)+n-i);
	write(ans,'\n');
	IO::flush();
	return 0;
}
