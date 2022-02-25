#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 21000
#define INF 1e15//0x3f Ӧ�ò���,��ΪwȨ�Ϳ��ܱ�0x3f����
using namespace std;
typedef long long ll;

/*
����:n������,�������·,��һ���·�ǵ�������֮���˫���·,
�ڶ����·�ǳ���Ⱥ֮��ĵ�·,һ������Ⱥ�����г��п�ͨ���ڶ����·��
��һ������Ⱥ�ڵ����е�·��ͨ,�ʴӳ���s������t����̾����Ƕ���.
����:https://nanti.jisuanke.com/t/A1244
˼·:�ڶ����·�Ľ�����Ȼ�����ܽ���������Ⱥ�е����г�����������,������MLE,
Ҳ��TLE,��˿��Զ���ÿ������Ⱥ��㹹���һ������(�ɳ���Ⱥ�����г�������)
��һ�����(�������Ⱥ�����еĳ���),��Ȩ��Ϊ0,������������Ⱥ�еĵڶ����·,
��ͨ��һ������Ⱥ�ĳ��㵽��һ������Ⱥ����㽨��ʵ�ֻ�ͨ.
*/

int n,m,cnt,head[N<<2],vis[N<<2];//ÿ������Ⱥ����2�����(3N) �������N<<2
ll dis[N<<2];
struct Node{
    int to,next;
    ll w;
}edge[N<<3];//������������

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    for(int i=1;i<(n<<2);i++)
        dis[i]=(i==s?0:INF);
}

void spfa(int s){
    queue <int>Q;
    init(s);
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

int main(){
    int u,v,s,t,num,m0;
    ll w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d",&num);
        while(num--){
            scanf("%d",&v);
            addEdge(v,i+n,0);//ÿ�����е����㽨��
            addEdge(i+n+m,v,0);//��㵽ÿ�����н��� ��Ȩ��Ϊ0
        }
    }
    scanf("%d",&m0);
    while(m0--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    scanf("%d",&m0);
    while(m0--){
        scanf("%d%d%lld",&u,&v,&w);//���ｨ���������u+2*n,v+n+m��u+n�п��ܻ���
        addEdge(u+n,v+n+m,w);//����Ⱥu�ĳ��������Ⱥv����㽨��
        addEdge(v+n,u+n+m,w);//����Ⱥv�ĳ��������Ⱥu����㽨�� ������ʵ����������Ⱥ֮��������ͨ
    }
    scanf("%d%d",&s,&t);
    spfa(s);
    if(dis[t]!=INF)
        printf("%lld\n",dis[t]);
    else
        printf("-1\n");
    return 0;
}

/*
Dijkstra����
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 21000
#define INF 1e15//0x3f Ӧ�ò���,��ΪwȨ�Ϳ��ܱ�0x3f����
using namespace std;
typedef long long ll;

int n,m,cnt,head[N<<2],vis[N<<2];
ll dis[N<<2];
struct Node{
    int to,next;
    ll w;
}edge[N<<3];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    for(int i=1;i<(n<<2);i++)
        dis[i]=(i==s?0:INF);
}

void Dijkstra(int s){
    priority_queue<pair<int,int> >Q;
    init(s);
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int u,v,s,t,num;
    ll w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d",&num);
        while(num--){
            scanf("%d",&v);
            addEdge(v,i+n,0);
            addEdge(i+2*n,v,0);
        }
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u+n,v+2*n,w);
        addEdge(v+n,u+2*n,w);
    }
    scanf("%d%d",&s,&t);
    Dijkstra(s);
    if(dis[t]!=INF)
        printf("%lld\n",dis[t]);
    else
        printf("-1\n");
    return 0;
}
*/
