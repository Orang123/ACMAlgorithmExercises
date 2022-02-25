#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 500
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;
//ac 47ms EK�㷨
/*
����:nͷţ,f��ʳ���d������,ÿͷţ��ϲ���Ե�
ʳ�����������,����ҪΪÿͷţָ��һ��ʳ�������,
����һͷţֻ��ѡ��һ��ʳ���һ������,����ÿ��ʳ��
������ֻ�ܹ�һͷţʳ��,����������м�ͷţ��ѡ��
�Լ�ϲ����ʳ�������.
����:http://poj.org/problem?id=3281
˼·:���Թ���Դ��0,���f+2*n+d+1,��ţ����������f+i,f+n+i,
f+i��������ʳ��,f+n+i������������.Դ����ÿ��ʳ��i����,
��:0->i,ʳ����ţ����,ţ����������,������������,���б�
����Ϊ1,����������Ǵ�.
0ΪԴ��,1-fΪʳ��,f+i��f+n*2Ϊţ,f+n*2+i��F+n*2+dΪ����,f+n*2+d+1Ϊ���,
������Ϊ1.

ע��:ţ����Ҫ���,��������ֱ��Դ��->ʳ��->ţ->����->���,
�������ܻ����ÿ��ţѡ����ʳ������ϵ����,��������ĿҪ��,
����һͷţҪ��Ϊ����������,����Ϊ1.
*/
int n,f,d,cnt,head[N],incf[N],pre[N];
struct Edge{
    int to,next,cf;
}edge[M];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0};
    head[to]=cnt++;
}

int bfs(int s,int ed){
    queue<int> Q;
    incf[s]=INF;
    memset(pre,-1,sizeof(pre));
    pre[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && pre[v] == -1){
                incf[v]=min(incf[u],edge[i].cf);
                pre[v]=i;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int max_flow(int st,int ed){
    int sum=0,v;
    while(bfs(st,ed)){
        v=ed;
        while(v!=st){
            edge[pre[v]].cf-=incf[ed];
            edge[pre[v]^1].cf+=incf[ed];
            v=edge[pre[v]^1].to;
        }
        sum+=incf[ed];
    }
    return sum;
}

void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
}

int main(){
    int f0,d0,v;
    init();
    scanf("%d%d%d",&n,&f,&d);//nͷţ,f��ʳ��,d������
    for(int i=1;i<=f;i++)//Դ����ʳ�ｨ�� ����Ϊ1
        addEdge(0,i,1);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&f0,&d0);
        while(f0--){
            scanf("%d",&v);
            addEdge(v,f+i,1);//ʳ��v��ţf+i����,����Ϊ1
        }
        addEdge(f+i,f+n+i,1);//��ţ�Ĳ����������,����Ϊ1
        while(d0--){
            scanf("%d",&v);
            addEdge(f+n+i,f+2*n+v,1);//ţf+n+i������f+2*n+v����,����Ϊ1
        }
    }
    for(int i=1;i<=d;i++)
        addEdge(f+2*n+i,f+2*n+d+1,1);//ÿ��������������,����Ϊ1
    printf("%d",max_flow(0,f+2*n+d+1));
    return 0;
}

/*
//ac 32ms dinic
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 500
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;

int n,f,d,cnt,head[N],dis[N];
struct Edge{
    int to,next,cf;
}edge[M];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0};
    head[to]=cnt++;
}

int bfs(int s,int ed){
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

int dfs(int u,int ed,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,ed,min(flow,edge[i].cf));
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

int max_flow(int st,int ed){
    int sum=0;
    while(bfs(st,ed))
        sum+=dfs(st,ed,INF);
    return sum;
}

void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
}

int main(){
    int f0,d0,v;
    init();
    scanf("%d%d%d",&n,&f,&d);
    for(int i=1;i<=f;i++)
        addEdge(0,i,1);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&f0,&d0);
        while(f0--){
            scanf("%d",&v);
            addEdge(v,f+i,1);
        }
        addEdge(f+i,f+n+i,1);
        while(d0--){
            scanf("%d",&v);
            addEdge(f+n+i,f+2*n+v,1);
        }
    }
    for(int i=1;i<=d;i++)
        addEdge(f+2*n+i,f+2*n+d+1,1);
    printf("%d",max_flow(0,f+2*n+d+1));
    return 0;
}
*/
