/*
题意:有一个电视台广播节目,广播的网络用n个节点一棵树表示,m个用户节点(编号n-m+1~n),
n-m个中继器节点(编号1~n-m)节点1表示电台(根节点),叶子结点表示用户,用户愿意付一定的
钱去收看这个节目,从非叶子结点到其他结点需要一定的费用(即从中继点到另一个中继点需要
一些钱),问最后在不亏本的情况下(用户交钱总额>=传输路径总费用),最多能使多少人收看到节目.
信号从电台节点1发出,发出点会影响实际结果.
n,m<=3000
同洛谷P1273 有线电视网
链接:http://poj.org/problem?id=1155
思路:树上分组背包.背包容量为m(所有m个用户收看到节目).恰好装满背包.
dp[i][j]=k表示以i为根节点的子树网络使得j个人可以收看节目实际获得的最大利润.
k>=0时,表示使得j个人收看到节目是合法的;
k<=0时,表示i为根节点的子树网路不能使得j个人收看节目,是不成立的.
初始状态dp[n-m+1..n][1]=money[n-m+1..n](用户所付观看节目费用).
dp[1..n-m][0]=0,代表初始中继器没有发送信号使得任何一个用户收看节目 实际花费为0.
状态转移方程为dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]-edge[i].w);
随着不断向父节点转移,转发信号的路径费用再不断增大,实际获得利润在不断减少,求解出
dp[u][j]状态下所能保留的最大利润,这样才能有更多利润将信号转发到别的子树节点使得
更多用户收到信号.

因为传输信号,要传给子节点 必须先传给父节点,有子父节点间的依赖关系.

注意:不能将路径花费作为背包容量,因为叶子节点获取的利润会使得花费减少,这个容量是动态变化的,
不好写状态转移方程,需要判断叶子节点是叶子节点的话 会使得实际的容量花费减少,而且题目也没给出
花费数值,可能很大吧,应该也开不出来MLE.
*/
//ac 204ms 这n<=3000 实际O(n^3)复杂度肯定会炸,数据较弱
//dp[i][j]=k表示以i为根节点的子树网络使得j个人可以收看节目实际获得的最大利润.
//dfs不优化当前子树背包容量会TLE,优化为:当前子树背包容量应该为子树中叶子总数.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 3100
using namespace std;

int cnt,head[N],n,m,dp[N][N];

struct Edge{
    int to,next,w;
}edge[N];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

int dfs(int u){
    int sum=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        sum+=dfs(v);
        //背包容量上界为sum表示当前u节点子树中已经遍历到的叶子节点(用户)的个数
        //直接以m作为背包容量为TLE
        for(int j=sum;j>=1;j--){
            //v子树节点中 用户个数至少为1,不可能为0,为0就没有转移的意义了
            for(int k=1;k<=j;k++)
                //这个转移 对于含有k个叶子节点的v子树来说,
                //如果v子树中含有分支较少,每个分支节点数较多,那么路径花费就较大,那实际能获得的利润就较少
                //如果v子树中含有分支较多,每个分支节点数较少,那么路径花费就较小,那实际能获得的利润就较多
                //状态转移方程决策的就是分支较多 分支节点数较少的子树作为较优解
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]-edge[i].w);
        }
    }
    if(head[u] == -1)//叶子节点 返回1
        return 1;
    else//非叶子节点返回当前sum
        return sum;
}

int main(){
    int num,w,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-m;i++){
        scanf("%d",&num);
        while(num--){
            scanf("%d%d",&v,&w);
            addEdge(i,v,w);
        }
    }
    //恰好装满背包
    memset(dp,-0x3f,sizeof(dp));
    //注意除过叶子节点外,其余点并不是用户因此初始状态只有dp[i][0]是合法的
    //虽然从1点发出信号经过了父节点 但背包容量只统计的是叶子节点的个数
    for(int i=1;i<=n-m;i++)
        dp[i][0]=0;
    for(int i=n-m+1;i<=n;i++)//用户收到信号可以支付的费用 作为叶子节点的初始状态
        scanf("%d",&dp[i][1]);
    dfs(1);
    for(int i=m;i>=0;i--){//降序 只要dp[1][i]>=0 即是合法状态
        if(dp[1][i]>=0){
            printf("%d",i);
            break;
        }
    }
    return 0;
}

/*
《浅谈几类背包问题》中O(nv)dfs后序次序01背包的做法这里并不适用.
没有严格的父子节点间的依赖关系,每个节点没有明确的体积、价值的概念
此题的转移中主要用到的是路径边权.
*/

/*
//ac 266ms 另一种转移方程
//dp[i][j]=k表示以i为根节点的子树网络使得j个人可以收看节目实际获得的最大利润.
//dp[u][j+k]=max(dp[u][j+k],dp[u][j]+dp[v][k]-edge[i].w);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 3100
using namespace std;

int cnt,head[N],n,m,siz[N],dp[N][N],val[N];

struct Edge{
    int to,next,w;
}edge[N];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u){
    int sum=0;
    //非叶子节点 即使经过也不能算作用户节点
    dp[u][0]=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        dfs(v);
        //注意这里j的下界是0,因为刚开始初始状态只能从一个叶子节点开始转移,父节点并不算作用户
        for(int j=siz[u];j>=0;j--){
            for(int k=1;k<=siz[v];k++)
                dp[u][j+k]=max(dp[u][j+k],dp[u][j]+dp[v][k]-edge[i].w);
        }
        siz[u]+=siz[v];
    }
    if(head[u] == -1){
    	siz[u]=1;
    	//初始状态
    	dp[u][1]=val[u];//只有叶子节点才是用户 才能提供利润
	}
}

int main(){
    int num,w,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-m;i++){
        scanf("%d",&num);
        while(num--){
            scanf("%d%d",&v,&w);
            addEdge(i,v,w);
        }
    }
    memset(siz,0,sizeof(siz));
    memset(dp,-0x3f,sizeof(dp));
    for(int i=n-m+1;i<=n;i++)//用户收到信号可以支付的费用 作为叶子节点的初始状态
        scanf("%d",&val[i]);
    dfs(1);
    for(int i=m;i>=0;i--){//降序 只要dp[1][i]>=0 即是合法状态
        if(dp[1][i]>=0){
            printf("%d",i);
            break;
        }
    }
    return 0;
}
*/
