#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 500
#define M 200100
#define INF 0x3f3f3f3f
using namespace std;

/*
����:n������,m����·,����������������û����·,
�ͻ��޽���·,������������·�͹�·���ȶ�Ϊ1,
һ�л𳵺�һ������ͬʱ��1���������n��,��·;�в�����ͬһ
��������(n�����),������Ҫ�೤ʱ��,�𳵺��������ܶ�����n��.
����:https://codeforces.ml/problemset/problem/602/C
˼·:���������֪��·�͹�·�պù�������ȫͼ,�������·�͹�·
����һ��·����ֱ�Ӵ�1�㵽��n��,������һ��·��ֱ�������·����.
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
    if(mp1[1][n]){//��·��ֱ�Ӵ�1����n,��·�����·
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i == j) continue;
                if(!mp1[i][j]) mp2[i][j]=1;
            }
        }
        bfs(1,mp2);
    }//��·����ֱ�Ӵ�1����n,��·��Ȼ�ܴ�1����n,��ô��·�����·
    else
        bfs(1,mp1);
    if(dis[n]!=INF)
        printf("%d",dis[n]);
    else
        printf("-1");
    return 0;
}
