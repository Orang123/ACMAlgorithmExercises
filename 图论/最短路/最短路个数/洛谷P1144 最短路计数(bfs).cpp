#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1000100
#define M 2000100
#define INF 0x3f3f3f3f
#define MOD 100003
using namespace std;

/*
����:����1��������ÿ��������·����.
����:https://www.luogu.com.cn/problem/P1144s
˼·:����num[x]��ʾ����ڵ�x�����·����,dis[v]����ʱ,num[v]=num[u],
���������·��ʱ��Ȩֵ����ͬʱ,num[v]+=num[u].

��Ϊ����Ȩֵ�㶨Ϊ1,����Ҳ�������ص�bfs��,���Ƕ�������ͼ ��ȨΪw�Ĳ���ֵ,
���·�����Ǿ���������,��ʱ���ص�bfs�Ͳ���Ӧ��,��ΪȨֵ���㶨,���ѵ���Ҳ
��һ�������·.
*/

int n,m,cnt,head[N],vis[N],num[N],dis[N];
struct Node{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void bfs(int s){
    init(s);
    queue <int>Q;
    num[s]=vis[s]=1;//��ʼ�����һ��·��
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //�����û������,��ô��ǰ�������ľ��������̵�,��Ϊ�����Ȩ��Ϊ1,bfs��һ�α�������һ������̵�
            if(!vis[v]){
                vis[v]=1;
                dis[v]=dis[u]+1;
                Q.push(v);
            }
            //���ҵ����·���ߺ����·�������ʱ ���ۼ����·����
            if(dis[v] == dis[u]+1)
                num[v]=(num[v]+num[u])%MOD;
        }
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    bfs(1);
    for(int i=1;i<=n;i++)
        printf("%d\n",num[i]);
    return 0;
}
/*
//Dijkstra����
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1000100
#define M 2000100
#define INF 0x3f3f3f3f
#define MOD 100003
using namespace std;
//Dijkstra ���·����
int n,m,cnt,head[N],vis[N],num[N],dis[N];
struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void Dijkstra(int s){
    init(s);
    priority_queue <pair<int,int> >Q;
    num[s]=1;//��ʼ�����һ��·��
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
                num[v]=num[u];//���·�������仯,����ǰ���ڵ��·����������v�ڵ�·������
                Q.push(make_pair(-dis[v],v));
            }
            else if(dis[v]==dis[u]+edge[i].w)
                num[v]=(num[v]+num[u])%MOD;//�����ʱ,v�ڵ�·��������Ҫ����uǰ���ڵ�·������
        }
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v,1);
        addEdge(v,u,1);
    }
    Dijkstra(1);
    for(int i=1;i<=n;i++)
        printf("%d\n",num[i]);
    return 0;
}
*/


