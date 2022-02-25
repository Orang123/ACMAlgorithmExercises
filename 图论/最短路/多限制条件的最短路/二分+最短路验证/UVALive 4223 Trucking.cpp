#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;
//UVALive 代码提交了,但是系统不判题,样例都能过
/*
题意:n个城市,m条双向道路,每条道路都有一个高度限制h和距离w,
现在一个卡车要运送一批货物从s地到t地,卡车拉的货物量与其高度
成正比,现在要求在卡车拉最多货物的基础上,从s地到t地,最短要多少距离.
输出卡车此时的车身高和s到t的距离.输入数据会给出卡车车身高的最高限度.s
链接:https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2224
思路:暴力做法是遍历整个图,搜索每一条从s到达t点的路径,
记录每个路径上的车身的最低限度和距离和保存下来,
最后按照车身高作为第一要素降序排列,距离和作为第二要素升序排列.
但这样如果复杂度在于s到t的路径条数,最坏情形下假设s到t有50个点,每两个点之间的连边有5条,
根据乘法原理5^(49)>10^12,时间空间已经爆炸.
正解:对于车身高度输入给出了上限,可以二分车身的高度,跑最短路去验证当前高度是否能到达t点,
若能,继续正大高度,否则减小高度,这样就避免了去遍历所有可能的s到t的路径,最坏时间复杂度为
O(nlog(n)log(h))

*/

int n,m,cnt,head[N],vis[N],dis[N],st,ed;
struct Node{
    int to,next,h,w;
}edge[M<<1];

void addEdge(int from,int to,int h,int w){
    edge[cnt]=(Node){to,head[from],h,w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int Dijkstra(int s,int h){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(u == ed) return 1;
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            if(edge[i].h<h) continue;//若当前道路的高度小于当前二分车身高则不可通过
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return 0;
}

int main(){
    int u,v,h,w,cas=0;
    while(scanf("%d%d",&n,&m) && n+m){
        cas++;
        cnt=0;
        memset(head,-1,sizeof(head));
        while(m--){
            scanf("%d%d%d%d",&u,&v,&h,&w);
            if(h == -1) h=INF;//h为-1时,代表道路高度无限大
            addEdge(u,v,h,w);
            addEdge(v,u,h,w);
        }
        int l=0,r;
        scanf("%d%d%d",&st,&ed,&r);//初始地 目标地 r为车身高的上限
        //二分车身高,跑最短路验证
        while(l<=r){
            int mid=(l+r)/2;
            if(Dijkstra(st,mid)) l=mid+1;//若当前车身高能到达t点,则继续增大车身高
            else r=mid-1;//否则减小车身高
        }
        printf("Case %d:\n",cas);
        if(dis[n]!=INF){
            printf("maximum height = %d\n",r);
            printf("length of shortest route = %d\n",dis[n]);
        }
        else
            printf("cannot reach destination\n");
    }
    return 0;
}
/*
Sample Input
5 6
1 2 7 5
1 3 4 2
2 4 -1 10
2 5 2 4
3 4 10 1
4 5 8 5
1 5 10
5 6
1 2 7 5
1 3 4 2
2 4 -1 10
2 5 2 4
3 4 10 1
4 5 8 5
1 5 4
3 1
1 2 -1 100
1 3 10
0 0

Sample Output
Case 1:
maximum height = 7
length of shortest route = 20
Case 2:
maximum height = 4
length of shortest route = 8
Case 3:
cannot reach destination
*/
