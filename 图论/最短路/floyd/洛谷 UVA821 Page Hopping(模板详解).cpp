#include<bits/stdc++.h>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;
//floyd 路径分割点k放在最外层原因:
//1.https://www.zhihu.com/question/30955032
//2.https://discuss.codechef.com/t/floyd-warshall-algorithm/1403
/*
题意:n个网页通过点击可跳转到另一个网页,需要的距离为1,
现在求任意两网页跳转的最小距离的平均值.
链接:https://www.luogu.com.cn/problem/UVA821
思路:n<=100 floyd
*/

int dis[N][N];
int main(){
    int u,v,n,cnt,cas=0;
    double sum;
    while(scanf("%d%d",&u,&v)&&u+v){
        cas++;
        n=cnt=sum=0;
        /*
        如果题目答案会用到dis[i][i]这样的自环,初始化时一定要将dis[i][i]设置为0.
        实际全部设置为INF如果存在i->k->k->i这样的回路,mp[i][i]会错误
        更新成mp[i][k]+mp[k][i]的数值,但它本身就应为0,但这并不影响
        求解其余顶点对的最短距离.
        实际按照dp的思维初始状态是dp[i][i],因此dp[i][i]初始化为0,其余初始化为INF.
        如果dp[i][i]也都设置为INF,那么没有初始状态,加入存在1-5边权为3,则不能直接更新dp[1][5]=3,
        而只能通过别的中间状态dp[1][3]+dp[3][5]=4+3=dp[1][5]=7,这样结果就偏大.
        */
        for(int i=1;i<N;i++)
            for(int j=1;j<N;j++)
                dis[i][j]=(i==j?0:INF);
        dis[u][v]=1;
        n=max(n,max(u,v));//算出最大点数
        while(scanf("%d%d",&u,&v)&&u+v){
            dis[u][v]=1;
            n=max(n,max(u,v));
        }
        //这里必须先枚举路径的分割点k,再枚举起点i和终点j. floyd是一种基于动态规划 枚举分割点k进行状态转移的算法由k-1向k转移
        /*
        中间点k的枚举必须在最外层的原因,详细解释如下:
        dp[k][i][j]表示i、j之间可以通过编号为k的节点的最短路径,dp[0][i][j]为其初始
        状态,表示i、j没有经过任何节点的最短路径.
        dp[k][i][j]的最优解可以不经过k节点,即:直接继承上一个状态dp[k-1][i][j],表示不经过k这个节点.
        也可以经过k节点,由dp[k-1][i][k]+dp[k-1][k][j],上一状态经过k-1节点的2段最短路径且
        将k作为中间点组合成的最优解构成,即:dp[k][i][j]=max(dp[k][i][j],dp[k-1][i][k]+dp[k-1][k][j]),
        因为dp[k][i][j]只和dp[k-1][i][j]有关,所以滚动数组优化掉第一维度k,状态转移方程变为:
        dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]),这个状态转移方程并不是传统区间dp,
        总之Floyd算法的本质是DP,而k是DP的阶段,因此要写最外面.
        dp[k][i][j] i到j的路径只可能经过1~k这些点,而不可能经过k+1、k+2、k+3..n这些点,
        dp[k][i][j]只是在i到j经过1..k这些路径时的最优解,但并不是实际i到j的最优解,因为实际
        i到j的最优解可能是经过k+1、k+2...n这些点的.
        dp正是不断枚举新的中间点来更新i、j间的最优解,当k=n时已达到全局最优.
        尝试将这个dp改为记忆化搜索,并且想想看最初的暴力枚举搜索做法可能是怎样的？
        */
        for(int k=1;k<=n;k++){//枚举中间点
            for(int i=1;i<=n;i++){//枚举起点
                for(int j=1;j<=n;j++)//枚举终点
                    dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(dis[i][j]!=INF&&i!=j){
                    sum+=dis[i][j];
                    cnt++;//求出多少个最短路
                }
            }
        }
        printf("Case %d: average length between pages = %.3f clicks\n",cas,sum/cnt);
    }
    return 0;
}
