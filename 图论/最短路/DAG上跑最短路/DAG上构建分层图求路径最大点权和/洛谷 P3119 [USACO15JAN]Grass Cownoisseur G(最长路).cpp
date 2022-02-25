#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define N 100100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;
//ac 274ms 缩点构造DAG上的分层图(思维建边)+spfa找到达(block[1]+id)最大点权和的路径
/*
题意:约翰有n块草场,编号1到n,这些草场由若干条单行道相连.
奶牛贝西是美味牧草的鉴赏家,她想到达尽可能多的草场去品尝牧草.
贝西总是从1号草场出发,最后回到1号草场.她想经过尽可能多的草场,
贝西在通一个草场只吃一次草,所以一个草场可以经过多次,因为草场是单行道连接,
这给贝西的品鉴工作带来了很大的不便,贝西想偷偷逆向行走一次,
但最多只能有一次逆行.问,贝西最多能吃到多少个草场的牧草.
链接:https://www.luogu.com.cn/problem/P3119
思路:因为只能逆行一次,所以可以考虑构造分层图,但是为了减少复杂度,需要先缩点
去除环,这样在构造DAG的同时构造2层的分层图即可,最后spfa跑到达(block[1]+id)的
最大点权和,这里为了避免回到1所在的scc时点权重复累加,可以在更新点权和时延后累加,
这样既避免了点权重复累加,也解决了当使用一次逆向机会走到分层图i+n编号的点将之前已经
累加过点权的点重复累加的问题.
需要注意的是对于原图本身就是强连通图时,需要特判,因为延迟累加点权会在下一个节点才累加
当前这个点的点权,而现在没有边,所以要特判直接输出block[1]中点数,或者直接再构造一条,
block[1]连向(block[1]+id)(第二层图中的1所在scc).
*/
//此题如果有k次走逆向边的机会,那基本只能用分层图的办法,不能再考虑反向建边跑两次spfa枚举逆边,
//那样枚举需要枚举好几条边逆向,就好几重循环
//因为要构建2层DAG,所以数组要开到2N
int n,m,head[N],cnt;
int id,dfn[N],low[N],clock,block[N],num[N<<1],vis[N<<1],dis[N<<1];
stack<int> s;
vector<int> G[N<<1];

struct Edge{
    int from,to,next;
}edge[M*3];//两层图+中间的逆向边 3M

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(block[v]) continue;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            num[id]++;
        }while(v!=u);
    }
}

void spfa(int s){
    queue<int> Q;
    vis[s]=1;
    //初始点权不能累加,为了避免重复累加
    Q.push(s);
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int v : G[u]){
            //延迟累加点权,到达v点时 累加的是前驱u的点权,可以避免回到block[1]+id时block[1]点权重复累加
            //其实也可以累加num[v]的点权,这样回到block[1]时,就可以把初始时没累加的block[1]补上,
            //只是这样其余没有回到block[1]的路径都少加了block[1]的点权
            if(dis[v]<dis[u]+num[u]){
                dis[v]=dis[u]+num[u];
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++){//这个一定要把所有点都求出scc,因为可以走一次逆向边
        if(!dfn[i])
            tarjan(i);
    }
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v]){
            G[block[u]].push_back(block[v]);
            G[block[u]+id].push_back(block[v]+id);//第二层DAG
            G[block[v]].push_back(block[u]+id);//两层间的逆向边
            num[block[u]+id]=num[block[u]];//初始化第二层图的点权
            num[block[v]+id]=num[block[v]];
        }
    }
    //当原图本身就是强连通图时,1所在的scc的个数就是答案,但因为点权是延后累加的,
    //所以要直接构造一个block[1]到block[1]+id的边,这样点权就能累加到block[1]+id上.
    G[block[1]].push_back(block[1]+id);
    //num[block[1]+id]=num[block[1]];//这个是当延迟加点权 加的是num[v]是要初始化num[block[1]+id],否则原图为SCG时结果为0
    spfa(block[1]);
    printf("%d",dis[block[1]+id]);//这样要求回到block[1],因为是DAG,那么dis[block[1]+id]便是答案
    return 0;
}

/*
//tarjan构建DAG+拓扑序dp求路径最大点权和 不可行
//这个题目因为可以走1次逆向边,所以要整个图都要tarjan求解出scc构建DAG,而且还要求从s出发,所以无法用拓扑序求解,
//因为所有点的DAG构建出来,有些点1是无法到达的,如果按照入度为0点初始化,但是无法保证结果起点是否是s,所以结果会错;
//如果只将s点入队,那么其余点入度可能在中间过程永远不为0
*/

/*
//ac 274ms 分层图的dp枚举状态形式
//注意这里不能用Dijkstra(),因为这里求解的是最大点权和,而优先队列先弹出后 就不会再更新了,
//但后续可能会有更优的,这是因为bfs层序遍历和最大点权和相矛盾导致的
#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define N 100100
#define M 100100
#define INF 0x3f3f3f3f

using namespace std;
int n,m,head[N],cnt;
//dis[u][0]代表到达u点不走逆向边能吃的最多草数
//dis[u][1]代表到达u点只走1次逆向边能吃的最多草数
int id,dfn[N],low[N],clock,block[N],num[N],vis[N][2],dis[N][2];
stack<int> s;
//first表示连接 点的编号 second表示边的方向,0代表正向,1代表实际不存在的逆向边
vector<pair<int,int> > G[N];

struct Edge{
    int from,to,next;
}edge[M];
struct state{
    int u,cnt;//cnt是当前走了几次逆向边cnt<=1
    state(int u=0,int cnt=0):u(u),cnt(cnt){}
};

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(block[v]) continue;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            num[id]++;
        }while(v!=u);
    }
}

void spfa(int s){
    queue<state> Q;
    vis[s][0]=1;
    //这里并没有累加初始block[1]的点权,因为下面加的是num[v],
    //回到初始点block[1]时会补上开始没累加的num[block[1]]避免重复累加
    Q.push(state(s,0));
    state tmp;
    int u,v,nowcnt,flag;
    while(!Q.empty()){
        tmp=Q.front();
        u=tmp.u,nowcnt=tmp.cnt;
        Q.pop();
        vis[u][nowcnt]=0;
        for(pair<int,int> e : G[u]){
            v=e.first,flag=e.second;
            //正向边 只要权值和能更新更大就更新
            if(!flag && dis[v][nowcnt]<dis[u][nowcnt]+num[v]){//这里延迟加点权可以加num[u]
                dis[v][nowcnt]=dis[u][nowcnt]+num[v];
                if(!vis[v][nowcnt]){
                    vis[v][nowcnt]=1;
                    Q.push(state(v,nowcnt));
                }
            }
            //反向边 当前走逆向边的次数需为0 并且权值和还能更大才更新
            else if(flag && !nowcnt && dis[v][nowcnt+1]<dis[u][nowcnt]+num[v]){
                dis[v][nowcnt+1]=dis[u][nowcnt]+num[v];//dis[v][nowcnt+1] 到达v点是通过走一次逆向边实现
                if(!vis[v][nowcnt+1]){
                    vis[v][nowcnt+1]=1;
                    Q.push(state(v,nowcnt+1));
                }
            }
        }
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i);
    }
    if(id == 1){
        printf("%d",num[1]);
        return 0;
    }
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v]){//构造DAG
            G[block[u]].push_back(make_pair(block[v],0));//建正向边 标记0
            G[block[v]].push_back(make_pair(block[u],1));//建反向边 标记1
        }
    }
    spfa(block[1]);
    printf("%d",dis[block[1]][1]);
    return 0;
}
*/

/*
//ac 220ms 反向建边,跑两次spfa,然后枚举每一条边 尝试逆向走
//dis1[block[v]]+dis2[block[u]]-num[block[1]] 便是答案,这里除了block[1]会累加两次外,
//其余点是不会重复累加的,因为已经缩点构造出DAG,如过还有点重复累加,会出现环的,显然和前提DAG相矛盾.
#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define N 100100
#define M 100100
#define INF 0x3f3f3f3f

using namespace std;
int n,m,head[N],cnt;
int id,dfn[N],low[N],clock,block[N],num[N],vis[N],dis1[N],dis2[N];
stack<int> s;
vector<int> G1[N],G2[N];

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(block[v]) continue;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            num[id]++;
        }while(v!=u);
    }
}

void spfa1(int s){
    queue<int> Q;
    vis[s]=1;
    dis1[s]=num[s];
    Q.push(s);
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int v : G1[u]){
            if(dis1[v]<dis1[u]+num[v]){
                dis1[v]=dis1[u]+num[v];
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

void spfa2(int s){
    queue<int> Q;
    vis[s]=1;
    dis2[s]=num[s];
    Q.push(s);
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int v : G2[u]){
            if(dis2[v]<dis2[u]+num[v]){
                dis2[v]=dis2[u]+num[v];
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v,ans;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i);
    }
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v]){//构造DAG
            G1[block[u]].push_back(block[v]);
            G2[block[v]].push_back(block[u]);//建反图-DAG
        }
    }
    spfa1(block[1]);//跑正向边
    spfa2(block[1]);//跑反向边
    //因为从1点出发,所以至少吃的草是1所在的scc中点的个数,当原图就是强连通图时,也能保证ans的有初始值 保证结果正确
    ans=num[block[1]];
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v]){
            //这里一定是block[v]用正向边到达,block[u]用反向边到达,
            //否则block[v]反向,block[u]正向,而现在边是block[u]->block[v],
            //这样构成了环,而DAG中是不存在环的,即没有一条边会同时满足dis1[block[v]] && dis2[block[u]],求不出答案.
            //其实就是通过枚举每一条边,然后假定逆向走了这条边使得其回到block[1]的.本身是不构成环的.
            if(dis1[block[v]] && dis2[block[u]])//block[u] block[v]一定得是可达的
                ans=max(ans,dis1[block[v]]+dis2[block[u]]-num[block[1]]);
        }
    }
    printf("%d",ans);
    return 0;
}
*/

/*
//记忆化搜索 暂时还没看 https://www.luogu.com.cn/problem/solution/P3119
#include<iostream>
#include<cstdio>
#include<vector>
#include<stack>
#include<cstring>
using namespace std;
long long read()
{
    long long x=0,f=1; char c=getchar();
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int N=100000+100;
struct road
{
    int to,IsBack;
    road (int A,int B)
    {
        to=A,IsBack=B;
    }
};
vector <int> e[N];
vector <road> e2[N];
int belong[N],nd_tot,nd_to,low[N],dfn[N],InStack[N],cnt[N];
stack <int> st;
void Tarjan(int now)
{
    low[now]=dfn[now]=++nd_to;
    InStack[now]=true;
    st.push(now);
    for(int i=0;i<int(e[now].size());i++)
        if(dfn[e[now][i]]==0)
        {
            Tarjan(e[now][i]);
            low[now]=min(low[now],low[e[now][i]]);
        }
        else if(InStack[e[now][i]]==true)
            low[now]=min(low[now],low[e[now][i]]);
    if(low[now]==dfn[now])
    {
        nd_tot++;
        while(st.empty()==false)
        {
            int temp=st.top();
            st.pop();
            belong[temp]=nd_tot;
            InStack[temp]=false;
            cnt[nd_tot]++;
            if(temp==now)
                break;
        }
    }
}
int n,m,S,f[N][2];
int dfs(int now,int back)
{
    if(f[now][back]>=0) return f[now][back];
    int t_ans=0;
    bool OK=false;
    for(int i=0;i<int(e2[now].size());i++)
        if(e2[now][i].to!=S and back-e2[now][i].IsBack>=0)
            t_ans=max(t_ans,dfs(e2[now][i].to,back-e2[now][i].IsBack));
        else if(back>=e2[now][i].IsBack)
            OK=true;
    if(t_ans!=0 or OK==true)
        return f[now][back]=t_ans+cnt[now];
    else
        return f[now][back]=0;
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
        e[i].reserve(4),
        e2[i].reserve(4);
    for(int i=1;i<=m;i++)
    {
        int s=read(),t=read();
        e[s].push_back(t);
    }

    for(int i=1;i<=n;i++)
        if(dfn[i]==0)
            Tarjan(i);
    S=belong[1];
    for(int i=1;i<=n;i++)
        for(int j=0;j<int(e[i].size());j++)
            if(belong[i]!=belong[e[i][j]])
            {
                e2[belong[i]].push_back(road(belong[e[i][j]],0));
                e2[belong[e[i][j]]].push_back(road(belong[i],1));
            }

    memset(f,0x80,sizeof f);
    int ans=0;
    for(int i=0;i<int(e2[S].size());i++)
        ans=max(ans,dfs(e2[S][i].to,1-e2[S][i].IsBack));

    printf("%d",ans+cnt[S]);
    return 0;
}
*/
