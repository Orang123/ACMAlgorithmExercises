#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f
using namespace std;
//此题不能理解 把取模的余数作为实际的点
/*
题意:给定一个整数K.求一个K的整数倍SUM,使得SUM的数位累加和最小
链接:https://atcoder.jp/contests/arc084/tasks/arc084_b
思路:
https://blog.csdn.net/ACM2017/article/details/81395233 来自此博客
首先，让我们转换一下思维，从数到图。先说说操作，对于任意一个0..k-1之间的整数x，将x看做一个点。
由于从x出发可以引出两项基本操作：
(1)x*=10,此时x的各位数字和不发生改变，此操作可以转换成从x到x*10%k连一条有向边，权值0；
(2)x++,此时x的各位数字和也加一，此操作可以转换成从x到(x+1)%k连一条有向边，权值1。
这样图中有k个点（0..k-1），2*k条边。
然后， 关于合理性和含义，阐释如下。所有对k同余的数目可以看做图中的同一个点，当我们从点1出发，
沿着构造好的有向图的边走到0点时，就相当于走到了一个k的正整数倍数的点值，不妨设其为ak。
而这一路走来经过的所有边的权值之和，也就是逐步或加1或加0得到的总和，正是ak的各位数值总和减一。
（这一路走来是经过了连接点与点的路径，而出发点是1不是0；出发点显然不能与终点相同，故不能是0；
若出发点不是1而是1后面的点，难免会忽略了一些在那后面的点之前的可能的比较优的路径。因此应从1到0走一趟）。
易知此有向图的最短路径长度减一就是答案。
(3)k<=1e5,点数k，边数2k，跑dijkstra即可。
*/

int n,cnt,head[N],vis[N],dis[N];

struct Node{
    int to,next,w;
}edge[N*10];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void Dijkstra(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
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
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        for(int j=0;j<=9;j++)
            addEdge(i,(i*10+j)%n,j);
    }
    Dijkstra(1);
    printf("%d",dis[0]+1);//%n为0的 刚好就是n的倍数 其数位和就是最短路权值和+1,这里的1是第一次1作为起点没有加上的1数位
    return 0;
}

/*
另一种做法:https://blog.csdn.net/ACM2017/article/details/81395233
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100001;
struct node{
    int v,nxt,cost;
}edge[N<<1];
int head[N],k,tot;
int q[N*8],l,r,u,v;
int dist[N];
void addEdge(int u,int v,int val) {
    edge[++tot].v=v;
    edge[tot].cost=val;
    edge[tot].nxt=head[u];
    head[u]=tot;
}
int main() {
    //freopen("out.txt","w",stdout);
    scanf("%d",&k);
    for (int i=0;i<k;++i) {
        addEdge(i,i+1==k?0:i+1,1);
        addEdge(i,i*10%k,0);
        dist[i]=N;
    }
    dist[1]=0;
    l=-1;
    r=0;
    q[0]=1;
    while (l<r) {
        u = q[++l];
        for (int i=head[u];i;i=edge[i].nxt) {
            v=edge[i].v;
            if (dist[u]+edge[i].cost<dist[v]) {
                dist[v]=dist[u]+edge[i].cost;
                q[++r]=v;
            }
        }
    }
    printf("%d\n",dist[0]+1);
    return 0;
}
*/
