#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 5500
#define INF 0x3f3f3f3f
using namespace std;
//ac 63ms EK ��С������ Դ��(0)->1->�����(���)->n*n->���(n*n*2+1) ���ñ�ȨΪ��
//ò���д�dp���ǵ�,�����Ǹ�̰�ĵĴ���˼·
/*
����:��һ��N*N�ķ���,��[1,1]��[n,n]��K��,�߹�ÿ����������������
(ÿ�������ʼ����һ���Ǹ���),Ȼ����������������Ϊ0.���ȡ�õ�����ֵ.
����:http://poj.org/problem?id=3422
˼·:��С���������.���ø�ֵȨ,��С����ȡ������.
��[1,1]��[n,n,]Ҫ��k��,ÿ�����ϵ���ֵֻ��ȡһ��,�ڶ��ξ���û�з���,
���Խ�i��j�еĵ���Ϊ���(i-1)*n+j�ͳ���(i-1)*n+j+n*n,��(i-1)*n+j��(i-1)*n+j+n*n
��������,һ��������Ϊ1,����Ϊ[i,j]���ϵ���ֵ,����Ϊ����,��ʾ��ֵֻ��ȡһ��,
��һ��������ΪINF,����Ϊ0,������Ծ����õ���,���ڶ��ξ���û�е÷�.Դ��Ϊ0,
���Ϊn*n*2+1,Դ����1������Ϊk,����Ϊ0�ı�,����Ҫ��k��,n*n*2����������Ϊk,
����Ϊ0�ı�,������k��.�ܷ�����,���ȡ������.
*/
int st,ed,cnt,head[N];
int n,k,dis[N],incf[N],pre[N],vis[N],mp[60][60];
struct Edge{
    int to,next,cf,w;
}edge[N*N];

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
                incf[v]=min(incf[u],edge[i].cf);
                dis[v]=dis[u]+edge[i].w;
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
    st=0,ed=n*n*2+1;
    memset(head,-1,sizeof(head));
}

int main(){
    scanf("%d%d",&n,&k);
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            scanf("%d",&mp[i][j]);
    }
    addEdge(st,1,k,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            addEdge((i-1)*n+j,(i-1)*n+j+n*n,1,-mp[i][j]);//����Ϊ��
            addEdge((i-1)*n+j,(i-1)*n+j+n*n,INF,0);
            if(j<n)
                addEdge((i-1)*n+j+n*n,(i-1)*n+j+1,INF,0);
            if(i<n)
                addEdge((i-1)*n+j+n*n,i*n+j,INF,0);
        }
    }
    addEdge(n*n*2,ed,k,0);
    printf("%d",-mcmf());
    return 0;
}

/*
//ac 79ms EK�㷨 ������ ���ö�Ϊ����,�޸�spfa�ж�����dis[v]<dis[u]+edge[i].w ���������
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 5500
#define INF 0x3f3f3f3f
using namespace std;

int st,ed,cnt,head[N];
int n,k,dis[N],incf[N],pre[N],vis[N],mp[60][60];
struct Edge{
    int to,next,cf,w;
}edge[N*N];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    for(int i=0;i<N;i++)
        dis[i]=-INF;//��ֵ������,��ΪԴ�������ķ���Ϊ0,Ҳ�����ʵ������·����Ϊ�������
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
            //����·�ĺ���������,����������,����cfһ��<=0,�����ܻ�ȥ������ѭ��
            if(edge[i].cf>0 && dis[v]<dis[u]+edge[i].w){//���������
                pre[v]=i;
                incf[v]=min(incf[u],edge[i].cf);
                dis[v]=dis[u]+edge[i].w;
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
    st=0,ed=n*n*2+1;
    memset(head,-1,sizeof(head));
}

int main(){
    scanf("%d%d",&n,&k);
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            scanf("%d",&mp[i][j]);
    }
    addEdge(st,1,k,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            addEdge((i-1)*n+j,(i-1)*n+j+n*n,1,mp[i][j]);//����Ϊ��
            addEdge((i-1)*n+j,(i-1)*n+j+n*n,INF,0);
            if(j<n)
                addEdge((i-1)*n+j+n*n,(i-1)*n+j+1,INF,0);
            if(i<n)
                addEdge((i-1)*n+j+n*n,i*n+j,INF,0);
        }
    }
    addEdge(n*n*2,ed,k,0);
    printf("%d",mcmf());
    return 0;
}
*/

/*
//ac 79ms dinic ������ ��� ���ñ�ȨΪ��,�����С���� ȡ��
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 5500
#define INF 0x3f3f3f3f
using namespace std;

int st,ed,cnt,head[N];
int n,k,dis[N],incf[N],pre[N],vis[N],mp[60][60];
struct Edge{
    int to,next,cf,w;
}edge[N*N];

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
    return dis[ed] != INF;
}

int dfs(int u,int flow){
    if(u == ed)
        return flow;
    vis[u]=1;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!vis[v] && edge[i].cf>0 && dis[v] == dis[u]+edge[i].w){
            incf=dfs(v,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
                if(!flow)
                    break;
            }
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
    st=0,ed=n*n*2+1;
    memset(head,-1,sizeof(head));
}

int main(){
    scanf("%d%d",&n,&k);
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            scanf("%d",&mp[i][j]);
    }
    addEdge(st,1,k,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            addEdge((i-1)*n+j,(i-1)*n+j+n*n,1,-mp[i][j]);
            addEdge((i-1)*n+j,(i-1)*n+j+n*n,INF,0);
            if(j<n)
                addEdge((i-1)*n+j+n*n,(i-1)*n+j+1,INF,0);
            if(i<n)
                addEdge((i-1)*n+j+n*n,i*n+j,INF,0);
        }
    }
    addEdge(n*n*2,ed,k,0);
    printf("%d",-mcmf());
    return 0;
}
*/
