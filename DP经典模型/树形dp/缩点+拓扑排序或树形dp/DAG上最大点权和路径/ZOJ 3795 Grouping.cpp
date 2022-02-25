#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#define N 100100
#define M 300100
using namespace std;
//ac 80ms tarjan����+DAG�����������·��������Ȩ��
/*
����:n����,m�����������С��ϵ,si->ti����,si��������ڵ���ti������,
����������Ҫ����Щn�������ٷֳɼ���С��,һ���˵����䲻Ӧ��ֱ�ӻ��ӵ�
��ͬһȺ�����໥�Ƚ�,Ҳ����˵ͬ���ڵ��������С��ϵ��δ֪�Ĳ��ɱȽϵ�.
����:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827369801
˼·:����һ��ѭ���ջ� s1>=s2>=s3>=s4>=s1,˵��һ��scc�������˵����䶼����ȵ�,
��Ȼͬһscc�������С��ϵһ������֪��,��ô����һ��scc�ڵĵ�ÿ���˱��뱻�ֵ���ͬ
����,��ĸ�����Ϊscc�ڵ�ĸ���,��������������ǿ���tarjan���㹹��DAG,ֻ����DAG
�ϲ�ͬ·����֧�ĵ�֮���С��ϵ����δ֪���ܱȽϵ�,��ô����һ��·���ϵĵ�ÿ����(scc)��Ӧ��
�ֵ���ͬ����,ͬʱÿ��scc�ڵĵ�ҲӦ�ڲ�ͬ����,�����ڲ�ͬ·���ϵĵ��ǿ��Էֵ�ͬһ���,��Ϊ��Сδ֪,
�������·���ϵ�Ȩ�͸���,��ô��Ȩ�ͽϴ��·���϶��е�ʣ�໹��Ҫ�ٵ�������,��ô��Ȼ����Ҫ�ֵ���
Ӧ����Ȩֵ������·��,����Ҫ�������ǲ�ͬ·����֧�ϵ�����Ȩ��,��ȨΪÿ��scc�ڵ�ĸ���.

ע��:�����������dfs��dp����ĺ��岻ͬ,dp[u]��������������ȴ�������Ϊ0�ĵ㵽u��·���ϵ�����Ȩ��,
���Ϊ0�ĵ�dp[u]����С��,·��ĩ�˵��dp��������.
����dp dp[u]����u��������֧·����(����u��)���ĵ�Ȩ�� ֻ�����Ϊ0�ĵ����dp[u]��������,Ҷ�ӽڵ��dpֵ����С��
*/
int n,m,dfn[N],low[N],clock,cnt,block[N],cost[N],dp[N],id,head[N],inde[N],ans;
stack<int> s;
vector<int> G[N];

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
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
//dp[u]��������Ϊ0�ĵ㵽u��·���ϵ�����Ȩ��
void topSort(){
    queue<int> Q;
    for(int i=1;i<=id;i++){
        if(!inde[i]){
            dp[i]=cost[i];
            Q.push(i);
        }
    }
    int u;
    while(!Q.empty()){
        u=Q.front();
        ans=max(ans,dp[u]);
        Q.pop();
        for(int &v : G[u]){
            dp[v]=max(dp[v],dp[u]+cost[v]);
            if(!--inde[v])
                Q.push(v);
        }
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        ans=id=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(dfn,0,sizeof(dfn));
        memset(inde,0,sizeof(inde));
        memset(dp,0,sizeof(dp));
        memset(cost,0,sizeof(cost));
        for(int i=1;i<=n;i++) G[i].clear();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v]){
                inde[block[v]]++;
                G[block[u]].push_back(block[v]);
            }
        }
        topSort();
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 83ms tarjan����+DAG������dp
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#define N 100100
#define M 300100
using namespace std;

int n,m,dfn[N],low[N],clock,cnt,block[N],cost[N],dp[N],id,head[N],inde[N],ans,vis[N];
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
    dp[u]=cost[u];//������Ϊ�˱���Ҷ�ӽڵ�dp[u]û�и�ֵ
    for(int &v : G[u]){
        if(!vis[v])//���֮ǰ�Լ����dp �Ͳ���dp
            dfs(v);
        dp[u]=max(dp[u],cost[u]+dp[v]);
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        ans=id=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(block,0,sizeof(block));
        memset(dfn,0,sizeof(dfn));
        memset(inde,0,sizeof(inde));
        memset(cost,0,sizeof(cost));
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++) G[i].clear();
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                tarjan(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v]){
                inde[block[v]]++;
                G[block[u]].push_back(block[v]);
            }
        }
        for(int i=1;i<=id;i++){//DAG���ܱ��ָ�Ϊ������ͨ��
            if(!vis[i]){//��ſ�ǰ�ĵ㲻һ���������Ϊ0�ĵ�
                dfs(i);
                ans=max(ans,dp[i]);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
