#include <bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define MOD 998244353
#define lc(p) (p<<1)
#define rc(p) (p<<1|1)
#define ad(p) t[p][0]
#define ml(p) t[p][1]
#define mid (lef+rig>>1)
#define MUL(p,k) (k^1 ? ad(p) = 1ll*ad(p)*k%MOD, ml(p) = 1ll*ml(p)*k%MOD : 0)
#define LZ(p) (MUL(lc(p),ml(p)), MUL(rc(p),ml(p)), ml(p) = 1)
#define PS(p) (ad(p) = (ad(lc(p))+ad(rc(p)))%MOD)
#define Auto(v,j) for(vector<int>::iterator j = v.begin(); j != v.end(); j++)
#define rint register int
inline int rf() {
	int r;
	int s=0,c;
	for(; !isdigit(c=getchar()); s=c);
	for(r=c^48; isdigit(c=getchar()); (r*=10)+=c^48);
	return s^45?r:-r;
}
inline int fxp(int s, int n=MOD-2) {
	int a=1;
	for(; n; n&1?a=1ll*a*s%MOD:0,s=1ll*s*s%MOD,n>>=1);
	return a;
}
int n, Le, Ri, K, Ans, t[524288][2], d[MAXN+5], md[MAXN+5], pos[MAXN+5];
vector<int> e[MAXN+5];
inline bool cmp(int x, int y) {
	return md[x]>md[y];
}
void BD(int p, int lef, int rig) {
	ml(p)=1,ad(p)=0,lef^rig?BD(lc(p),lef,mid),BD(rc(p),mid+1,rig),0:0;
}
void AD(int p, int lef, int rig, int x, int v) {
	lef^rig?LZ(p),x<=mid?AD(lc(p),lef,mid,x,v):AD(rc(p),mid+1,rig,x,v),PS(p):ad(p)=(ad(p)+v)%MOD;
}
int QU(int p, int lef, int rig, int L, int R) {
return L^lef||R^rig?LZ(p),((L<=mid?QU(lc(p),lef,mid,L,min(mid,R)):0)+(R>mid?QU(rc(p),mid+1,rig,max(L,mid+1),R):0))%MOD:ad(p);
}
void MU(int p, int lef, int rig, int L, int R, int k) {
	L^lef||R^rig?LZ(p),L<=mid?MU(lc(p),lef,mid,L,min(mid,R),k),0:0,R>mid?MU(rc(p),mid+1,rig,max(L,mid+1),R,k),0:0,PS(p):MUL(p,k);
}
void DFS1(int p, int fa) {
	if(fa) e[p].erase(find(e[p].begin(),e[p].end(),fa));
	md[p] = d[p] = d[fa]+1;
	Auto(e[p],j) DFS1(*j,p), md[p] = max(md[p],md[*j]);
}
void DFS2(int p) {
	sort(e[p].begin(),e[p].end(),cmp);
	pos[p] = ++n;
	Auto(e[p],j) DFS2(*j);
}
void DFS3(int p) {
	static int k[MAXN+5], f[MAXN+5];
	static map<int,int> G;
	int X = md[p]-d[p], Y, v, _;
	AD(1,1,n,pos[p],1);
	Auto(e[p],j) {
		DFS3(v=*j);
		if(j==e[p].begin()) continue;
		Y = md[v]-d[v];
		G.clear();
		G[0] = 1;
		G[X+1] = 0;
		_ = 0;
		for(rint y = 0; y <= Y && y < K; k[y] = QU(1,1,n,pos[p],pos[p]+min(y,K-y-1)), f[y] = QU(1,1,n,pos[v]+y,pos[v]+y), y++);
		for(rint y = 0; y <= Y && y < K; y+1<K-y?(G[y+1]+=f[y])%=MOD,(G[min(K-y,X+1)]+=MOD-f[y])%=MOD:0, y++);
		for(map<int,int>::iterator a = G.begin(), b = ++G.begin(); b != G.end(); a++, b++)
			_ = (_+a->second)%MOD, MU(1,1,n,pos[p]+a->first,pos[p]+b->first-1,_);
		for(rint y = 0; y <= Y && y < K; AD(1,1,n,pos[p]+y+1,1ll*k[y]*f[y]%MOD), y++);
	}
	Ans = (Ans+QU(1,1,n,pos[p],pos[p]+min(K,X)))%MOD;
}
int Work(int _K) {
	BD(1,1,n);
	K = _K;
	Ans = 0;
	DFS3(1);
	return Ans;
}
int main() {
	freopen("tree.in","r",stdin), freopen("tree.out","w",stdout);
	n = rf();
	Le = rf();
	Ri = rf();
	for(rint i = 1, u, v; i < n; u = rf(), v = rf(), e[u].push_back(v), e[v].push_back(u), i++);
	DFS1(1,0);
	n = 0;
	DFS2(1);
	return !printf("%d\n",1ll*fxp(Work(n))*(Work(Ri)-Work(Le-1)+MOD)%MOD);
}
