#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define N 200100
#define M 1000100
#define INF 0x3f3f3f3f
using namespace std;
//ac 70ms tarjan���㹹��DAG+Dijkstra���· spfaҲ�ǿ��Ե�
//��Ϊ�����·���Կ�����Dijkstra
/*
����:��n����,m���ߵ�����ͼ,ÿ�����б�Ȩ,���㰴����ߵ���Ļ���Ϊ���Ȩ,
�����㻥��ɴ�(��һ������)ʱ,���໥֮�䵽�ﲻ��Ҫ����,�����ʴ�1�㵽��n��
����С����.
����:https://www.luogu.com.cn/problem/P2169
˼·:tarjan���㹹��DAG+Dijkstra���·.
*/

int n,m,head[N],cnt;

int id,dfn[N],low[N],clock,block[N],vis[N],dis[N];
stack<int> s;
vector<pair<int,int> > G[N];

struct Edge{
    int from,to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){from,to,head[from],w};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(block[v]) continue;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
        }while(v!=u);
    }
}

void Dijkstra(int s){
    priority_queue<pair<int,int> > Q;
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    Q.push(make_pair(dis[s],s));
    int u,v,w;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        if(u == block[n]) break;
        vis[u]=1;
        for(pair<int,int> &e : G[u]){
            v=e.first,w=e.second;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
    }
    tarjan(1);//ֻ�蹹��1��������ܵ���ĵ��DAG
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(!dfn[u]) continue;//1��������ɴ�ĵ� �������DAG
        if(block[u]!=block[v])
            G[block[u]].push_back(make_pair(block[v],edge[i].w));
    }
    Dijkstra(block[1]);
    printf("%d",dis[block[n]]);
    return 0;
}

/*
//spfa����TLE,���������������
//ac 85ms tarjan���㹹��DAG+�������������Ȩ��
#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define N 200100
#define M 1000100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,head[N],cnt;
int id,dfn[N],low[N],clock,block[N],dis[N],inde[N];
stack<int> s;
vector<pair<int,int> > G[N];

struct Edge{
    int from,to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){from,to,head[from],w};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(block[v]) continue;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
        }while(v!=u);
    }
}

void topSort(int s){
    queue<int> Q;
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    int u,v,w;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(pair<int,int> &e : G[u]){
            v=e.first,w=e.second;
            dis[v]=min(dis[v],dis[u]+w);
            if(!--inde[v])
                Q.push(v);
        }
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
    }
    tarjan(1);
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(!dfn[u]) continue;
        if(block[u]!=block[v]){
            G[block[u]].push_back(make_pair(block[v],edge[i].w));
            inde[block[v]]++;
        }
    }
    topSort(block[1]);
    printf("%d",dis[block[n]]);
    return 0;
}
*/
