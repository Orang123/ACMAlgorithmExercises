#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 500
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;
//ac 47ms EK算法
/*
题意:n头牛,f种食物和d种饮料,每头牛有喜欢吃的
食物和饮料类型,现在要为每头牛指定一种食物和饮料,
并且一头牛只能选择一种食物和一种饮料,并且每种食物
和饮料只能供一头牛食用,现在问最多有几头牛能选择到
自己喜欢的食物和饮料.
链接:http://poj.org/problem?id=3281
思路:可以构造源点0,汇点f+2*n+d+1,将牛拆点成两个点f+i,f+n+i,
f+i串行连接食物,f+n+i串行连接饮料.源点向每个食物i连边,
即:0->i,食物向牛连边,牛向饮料连边,饮料向汇点连边,所有边
容量为1,跑最大流即是答案.
0为源点,1-f为食物,f+i到f+n*2为牛,f+n*2+i到F+n*2+d为饮料,f+n*2+d+1为汇点,
容量都为1.

注意:牛必须要拆点,如果不拆点直接源点->食物->牛->饮料->汇点,
这样可能会出现每个牛选择多个食物和饮料的情况,不满足题目要求,
所以一头牛要拆为两个点连接,容量为1.
*/
int n,f,d,cnt,head[N],incf[N],pre[N];
struct Edge{
    int to,next,cf;
}edge[M];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0};
    head[to]=cnt++;
}

int bfs(int s,int ed){
    queue<int> Q;
    incf[s]=INF;
    memset(pre,-1,sizeof(pre));
    pre[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && pre[v] == -1){
                incf[v]=min(incf[u],edge[i].cf);
                pre[v]=i;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int max_flow(int st,int ed){
    int sum=0,v;
    while(bfs(st,ed)){
        v=ed;
        while(v!=st){
            edge[pre[v]].cf-=incf[ed];
            edge[pre[v]^1].cf+=incf[ed];
            v=edge[pre[v]^1].to;
        }
        sum+=incf[ed];
    }
    return sum;
}

void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
}

int main(){
    int f0,d0,v;
    init();
    scanf("%d%d%d",&n,&f,&d);//n头牛,f种食物,d种饮料
    for(int i=1;i<=f;i++)//源点向食物建边 容量为1
        addEdge(0,i,1);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&f0,&d0);
        while(f0--){
            scanf("%d",&v);
            addEdge(v,f+i,1);//食物v向牛f+i建边,容量为1
        }
        addEdge(f+i,f+n+i,1);//将牛的拆点连接起来,容量为1
        while(d0--){
            scanf("%d",&v);
            addEdge(f+n+i,f+2*n+v,1);//牛f+n+i向饮料f+2*n+v建边,容量为1
        }
    }
    for(int i=1;i<=d;i++)
        addEdge(f+2*n+i,f+2*n+d+1,1);//每个饮料向汇点连边,容量为1
    printf("%d",max_flow(0,f+2*n+d+1));
    return 0;
}

/*
//ac 32ms dinic
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 500
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;

int n,f,d,cnt,head[N],dis[N];
struct Edge{
    int to,next,cf;
}edge[M];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0};
    head[to]=cnt++;
}

int bfs(int s,int ed){
    queue<int> Q;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v] == -1){
                dis[v]=dis[u]+1;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int dfs(int u,int ed,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,ed,min(flow,edge[i].cf));
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
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(int st,int ed){
    int sum=0;
    while(bfs(st,ed))
        sum+=dfs(st,ed,INF);
    return sum;
}

void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
}

int main(){
    int f0,d0,v;
    init();
    scanf("%d%d%d",&n,&f,&d);
    for(int i=1;i<=f;i++)
        addEdge(0,i,1);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&f0,&d0);
        while(f0--){
            scanf("%d",&v);
            addEdge(v,f+i,1);
        }
        addEdge(f+i,f+n+i,1);
        while(d0--){
            scanf("%d",&v);
            addEdge(f+n+i,f+2*n+v,1);
        }
    }
    for(int i=1;i<=d;i++)
        addEdge(f+2*n+i,f+2*n+d+1,1);
    printf("%d",max_flow(0,f+2*n+d+1));
    return 0;
}
*/
