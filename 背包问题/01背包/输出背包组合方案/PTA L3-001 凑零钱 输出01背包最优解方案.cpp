#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 110
using namespace std;
//ac 16ms 01背包输出最优组合方案 尽可能多地装满
/*
题意:韩梅梅喜欢满宇宙到处逛街.现在她逛到了一家火星店里,
发现这家店有个特别的规矩:你可以用任何星球的硬币付钱,但是
绝不找零,当然也不能欠债.韩梅梅手边有10^4枚来自各个星球的硬币,
需要请你帮她盘算一下,是否可能精确凑出要付的款额v.如果有多个最优解,
就按照硬币面值的字典序升序输出硬币面值的组合方案.若不存在能凑出v的
硬币组合方案,则输出"No Solution".
链接:https://pintia.cn/problem-sets/994805046380707840/problems/994805054207279104
思路:可以用vis[i][j]标记在背包容量为j时,放入第i个物品,因为要输出面值字典序最小
的组合,所以先降序排序,越到后面的硬币面值越小,之后从vis[n][m]模拟实际dp的过程逆序
输出即可.
*/
//vis[i][j]=1代表背包容量为j时,最优解放入了第i个物品
//vis[i][j]=0代表背包容量为j时,最优解没有放入了第i个物品
//注意这里vis[i][j]只是单纯地表示第i个物品在背包容量j时最优解情况是否装入,不能代表实际的递推关系
int n,v,val[N],dp[M],vis[N][M];

bool cmp(int a,int b){
    return a>b;
}

int main(){
    memset(dp,0,sizeof(dp));//尽可能装满背包,初始化为0
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    sort(val+1,val+1+n,cmp);
    for(int i=1;i<=n;i++){
        for(int j=v;j>=val[i];j--){
            if(dp[j]<=dp[j-val[i]]+val[i]){//如果选后面硬币面值和与相面硬币组合相等,优先考虑选后面面值小的,注意这里是"<="
                dp[j]=dp[j-val[i]]+val[i];
                vis[i][j]=1;//标记背包容量为j时,最优解的面值和中最后放入的是第i个硬币
            }
        }
    }
    if(dp[v]!=v)//只有当恰好能凑齐面值为v的硬币时 才有解 这里是尽可能多地装满背包
        printf("No Solution");
    else{//输出最优解的硬币组合方案 按面值从小到大输出
        int i=n,j=v;
        //因为是恰好装满,所以结束条件一定是背包容量为0 因为dp[j]等于j,而dp[v]!=v时,
        //起始点的dp[j]并不等于0,因为此时已经是前n个物品的状态了,只有前0个物品dp[j]才是0
        while(j){
            if(vis[i][j]){//j容量下,有放入第i个硬币
                j-=val[i];//背包容量减少,因为不同背包容量下 最优解的方案不同,这里要不断骤减求出在最大容量v下的最优解
                if(j)
                    printf("%d ",val[i]);
                else//j == 0是最后一个面值最大的硬币
                    printf("%d",val[i]);
            }
            i--;
        }
    }
    return 0;
}

/*
//ac 8ms 01背包输出最优组合方案 背包容量恰好装满
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 110
using namespace std;

int n,v,val[N],dp[M],vis[N][M];

bool cmp(int a,int b){
    return a>b;
}

int main(){
    memset(dp,-0x3f,sizeof(dp));//背包容量恰好装满
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    sort(val+1,val+1+n,cmp);
    dp[0]=0;//初始状态是0
    for(int i=1;i<=n;i++){
        for(int j=v;j>=val[i];j--){
            if(dp[j]<=dp[j-val[i]]+val[i]){
                dp[j]=dp[j-val[i]]+val[i];
                vis[i][j]=1;
            }
        }
    }
    if(dp[v]<0)//因为是恰好装满只需判断 容量为v是否合法
        printf("No Solution");
    else{
        int i=n,j=v;
        while(j){
            if(vis[i][j]){
                j-=val[i];
                if(j)
                    printf("%d ",val[i]);
                else
                    printf("%d",val[i]);
            }
            i--;
        }
    }
    return 0;
}
*/

/*
不能用递归输出方案,因为dp[i][j] == dp[i-1][j] 在j不能全部装下前i个或前i-1个物品,时它会认为没有选择第i个物品,
而实际字典序方案 可能是选择了第i个的物品的,所以递归无法输出字典序方案,只能说是能输出其中一种方案.
具体到字典序还是需要vis[i][j]数组标记做判断
*/
