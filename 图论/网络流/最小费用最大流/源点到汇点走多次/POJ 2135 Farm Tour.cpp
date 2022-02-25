#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 10010
#define INF 0x3f3f3f3f
using namespace std;
//ac 16ms EK�㷨 ��С������ Դ��->1->n->���
//��֪Ϊ�δ��� Դ������1,�������n,�ͻ����.
/*
����:����һ������ͼ,������һ����С��·����1��N�ٻص�1.�߲����ظ���.
�����ߵ���̾����Ƕ���.
����:http://poj.org/problem?id=2135
˼·:�������������������·,��Ϊ�����������ܻᵼ����Ȼ��һ��������
�������,���ڶ��ο��ܲ�ͨ,��ĳ����Ȩѡ�Ĺ���,���ǽ����һ��������С
��,��ȷ�Եò�����֤.���Կ��Կ��Ƿ�����,Դ��0,���n+1,Դ����1��������
Ϊ2,����Ϊ0�������,ע����Ϊ������ͼ,��2����.��ΪҪ��1�ߵ�n,�ٴ�n�ߵ�1,
��������������Ϊ2,����������ߵĹ���ת��Ϊ���������Ա�Ϊ�����������1��n.
n������������Ϊ2,����Ϊ0�������.�����u-v,Ҳ�ǽ�����Ϊ1,����Ϊw�����������.
�ܷ��������ɵõ���.
*/
int n,m,cnt,head[N],st,ed,incf[N],pre[N],dis[N],vis[N];
struct Edge{
    int to,next,cf,w;
}edge[M<<2];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    incf[s]=INF;
    pre[ed]=0;
    vis[s]=1;
}

int spfa(int s){
    queue<int> Q;
    init0(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w){
                pre[v]=i;
                dis[v]=dis[u]+edge[i].w;
                incf[v]=min(incf[u],edge[i].cf);
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return pre[ed];
}

int mcmf(){
    int sum=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed]*dis[ed];
    }
    return sum;
}

void init(){
    cnt=0;
    st=0,ed=n+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v,w;
    scanf("%d%d",&n,&m);
    init();
    addEdge(st,1,2,0);
    addEdge(n,ed,2,0);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,1,w);//��Ϊ������ͼ,���Խ�������
        addEdge(v,u,1,w);
    }
    printf("%d",mcmf());
    return 0;
}

/*
//ac 16ms dinic ��С������ Դ��->1->n->���
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 10010
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],st,ed,dis[N],vis[N];
struct Edge{
    int to,next,cf,w;
}edge[M<<2];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    memset(vis,0,sizeof(vis));
    vis[s]=1;
}

int spfa(int s){
    queue<int> Q;
    init0(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return dis[ed]!=INF;
}

int dfs(int u,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    vis[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!vis[v] && edge[i].cf>0 && dis[v] == dis[u]+edge[i].w){
            incf=dfs(v,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
            }
            if(!flow)
                break;
        }
    }
    return res;
}

int mcmf(){
    int sum=0,incf;
    while(spfa(st)){
        incf=dfs(st,INF);
        sum+=incf*dis[ed];
    }
    return sum;
}

void init(){
    cnt=0;
    st=0,ed=n+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v,w;
    scanf("%d%d",&n,&m);
    init();
    addEdge(st,1,2,0);
    addEdge(n,ed,2,0);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,1,w);//��Ϊ������ͼ,���Խ�������
        addEdge(v,u,1,w);
    }
    printf("%d",mcmf());
    return 0;
}
*/
