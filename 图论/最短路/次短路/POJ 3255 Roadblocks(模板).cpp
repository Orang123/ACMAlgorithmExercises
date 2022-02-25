#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 5100
#define M 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//spfa����
/*
����:����1�ڵ��������n�ڵ�Ĵζ�·,ע��ζ�·һ���ϸ�������·.
����:http://poj.org/problem?id=3255
˼·:spfa,dis1������·,dis2���ζ�·,ÿ���ɳڽڵ�ʱ,ͬʱ�������·�ʹζ�·.
�����������
1.���õ����·+��һ���߱ȵ��¸�������·�̣�������¸�������·��ͬʱ���´ζ�·Ϊԭ���·
2.���õ�ζ�·+��һ���߱ȵ��¸���Ĵζ�·�̣�������¸���Ĵζ�·
3.���õ����·+��һ���߱ȵ��¸�������·��ͬʱ���¸���Ĵζ�·�̣�������¸���Ĵζ�·
����֮����Ҫ���������,����if�ж�����Ϊspfa�����Զ��¼����һ����,��Dijkstra ��;�����ͬʱ��ӵ�,
������뱾��Ͱ��������·�ʹζ�·�Ŀ�����,���if else if2���ж��͹�.
*/

int n,m,cnt,head[N],vis[N];
ll dis1[N],dis2[N];
struct Node{
    int to,next;
    ll w;
}edge[M<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    cnt=0;
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        dis1[i]=dis2[i]=INF;
    //dis2[s]�ζ�·�������ó�0,��Ϊ�ζ�·�Ǹ��ݺ����·�Ƚϵó���,����ʼ��Ϊ0,����ֱ����ζ�·��Զ����0,�������ٸ�����
    dis1[s]=0;
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
            //���1 �������·
            if(dis1[v]>dis1[u]+edge[i].w){
                dis2[v]=dis1[v];
                dis1[v]=dis1[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
            //���2 �ζ�·���´ζ�· ��Ϊ�п��ܵ���v�����·ֻ��һ��,��ô�ζ�·ֻ���ɵ���v��ϴ�Ĵζ�·����
            if(dis2[v]>dis2[u]+edge[i].w){
                dis2[v]=dis2[u]+edge[i].w;
                /*
                ����ζ�·���º�Ľ��ͬ��ҲҪ��Ϊ�µ�·��ȥ���º���ڵ�Ĵζ�·,
                �������v��֮ǰ�Ѿ�����������,��Ҫ�������.
                ��Ϊ����ڵ�Ĵζ�·��һ������ͨ��ǰ��ڵ�����·��ø���(����û��������֧,
                ������ʱ�ʼ��һ���ζ�·��ͨ��ǰ������·���µ�),ǰ��Ĵζ�·Ҳ�п��ܻ�
                ���º���ڵ�Ĵζ�·.
                */
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
            //���3 ���·(�ȵ�ǰ���·��,�ȵ�ǰ�ζ�·С)���´ζ�·
            if(dis2[v]>dis1[u]+edge[i].w && dis1[u]+edge[i].w>dis1[v]){
                dis2[v]=dis1[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v;
    ll w;
    scanf("%d%d",&n,&m);
    init(1);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    spfa(1);
    printf("%lld\n",dis2[n]);
    return 0;
}

/*
//Dijkstra ���������������
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 5100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],vis[N][2],dis[N][2];

struct state{
    int v,dis,flag;
    state(int dis=0,int v=0,int flag=0):dis(dis),v(v),flag(flag){}
    bool operator < (const state &x)const{
        return dis>x.dis;
    }
};

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
    dis[s][0]=0;
}

int Dijkstra(int s){
    init(s);
    priority_queue<state> Q;
    Q.push(state(0,s,0));
    int u,v,flag;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v,flag=tmp.flag;
        Q.pop();
        if(u == n && flag) return dis[u][flag];
        if(vis[u][flag]) continue;
        vis[u][flag]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v][0]>tmp.dis+edge[i].w){
                if(dis[v][0]!=INF){
                    dis[v][1]=dis[v][0];
                    Q.push(state(dis[v][1],v,1));
                }
                dis[v][0]=tmp.dis+edge[i].w;
                Q.push(state(dis[v][0],v,0));
            }
            else if(dis[v][1]>tmp.dis+edge[i].w){
                dis[v][1]=tmp.dis+edge[i].w;
                Q.push(state(dis[v][1],v,1));
            }
        }
    }
    return -1;
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    printf("%d",Dijkstra(1));
    return 0;
}
*/

/*
//Dijkstra  �Ƽ��Լ������� ˼·������ͳһ˼·Ҫ������һ�� ������
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 5100
#define M 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N];
ll dis1[N],dis2[N];
struct Node{
    int to,next;
    ll w;
}edge[M<<1];
struct state{
    ll dis;
    int v;
    state(ll dis=0,int v=0):dis(dis),v(v){}
    bool operator <(const state &x)const{
        return dis>x.dis;
    }
};

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        dis1[i]=dis2[i]=INF;
    //dis2[s]�ζ�·�������ó�0,��Ϊ�ζ�·�Ǹ��ݺ����·�Ƚϵó���,����ʼ��Ϊ0,����ֱ����ζ�·��Զ����0,�������ٸ�����
    dis1[s]=0;
}

void Dijkstra(int s){
    priority_queue <state>Q;
    Q.push(state(0,s));
    int u,v;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v;
        Q.pop();
        //������u��Ĵζ�·�Ѿ������ܸ�Сʱ,�Ͳ�����ȥ�ɳ���
        //�����п��ܱ������ڴζ�·,������������ظ��ı��ɳڳ��µĴζ�·��,���⹹�������
        if(tmp.dis>dis2[u]) continue;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //����tmp.dis+edge[i].w�������ά���ĵ�ǰ��С��·��ֵ,�п�����֮ǰ�ڵ����·Ҳ�п����Ǵζ�·
            //��tmp.dis+edge[i].w�����·,���ڸ������·��֮ǰ,���Ƚ�֮ǰ�����·����Ϊ�µĴζ�·,Ҳ����ֱ���������´ζ�·
            //��tmp.dis+edge[i].w�Ǵζ�·,��ֻ�ܸ��º����ڵ�Ĵζ�·
            //���1 �������·
            if(dis1[v]>tmp.dis+edge[i].w){
                if(dis1[v]!=INF){
                    dis2[v]=dis1[v];//�Ƚ�֮ǰ�����·����Ϊ�µĴζ�·,�ٸ��µ�ǰ�µ����·
                    Q.push(state(dis2[v],v));
                }
                dis1[v]=tmp.dis+edge[i].w;
                Q.push(state(dis1[v],v));
            }
            //���2 �ζ�·�����·���´ζ�·
            //���tmp.dis+edge[i].w�п��ܱ�����Ǵζ�·,Ҳ�п��ܱ���������·���Ǳ�dis1[v]��,��ȴ��dis2[v]С
            else if(dis2[v]>tmp.dis+edge[i].w){
                dis2[v]=tmp.dis+edge[i].w;
                Q.push(state(dis2[v],v));//���ζ�·ѹ�����,���ܸ��º���ڵ�Ĵζ�·
            }
        }
    }
}

int main(){
    int u,v;
    ll w;
    scanf("%d%d",&n,&m);
    init(1);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    Dijkstra(1);
    printf("%lld\n",dis2[n]);
    return 0;
}
*/

/*
//Dijkstra���ζ�· ����ͳһ�汾 ���´ζ�·��������׻������Ƽ�
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 5100
#define M 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N];
ll dis1[N],dis2[N];
struct Node{
    int to,next;
    ll w;
}edge[M<<1];
struct state{
    ll dis;
    int v;
    state(ll dis=0,int v=0):dis(dis),v(v){}
    bool operator <(const state &x)const{
        return dis>x.dis;
    }
};

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        dis1[i]=dis2[i]=INF;
    dis1[s]=0;
}

void Dijkstra(int s){
    priority_queue <state>Q;
    Q.push(state(0,s));
    int u,v;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v;
        Q.pop();
        //������u��Ĵζ�·�Ѿ������ܸ�Сʱ,�Ͳ�����ȥ�ɳ���
        //�����п��ܱ������ڴζ�·,������������ظ��ı��ɳڳ��µĴζ�·��,���⹹�������
        //����tmp.dis=dis2[u]����� eg:1->2 2�����߸ո���1�Ĵζ�·,��ʱtmp.dis==dis2[1]����Ҫ������ζ�·ȥ����2�Ĵζ�·
        if(tmp.dis>dis2[u]) continue;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            //����d�������ά���ĵ�ǰ��С��·��ֵ,�п�����֮ǰ�ڵ����·Ҳ�п����Ǵζ�·
            //��d�����·,����ܸ������·,Ҳ�ܸ��´ζ�·
            //��d�Ǵζ�·,��ֻ�ܸ��º����ڵ�Ĵζ�·
            ll d=tmp.dis+edge[i].w;
            //���1 �������· ͬʱ����d��ԭ�����·
            if(dis1[v]>d){
                swap(dis1[v],d);
                Q.push(state(dis1[v],v));
            }
            //���2 �ζ�·�����·���´ζ�·
            //���d�п��ܱ�����Ǵζ�·,Ҳ�п�����ԭ�ȵı��滻�����·,Ҳ�п��ܱ���������·����û��dis1[v]С
            if(dis2[v]>d && d>dis1[v]){
                dis2[v]=d;
                Q.push(state(dis2[v],v));//���ζ�·ѹ�����,���ܸ��º���ڵ�Ĵζ�·
            }
        }
    }
}

int main(){
    int u,v;
    ll w;
    scanf("%d%d",&n,&m);
    init(1);
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    Dijkstra(1);
    printf("%lld\n",dis2[n]);
    return 0;
}
*/

/*
�����ⷨ ö��·���Ŀ��������� Ч��Ҫ��һЩ ���������·(һ��1��ʼ,һ��n��ʼ)
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 5100
#define M 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N],vis[N];
ll dis1[N],dis2[N],ans=INF;
struct Node{
    int to,next;
    ll w;
}edge[M<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    cnt=0;
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        dis1[i]=dis2[i]=INF;
    dis1[1]=0;
    dis2[n]=0;
}

void spfa(int s,ll *dis){
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
    int u,v;
    ll w;
    scanf("%d%d",&n,&m);
    init();
    while(m--){
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    spfa(1,dis1);//����1->v�����·dis1
    spfa(n,dis2);//����n->v�����·dis2
    for(int u=1;u<=n;u++){//ö��ÿ������Ϊ�м�ָ�ߵ����,ʵ�ʾ���ö������·�� ѡ������·�������·��������С��ֵ
        //Ҳ����ֻö��dis1[u]+dis2[u],��ö�ٷָ��,��������1->2������·���ζ�·�Ͳ�������.
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].to;//ö����һ���ָ��
            //1->n��·�������� dis1[1->u]+d[u->v]+dis2[v->n]
            //����1->2���ֵ��������,��u=2ʱ ��2->1��������ߵĴ���,����sum=dis1[1->2]+d[2->1]+dis2[2->1]=3,�պ��Ǵζ�·����Ϊ3�����·��1->2����Ϊ1
            ll sum=dis1[u]+edge[i].w+dis2[v];
            if(sum>dis1[n] && sum<ans)//ֻҪ�����·С,��֮ǰ��¼�Ĵζ�·��,�͸���
                ans=sum;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
*/

/*
A*�����ⷨ https://blog.csdn.net/algzjh/article/details/77542212 ��û��
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
typedef long long LL;
const LL INF=1e18;
const int MAXN=1e5+5;
int head[MAXN],head1[MAXN];
LL dis[MAXN];
bool vis[MAXN];
int n,m,tot,st,en,k;

struct Edge
{
    int u,v,nxt,nxt1;
    LL c;
    Edge(){}
    Edge(int _u,int _v,LL _c):u(_u),v(_v),c(_c){}
}e[MAXN*2];

struct qnode
{
    int v;
    LL c;
    qnode(){}
    qnode(int _v,LL _c):v(_v),c(_c){}
    bool operator < (const qnode& rhs) const
    {
        return c+dis[v]>rhs.c+dis[rhs.v];
    }
};

void addedge(int u,int v,LL c)
{
    e[tot]=Edge(u,v,c);
    e[tot].nxt=head[u];head[u]=tot;
    e[tot].nxt1=head1[v];head1[v]=tot++;
}

void dij(int src)
{
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;i++) dis[i]=INF;
    dis[src]=0;
    priority_queue<qnode> que;
    que.push(qnode(src,0));
    while(!que.empty())
    {
        qnode pre=que.top(); que.pop();
        if(vis[pre.v]) continue;
        vis[pre.v]=true;
        for(int i=head1[pre.v];i!=-1;i=e[i].nxt1)
        {
            if(dis[e[i].u]>dis[pre.v]+e[i].c)
            {
                dis[e[i].u]=dis[pre.v]+e[i].c;
                que.push(qnode(e[i].u,0));
            }
        }
    }
}

LL a_star(int src)
{
    priority_queue<qnode> que;
    que.push(qnode(src,0));
    k--;
    while(!que.empty())
    {
        qnode pre=que.top();que.pop();
        if(pre.v==en)
        {
            if(k) k--;
            else return pre.c;
        }
        for(int i=head[pre.v];i!=-1;i=e[i].nxt)
            que.push(qnode(e[i].v,pre.c+e[i].c));
    }
    return -1;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));
        memset(head1,-1,sizeof(head1));
        tot=0;
        for(int i=0;i<m;i++)
        {
            int u,v;LL c;
            scanf("%d%d%lld",&u,&v,&c);
            addedge(u,v,c);
            addedge(v,u,c);
        }
        st=1,en=n;k=2;
        dij(en);
        if(st==en) k++;
        printf("%lld\n",a_star(st));
    }
    return 0;
}
*/

