#include<bits/stdc++.h>

typedef long long ll;
const int maxn=1e5+10;
const ll INF=0x3f3f3f3f3f3f3f3fll;

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

struct Orz{int w,s,p;}o[maxn];
inline bool cmp(Orz a,Orz b)//和题解正好相反，无所谓了
{
	return a.w>b.w || (a.w==b.w && a.p<b.p);
}

ll f[2][250][250];//f[i][a][b]表示考虑了排序后的前 i 个人，目前已经有 a 个组配好了，还有 b 个组只有组长的最小代价
int main()
{
	int n,kk;read(n);read(kk);
	for (int i=1; i<=n; ++i) read(o[i].w),read(o[i].s),read(o[i].p);
	if (kk<<1>n) return puts("-1"),0;//需要招聘的人超过了来应聘的人，无解

	for (int i=1; i<=n; ++i)
	{
		if (o[i].p==2) o[i].p=3;
		else if (o[i].p==3) o[i].p=2;
	}
	std::sort(o+1,o+n+1,cmp);//按照经验值从大到小，先组长后组员的顺序排序
	memset(f,0x3f,sizeof(f));//初值
	f[0][0][0]=0;
	int x=1;//滚动数组
	for (int i=1; i<=n; ++i)
	{
		int lim1=min(i>>1,kk);//已经配好组的边界（赋初值）
		for (int j=0; j<=lim1; ++j)
		{
			int lim2=min(i-(j<<1),kk-j);//将要配好的组的边界（赋初值）
			for (int k=0; k<=lim2; ++k) f[x][j][k]=INF;
		}
		lim1=min((i-1)>>1,kk);//已经配好组的边界（转移）
		for (int j=0; j<=lim1; ++j)
		{
			int lim2=min(i-1-(j<<1),kk-j);//将要配好的组的边界（转移）
			for (int k=0; k<=lim2; ++k)
			{
				if (o[i].p==1 && j+k+1<=kk) chkMin(f[x][j][k+1],f[x^1][j][k]+o[i].s);//组长嘛，只能多开一组了
				else if (o[i].p==2)
				{
					if (j+k+1<=kk) chkMin(f[x][j][k+1],f[x^1][j][k]+o[i].s);//组员，这就考虑是多开一组给他
					if (k>0) chkMin(f[x][j+1][k-1],f[x^1][j][k]+o[i].s);//还是去填补以前没有配好的组
				}
				else if (o[i].p==3 && k>0) chkMin(f[x][j+1][k-1],f[x^1][j][k]+o[i].s);//通配符，就填补以前没有配好的组
				chkMin(f[x][j][k],f[x^1][j][k]);//也可能你试着配了一次，还没有原先的方案的代价小
			}
		}
		x^=1;
	}
	if (f[x^1][kk][0]==INF) f[x^1][kk][0]=-1;//无解
	write(f[x^1][kk][0],'\n');
	IO::flush();
	return 0;
}
