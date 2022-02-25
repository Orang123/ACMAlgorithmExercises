#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 2000
#define INF 0x3f3f3f3f
using namespace std;
//ac 15ms EK算法 最大费用流 拆点 源点->[1,1]->...->[n,n]->汇点
//其实源点和汇点也可以设立为1和n*n*2,起点和终点拆点的连边 2条一条有费用,一条无费用,容量都为1
/*
题意:有一个n*n的矩阵,矩阵的格子中每个都有一个正数.
现在你要从左上角走到右下角去,然后在从右下角回到左上角.
过程中除了左上角和右下角外,任意网格最多走一次,且要求你
所走过的所有网格的权值和最大,为最大值是多少?
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2686
思路:网格拆点思维采用了POJ 3422的思路,而从[1,1]走到[n,n],
再从[n,n]走到[1,1]采用了POJ 2135的思路,所以还是拆点将点权
转化为边权,每个格子只能走1次,容量设置为1,而[1,1],[n,n],能走
2次,但是数值只累加一次,需要再建一条容量为1,费用为0的边,跑费用流即可.
*/
int n,cnt,head[N],st,ed,incf[N],pre[N],dis[N],vis[N],mp[40][40];
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
                dis[v]=dis[u]+edge[i].w;
                incf[v]=min(incf[u],edge[i].cf);
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
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        addEdge(st,1,2,0);//要正反跑2次
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if((i==1 && j==1) || (i==n && j==n))//[1,1] [n,n]要经过2次,但是第二次经过不计算费用
                    addEdge((i-1)*n+j,(i-1)*n+j+n*n,1,0);
                addEdge((i-1)*n+j,(i-1)*n+j+n*n,1,-mp[i][j]);//拆点为入度和出度,容量1,只能走一次,费用设置为负数,求取最大费用
                if(j<n)
                    addEdge((i-1)*n+j+n*n,(i-1)*n+j+1,INF,0);
                if(i<n)
                    addEdge((i-1)*n+j+n*n,i*n+j,INF,0);
            }
        }
        addEdge(n*n*2,ed,2,0);
        printf("%d\n",-mcmf());
    }
    return 0;
}

/*
//ac 15ms dinic 最大费用流 拆点
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 2000
#define INF 0x3f3f3f3f
using namespace std;

int n,cnt,head[N],st,ed,incf[N],pre[N],dis[N],vis[N],mp[40][40];
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
    return dis[ed]!=INF;
}

int dfs(int u,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!vis[v] && edge[i].cf>0 && dis[v] == dis[u]+edge[i].w){
            incf=dfs(v,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
            }
            if(!flow)
                break;
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
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        addEdge(st,1,2,0);//要正反跑2次
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if((i==1 && j==1) || (i==n && j==n))//[1,1] [n,n]要经过2次,但是第二次经过不计算费用
                    addEdge((i-1)*n+j,(i-1)*n+j+n*n,1,0);
                addEdge((i-1)*n+j,(i-1)*n+j+n*n,1,-mp[i][j]);//拆点为入度和出度,容量1,只能走一次,费用设置为负数,求取最大费用
                if(j<n)
                    addEdge((i-1)*n+j+n*n,(i-1)*n+j+1,INF,0);
                if(i<n)
                    addEdge((i-1)*n+j+n*n,i*n+j,INF,0);
            }
        }
        addEdge(n*n*2,ed,2,0);
        printf("%d\n",-mcmf());
    }
    return 0;
}
*/
