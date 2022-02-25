#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 50100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//˼ά����
/*
����:Լ��һ����N������.��M������������С�����ӡ�С������˫��ͨ�С�
ÿ������Լ��������1����������Nȥ����ţ������塣
ͨ��ÿ��С������Ҫ����һ����ʱ�䡣Լ��������������K��С����ʹ֮��Ϊ���ٹ�·��
�ڸ��ٹ�·�ϵ�ͨ�м�����˲����ɵģ����Ը��ٹ�·��ͨ��ʱ��Ϊ0��
�����Լ����������ЩС������������ʹ��ÿ���1����������N������������ʱ����̡�
����:https://www.luogu.com.cn/problem/P2939
˼·:����ֲ�ͼ���·
*/

int n,m,k,cnt,head[N*21],vis[N*21];
ll dis[N*21];

struct Node{
    int to,next;
    ll w;
}edge[(M*2*21)<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void Dijkstra(int s){
    priority_queue<pair<ll,int> >Q;
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
    int u,v;
    ll w,ans=INF;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        for(int i=0;i<=k;i++){
            addEdge(u+n*i,v+n*i,w);
            addEdge(v+n*i,u+n*i,w);
            if(i){
                addEdge(u+(i-1)*n,v+i*n,0);
                addEdge(v+(i-1)*n,u+i*n,0);
            }
        }
    }
    Dijkstra(1);
    for(int i=1;i<=k;i++)
        ans=min(ans,dis[n+n*i]);
    printf("%lld",ans);
    return 0;
}

/*
//״̬ö�� dis��ά��������
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 50100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,k,cnt,head[N],vis[N][21];
ll dis[N][21];

struct state{
    int v,cnt;
    ll dis;
    state(int v=0,ll dis=0,int cnt=0):v(v),dis(dis),cnt(cnt){}
    bool operator <(const state &x)const{
        return dis>x.dis;
    }
};

struct Node{
    int to,next;
    ll w;
}edge[M<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    for(int i=0;i<=k;i++)
        dis[s][i]=0;
}

void Dijkstra(int s){
    priority_queue<state>Q;
    init(s);
    Q.push(state(s,0,0));
    state tmp;
    int u,v,cnt;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v,cnt=tmp.cnt;
        Q.pop();
        if(vis[u][cnt]) continue;
        vis[u][cnt]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v][cnt]>dis[u][cnt]+edge[i].w){
                dis[v][cnt]=dis[u][cnt]+edge[i].w;
                Q.push(state(v,dis[v][cnt],cnt));
            }
            if(cnt<k && dis[v][cnt+1]>dis[u][cnt]){
                dis[v][cnt+1]=dis[u][cnt];
                Q.push(state(v,dis[v][cnt+1],cnt+1));
            }
        }
    }
}

int main(){
    int u,v;
    ll w,ans=INF;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    Dijkstra(1);
    for(int i=1;i<=k;i++)
        ans=min(ans,dis[n][i]);
    printf("%lld",ans);
    return 0;
}
*/
