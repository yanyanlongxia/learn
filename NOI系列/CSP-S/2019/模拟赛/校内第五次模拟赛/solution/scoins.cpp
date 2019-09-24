#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rint register int
inline ll rf() {
	ll r;
	int s=0,c;
	for(; !isdigit(c=getchar()); s=c);
	for(r=c^48; isdigit(c=getchar()); (r*=10)+=c^48);
	return s^45?r:-r;
}
int main() {
	freopen("scoins.in","r",stdin), freopen("scoins.out","w",stdout);
	ll n = rf(), c = sqrtl(n+1.9);
	return !printf("%lld\n",(c-(c*c>n+1))-1);
}
