#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;
//Dijkstra 358ms
/*
题意:n个点的图,现在要删掉一条边,求出从1到n最短路的最大值,
如果最坏情况下不可达,请输出-1.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3986
思路:如果暴力枚举所有边,这样时间复杂度可达O(M*NlogN),因为只是删除一条边,
所以可以考虑枚举删除原先最短路中的一条边,这样再次求出的最短路更大概率比
原先的要大,而如果所有边都枚举,则大多数情况下,结果还是原先的最短路,没有意义.
要将第一次遍历的最短路路径和每条边的edge 下标记录下来,再从n往前枚举删除每
条边跑最短路.
*/

int n,m,cnt,head[N],vis[N],dis[N],pre[N],minEdge[N];
struct Node{
    int to,next,w,sign;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w,0};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}
//求出最短路路径和最短路边的编号
void Dijkstra1(int s){
    init(s);
    priority_queue<pair<int,int> > Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                minEdge[v]=i;
                pre[v]=u;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

void Dijkstra2(int s){
    init(s);
    priority_queue<pair<int,int> > Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            if(edge[i].sign) continue;
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int T,u,v,w,ans;
    scanf("%d",&T);
    while(T--){
        ans=cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&n);
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        Dijkstra1(1);
        if(dis[n]==INF){
            printf("-1\n");
            continue;
        }
        int x=n;
        while(x!=1){
            int y=minEdge[x];
            //这里严格来讲其反向边也是要删除的,有些做法只删掉了正向边也过了,数据太弱
            edge[y].sign=edge[y^1].sign=1;
            Dijkstra2(1);//删掉一条边后再跑最短路
            edge[y].sign=edge[y^1].sign=0;
            ans=max(ans,dis[n]);
            x=pre[x];
        }
        if(ans==INF) printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}

/*
//spfa 436ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 50100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],vis[N],dis[N],pre[N],minEdge[N];
struct Node{
    int to,next,w,sign;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w,0};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}
//求出最短路路径和最短路边的编号
void spfa1(int s){
    init(s);
    queue<int> Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                minEdge[v]=i;
                pre[v]=u;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

void spfa2(int s){
    init(s);
    queue<int> Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            if(edge[i].sign) continue;
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int T,u,v,w,ans;
    scanf("%d",&T);
    while(T--){
        ans=cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&n);
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        spfa1(1);
        if(dis[n]==INF){
            printf("-1\n");
            continue;
        }
        int x=n;
        while(x!=1){
            int y=minEdge[x];
            //这里严格来讲其反向边也是要删除的,有些做法只删掉了正向边也过了,数据太弱
            edge[y].sign=edge[y^1].sign=1;
            spfa2(1);//删掉一条边后再跑最短路
            edge[y].sign=edge[y^1].sign=0;
            ans=max(ans,dis[n]);
            x=pre[x];
        }
        if(ans==INF) printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}
*/
