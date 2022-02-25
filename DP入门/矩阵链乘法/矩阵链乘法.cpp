#include<iostream>
/*
�˴���Դ��:https://blog.csdn.net/c18219227162/article/details/50412333
����n�����������,ϣ���������ǵĳ˻�,��������Ҫ���ٴγ˷�����?
(��Ϊpxq�ľ�����qxr�ľ�����˴�����p*q*r
��ȫ���Ż�������ָҪ����˭�Ⱥ�˭��.
�˷�����Ϊʲô��p*q*r,��Ϊpxq��qxr�ľ�����˵õ��ľ�����pxr�ľ���,
Ҳ������pxr��Ԫ��,����ÿ��Ԫ�ض�����q����������ۼӵĵ���,��������Ԫ�صĴ�����pxrxq=pxqxr
*/
using namespace std;
const int INF=2147483647;
int const M=7;
void MATRIX_CHAIN_ORDER(int *p,int Length,int m[][M],int s[][M])
{
	int q,n=Length-1;
	for(int i=1;i<=n;i++) m[i][i]=0;
	for(int l=2;l<=n;l++) 	/* �������ĳ��� */
	{
		for(int i=1;i<=n-l+1;i++)
		{
			int j=i+l-1;         /* �ȼ��� l=j-i+1 */
			m[i][j]=INF;//m[i][j]�����i~j���������˵����ٳ˷�����
			for(int k=i;k<=j-1;k++)
			{
			    /*
			    p[i-1]�ǵ�i���������,p[k]�ǵ�k���������,
			    p[k]ͬʱҲ�ǵ�k+1���������,p[j]�ǵ�j���������.
			    m[i][j]����i~j�������������õ�����Ϊp[i-1]��Ϊp[j]�ľ���,
			    ����ö��m[i][j]���������������еľ�����˵õ�,�ָ��K
			    p[i-1] x p[k]  p[k]x p[j] ������������������˵õ�,����Ϊp[i-1]*p[k]*p[j].
			    */
				q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];//��ȡ��i~j���������˵����ٳ˷�����
				if(q<m[i][j])
				{
					m[i][j]=q;
					s[i][j]=k;//��¼���ٳ˷������ľ������ָ��,����������������˵�˳��
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
   p[i]�����i+1���������,ͬʱҲ�����i���������,��Ȼ���鳤��M=7,
   ʵ��ֻ��6�������ľ���,�����ͱ�֤�������������ڵľ�����������˷�.
   */
   int p[M]={30,35,15,5,10,20,25};
   int m[M][M],s[M][M];
   MATRIX_CHAIN_ORDER(p,M,m,s);
   cout<<"��n=6ʱ���Ž�Ϊ: \n"<<m[1][6];
   cout<<"\n���Ż�����Ϊ��\n";
   PRINT_OPTIMAL_PARENS(s,1,6);
   return 0;
}
