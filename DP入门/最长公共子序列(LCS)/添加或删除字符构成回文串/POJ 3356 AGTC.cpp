/*
����:���ֲ��������룬ɾ�����޸ģ������ٲ�������ʹ�õ�һ������ɵڶ�����
�ַ�������<=1000.
����:http://poj.org/problem?id=3356
˼·:LCS.����ȼ�ȥLCS����,max(n,m)-dp[n][m].
*/
//ac 16ms ����ȼ�ȥLCS����,max(n,m)-dp[n][m]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,m,dp[N][N];
char a[N],b[N];

int main(){
    int len;
    while(scanf("%d %s",&n,a+1)!=EOF){
        scanf("%d %s",&m,b+1);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i]==b[j])
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        len=max(n,m);
        printf("%d\n",len-dp[n][m]);
    }
    return 0;
}

/*
//ac 0ms
//����˼·ժ�Բ���:https://blog.csdn.net/u013480600/article/details/40780781
//dp[i][j] Ϊa����ǰi���ֱ��b����ǰj��������Ҫ����С������
//��ʼ״̬: dp[0][i]==i�� dp[i][0]=i. ����ǰ�߱�ʾ���a��i���ַ�, ���߱�ʾɾ��a��i���ַ�.
//״̬ת��: dp[i][j]�������ֻ��Դ����ĩβ����3�ֲ���,��ô������3�����.
//1.dp[i-1][j-1]+(x[i]==y[j]?0:1).�����Դ����Ŀ�����һ���ַ���ͬ, ��Ȼdp[i-1][j-1]��������.
//����������һ���ַ���ͬ, ��ô�����滻Դ�������һ���ַ���Ŀ�����Ǹ��ַ�.
//2.dp[i-1][j]+1.���ǿ���ɾ��Դ�����һ���ַ�(1��ɾ������), Ȼ��Դ�����Ŀ��(dp[i-1][j]������).
//3.dp[i][j-1]+1.���ǿ��Խ�Դ�����Ŀ����ǰj-1���ַ��Ĵ�(dp[i][j-1]������),Ȼ����Դ��ĩβ�����һ��b[j]�������Ŀ��(1������).
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,m,dp[N][N];
char a[N],b[N];

int main(){
    int len;
    for(int i=0;i<N;i++)
    	dp[i][0]=dp[0][i]=i;
    while(scanf("%d %s",&n,a+1)!=EOF){
        scanf("%d %s",&m,b+1);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
            	dp[i][j]=dp[i-1][j-1]+(a[i] == b[j]?0:1);
            	dp[i][j]=min(dp[i][j],min(dp[i-1][j]+1,dp[i][j-1]+1));
            }
        }
        printf("%d\n",dp[n][m]);
    }
    return 0;
}
*/
