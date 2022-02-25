#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M0 110
using namespace std;
//ac 51ms 二维费用背包(滚动数组优化掉了一维) 不优化有三维dp[i][j][k]
/*
题意:有n件物品和一个容量是V的背包,背包能承受的最大重量是M.
每件物品只能用一次.体积是v[i],重量是m[i],价值是w[i].
求解将哪些物品装入背包,可使物品总体积不超过背包容量,
总重量不超过背包可承受的最大重量,且价值总和最大,
输出最大价值.

释义:二维费用的背包问题是指:对于每件物品,具有两种不同的费用,
选择这件物品必须同时付出这两种费用.对于每种费用都有一个可付
出的最大值(背包容量).问怎样选择物品可以得到最大的价值.
链接:https://www.acwing.com/problem/content/description/8/
思路:模板题,再增加一个维度,一个维度作为容量限制,一个维度作为
重量限制,仍然是按照01背包的思路,具体先枚举容量限制还是先枚举
重量限制,并没有区别,都可解决,但是要注意第二层循环枚举的变量要
降序这样才可保证状态转移方程中的dp[j-v[i]][k-m[i]]是没有放入第
i个物品的前i-1个物品的状态.
*/
/*
说明:
对于求解容量V恰好装满,重量M尽可能多地装满就初始化dp[0][0..M]=0,
对于求解重量M恰好装满,容量V尽可能多地装满就初始化dp[0..V][0]=0,
对于求解容量V和重量M都恰好装满就初始化dp[0][0]=0
对于求解容量V和重量M都尽可能多地装满就初始化 memset(dp,0,sizeof(dp))

对于求解放入指定物品个数的最大价值,方案数那类问题,本质就是二维费用背包,
物品个数本身就是一个维度,每个物品算一个物品个数费用为1,每次上一状态都是当前物品个数-1.
*/
int n,V,M,v[N],m[N],w[N],dp[M0][M0];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d",&n,&V,&M);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&v[i],&m[i],&w[i]);
    for(int i=1;i<=n;i++){
        //因为影响物品放入背包的限制条件 不光是重量还有体积,所以同时枚举背包剩余可用容积和重量
        //这样才能构造出在前i个物品最优解情况下,每个物品1、2、..i-1、i的放入与否的最优组合情况
        for(int j=V;j>=v[i];j--){
            for(int k=m[i];k<=M;k++)
                dp[j][k]=max(dp[j][k],dp[j-v[i]][k-m[i]]+w[i]);
        }
    }
    printf("%d",dp[V][M]);
    return 0;
}
/*
//ac 48ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M0 110
using namespace std;

int n,V,M,v[N],m[N],w[N],dp[M0][M0];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d",&n,&V,&M);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&v[i],&m[i],&w[i]);
    for(int i=1;i<=n;i++){
        for(int j=V;j>=v[i];j--){
            for(int k=M;k>=m[i];k--)
                dp[j][k]=max(dp[j][k],dp[j-v[i]][k-m[i]]+w[i]);
        }
    }
    printf("%d",dp[V][M]);
    return 0;
}
*/

/*
//ac 47ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M0 110
using namespace std;

int n,V,M,v[N],m[N],w[N],dp[M0][M0];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d",&n,&V,&M);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&v[i],&m[i],&w[i]);
    for(int i=1;i<=n;i++){
        for(int j=M;j>=m[i];j--){
            for(int k=v[i];k<=V;k++)
                dp[j][k]=max(dp[j][k],dp[j-m[i]][k-v[i]]+w[i]);
        }
    }
    printf("%d",dp[M][V]);
    return 0;
}
*/

/*
//ac 48ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M0 110
using namespace std;

int n,V,M,v[N],m[N],w[N],dp[M0][M0];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d",&n,&V,&M);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&v[i],&m[i],&w[i]);
    for(int i=1;i<=n;i++){
        for(int j=M;j>=m[i];j--){
            for(int k=V;k>=v[i];k--)
                dp[j][k]=max(dp[j][k],dp[j-m[i]][k-v[i]]+w[i]);
        }
    }
    printf("%d",dp[M][V]);
    return 0;
}
*/

/*
暴力搜索能做,但肯定tle
*/
