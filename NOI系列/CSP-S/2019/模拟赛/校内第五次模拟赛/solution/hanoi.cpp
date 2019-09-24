#include <bits/stdc++.h>
using namespace std;
#define MAXN 1500
#define ll unsigned long long
#define INFLL 0x3f3f3f3f3f3f3f3fllu
#define rint register int
inline int rf() {
	int r;
	int s=0,c;
	for(; !isdigit(c=getchar()); s=c);
	for(r=c^48; isdigit(c=getchar()); (r*=10)+=c^48);
	return s^45?r:-r;
}
int n, m, T;
ll f[MAXN+5][MAXN+5];
vector<int> A[MAXN+5];
inline void Mul2(vector<int> &A) {
	A.push_back(0);
	A[0] *= 2;
	for(int i = 1; i < (int)A.size(); A[i] = (A[i]<<1)+A[i-1]/10, A[i-1] %= 10, i++);
	if(!A.back()) A.pop_back();
}
int main() {
	freopen("hanoi.in","r",stdin);
	freopen("hanoi.out","w",stdout);
	n = MAXN;
	m = MAXN;
	A[1].assign(1,2);
	for(rint i = 2; i <= n; A[i] = A[i-1], --A[i-1][0], Mul2(A[i++]));
	--A[n][0];
	memset(f,0x3f,sizeof f);
	memset(f[1]+1,0,n<<3);
	f[2][1] = 1;
	{
		ll s = 2;
		for(rint i = 1; i <= n; f[3][i] = min(f[3][i],s-1), s = min(s<<1,INFLL+1), i++);
	}
	for(rint i = 4, j, k; i <= m; i++)
		for(f[i][1] = 1, j = 2, k = 1; j <= n; f[i][j] = f[i-1][j-k]+(f[i][k]<<1), j++)
			for(; k<j-1 && f[i-1][j-k]+(f[i][k]<<1) > f[i-1][j-k-1]+(f[i][k+1]<<1); ++k);
	for(T = rf(); T--; ) {
		n = rf();
		m = rf();
		if(m==1) {
			puts("0");
			continue;
		}
		if(m==2) {
			puts(n>1?"No Solution":"1");
			continue;
		}
		if(m==3) {
			for(rint i = A[n].size()-1; ~i; putchar(A[n][i]+'0'), i--);
			putchar('\n');
			continue;
		}
		printf("%llu\n",f[m][n]);
	}
	return 0;
}
