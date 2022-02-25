#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;

/*
����:n���ڵ������ͼ,��1�ڵ㵽������ڵ����·��������.
����:http://poj.org/problem?id=1502
˼·:���·.ע�������ǰ������,x�������㲻��ͨ.
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
