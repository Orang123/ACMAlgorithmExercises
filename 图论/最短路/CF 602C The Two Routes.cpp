#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 500
#define M 200100
#define INF 0x3f3f3f3f
using namespace std;

/*
题意:n个城镇,m条铁路,如果任意两个城镇间没有铁路,
就会修建公路,两个城镇间的铁路和公路长度都为1,
一列火车和一辆汽车同时从1点出发到达n点,在路途中不能在同一
城镇相遇(n点除外),问最少要多长时间,火车和汽车才能都到达n点.
链接:https://codeforces.ml/problemset/problem/602/C
思路:根据题意可知铁路和公路刚好构成了完全图,则对于铁路和公路
必有一条路线能直接从1点到达n点,对于另一条路线直接跑最短路即可.
*/

int n,m,mp1[N][N],mp2[N][N],dis[N],vis[N];

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void bfs(int s,int mp[][N]){
    init(s);
    queue<int> Q;
    vis[s]=1;
    Q.push(s);
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int v=1;v<=n;v++){
            if(!mp[u][v]) continue;
            if(!vis[v]){
                vis[v]=1;
                dis[v]=dis[u]+1;
                if(v == n) return;
                Q.push(v);
            }
        }
    }
}

int main(){
    int u,v;
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        mp1[u][v]=mp1[v][u]=1;
    }
    if(mp1[1][n]){//铁路能直接从1到达n,公路跑最短路
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i == j) continue;
                if(!mp1[i][j]) mp2[i][j]=1;
            }
        }
        bfs(1,mp2);
    }//铁路不能直接从1到达n,则公路必然能从1到达n,那么铁路跑最短路
    else
        bfs(1,mp1);
    if(dis[n]!=INF)
        printf("%d",dis[n]);
    else
        printf("-1");
    return 0;
}
