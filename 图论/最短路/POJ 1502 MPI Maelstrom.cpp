#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;

/*
题意:n个节点的无向图,求1节点到其余各节点最短路的最大距离.
链接:http://poj.org/problem?id=1502
思路:最短路.注意输入是半个矩阵,x代表两点不互通.
*/

int n,mp[N][N],vis[N],dis[N],ans;

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}
void Dijkstra(int s){
    init(s);
    priority_queue<pair<ll,int> >Q;
    Q.push(make_pair(0,s));
    int u;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        ans=max(ans,dis[u]);
        vis[u]=1;
        for(int v=1;v<=n;v++){
            if(!mp[u][v]) continue;
            if(dis[v]>dis[u]+mp[u][v]){
                dis[v]=dis[u]+mp[u][v];
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    char str[20];
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            scanf("%s",str);
            if(str[0] != 'x')
                mp[j][i]=mp[i][j]=atoi(str);
        }
    }
    Dijkstra(1);
    printf("%d",ans);
    return 0;
}
