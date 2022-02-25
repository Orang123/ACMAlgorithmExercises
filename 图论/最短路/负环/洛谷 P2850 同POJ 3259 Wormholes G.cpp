#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 600
#define M 5400
#define INF 0x3f3f3f3f
using namespace std;
//spfa做法 较快 188ms
/*
题意:n个农田,m条小路(双向边),w个虫洞
(可以回到过去某个时刻,边权为负,单向边),
现在问john从某地出发是否能回到出发时刻之前,即是否存在负环.
感觉实际图可能是不连通的,需每个点出发都试一下,但是只判断从1出发,确实是ac了.
链接:https://www.luogu.com.cn/problem/P2850
思路:spfa判负环
*/
int n,m,k,cnt,head[N],vis[N],dis[N],num[N];
struct Node{
    int to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(num,0,sizeof(num));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int spfa(int s){
    init(s);
    queue<int>Q;
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
                if(!vis[v]){
                    vis[v]=1;
                    num[v]++;
                    if(num[v]>=n) return 1;
                    Q.push(v);
                }
            }
        }
    }
    return 0;
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d%d",&n,&m,&k);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        while(k--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,-w);
        }
        if(spfa(1)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

/*
//这个做法带有一定的偶然性,有些题目会有wa、tle等错误,还是不建议采用,标准做法仍旧是spfa判负环
//下面这个dfs判负环快的原因在于 memset(dis,0,sizeof(dis)),
//这样dfs求最短路会率先走负权边,这样会较早形成负环,退出dfs,相对会避免很多无意义的路径
//47ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 600
#define M 5400
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,cnt,head[N],vis[N],dis[N];
struct Node{
    int to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    //这是避免TLE的关键原因,这样dfs求最短路时会先走负权边,较早形成负环,避免很多无意义的路径去试探
    memset(dis,0,sizeof(dis));
}

int dfs(int u){
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(dis[v]>dis[u]+edge[i].w){
            dis[v]=dis[u]+edge[i].w;
            if(vis[v]) return 1;
            if(dfs(v)) return 1;
        }
    }
    vis[u]=0;
    return 0;
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d%d",&n,&m,&k);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        while(k--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,-w);
        }
        int flag=0;
        //实际图可能并不连通,所以要从每个点开始搜索,只要有负环就退出
        for(int i=1;i<=n;i++){
        	init(i);
        	if(dfs(i)){
        		flag=1;
        		break;
			}
		}
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
*/


/*
//dfs做法 532ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 600
#define M 5400
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,cnt,head[N],vis[N],dis[N];
struct Node{
    int to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int dfs(int u){
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(dis[v]>dis[u]+edge[i].w){
            dis[v]=dis[u]+edge[i].w;
            if(vis[v]) return 1;
            if(dfs(v)) return 1;
        }
    }
    vis[u]=0;
    return 0;
}

int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d%d",&n,&m,&k);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        while(k--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,-w);
        }
        init(1);
        if(dfs(1)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
*/
