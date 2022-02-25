#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 210
#define INF 0x3f3f3f3f
using namespace std;
//ac 120ms Ek������ ���򻷸���
/*
����:���Ű�ʿ·�����,��������:�и��������Ҫ�Ľ����Ĺ���ϵͳ,
����һ��������������ͨ������Ĺ۹�·��,����������Ϊ�óǵĹ�
�⹫����һ������·�߼ƻ�.�㽫�ᱻ����һ�龰��,����ÿ���������ľ���,
ֻ����һ������·�߾���,���ҹ���·��ֻ�ܾ����������һ��.����·�ߵ���
�����������޵�, ��ÿ��·�߱�����������������.������������ĵ�·�ǵ����,
���ڵ�·(i,j),���ĳ���Ϊd(i,j).ע�⼴ʹ(i,j)��(j,i)������,d(i,j)��d(j,i)
Ҳ��һ����ͬ. ÿ������·�߱����Ǹ�����.����Ҫ�����С�Ĺ���·���ܳ�,
�����й���·����ͨ����·��d���ܺ�.
����:https://www.luogu.com.cn/problem/UVA1349
˼·:���й���·�߶�Ҫ��������ཻ�����򻷸���,ͬHDU 1853.
*/
int n,m,cnt,st,ed,head[N],incf[N],pre[N],vis[N],dis[N];
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
    if(sum == n)
        printf("%d\n",cost);
    else
        printf("N\n");
}

void init(){
    cnt=0;
    st=0,ed=n*2+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v,w;
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++){
            addEdge(st,i,1,0);
            addEdge(i+n,ed,1,0);
        }
        for(u=1;u<=n;u++){
            while(scanf("%d",&v) && v){
                scanf("%d",&w);
                addEdge(u,v+n,1,w);
            }
        }
        mcmf();
    }
    return 0;
}
