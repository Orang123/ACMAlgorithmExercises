/*
题意:有n组物品和一个容量是v的背包.每组物品有num[i]个,
同一组内的物品最多只能选一个.每件物品的体积是w[i][j],
价值是val[i][j],其中i是组号,j是组内编号.求解在物品总
体积不超过背包容量条件下,能得到的最大价值.输出最大价值.
每个物品仍然只有选或不选,同一个物品只能选一次.
0<n,v<=100.
0<num[i]<=100.
0<w[i][j],val[i][j]<=100.
链接:https://www.acwing.com/problem/content/description/9/
思路:分组背包模板题.尽可能多地装满背包.
//dp[i][j]代表前i组在每组最多拿一件物品背包容量为j时能获得的最大价值.
滚动数组表示为dp[j].
时间复杂度O(n*v*max(num[i]))=100*100*100=10^6
*/
//ac 44ms 一维数组实现分组背包 每组最多取一个物品
//一维数组  后两层循环顺序,只能是先枚举枚举背包容量,再枚举每组物品,这样才能保证dp[j-w[i][k]]是前i-1组的状态
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

//dp[i][j]代表前i组在每组最多拿一件物品背包容量为j时能获得的最大价值.
int n,v,num[N],w[N][N],val[N][N],dp[M];

int main(){
    //尽可能多地装满背包,所有状态都合法
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++){
        scanf("%d",&num[i]);
        for(int j=1;j<=num[i];j++)
            scanf("%d%d",&w[i][j],&val[i][j]);
    }
    //考虑第i组的物品 时间复杂度O(n*v*max(num[i]))
    for(int i=1;i<=n;i++){
        //滚动数组优化这里背包容量必须降序,注意有可能物品体积为0,所以背包容量下界是0
        //后两层循环顺序不能颠倒,否则就会变成∑num[i]所有物品进行01背包,同组内物品可以取很多个了
        for(int j=v;j>=0;j--){
            //在背包容量为j时,考虑在前i-1组内物品最优解基础上放入第i组内编号为k的一个物品
            //或不放入第i组内物品即:前i-1组内物品最优解
            for(int k=1;k<=num[i];k++){//枚举第i组内的每个物品放入,比较求出那个放入后价值最大的物品作为最优解
                if(j>=w[i][k])//保证背包容量能放大下 第i组内第k个物品
                    //dp[j-w[i][k]]是前i-1组物品在背包容量为j-w[i][k]时的最优解 保证了第i组物品不会叠加选取,最多只能选一个
                    dp[j]=max(dp[j],dp[j-w[i][k]]+val[i][k]);
            }
        }
    }
    printf("%d",dp[v]);
    return 0;
}

/*
//ac 51ms 二维数组实现分组背包 后两层循环顺序,先枚举枚举背包容量,再枚举每组物品
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

//dp[i][j]代表前i组在每组最多拿一件物品背包容量为j时能获得的最大价值.
int n,v,num[N],w[N][N],val[N][N],dp[N][M];

int main(){
    //初始状态是一个组的物品也不放,尽可能多地装满背包,dp[0][1..v]=0 都是合法状态
    memset(dp[0],0,sizeof(dp[0]));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++){
        scanf("%d",&num[i]);
        for(int j=1;j<=num[i];j++)
            scanf("%d%d",&w[i][j],&val[i][j]);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=v;j++){//这里升序 降序皆可
            //有可能第i组一个物品也没有,所以要提前转移状态
            dp[i][j]=dp[i-1][j];//前i组的初始状态直接由前i-1组的最优解转移而来
            for(int k=1;k<=num[i];k++){//枚举第i组内每个物品放入 只保留放入后价值最大的那1个物品作为最优解
                if(j>=w[i][k])
                //k=1时,dp[i][j]代表不放入第i组内物品即前i-1组物品的最优解.
                //k>1时,dp[i][j]是之前放入第i组内编号为1~k-1各个物品(只有一个,不叠加)的最优解与dp[i-1][j]的最优解的较大值
                //dp[i-1][j-w[i][k]]是前i-1组物品在背包容量为j-w[i][k]时的最优解
                    dp[i][j]=max(dp[i][j],dp[i-1][j-w[i][k]]+val[i][k]);
            }
        }
    }
    printf("%d",dp[n][v]);
    return 0;
}
*/

/*
//ac 35ms 二维数组实现 颠倒后两层循环顺序,先枚举每组物品,再枚举背包容量
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

//dp[i][j]代表前i组在每组最多拿一件物品背包容量为j时能获得的最大价值.
int n,v,num[N],w[N][N],val[N][N],dp[N][M];

int main(){
    //初始状态是一个组的物品也不放,尽可能多地装满背包,dp[0][1..v]=0 都是合法状态
    memset(dp[0],0,sizeof(dp[0]));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++){
        scanf("%d",&num[i]);
        for(int j=1;j<=num[i];j++)
            scanf("%d%d",&w[i][j],&val[i][j]);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=v;j++)//前i组状态的初始状态直接继承前i-1组最优解
            dp[i][j]=dp[i-1][j];
        for(int k=1;k<=num[i];k++){//枚举第i组物品
            for(int j=v;j>=w[i][k];j--)//枚举背包容量 这里背包容量j 降序或升序皆可
                //每组物品只能在前i-1组物品dp[i-1][j-w[i][k]]基础上放入第i组中第k个物品
                dp[i][j]=max(dp[i][j],dp[i-1][j-w[i][k]]+val[i][k]);
        }
    }
    printf("%d",dp[n][v]);
    return 0;
}
*/

/*
//TLE 40分 dfs暴力枚举搜索+剪枝
//不加dp[i][j]对前i个状态剪枝,TLE只能得20分.
//时间复杂度O(max(num[i])^n)=O(100^100)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

//dp[k][j]代表考虑前k组每组最多拿一件物品在总体积为j时能获得的最大价值
int n,v,num[N],w[N][N],val[N][N],dp[N][M],ans;

//时间复杂度O(max(num[i])^n)=O(100^100)
void dfs(int k,int curV,int sum){
    if(curV>v)//当前所选物品体积大于背包容量
        return;
    //如果当前前k-1组所选物品在总体积为curV获得的价值不能比之前搜索在相同状态下的结果更优,就剪枝,不必再搜索下去
    //因为后面的阶段都是相同的搜索,而前面的子状态都不优,后面的状态自然不会更优.
    if(sum<=dp[k-1][curV])
        return;
    dp[k-1][curV]=sum;//更新前k-1组所选物品在总体积为curV获得的价值
    if(sum>ans)//记录最大价值
        ans=sum;
    if(k == n+1)//n组物品都考虑完
        return;
    //第k组内的物品只考虑放入其中的1件
    for(int i=1;i<=num[k];i++)
        dfs(k+1,curV+w[k][i],sum+val[k][i]);
    //第k组内的物品1件也不放入
    dfs(k+1,curV,sum);
}

int main(){
    ans=0;
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++){
        scanf("%d",&num[i]);
        for(int j=1;j<=num[i];j++)
            scanf("%d%d",&w[i][j],&val[i][j]);
    }
    memset(dp,0,sizeof(dp));
    //初始化前k组物品一个物品也不选时的值为-1,避免搜索直接结束退出
    for(int k=0;k<=n;k++)
        dp[k][0]=-1;
    dfs(1,0,0);
    printf("%d",ans);
    return 0;
}
*/
