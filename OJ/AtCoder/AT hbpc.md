[TOC]

# A - 1→1

## title

[LUOGU AT180](https://www.luogu.org/problem/AT180)

简化题意：

>$m$ 表示变化规则的数量，$n$ 表示要生成 $1$ 的数量。
>
>对于生成规则 $a_i,b_i$ 而言，它表示可以将原字符串中的 $a_i$ 个 $1$ 变为 $b_i$ 个 $1$ 。例如，$a_i=2,b_i=3$，表示原字符串中 $11$ 可以变为 $111$。
>
>现在，原字符串中只有 $1$ 个 $1$ ，要求你使用最少的变化次数将字符串变成 $n$ 个 $1$ 。

## analysis

贪心 $+~BFS$。

要求最少步数，当然需要我们花费最小的代价（步数）来取得更高的增幅（1 增加的个数）。

所以开一个 `add[]` 记录更新所需最少的 1 即可。

然后开一个 `ans[]` 记录答案，借助循环队列进行 $BFS$ ，循环队列中的元素表示当前 1 的个数。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxm=300,maxn=2e4;

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
template<typename T>inline void write(T x)
{
    if (!x) *fe++=48;
    if (x<0) *fe++='-', x=-x;
    T num=0, ch[20];
    while (x) ch[++num]=x%10+48, x/=10;
    while (num) *fe++=ch[num--];
    *fe++='\n';
}

int add[maxm<<1],ans[maxn];
int main()
{
	memset(add,0x3f,sizeof(add));
	memset(ans,-1,sizeof(ans));
	int m,n;read(m);read(n);
	for (int i=1,a,b; i<=m; ++i) read(a),read(b),add[b-a+300]=min(add[b-a+300],a);//更新所需最少的1，注意，a不总是小于b，所以需要根据数据范围加上一个偏移量
	ans[1]=1;
	queue<int>q; q.push(1);//从只有一个1开始扩展
	while (!q.empty())
	{
		int x=q.front();
		q.pop();
		for (int i=-300; i<300; ++i)//达到规则所需的1的数量，数组未越界，未扩展过，执行
			if (x>=add[i+300] && 0<=x+i && x+i<maxn && ans[x+i]==-1) ans[x+i]=ans[x]+1,q.push(x+i);
	}
	write(ans[n]);
	flush();
	return 0;
}
```



# B - 01:01

## title

[LUOGU AT181](https://www.luogu.org/problem/AT181)

简化题意：

>输入遵循以下格式。
>
>```
>$ city_A $
>$ hour_0 $ $ hour_1 $ $ $…$ $ hour_{23} $
>$ N $
>$ city_{1,1} $ $ time_{1,1} $ $ city_{1,2} $ $ time_{1,2} $
>$ city_{2,1} $ $ time_{2,1} $ $ city_{2,2} $ $ time_{2,2} $
>
>$ city_{N,1} $ $ time_{n,1} $ $ city_{N,2} $ $ time_{n,2} $
>$ city_B $
>$ time_B $
>```
>$city_A , city_B$ 分别表示都市 A 、都市 B 的名字。
>
>$hour_i$ 表示时间的名称。都市A：00:00～00:59叫做 $hour_0$、01:00～01:59叫做 $hour_1$、…23:00～23:59叫做 $hour_{23}$。时间名称是世界通用的，在某个时刻，若某个城市的时间名称为 $hour_i$，那么所有城市的时间名称都为 $hour_i$。
>
>$city_{i,j}$ 表示城市名称、$time_{i,j}$ 表示时间。当城市 $city_{i,1}$ 为时刻 $time_{i,1}$ 时，城市$city_{i,2}$ 为时刻 $time_{i,2}$ ，给出这样的信息 $N$ 个。
>
>求都市 B 在时刻 $time_B$ 的时候的时间的名称。假设夏天没有时间。

（机翻+修正润色，有点看不下去？抱歉抱歉）

## analysis

利用 $map$ 存下每个城市多对应的那个城市的编号与时间，最后查询 $cityB$ 即可。

## code

```cpp
#include<bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef pair<int,int> pii;
const int maxn=32, T=24*60;

inline int read()
{
	string s; cin>>s;
	int h,m;
	sscanf(s.c_str(),"%d:%d",&h,&m);
	return h*60+m;
}

string cityA,cityB,hours[maxn],city1[maxn],city2[maxn];
int time1[maxn],time2[maxn],timeB,cnt;
map<string,int>M;
vector<pii>g[maxn<<2];
int off[maxn<<2];
inline void add(const string &s)
{
	if (!M.count(s)) M[s]=cnt++;
}

inline int id(const string &s)
{
	return M[s];
}

inline void rec(int x,int t)
{
	if (off[x]^-1) return ;//off[i]==t
	off[x]=t;
	for (int i=0; i<g[x].size(); ++i) rec(g[x][i].first,(t+g[x][i].second)%T);
}

int main()
{
	cin>>cityA;
	for (int i=0; i<=23; ++i) cin>>hours[i];
	int n;cin>>n;
	for (int i=1; i<=n; ++i)
	{
		cin>>city1[i],time1[i]=read();
		cin>>city2[i],time2[i]=read();
	}
	cin>>cityB;
	timeB=read();
	add(cityA),add(cityB);
	for (int i=1; i<=n; ++i) add(city1[i]),add(city2[i]);
	for (int i=1; i<=n; ++i)
	{
		int i1=id(city1[i]), i2=id(city2[i]);
		g[i1].push_back(mp(i2,(time2[i]-time1[i]+T)%T));
		g[i2].push_back(mp(i1,(time1[i]-time2[i]+T)%T));
	}
	memset(off,-1,sizeof(off));
	rec(id(cityA),0);
	int ans=(timeB-off[id(cityB)]+T)%T;
	cout<<hours[ans/60]<<endl;
	return 0;
}
```



# C - 1=0.999...

## title

[LUOGU AT182](https://www.luogu.org/problem/AT182)

简化题意：

>第一行为小数的个数 $n$。从第二行开始的 $n$ 行为实数 $a_i$。$a_i$ 为有限小数或循环小数。
>实数集合 $A$ 为所有 $a_i$ 组成的集合。
>同一个实数可能有不同表示形式。
>有限小数和循环小数遵从以下 BNF 。循环小数中括号括起来的部分表示循环节。例如，$0.(01)$ 就表示 $0.010101…$。
>求实数集 $A$ 中的元素个数（结尾换行）。

## analysis

毒瘤模拟。

先将所有实数统一化（这个具体看代码），然后将所有实数排序（好比较是否相同），接着两两进行比较（无限循环小数的比较方式详见代码），若有不同，答案 $+1$。

## code

```cpp
#include<bits/stdc++.h>
#define A1 (500)
#define A2 (10000)
using namespace std;
const int maxn=321;

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
template<typename T>inline void write(T x)
{
    if (!x) *fe++=48;
    if (x<0) *fe++='-', x=-x;
    T num=0, ch[20];
    while (x) ch[++num]=x%10+48, x/=10;
    while (num) *fe++=ch[num--];
    *fe++='\n';
}

string a[maxn];
inline string normal(const string a)
{
	const size_t dot=a.find('.');
	string p1=a.substr(0,dot), p2=a.substr(dot+1);//将a分成p1（1~dot），p2（dot+1~结尾）
	const size_t p=p2.find('(');
	if (p!=string::npos)
	{
		string b=p2.substr(0,p), c=p2.substr(p+1);//将p2分成b（1~p），c（p+1~结尾）
		c.resize(c.size()-1);
		for (int i=0; b.size()<A2; ++i, i%=c.size()) b+=c[i];
		p2=b;
	}
	return string(A1-p1.size(),'0')+p1+p2+string(A2-p2.size(),'0');
}

inline bool same(const string &a,const string &b)
{
	if (a==b) return true;
	string r=a;
	int c=1;//记录是否进位
	for (int i=r.size()-1; i>=0; --i)//无限循环小数的比较方式
	{
		int v=r[i]-'0'+c;
		c=0;
		if (v>=10) v-=10,c=1;
		r[i]='0'+v;
	}
	return r==b;
}

int main()
{
	int n;read(n);
	for (int i=1; i<=n; ++i) cin>>a[i], a[i]=normal(a[i]);//统一化
	sort(a+1,a+n+1);
	int ans=0;
	for (int i=1; i<=n; ++i)
		if (!same(a[i],a[i+1])) ++ans;
	write(ans), flush();
	return 0;
}
```



# D - 1+1

## title

[LUOGU AT183](https://www.luogu.org/problem/AT183)

简化题意：

>输入遵循以下格式。给出的数目都是整数。
>
>```cpp
>
>$ n $ $ m $ $ r $ r $
>```
>分别表示以下规则中的要素的状态数 $n$ ，最大分割次数 $m$ ，加法规则 $r$。- 表示状态 $(x,y)$，$x,y$ 被称为“要素”。
>
>- 初始状态是 $(1,1)$。
>
>- 各回合可以采取的“行动”是“选择”或“分割”中的一个。
>
>- 先攻后攻交替反复行动 $(0,0)$ 变成的话输。
>
>- 选择：选择自己不是 $0$ 的要素 $x$ 与对方不是 $0$ 的要素 $y$，将 $x$ 加法到选择的对方的要素，即 $x+y$。此时，应用以下任一加法规则 $r$。
>
>- 加法规则 $0$：$x+y$ 在 $n$ 以上时成为 $0$。
>
>- 加法规则 $1$：$x+y$ 在 $n$ 以上时成为 $x+y-n$。
>
>- 分割：一方的要素为 0、且另一个要素 $k$ 在 2 以上的话，就可以进行“分割”。$a+b==k,a\geqslant 1,b\geqslant 1$的自然数 $a , b$ 选择 $(a,b)$。
>
>- 分割最大 $m$ 可旋转。
>
>如果存在持续无限行动的程序，请输出 `Infinite`。这时，先手和后手可以协助他们继续无限的行动。
>
>如果不存在的话，先手和后手选择以下的基准行动时，游戏的结果和游戏几回合结束。然后，先胜的情况 `First`，后胜的情况 `Second`，在第 1 行输出。第 2 行输出游戏结束是第几回合。
>
>当自己存在能取胜的手时，要选择那只手。自己胜利的手存在负数的时候从其中选择游戏以最短结束一样的手。
>
>当自己只存在输掉的手时，选择用游戏最长结束的手。

（机翻+修正润色，仍有不当之处，烦请见谅）

## analysis

机翻后总算读懂了题意，原来是这么回事。

所以我们可以直接从初始状态 $dfs$ ，检测是否有无限行动，即无解的情况。

如果有解，那么运用 $Dp$ 的思想（其实和 $dfs$ 差不多，只不过 $dfs$ 只是检测一下，而 $Dp$ 要算出答案），统计出答案。

详见代码，这是个很值得对着代码细细研究一番的题目。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Max_a1=17,Max_a2=17,Max_am=3,Max_b1=17,Max_b2=17,Max_bm=3;
const ll inf=1ll<<60;

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
template<typename T>inline void write(T x)
{
	if (!x) *fe++=48;
	if (x<0) *fe++='-', x=-x;
	T num=0, ch[20];
	while (x) ch[++num]=x%10+48, x/=10;
	while (num) *fe++=ch[num--];
	*fe++='\n';
}

int n,m,rule;
inline ll add(ll x,ll y)
{
	if (x+y>=n) return !rule ? 0 : x+y-n;
	return x+y;
}

ll f[Max_a1][Max_a2][Max_am][Max_b1][Max_b2][Max_bm];
inline ll fun(int a1,int a2,int am,int b1,int b2,int bm)
{
	ll &res=f[a1][a2][am][b1][b2][bm];
	if (res^-1) return res;
	if (!a1 && !a2) return res=-inf;
	ll ans=-inf-1;
	if ( (!a1 || !a2) && am>0)
		for (int k=1; k<a1+a2; ++k) ans=max(ans,-fun(b1,b2,bm,k,a1+a2-k,am-1));
	if (a1 && b1) ans=max(ans,-fun(add(b1,a1),b2,bm,a1,a2,am));
	if (a1 && b2) ans=max(ans,-fun(b1,add(b2,a1),bm,a1,a2,am));
	if (a2 && b1) ans=max(ans,-fun(add(b1,a2),b2,bm,a1,a2,am));
	if (a2 && b2) ans=max(ans,-fun(b1,add(b2,a2),bm,a1,a2,am));
	if (ans<0) ++ans;
	if (ans>0) --ans;
	return res=ans;
}

int vis[Max_a1][Max_a2][Max_am][Max_b1][Max_b2][Max_bm];
inline bool dfs(int a1,int a2,int am,int b1,int b2,int bm)
{
	int &res=vis[a1][a2][am][b1][b2][bm];
	if (res==1) return false;
	if (res==2) return true;
	res=1;
	if (!a1 && !a2)
	{
		res=2;
		return true;
	}
	if ( (!a1 || !a2) && am>0)
		for (int k=1; k<a1+a2; ++k)
			if (!dfs(b1,b2,bm,k,a1+a2-k,am-1)) return false;
	if (a1 && b1) if (!dfs(add(b1,a1),b2,bm,a1,a2,am)) return false;
	if (a1 && b2) if (!dfs(b1,add(b2,a1),bm,a1,a2,am)) return false;
	if (a2 && b1) if (!dfs(add(b1,a2),b2,bm,a1,a2,am)) return false;
	if (a2 && b2) if (!dfs(b1,add(b2,a2),bm,a1,a2,am)) return false;
	res=2;
	return true;
}

int main()
{
	memset(f,-1,sizeof(f));
	read(n);read(m);read(rule);
	if (!dfs(1,1,m,1,1,m)) return puts("Infinite"),0;
	ll res=fun(1,1,m,1,1,m);
	if (res>0) puts("First"),write(inf-res),flush();
	if (res<0) puts("Second"),write(res+inf),flush();
	return 0;
}
```
附上一位大佬的附带调试 $code$。没有别的意思，只是从这位大佬的代码中，学习到了很多调试的东西，有感而发，所以记录下来，谢谢。

```cpp
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <cfloat>
#include <map>
#include <utility>
#include <set>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>
#include <complex>
#include <stack>
#include <queue>
#include <cstring>
#include <assert.h>
#include <sys/time.h>
#include <fstream>

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)
#define EXIST(s,e) ((s).find(e)!=(s).end())

#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
#define deb(x) cerr << #x << " = " << (x) << " , ";
#define debl cerr << " (L" << __LINE__ << ")"<< endl;


#define clr(a) memset((a),0,sizeof(a))
#define nclr(a) memset((a),-1,sizeof(a))
#define pb push_back
#define INRANGE(x,s,e) ((s)<=(x) && (x)<(e))
#define MP(x,y) make_pair((x),(y))

double pi=3.14159265358979323846;

using namespace std;
static const double EPS = 1e-5;
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<string> vs;

template<typename T> std::ostream& operator<<(std::ostream& os, const vector<T>& z){
	os << "[ ";
	REP(i,z.size())os << z[i] << ", " ;
	return ( os << "]" << endl);
}

template<typename T> std::ostream& operator<<(std::ostream& os, const set<T>& z){
	os << "set( ";
	EACH(p,z)os << (*p) << ", " ;
	return ( os << ")" << endl);
}

template<typename T,typename U> std::ostream& operator<<(std::ostream& os, const map<T,U>& z){
	os << "{ ";
	EACH(p,z)os << (p->first) << ": " << (p->second) << ", " ;
	return ( os << "}" << endl);
}

template<typename T,typename U> std::ostream& operator<<(std::ostream& os, const pair<T,U>& z){
	return ( os << "(" << z.first << ", " << z.second << ",)" );
}

double get_time(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + tv.tv_usec*1e-6;
}

ll inf=1LL<<60;

int n,rule;

ll add(ll x, ll y){
	if(x+y>=n){
		if(rule==0)return 0;
		else return x+y-n;
	}
	return x+y;
}

const int Max_a1 = 17;
const int Max_a2 = 17;
const int Max_am = 3;
const int Max_b1 = 17;
const int Max_b2 = 17;
const int Max_bm = 3;
ll memo_f[Max_a1][Max_a2][Max_am][Max_b1][Max_b2][Max_bm];
ll f(int a1, int a2, int am, int b1, int b2, int bm){
	assert(0<=a1 && a1<Max_a1);
	assert(0<=a2 && a2<Max_a2);
	assert(0<=am && am<Max_am);
	assert(0<=b1 && b1<Max_b1);
	assert(0<=b2 && b2<Max_b2);
	assert(0<=bm && bm<Max_bm);
	ll &ret=memo_f[a1][a2][am][b1][b2][bm];
	if(ret!=-1)return ret;
	if(a1==0 && a2==0)return ret=-inf;
	ll ans=-inf-1;
	if( (a1==0 || a2==0) && am>0){
		for(int k1=1; k1<a1+a2; k1++){
			ans=Max(ans, -f(b1,b2,bm, k1, a1+a2-k1, am-1));
		}
	}
	if(a1 && b1)ans=Max(ans, -f(add(b1,a1), b2,bm, a1, a2, am));
	if(a1 && b2)ans=Max(ans, -f(b1,add(b2,a1),bm, a1, a2, am));
	if(a2 && b1)ans=Max(ans, -f(add(b1,a2),b2,bm, a1, a2, am));
	if(a2 && b2)ans=Max(ans, -f(b1,add(b2,a2),bm, a1, a2, am));
	if(ans>0)ans--;
	if(ans<0)ans++;
	return ret=ans;
}

int visit[Max_a1][Max_a2][Max_am][Max_b1][Max_b2][Max_bm];
bool dfs(int a1, int a2, int am, int b1, int b2, int bm){
	//deb(a1);deb(a2);deb(am);deb(b1);deb(b2);deb(bm);debl;
	assert(0<=a1 && a1<Max_a1);
	assert(0<=a2 && a2<Max_a2);
	assert(0<=am && am<Max_am);
	assert(0<=b1 && b1<Max_b1);
	assert(0<=b2 && b2<Max_b2);
	assert(0<=bm && bm<Max_bm);//assert宏的原型定义在<assert.h>中，其作用是如果它的条件返回错误，则终止程序执行
	int &ret=visit[a1][a2][am][b1][b2][bm];
	if(ret==1)return false;
	if(ret==2)return true;
	ret=1;
	if(a1==0 && a2==0){
		ret=2;
		return true;
	}
	if( (a1==0 || a2==0) && am>0){
		for(int k1=1; k1<a1+a2; k1++){
			if(! dfs(b1,b2,bm, k1, a1+a2-k1, am-1))return false;
		}
	}
	if(a1 && b1)if(! dfs(add(b1,a1), b2,bm, a1, a2, am))return false;
	if(a1 && b2)if(! dfs(b1,add(b2,a1),bm, a1, a2, am)) return false;
	if(a2 && b1)if(! dfs(add(b1,a2),b2,bm, a1, a2, am)) return false;
	if(a2 && b2)if(! dfs(b1,add(b2,a2),bm, a1, a2, am)) return false;
	ret=2;
	return true;
}

void _main(istream &inp){
	clr(visit);
	nclr(memo_f);
	int m;
	inp >> n >> m >> rule;
	if(!dfs(1,1,m, 1,1, m)){
		cout << "Infinite" << endl;
		return;
	}
	ll res=f(1,1,m, 1,1,m);
	if(res>0){
		cout << "First" << endl;
		cout << inf-res << endl;
	}
	if(res<0){
		cout << "Second" << endl;
		cout << res+inf << endl;
	}

}

int main(){
	if(0){
		ifstream ifs("test.txt");
		_main(ifs);
	}
	else{
		_main(cin);
	}
	return 0;
}
```