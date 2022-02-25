#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
#define M 100000
#define INF 0x3f3f3f3f
using namespace std;
//ac 63ms dinic
/*
摘自网上
题意:n个点,其中有np个是能提供电力的点,nc个是能消费电力的点,剩下的点(n-np-nc)
是中转战即不提供电力也不消费电力,点与点之间是有线路存在的,有m条线路,
每条线路有最多运载限定.前4个数据就是有n个点,np个供电点,nc个消费点,m条线路,
接来题目先给出的是m条线路的数据,(起点,终点)最多运载量,然后是np个供电点的数据
(供电点)最多供电量,接着就是nc个消费点的数据(消费点)最多消费电量.题目要我们
求出给定的图最大能消费的总电量(就是求最大流).
链接:http://poj.org/problem?id=1459
思路:最大流裸题,dinic算法求解.
*/
int n,np,nc,m,st,ed,cnt,head[N],dis[N];
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
    int ans=0;
    while(bfs(st,ed))
        ans+=dfs(st,ed,INF);
    return ans;
}

void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v,cf;
    while(scanf("%d%d%d%d",&n,&np,&nc,&m)!=EOF){
        init();
        while(m--){//m条线路,有运载量限制cf
            scanf(" (%d,%d)%d",&u,&v,&cf);
            addEdge(u+1,v+1,cf);//输入编号0~n-1,设置源点0,汇点n+1,所以点编号都加1
        }
        while(np--){//np个发电线路,发电量为icf
            scanf(" (%d)%d",&v,&cf);
            addEdge(0,v+1,cf);
        }
        while(nc--){//nc个消费线路,消费电量cf
            scanf(" (%d)%d",&v,&cf);
            addEdge(v+1,n+1,cf);
        }
        printf("%d\n",max_flow(0,n+1));
    }
    return 0;
}
