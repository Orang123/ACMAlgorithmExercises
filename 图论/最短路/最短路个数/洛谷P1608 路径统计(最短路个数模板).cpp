#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 2100
#define M 4000100
#define INF 0x3f3f3f3f
using namespace std;
//spfa做法
/*
题意:求解1->n的最短路个数,两个不同的最短路方案要求为
路径长度相同(均为最短路长度)且至少有一条边不重合,输入数据会有重边
这里对于重边如果也计算进去就会导致,最短路数目计算偏大.
链接:https://www.luogu.com.cn/problem/P1608
思路:设置num数组,num[v]表示到达点v的最短路个数.
*/


int n,m,cnt,head[N],vis[N],num[N],dis[N],mp[N][N];
struct Node{
    int to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void spfa(int s){
    init(s);
    queue <int>Q;
    num[s]=vis[s]=1;//起始点代表一条路径
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        //一方面来讲n点不需要再去扩展别的点,因为这对扩展n的最短路没有什么贡献,只会使得dis[n]变得越来越大
        //另一方面来讲 已经计算好的num[n]也会被清空,导致答案错误.
        if(u == n) continue;//这里也不能直接return结束,因为spfa先出队的点其dis不一定就是最小的,还可能其它路径会再更新到该点
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                num[v]=num[u];//最短路径发生变化,根据前驱节点的路径条数更新v节点路径条数
            }
            else if(dis[v]==dis[u]+edge[i].w)
                num[v]+=num[u];//当相等时,v节点路径条数就要加上u前驱节点路径条数
            /*
            spfa算法这里对于dis[v]==dis[u]+edge[i].w也是需要入队的,
            因为spfa是bfs遍历无法保证n出队时,到达n前驱的节点的u的最短路个数num[u]都统计出来,
            可能的一种情况是已经有边数较少的最短路先遍历到了n的前驱节点u,然后后来松弛到
            n的前驱节点u时,虽然dis[u]相等,但是此时并不入队,所以对于num[n]也并没有累加到
            后来扩展的最短路的个数.因此这里对于相等的情况,也同样需要需要入队,这样才能使得
            其余可能的最短路都扩展到n节点.
            */
            //num[v]不等于0 就代表dis[v]>=dis[u]+edge[i].w 的情况,对于dis[v]<dis[u]+edge[i].w是不需要入队的
            if(num[v] && !vis[v]){
                vis[v]=1;
                Q.push(v);
            }
        }
        /*
        u节点扩展过后其 num[u]要清0,这样可以避免其余最短路num[v]累加时,原先v点的已经出队的最短路重复计算
        所以每次累加最短路都是同事累加边数相同的最短路个数,其中边数较少的最短路会较早累加,累加完了后,
        其节点的num都会清空,避免后面边数较长的最短路累加时重复累加.
        */
        num[u]=0;
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        //注意输入数据可能会有重边,所以为了避免最短路数目计算过大,这里对于两点间只能有一条边,并且是最小的边权.
        if(!mp[u][v] || w<mp[u][v]){
            addEdge(u,v,w);
            mp[u][v]=w;
        }
    }
    spfa(1);
    if(dis[n]!=INF)
        printf("%d %d",dis[n],num[n]);
    else
        printf("No answer");
    return 0;
}

/*
//Dijkstra,不需要避免重复计算的情况,因为不会出现某些最短路先行扩展到n节点的情况,
//对于num[v]而言都是将到达v点的最短路个数全部统计完后,才将v点出队,再继续扩展别的点
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 2100
#define INF 0x3f3f3f3f
using namespace std;
//因为有重边所以可以用邻接矩阵 存边,方便判重
int n,m,cnt,head[N],vis[N],num[N],mp[N][N],dis[N];

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void Dijkstra(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    num[s]=1;//起始点代表一条路径
    Q.push(make_pair(0,s));
    int u;
    while(!Q.empty()){
        //每次出队的都是权值和较小的点,并不一定是边数最少的点,所以即使有某些路径边数较小,
        //在权值和最小但不唯一的情况下,也不会先行出队扩展到n节点,因为其到达u节点的边数少,
        //所以在相同情况下其路径上节点的权也会较大,
        //所以相比较路径边数较多到达u节点dis[u]相同的情况,出队也会较晚,因为边数较小的路径节点权值和相对较小,
        //所以在u出队时到达u的最短路数目是全部被计算完毕的.
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int v=1;v<=n;v++){
            if(v == u) continue;
            if(dis[v]>dis[u]+mp[u][v]){
                dis[v]=dis[u]+mp[u][v];
                num[v]=num[u];//最短路径发生变化,根据前驱节点的路径条数更新v节点路径条数
                Q.push(make_pair(-dis[v],v));
            }
            else if(dis[v]==dis[u]+mp[u][v])
                num[v]+=num[u];//当相等时,v节点路径条数就要加上u前驱节点路径条数
        }
    }
}

int main(){
    int u,v,w;
    memset(mp,INF,sizeof(mp));
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        mp[u][v]=min(mp[u][v],w);
    }
    Dijkstra(1);
    if(dis[n]!=INF)
        printf("%d %d",dis[n],num[n]);
    else
        printf("No answer");
    return 0;
}
*/
