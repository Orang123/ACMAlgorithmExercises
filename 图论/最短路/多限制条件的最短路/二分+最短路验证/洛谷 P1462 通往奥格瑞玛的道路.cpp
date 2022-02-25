#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 10100
#define M 50100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//���ֵ��С��
/*
����:n������,m��˫��·,ÿ����·����Ҫ����һ��Ѫ��,
ÿ�����о���ʱ,����Ҫ��һ������,����һ����ʼѪ��,���
1��n��·���������ķ������ֵ�����Сֵ�Ƕ���.
����:https://www.luogu.com.cn/problem/P1462
˼·:���ַ���,���·��֤�ڳ�ʼѪ���������Ƿ��ܵ���n��.
*/

int n,m,cnt,head[N],vis[N],a[N],c[N];
ll dis[N],b;

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
    dis[s]=0;
}

int Dijkstra(int s,int cost){
    init(s);
    priority_queue<pair<ll,int> > Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        if(u == n) break;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(a[v]>cost) continue;//����ȶ��ֵķ��ø�����
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    if(dis[n]<=b) return 1;
    else return 0;
}

int main(){
    int u,v;
    ll w;
    memset(head,-1,sizeof(head));
    scanf("%d%d%lld",&n,&m,&b);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        c[i]=a[i];
    }
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    if(!Dijkstra(1,INF)){
        printf("AFK\n");
        return 0;
    }
    sort(c+1,c+n+1);//����ÿ�����з���,���з��õ��������
    int l=1,r=n;
    while(l<=r){
        int mid=(l+r)/2;
        //˵���ܵ���n��,˵�����ֵķ���ƫ��,�ٱ�С��
        //Dijk����1,���������Ǽ�С,����ֵ�ĵڶ��������Ҫ���������С
        //�������ֵ��С��,�ڶ���������С��,������С�ұ߽�,��С,��֮������߽�
        if(Dijkstra(1,c[mid])) r=mid-1;//������Сֵ���������l=mid+1
        //˵�����ܵ���n��,˵�����ֵķ���ƫС,�ٱ���
        else l=mid+1;//������Сֵ���������r=mid-1
    }
    printf("%d",c[l]);
    return 0;
}
/*
//��֮��Ӧ����Сֵ���
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 10100
#define M 50100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N],vis[N],a[N],c[N];
ll dis[N],b;

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
    dis[s]=0;
}

int Dijkstra(int s,int cost){
    init(s);
    priority_queue<pair<ll,int> > Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        if(u == n) break;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(a[v]>cost) continue;//����ȶ��ֵķ��ø�����
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    if(dis[n]<=b) return 1;
    else return 0;
}

int main(){
    int u,v;
    ll w;
    memset(head,-1,sizeof(head));
    scanf("%d%d%lld",&n,&m,&b);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        c[i]=a[i];
    }
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    if(!Dijkstra(1,INF)){
        printf("AFK\n");
        return 0;
    }
    sort(c+1,c+n+1);//����ÿ�����з���,���з��õ��������
    int l=1,r=n;
    while(l<=r){
        int mid=(l+r)/2;
        //˵���ܵ���n��,˵�����ֵķ���ƫ��,�ٱ���
        if(Dijkstra(1,c[mid])) l=mid+1;
        //˵�����ܵ���n��,˵�����ֵķ���ƫС,�ٱ�С��
        else r=mid-1;
    }
    printf("%d",c[l]);
    return 0;
}
*/
