#include<bits/stdc++.h>

#define mp std::make_pair
typedef std::pair<int,int> pii;
const int maxn=1e6+10;

namespace IO
{
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

using IO::write;

char str[maxn];
std::map<pii,int> M;
int main()
{
	scanf("%s",str+1);
	int n=strlen(str+1), B_A=0, C_A=0, ans=0;
	M[mp(0,0)]=1;
	for (int i=1; i<=n; ++i)
	{
		if (str[i]=='A') --B_A, --C_A;
		if (str[i]=='B') ++B_A;
		if (str[i]=='C') ++C_A;
		ans+=M[mp(B_A,C_A)];
		++M[mp(B_A,C_A)];
	}
	write(ans,'\n');
	IO::flush();
	return 0;
}
