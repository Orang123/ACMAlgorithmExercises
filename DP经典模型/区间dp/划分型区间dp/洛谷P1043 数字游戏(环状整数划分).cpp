#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
/*
����:��n������λ��״�������Ϊk�����֣�k�����ֶ�10ȡģ,Ȼ���۳�������
����������С��ֵ.
����:https://www.luogu.com.cn/problem/P1043
˼·:��ʵ���ǻ�״��������������,��Ҫ��չ���鵽2n.
dp1[i][j][k],dp2[i][j][k]�ֱ����[i,j]�����ڵ�������Ϊk�����ֵĳ˻�����Сֵ�����ֵ.
*/
int dp1[110][110][10],dp2[110][110][10],n,m,a[110],sum[110];
//x%10 ���ڸ����������-10,�ټ�10��Ϊ����֮����ȡ��
//�����������-1%10=9,Ӧ����ʹ�ø���ȡģΪ����,������ȡģ���10λ��������ȡģ(��ȡģ��Ӧ�������Ķ�10ȡģ)
int mod(int x){
    return (x%10+10)%10;
}

int main(){
    int ans1=0x3f3f3f3f,ans2=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i+n]=a[i];
    }
    for(int i=1;i<=2*n-1;i++)//����ǰ׺�ͷ���dp[i][j][1]�����
        sum[i]=sum[i-1]+a[i];
    memset(dp1,0x3f,sizeof(dp1));//dp1�����Сֵ,��ʼ���������
    for(int i=1;i<=2*n-1;i++){//��ʼ��dp[i][j][1]
        for(int j=i;j<=2*n-1;j++){
            dp1[i][j][1]=dp2[i][j][1]=mod(sum[j]-sum[i-1]);
        }
    }
    for(int t=2;t<=m;t++){//ö�ٷָ�ɼ�����,��t������t+1����ת��
        for(int l=t-1;l<n;l++){//ö�����䳤��,��ʼֵΪt-1,��Ϊj-i+1��������Ϊt��,���ܷ�Ϊt����
            for(int i=1;i+l<2*n;i++){//ö��������ʼ��
                int j=i+l;
                for(int k=i+t-2;k<j;k++){//ÿ�ַָ��k,k����k����,��ô��ʼֵ��ҪΪi+t-2,����k-i+1����Ϊt-1������ ��Ϊ�ǻ�״,����Ҫ��t-1�������ֳܷ�t-1����
                    dp1[i][j][t]=min(dp1[i][j][t],dp1[i][k][t-1]*dp1[k+1][j][1]);
                    dp2[i][j][t]=max(dp2[i][j][t],dp2[i][k][t-1]*dp2[k+1][j][1]);
                }
            }
        }
    }
    for(int i=1;i<=n;i++){//��⻷״�� n�����ܵ������������С���ֵ��Ϊ��
        ans1=min(ans1,dp1[i][i+n-1][m]);
        ans2=max(ans2,dp2[i][i+n-1][m]);
    }
    printf("%d\n",ans1);
    printf("%d\n",ans2);
    return 0;
}

/*
��ά���� �������� ת������
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
//dp1[i][j] dp2[i][j] �ֱ����ǰi�����ֳ�j�����ֵĳ˻�����Сֵ�����ֵ
int dp1[60][10],dp2[60][10],n,m,a[110],sum[110];

int mod(int x){
    return (x%10+10)%10;
}

int main(){
    int ans1=0x3f3f3f3f,ans2=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i+n]=a[i];
    }
    for(int i=1;i<=2*n-1;i++)
        sum[i]=sum[i-1]+a[i];
    for(int s=1;s<=n;s++){//ö��n�����ܵĳ���Ϊn���������伴 [s~s+n-1]
        memset(dp1,0x3f,sizeof(dp1));
        memset(dp2,0,sizeof(dp2));
        for(int i=1;i<=n;i++)//��ʼ�� ǰi�����ֳ�1�����ֵ�ֵ m�п��ܵ���1,����Ҫ���㵽ǰn������Ϊ1���ֵ�ֵ
            dp1[i][1]=dp2[i][1]=mod(sum[i+s-1]-sum[s-1]);
        for(int t=2;t<=m;t++){//�ֳ�t����
            for(int i=t;i<=n;i++){//ö���ұ߽� t�����ұ߽�����Ϊt
                for(int j=t-1;j<i;j++){//t-1�����ұ߽�����Ϊt-1
                    dp1[i][t]=min(dp1[i][t],dp1[j][t-1]*mod(sum[i+s-1]-sum[j+s-1]));
                    dp2[i][t]=max(dp2[i][t],dp2[j][t-1]*mod(sum[i+s-1]-sum[j+s-1]));
                }
            }
        }
        ans1=min(ans1,dp1[n][m]);//��ǰ��������[s,s+n-1]�����ֵ
        ans2=max(ans2,dp2[n][m]);
    }
    printf("%d\n",ans1);
    printf("%d\n",ans2);
    return 0;
}
*/

/*
//ac 55ms ����dfs ժ��dingcx����
#include<cstdio>
#include<algorithm>//�㷨�⣬��max��min
using namespace std;
const int MAXN=110;
const int INF=0x3f3f3f3f;//�����2e9��2147483647Ҳ��
const int n9[9]={9,81,729,6561,59409,531441,4782969,43046721,387420489};//m<=9�������ͺ���
int n,m;
int a[MAXN];
int ansmin=INF,ansmax=0;//��С����󣬶�Ҫ��ʼ��
int mod10(int x){//����ģ10�ĺ���
	return (x%10+10)%10;
}
void dfs(int depth,int now,int value){//�ذ�dfs
	if(value>=ansmin&&value*n9[m-depth]<=ansmax) return;//��֦
	int sum=0;
	if(depth==m){
		for(int i=now;i<=n;i++) sum+=a[i];//�����
		ansmin=min(ansmin,value*mod10(sum));//�Ƚ�
		ansmax=max(ansmax,value*mod10(sum));
		return;
	}
	for(int i=now;i<=(n-m+depth);i++){//������һ����
		sum+=a[i];//ǰ׺��
		dfs(depth+1,i+1,value*mod10(sum));//��һ������
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		a[i+n]=a[i];//�ƻ�����
	}
	for(int i=1;i<=n;i++){//ö�ٳ�ʼ��
		dfs(1,1,1);//����1��ֻ���ɺ�
		for(int j=1;j<=2*n;j++) a[j]=a[j+1];//��ǰŲ
	}
	printf("%d\n%d\n",ansmin,ansmax);//���
	return 0;//��������
}
*/
