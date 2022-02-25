#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1600
#define INF 0x3f3f3f3f
using namespace std;

/*
����:https://www.luogu.com.cn/problem/P2458
����:https://www.luogu.com.cn/problem/P2458
˼·:�����P2899˼·һ��,ֻ��������ÿ�����ѡ����Ҫ�ټ���Ȩֵ.
��Ϊ��ϵ������ֵ��ѡȡ,������ֻ��������ѡȡ���ٸ���ʹ�ñ����ܿ������и�λ,
������������dfs+̰�Ľⷨ.
*/

int cnt,n,m,head[N],dp[N][3],cost[N];

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    int t=INF;
    dp[u][0]=cost[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        dp[u][0]+=min(dp[v][0],min(dp[v][1],dp[v][2]));
        dp[u][1]+=min(dp[v][0],dp[v][2]);
        dp[u][2]+=min(dp[v][0],dp[v][2]);
        t=min(t,dp[v][0]-min(dp[v][0],dp[v][2]));
    }
    dp[u][2]+=t;
}

int main(){
    int u,v,k;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&u);
        scanf("%d%d",&cost[u],&k);
        while(k--){
            scanf("%d",&v);
            addEdge(u,v);
            addEdge(v,u);
        }
    }
    dfs(1,-1);
    printf("%d",min(dp[1][0],dp[1][2]));
    return 0;
}
