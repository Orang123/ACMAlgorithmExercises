#include<cstdio>
#include<queue>
#include<cmath>
#include<algorithm>
#include<cstring>
#define N 110
#define M 11000
#define eps 1e-9
#define INF 1e18
using namespace std;
//ac 873ms EK�㷨 ��С���ʷ����� log2��2Ϊ������
/*
����:ͼ����n����,ÿ��������a����,b�����,��������Ե�ȥ�����ط�,
����m������·��,ÿ��·����һ����������.·��֮�����˵���,ÿ������
ͨ��ʱ������pi�ĸ���������,���ǵ�һ��ͨ������һ����������,��������
����ȡ��ʳ����������ߵ���С���ʡ�
����:http://acm.hdu.edu.cn/showproblem.php?pid=5988
˼·:������,���Ƿ������Ǽӷ�,��С������ȻҪ�ó˷�ԭ��,����ȡ�����
log2(ab)=log2(a)+log2(b),��ÿ���������˺�Դ�㽨��,ÿ��������ʧ���
��㽨��,����Ϊ�������,����Ϊ0,������߽�2����,һ������Ϊ1,����Ϊ0,һ��
����cf-1,����Ϊpi.
*/
int n,m,cnt,head[N],st,ed,incf[N],pre[N],vis[N];
double dis[N];
struct Edge{
    int to,next,cf;
    double w;
}edge[M<<1];

void addEdge(int from,int to,int cf,double w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    for(int i=st;i<=ed;i++)
        dis[i]=i==s?0:INF;
    incf[s]=0x3f3f3f3f;
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
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w+eps){
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

double mcmf(){
    double sum=0;
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
    int T,s,b,u,v,cf;
    double w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        for(int i=1;i<=n;i++){
            scanf("%d%d",&s,&b);
            s-=b;
            if(s>0)
                addEdge(st,i,s,0);
            if(s<0)
                addEdge(i,ed,-s,0);
        }
        while(m--){
            scanf("%d%d%d%lf",&u,&v,&cf,&w);
            if(cf>0)//��һ���˲�����������
                addEdge(u,v,1,0);
            if(cf-1>0)//ʣ�µ��˻�����
                addEdge(u,v,cf-1,-log2(1-w));
        }
        printf("%.2f\n",1-pow(2,-mcmf()));
    }
    return 0;
}

/*
//ac 858ms EK�㷨 ��С���ʷ����� log��10Ϊ������
#include<cstdio>
#include<queue>
#include<cmath>
#include<algorithm>
#include<cstring>
#define N 110
#define M 11000
#define eps 1e-9
#define INF 1e18
using namespace std;
int n,m,cnt,head[N],st,ed,incf[N],pre[N],vis[N];
double dis[N];
struct Edge{
    int to,next,cf;
    double w;
}edge[M<<1];

void addEdge(int from,int to,int cf,double w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    for(int i=st;i<=ed;i++)
        dis[i]=i==s?0:INF;
    incf[s]=0x3f3f3f3f;
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
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w+eps){
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

double mcmf(){
    double sum=0;
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
    int T,s,b,u,v,cf;
    double w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        init();
        for(int i=1;i<=n;i++){
            scanf("%d%d",&s,&b);
            s-=b;
            if(s>0)
                addEdge(st,i,s,0);
            if(s<0)
                addEdge(i,ed,-s,0);
        }
        while(m--){
            scanf("%d%d%d%lf",&u,&v,&cf,&w);
            if(cf>0)
                addEdge(u,v,1,0);
            if(cf-1>0)
                addEdge(u,v,cf-1,-log(1-w));
        }
        printf("%.2f\n",1-exp(-mcmf()));
    }
    return 0;
}
*/
