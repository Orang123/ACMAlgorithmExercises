/*
题意:摘自网上
有4堆糖果，每一堆有n个糖果，有一个篮子，这个篮子的最大容量为5块糖，
每一次从这四堆中选择一堆，然后将最上面的糖果拿下来，放到篮子里面去，
如果有相同两块糖的就把这；两块糖拿出来，如果达到了5块糖，并且这5块糖
是两两不相同的就结束游戏，问你，最多能拿出多少对糖.
n<=40.糖的颜色编号在[1,20]
链接:https://www.luogu.com.cn/problem/UVA10118
思路:因为每次是从4堆糖的最上面开始拿,那就枚举拿的可能性,定义4堆糖的
一个顶部下标,当拿到n个时就结束,只是在枚举的过程中对于4堆糖当前已拿
的每堆糖的顶部 是有可能重复搜素的,因此需要记忆化搜索对重叠子问题进行判重.
dp[top[1]][top[2]][top[3]][top[4]]表示当前4堆糖顶部分别拿了top[1]、top[2]
、top[3]、top[4]个后剩余的4堆糖中能从篮子里拿出相同的一对的最多的对数.
注意对于0也是搜索的结果,因此dp初始化为-1,并且结束条件不一定能刚好拿完5个,
可能本身总共就只有4个糖果,因此dp搜索时的初始值赋为0.
*/
//ac 80ms 记忆化搜索
//dp[top[1]][top[2]][top[3]][top[4]]表示当前4堆糖顶部分别拿了top[1]、top[2]
//、top[3]、top[4]个后剩余的4堆糖中能从篮子里拿出相同的一对的最多的对数.
//因为每堆最多有40个,用41进制数表示状态 数值比dp[top[1]][top[2]][top[3]][top[4]]要大点
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
using namespace std;

int n,dp[N][N][N][N],a[5][N],top[5],vis[21];

int dfs(int k){
    int &res=dp[top[1]][top[2]][top[3]][top[4]];
    if(res!=-1)
        return res;
    if(k == 5)
        return res=0;
    res=0;
    for(int i=1;i<=4;i++){
        if(top[i] == n)
            continue;
        top[i]++;
        if(!vis[a[i][top[i]]]){//当前第i堆糖果第top[i]个 还未拿
            vis[a[i][top[i]]]=1;
            res=max(res,dfs(k+1));//当前篮子里的糖果数+1
            vis[a[i][top[i]]]=0;
        }
        //当前第i堆糖果第top[i]个颜色为a[i][top[i]]的糖果篮子里已经有一个了,在放入一个 刚好凑成一对,
        //可以将其拿出来,篮子里剩余糖果数就减1,拿出来糖果对数+1
        else{
            vis[a[i][top[i]]]=0;
            res=max(res,dfs(k-1)+1);
            vis[a[i][top[i]]]=1;
        }
        top[i]--;
    }
    return res;
}

int main(){
    while(scanf("%d",&n) && n){
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=4;j++)
                scanf("%d",&a[j][i]);
        }
        printf("%d\n",dfs(0));
    }
    return 0;
}

/*
//ac 80ms 记忆化搜索+状压
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
using namespace std;

int n,dp[N][N][N][N],a[5][N],top[5];

//篮子里放置的永远是只有一个颜色的糖果,当出现相同颜色的时候会把原先的立马取出
int dfs(int sta,int k){
    int &res=dp[top[1]][top[2]][top[3]][top[4]];
    if(res!=-1)
        return res;
    if(k == 5)
        return res=0;
    res=0;
    for(int i=1;i<=4;i++){
        if(top[i] == n)
            continue;
        top[i]++;
        int tp=1<<a[i][top[i]]-1;
        if(sta & tp)
            res=max(res,dfs(sta^tp,k-1)+1);//按位异或 抵消掉a[i][top[i]]颜色的糖果
        else
            res=max(res,dfs(sta|tp,k+1));//按位或 将a[i][top[i]]颜色的糖果二进制位加入
        top[i]--;
    }
    return res;
}

int main(){
    while(scanf("%d",&n) && n){
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=4;j++)
                scanf("%d",&a[j][i]);
        }
        printf("%d\n",dfs(0,0));
    }
    return 0;
}
*/
