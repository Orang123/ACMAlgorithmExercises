/*
题意:摘自网上
给出课题数n，以及每堂课的时间l,以及常数c，然后是n个课题所需要的时间t[i]。
问题1：最少需要几节课时可以讲所有的课题讲完，并且课题的顺序不能调换，
一个课题不能分在两节课讲。
问题2：在用的课时最少的情况下，如何让同学们的不满意度最低，
不满意度的计算是根据课时的剩余时间t计算的.
DI的计算方式
1.剩余时间t为0,badness为0,
2.1<=t<=10,badness=-c,
3.其余情况 badness=(t-10)^2.
n<=1000,1<=l<=500.
链接:https://www.luogu.com.cn/problem/UVA607
思路:问题1可以直接贪心,将尽可能多地课题安排在同一门课中.
问题2可以在问题1计算的最少课程数不变的情况下,枚举每门课是安排在
当前课堂上一门课后面 还是重新安排在下一堂课的开始,这样结束条件是
当最少课程数为0时,刚好n个课题都已安排完.
dp[i][j]表示在剩下cnt-i+1门课安排j~n的课题所产生的最少badness.
因为这个问题负数和0都是合法状态,因此判断重叠子问题需要单独设置vis数组标记.
*/
//ac 160ms 记忆化搜索
//dp[i][j]表示在剩下cnt-i+1门课安排j~n的课题所产生的最少badness.
//复杂度O(1000*1000)=10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,l,c,t[N],cnt,dp[N][N],vis[N][N];

int getIndex(int val){
    if(!val)
        return 0;
    else if(val>=1 && val<=10)
        return -c;
    else
        return (val-10)*(val-10);

}

int  dfs(int i,int j){
    if(vis[i][j])
        return dp[i][j];
    if(i == cnt+1){
        if(j == n+1)
            return dp[i][j]=0;
        else
            return dp[i][j]=INF;
    }
    dp[i][j]=INF;
    int sum=0;
    for(int k=j;k<=n;k++){
        sum+=t[k];
        if(sum>l)
            break;
        //输入样例是必然有解的 所以不必特判INF 无解的情况
        dp[i][j]=min(dp[i][j],dfs(i+1,k+1)+getIndex(l-sum));
    }
    vis[i][j]=1;
    return dp[i][j];
}

int main(){
    int sum,cas=0;
    while(scanf("%d",&n) && n){
        sum=0;
        cnt=1;
        cas++;
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&l,&c);
        for(int i=1;i<=n;i++){
            scanf("%d",&t[i]);
            sum+=t[i];
            if(sum>l){
                sum=t[i];
                cnt++;
            }
        }
        if(cas!=1)
            printf("\n");
        printf("Case %d:\n",cas);
        printf("Minimum number of lectures: %d\n",cnt);
        printf("Total dissatisfaction index: %d\n",dfs(1,1));
    }
    return 0;
}

/*
//ac 140ms 正向dp
//摘自博客:https://www.cnblogs.com/cyd308/p/4771624.html
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int inf=0x3f3f3f3f;

int n,l,c;
    int i,j,k;
    int cas=1,ans;
    int a[1005],sum[1005],dp[1005][1005];

int dissatisfaction(int x)
{
    if(x==0)
        return 0;
    else if(1<=x && x<=10)
        return (-c);
    else
        return (x-10)*(x-10);

}

int main()
{

    while(scanf("%d",&n)!=EOF && n!=0)
    {
        sum[0]=0;
        scanf("%d %d",&l,&c);
        for(i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            sum[i]=sum[i-1]+a[i];
        }
        for(i=0;i<=n;i++)
        {
            dp[i][0]=0;
            for(j=1;j<=n;j++)
                dp[i][j]=inf;
        }

        for(i=1;dp[i-1][n]==inf;i++)
        {
            for(j=i;j<=n && sum[j]<=i*l;j++)
            {
                for(k=j;k>=i-1;k--)
                {
                    if(dp[i-1][k]!=inf && (sum[j]-sum[k])<=l)
                        dp[i][j]=min(dp[i][j],dp[i-1][k]+dissatisfaction(l-sum[j]+sum[k]));
                    else if(sum[j]-sum[k]>l)
                        break;
                }
            }
        }

        for(i=1;i<=n;i++)
        {
            if(dp[i][n]!=inf)
            {
                ans=i;
                break;
            }
        }
        if(cas>1)
            printf("\n");
        printf("Case %d:\nMinimum number of lectures: %d\nTotal dissatisfaction index: %d\n",cas++,ans,dp[ans][n]);
    }
    return 0;
}
*/
