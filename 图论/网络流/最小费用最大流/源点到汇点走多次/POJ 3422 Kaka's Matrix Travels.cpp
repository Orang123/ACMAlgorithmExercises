#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 5500
#define INF 0x3f3f3f3f
using namespace std;
//ac 63ms EK 最小费用流 源点(0)->1->网格点(拆点)->n*n->汇点(n*n*2+1) 费用边权为负
//貌似有从dp考虑的,不过是个贪心的错误思路
/*
题意:给一个N*N的方阵,从[1,1]到[n,n]走K次,走过每个方格加上上面的数
(每个方格初始都有一个非负数),然后这个格上面的数变为0.求可取得的最大的值.
链接:http://poj.org/problem?id=3422
思路:最小费用最大流.设置负值权,最小费用取反即可.
从[1,1]到[n,n,]要走k次,每个点上的数值只能取一次,第二次经过没有分数,
可以将i行j列的点拆点为入点(i-1)*n+j和出点(i-1)*n+j+n*n,建(i-1)*n+j到(i-1)*n+j+n*n
的两条边,一条边容量为1,花费为[i,j]点上的数值,设置为负数,表示数值只能取一次,
另一条边容量为INF,花费为0,代表可以经过该点多次,但第二次经过没有得分.源点为0,
汇点为n*n*2+1,源点向1连容量为k,花费为0的边,代表要走k次,n*n*2向汇点连容量为k,
花费为0的边,代表走k次.跑费用流,输出取反即可.
*/
int st,ed,cnt,head[N];
int n,k,dis[N],incf[N],pre[N],vis[N],mp[60][60];
struct Edge{
    int to,next,cf,w;
}edge[N*N];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    incf[s]=INF;
    pre[ed]=0;
    vis[s]=1;
}

int spfa(int s){
    queue<int> Q;
    init0(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w){
                pre[v]=i;
                incf[v]=min(incf[u],edge[i].cf);
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return pre[ed];
}

int mcmf(){
    int sum=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed]*dis[ed];
    }
    return sum;
}

void init(){
    cnt=0;
    st=0,ed=n*n*2+1;
    memset(head,-1,sizeof(head));
}

int main(){
    scanf("%d%d",&n,&k);
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            scanf("%d",&mp[i][j]);
    }
    addEdge(st,1,k,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            addEdge((i-1)*n+j,(i-1)*n+j+n*n,1,-mp[i][j]);//费用为负
            addEdge((i-1)*n+j,(i-1)*n+j+n*n,INF,0);
            if(j<n)
                addEdge((i-1)*n+j+n*n,(i-1)*n+j+1,INF,0);
            if(i<n)
                addEdge((i-1)*n+j+n*n,i*n+j,INF,0);
        }
    }
    addEdge(n*n*2,ed,k,0);
    printf("%d",-mcmf());
    return 0;
}

/*
//ac 79ms EK算法 费用流 费用都为正数,修改spfa判断条件dis[v]<dis[u]+edge[i].w 求解最大费用
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 5500
#define INF 0x3f3f3f3f
using namespace std;

int st,ed,cnt,head[N];
int n,k,dis[N],incf[N],pre[N],vis[N],mp[60][60];
struct Edge{
    int to,next,cf,w;
}edge[N*N];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    for(int i=0;i<N;i++)
        dis[i]=-INF;//赋值负无穷,因为源点的连向的费用为0,也会出现实际增广路费用为负的情况
    dis[s]=0;
    incf[s]=INF;
    pre[ed]=0;
    vis[s]=1;
}

int spfa(int s){
    queue<int> Q;
    init0(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //求解最长路的合理性在于,如果正向过来,反向cf一定<=0,不可能回去构成死循环
            if(edge[i].cf>0 && dis[v]<dis[u]+edge[i].w){//求解最大费用
                pre[v]=i;
                incf[v]=min(incf[u],edge[i].cf);
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return pre[ed];
}

int mcmf(){
    int sum=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed]*dis[ed];
    }
    return sum;
}

void init(){
    cnt=0;
    st=0,ed=n*n*2+1;
    memset(head,-1,sizeof(head));
}

int main(){
    scanf("%d%d",&n,&k);
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            scanf("%d",&mp[i][j]);
    }
    addEdge(st,1,k,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            addEdge((i-1)*n+j,(i-1)*n+j+n*n,1,mp[i][j]);//费用为正
            addEdge((i-1)*n+j,(i-1)*n+j+n*n,INF,0);
            if(j<n)
                addEdge((i-1)*n+j+n*n,(i-1)*n+j+1,INF,0);
            if(i<n)
                addEdge((i-1)*n+j+n*n,i*n+j,INF,0);
        }
    }
    addEdge(n*n*2,ed,k,0);
    printf("%d",mcmf());
    return 0;
}
*/

/*
//ac 79ms dinic 费用流 拆点 费用边权为负,求解最小费用 取反
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 5500
#define INF 0x3f3f3f3f
using namespace std;

int st,ed,cnt,head[N];
int n,k,dis[N],incf[N],pre[N],vis[N],mp[60][60];
struct Edge{
    int to,next,cf,w;
}edge[N*N];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    memset(vis,0,sizeof(vis));
    vis[s]=1;
}

int spfa(int s){
    queue<int> Q;
    init0(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return dis[ed] != INF;
}

int dfs(int u,int flow){
    if(u == ed)
        return flow;
    vis[u]=1;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!vis[v] && edge[i].cf>0 && dis[v] == dis[u]+edge[i].w){
            incf=dfs(v,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
                if(!flow)
                    break;
            }
        }
    }
    return res;
}

int mcmf(){
    int sum=0,incf;
    while(spfa(st)){
        incf=dfs(st,INF);
        sum+=incf*dis[ed];
    }
    return sum;
}

void init(){
    cnt=0;
    st=0,ed=n*n*2+1;
    memset(head,-1,sizeof(head));
}

int main(){
    scanf("%d%d",&n,&k);
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            scanf("%d",&mp[i][j]);
    }
    addEdge(st,1,k,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            addEdge((i-1)*n+j,(i-1)*n+j+n*n,1,-mp[i][j]);
            addEdge((i-1)*n+j,(i-1)*n+j+n*n,INF,0);
            if(j<n)
                addEdge((i-1)*n+j+n*n,(i-1)*n+j+1,INF,0);
            if(i<n)
                addEdge((i-1)*n+j+n*n,i*n+j,INF,0);
        }
    }
    addEdge(n*n*2,ed,k,0);
    printf("%d",-mcmf());
    return 0;
}
*/
