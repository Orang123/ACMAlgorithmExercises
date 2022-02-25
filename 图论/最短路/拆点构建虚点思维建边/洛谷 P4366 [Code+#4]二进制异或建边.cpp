#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:n个点的图,有m条单向边,任意两点之间默认还有单向边连接,
其权值为i^j*c,现在求从a到b的最短路.
链接:https://www.luogu.com.cn/problem/P4366
思路:对于任意两点间的连边不能暴力建边空间开销为M+N^2(N<=10^5),可以考虑异或的性质和二进制
的特性去建边,1(001)和6(110) 1->6代价为7(111)C,
可以转化为1(001)->5(101) 代价4C,5(101)->4(100) 代价C
4(100)->6(110) 代价2C,1->5->4->6 总代价还是7C
这样只需要建M+N*log2(N)条边.
*/

int n,m,c,a,b,cnt,head[N],vis[N],dis[N];

struct Node{
    int to,next,w;
}edge[M+N*17];//log2(N)=16.6

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    /*
    任意两点间连边,有些点是直接相连,有些点可通过其余点拼接,
    间接相连,这样代价不变.这个二进制建边十分巧妙,需要建个图,
    对照图理解.
    */
    for(int i=0;i<=n;i++){//o(nlog2(n))
        for(int j=1;j<=n;j<<=1){
            if((i^j)>n) continue;//i^j大于n的编号的点是不存在的
            addEdge(i,i^j,j*c);//从i->(i^j) 花费为 i^(i^j)*c=j*c 构造点边的连接
        }
    }
}

void Dijkstra(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(u == b) return;
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
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&c);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
    }
    scanf("%d%d",&a,&b);
    Dijkstra(a);
    printf("%d",dis[b]);
    return 0;
}
