题意：随机生成一个 m + 1 个数的数列，第一个数为 0, 生成第 i个数时，在前 i − 1 个数中等概率选择一个数 k, 则第 i 个数为k + 1。每个数均有一个对应的权值，求数列权值和的期望。

回想一下正睿老师讲期望与概率的套路。。。

$S$：数列的权值和

$X_i$：第i个数的权值（$X_1$为定值0，所以忽略不计）
$$
S=\sum_{i=2}^{m+1}X_i
根据期望的线性性有
$$

根据期望的线性性有
$$
E(S)=\sum_{i=2}^{m+1}E(X_i)
$$
只要求出$E(X_i)$就可以了

$P_i(j)$：序列的第i个数为j的概率
$$
E(X_i)=\sum_{j=1}^{i-1}P_i(j)\ast a_j
$$
现在只要求出$P_i(j)$就可以了

现在只要求出$P_i(j)$就可以了

$j$的出现要求在前$i-1$个数中随机到$j-1$
$$
P_i(j)=\sum_{k=1}^{i-1}\frac {1}{i-1}P_k(j-1)
综上所述
$$

综上所述
$$
E(S)=\sum_{i=2}^{m+1}\sum_{j=1}^{i-1}a_j \sum_{k=1}^{i-1}P_k(j-1)
$$
代码（这份和题解相符）

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
long long a[100010],y[30],Mod=998244353;
long long X[30];//第i次玩的期望战斗次数 
long long p[30][30];//第i次玩的是章节j的概率 
long long ksm(long long aa,long long bb)
{
	long long an=1;
	for (;bb;bb>>=1)
	{
		if (bb&1) an=an*aa%Mod;
		aa=aa*aa%Mod;
    }
    return an;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	  scanf("%lld",&a[i]); 
	for (int i=1;i<=m+1;i++)
	  y[i]=ksm(i,Mod-2);//预处理逆元 
	X[1]=0;p[1][0]=1;//序章 
	for (int i=2;i<=m+1;i++)//第i次 
	  for (int j=1;j<i;j++)//枚举玩的章节 
	  {
	    for (int k=1;k<i;k++)//枚举随机到的存档 
		    p[i][j]=(p[i][j]+p[k][j-1]*y[i-1]%Mod)%Mod;
		X[i]=(X[i]+p[i][j]*a[j]%Mod)%Mod; 
      }
    long long S=0;
    for (int i=2;i<=m+1;i++)
      S=(S+X[i])%Mod;
    cout<<S;
    return 0; 
}
```