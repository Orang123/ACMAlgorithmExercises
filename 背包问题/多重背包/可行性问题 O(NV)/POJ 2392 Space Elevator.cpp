/*
题意:有n种积木块,每个块的高度h[i],第i种块允许用的最高高度为max_h[i],
数量为cnt[i],求能组合的最高高度.
链接:http://poj.org/problem?id=2392
思路:因为要求最高高度,但是每种块有单独的限高,所以要先放限制高度较小的,
这样才能高度最大化,否则如果先放限制高度较大的,后面放高度限制较小的时候,
本身的高度已经很大了,可能会导致限高小的块放不了,因此先放限制高度小的,对于
限制高度本身较大的影响是最小的.
*/
//ac 63ms 贪心+限制物品数量的完全背包
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
//79ms 可行性O(nv)标准解
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
