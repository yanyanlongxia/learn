#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

typedef long long ll;
const int maxn=1e5+10;
typedef int iarr[maxn];

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

const int M=1e3;
iarr s, d; int K, n, m;
std::queue<int>q;

inline int bfs()
{
	while (!q.empty())
	{
		int x=q.front();
		q.pop();
		if (!x) return d[x+M];
		for (int i=-M; i<=M; ++i) if (s[i+M])
		{
			int y=i+x;
			if (-m<=y && y<=m && !d[y+M]) d[y+M]=d[x+M]+1, q.push(y);
		}
	}
 return -1;
}

int main()
{
	read(K), read(n), read(m);
	for (int i=1, x; i<=K; ++i)
	{
		read(x);
		x-=n;
		s[x+M]=d[x+M]=1, q.push(x);
	}
	write(bfs(),'\n');
	IO::flush();
	return 0;
}
