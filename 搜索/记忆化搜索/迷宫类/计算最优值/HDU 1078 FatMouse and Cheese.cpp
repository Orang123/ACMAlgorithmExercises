/*
题意:给出n*n的网格,每个网格里面有一些奶酪,一只老鼠从(1,1)点出发,
可以水平或垂直朝一个方向最多走k步,并且每次走到的位置奶酪应该比当
前位置奶酪更多才行,问这只老鼠走到不能再走为止最多能吃的奶酪数量是多少.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1078
思路:dp[x][y]表示从(x,y)点出发走到不能再走的位置所能获取的最多的奶酪
记忆化搜索 递归地从目标状态(不能走的状态)向初始状态(1,1)转移,已经搜索
过的重叠子问题直接返回dp[x][y]这个结果就行.
之所以从终止状态回溯式地向初始状态逆推是因为终止状态已经停止了,不会继续搜索
下去,而如果从初始状态计算到达当前所走到状态的最优解,这里是会继续搜索下去的,
而且还无法保证当前先搜索到的就一定是最优解,最坏情况剪枝条件几乎不会触发.
这个记忆化数组dp的剪枝是从中止状态不断向初始状态靠近来剪枝的.
*/
//ac 62ms 记忆化搜索 递归地从目标状态(不能走的状态)向初始状态(1,1)转移
//dp[x][y]表示从(x,y)点出发走到不能再走的位置所能获取的最多的奶酪
//记忆化搜索决定已经搜索过的路径没必要重复搜索,剪枝对搜索的路径做出决策,不好的搜索路径应舍弃
//时间复杂度O(n*n)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,k,mp[N][N],dp[N][N],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

int dfs(int x,int y){
    if(dp[x][y])//因为是记忆化搜索,如果dp[x][y]不为0代表从这点开始所枚举的路径是被搜索过的,属于重叠子问题,不要去重复搜索,那就直接用之前所搜索的值就好
        return dp[x][y];
    int nx,ny,res=0;
    for(int i=1;i<=k;i++){//枚举每次所走的步长
        for(int j=0;j<4;j++){//枚举方向
            nx=x+dir[j][0]*i;
            ny=y+dir[j][1]*i;
            if(nx<1 || nx>n || ny<1 || ny>n)
                continue;
            if(mp[nx][ny]<=mp[x][y])
                continue;
            res=max(res,dfs(nx,ny));//类似dp中的状态转移方程，取max的决策方案
        }
    }
    return dp[x][y]=mp[x][y]+res;
}

int main(){
    while(scanf("%d%d",&n,&k) && (n!=-1 || k!=-1)){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        printf("%d\n",dfs(1,1));
    }
    return 0;
}

/*
//dfs暴力搜索 类背包dp阶段性剪枝 TLE 1000ms
//dp[x][y]表示从(1,1)出发到达(x,y)所能获得的最多奶酪
//剪枝1 如果当前从(1,1)出发获得奶酪不比之前获得的多 就不必再搜索下去
//这个做法超时的主要原因是这个剪枝的高效性无法保证,有可能最坏情况下,
//先搜索到的路径获取的奶酪数都比较小,整体还是搜索了很多重复的路径.
//而上面代码里的记忆化搜索 是从终止状态转移的,它能保证当前阶段已经记录的dp[x][y]一定是最优解,
//如果需要搜索(x,y),而dp[x][y]已经被计算,直接返回这个结果即可,是一个确切的剪枝.

//为啥一定要 从结束状态向初始状态推最优解主要原因是:
//如果从初始状态 推所走到状态的最优解,它这个 还是会往下继续搜索的,而且先搜索到的还不一定是最优,
//剪枝的高效性就无法保证,而终止状态去逆推,因为已经停下了,不能再往下继续搜索了,就不会重复搜索,
//而且它是保证了对于子阶段的状态已经就是最优的了,所以才更高效吧.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,k,mp[N][N],dp[N][N],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},ans;

void dfs(int x,int y,int sum){
    if(sum<=dp[x][y])//剪枝1 如果当前从(1,1)出发获得奶酪不比之前获得的多 就不必再搜索下去
        return;
    dp[x][y]=sum;
    ans=max(ans,sum);
    int nx,ny;
    for(int i=1;i<=k;i++){
        for(int j=0;j<4;j++){
            nx=x+dir[j][0]*i;
            ny=y+dir[j][1]*i;
            if(nx<1 || nx>n || ny<1 || ny>n)
                continue;
            if(mp[nx][ny]<=mp[x][y])
                continue;
            dfs(nx,ny,sum+mp[nx][ny]);
        }
    }
}

int main(){
    while(scanf("%d%d",&n,&k) && (n!=-1 || k!=-1)){
        memset(dp,0,sizeof(dp));
        ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        dfs(1,1,mp[1][1]);
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//bfs暴力搜索 类背包dp阶段性剪枝 MLE 390ms
//dp[x][y]表示从(1,1)出发到达(x,y)所能获得的最多奶酪
//MLE TLE的原因和dfs是一样的.
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
using namespace std;

int n,k,mp[N][N],dp[N][N],dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}},ans;
struct State{
    int x,y,sum;
    State(int x=0,int y=0,int sum=0):x(x),y(y),sum(sum){}
};

void bfs(){
    queue<State> Q;
    Q.push(State(1,1,mp[1][1]));
    dp[1][1]=mp[1][1];
    State tp;
    int nx,ny;
    while(!Q.empty()){
        tp=Q.front();
        ans=max(ans,tp.sum);
        Q.pop();
        for(int i=1;i<=k;i++){
            for(int j=0;j<4;j++){
                nx=tp.x+dir[j][0]*i;
                ny=tp.y+dir[j][1]*i;
                if(nx<1 || nx>n || ny<1 || ny>n)
                    continue;
                if(mp[nx][ny]<=mp[tp.x][tp.y])
                    continue;
                //剪枝1 如果当前从(1,1)出发获得奶酪不比之前获得的多 就不必再搜索下去
                if(tp.sum+mp[nx][ny]<=dp[nx][ny])
                    continue;
                Q.push(State(nx,ny,tp.sum+mp[nx][ny]));
            }
        }
    }
}

int main(){
    while(scanf("%d%d",&n,&k) && (n!=-1 || k!=-1)){
        memset(dp,0,sizeof(dp));
        ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        bfs();
        printf("%d\n",ans);
    }
    return 0;
}
*/
