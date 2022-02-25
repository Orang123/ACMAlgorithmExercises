#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;
//ac 360ms EK 费用流 源点->供应商->顾客->汇点
/*
题意:(摘自网上)有n个顾客,m个供应商,k种货物,给你顾客对于每种货物的要求个数,
和供应商对于每种货物的现有量,以及供应每种货物的时候供应商和顾客之间的运输单价,
问你满足所有顾客的前提下的最小运输费用是多少.
链接:http://poj.org/problem?id=2516
思路:首先判断每个所有供应商对每种货物的供应量是否都大于等于所有顾客的需求量,
若是则有解,否则无解,输出-1.有解的情况对每种货物跑一遍最小费用最大流,源点0,汇点n+m+1,
对于货物k,源点向每个供应商建容量为存货量的边,每个顾客向汇点建容量为货物需求量的边,
每个供应商向每个顾客建容量为INF,单位费用为该商品单位运费的边,跑最大流,求出最小费用即可.
*/
int st,ed,cnt,head[N];
int n,m,k,need[N][N],supply[N][N],goods[N],cost[N][N][N],dis[N],incf[N],pre[N],vis[N],ans;
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
    ans=0;
    st=0,ed=n+m+1;
    memset(goods,0,sizeof(goods));
}

int main(){
    while(scanf("%d%d%d",&n,&m,&k) && n+m+k){
        init();
        for(int i=1;i<=n;i++){//n个顾客对j货物的需求量
            for(int j=1;j<=k;j++){
                scanf("%d",&need[i][j]);
                goods[j]+=need[i][j];
            }
        }
        for(int i=1;i<=m;i++){//m个供应商对j货物的供应量
            for(int j=1;j<=k;j++){
                scanf("%d",&supply[i][j]);
                goods[j]-=supply[i][j];
            }
        }
        for(int i=1;i<=k;i++)
            for(int j=1;j<=n;j++)
                for(int l=1;l<=m;l++)//对于第i种货物,l供应商运输给j顾客的单位费用为cost[i][l][j]
                    scanf("%d",&cost[i][l][j]);
        int flag=0;
        for(int i=1;i<=k;i++){//判断每种货物是否存在解
            if(goods[i]>0){//需求量大于供应量无解
                flag=1;
                break;
            }
        }
        if(flag){
            printf("-1\n");
            continue;
        }
        for(int i=1;i<=k;i++){//每种货物跑一遍最大流
            cnt=0;
            memset(head,-1,sizeof(head));
            for(int j=1;j<=m;j++)
                addEdge(st,j,supply[j][i],0);//源点向供应商建边 容量货物现存量,费用0
            for(int j=1;j<=n;j++)
                addEdge(j+m,ed,need[j][i],0);//每个顾客向汇点建边 容量为货物需求量,费用0
            for(int j=1;j<=m;j++){
                for(int l=1;l<=n;l++)
                    addEdge(j,l+m,INF,cost[i][j][l]);//供应商j向顾客l+m建边,容量INF,费用为对应运输单价
            }
            ans+=mcmf();//累加最小费用
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 375ms EK 费用流 源点->顾客->供应商->汇点
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int st,ed,cnt,head[N];
int n,m,k,need[N][N],supply[N][N],goods[N],cost[N][N][N],dis[N],incf[N],pre[N],vis[N],ans;
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
    ans=0;
    st=0,ed=n+m+1;
    memset(goods,0,sizeof(goods));
}

int main(){
    while(scanf("%d%d%d",&n,&m,&k) && n+m+k){
        init();
        for(int i=1;i<=n;i++){//n个顾客对j货物的需求量
            for(int j=1;j<=k;j++){
                scanf("%d",&need[i][j]);
                goods[j]+=need[i][j];
            }
        }
        for(int i=1;i<=m;i++){//m个供应商对j货物的供应量
            for(int j=1;j<=k;j++){
                scanf("%d",&supply[i][j]);
                goods[j]-=supply[i][j];
            }
        }
        for(int i=1;i<=k;i++)
            for(int j=1;j<=n;j++)
                for(int l=1;l<=m;l++)//对于第i种货物,l供应商运输给j顾客的单位费用为cost[i][l][j]
                    scanf("%d",&cost[i][l][j]);
        int flag=0;
        for(int i=1;i<=k;i++){//判断每种货物是否存在解
            if(goods[i]>0){//需求量大于供应量无解
                flag=1;
                break;
            }
        }
        if(flag){
            printf("-1\n");
            continue;
        }
        for(int i=1;i<=k;i++){//每种货物跑一遍最大流
            cnt=0;
            memset(head,-1,sizeof(head));
            for(int j=1;j<=n;j++)
                addEdge(st,j,need[j][i],0);//源点向顾客建边 容量顾客需求量,费用0
            for(int j=1;j<=m;j++)
                addEdge(j+n,ed,supply[j][i],0);//每个货物向汇点建边 容量为货物现存量,费用0
            for(int j=1;j<=n;j++){
                for(int l=1;l<=m;l++)
                    addEdge(j,l+n,INF,cost[i][l][j]);//顾客j向供应商l+n建边,容量INF,费用为对应运输单价
            }
            ans+=mcmf();//累加最小费用
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 297ms dinic 费用流 源点->供应商->顾客->汇点
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int st,ed,cnt,head[N];
int n,m,k,need[N][N],supply[N][N],goods[N],cost[N][N][N],dis[N],vis[N],ans;
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
    ans=0;
    st=0,ed=n+m+1;
    memset(goods,0,sizeof(goods));
}

int main(){
    while(scanf("%d%d%d",&n,&m,&k) && n+m+k){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=k;j++){
                scanf("%d",&need[i][j]);
                goods[j]+=need[i][j];
            }
        }
        for(int i=1;i<=m;i++){
            for(int j=1;j<=k;j++){
                scanf("%d",&supply[i][j]);
                goods[j]-=supply[i][j];
            }
        }
        for(int i=1;i<=k;i++)
            for(int j=1;j<=n;j++)
                for(int l=1;l<=m;l++)
                    scanf("%d",&cost[i][l][j]);
        int flag=0;
        for(int i=1;i<=k;i++){
            if(goods[i]>0){
                flag=1;
                break;
            }
        }
        if(flag){
            printf("-1\n");
            continue;
        }
        for(int i=1;i<=k;i++){
            cnt=0;
            memset(head,-1,sizeof(head));
            for(int j=1;j<=m;j++)
                addEdge(st,j,supply[j][i],0);
            for(int j=1;j<=n;j++)
                addEdge(j+m,ed,need[j][i],0);
            for(int j=1;j<=m;j++){
                for(int l=1;l<=n;l++)
                    addEdge(j,l+m,INF,cost[i][j][l]);
            }
            ans+=mcmf();
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
