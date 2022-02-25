/*
����:��n�ֻ�ľ��,ÿ����ĸ߶�h[i],��i�ֿ������õ���߸߶�Ϊmax_h[i],
����Ϊcnt[i],������ϵ���߸߶�.
����:http://poj.org/problem?id=2392
˼·:��ΪҪ����߸߶�,����ÿ�ֿ��е������޸�,����Ҫ�ȷ����Ƹ߶Ƚ�С��,
�������ܸ߶����,��������ȷ����Ƹ߶Ƚϴ��,����Ÿ߶����ƽ�С��ʱ��,
����ĸ߶��Ѿ��ܴ���,���ܻᵼ���޸�С�Ŀ�Ų���,����ȷ����Ƹ߶�С��,����
���Ƹ߶ȱ���ϴ��Ӱ������С��.
*/
//ac 63ms ̰��+������Ʒ��������ȫ����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 410
#define M 40010
using namespace std;

struct block{
    int h,max_h,cnt;
    bool operator <(const block &a)const{
        return max_h<a.max_h;
    }
}a[N];
int dp[M],sum[M];

int main(){
    int k;
    while(scanf("%d",&k)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d%d",&a[i].h,&a[i].max_h,&a[i].cnt);
        sort(a+1,a+k+1);
        int ans=0;
        dp[0]=1;
        for(int i=1;i<=k;i++){
            memset(sum,0,sizeof(sum));
            for(int j=a[i].h;j<=a[i].max_h;j++){
                if(!dp[j]&&dp[j-a[i].h]&&sum[j-a[i].h]+1<=a[i].cnt){
                    dp[j]=1;
                    sum[j]=sum[j-a[i].h]+1;
                    ans=max(ans,j);
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//79ms ������O(nv)��׼��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 410
#define M 40010
using namespace std;

struct block{
    int h,max_h,cnt;
    bool operator <(const block &a)const{
        return max_h<a.max_h;
    }
}a[N];
int dp[M];

int main(){
    int k;
    while(scanf("%d",&k)!=EOF){
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=k;i++)
            scanf("%d%d%d",&a[i].h,&a[i].max_h,&a[i].cnt);
        sort(a+1,a+k+1);
        int ans=0;
        dp[0]=1;
        for(int i=1;i<=k;i++){
            for(int j=0;j<=a[i].max_h;j++){
                if(dp[j] != -1)
                    dp[j]=a[i].cnt;
                if(j>=a[i].h)
                    dp[j]=max(dp[j],dp[j-a[i].h]-1);
                if(dp[j]!=-1)
                        ans=max(ans,j);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
