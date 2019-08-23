# title

[LUOGU AT2166 Rotate 3x3](https://www.luogu.org/problem/AT2166)

简化题意

>我们有一个 $3$ 行 $N$ 列的初始矩阵，$(i,j)$ 位置的数为 $i+3j-3$。
>我们有一个这样的操作：选择一个 $3\times 3$ 的子矩阵，将这个子矩阵旋转 $180°$。（具体见下面的图）。
>现在给出一个 $3$ 行 $N$ 列的矩阵（矩阵中的数各不相同），问能否通过若干次上述操作将初始矩阵变为给定的矩阵。

# analysis

很锻炼思维的一道题目啊。

思维不难（啊？）

我们首先要把存在一列不合法情况的现有矩阵直接判掉。

然后下面是好玩的地方：我们用<font color=black> $to[i]$ 表示第 $i$ 列原本在矩阵中的位置</font>。

然后我们发现，如果 $to[i]$ 和 $i$ 不是同为奇数或偶数，那就不合法，直接判掉。

下面，来介绍一个奇妙的东西：我们可以将隔着一列的两列同时颠倒！方法如下： 

我们把每一列当做一个字母，设小写字母颠倒之后是大写字母， 于是我们设 $abcde$ 为原矩阵的一部分 ，然后就到了我们构造的时候啦！ 
$$
\underline{abc}de\to CB\underline{Ade}\to \underline{CBE}Da\to eb\underline{cDa}\to \underline{ebA}dC\to aB\underline{EdC}\to aBcDe
$$
这样我们就构造出了一种方案使得这部分的第二列和第四列颠倒了。 

那第一列和第三列呢？ 

基于上面的方案，我们有： 
$$
a\underline{BcD}e\to\underline{adC}be\to\underline{DAb}e\to\underline{cBa}de\to AbCde
$$
大功告成！ 

第三列和第五列同理啦 ！

所以如果这个矩阵的每一列都已经排好了，那剩下的就直接看看如果<font color=blue>奇数列或偶数列</font>共有<font color=red>奇数个</font>列是颠倒的话，那就是输出 $No$ 就好了。（因为只需要判奇偶，所以下面写的都是 $^1$ 。 ）

我们会发现如果我们要交换两个奇数列，我们只需要将偶数列的颠倒数 $^1$ 就好了，偶数列反之。 

于是我们枚举$1\sim n$，然后将 $i$ 和 $to[i]$ 交换，直到 $i==to[i]$ 为止。 

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;

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

int t[2],to[maxn],a[4][maxn];
int main()
{
	int n;read(n);
	for (int i=1; i<=3; ++i)
		for (int j=1; j<=n; ++j) read(a[i][j]);
	for (int i=1; i<=n; ++i)
	{
		to[i]=a[2][i]/3+1;
		if (!((a[1][i]-a[2][i]==-1 && a[2][i]-a[3][i]==-1 && a[1][i]%3==1) || (a[1][i]-a[2][i]==1 && a[2][i]-a[3][i]==1 && !(a[1][i]%3))) || (abs(i-to[i])&1))
		{
            puts("No"); exit(0);
		}
        t[i&1]^=(a[1][i]>a[2][i]);
	}
	for (int i=1; i<=n; ++i)
		while (to[i]^i)
		{
			t[i&1^1]^=1;
			swap(to[i],to[to[i]]);
		}
	puts(t[0] || t[1] ? "No" : "Yes");
	return 0;
}
```