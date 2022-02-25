/*
����:��mԪ,��n������,����ÿ������ļ۸�w[i],��x����i���������
���a[i]*x+b[i]����,����ô����ʹ��õ������.
n<=1000,m<=2000,w[i]<=2000
����:http://acm.hdu.edu.cn/showproblem.php?pid=5410
˼·:���ȹ���ÿ�������õ��ǹ���:a[i]*x+b[i],���Կ�������
b[i]�������ʵ��ֻ�������������벻��,��a[i]���򼸸���������,
�ͻ��м���a[i],��ô����b[i]ʵ����01����,��a[i]����ȫ����ֻҪ����
�ۼӼ���.��˶��ڵ�i���������ж����벻��dp[j]=max(dp[j],dp[j-w[i]]+a[i]+b[i]);
�������i����Ʒ�Ƿ�Ҫ������ת����dp[j]=max(dp[j],dp[j-w[i]]+a[i]);ֻ�ǲ����ۼ�a[i]
���������i������û��,��ô��������ȫ������Ȼ���Ž�Ҳ��û���,
�����i����������һ����,����������Ƿ�������ܻ�ø��Ž�.
*/
//ac 93ms 01����+��ȫ����
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 2100
typedef long long ll;
using namespace std;

int n,m,w[N],a[N],b[N];
ll dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&m,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&a[i],&b[i]);
        for(int i=1;i<=n;i++){
            //�����Ƚ���01����������ȫ����˳�� ����Ӱ�����Ž�
            for(int j=m;j>=w[i];j--)//01����
                dp[j]=max(dp[j],dp[j-w[i]]+a[i]+b[i]);
            for(int j=w[i];j<=m;j++)//��ȫ����
                dp[j]=max(dp[j],dp[j-w[i]]+a[i]);
        }
        printf("%lld\n",dp[m]);
    }
    return 0;
}

/*
//ac 78ms 01����+��ȫ����
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 2100
typedef long long ll;
using namespace std;

int n,m,w[N],a[N],b[N];
ll dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&m,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&a[i],&b[i]);
        for(int i=1;i<=n;i++){
            for(int j=m;j>=w[i];j--)
                dp[j]=max(dp[j],dp[j-w[i]]+a[i]+b[i]);
        }
        for(int i=1;i<=n;i++){
            for(int j=w[i];j<=m;j++)
                dp[j]=max(dp[j],dp[j-w[i]]+a[i]);
        }
        printf("%lld\n",dp[m]);
    }
    return 0;
}
*/

/*
��Ʒ�������ɴ�1000,�����������2000,
���dfs��������Ȼ����,�϶�tle
*/
