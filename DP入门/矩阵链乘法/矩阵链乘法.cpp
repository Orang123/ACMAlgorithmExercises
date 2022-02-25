#include<iostream>
/*
此代码源自:https://blog.csdn.net/c18219227162/article/details/50412333
给出n个矩阵的序列,希望计算他们的乘积,问最少需要多少次乘法运算?
(认为pxq的矩阵与qxr的矩阵相乘代价是p*q*r
完全括号化方案是指要给出谁先和谁乘.
乘法代价为什么是p*q*r,因为pxq和qxr的矩阵相乘得到的矩阵是pxr的矩阵,
也就是有pxr个元素,对于每个元素都是由q对数相乘再累加的到的,所以所有元素的代价是pxrxq=pxqxr
*/
using namespace std;
const int INF=2147483647;
int const M=7;
void MATRIX_CHAIN_ORDER(int *p,int Length,int m[][M],int s[][M])
{
	int q,n=Length-1;
	for(int i=1;i<=n;i++) m[i][i]=0;
	for(int l=2;l<=n;l++) 	/* 矩阵链的长度 */
	{
		for(int i=1;i<=n-l+1;i++)
		{
			int j=i+l-1;         /* 等价于 l=j-i+1 */
			m[i][j]=INF;//m[i][j]代表第i~j个矩阵连乘的最少乘法次数
			for(int k=i;k<=j-1;k++)
			{
			    /*
			    p[i-1]是第i个矩阵的行,p[k]是第k个矩阵的列,
			    p[k]同时也是第k+1个矩阵的行,p[j]是第j个矩阵的列.
			    m[i][j]代表i~j个矩阵连乘所得到的行为p[i-1]列为p[j]的矩阵,
			    尝试枚举m[i][j]可能由哪两种行列的矩阵相乘得到,分割点K
			    p[i-1] x p[k]  p[k]x p[j] 由这样的两个矩阵相乘得到,代价为p[i-1]*p[k]*p[j].
			    */
				q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];//求取第i~j个矩阵连乘的最少乘法次数
				if(q<m[i][j])
				{
					m[i][j]=q;
					s[i][j]=k;//记录最少乘法次数的矩阵链分割点,方便输出具体矩阵相乘的顺序
				}
			}
		}
	}
}
void PRINT_OPTIMAL_PARENS(int s[][M],int i,int j)
{
	if(i == j) cout<<"A"<<i;
	else
	{
		cout<<"(";
		PRINT_OPTIMAL_PARENS(s,i,s[i][j]);
		PRINT_OPTIMAL_PARENS(s,s[i][j]+1,j);
		cout<<")";
	}
}
int main()
{
   /*
   p[i]代表第i+1个矩阵的行,同时也代表第i个矩阵的列,虽然数组长度M=7,
   实际只有6个连续的矩阵,这样就保证了任意两个相邻的矩阵都能做矩阵乘法.
   */
   int p[M]={30,35,15,5,10,20,25};
   int m[M][M],s[M][M];
   MATRIX_CHAIN_ORDER(p,M,m,s);
   cout<<"当n=6时最优解为: \n"<<m[1][6];
   cout<<"\n括号化方案为：\n";
   PRINT_OPTIMAL_PARENS(s,1,6);
   return 0;
}
