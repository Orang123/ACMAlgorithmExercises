/*
����:ACBOY��n�Ź���Ҫ��,���ܹ���m������Щ����,һ�ſ���m���Ϸ�,
�ֱ��Ϊ1..m������,�������j���ڹ���i��,���ܹ���õļ�ֵ��a[i][j],
��ACBOY��m�����Ͽ��ܻ������ֵ.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1712
1<=n,m<=100
˼·:����ÿ�ſε��Ϸ���m�ַ�ʽ����,�����ſ�ֻ��ѡ��һ�ַ�ʽȥ��,
���Խ���ͬ����Ϊ��ͬ�ķ���,���ڵ���Ʒ�������ſ�m���Ͽη�ʽ,��Ʒ
������������Ͽη�ʽ������,��Ʒ��ֵ�������Ͽη�ʽ��õļ�ֵa[i][j].
��������Ϊ������m,ת��Ϊһ�����鱳��ģ��.
*/
//ac 62ms һά����ʵ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int a[N][M],dp[M];

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m) && n+m){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&a[i][j]);
        for(int i=1;i<=n;i++){
            for(int j=m;j>=1;j--){//��Ϊ���пγ�����Ҫ��1����,���Ա�������j���½���1
                for(int k=1;k<=j;k++)//�Ͽε��������ᳬ����ǰ��������j,����Ͽη�ʽ�����Ͻ���j
                    dp[j]=max(dp[j],dp[j-k]+a[i][k]);
            }
        }
        printf("%d\n",dp[m]);
    }
    return 0;
}

/*
//ac 62ms ��ά����ʵ�� ������ѭ��˳��,��ö��ö�ٱ�������,��ö��ÿ����Ʒ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int a[N][M],dp[N][M];

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m) && n+m){
        memset(dp[0],0,sizeof(dp[0]));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&a[i][j]);
        for(int i=1;i<=n;i++){
            //��Ȼ���пγ�����Ҫ��1����,��������j���½���1,����ÿ��״̬��dp[i][0]��Ҫ�̳�ǰdp[i-1][0],
            //��Ϊĳ�������һ����ƷҲ��ȡ,���j�½���0
            for(int j=m;j>=0;j--){
                dp[i][j]=dp[i-1][j];
                for(int k=1;k<=j;k++)//�Ͽε��������ᳬ����ǰ��������j,����Ͽη�ʽ�����Ͻ���j
                    dp[i][j]=max(dp[i][j],dp[i-1][j-k]+a[i][k]);
            }
        }
        printf("%d\n",dp[n][m]);
    }
    return 0;
}
*/

/*
//ac 46ms ��ά����ʵ�� �ߵ�������ѭ��˳��,��ö��ÿ����Ʒ,��ö�ٱ�������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int a[N][M],dp[N][M];

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m) && n+m){
        memset(dp[0],0,sizeof(dp[0]));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&a[i][j]);
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++)
                dp[i][j]=dp[i-1][j];
            for(int k=1;k<=m;k++)//�Ͽε��������ᳬ����ǰ��������j,����Ͽη�ʽ�����Ͻ���j
                for(int j=k;j<=m;j++){//��Ϊ���пγ�����Ҫ��1����,���Ա�������j���½���1
                    dp[i][j]=max(dp[i][j],dp[i-1][j-k]+a[i][k]);
            }
        }
        printf("%d\n",dp[n][m]);
    }
    return 0;
}
*/
