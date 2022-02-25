/*
����:����T������,���1~T,ÿ�����͵�������N[i]��.
�������ֵ��ܸ���Ϊa.����Щ������ѡ��ָ�������ļ�
�����ж����ַ���,�ʼ��ϸ�����S~B֮��ķ������ܹ���
����.���������ܻ�ܴ�,ֻ�豣������ĺ�6λ���ּ���.
T<=1000,N[i]<=100.
����:��T�����������family���������aֻ���ϣ����ִ������Եڼ���family�ģ�
������aֻ��ȡ��xֻ��ɳ��ȴ�С��[s,b]֮��ļ��������ж��ٸ��� ת��һ�����⣬
����T������ a �����壬������ȡ [s,b] ����ɵļ��ϸ����ж��ٸ���
����:http://poj.org/problem?id=3046
˼·:ʵ�ʾ����� ָ���������ظ���ϵķ�������,��Ȼֱ��
��������Ʒ�ŵ�һ����01����,��ͬ�����͵������ж���ᵼ��
���ظ�����ϸ����ظ�����,�ᳬ�������������ֵ�����.���Կɲ��÷��鱳������,����ͬ
���͵�������Ϊһ��,ÿ���ڵ���ƷΪ�����������ֵĿ��ܸ���,
����ÿ�μ�������һ���Ե�ȡ��i���͵�����k��,��ǰ��ǰi-1��
���͵������в���������i�����͵�����,�Ͳ����ظ�����.
*/
//ac 282ms ���鱳��ͳ�Ʒ�����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 100100
#define mod 1000000
using namespace std;

int T,a,s,b,num[N],dp[M];

int main(){
    int x;
    memset(dp,0,sizeof(dp));
    memset(num,0,sizeof(dp));
    scanf("%d%d%d%d",&T,&a,&s,&b);
    for(int i=1;i<=a;i++){
        scanf("%d",&x);
        num[x]++;
    }
    dp[0]=1;
    for(int i=1;i<=T;i++){
        for(int j=a;j>=1;j--){
            for(int k=1;k<=num[i];k++)
                dp[j]=(dp[j]+dp[j-k])%mod;
        }
    }
    int ans=0;
    for(int i=s;i<=b;i++)
        ans=(ans+dp[i])%mod;
    printf("%d",ans);
    return 0;
}

/*
//ac 110ms ��������
//�ο�����:https://blog.csdn.net/stay_accept/article/details/50118457
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdlib.h>
using namespace std;
const long long MOD=1000000;
long long dp[1005][100005];
long long num[1005];
int main(){
    long long T,A,S,B,i,j,x,ans;
    while(scanf("%I64d%I64d%I64d%I64d",&T,&A,&S,&B)!=EOF){
        memset(num,0,sizeof(num));
        for(i=0;i<A;i++){
            scanf("%I64d",&x);
            num[x-1]++;
        }                                               //����dp[i][j]�Ǵ�ǰi����Ʒ��ȡ��j�����������
        for(i=0;i<=T;i++)                               //���Կ��Դ�ǰi-1����Ʒ��ȡ��j-k�����ٴӵ�i����
        dp[i][0]=1;                                     //Ʒ��ȡ��k���������Ƴ����ƹ�ϵʽ
        for(i=0;i<T;i++)                                //dp[i+1][j]=��{k=0~min(j,a[i])}dp[i][j-k]����չ��
        for(j=1;j<=B;j++){                              //��˿��Կ�����{k=0~min(j-1,a[i])}dp[i][j-1-k]���
            if(j-1-num[i]>=0)                           //��{k=0~min(j,a[i])}dp[i][j-k]����һ��dp[i][j]��
            dp[i+1][j]=(dp[i+1][j-1]+dp[i][j]-dp[i][j-1-num[i]]+MOD)%MOD;
            else                                        //dp[i][j-1-ai],����Ϊdp[i+1][j]=��{k=0~min(j,a[i])}
            dp[i+1][j]=(dp[i+1][j-1]+dp[i][j])%MOD;     //dp[i][j-k]�����ԡ�{k=0~min(j-1,a[i])}dp[i][j-1-k]=
        }                                               //dp[i+1][j-1].���Կ����Ƴ��Ż���ĵ���ʽ
        ans=0;                                          //dp[i+1][j]=dp[i+1][j-1]+dp[i][j]-dp[i][j-1-ai]
        for(j=S;j<=B;j++)
        ans=(ans+dp[T][j])%MOD;                         //��S��B�ӺͲ�ȡ��
        printf("%I64d\n",ans);
    }
    return 0;
}
*/

/*
//ac 0ms ���ƶ��ر���������
//���Ӷ�O(n^2)
�ο�����:https://blog.csdn.net/sdj222555/article/details/10440021
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#define MAXN 111111
#define INF 1000000007
using namespace std;
int dp[2][MAXN], num[1111];
int sum[MAXN], up[1111];
int main()
{
    int T, S, A, B, x;
    scanf("%d%d%d%d", &T, &A, &S, &B);
    for(int i = 1; i <= A; i++)
    {
        scanf("%d", &x);
        num[x]++;
    }
    for(int i = 1; i <= T; i++)
        up[i] = up[i - 1] + num[i];
    dp[0][0] = 1;
    int *pre = dp[0], *nxt = dp[1];
    for(int i = 1; i <= T; i++)
    {
        sum[0] = pre[0];
        for(int j = 1; j <= up[i]; j++)
            sum[j] = (sum[j - 1] + pre[j]) % 1000000;
        for(int j = 0; j <= up[i]; j++)
        {
            int tmp = max(0, j - num[i]);
            nxt[j] = (tmp == 0 ? sum[j] : (sum[j] - sum[tmp - 1] + 1000000));
            nxt[j] %= 1000000;
        }
        swap(nxt, pre);
    }
    int ans = 0;
    for(int i = S; i <= B; i++)
        ans = (ans + pre[i]) % 1000000;
    printf("%d\n", ans);
    return 0;
}
*/
