//���ֵ��С��
//˼����Ϊʲô�������������أ���Ϊ�����еĴ�Ҫ��С������̰�Ŀ϶�Ҫʹk����ѵ��ʸ����꣬
//��ô���ķ����϶��������k��·ʹ֮��ѣ�Ȼ�󸶵�k+1��·�ĳ��ȵ�Ǯ������������̰��˼·��Ȼ����ȷ�ġ�

//˼·���������ȶ��ֵ�k+1����·�ĳ���(����)���߽�ֵl��Ȼ��0��r��1000000(��Ŀ��˵���Ϊ1000000)��
//Ȼ��ؼ�������ж���ȷ�ԡ����ǿ��Ǽ����⣬���ڳ���С�ڶ��ֳ��Ĵ𰸵��߶Σ���Ϊ����Ҫ����Ǯ��
//���Կ��Խ���Ȩֵ������0;ͬ�����ڶ��ֵ�ֵ��·�������ǽ����ȿ���1(��ζ������Ҫʹ��1����ѵ��ʸ�)��
//so��������һ��spfa��������n������·�ĳ��ȣ��������k�����У���Сr��Χ��������;���С�ڣ����п��ܸ�С����Сl��Χ�������֡�
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
/*
����:n����,m��ȨֵΪw��˫���,����Ҫ��1�㵽��n��,
��k�����ͨ���ߵĻ���,��1����n������·���б�Ȩ���ߵ���Сֵ.
����:https://www.luogu.com.cn/problem/P1948
˼·:����+���·
*/

int n,m,k,cnt,head[N],vis[N],dis[N];

struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int Dijkstra(int s,int cost){
    priority_queue<pair<int,int> >Q;
    init(s);
    Q.push(make_pair(0,s));
    int u,v,w;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].w>cost) w=1;
            else w=0;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return dis[n]<=k;
}

int main(){
    int u,v,w,l=0,r=0;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
        r=max(r,w);
    }
    while(l<=r){
        int mid=(l+r)/2;
        if(Dijkstra(1,mid)) r=mid-1;//������Сֵ��� ������l=mid+1
        else l=mid+1;//������Сֵ��� ������r=mid-1
    }
    if(dis[n]!=INF) printf("%d",l);//������Сֵ��� ������r
    else printf("-1\n");
    return 0;
}
/*
//��Сֵ���
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,k,cnt,head[N],vis[N],dis[N];

struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int Dijkstra(int s,int cost){
    priority_queue<pair<int,int> >Q;
    init(s);
    Q.push(make_pair(0,s));
    int u,v,w;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].w>cost) w=1;
            else w=0;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return dis[n]<=k;
}

int main(){
    int u,v,w,l=0,r=0;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&k);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
        r=max(r,w);
    }
    while(l<=r){
        int mid=(l+r)/2;
        if(Dijkstra(1,mid)) l=mid+1;
        else r=mid-1;
    }
    if(dis[n]!=INF) printf("%d",r);
    else printf("-1\n");
    return 0;
}
*/

/*
//�ֲ�ͼ���·
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 10100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,k,cnt,head[N*1000],vis[N*1000];
ll dis[N*1000];

struct Node{
    int to,next;
    ll w;
}edge[(M*2*1000)<<1];

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
            //��ǰ·���бߵ����ֵ����֮ǰ����v��·���е����ֵС���ɳ����
            if(dis[v]>max(dis[u],edge[i].w)){
                dis[v]=max(dis[u],edge[i].w);
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
    for(int i=0;i<=k;i++)
        ans=min(ans,dis[n+n*i]);
    if(ans!=INF) printf("%lld",ans);
    else printf("-1");
    return 0;
}
*/
