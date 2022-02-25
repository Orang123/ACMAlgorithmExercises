/*
题意:一颗有n个节点的树,最少去掉多少条边可以孤立出节点数p的子树.
n<=150
链接:http://poj.org/problem?id=1947
思路:树上分组背包.背包容量为恰好含有的节点个数.
dp[u][j]=k代表以u为根节点的子树含有j个节点时最少需要删除k条边.
每个子树为一组,每组中的物品为当前子树包含多少节点最少要删除的边数.
初始状态是dp[u][1]=u节点所有直接邻接儿子个数 以u为根节点的子树,只保留了根节点u自己,
需要删除所有直接邻接的儿子连边.需要注意的是最终结果需要考虑每个节点为根节点的子树含有
p个节点时删除的边数,对于根节点不是dp时的节点,结果还要再删除当前根节点与本身的父节点的
连边.即:dp[i][p]+1(i!=rt),dp[i][p](i==rt).
虽然没有直接说明父子节点相互依赖,实际dp[u][j] 一定至少会保留u节点本身的基础上才能保留v节点.
*/
//ac 32ms
//复杂度 O(n*v^2) =150^3=3.375*10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 160
#define INF 0x3f3f3f3f
using namespace std;

//dp[u][j]=k代表以u为根节点的子树含有j个节点时最少需要删除k条边.
int cnt,head[N],vis[N],n,p,dp[N][N];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    int sum=1,m;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        //sum是以u为根节点的子树含有的所有节点个数(包括u自身)
        sum+=dfs(v);
        //背包容量是动态变化的,当子树节点个数不超过要求解的p时,上限为sum,超过时,上限是p,因为大于p的状态无需求解.
        m=sum<p?sum:p;
        for(int j=m;j>=2;j--){//背包容量上限是2,容量为1是初始状态 无需再转移
            for(int k=1;k<=j-1;k++)//子树的容量要小于j,因为现在是求解父节点u为根的子树含有j个节点的状态,u节点必须选上才能选子节点.
                //减1 是之前初始状态只保留u一个节点的dp[u][1]被减去v节点与u的连边要再加回来,实际减去边的个数-1
                //v节点子树保留k个节点,当前u节点保留j-k个节点
                //这个转移 对于含有k个节点的v子树来说,
                //如果v子树中含有分支较少,每个分支节点数较多,那实际需要删除的边数就较少
                //如果v子树中含有分支较多,每个分支节点数较少,那实际需要删除的边数就较多
                //状态转移方程决策的就是分支较少 分支节点数较多的子树作为较优解
                dp[u][j]=min(dp[u][j],dp[u][j-k]+dp[v][k]-1);
        }
    }
    return sum;
}

int main(){
    int u,v,rt;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&p);
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=n;i++)
        dp[i][1]=0;
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        dp[u][1]++;//初始状态u只保留u节点本身 要删边个数为直接邻接的所有儿子节点的个数.
        vis[v]=1;
    }
    //找根节点 入度为0
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            rt=i;
            break;
        }
    }
    dfs(rt);
    int ans=INF;
    for(int i=1;i<=n;i++){
        if(i!=rt)//不是dp时的根节点,则还得删去当前i点与父节点的连边才能将含有p个节点的子树分离出来
            ans=min(ans,dp[i][p]+1);
        else
            ans=min(ans,dp[i][p]);
    }
    printf("%d",ans);
    return 0;
}

/*
这种纯树形dp的树上问题,只能用O(n*v^2)的树上分组背包来做.
《浅谈几类背包问题》中O(nv)的后序次序01背包,那是严格的每个节点当做
一个物品,含有体积和价值的概念的,并且父子节点间存在着严格的依赖关系才行,
而这种类型的题目,每个节点并不能单独看做一个物品,并不具备物品体积和价值的
特征,只能说是背包类的树形dp吧.
*/

/*
//另一种转移,摘自博客:https://www.cnblogs.com/20143605--pcx/p/5348610.html
//题目分析：定义状态dp(root,k)表示在以root为根节点的子树中，删掉一些边变成恰有
//k个节点的新树需要删去的最少边数。对于根节点root的某个儿子son，要么将son及其所
//有的子节点全部删掉，则dp(root,k)=dp(root,k)+1，只需删除root与son之间的边；要么
//在son的子树中选出一些边删掉，构造出有j个节点的子树，状态转移方程为dp(root,k)=max(dp(root,k),dp(son,j)+dp(root,k-j))。

//dp[u][j]=min(dp[u][j],dp[v][k]+dp[u][j-k]);,不理解为什么每个j要先dp[u][j]++,
//貌似这个做法 刚开始的子状态 并不能直接求解出正确的结果,在dp[u][j]不但自增后,才能使得错误的状态结果正确
//ac 16ms
# include<iostream>
# include<cstdio>
# include<cstring>
# include<vector>
# include<algorithm>
using namespace std;

const int N=155;
const int INF=1000000000;

int n,m;
bool flag[N];
int dp[N][N];
vector<int>e[N];

void init()
{
    int a,b;
    for(int i=1;i<=n;++i){
        e[i].clear();
        for(int j=0;j<=m;++j)
            dp[i][j]=INF;
    }
    memset(flag,false,sizeof(flag));
    for(int i=1;i<n;++i){
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        flag[b]=true;
    }
}

void dfs(int u)
{
    dp[u][1]=0;
    for(int i=0;i<e[u].size();++i){
        int v=e[u][i];
        dfs(v);
        for(int j=m;j>=1;--j){
            dp[u][j]+=1;
            for(int k=1;k<j;++k){    ///k从1循环到j-1，一定不能从0循环到j
                dp[u][j]=min(dp[u][j],dp[v][k]+dp[u][j-k]);
            }
        }
    }
}

void solve()
{
    int ans=INF;
    for(int i=1;i<=n;++i){
        if(flag[i]) continue;
        dfs(i);
        ans=dp[i][m];
        break;
    }
    for(int i=1;i<=n;++i)
        ans=min(ans,dp[i][m]+1);
    printf("%d\n",ans);
}

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        init();
        solve();
    }
    return 0;
}
*/

/*
//另一种状态表示方式 摘自博客:https://www.cnblogs.com/cglongge/p/10308685.html
//基本能看懂,就是求结果是 要反过来,因为要得到m个,实际就删掉了n-m个子树中的节点需要的最少边数.
//dp[i][j]表示在i节点的子树里（不是以i组成的子树）去掉j个节点需要减少的最少的边数

//ac 16ms
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct{//链式前向星
    int v,next;
}edge[320];
int head[160];
int dp[160][160];//dp[i][j]表示在i节点的子树里（不是以i组成的子树）去掉j个节点需要减少的最少的边数
int sum[160];//sum[i]表示在i节点的子树里一个有多少个节点（不包括i）
int cnt;
void add(int u,int v){
    edge[cnt].v=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

//i节点的子树（不包括i）
//以i节点为根组成子树（树）（包括i）

int n,m;
void dfs(int k){
    sum[k]=0;//初始化
    for(int i=1;i<=n;i++)//初始化
    dp[k][i]=1e9;
    dp[k][0]=0;//无论是哪个点，去掉0个节点的花费一定是0
    for(int i=head[k];i!=-1;i=edge[i].next){
            dfs(edge[i].v);//先向子节点搜索
            sum[k]+=sum[edge[i].v]+1;//计算k节点的子树里有多少个节点
            dp[edge[i].v][sum[edge[i].v]+1]=1;//去除当前子节点为根组成树的所有的节点的花费一定是1（只需断开k与当前子节点的连接）
            //printf("%d %d %d\n",edge[i].v,sum[edge[i].v]+1,dp[edge[i].v][sum[edge[i].v]+1])    ;
            for(int j=n;j>0;j--){ //为什么要j>0,因为j=0的花费一定是0，没必要更新
                for(int l=1;l<=j;l++)
                dp[k][j]=min(dp[k][j],dp[k][j-l]+dp[edge[i].v][l]);
                //为什么l从1开始，因为从0开始没必要（min(dp[k][j],dp[k][j]+dp[edge[i].v][0]);）它的
                //结果一定是原来的dp[k][j],因为 dp[edge[i].v][0]=0，为什么l可以等于j，因为我可以当前的j个全部
                //从当前子节点组成的子树去除
            }
    }
}
bool vt[160];//标记数组
int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        int u,v;
        cnt=0;
        fill(head,head+152,false);//初始化
        fill(head,head+152,-1);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            add(u,v);
            vt[v]=true;
        }
        int root=0;
        for(int i=1;i<=n&&!root;i++){//找根节点
            if(!vt[i])
            root=i;
        }
        dfs(root);
        int ans=dp[root][n-m];//我要得到节点数为m的子树，需要去掉n-m个点
        for(int i=1;i<=n;i++)
        if(sum[i]+1>=m)//i节点 子树中必修至少要有m个节点才行
        ans=min(ans,dp[i][sum[i]+1-m]+1);//取以第i个节点为根节点组成的子树（包括i）时，先要减去他与父节点的连接，
        //然后再到子树里减去sum[i]+1-m个节点（因为以i为根组成的子树（树）只有sum[i]+1个节点）
        printf("%d\n",ans);
    }

    return 0;
}
*/

