#include<bits/stdc++.h>

#define file(s) freopen(s".in","r",stdin), freopen(s".out","w",stdout)

#define G ch=getchar()
#define DeBug(x) std::cout<<#x<<':'<<x<<std::endl

#define mp std::make_pair
typedef std::pair<int,int> pii;
const int MaxN=2e3+10, MaxX=4e3+10, inf=0x3f3f3f3f;

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

template<typename T>inline bool chkMin(T &a,const T &b) { return b<a ? (a=b, true) : false; }//ÖØÔØÁË<
template<typename T>inline bool chkMax(T &a,const T &b) { return a<b ? (a=b, true) : false; }
template<typename T>inline T min(T a,T b) { return a<b ? a : b; }
template<typename T>inline T max(T a,T b) { return a>b ? a : b; }

struct Orz{int x, y, z;} a[MaxN], pre[MaxN][MaxN*6];
inline bool operator < (const Orz x, const Orz y)
{
	if (x.x!=y.x) return x.x>y.x;
	if (x.y!=y.y) return x.y>y.y;
	return x.z>y.z;
}

int f[2][MaxX][MaxX], vis[MaxN], X, n;
inline void Clear(int cur, int m)
{
	for (int i=0; i<=X; ++i) f[cur][0][i]=f[cur][i][0]=-inf;
	for (int i=0; i<=m; ++i) f[cur][i][m-i]=-inf;
}

inline int getnum(int y, int z)
{
	if (!y) return X+z;
	if (!z) return (X<<1|1)+y;
	return y;
}

int cur;
inline void update(int ax, int ay, int bx, int by, int c, int i, int x)
{
	if (chkMax(f[cur][ax][ay], f[cur^1][bx][by]+c)) pre[i][getnum(ax, ay)]=(Orz){x, bx, by};
}

inline void print(int x, int y, int z)
{
	if (!x)
	{
		for (int i=1; i<=n; ++i)
			if (!vis[i]) write(i, ' ');
		return ;
	}
	Orz t=pre[x][getnum(y, z)];
	vis[t.x]=1;
	print(x-1, t.y, t.z);
	if (t.x) write(t.x, ' ');
}

int main()
{
	read(X), read(n); int m=X;
	for (int i=1; i<=n; ++i) read(a[i].x), a[i].z=i;
	for (int i=1; i<=n; ++i) read(a[i].y);
	std::sort(a+1, a+n+1);

	Clear(cur, m);
	for (int i=0; i<=X; ++i) f[cur][i][X-i]=0;

	for (int i=1; i<=n; ++i)
	{
		cur^=1, Clear(cur, max(0, m-a[i].x));
		for (int j=0; j<=m; ++j) update(max(0, j-a[i].x), m-j, j, m-j, max(0, a[i].y-max(0, j-a[i].x)), i, a[i].z), update(j, max(0, m-j-a[i].x), j, m-j, 0, i, 0);
		for (int j=0; j<=X; ++j) update(0, j, 0, j, a[i].y, i, a[i].z), update(0, max(0, j-a[i].x), 0, j, 0, i, 0);
		for (int j=0; j<=X; ++j) update(max(0, j-a[i].x), 0, j, 0, max(0, a[i].y-max(0, j-a[i].x)), i, a[i].z), update(j, 0, j, 0, 0, i, 0);
		m=max(0, m-a[i].x);
	}

	Orz ans=(Orz){-inf, 0, 0};
	for (int i=0; i<=X; ++i) chkMin(ans, (Orz){f[cur][i][0], i, 0});
	write(ans.x, '\n');
	print(n, ans.y, ans.z), *IO::fe++='\n';
	IO::flush();
	return 0;
}
