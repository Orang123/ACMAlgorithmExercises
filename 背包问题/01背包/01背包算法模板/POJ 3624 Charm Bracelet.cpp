#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 3500
#define M 13000
using namespace std;
//ac 266ms 01��������
/*
����:01��������
����:http://poj.org/problem?id=3624
˼·:01��������
*/

int n,v,w[N],val[N],dp[M];
int main(){
    memset(dp,0,sizeof(dp));//������װ������,��ʼ��Ϊ0
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&w[i],&val[i]);
    for(int i=1;i<=n;i++)
        //������������Ϊ����ᵼ��j�ڽ�Сʱdp[j]���º�,��j�ϴ�ʱ,����dp[j]=dp[j-w[i]]+val[i]���֮ǰ��С��j��ֵ�ظ��ۼ�,����i����Ʒ�ظ�ѡȡ,��Ȼ�Ǵ��
        //������տ�ʼ���µ��ǽϴ��j,j�ǲ��ϼ��ٵ�,dp[j-w[i]]��Զ��û�и��¹���,������ȷ
        for(int j=v;j>=w[i];j--)
            dp[j]=max(dp[j],dp[j-w[i]]+val[i]);//dp[j]����dp[i-1][j],dp[j-w[i]]����dp[i-1][j-w[i]]
    printf("%d",dp[v]);
    return 0;
}
