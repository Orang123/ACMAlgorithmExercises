/*
����:ժ������
������1���յ�2������������·��������
�����Ǹ���·���ϵ����б�AB��Ҫ����A���յ��
���·����B���յ�����·��
����:http://acm.hdu.edu.cn/showproblem.php?pid=1142
˼·:�����������2���������·.��������1������·��ʱ,
���ڶ��֧�Ľ����,����·�����������ص�������,������Ҫ���仯
����.
dp[v]��ʾ2��v�Ϸ�·��������
*/
//ac 78ms ���·(Dijkstra)+���仯����
//dp[v]��ʾ2��v�Ϸ�·��������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dp[N],mp[N][N],vis[N],dis[N];

void Dijkstra(int s){
    dis[s]=0;
    int mind,u;
    for(int i=1;i<=n;i++){
        mind=INF;
        for(int j=1;j<=n;j++){
            if(!vis[j] && dis[j]<mind){
                mind=dis[j];
                u=j;
            }
        }
        vis[u]=1;
        for(int v=1;v<=n;v++){
            if(dis[v]>dis[u]+mp[u][v])
                dis[v]=dis[u]+mp[u][v];
        }
    }
}

int dfs(int u){
    if(dp[u]!=-1)
        return dp[u];
    if(u == 2)//�����յ㷵��1
        return dp[u]=1;
    dp[u]=0;
    for(int v=1;v<=n;v++){
        if(mp[u][v] == INF || dis[u]<=dis[v])
            continue;
        dp[u]+=dfs(v);
    }
    return dp[u];
}

int main(){
    int u,v,w;
    while(scanf("%d",&n) && n){
        scanf("%d",&m);
        memset(vis,0,sizeof(vis));
        memset(mp,0x3f,sizeof(mp));
        memset(dis,0x3f,sizeof(dis));
        memset(dp,-1,sizeof(dp));//0Ҳ�ǺϷ�ֵ,��˳�ʼ��Ϊ-1
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            mp[u][v]=mp[v][u]=w;
        }
        Dijkstra(2);
        printf("%d\n",dfs(1));
    }
    return 0;
}

/*
//ac 31ms ���·(spfa)+���仯����
//dp[v]��ʾ2��v�Ϸ�·��������
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],dp[N],vis[N],dis[N];
struct Edge{
	int to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
	edge[cnt]=(Edge){to,head[from],w};
	head[from]=cnt++;
}

void spfa(int s){
	queue<int> Q;
	dis[s]=0;
	vis[s]=1;
	Q.push(s);
	int u,v;
	while(!Q.empty()){
		u=Q.front();
		Q.pop();
		vis[u]=0;
		for(int i=head[u];i!=-1;i=edge[i].next){
			v=edge[i].to;
			if(dis[v]>dis[u]+edge[i].w){
				dis[v]=dis[u]+edge[i].w;
				if(!vis[v]){
					vis[v]=1;
					Q.push(v);
				}
			}
		}
	}
}

int dfs(int u){
    if(dp[u]!=-1)
        return dp[u];
    if(u == 2)
        return dp[u]=1;
    dp[u]=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
    	int v=edge[i].to;
    	if(dis[u]<=dis[v])
    		continue;
    	dp[u]+=dfs(v);
	}
    return dp[u];
}

int main(){
    int u,v,w;
    while(scanf("%d",&n) && n){
        scanf("%d",&m);
        cnt=0;
        memset(head,-1,sizeof(head));
        memset(vis,0,sizeof(vis));
        memset(dis,0x3f,sizeof(dis));
        memset(dp,-1,sizeof(dp));
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        spfa(2);
        printf("%d\n",dfs(1));
    }
    return 0;
}
*/
