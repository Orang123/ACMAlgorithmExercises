#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#define N 30010
#define M 150100
using namespace std;
//ac 79ms
/*
//����ժ����https://www.cnblogs.com/ZShogg/archive/2013/03/05/2944158.html
����:���������ҷ�����,�յ�������Ҹ����������̶ȶ���������(�����и�).
ÿ���˶�סһ������,����֮���·�ǵ����,�������ѡ��һ����Ϊ���,
·�����ظ���,���䲻���ظ�����,�����Ծ�����������.
�����ʷ���õ�������̶������Ƕ��٣�
����:�������DAG������Ȩ�͵�·��,��Ȩ����Ϊ��,�����ߵ��õ��ʱ��,
���ڸ�ֵ���Բ�ȡ.
����:http://poj.org/problem?id=3160
˼·:tarjan���sccʱ̰�Ķ��ڸ�Ȩ��ȡ����,���㹹��DAG,������������Ȩ�ͺ͵�·������.
*/

int n,m,dfn[N],low[N],clock,cnt,block[N],cost[N],dp[N],id,head[N],inde[N],val[N],ans;
stack<int> s;
vector<int> G[N];
vector<int>:: iterator it;

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
            if(val[v]>0)//̰��ֻѡȡ��Ȩֵ�ķ������,�����븺Ȩֵ�ķ���
                cost[id]+=val[v];
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
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        ans=max(ans,dp[u]);
        Q.pop();
        for(it=G[u].begin();it!=G[u].end();it++){
            v=*it;
            dp[v]=max(dp[v],dp[u]+cost[v]);
            if(!--inde[v])
                Q.push(v);
        }
    }
}

void init(){
    ans=id=clock=cnt=0;
    memset(head,-1,sizeof head);
    memset(block,0,sizeof(block));
    memset(dfn,0,sizeof(dfn));
    memset(inde,0,sizeof(inde));
    memset(dp,0,sizeof(dp));
    memset(cost,0,sizeof(cost));
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        for(int i=0;i<n;i++)
            scanf("%d",&val[i]);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        for(int i=0;i<n;i++){
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
