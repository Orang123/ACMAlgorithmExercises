#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
/*
题意:一头牛跑步，开始时劳累程度是0，一共有N分钟，如果第i分钟跑步的话，能跑di的距离。
同时劳累程度加1，如果这一分钟休息的话，劳累程度减一，而且如果一旦休息，就一定要休息到劳累程度为0时才能继续跑。
问第N分钟劳累程度是0的时候最多能跑多远。
链接:http://poj.org/problem?id=3661
思路:dp[i][j]代表经过i分钟疲劳值为j时所跑的最大距离
*/
int n,m,d[10100],dp[10100][510];

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++)
            scanf("%d",&d[i]);
        for(int i=1;i<=n;i++){
            dp[i][0]=dp[i-1][0];//上一分钟疲劳度为0,可以接着休息1分钟到i分钟
            for(int j=1;j<=m;j++){//枚举可能休息的时长
                if(i>j)
                    dp[i][0]=max(dp[i-j][j],dp[i][0]);//dp[i][0]=dp[i-j][j]代表在i-j分钟疲劳值为j时一直连续休息j分钟到i分钟疲劳值为0,所跑距离是之前dp[i-j][j]时的
                dp[i][j]=dp[i-1][j-1]+d[i];//第i分钟选择跑步,由之前i-1分钟 j-1疲劳值所跑距离+当前分钟所能跑的距离d[i]
            }
        }
        printf("%d\n",dp[n][0]);
    }
    return 0;
}


