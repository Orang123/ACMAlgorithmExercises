#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#define N 50100
#define M 50100
using namespace std;
//ac 139ms
/*
����:Ҫ����һ���ʼ�,�����ܴ����������,�������a,a�ܷ���b,b�ܷ���c,�������㴫����,
���ڷ���˭�ܷ����������.�������˵ı��,����һ�������Ž�С���˵ı��.
����:http://lightoj.com/volume_showproblem.php?problem=1417
˼·:Ҫ�����������,�Ǿ�Ӧ�ð��ʼ��������Ϊ0����,�ټ�������.
��Ȼtarjan������DAG���ܵ�Ȩ�����·��.
Ϊʲô����,��Ϊ���������Ϊ����������·��,ֱ��dfs��������������������.

ע��:����ֻ��������dp�������Ȩ��·��,��Ϊ����dp����Ȩ��·��ǡ�������Ϊ0�ĵ�,
������������Ȩ����·��ĩ�˵�,���������˵ı���Ǵ��.
*/
int n,m,dfn[N],low[N],clock,cnt,block[N],cost[N],dp[N],id,head[N],ans,vis[N];
stack<int> s;
vector<int> G[N];

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            cost[id]++;
        }while(v!=u);
    }
}
//dp[u]����u����·����(����u��)���ĵ�Ȩ��
void dfs(int u){
    vis[u]=1;
    dp[u]=cost[u];
    for(int &v : G[u]){
        if(!vis[v])//���֮ǰ�Լ����dp �Ͳ���dp
            dfs(v);
        dp[u]=max(dp[u],cost[u]+dp[v]);
    }
}

int main(){
    int T,u,v,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        ans=id=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(dfn,0,sizeof(dfn));
        memset(cost,0,sizeof(cost));
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        m=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&u,&v);
            m=max(m,max(u,v));
            addEdge(u,v);
        }
        for(int i=1;i<=m;i++)
            G[i].clear();
        for(int i=1;i<=m;i++){
            if(!dfn[i])
                tarjan(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v])
                G[block[u]].push_back(block[v]);
        }
        for(int i=1;i<=id;i++){//DAG���ܱ��ָ�Ϊ������ͨ��
            if(!vis[i]){//��ſ�ǰ�ĵ㲻һ���������Ϊ0�ĵ�
                dfs(i);
                ans=max(ans,dp[i]);
            }
        }
        for(int i=1;i<=m;i++){
            if(dp[block[i]] == ans){//���ĵ� һ����scc���Ϊ0�ĵ�
                printf("Case %d: %d\n",cas,i);
                break;
            }
        }
    }
    return 0;
}
