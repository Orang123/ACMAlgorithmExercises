#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 300
#define INF 0x3f3f3f3f
using namespace std;
//ac 94ms floyd+���־���(���ֵ��С��)+�������֤
/*
����ժ������
����:k������,ÿ������������mͷţ.cͷţ,ÿ��ţ��Ҫ1̨����������.
������ţ�����ÿ��֮���ֱ�Ӿ���,�������е�ţ��������������,
ʹ�ߵ���Զ��ţ�ľ������,���������.
����ľ�����(k+c)*(k+c),�����������ţ֮��ľ���,����ţ������֮��
�ľ���,�������1~k,��ţ���k+1~k+c,��������ţ����Ϊ0,�����������ţ
֮�䲻��ͨ��.
����:http://poj.org/problem?id=2112
˼·:��Ȼ������ţ����������ʹ�����ֵ��С��,��ô���Կ��Ƕ���ö��������,
�����������������֤,Դ��0,���k+c+1,Դ����ÿ������1~k������Ϊm�ı�,ÿ������
��ÿ����ͨ�еõ���ţ(���벻ΪINF)������Ϊ1�ı�,ÿ����ţ���㽨����Ϊ1�ı�,
��������жϽ���Ƿ�Ϊc��ţ����,����,����Զ�����С,������,����Զ������.
*/
int k,c,m,n,st,ed,cnt,head[N],dis[N],vis[N],mp[N][N];
struct Edge{
    int to,next,cf;
}edge[N*N];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0};
    head[to]=cnt++;
}

int bfs(int s){
    queue<int> Q;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v] == -1){
                dis[v]=dis[u]+1;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int dfs(int u,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
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
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(int mid){
    int sum=0;
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=k;i++)
        addEdge(st,i,m);
    for(int i=k+1;i<=n;i++)
        addEdge(i,ed,1);
    for(int i=1;i<=k;i++){
        for(int j=k+1;j<=n;j++){
            if(mp[i][j] != INF && mp[i][j]<=mid)//������i����ţj֮����벻����mid,�򹹽����ӹ�ϵ
                addEdge(i,j,1);
        }
    }
    while(bfs(st))
        sum+=dfs(st,INF);
    return sum == c;
}

void floyd(){
    for(int t=1;t<=n;t++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(mp[i][j]>mp[i][t]+mp[t][j])
                    mp[i][j]=mp[i][t]+mp[t][j];
            }
        }
    }
}

void init(){
    st=0,ed=k+c+1;
    n=k+c;
}

int main(){
    int l,r,mid;
    scanf("%d%d%d",&k,&c,&m);
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&mp[i][j]);
            if(i != j && !mp[i][j])
                mp[i][j]=INF;
        }
    }
    floyd();
    l=0,r=0;
    for(int i=1;i<=k;i++){
        for(int j=k+1;j<=n;j++){
            r=max(r,mp[i][j]);//���������ĳ�ʼ�Ͻ�
        }
    }
    while(l<r){
        mid=(l+r)/2;
        if(max_flow(mid))
            r=mid;
        else
            l=mid+1;
    }
    printf("%d",r);
    return 0;
}

/*
//ac 125ms ����������+����ƥ��(������)
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 250
#define INF 0x3f3f3f3f
using namespace std;

int k,c,m,n,cnt,head[N],link[50][20],vis[50],num[50],mp[N][N];
struct Edge{
    int to,next;
}edge[N*30];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u,int clock){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v] == clock) continue;
        vis[v]=clock;
        if(num[v]<m){
            link[v][++num[v]]=u;
            return 1;
        }
        else{
            for(int i=1;i<=num[v];i++){
                if(dfs(link[v][i],clock)){
                    link[v][i]=u;
                    return 1;
                }
            }
        }
    }
    return 0;
}

void init(int mid){
    cnt=0;
    memset(head,-1,sizeof(head));
    memset(num,0,sizeof(num));
    memset(vis,0,sizeof(vis));
    for(int i=k+1;i<=n;i++){
        for(int j=1;j<=k;j++){
            if(mp[i][j] !=INF && mp[i][j]<=mid)//����ţi���뼷�̻�j���벻����mid,�򹹽��ɵ����ϵ
                addEdge(i,j);
        }
    }
}

int hungary(int mid){
    int sum=0;
    init(mid);
    for(int i=k+1;i<=n;i++)
        if(dfs(i,i)) sum++;
    return sum == c;
}

void floyd(){
    for(int t=1;t<=n;t++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(mp[i][j]>mp[i][t]+mp[t][j])
                    mp[i][j]=mp[i][t]+mp[t][j];
            }
        }
    }
}

int main(){
    int l,r,mid;
    scanf("%d%d%d",&k,&c,&m);
    n=k+c;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&mp[i][j]);
            if(i != j && !mp[i][j])
                mp[i][j]=INF;
        }
    }
    floyd();
    l=0,r=0;
    for(int i=k+1;i<=n;i++){
        for(int j=1;j<=k;j++)
            r=max(r,mp[i][j]);//���������ĳ�ʼ�Ͻ�
    }
    while(l<r){
        mid=(l+r)/2;
        if(hungary(mid))
            r=mid;
        else
            l=mid+1;
    }
    printf("%d",r);
    return 0;
}
*/
