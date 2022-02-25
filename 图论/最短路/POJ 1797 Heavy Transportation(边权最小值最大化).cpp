#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;
//Dijkstra 266ms
//�������·���б�Ȩ��Сֵ����������spfa,��Ϊspfa�޷���֤�ظ�����ǰ���ڵ������,��Ϊ�ɳڱ�����ǲ�ȷ����
/*
��ȻDijkstra�޷������Ȩͼ�·,���������Ŀ������Ȩ����Сֵ���,
����1->2->3 ��Ȩ2��5 1->3 ��Ȩ4 ��ô��ʼ1�ڵ���չʱ,2 ��4��Ȩ���,����̰��4�ȳ���,
3�ڵ���,����Ϊʲô������2->3�ı�Ȩ5��,��Ϊ����ȡ·������Сֵ,һ��ʼ2�ͱ�4С,��������Сֵֻ��<=2,
������3��ʱ,���ֵ����4,���3�ڵ��һ�α�Ǻ�,��¼�ľ�������Ȩ,�����ٱ��ɳ�.���Ǻ��·��Ȩ��
��ͬ�ĵط�.ͬ������·����Ȩ���ֵ��С������,Dijkstraͬ������.
*/
/*
����:���1��n��·���б�Ȩ��С�����ֵ�Ƕ���.
����:http://poj.org/problem?id=1797
˼·:���·,�޸����ɳ�����.dis[v]<min(dis[u],edge[i].w)
*/

int n,m,cnt,head[N],dis[N],vis[N];
struct Node{
    int to,next,w;
}edge[M];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0,sizeof(dis));//����Dijkstra Q.top
    dis[s]=INF;
}

void Dijkstra(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(dis[s],s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;//����Dijkstra Q.top ÿ�ζ������������ֵ��ǰ·���б�Ȩ�����ֹ��
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //��ǰ����v��·���еı�Ȩ��Сֵ�����֮ǰ·������v�����Сֵ��������
            //����v��һ����δ������,�����п��ܻ�ʹ��v�ڵ��ǰ���ڵ��ظ���� ����dis[u]���ֵ�������
            if(!vis[v] && dis[v]<min(dis[u],edge[i].w)){
                dis[v]=min(dis[u],edge[i].w);
                Q.push(make_pair(dis[v],v));
            }
        }
    }
}

int main(){
    int u,v,w,T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        Dijkstra(1);
        printf("Scenario #%d:\n",cas);
        printf("%d\n\n",dis[n]);
    }
    return 0;
}
/*
//kruskal ��������� 266ms
#include<cstdio>
#include<algorithm>
#define N 1100
#define M 500100
using namespace std;

int n,m,fa[N],sum;

struct Edge{
    int u,v,w;
    bool operator <(const Edge &x)const{
        return w>x.w;
    }
}edge[M];

void init(){
    sort(edge+1,edge+1+m);
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}

int kruskal(){
    init();
    int x,y;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            if(find(1) == find(n)) return edge[i].w;
        }
    }
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        printf("Scenario #%d:\n",cas);
        printf("%d\n\n",kruskal());
    }
    return 0;
}
*/

/*
//prim ac 313ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,mp[N][N],dis[N],vis[N];

void init(){
    memset(vis,0,sizeof(vis));
    memset(dis,0,sizeof(dis));
}

int prim(int s){
    init();
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,ans=INF;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        if(u!=s)
            //��Ϊprimÿ�μӵ��ǼӾ���mst�еĵ��Ȩֵ���ĵ�ӵ�,�������ı�Ȩ��һ������С��,�п��ܺ���ӵı߷�������һЩ
            //����Ҫ��ȡ�Ѽ����Ȩ����С�ı߾���1��n·������Сֵ�����ı�Ȩ,
            ans=min(ans,dis[u]);
        //δ����mst�еı߼�ʹ�д�1��n��·����,Ҳ�ǽ�С�ı�,������ȡ��С�ߵ����ֵ
        if(u == n) break;//ֻҪn���1����ͨ��,��û��Ҫ���Ǻ���ĵ�,û����,��1��n��·����û��ϵ��,Ϊ����ans�����¼,�͵���ǰ����
        for(int v=1;v<=n;v++){
            if(mp[u][v] == -1) continue;//û�б�
            if(!vis[v] && mp[u][v]>dis[v]){
                dis[v]=mp[u][v];
                Q.push(make_pair(dis[v],v));
            }
        }
    }
    return ans;
}

int main(){
    int T,cas=0,u,v,w;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(mp,-1,sizeof(mp));//��һ������ȫͼ
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&u,&v,&w);
            mp[u][v]=mp[v][u]=w;
        }
        printf("Scenario #%d:\n",cas);
        printf("%d\n\n",prim(1));
    }
    return 0;
}
*/

/*
���ֽⷨ
*/
