#include<bits/stdc++.h>

const int maxn=505,maxk=1e3+10;

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

struct Orz{int in,out,w,s,v;}o[maxn];
inline bool cmp(Orz a,Orz b)
{
	return a.out<b.out || (a.out==b.out && a.in>b.in);
}

int f[maxn][maxk],g[maxk];//表示 i 以及 i 上面物品在所有时刻中最大重量为 j 时的最大收益
int main()
{
	int n,S,nowt=0,noww=0;
	read(n);read(S);
	for (int i=1; i<=n; ++i) read(o[i].in),read(o[i].out),read(o[i].w),read(o[i].s),read(o[i].v);
	o[++n]=(Orz){0,n<<1,0,S,0};
	std::sort(o+1,o+n+1,cmp);//按照拿走时间从小到大排（相等则放上去时间从大到小排），保证这个物品上方的物品一定在他前面

	for (int i=1; i<=n; ++i)//枚举物品
		for (int w=o[i].w; w<=S; ++w)//枚举空间（已经放进背包里）
		{
			nowt=o[i].in;//现在的时间
			g[nowt]=0;//表示时刻 i 之前物品的最大收益
			noww=min(w-o[i].w,o[i].s);//承重能力，第三条规定
			for (int j=1; j<i; ++j)//枚举 i 上面的物品
				if (o[j].in>=o[i].in)
				{
					while (nowt<o[j].out) ++nowt, g[nowt]=g[nowt-1];
					chkMax(g[nowt],g[o[j].in]+f[j][noww]);//计算出最大收益
				}
			f[i][w]=g[nowt]+o[i].v;//最后把它拿出来，获得价值
		}
	write(f[n][S],'\n');
	IO::flush();
	return 0;
}
