#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:一棵n个节点的树,需要在一些节点处放置信号塔,一个信号塔能将
信号发送至树上与其邻接的节点(信号塔放置节点也能接收到),
问最少需要在几个节点安置信号塔可使得所有节点均能接受到信号
链接:https://www.luogu.com.cn/problem/P2899
思路:树形dp
dp[u][0]代表在u节点位置放置一个信号塔,u及其子树总共所需要放置的最少节点
dp[u][1]代表u节点的信号由父节点放置的信号塔传递覆盖,u及其子树总共所需要放置的最少节点
dp[u][2]代表u节点的信号由子节点放置的信号塔传递覆盖,u及其子树总共所需要放置的最少节点
*/

int cnt,n,head[N],dp[N][3];

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    int t=INF;//对于叶子节点没有儿子的情况,dp[u][2]会直接加上这个t=INF的情形
    dp[u][0]=1;//在u节点本身放置一个信号塔,个数为1
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        /*
        若在u节点本身放置信号塔,如果儿子节点v放置信号塔只能是dp[v][0],
        若儿子v节点不放置信号塔,则v的信号覆盖可能由v的父亲或v的儿子节点
        放置的信号塔提供.即分别是dp[v][1]和dp[v][2].
        因为是求总共要放置的信号塔个数因此要累加每一个子树v的答案
        */
        dp[u][0]+=min(dp[v][0],min(dp[v][1],dp[v][2]));
        /*
        若u节点本身的信号由u的父亲节点覆盖,则其儿子节点的信号一定不能由
        v的父亲u提供,则儿子节点要么本身放置信号塔,要么由v的儿子放置的信号塔提供信号.
        即分别是dp[v][0],dp[v][2]
        */
        dp[u][1]+=min(dp[v][0],dp[v][2]);
        /*
        若u节点本身的信号由u的儿子节点提供,那么这个信号只需要u的一个儿子提供即可,
        其它儿子取在儿子节点本身放置信号塔或由v的儿子覆盖信号所需信号塔较小的方案即可.
        这里是先不考虑要保留一个儿子节点放置信号塔,全部都尽可能取最小节点数的方案.
        */
        dp[u][2]+=min(dp[v][0],dp[v][2]);
        /*
        t代表 对于u节点的信号由儿子提供时,应该选取哪个儿子节点放置信号塔所能增加加的最小节点数
        dp[v][0]-min(dp[v][0],dp[v][2]),这里dp[v][0]代表考虑将v作为确定放置一个信号塔的节点,
        -min(dp[v][0],dp[v][2]),对于之前选择的较小值需要再增加的节点数,这个值所有节点取最小的增加量,
        当然有可能较小的本身就是dp[v][0],那增加节点数就是0,这里只需要确定一个放置的信号塔v节点,其它节点
        去选取最小节点数的方案,有可能u的儿子节点又多个放置了信号塔,但那是最小的方案.
        */
        t=min(t,dp[v][0]-min(dp[v][0],dp[v][2]));
    }
    dp[u][2]+=t;//加上 dp[u][2]对于确定的v节点作为信号塔最小增加节点数
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,-1);
    //1节点为终止状态,为根节点没有父亲,只需考虑dp[1][0]与dp[1][2]
    printf("%d",min(dp[1][0],dp[1][2]));
    return 0;
}

/*
树形dp另一种思路
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define INF 0x3f3f3f3f
using namespace std;

int cnt,n,head[N],dp[N][3];

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dp[u][0]=1;
    dp[u][2]=INF;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        dp[u][0]+=min(dp[v][0],min(dp[v][1],dp[v][2]));
        dp[u][1]+=min(dp[v][0],dp[v][2]);
    }
    //考虑将u的哪一个儿子v作为确定的放置了信号塔的节点
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        //dp[u][1]实际就是dp[u][2]不考虑至少要有一个儿子放置信号塔,所有儿子都取最少节点的情况,数值上是相等的
        //+dp[v][0]代表v点放置信号塔,-min(dp[v][0],dp[v][2])代表将之前选择的较优方案抵消掉,在原先基础上加上可能增加的节点数
        dp[u][2]=min(dp[u][2],dp[u][1]+dp[v][0]-min(dp[v][0],dp[v][2]));
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,-1);
    printf("%d",min(dp[1][0],dp[1][2]));
    return 0;
}
*/

/*
//dfs+贪心
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;
//贪心思维:对于信号塔要建在哪里,如果选择建在叶子节点,那么信号只能覆盖到当前节点和父节点,
//其它兄弟节点和祖父节点是无法覆盖的,因此要尽量将信号塔建在父节点上
int cnt,n,head[N],fa[N],vis[N],ans;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fath){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fath) continue;
        fa[v]=u;
        dfs(v,u);
    }
    if(!vis[u]){
        //尽量选取在u节点的父亲节点上建立信号塔,这样信号可以覆盖到u的兄弟节点和u的祖父节点
        ans++;//放置信号塔个数+1 贪心选择放在父亲处
        int u0=fa[u];//这里假定u0的父亲为u1
        //将u(叶子)的父亲(u0)标记已经放置过信号塔,同时将其u0的所有儿子都做标记,表示u0建造的信号塔可以覆盖u0所有儿子和父亲u1
        //当回溯到u1时,这里u1之前已经作为u0的儿子(其实是u0的父亲),被标记过,所以到底u1放不放置信号塔,需要判断u1是否还有其它儿子,
        //因为u1的其它儿子还未被标记,若有其它儿子,则处理方式和前面叶子处理方式相同,会把信号塔放置在u1(父亲处),不过不同的时,
        //这里u1之前已经被标记了,但是并不影响ans++以及u1其它儿子的标记操作,这里在u1放置信号塔,覆盖所有儿子和u1的父亲,
        //若u1没有其它儿子,则因为u1之前已经标记,不会进入这个if,那最终就只有u0处放置信号塔,ans只加了1次
        vis[u0]=1;
        for(int i=head[u0];i!=-1;i=edge[i].next)//将u0的儿子全部标记为信号覆盖,这里儿子也包括了u0的父亲
            vis[edge[i].to]=1;
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,-1);
    printf("%d",ans);
    return 0;
}
*/
