#include<bits/stdc++.h>

const int maxn=1e5+10, inf=0x3f3f3f3f;

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

struct SGT
{
	int Max[maxn<<2],Min[maxn<<2];
	inline void pushup(int x)//上传标记
	{
		Max[x]=max(Max[x<<1],Max[x<<1|1]);
		Min[x]=min(Min[x<<1],Min[x<<1|1]);//颇字面意思
	}

	inline void Change(int x,int l,int r,int k,int v)//权值为当前行列最后一次被消除的时间
	{
		if (l==r)
		{
			Max[x]=Min[x]=v;
			return ;
		}
		int mid=(l+r)>>1;
		if (k<=mid) Change(x<<1,l,mid,k,v);
		else Change(x<<1|1,mid+1,r,k,v);
		pushup(x);
	}

	inline int QueryL(int x,int l,int r,int v)
	{
		if (l==r) return Max[x]>=v ? l : 0;
		int mid=(l+r)>>1;
		if (Max[x<<1|1]>=v) return QueryL(x<<1|1,mid+1,r,v);//因为要找到前方最后一个合法的位置，所以要尽量靠右边些
		else return QueryL(x<<1,l,mid,v);//所以条件为右儿子的权值是否合法
	}

	inline int queryl(int x,int l,int r,int k,int v)//找到在 k 位置前的最后一个大于等于 v 的位置
	{
		if (l==r) return Max[x]>=v ? l : 0;
		int mid=(l+r)>>1;
		if (k<=mid) return queryl(x<<1,l,mid,k,v);//注意判断条件，找前方，即左边
		else
		{
			int t=queryl(x<<1|1,mid+1,r,k,v);
			if (t) return t;
			return QueryL(x<<1,l,mid,v);//在左区间进行线段树树上二分
		}
	}

	inline int QueryR(int x,int l,int r,int v)
	{
		if (l==r) return Max[x]>=v ? l : 0;
		int mid=(l+r)>>1;
		if (Max[x<<1]>=v) return QueryR(x<<1,l,mid,v);//因为要找到后方第一个合法的位置，所以要尽量靠左边些
		else return QueryR(x<<1|1,mid+1,r,v);//所以条件为左儿子的权值是否合法
	}

	inline int queryr(int x,int l,int r,int k,int v)//找到在 k 位置后的第一个大于等于 v 的位置
	{
		if (l==r) return Max[x]>=v ? l : 0;
		int mid=(l+r)>>1;
		if (k>mid) return queryr(x<<1|1,mid+1,r,k,v);//注意判断条件，找后方，即右边
		else
		{
			int t=queryr(x<<1,l,mid,k,v);
			if (t) return t;
			return QueryR(x<<1|1,mid+1,r,v);//在右区间进行线段树树上二分
		}
	}

	inline int querymin(int x,int l,int r,int tl,int tr)//查询 [tl,tr] 区间的最小值
	{
		if (tl<=l && r<=tr) return Min[x];
		int mid=(l+r)>>1;
		int ans=inf;
		if (tl<=mid) chkMin(ans,querymin(x<<1,l,mid,tl,tr));
		if (tr>mid) chkMin(ans,querymin(x<<1|1,mid+1,r,tl,tr));//这个写法就比较常规了，下次要大胆写出来
		return ans;
	}
} R, C;//row，col 各建一颗线段树以便查询区间极值

int row[maxn], col[maxn], n, m, Q;
inline int ask(int a,int b,int c,int d,int v)
{
	if (a==c && b==d) return 0;//同一个点，0 步到达
	if ( (row[a]<v && col[b]<v) || (row[c]<v && col[d]<v) ) return -1;//其中一个点的行列都被 ban
	if ( (row[a]>=v && col[b]>=v) || (row[c]>=v && col[d]>=v) ) return abs(a-c)+abs(b-d);//只要一个点的所在行列均没有被 ban，答案为曼哈顿距离
	//上面的两种情况都不符合，那么现在两个点情况都是：行和列中有一个被 ban
	bool v1=(row[a]>=v), v2=(row[c]>=v);//这里确定两个点的行列中那一个元素被 ban
	if (v1^v2) return abs(a-c)+abs(b-d);//一个点的行是好的，一个点的列是好的，所以存在一条曼哈顿距离路径，画图可知
	//下面就是说两个点情况一样的，要么是行被 ban，要么是列被 ban
	if (v1)//列被 ban
	{
		if (a>c) std::swap(a,c);
		if (R.querymin(1,1,n,a,c)>=v) return abs(a-c)+abs(b-d);//[a,c] 中最早的被消除的时间也合法的话，就一定有解

		if (b>d) std::swap(b,d);
		if (C.Max[1]<v) return -1;////所有列最晚被消除的时间不合法，说明没有一个完整的合法列，旨在查看中转列是否存在

		int t=C.queryr(1,1,m,b,v);//找到在 b 位置后的第一个大于等于 v 的位置
		if (t && t<=d) return abs(a-c)+abs(b-d);//且这个位置在合法区间内
		int ans=inf;
		t=C.queryl(1,1,m,b,v);//向左找中转点
		if (t) chkMin(ans,abs(a-c)+abs(b-t)+abs(d-t));
		t=C.queryr(1,1,m,d,v);//向右找中转点
		if (t) chkMin(ans,abs(a-c)+abs(b-t)+abs(d-t));
		return ans<inf ? ans : -1;
	}
	else//行被 ban
	{
		if (b>d) std::swap(b,d);
		if (C.querymin(1,1,m,b,d)>=v) return abs(a-c)+abs(b-d);//[b,d] 中最早的被消除的时间也合法的话，就一定有解

		if (a>c) std::swap(a,c);
		if (R.Max[1]<v) return -1;//所有行最晚被消除的时间不合法，说明没有一个完整的合法行，旨在查看中转行是否存在

		int t=R.queryr(1,1,n,a,v);//找到在 a 位置后的第一个大于等于 v 的位置
		if (t && t<=c) return abs(a-c)+abs(b-d);//且这个位置在合法区间内
		int ans=inf;
		t=R.queryl(1,1,n,a,v);//向左找中转点
		if (t) chkMin(ans,abs(b-d)+abs(a-t)+abs(c-t));
		t=R.queryr(1,1,n,c,v);//向右找中转点
		if (t) chkMin(ans,abs(b-d)+abs(a-t)+abs(c-t));
		return ans<inf ? ans : -1;
	}
}

int main()
{
	read(n), read(m), read(Q);
	for (int i=1,opt; i<=Q; ++i)
	{
		read(opt);
		if (opt==1)//行的修改
		{
			int x;read(x);
			row[x]=i;
			R.Change(1,1,n,x,i);
		}
		else if (opt==2)//列的修改
		{
			int x;read(x);
			col[x]=i;
			C.Change(1,1,m,x,i);
		}
		else//查询答案
		{
			int a,b,c,d,v;
			read(a), read(b), read(c), read(d), read(v);
			write(ask(a,b,c,d,max(0,i-v)),'\n');//为何这个传递的值为 max(0,(i-v))
		}//缘由：当前 row 的值 = 当前时间 i -它最后一次被消除的时间 row[x]，题目要求：i-row[x]<=v，即 rox[x]>=i-v
	}
	IO::flush();
	return 0;
}
