/*
����:N��ʯ�Ӱڳ�һ���ߡ���Ҫ��ʯ���д���غϲ���һ�ѡ��涨ÿ��ֻ��ѡ����
��2��ʯ�Ӻϲ����µ�һ�ѣ������µ�һ��ʯ������Ϊ�ôκϲ��Ĵ��ۡ�
���㽫N��ʯ�Ӻϲ���һ�ѵ���С���ۡ�
���磺 1 2 3 4���в��ٺϲ�����
1 2 3 4 => 3 3 4(3) => 6 4(9) => 10(19)
1 2 3 4 => 1 5 4(5) => 1 9(14) => 10(24)
1 2 3 4 => 1 2 7(7) => 3 7(10) => 10(20)
��������Ϊ�ܴ��ۿ��Կ�������һ�ַ����Ĵ�����ͣ����ڸ���n��ʯ�ӵ�������
������С�ϲ����ۡ�
n<=1000.
����:https://www.51nod.com/Challenge/Problem.html#problemId=1022
˼·:
n�����1000,�������ԭ�����ص�����dp O(N^3)=10^9,1s֮����Ȼ�ᳬʱ,
������Ҫ�õ��ı��β���ʽ�Ż�,ʵ�����ڷָ�����ʱ��¼���ŵĶϵ�,
����ı��β���ʽ��ʱҲû����,�м���֤��������:
https://blog.csdn.net/noiau/article/details/72514812
https://wenku.baidu.com/view/c44cd84733687e21af45a906.html
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp[2100][2100],s[2100][2100],sum[2100];
int main(){
    int minc=INF;
    memset(dp,INF,sizeof(dp));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i+n]=sum[i];
    }
    for(int i=1;i<=2*n-1;i++){
        sum[i]+=sum[i-1];
        dp[i][i]=0;
        s[i][i]=i;
    }
    for(int l=1;l<=n-1;l++){
        for(int i=1;i+l<=2*n-1;i++){
            int j=i+l;
            for(int k=s[i][j-1];k<=s[i+1][j];k++){
                if(dp[i][j]>dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1]){
                    dp[i][j]=dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1];
                    s[i][j]=k;//��¼�ϵ�
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
        minc=min(minc,dp[i][i+n-1]);
    printf("%d",minc);
    return 0;
}
