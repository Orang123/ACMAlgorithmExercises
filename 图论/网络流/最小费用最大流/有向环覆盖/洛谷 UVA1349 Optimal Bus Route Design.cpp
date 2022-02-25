#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 210
#define INF 0x3f3f3f3f
using namespace std;
//ac 120ms Ek费用流 有向环覆盖
/*
题意:最优巴士路线设计,问题描述:有个大城市想要改进它的公交系统,
其中一个方法就是增加通过景点的观光路线,你的任务就是为该城的观
光公交作一个公交路线计划.你将会被给出一组景点,对于每个被给出的景点,
只能有一条公交路线经过,而且公交路线只能经过这个景点一次.公交路线的数
量可以是无限的, 但每条路线必须至少有两个景点.连接两个景点的道路是单向的,
对于道路(i,j),它的长度为d(i,j).注意即使(i,j)与(j,i)都存在,d(i,j)与d(j,i)
也不一定相同. 每条公交路线必须是个有向环.你需要求出最小的公交路线总长,
即所有公交路线所通过道路的d的总和.
链接:https://www.luogu.com.cn/problem/UVA1349
思路:所有公交路线都要被多个不相交的有向环覆盖,同HDU 1853.
*/
int n,m,cnt,st,ed,head[N],incf[N],pre[N],vis[N],dis[N];
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
    if(sum == n)
        printf("%d\n",cost);
    else
        printf("N\n");
}

void init(){
    cnt=0;
    st=0,ed=n*2+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v,w;
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++){
            addEdge(st,i,1,0);
            addEdge(i+n,ed,1,0);
        }
        for(u=1;u<=n;u++){
            while(scanf("%d",&v) && v){
                scanf("%d",&w);
                addEdge(u,v+n,1,w);
            }
        }
        mcmf();
    }
    return 0;
}
