#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1000100
#define INF 0x3f3f3f3f
using namespace std;

/*
����:n������,����k��������,��m��˫���·,����һ������Ӣ��
��s����,����Ҫ�������Ӣ�۵��������������·�����ֵ,��k��
�����ӷֱ𵽴�����(ʵ�ʾ���k����֮��ĵ�)·�����·�����ֵ,
�������ֵ���бȽ�,����Ӣ��Ҫ����c,���ԭ�Ƚ�С�����ֵ.
����:https://nanti.jisuanke.com/t/41349
˼·:����Ӣ�۵����������·�ܺ���,�������ӷֱ����������·����һ��
��Դ������·����,��������������Ҫ��k�����·��floyed O(N^3),���Խ���
һ������Դ��(0)��k�����������ڵĵ㹹��һ�������,�����Գ���Դ��0��Ϊ���
��һ�����·,�Ƚ�ÿ�����dis,������ֵ����k�������ӵ�����ص����·�����ֵ.
�����������ȥ�ӳ���Դ�����Ҳ������ÿ����������Ϊ���,�����ܵĹ�����,dijkstra
��̰���㷨,������и��µ��ǽ϶̵�dis,������ͬ���dis,�ϴ�ı�Ȩ�Ϳ��ܾͲ��ᱻ����,
������������,ʵ���������ı����Ǳȱ�����k�����·ҪС��,���ʱ��Ҳ����.
*/

int n,m,s,k,c,cnt,head[N],vis[N],dis[N];

struct Node{
    int to,next,w;
}edge[M];

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
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int T,u,v,w,ans1,ans2;
    scanf("%d",&T);
    while(T--){
        ans1=ans2=cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d%d%d%d",&n,&m,&s,&k,&c);
        for(int i=1;i<=k;i++){
            scanf("%d",&v);
            addEdge(0,v,0);//����Դ������k�����������ڵ�
        }
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        Dijkstra(s);
        for(int i=1;i<=n;i++)
            ans1=max(ans1,dis[i]);
        //��ʵ�������Ǵ�0(����Դ��)��ʼ���·,���������ӵ�dis����Ҳ��Ϊ0��,ʵ���Ͼ��������������ӵ����������·��������
        Dijkstra(0);
        for(int i=1;i<=n;i++)
            ans2=max(ans2,dis[i]);
        if(ans1<=ans2*c)
            printf("%d\n",ans1);
        else
            printf("%d\n",ans2);
    }
    return 0;
}
