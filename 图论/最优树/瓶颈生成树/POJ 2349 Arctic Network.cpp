#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 550
#define M 130000
using namespace std;
//kruskal 172ms ���ڱ���prim�㷨���ʺ�
/*
����:n��ǰ��վҪ����֮���ͨ�����ǻ����ߵ����ͨ��,
�ֱ�������ǵ�2��ǰ��վͨ�ſɲ�����λ�þ���,�����ߵ�ͨ�Ų���
�ɱ�Ϊ����ǰ��վ��ľ���D,�����շ����Ĺ��ʺ�����Dֵ
���,DֵԽ��,�ɱ�Խ��,����Ҫ����n��ǰ��վ������ͨ��ͨ����,
����С�ɱ��Ƕ���.
����:http://poj.org/problem?id=2349
˼·:��Сƿ����,����ȨΪ����������������Ȩ����Сֵ,mstһ������Сƿ����,
����Сƿ������һ����mst.
�����С�������е�����Ȩ,��Ϊ�������ǵ�ǰ��վ��ͨ��,
�ɲ����ǳɱ�,����̰��ѡ���������б�Ȩ���ıߵĶ˵��������,�����ɱ����.
eg:s�����Ƿ�����s���˵���,����s-1���߱�ȨΪ0,����kruskal�ӱ�ʱ,�ӵ�n-1-(s-1)
=n-s����ʱ,ʣ�µ�s-1����Ҳ����s����ɽ�s�����Ƿ�������Щ�˵���,��Ȩ��Ϊ0,��ô
����Ȩ���Ǽӵĵ�n-s����.
*/

int s,n,m,fa[N];

struct Edge{
    int u,v;
    double w;
    Edge(int u=0,int v=0,double w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

struct Point{
    int x,y;
}point[N];

double getDis(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

double kruskal(){
    init();
    int x,y,cnt=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            cnt++;
            if(cnt == n-s)
                return edge[i].w;
        }
    }
}

int main(){
    int T;
    double w;
    scanf("%d",&T);
    while(T--){
        m=0;
        scanf("%d%d",&s,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&point[i].x,&point[i].y);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                edge[++m]=Edge(i,j,w);
            }
        }
        printf("%.2f\n",kruskal());
    }
    return 0;
}
/*
//V<=500 E<=130000
//E>Vlog(V) Ϊ����ͼ ����ͼ���ʺ�prim
//prim 125ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
#define N 550
#define M 130000
#define INF 1e18
using namespace std;

int s,n,cnt,head[N],vis[N];
double dis[N],a[N];

struct Edge{
    int to,next;
    double w;
}edge[M<<1];

struct Point{
    int x,y;
}point[N];

double getDis(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void addEdge(int from,int to,double w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=i==s?0:INF;
}

void prim(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v,num=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        num++;
        //������mst�еı߷���a����������,��Ϊÿ�ε�����Ȩ�ľ���mst�м��ϵĵ�ı�Ȩ��С�������
        if(num!=1) a[num]=dis[u];
        if(num == n) return;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && edge[i].w<dis[v]){
                dis[v]=edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int T;
    double w;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&s,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&point[i].x,&point[i].y);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                addEdge(i,j,w);
                addEdge(j,i,w);
            }
        }
        prim(1);
        sort(a+2,a+n+1,less<double>());
        printf("%.2f\n",a[n-s+1]);
    }
    return 0;
}
*/
