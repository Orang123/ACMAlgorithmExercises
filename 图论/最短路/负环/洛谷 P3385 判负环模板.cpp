#include<cstdio>
#include<cstring>
#include<queue>
#define N 3500//100分
#define INF 0x3f3f3f3f
using namespace std;
//spfa bfs判负环
/*
题意:https://www.luogu.com.cn/problem/P3385
链接:https://www.luogu.com.cn/problem/P3385
思路:spfa判负环
*/

struct node{
    int to,w,next;
}edge[N<<1];
int cnt,vis[N],num[N],n,m,dis[N],head[N];

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(){
    dis[1]=0;
    for(int i=2;i<=n;i++)
        dis[i]=INF;//这里初始化为无穷小,因为要求最长路,超级源点松弛后就可更新
}

bool SPFA(int u){
    init();
    queue<int> Q;
    int v;
    Q.push(u);
    vis[u]=1;
    num[u]++;
    while(!Q.empty()){
        u=Q.front();
        vis[u]=0;
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){//松弛判定 最长路
                dis[v]=dis[u]+edge[i].w;
                num[v]++;
                 /*
                判断是否存在负环,理论上每个点最多只可被除自己外n-1个点构成的路径松弛,
                当第n个路径开始对这个点松弛时这个路径一定构成了负环,因为它一定和之前的n-1个路径中的其中一条重复了,
                这里再度松弛就是因为环的权值和为负数才导致其松弛值越来越小
                */
                if(num[v] >= n) return false;//这里 注意是>= 才会满分 网上的板子这里是>n 有点不解,>=n也都ac了
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return true;
}
int main(){
       int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));
        memset(num,0,sizeof(num));
        memset(vis,0,sizeof(vis));
        memset(dis,0,sizeof(dis));
        cnt=0;
        while(m--){
            scanf("%d%d%d",&u,&v,&w);//这里这里构建最短路模型 求取最大值
            if(w>=0){
                addEdge(u,v,w);
                addEdge(v,u,w);
            }
            else
                addEdge(u,v,w);
        }
        if(SPFA(1)) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}

/*
//dfs判负环
//这种做法有点看运气,如果第一条遍历的路径存在负环立马就能结束,但是深度优先遍历 如果一直没有遍历到存在负环的路径,效率也比较低,
//但bfs层次遍历是按照边数层次入队,这样平均对于每条路劲都不会遍历 过深,所以当出现负环时,在这之前不会做太多无意义路径去遍历
//总体而言 spfa还是判负环最标准的做法
#include<cstdio>
#include<cstring>
#define N 3500//洛谷的数据 很强,一个样例超时了,91分
#define INF 0x3f3f3f3f
using namespace std;
struct node{
    int to,w,next;
}edge[N<<1];
int cnt,vis[N],n,m,dis[N],head[N];

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(){
    dis[1]=0;
    for(int i=2;i<=n;i++)
        dis[i]=INF;
}

bool dfs(int u){
    int v;
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(dis[v]>dis[u]+edge[i].w){//松弛判定 最短路
            dis[v]=dis[u]+edge[i].w;
            //如果第二次访问到该点(说明构成了环),因为是dfs深度优先是以原先的那条路径一路访问到底,
            //此过程权值和正常来讲是不断累加变大的过程,若第二次访问再度变得更小，
            //只能说明所构成的环权值和为负数，因此才能在第二次访问时得到松弛,说明在访问的过程中构成了负环,之后就回溯依次全部退栈
            //这里相比spfa判负环显然效率高,当第二次访问到的时候就可以判定负环,而spfa需要连续访问n次才能正式判定
            if(vis[v]) return false;
            if(!dfs(v)) return false;//没有负环就尝试另一条边是否构成负环
        }
    }
    vis[u]=0;
    return true;//没有负环就正常退出
}
int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));
        memset(vis,0,sizeof(vis));
        memset(dis,0,sizeof(dis));
        cnt=0;
        init();
        while(m--){
            scanf("%d%d%d",&u,&v,&w);//这里构建最短路模型 求取最大值
            if(w>=0){
                addEdge(u,v,w);
                addEdge(v,u,w);
            }
            else
                addEdge(u,v,w);
        }
        if(dfs(1)) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}
*/

/*
//这个memset(dis,0,sizeof(dis))先走负权边的做法 还是带有一定偶然性,有些错误,标准做法还是建议spfa判负环
//结果一个测试点超时,一个测试点wa 82分,不建议再采用,
//而且此题虽然要求从1点走,但是这个做法的话因为是从负权边开始遍历,因此需要每个点都作为起点尝试dfs才能保证结果正确
#include<cstdio>
#include<cstring>
#define N 3500
#define INF 0x3f3f3f3f
using namespace std;
struct node{
    int to,w,next;
}edge[N<<1];
int cnt,vis[N],n,m,dis[N],head[N];

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(){
	memset(vis,0,sizeof(vis));
	memset(dis,0,sizeof(dis));
}

bool dfs(int u){
    int v;
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(dis[v]>dis[u]+edge[i].w){//松弛判定 最短路
            dis[v]=dis[u]+edge[i].w;
            if(vis[v]) return false;
            if(!dfs(v)) return false;//没有负环就尝试另一条边是否构成负环
        }
    }
    vis[u]=0;
    return true;//没有负环就正常退出
}
int main(){
    int T,u,v,w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));
        cnt=0;
        while(m--){
            scanf("%d%d%d",&u,&v,&w);//这里构建最短路模型 求取最大值
            if(w>=0){
                addEdge(u,v,w);
                addEdge(v,u,w);
            }
            else
                addEdge(u,v,w);
        }
        int flag=0;
        for(int i=1;i<=n;i++){
        	init();
        	if(!dfs(i)){
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
