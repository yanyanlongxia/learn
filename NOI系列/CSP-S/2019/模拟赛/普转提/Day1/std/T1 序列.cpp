#include<bits/stdc++.h>

const int maxn=1e3+10;

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

int a[maxn],b[maxn],m[maxn],tot,ans=0x3f3f3f3f;
int main()
{
	int n;read(n);
	for (int i=1; i<=n; ++i) read(a[i]), b[i]=a[i];

	std::sort(b+1,b+n+1);
	int k=std::unique(b+1,b+n+1)-b-1;//可以先通过离散去重找到目标序列
	for (int i=1; i<=n; ++i)
	{
		a[i]=std::lower_bound(b+1,b+k+1,a[i])-b;
		if (++m[a[i]]==2) ++tot;//标记出现次数大于 1 的元素的数量
	}

	if (!tot) return puts("0"),0;//没有的话就不需要了
	for (int i=1; i<=n; ++i)
	{
		memcpy(b,m,sizeof(b));//原序列元素出现次数不能被改变
		int x=tot;//原出现两次的元素个数不能被改变
		for (int j=i; j<=n; ++j)//查看区间 [i,j] 中是否存在合法情况
			if (--b[a[j]]==1)//即这个元素正好出现两次
				if (!--x) { chkMin(ans,j-i+1); break; }//并且是最后一个，那么这个区间对答案有贡献
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
