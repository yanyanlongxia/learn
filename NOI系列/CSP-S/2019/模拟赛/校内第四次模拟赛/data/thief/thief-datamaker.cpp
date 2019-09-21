#include<bits/stdc++.h>
using namespace std;
const int T=10,L=200;
const char* problemname="thief";
const int N1=20,N2=999,V1=20,V2=10000;
const int N[T+1]={0,N1,N1,N1,N1,N1,N2,N2,N2,N2,N2};
const int V[T+1]={0,V1,V1,V1,V1,V1,V2,V2,V2,V2,V2};
char buf[L]={};
int randomint(int l,int r)
{
	return (rand()*32768+rand())%(r-l+1)+l;
}
int main()
{
	srand(time(0));
	for(int t=1;t<=T;++t)
	{
		cerr<<"start time="<<clock()<<endl;
		
		sprintf(buf,"%s%d.in",problemname,t);
		freopen(buf,"w",stdout);
		
		int n=randomint(2,N[t]);
		if(n%2==0)
			n=randomint(2,N[t]);
		cout<<n<<endl;
		for(int j=1;j<=n;++j)
			cout<<randomint(1,V[t])<<' ';
		cout<<endl;
		fclose(stdout);
		
		cerr<<"t1="<<clock()<<endl;
		sprintf(buf,"copy %s%d.in %s.in >nul",problemname,t,problemname);
		system(buf);
		sprintf(buf,"\"%s.exe\"",problemname);
		system(buf);
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
