#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 50100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//Dijkstra 657ms
/*
����:n���ڵ��ͼ,ÿ���㶼�е�Ȩ,�����֮���б�Ȩ,����Ҫ����һ����ʹ�û�����С,
����һ���ߵĻ��Ѷ���Ϊ:һ���ߵ�Ȩ*�������������ж˵��Ȩ�ĺ�,
�������Ļ���Ϊ���бߵĻ���,1�ڵ��Ϊ���ڵ�,����Ҫ��ȡ��������������С����.
����:http://poj.org/problem?id=3013
˼·:���ȷ�������2:
�󻨷ѵ����:
sum=4*40+3*50+2*60+3*(20+40+50+60)+2*30+1*(10+20+30+40+50+60)
=10*1+20*(1+3)+30*(2+1)+40*(4+1+3)+50*(3+1+3)+60*(1+2+3)
=10+80+90+320+350+360
=1210
���Է���:sum=10*1+20*(1+3)+30*(2+1)+40*(4+1+3)+50*(3+1+3)+60*(1+2+3)
�ⲻ����ÿ��������·*�õ��Ȩ���ۼӺ���.
ʵ������С�ܻ���=ÿ����(u,v)*v�������и����ĵ�Ȩ
                =(��ȡ����ʽ(��ͬ��Ȩ))ÿ����ĵ�Ȩ*�Ӹ��ڵ㵽�õ��ÿ���ߵı�Ȩ�ۼӺ�
                =ÿ����*�õ㵽���������·
��Ȼԭͼ����������ͨͼ,����ֱ����һ����,����ʵ�ʲ��ÿ��ǹ���һ��������,
��Ϊ��ʹ���������С��,����ֻ�ܵõ���Ȩ����С,��Ӱ����õ����ز����Ǳ�Ȩ,
�Ǳ�Ȩ�͵�Ȩ�ĳ˻�,������С�����ܲ�Ψһ,���ǲ�ͬ����С���������� ���ݱ�Ȩ��������Ȩ��,
���ܼ�ʹ������С��,����Ҳ��һ��,��Ϊ������̬����ı�Ȩ�͵�Ĺ�ϵ��Ҳ��Ӱ�����.
�����ݱߵ������еĵ�Ȩ�ͳ��Ա�Ȩ,ʵ������������������·*��Ȩ������С����

*/

int n,m,cnt,head[N],vis[N];
ll dis[N],val[N],sum;

struct Node{
    int to,next;
    ll w;
}edge[N<<1];

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
    init(s);
    priority_queue<pair<ll,int> >Q;
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
    int T,u,v;
    ll w;
    scanf("%d",&T);
    while(T--){
        sum=cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%lld",&val[i]);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        Dijkstra(1);
        int flag=0;
        for(int i=2;i<=n;i++){
            if(dis[i]==INF){//������ͨ,��������No Answer
                flag=1;
                break;
            }
            sum+=dis[i]*val[i];
        }
        if(flag)
            printf("No Answer\n");
        else
            printf("%lld\n",sum);
    }
    return 0;
}

/*
spfa 657ms
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 50100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N],vis[N];
ll dis[N],val[N],sum;

struct Node{
    int to,next;
    ll w;
}edge[N<<1];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void spfa(int s){
    init(s);
    queue<int> Q;
    Q.push(s);
    vis[s]=1;
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
    int T,u,v;
    ll w;
    scanf("%d",&T);
    while(T--){
        sum=cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%lld",&val[i]);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        spfa(1);
        int flag=0;
        for(int i=2;i<=n;i++){
            if(dis[i]==INF){
                flag=1;
                break;
            }
            sum+=dis[i]*val[i];
        }
        if(flag)
            printf("No Answer\n");
        else
            printf("%lld\n",sum);
    }
    return 0;
}

*/
