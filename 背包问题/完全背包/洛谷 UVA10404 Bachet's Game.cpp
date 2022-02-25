/*
//题意 思路摘自网上
题意:给定n个石头,和m种去除石头的方式,每种方式可以去除一定量的石头,
现在Stan(简称S),Ollie(简称O),S先手,O后手,每次每个人能选择一种去除
石头的方式,谁去除最后一堆谁就赢了.要求出必胜之人是谁.
链接:https://www.luogu.com.cn/problem/UVA10404
思路:问题可以看做是一个完全背包的变形,dp[i]只有0和1两种状态,1是代表
当前i个石子先取者为必胜,0带表当前i个石子先取者为必败.转态转移方程
if(dp[i - val[j]] == 0)dp[i] = 1;(当前状态可以转化成先手必败,说明当前
为先手必胜).
*/

//ac 160ms 完全背包+博弈
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 1000100
using namespace std;

//dp[i]=true表示有i个石子，首先选的人可以获胜。
int n,m,w[N],dp[M];

int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%d",&w[i]);
        for(int i=1;i<=n;i++){//这里模拟博弈过程 必须先枚举背包容量 后枚举每种去除石头的方式
            for(int j=1;j<=m;j++){
                if(i-w[j]>=0 && !dp[i-w[j]]){
                    dp[i]=1;
                    break;
                }
            }
        }
        if(dp[n])//dp[n]=1,stan最后移动石头
            printf("Stan wins\n");
        else
            printf("Ollie wins\n");
    }
    return 0;
}
