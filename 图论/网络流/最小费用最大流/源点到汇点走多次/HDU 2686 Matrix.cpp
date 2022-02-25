#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 2000
#define INF 0x3f3f3f3f
using namespace std;
//ac 15ms EK�㷨 �������� ��� Դ��->[1,1]->...->[n,n]->���
//��ʵԴ��ͻ��Ҳ��������Ϊ1��n*n*2,�����յ�������� 2��һ���з���,һ���޷���,������Ϊ1
/*
����:��һ��n*n�ľ���,����ĸ�����ÿ������һ������.
������Ҫ�����Ͻ��ߵ����½�ȥ,Ȼ���ڴ����½ǻص����Ͻ�.
�����г������ϽǺ����½���,�������������һ��,��Ҫ����
���߹������������Ȩֵ�����,Ϊ���ֵ�Ƕ���?
����:http://acm.hdu.edu.cn/showproblem.php?pid=2686
˼·:������˼ά������POJ 3422��˼·,����[1,1]�ߵ�[n,n],
�ٴ�[n,n]�ߵ�[1,1]������POJ 2135��˼·,���Ի��ǲ�㽫��Ȩ
ת��Ϊ��Ȩ,ÿ������ֻ����1��,��������Ϊ1,��[1,1],[n,n],����
2��,������ֵֻ�ۼ�һ��,��Ҫ�ٽ�һ������Ϊ1,����Ϊ0�ı�,�ܷ���������.
*/
int n,cnt,head[N],st,ed,incf[N],pre[N],dis[N],vis[N],mp[40][40];
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
    st=0,ed=n*n*2+1;
    memset(head,-1,sizeof(head));
}

int main(){
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        addEdge(st,1,2,0);//Ҫ������2��
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if((i==1 && j==1) || (i==n && j==n))//[1,1] [n,n]Ҫ����2��,���ǵڶ��ξ������������
                    addEdge((i-1)*n+j,(i-1)*n+j+n*n,1,0);
                addEdge((i-1)*n+j,(i-1)*n+j+n*n,1,-mp[i][j]);//���Ϊ��Ⱥͳ���,����1,ֻ����һ��,��������Ϊ����,��ȡ������
                if(j<n)
                    addEdge((i-1)*n+j+n*n,(i-1)*n+j+1,INF,0);
                if(i<n)
                    addEdge((i-1)*n+j+n*n,i*n+j,INF,0);
            }
        }
        addEdge(n*n*2,ed,2,0);
        printf("%d\n",-mcmf());
    }
    return 0;
}

/*
//ac 15ms dinic �������� ���
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 2000
#define INF 0x3f3f3f3f
using namespace std;

int n,cnt,head[N],st,ed,incf[N],pre[N],dis[N],vis[N],mp[40][40];
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
    st=0,ed=n*n*2+1;
    memset(head,-1,sizeof(head));
}

int main(){
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        addEdge(st,1,2,0);//Ҫ������2��
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if((i==1 && j==1) || (i==n && j==n))//[1,1] [n,n]Ҫ����2��,���ǵڶ��ξ������������
                    addEdge((i-1)*n+j,(i-1)*n+j+n*n,1,0);
                addEdge((i-1)*n+j,(i-1)*n+j+n*n,1,-mp[i][j]);//���Ϊ��Ⱥͳ���,����1,ֻ����һ��,��������Ϊ����,��ȡ������
                if(j<n)
                    addEdge((i-1)*n+j+n*n,(i-1)*n+j+1,INF,0);
                if(i<n)
                    addEdge((i-1)*n+j+n*n,i*n+j,INF,0);
            }
        }
        addEdge(n*n*2,ed,2,0);
        printf("%d\n",-mcmf());
    }
    return 0;
}
*/
