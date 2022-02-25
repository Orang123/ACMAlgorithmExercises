#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//Dijkstra 421ms
/*
����:n���ڵ㹹�ɵ�ͼ,ÿ���ڵ㶼����һ�����,�������ڵĲ��֮���
������໥���ʴ���Ϊc,��x�����Դ���c����x+1���е�Ԫ��,x+1��ͬ����
�Դ���c����x���е�Ԫ��.���1��n����С���ۡ�
����:http://acm.hdu.edu.cn/showproblem.php?pid=4725
˼·:�������ڲ�֮��Ԫ�ؿ����໥����,�϶���������Ԫ�ر�������,
���԰�ÿ��(x)���2����,һ�����f+2*n,һ������f+n,
�������ò������Ԫ��,�ò������Ԫ���������,��ȨΪ0.
����x�����x+1��Ԫ�� x+n->(x+1)+2*n x���������x+1�����
����x+1�����x��Ԫ�� x+1+n->x+2*n x+1���������x�����
���϶��������.˫��߻ᵼ��,ÿ���Ԫ���໥֮����ʴ���Ϊ0.
*/

int n,m,cnt,head[3*N],vis[3*N];
ll dis[3*N],c;
struct Node{
    int to,next;
    ll w;
}edge[6*N];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    cnt=0;
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
    memset(dis,INF,sizeof(dis));
    dis[1]=0;
}

void Dijkstra(int s){
    priority_queue<pair<ll,int> >Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        //��n���Ѿ������� ��,dis[n]�Ѿ�����С(Dijkstra��̰�ĵ�����ǰ������С�ľ���),���Բ����ٸ�����,������
        if(u == n) return;
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
    int T,u,v,f,cas=0;
    ll w;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d%lld",&n,&m,&c);
        init();
        for(int i=1;i<=n;i++){
            scanf("%d",&f);
            addEdge(i,f+n,0);//i�������f+n
            addEdge(f+2*n,i,0);//���f+2*n����i
        }
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        /*
        ʵ�ʲ������ܻ��жϲ�,���߸����ﲻ��n��,
        ��ȻҲ����������������,���Ȿ����������
        ��û��ʲô������,Ҳ��Ӱ����������.
        */
        for(int i=1;i<n;i++){
            addEdge(i+n,i+1+2*n,c);//i���������i+1�����
            addEdge(i+1+n,i+2*n,c);//i+1���������i�����
        }
        Dijkstra(1);
        if(dis[n] == INF) dis[n] =-1;
        printf("Case #%d: %lld\n",cas,dis[n]);
    }
    return 0;
}

/*
x������ͳ��㻹�ɱ�ʾ�� 2*x-1+n,2*x+n
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[3*N],vis[3*N];
ll dis[3*N],c;
struct Node{
    int to,next;
    ll w;
}edge[6*N];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    cnt=0;
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
    memset(dis,INF,sizeof(dis));
    dis[1]=0;
}

void Dijkstra(int s){
    priority_queue<pair<ll,int> >Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(u == n) return;
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
    int T,u,v,f,cas=0;
    ll w;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d%lld",&n,&m,&c);
        init();
        for(int i=1;i<=n;i++){
            scanf("%d",&f);
            addEdge(i,2*f+n,0);
            addEdge(2*f-1+n,i,0);
        }
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        for(int i=1;i<n;i++){
            addEdge(2*i+n,2*(i+1)-1+n,c);
            addEdge(2*(i+1)+n,2*i-1+n,c);
        }
        Dijkstra(1);
        if(dis[n] == INF) dis[n] =-1;
        printf("Case #%d: %lld\n",cas,dis[n]);
    }
    return 0;
}

*/
/*
spfa 889ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[3*N],vis[3*N];
ll dis[3*N],c;
struct Node{
    int to,next;
    ll w;
}edge[6*N];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    cnt=0;
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
    memset(dis,INF,sizeof(dis));
    dis[1]=0;
}

void spfa(int s){
    queue <int>Q;
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
    int T,u,v,f,cas=0;
    ll w;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d%lld",&n,&m,&c);
        init();
        for(int i=1;i<=n;i++){
            scanf("%d",&f);
            addEdge(i,f+n,0);
            addEdge(f+2*n,i,0);
        }
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        for(int i=1;i<n;i++){
            addEdge(i+n,i+1+2*n,c);
            addEdge(i+1+n,i+2*n,c);
        }
        spfa(1);
        if(dis[n] == INF) dis[n] =-1;
        printf("Case #%d: %lld\n",cas,dis[n]);
    }
    return 0;
}
*/

/*
��һ������x������x+1����㹲��һ���������,�ȽϽ�Լ�ռ�,Ҳû�й���û�еĶϲ�ı߼�.
https://blog.csdn.net/zcmartin2014214283/article/details/52775288
#include <iostream>
#include <string.h>
#include <queue>
#include <stdio.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int maxn=200005;//���һ����200000����Ϊ����������һ��
const int maxm=800010;
struct Edge
{
    int to,next,w;
} edge[maxm];
int tot;
int head[maxn];
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int w)
{
    edge[tot].to=v;
    edge[tot].w=w;
    edge[tot].next=head[u];
    head[u]=tot++;
}
int d[maxn*2];
bool vis[maxn*2];
struct node
{
    int u,w;
    node(int u,int d):u(u),w(d) {}
};
bool operator < (node a,node b)
{
    return a.w > b.w;
}
void  dijk(int s,int n)
{
    memset(vis,0,sizeof(vis));
    priority_queue<node> que;
    for(int i=0; i<=n; i++) d[i]=INF;
    d[s]=0;
    que.push(node(s,0));
    while(!que.empty())
    {
        node tmp = que.top();
        que.pop();
        int u=tmp.u;
        if(vis[u]) continue;
        vis[u]=true;
        for(int e=head[u]; e!=-1; e=edge[e].next)
        {
            int v=edge[e].to,w=edge[e].w;
            if(vis[v]) continue;
            if(d[u]+w<d[v])
            {
                d[v]=d[u]+w;
                que.push(node(v,d[v]));
            }
        }
    }
}
int a[maxn*2];
int main()
{
    //ios::sync_with_stdio(false);
    int T,n,m,t,u,v,w;
    int cases=1;
    scanf("%d",&T);
    //cin>>T;
    while(T--)
    {
        init();
        memset(a,0,sizeof(a));
        memset(d,0,sizeof(d));
        memset(vis,0,sizeof(vis));
        //cin>>n>>m>>t;
        scanf("%d%d%d",&n,&m,&t);
        int val;
        for(int i=1;i<=n;i++)
            {
                //cin>>val;
                scanf("%d",&val);
                a[i]=val;//a[i]//��ʾi�Ĳ�����val
                vis[val]=1;//�����������������Ƿ��������ֹ�
            }
            for(int i=1;i<=n;i++)
            {
                if(a[i]==1)//����ǵ�һ�㣬��ֻ��������һ��
                {
                    addedge(a[i]+n,i,0);
                    if(vis[a[i]+1]&&a[i]<n)//ע������һ����a[i]+1����ΪҪ��ʾ����������һ��
                // ���д����a[i+1]�Ļ���ʾ������i����һ�������һ�㣬�����ǲ��Եģ�ֻ�����ڵĲ㽨��
                        addedge(i,a[i]+n+1,t);
                }
                else if(a[i]==n)//����ǵ�n�㣬��ֻ��������һ��
                {
                    addedge(a[i]+n,i,0);
                    if(vis[a[i]-1]&&a[i]>1)
                        addedge(i,a[i]+n-1,t);
                }
                else
                {
                    addedge(a[i]+n,i,0);
                    if(vis[a[i]+1]&&a[i]<n)
                        addedge(i,a[i]+n+1,t);
                      if(vis[a[i]-1]&&a[i]>1)
                        addedge(i,a[i]+n-1,t);
                }
            }
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            //cin>>u>>v>>w;
            addedge(u,v,w);
            addedge(v,u,w);
        }
        dijk(1,n*2);
        if(d[n]==INF)
            d[n]=-1;
       // cout<<"Case #"<<cases++<<": ";
        //cout<<d[n]<<endl;
        printf("Case #");
        printf("%d",cases++);
        printf(": ");
        printf("%d\n",d[n]);

    }
    return 0;
}


*/
