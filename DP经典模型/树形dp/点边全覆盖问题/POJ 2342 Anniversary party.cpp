#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
//ac 16ms 树形dp 遍历一棵树,直接在每个节点枚举2个状态的正向dp形式
/*
题意:学校举行校庆,邀请员工来参加聚会,每个人来都有自己的快乐度,可是每个员工都不能和自己的上司
同时在场,问来参加聚会的人最大快乐度总和是多少.
链接:http://poj.org/problem?id=2342
思路:dp[i][0] dp[i][1]分别代表员工i不来和来所能累加的最大快乐度.
此题就是树上带权最大独立集.但是不能用二分图里的最大独立集=顶点数-最大匹配来解,
首先时间上N<=6000,而匈牙利O(VE)肯定超时,再一个二分图中的最大独立集只能处理数量上的
最大,无法处理点权和上的最大,因为首先最大匹配方案是不唯一的,最小顶点覆盖也就不唯一,
那么最大独立集自然也不唯一,真正处理起来还需枚举所有可能情况的最大独立集比较求最大值,
很麻烦,但这题已经是一个树了,就可以应用树形dpO(V+E)去解决.
*/
struct _edge{
    int to,next;
}edge[6005];
int x[6005],dp[6005][2],head[6005],father[6005];

void dfs(int root){
    int son;
    for(int i=head[root];i!=-1;i=edge[i].next){
        son=edge[i].to;
        dfs(son);
        //枚举父节点是否来参加聚会
        //如果上司不来,如果下级的儿子的快乐度更大,那么下级不来快乐度就是最大,如果下级儿子快乐度比下级小很多,那么下级来总快乐度才会更大
        dp[root][0]+=max(dp[son][0],dp[son][1]);//若不来，则取子节点来或不来欢乐度的最大值,因为是多叉树，这里是+=
        dp[root][1]+=dp[son][0];//若来 子节点必不来
    }
}

int main(){
    int N,a,b,root;
    scanf("%d",&N);
    memset(head,-1,sizeof(head));
    memset(father,-1,sizeof(father));
    for(int i=1;i<=N;i++){
        scanf("%d",&x[i]);
        dp[i][0]=0;//父节点为i不来
        dp[i][1]=x[i];//父节点为i来
    }
    for(int i=0;i<N-1;i++){
        //因为b是a的父节点，b是a的上司,有题可知是一颗有向树，因此无需建两条边，无需设置visit标记数组
        scanf("%d %d",&a,&b);
        edge[i].to=a;
        edge[i].next=head[b];
        head[b]=i;
        father[a]=1;
    }
    //找出根节点
    for(int i=1;i<=N;i++){
        if(father[i]==-1){
            root=i;
            break;
        }
    }
    dfs(root);//深度遍历因为上下级的关系，必须得从整棵树的根节点最大的上级开始才行
    printf("%d\n",max(dp[root][0],dp[root][1]));
    return 0;
}

/*
//ac 32ms 分治记忆化搜索
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

struct _edge{
    int to,next;
}edge[6005];
int x[6005],dp[6005][2],head[6005],father[6005];

//这里的重叠子问题是 u点来和u点不来,其子树中的节点的状态是一样的,
//即u点来和u点不来,都需要考虑v点不来的状态,这个状态就是重复出现的
int dfs(int u,int k){
    if(dp[u][k])//对于重叠子问题只需计算一次
        return dp[u][k];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(k)//k=1 u点来,那么下级v肯定不能来
            dp[u][k]+=dfs(v,0);
        else//k=0 u点没来,那么下级v可以来 也可以不来
            dp[u][k]+=max(dfs(v,0),dfs(v,1));
        //上述状态中 dfs(v,0)很明显是重叠子问题
    }
    if(k) dp[u][k]+=x[u];//k=1代表u点来,还需加上u点的快乐度
    return dp[u][k];
}

int main(){
    int N,a,b,root;
    scanf("%d",&N);
    memset(head,-1,sizeof(head));
    memset(father,-1,sizeof(father));
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=N;i++)
        scanf("%d",&x[i]);
    for(int i=0;i<N-1;i++){
        //因为b是a的父节点，b是a的上司,有题可知是一颗有向树，因此无需建两条边，无需设置visit标记数组
        scanf("%d %d",&a,&b);
        edge[i].to=a;
        edge[i].next=head[b];
        head[b]=i;
        father[a]=1;
    }
    //找出根节点
    for(int i=1;i<=N;i++){
        if(father[i]==-1){
            root=i;
            break;
        }
    }
    printf("%d\n",max(dfs(root,0),dfs(root,1)));//root 来或不来 其子问题中的儿子都需要考虑儿子不来的情况显然重叠子问题
    return 0;
}
*/
