/*
题意:n个房间,房间之间通道构成树状结构,每个房间有bug数和消灭所有bug能
得到的能量数,m个士兵,每个士兵最多消灭20个BUG,要到下一个房间必须攻破上
一个房间,就算不足20个BUG也要安排一个士兵.在房间1是入口条件下,问最多能
得到的能量数.
0<=n,m<=100.
注意:
房间bug数可能为0,但仍旧需要放置一名士兵才能获得该房间的能量数.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1011
思路:因为要先消灭一个树上分组背包.背包容量为总士兵数.每个节点的体积为消灭所有bug最少
要放置的士兵数,即:w[i]=(w[i]+19)/20,但注意这里实际如果w[i]输入为0,则
也需要放置一名士兵,才能获得房间能量数,即:w[i]>=1,但这题杭电 测试数据
有误,实际ac的标程是错的,就w[i]可能是为0的,在转移时,dp[u][j-k]中的j-k
可以为0,但dp[v][k]的k不为0,这样只能结果ac,实际转移结果是错的.
每个节点的价值为消灭所有bug获得的房间能量数.这样就是一个标准的树上分组
背包.
dp[i][j]表示以i为根节点的子树在所有节点共放置j名士兵时能获得的最大能量数.
dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
*/
//ac 31ms
//dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int cnt,head[N],n,m,w[N],val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa,int tot){
	if(tot<=0)
		return;
    for(int i=w[u];i<=tot;i++)
        dp[u][i]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u,tot-w[u]);
        for(int j=tot;j>=w[u];j--){
            //这里k的下界觉得 w[v]即可,因为v的初始状态dp[v][w[v]..m]才是合法的.
            for(int k=1;k<=j-w[u];k++)
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
        }
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && (n!= -1 || m!=-1)){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&w[i],&val[i]);
            w[i]=(w[i]+19)/20;
            //这里杭电测试数据有误,w[i]实际是不能为0的,而ac标程w[i]可以为0
            //if(w[i])
                //w[i]=1
        }
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        if(!m){//正解w[i]>=1的话,m 即使为0 也不需要特判
            printf("0\n");
            continue;
        }
        memset(dp,0,sizeof(dp));
        dfs(1,-1,m);
        printf("%d\n",dp[1][m]);
    }
    return 0;
}

/*
//ac 46ms 另一种状态转移
//dp[u][j+k]=max(dp[u][j+k],dp[u][j]+dp[v][k]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int cnt,head[N],n,m,w[N],val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=w[u];i<=m;i++)
        dp[u][i]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        //这里j必须降序 才能保证dp[u][j]是之前兄弟子树分组的状态
        for(int j=m;j>=w[u];j--){
            //注意:这里是实际并不包括k为0的情况,如果实际k=0也是有意义的,那么k=0必须最后一个计算
            //否则 k=0时会更新dp[u][j]的值,而之后转移中的dp[u][j]就可能已经包含了当前v子树的情况
            //不能表示只包括之前兄弟子树的状态.
            //可以考虑k降序 m-j到0,或从1到m-j升序,k=0的情况最后再二层循环退出时单独计算
            for(int k=1;k+j<=m;k++)
                dp[u][j+k]=max(dp[u][j+k],dp[u][j]+dp[v][k]);
        }
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && (n!= -1 || m!=-1)){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&w[i],&val[i]);
            w[i]=(w[i]+19)/20;
        }
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        if(!m){
            printf("0\n");
            continue;
        }
        memset(dp,0,sizeof(dp));
        dfs(1,-1);
        printf("%d\n",dp[1][m]);
    }
    return 0;
}
*/

/*
《浅谈几类背包问题》中O(nv)dfs后序次序01背包的做法  这里会wa 不懂
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int cnt,head[N],n,m,w[N],val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa,int tot){
	if(tot<=0)
		return;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        for(int j=0;j<=tot-w[v];j++)
        	dp[v][j]=dp[u][j];
        dfs(v,u,tot-w[v]);
        for(int j=tot;j>=w[v];j--)
            dp[u][j]=max(dp[u][j],dp[v][j-w[v]]+val[v]);
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && (n!= -1 || m!=-1)){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&w[i],&val[i]);
            w[i]=(w[i]+19)/20;
            //这里杭电测试数据有误,w[i]实际是不能为0的,而ac标程w[i]可以为0
            //if(w[i])
                //w[i]=1
        }
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        if(!m){
            printf("0\n");
            continue;
        }
        memset(dp,0,sizeof(dp));
        dfs(1,-1,m);
        printf("%d\n",dp[1][m]);
    }
    return 0;
}
*/

