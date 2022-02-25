#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 50
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;

/*
����:n����,ֻ�ܳ���ɾ�����Ϊ2~n-1�е�һ����,������ʹ
1�㲻�ɴ�n��,�������ʹ�䲻�ɴ�,�������·�����ֵ.
(ϣ�����ϰ廨�����Ǯ,������׼������Ǯ).
����:http://acm.hdu.edu.cn/showproblem.php?pid=5137
˼·:��ΪN<=30,���Ա���ö��ɾ��2~n-1�е�һ���������·,��¼���ֵ.
*/

int n,m,cnt,head[N],vis[N],dis[N],sign[N];
struct Node{
    int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

void Dijkstra(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(sign[v]) continue;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int u,v,w,ans;
    while(scanf("%d%d",&n,&m) && n+m){
        ans=cnt=0;
        memset(head,-1,sizeof(head));
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        //ö��ɾ��2~n-1 ĳһ����
        for(int i=2;i<n;i++){
            sign[i]=1;
            Dijkstra(1);
            sign[i]=0;
            ans=max(ans,dis[n]);
            if(ans==INF) break;
        }
        if(ans!=INF) printf("%d\n",ans);
        else printf("Inf\n");
    }
    return 0;
}
