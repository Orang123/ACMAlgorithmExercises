#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;
//ac 360ms EK ������ Դ��->��Ӧ��->�˿�->���
/*
����:(ժ������)��n���˿�,m����Ӧ��,k�ֻ���,����˿Ͷ���ÿ�ֻ����Ҫ�����,
�͹�Ӧ�̶���ÿ�ֻ����������,�Լ���Ӧÿ�ֻ����ʱ��Ӧ�̺͹˿�֮������䵥��,
�����������й˿͵�ǰ���µ���С��������Ƕ���.
����:http://poj.org/problem?id=2516
˼·:�����ж�ÿ�����й�Ӧ�̶�ÿ�ֻ���Ĺ�Ӧ���Ƿ񶼴��ڵ������й˿͵�������,
�������н�,�����޽�,���-1.�н�������ÿ�ֻ�����һ����С���������,Դ��0,���n+m+1,
���ڻ���k,Դ����ÿ����Ӧ�̽�����Ϊ������ı�,ÿ���˿����㽨����Ϊ�����������ı�,
ÿ����Ӧ����ÿ���˿ͽ�����ΪINF,��λ����Ϊ����Ʒ��λ�˷ѵı�,�������,�����С���ü���.
*/
int st,ed,cnt,head[N];
int n,m,k,need[N][N],supply[N][N],goods[N],cost[N][N][N],dis[N],incf[N],pre[N],vis[N],ans;
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
    ans=0;
    st=0,ed=n+m+1;
    memset(goods,0,sizeof(goods));
}

int main(){
    while(scanf("%d%d%d",&n,&m,&k) && n+m+k){
        init();
        for(int i=1;i<=n;i++){//n���˿Ͷ�j�����������
            for(int j=1;j<=k;j++){
                scanf("%d",&need[i][j]);
                goods[j]+=need[i][j];
            }
        }
        for(int i=1;i<=m;i++){//m����Ӧ�̶�j����Ĺ�Ӧ��
            for(int j=1;j<=k;j++){
                scanf("%d",&supply[i][j]);
                goods[j]-=supply[i][j];
            }
        }
        for(int i=1;i<=k;i++)
            for(int j=1;j<=n;j++)
                for(int l=1;l<=m;l++)//���ڵ�i�ֻ���,l��Ӧ�������j�˿͵ĵ�λ����Ϊcost[i][l][j]
                    scanf("%d",&cost[i][l][j]);
        int flag=0;
        for(int i=1;i<=k;i++){//�ж�ÿ�ֻ����Ƿ���ڽ�
            if(goods[i]>0){//���������ڹ�Ӧ���޽�
                flag=1;
                break;
            }
        }
        if(flag){
            printf("-1\n");
            continue;
        }
        for(int i=1;i<=k;i++){//ÿ�ֻ�����һ�������
            cnt=0;
            memset(head,-1,sizeof(head));
            for(int j=1;j<=m;j++)
                addEdge(st,j,supply[j][i],0);//Դ����Ӧ�̽��� ���������ִ���,����0
            for(int j=1;j<=n;j++)
                addEdge(j+m,ed,need[j][i],0);//ÿ���˿����㽨�� ����Ϊ����������,����0
            for(int j=1;j<=m;j++){
                for(int l=1;l<=n;l++)
                    addEdge(j,l+m,INF,cost[i][j][l]);//��Ӧ��j��˿�l+m����,����INF,����Ϊ��Ӧ���䵥��
            }
            ans+=mcmf();//�ۼ���С����
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 375ms EK ������ Դ��->�˿�->��Ӧ��->���
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int st,ed,cnt,head[N];
int n,m,k,need[N][N],supply[N][N],goods[N],cost[N][N][N],dis[N],incf[N],pre[N],vis[N],ans;
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
    ans=0;
    st=0,ed=n+m+1;
    memset(goods,0,sizeof(goods));
}

int main(){
    while(scanf("%d%d%d",&n,&m,&k) && n+m+k){
        init();
        for(int i=1;i<=n;i++){//n���˿Ͷ�j�����������
            for(int j=1;j<=k;j++){
                scanf("%d",&need[i][j]);
                goods[j]+=need[i][j];
            }
        }
        for(int i=1;i<=m;i++){//m����Ӧ�̶�j����Ĺ�Ӧ��
            for(int j=1;j<=k;j++){
                scanf("%d",&supply[i][j]);
                goods[j]-=supply[i][j];
            }
        }
        for(int i=1;i<=k;i++)
            for(int j=1;j<=n;j++)
                for(int l=1;l<=m;l++)//���ڵ�i�ֻ���,l��Ӧ�������j�˿͵ĵ�λ����Ϊcost[i][l][j]
                    scanf("%d",&cost[i][l][j]);
        int flag=0;
        for(int i=1;i<=k;i++){//�ж�ÿ�ֻ����Ƿ���ڽ�
            if(goods[i]>0){//���������ڹ�Ӧ���޽�
                flag=1;
                break;
            }
        }
        if(flag){
            printf("-1\n");
            continue;
        }
        for(int i=1;i<=k;i++){//ÿ�ֻ�����һ�������
            cnt=0;
            memset(head,-1,sizeof(head));
            for(int j=1;j<=n;j++)
                addEdge(st,j,need[j][i],0);//Դ����˿ͽ��� �����˿�������,����0
            for(int j=1;j<=m;j++)
                addEdge(j+n,ed,supply[j][i],0);//ÿ���������㽨�� ����Ϊ�����ִ���,����0
            for(int j=1;j<=n;j++){
                for(int l=1;l<=m;l++)
                    addEdge(j,l+n,INF,cost[i][l][j]);//�˿�j��Ӧ��l+n����,����INF,����Ϊ��Ӧ���䵥��
            }
            ans+=mcmf();//�ۼ���С����
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 297ms dinic ������ Դ��->��Ӧ��->�˿�->���
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int st,ed,cnt,head[N];
int n,m,k,need[N][N],supply[N][N],goods[N],cost[N][N][N],dis[N],vis[N],ans;
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
    ans=0;
    st=0,ed=n+m+1;
    memset(goods,0,sizeof(goods));
}

int main(){
    while(scanf("%d%d%d",&n,&m,&k) && n+m+k){
        init();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=k;j++){
                scanf("%d",&need[i][j]);
                goods[j]+=need[i][j];
            }
        }
        for(int i=1;i<=m;i++){
            for(int j=1;j<=k;j++){
                scanf("%d",&supply[i][j]);
                goods[j]-=supply[i][j];
            }
        }
        for(int i=1;i<=k;i++)
            for(int j=1;j<=n;j++)
                for(int l=1;l<=m;l++)
                    scanf("%d",&cost[i][l][j]);
        int flag=0;
        for(int i=1;i<=k;i++){
            if(goods[i]>0){
                flag=1;
                break;
            }
        }
        if(flag){
            printf("-1\n");
            continue;
        }
        for(int i=1;i<=k;i++){
            cnt=0;
            memset(head,-1,sizeof(head));
            for(int j=1;j<=m;j++)
                addEdge(st,j,supply[j][i],0);
            for(int j=1;j<=n;j++)
                addEdge(j+m,ed,need[j][i],0);
            for(int j=1;j<=m;j++){
                for(int l=1;l<=n;l++)
                    addEdge(j,l+m,INF,cost[i][j][l]);
            }
            ans+=mcmf();
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
