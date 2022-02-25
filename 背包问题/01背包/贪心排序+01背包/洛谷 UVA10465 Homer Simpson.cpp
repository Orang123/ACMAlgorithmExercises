/*
题意:摘自网上
有两种汉堡包,第一种吃一个需要花m分钟,第二种吃一个需要花n分钟.
现在你有t分钟的时间,问你最少浪费几分钟不能吃汉堡,也就是让吃汉堡的时间
尽可能多.当吃汉堡花费的时间达到最大时,问你最多能吃几个汉堡?
链接:https://www.luogu.com.cn/problem/UVA10465
思路:每种汉堡可以吃多个,属于二维目标条件的完全背包问题.
dp[i][j]表示吃前i个汉堡在恰好花费时间j所能吃的最多的汉堡个数.
初始状态只有dp[0]=0是合法状态.
*/
//ac 80ms 二维目标条件的完全背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 3
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;

int t,w[N],dp[M];

int main(){
    while(scanf("%d%d%d",&w[1],&w[2],&t)!=EOF){
        memset(dp,-1,sizeof(dp));
        dp[0]=0;
        for(int i=1;i<=2;i++){
            for(int j=w[i];j<=t;j++){
                if(dp[j-w[i]]!=-1)
                    dp[j]=max(dp[j],dp[j-w[i]]+1);
            }
        }
        int ans=0;
        //吃汉堡时间降序判断是否合法,第一个合法的就是最多能吃汉堡的时间,对应的dp[ans]就是最多吃的汉堡个数
        for(int i=t;t>=0;i--){
            if(dp[i]!=-1){
                ans=i;
                break;
            }
        }
        printf("%d",dp[ans]);
        if(ans<t)
            printf(" %d",t-ans);
        printf("\n");
    }
    return 0;
}
