#include<bits/stdc++.h>
using namespace std;
const int T=10,L=200,TC1=50,TC2=5000,N1=10,N2=50,N3=50000,V1=50,V2=1000000000;
const char* problemname="noname";
//const bool skip[T+1]={0,0,0,0,0,0,0,0,0,0,0};
const int type[T+1]={0,0,0,0,0,0,0,0,0,0,0};
//const int Test[T+1]={0,9,20,20,20,40,50,50,50,99,99,99,99,99,99,99,99,99,99,99,99};
//const int add[T+1]={0,0,0,1,1,1,1,1,1,1,1};
const int N[T+1]={0,N1,N1,N1,N2,N2,N2,N2,N2,N3,N3};
const int V[T+1]={0,V1,V1,V1,V1,V1,V1,V1,V1,V2,V2};
const int TC[T+1]={0,TC1,TC1,TC1,TC1,TC1,TC1,TC1,TC1,TC2,TC2};
char buf[L]={};
int randomint(int l,int r)
{
	return (rand()*32768+rand())%(r-l+1)+l;
}/*
void get_data(int &x,int num)
{
	sprintf(buf,"add%d.txt",num);
	freopen(buf,"r",stdin);
	int T;
	cin>>T;
	for(int i=1;i<=T;++i)
	{
		int n,tmp;
		--x;
		cin>>n;
		cout<<n<<endl;
		for(int j=1;j<=n;++j)
		{
			cin>>tmp;
			cout<<tmp<<' ';
		}
		cout<<endl;
	}
}*/
void print(int N,int V,bool full)
{
	int n=full ? N : randomint(1,N);
	int v=rand()%3 ? N : randomint(1,V);
	int offset=randomint(0,V-v);
	cout<<n<<endl;
	for(int i=1;i<=n;++i)
		cout<<randomint(1,v)+offset<<' ';
	cout<<endl;
}
void make_data(int t)
{
	int T=TC[t];
	cout<<T<<endl;
	//if(add[t])
	//	get_data(T,add[t]);
	print(N[t],V[t],true);
	print(N[t],V[t],false);
	for(int i=1;i<=T-5;++i)
		print(min(N[t],N2),V[t],false);
	print(N[t],V[t],false);
	print(N[t],V[t],true);
	print(N[t],V[t],false);
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
