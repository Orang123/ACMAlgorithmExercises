/*
题意:摘自网上
分别表示有n种硬币,给定一个数s,对于每一种硬币有两个价值,
分别记做x[i],y[i],要求从中选择一些硬币,使得满足s*s=X*X+Y*Y,
其中X是选出的硬币的所有x价值的和,Y是所有选出的硬币的y价值的和,
硬币有无数多个,现在要求的是,满足上述要求使用的最少的硬币数.
链接:https://www.luogu.com.cn/problem/UVA10306
思路:每种硬币可以选用多次,每个硬币都有两种属性,二维费用完全背包.
dp[k][i][j]代表前k种硬币构成的x属性之和为i,y属性之和为j所选用的最少硬币数.
注意x价值和y价值之和的上限是s.因为超过s后,平方肯定比s的平方大,就没意义了.
*/
//ac 0ms
//dp[i][j]=min(dp[i][j],dp[i-x[k]][j-y[k]]+1);
//dp[k][i][j]代表前k种硬币构成的x属性之和为i,y属性之和为j所选用的最少硬币数.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 310
#define INF 0x3f3f3f3f
using namespace std;

int n,s,x[N],y[N],dp[M][M];

int main(){
    int T,ans;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d",&n,&s);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&x[i],&y[i]);
        dp[0][0]=0;
        for(int k=1;k<=n;k++){
            for(int i=x[k];i<=s;i++){
                for(int j=y[k];j<=s;j++){
                    if(dp[i-x[k]][j-y[k]]!=INF){
                        dp[i][j]=min(dp[i][j],dp[i-x[k]][j-y[k]]+1);
                        if(i*i+j*j == s*s)//每种满足情况的解 求最小硬币数
                            ans=min(ans,dp[i][j]);
                    }
                }
            }
        }
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("not possible\n");
    }
    return 0;
}

/*
//ac 0ms
//dp[i+x[k]][j+y[k]]=min(dp[i+x[k]][j+y[k]],dp[i][j]+1);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 310
#define INF 0x3f3f3f3f
using namespace std;

int n,s,x[N],y[N],dp[M][M];

int main(){
    int T,ans;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d",&n,&s);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&x[i],&y[i]);
        dp[0][0]=0;
        for(int k=1;k<=n;k++){
            for(int i=0;i+x[k]<=s;i++){
                for(int j=0;j+y[k]<=s;j++){
                    if(dp[i][j]!=INF){
                        dp[i+x[k]][j+y[k]]=min(dp[i+x[k]][j+y[k]],dp[i][j]+1);
                        if((i+x[k])*(i+x[k])+(j+y[k])*(j+y[k]) == s*s)//每种满足情况的解 求最小硬币数
                            ans=min(ans,dp[i+x[k]][j+y[k]]);
                    }
                }
            }
        }
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("not possible\n");
    }
    return 0;
}
*/

/*
//ac 200ms 暴力枚举dfs搜索 数据比较弱吧 n<=40
//O(n^(s/min(x[i]))
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 310
#define INF 0x3f3f3f3f
using namespace std;

//dp[i][j]=k 代表x价值之和为i,y价值之和为j时最少使用了k个硬币
int n,s,x[N],y[N],dp[M][M],ans;

//O(n^(s/min(x[i]))
void dfs(int sumx,int sumy,int num){
    //剪枝1:x价值之和 和 y价值之和都不能超过s,否则等式sumx*sumx+sumy*sumy == s*s就不成立
    if(sumx>s || sumy>s)
        return;
    //剪枝2:如果当前所选硬币x价值之和为sumx,y价值之和为sumy时,
    //所使用的硬币数不能比之前记录同等相同下的硬币数小,就没必要再搜索下去
    if(num>=dp[sumx][sumy])//也可以理解为记忆化搜索,实质类似dp的状态转移方程的子问题的最优决策
        return;
    dp[sumx][sumy]=num;
    if(sumx*sumx+sumy*sumy == s*s)
        ans=min(ans,num);
    for(int i=1;i<=n;i++)
        dfs(sumx+x[i],sumy+y[i],num+1);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d",&n,&s);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&x[i],&y[i]);
        dfs(0,0,0);
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("not possible\n");
    }
    return 0;
}
*/

/*
//ac 0ms bfs广度搜索枚举状态+剪枝
//bfs也基本是类似的,剪枝和这个是相同的,如果当前状态不能比之前的更优就不入队
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 50
#define M 310
#define INF 0x3f3f3f3f
using namespace std;

//dp[i][j]=k 代表x价值之和为i,y价值之和为j时最少使用了k个硬币
int n,s,x[N],y[N],dp[M][M],ans;
struct State{
    int sumx,sumy,num;
    //构造器初始化是根据:sumy(x),num(num),sumx(y)初始化而的,State(int ..)里的形参可以随意命名
    //但需保证实际构造的各项参数和sumx,sumy,num相互匹配
    State(int y=0,int x=0,int num=0):sumy(x),num(num),sumx(y){}
};

void bfs(){
    queue<State> Q;
    Q.push(State(0,0,0));
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        if(tp.sumx*tp.sumx+tp.sumy*tp.sumy == s*s)
            ans=min(ans,tp.num);
        Q.pop();
        for(int i=1;i<=n;i++){
            if(tp.sumx+x[i]>s || tp.sumy+y[i]>s)
                continue;
            if(tp.num+1>=dp[tp.sumx+x[i]][tp.sumy+y[i]])//不加这个剪枝会TLE
                continue;
            Q.push(State(tp.sumx+x[i],tp.sumy+y[i],tp.num+1));
            dp[tp.sumx+x[i]][tp.sumy+y[i]]=tp.num+1;
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d",&n,&s);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&x[i],&y[i]);
        bfs();
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("not possible\n");
    }
    return 0;
}
*/
