#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f
using namespace std;

/*
����:n�����ͼ,�����s����̾���Ϊl�ĵ����ϵĵ�
�ж��ٸ�.
����:https://codeforces.ml/problemset/problem/144/D
˼·:����s�ĵ�ֱ�������·����,���ڱߵĴ�����Կ���
���ڱߵ����˵�u,v,���dis[u]<l dis[u]+w>l ,��˵����������
����һ������s����Ϊl.
*/

int n,m,l,cnt,head[N],dis[N],vis[N];
struct Node{
    int from,to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){from,to,head[from],w};
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
    int u,v,w,s,sum=0;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&s);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    scanf("%d",&l);
    spfa(s);
    for(int i=1;i<=n;i++)
        if(dis[i]==l) sum++;
    for(int i=0;i<cnt;i+=2){//��Ϊu->v v->u���ظ���,����+2�պ����������
        u=edge[i].from;
        v=edge[i].to;
        w=edge[i].w;
        /*
        ��Ϊdis[u]<l && dis[u]+w>l
        ���ǿ���u�Ķ˵�dis[u]+����ĳһ��x�ϱ�Ȩ�պõ���l,
        dis[v]+w-(l-dis[u])>l��ʾ����dis[v],u->v��x����v�����һ����
        ����һ��y,��dis[v]�й���,�����x y���غ�,���������ӵ���x��,
        ��Ϊ�������dis[v]��l�Ĺ�ϵ,�¸��жϾ��ǿ���dis[v]
        */
        if(dis[u]<l && dis[u]+w>l && dis[v]+w-(l-dis[u])>l)//ʵ�ʾ���dis[u]+dis[v]+w>2*l
            sum++;
        if(dis[v]<l && dis[v]+w>l && dis[u]+w-(l-dis[v])>l)//ͬ��
            sum++;
        //u->v���ϵ�һ�����dis[u] dis[v]�Ĺ��׸պ�����l,���������պ��غ�,����ֻ��һ����
        if(dis[u]<l && dis[v]<l && dis[u]+dis[v]+w==2*l)
            sum++;
    }
    printf("%d",sum);
    return 0;
}
