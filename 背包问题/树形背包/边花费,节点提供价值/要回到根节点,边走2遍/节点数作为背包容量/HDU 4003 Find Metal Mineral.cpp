/*
题意:一棵n个节点的树,节点编号为1~n,每条边都有一个花费值w.
有k个机器人从S点出发,求所有机器人走完所有节点的最小花费.
1<=n<=10000,1<=k<=10,1<=w<=10000.
此题是POJ 1849的加强版,POJ 1849是2个人从s点出发要遍历所有边,
此题是遍历所有点,都会有边重复走.
The 36th ACM/ICPC Asia Regional Dalian Site —— Online Contest
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4003
思路:树上分组背包.
dp[i][j]表示以i为根节点的子树,分配j个机器人不回到i点所需的最小花费,这j个机器人都是一直遍历
到i节点子树的各个叶子节点才停止的,不会往回走.
要注意的是j=0时,即dp[i][0]代表分配一个机器人走完i子树的所有节点又回到i点的最小花费.
只考虑一个机器人回来的原因是同时派多个机器人下去,如果回来的人越多,走重复路线会越多.耗费越多.
背包容量为固定的k个机器人,因为有可能机器人个数大于节点个数,实际并用不了那么多机器人,但是输出
的时候还是输出k个机器人的状态,所以是尽可能多地装满背包.因此初始化必须是全0,dp[u][j]的初始状态
需要设定为dp[u][j]+=dp[v][0]+edge[i].w*2,最大值是子树全部由一个机器人将所有边遍历2遍回到u节点时.

很明显不能以花费为背包容量,M=nw=10^8 NM=10^13 会MLE TLE.

*/
//ac 280ms
//dp[u][j]=min(dp[u][j],dp[u][j-t]+dp[v][t]+t*edge[i].w);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
#define M 11
using namespace std;

int cnt,head[N],n,s,k,dp[N][M];

struct Edge{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        //这里当前子树分支的可分配的机器人上限并不是u节点分支个数,因为可能u节点只有一个分支,但子树下面的分支数可能很多 这样会wa
        //所以容量上限固定为k
        for(int j=k;j>=0;j--){
            //dp[u][j]的初始状态为所有子树的边都只由一个机器人遍历2遍回到u节点的花费,这是最大值
            dp[u][j]+=dp[v][0]+edge[i].w*2;
            for(int t=1;t<=j;t++)
                //v子树分配t个机器人一直遍历到子树的叶子节点停止,因此当前边有t个机器人都走了一次
                //所以花费为dp[v][t]+t*edge[i].w
                //状态转移的较优决策是
                //1.子树分支较多,每个分支链长较长,此时应多分配机器人,避免一个机器人往回走重复的长链路线,这样花费较大
                //2.子树分支较少,每个分支链长较短,此时应尽量少分配机器人,因为一个机器人往回走遍历各个分支(较短链)的花费并不会很大
                //对于v子树中分配机器人比节点分支数少时,dp[v][k]里必然有部分机器人是由dp[v'][0]转移而来,必然有机器人是走到叶子节点后,
                //还会往回走,能够保证分配的k个机器人能将v子树得到所有节点都遍历,只是有可能个别机器人走完自己的分支会回过头再走别的分支,
                //这个转移对于机器人个数不够的必然包含了dp[u][0]的重复走的2遍路径花费.
                //dp[u][j-t] j-t可能大于之前遍历的子树最多分支数,但因为初始化全0,并不影响结果,是尽可能多地装满背包
                //机器人可能有剩余
                dp[u][j]=min(dp[u][j],dp[u][j-t]+dp[v][t]+t*edge[i].w);
        }
    }
}

int main(){
    int u,v,w;
    while(scanf("%d%d%d",&n,&s,&k)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        //k可能大于总节点数,输出结果还是会输出dp[s][k],所以初始化全0,实际可能用不了那么多机器人
        //尽可能多地装满背包 这样结果直接输出dp[s][k]就是对的
        memset(dp,0,sizeof(dp));
        dfs(s,-1);
        printf("%d\n",dp[s][k]);
    }
    return 0;
}

/*
//ac 296ms 另一种状态表示法
//dp[i][j]表示i为根节点的子树用j个机器人最多可以少走的路径的花费.
//dp[u][j]=max(dp[u][j],dp[u][j-t]+dp[v][t]+2*edge[i].w-t*edge[i].w);
//sum*2-dp[s][k]
//下述理解摘自:https://blog.csdn.net/shuangde800/article/details/10217167
//如果从根节点出发,遍历所有节点之后再回到原点, 那么最少的花费一定是所有边的权值之和sum的两倍, 因为每条边都走了两次.
//而这题,遍历完之后,并不需要走回出发点,所以,有些边只走了一次就可以了,
//如果用1台机器人走,最少的的花费 = sum * 2 - {根节点到叶子节点路径的最大权值和}
//如果是j台机器走, 我们要让j台机器人只走一次的边的权值之和尽量大, 也就是减少的花费尽量大.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
#define M 11
using namespace std;

int cnt,head[N],n,s,k,dp[N][M],sum;

struct Edge{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        for(int j=k;j>=1;j--){
            for(int t=1;t<=j;t++)//这里分配给子树至少要一个机器人,如果是0的话,转移是求max最大花费,这样最终的dp[s][k]就等于sum*2了
                //dp[v][t]v子树分配t个机器人走到叶子节点不回来,当前边edge[i].w 有t个机器人共走了t次
                //实际可以减少走的花费就是2*edge[i].w-t*edge[i].w
                dp[u][j]=max(dp[u][j],dp[u][j-t]+dp[v][t]+2*edge[i].w-t*edge[i].w);
        }
    }
}

int main(){
    int u,v,w;
    while(scanf("%d%d%d",&n,&s,&k)!=EOF){
        sum=cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            sum+=w;
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        memset(dp,0,sizeof(dp));
        dfs(s,-1);
        printf("%d\n",sum*2-dp[s][k]);
    }
    return 0;
}
*/

/*
//ac 405ms 暴力做法 O(nk)=10^5
//这个做法来自另一道题 POJ 1849
//摘自博客:https://blog.csdn.net/this_poet/article/details/6767363
//https://www.cnblogs.com/AOQNRMGYXLMV/p/4691931.html
就是每次从起点出发找到一条最长的路径，记录下路径的长度，然后把这条路径上边的权值变为相反数。
注意，已经变为负权的边就不再变回去了。这样找K次最长的路径，然后加起来就是可以最多少走多少路。
为什么要把权值变成负的，因为你第二次第三次再走这条路的时候，就表示少走了负的权值，也就是多走了。
如果出现所有的路都是负权的情况，那么树中最长路的路径就是0，也就是机器人原地不动。
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 10000 + 10;

struct Edge
{
     int u, v, w;
     Edge(int u, int v, int w):u(u), v(v), w(w) {}
 };

 vector<Edge> edges;
 vector<int> G[maxn];

 void AddEdge(int u, int v, int w)
 {
     edges.push_back(Edge(u, v, w));
     edges.push_back(Edge(v, u, w));
     int m = edges.size();
     G[u].push_back(m - 2);
     G[v].push_back(m - 1);
 }

 int n, s, k;

 int len, id;
 int pre[maxn];

 void dfs(int u, int fa, int d)
 {
     if(d > len) { len = d; id = u; }
    for(int i = 0; i < G[u].size(); i++)
     {
         Edge& e = edges[G[u][i]];
         int v = e.v;
         if(v == fa) continue;
         pre[v] = G[u][i];
         dfs(v, u, d + e.w);
     }
 }

 int main()
 {
     while(scanf("%d%d%d", &n, &s, &k) == 3)
     {
         edges.clear();
         int tot = 0;
         for(int i = 1; i <= n; i++) G[i].clear();
         for(int i = 1; i < n; i++)
         {
             int u, v, w; scanf("%d%d%d", &u, &v, &w);
             tot += w;
             AddEdge(u, v, w);
         }
         tot <<= 1;

         int ans = 0;
         for(int i = 0; i < k; i++)
         {
             len = 0, id = s;
            pre[s] = -1;
             dfs(s, 0, 0);
             if(id == s) continue;
             ans += len;
             for(int u = id; u != s; u = edges[pre[u]].u)
             {
                 int& w = edges[pre[u]].w;
                 if(w > 0) w = -w;
             }
         }

         printf("%d\n", tot - ans);
     }

     return 0;
 }
*/
