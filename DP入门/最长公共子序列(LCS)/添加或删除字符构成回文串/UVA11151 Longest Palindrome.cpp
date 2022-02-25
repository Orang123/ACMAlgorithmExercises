/*
����:ժ������
����һ���ַ�������������ͨ��ȥ��Щ�ַ��õ�����Ļ��ĵĳ��ȡ�
�ַ�������<=1000.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2092
˼·:LCS����.
*/
//ac 10ms ����dp �±��1��ʼ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,dp[N][N];
char a[N],b[N];

int main(){
    int T;
    scanf("%d",&T);
    getchar();//����س���,����gets�������scanf("%d%*c",&T);
    while(T--){
        gets(a+1);//���������gets scanf����� ���ܰ����˿ո��
        n=strlen(a+1);
        for(int i=1;i<=n;i++)
            b[i]=a[n-i+1];
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i] == b[j])
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        printf("%d\n",dp[n][n]);
    }
    return 0;
}

/*
//ac 10ms �±��0��ʼ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,dp[N][N];
char a[N],b[N];

int main(){
    int T;
    scanf("%d",&T);
    getchar();//����س���,����gets�������scanf("%d%*c",&T);
    while(T--){
        gets(a);//���������gets scanf����� ���ܰ����˿ո��
        n=strlen(a);
        for(int i=0;i<n;i++)
            b[i]=a[n-i-1];
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i-1] == b[j-1])
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        printf("%d\n",dp[n][n]);
    }
    return 0;
}
*/

/*
//ac 0ms ���������Ż� �±��1��ʼ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,dp[2][N];
char a[N],b[N];

int main(){
    int T;
    scanf("%d",&T);
    getchar();//����س���,����gets�������scanf("%d%*c",&T);
    while(T--){
        gets(a+1);//���������gets scanf����� ���ܰ����˿ո��
        n=strlen(a+1);
        for(int i=1;i<=n;i++)
            b[i]=a[n-i+1];
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i] == b[j])
                    dp[i%2][j]=dp[(i-1)%2][j-1]+1;
                else
                    dp[i%2][j]=max(dp[(i-1)%2][j],dp[i%2][j-1]);
            }
        }
        printf("%d\n",dp[n%2][n]);
    }
    return 0;
}
*/
