#include<bits/stdc++.h>
using namespace std;
const int T=20,BufL=200;
const int N1=10,N2=40,N3=100,N4=200,L1=10,L2=100,L3=500;
const int N[T+1]={0,N1,N1,N1,N2,N2,N2,N2,N2,N2,N2,N3,N3,N3,N3,N3,N3,N3,N4,N4,N4};
const int L[T+1]={0,L1,L1,L1,L1,L1,L1,L2,L2,L2,L2,L2,L2,L2,L2,L3,L3,L3,L3,L3,L3};
const int full[T+1]={0,0,0,1,0,0,1,0,0,1,1,0,0,1,1,0,1,1,0,1,1};
const int V=2000,TC=5;
const char* problemname="service";
char buf[BufL]={};
int randomint(int l,int r)
{
	return (rand()*32768+rand())%(r-l+1)+l;
}
void make_data(int t)
{
	cout<<TC<<endl;
	for(int _=1;_<=TC;++_)
	{
		int n=full[t] ? N[t] : randomint(3,N[t]);
		int l=L[t];
		int vl,vr;
		rand()%2 ? (vl=0, vr=rand()%2?n:V) : (vl=randomint(0,V),vr=randomint(vl,V));
		cout<<n<<' '<<l<<endl;
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=n;++j)
				cout<<(i==j?0:randomint(vl,vr))<<' ';
			cout<<endl;
		}
		for(int i=1;i<=l;++i)
			cout<<randomint(1,n)<<' ';
		cout<<endl;
	}
}
int main()
{
	srand(time(0));
	for(int t=1;t<=T;++t)
	{
		cerr<<"start time="<<clock()<<endl;
		
		sprintf(buf,"%s%d.in",problemname,t);
		freopen(buf,"w",stdout);
		make_data(t);
		fclose(stdout);
		//*/
		
		cerr<<"t1="<<clock()<<endl;
		sprintf(buf,"copy %s%d.in %s.in >nul",problemname,t,problemname);
		system(buf);
		cerr<<"running start time="<<clock()<<endl;
		sprintf(buf,"\"%s.exe\"",problemname);
		system(buf);
		cerr<<"running end time="<<clock()<<endl;
		sprintf(buf,"copy %s.out %s%d.ans >nul",problemname,problemname,t);
		system(buf);
		sprintf(buf,"del %s.in",problemname);
		system(buf);
		sprintf(buf,"del %s.out",problemname);
		system(buf);
		cerr<<"data "<<t<<" has been made."<<endl;
		cerr<<"end time="<<clock()<<endl<<endl;
	}
}
