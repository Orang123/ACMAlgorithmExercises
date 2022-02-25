#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;

/*
����:n�����ͼ,��m�������,��������֮��Ĭ�ϻ��е��������,
��ȨֵΪi^j*c,�������a��b�����·.
����:https://www.luogu.com.cn/problem/P4366
˼·:�����������������߲��ܱ������߿ռ俪��ΪM+N^2(N<=10^5),���Կ����������ʺͶ�����
������ȥ����,1(001)��6(110) 1->6����Ϊ7(111)C,
����ת��Ϊ1(001)->5(101) ����4C,5(101)->4(100) ����C
4(100)->6(110) ����2C,1->5->4->6 �ܴ��ۻ���7C
����ֻ��Ҫ��M+N*log2(N)����.
*/

int n,m,c,a,b,cnt,head[N],vis[N],dis[N];

struct Node{
    int to,next,w;
}edge[M+N*17];//log2(N)=16.6

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    /*
    �������������,��Щ����ֱ������,��Щ���ͨ�������ƴ��,
    �������,�������۲���.��������ƽ���ʮ������,��Ҫ����ͼ,
    ����ͼ���.
    */
    for(int i=0;i<=n;i++){//o(nlog2(n))
        for(int j=1;j<=n;j<<=1){
            if((i^j)>n) continue;//i^j����n�ı�ŵĵ��ǲ����ڵ�
            addEdge(i,i^j,j*c);//��i->(i^j) ����Ϊ i^(i^j)*c=j*c �����ߵ�����
        }
    }
}

void Dijkstra(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(u == b) return;
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&c);
    while(m--){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
    }
    scanf("%d%d",&a,&b);
    Dijkstra(a);
    printf("%d",dis[b]);
    return 0;
}
