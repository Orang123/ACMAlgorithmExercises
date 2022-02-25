#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 2100
#define M 15000
#define INF 0x3f3f3f3f
using namespace std;
//ac 10ms EK费用流 拆点建边
/*
题意:一个带权有向图,求起点到终点的两条路径权值之和最小,
且两条路径没有公共点(除起点,终点).
链接:https://www.luogu.com.cn/problem/UVA1658
思路:费用流,因为每个点除了起点终点两条路径不能有公共点,
所以拆点,i(入点),i+n(出点).i->i+n建容量为1,费用为0的边,
注意起点终点拆点间的边容量为2,因为是找两条中间点不重复的路径,
起点是1,汇点是n+n.u-v之间存在w的有向边,建u+n->v容量为1,费用为
w的边,跑费用流即可.
*/
int n,m,cnt,st,ed,head[N],incf[N],pre[N],vis[N],dis[N];
struct Edge{
    int to,next,cf,w;
}edge[M<<1];

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

void mcmf(){
    int sum=0,cost=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed];
        cost+=incf[ed]*dis[ed];
    }
    printf("%d\n",cost);
}

void init(){
    cnt=0;
    st=1,ed=n*2;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v,w;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        for(int i=2;i<n;i++)//拆点
            addEdge(i,i+n,1,0);
        addEdge(1,1+n,2,0);//起点和终点 拆点间容量为2,因为起点终点可以重复2次,是找两条独立路径.
        addEdge(n,n+n,2,0);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u+n,v,1,w);
        }
        mcmf();
    }
    return 0;
}
