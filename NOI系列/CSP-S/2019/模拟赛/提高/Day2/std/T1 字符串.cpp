#include<bits/stdc++.h>

const int maxn=3e5+10;

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

int p[maxn];
char s[maxn],t[maxn];
int main()
{
	int n,m;read(n);read(m);
	scanf("%s",s+1), scanf("%s",t+1);
	for (int i=1, j=1; i<=m; ++i)
	{
		while (j<=n && s[j]!=t[i]) ++j;//选择第一个和 Ti 一样的与 Ti 进行匹配
		if (j==n+1) return puts("-1"),0;//到了末尾都没有，无解
		p[i]=j++;//Ti 的匹配位置为 Sj
	}
	for (int i=m, j=n; j>1; --j)
	{
		if (s[j]==s[j-1]) continue;//从后往前的顺序依次考虑 S 中所有满足相邻两个字母不同的位置
		while (i>0 && p[i]>j) --i;//pj~i 的一段前缀可以移动
		if (!i) return puts("-1"),0;//同上
		p[i]=j;//调整为 i 或 i+1 之一，从而使得 i 满足条件
		if (t[i]==s[j-1]) p[i]=--j;
	}
	for (int i=1; i<=m; ++i) write(p[i],' ');
	IO::flush();
	return 0;
}
