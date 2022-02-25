#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 2100
#define M 15000
#define INF 0x3f3f3f3f
using namespace std;
//ac 10ms EK������ ��㽨��
/*
����:һ����Ȩ����ͼ,����㵽�յ������·��Ȩֵ֮����С,
������·��û�й�����(�����,�յ�).
����:https://www.luogu.com.cn/problem/UVA1658
˼·:������,��Ϊÿ�����������յ�����·�������й�����,
���Բ��,i(���),i+n(����).i->i+n������Ϊ1,����Ϊ0�ı�,
ע������յ����ı�����Ϊ2,��Ϊ���������м�㲻�ظ���·��,
�����1,�����n+n.u-v֮�����w�������,��u+n->v����Ϊ1,����Ϊ
w�ı�,�ܷ���������.
*/
int n,m,cnt,st,ed,head[N],incf[N],pre[N],vis[N],dis[N];
struct Edge{
    int to,next,cf,w;
}edge[M<<1];

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

void mcmf(){
    int sum=0,cost=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed];
        cost+=incf[ed]*dis[ed];
    }
    printf("%d\n",cost);
}

void init(){
    cnt=0;
    st=1,ed=n*2;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v,w;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        for(int i=2;i<n;i++)//���
            addEdge(i,i+n,1,0);
        addEdge(1,1+n,2,0);//�����յ� ��������Ϊ2,��Ϊ����յ�����ظ�2��,������������·��.
        addEdge(n,n+n,2,0);
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u+n,v,1,w);
        }
        mcmf();
    }
    return 0;
}
