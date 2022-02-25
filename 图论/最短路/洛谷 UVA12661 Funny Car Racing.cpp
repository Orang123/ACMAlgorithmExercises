#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 330
#define M 50100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

/*
����:n������Ĺ��ɵ�����(����),ÿ�������и�����ʱ��͹ر�ʱ��,
����ֻ���ڿ���ʱ����һ����ͨ������,ͨ��ÿ��������ʱ�䲻ͬ,
���s���㵽t������Ҫ�����ʱ��.
����:https://www.luogu.com.cn/problem/UVA12661
˼·:��Ϊ��ÿ�������п���ʱ��a�͹ر�ʱ��b,�����õ�ǰ����ʱ���(a+b)
ȡģ,������֪���ھ�������ô����ʱ���,��ǰ������Ҫͨ�����������ڿ���
�͹رյ�ʲôʱ���,����������ж�,һ�ֵ�ǰʱ��+ͨ������ʱ��<=����ʱ��,
��˴�ͨ��������ʱ�����ͨ��(������ʱ��),����ǰʱ��+ͨ������ʱ��>����ʱ��,
������ͨ��������ʱ��(����ʱ��-��ǰʱ��+�ر�ʱ��(��Щ����Ҫ�ȴ�ʱ��)+ͨ��������ʱ��).
����ֻ��һ���Ե�ͨ������.
*/

int n,m,cnt,head[N],vis[N];
ll dis[N];

struct Node{
    int to,next;
    ll a,b,w;
}edge[M];

void addEdge(int from,int to,ll a,ll b,ll w){
    edge[cnt]=(Node){to,head[from],a,b,w};
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
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            ll t=dis[u]%(edge[i].a+edge[i].b);
            ll w;
            //��ǰʱ��+ͨ������ʱ��<=����ʱ��
            if(t+edge[i].w<=edge[i].a)
                w=edge[i].w;//ʱ�����ͨ��������ʱ��
            else//��ǰʱ��+ͨ������ʱ��>����ʱ��
            //ʱ����ǿ���ʱ��-��ǰʱ��+�ر�ʱ��(��Щ����Ҫ�ȴ�ʱ��)+ͨ��������ʱ��
                w=edge[i].w+(edge[i].a-t)+edge[i].b;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int s,t,u,v,cas=0;
    ll a,b,w;
    while(scanf("%d%d%d%d",&n,&m,&s,&t)!=EOF){
        cas++;
        cnt=0;
        memset(head,-1,sizeof(head));
        while(m--){
            scanf("%d%d%lld%lld%lld",&u,&v,&a,&b,&w);
            if(w<=a)//��ͨ��������ʱ��ȿ���ʱ�仹��ʱ,�����߾Ͳ�����,������,�����wa
                addEdge(u,v,a,b,w);
        }
        spfa(s);
        printf("Case %d: %lld\n",cas,dis[t]);
    }
    return 0;
}
