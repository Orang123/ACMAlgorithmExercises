#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 110
#define M 5000//��������ȫͼȡ����
using namespace std;
//kruskal 16ms
/*
����:n������״�Ŀռ乤��վ,����Ҫ��n���ռ�վ����������
�޽��໥���ӵ�����,��Ҫʹ�����й���վ��������ͨ,�޽����ȵ�
��С�����Ƕ���.
����:http://poj.org/problem?id=2031
˼·:mst,�������ľ����ȥ����뾶֮����С��0,����Ҫ�޽�,��ʱ����ȨֵΪ0�ı�,
��֮����ȨֵΪ���ľ���뾶֮�͵�Ȩ�ı�.
*/

int n,m,fa[N];

struct Edge{
    int u,v;
    double w;
    Edge(int u=0,int v=0,double w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

struct Point{
    double x,y,z,r;
}point[N];

double getDis(double x1,double y1,double z1,double x2,double y2,double z2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
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
    double sum=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n-1) break;
        }
    }
    return sum;
}

int main(){
    double w;
    while(scanf("%d",&n) && n){
        m=0;
        for(int i=1;i<=n;i++)
            scanf("%lf%lf%lf%lf",&point[i].x,&point[i].y,&point[i].z,&point[i].r);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                w=getDis(point[i].x,point[i].y,point[i].z,point[j].x,point[j].y,point[j].z)-point[i].r-point[j].r;
                if(w>0) edge[++m]=Edge(i,j,w);
                else edge[++m]=Edge(i,j,0);
            }
        }
        printf("%.3f\n",kruskal());
    }
    return 0;
}

/*
//prim 16ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
#define N 110
#define M 5000
#define INF 1e18
using namespace std;

int n,cnt,head[N],vis[N];
double dis[N];

struct Edge{
    int to,next;
    double w;
}edge[M<<1];

struct Point{
    double x,y,z,r;
}point[N];

void addEdge(int from,int to,double w){
    edge[cnt]=(Edge){to,head[from],w};
    head[from]=cnt++;
}

double getDis(double x1,double y1,double z1,double x2,double y2,double z2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
}

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)//���������� ����memset�����,ֱ�Ӹ�ֵ
        dis[i]=i==s?0:INF;
}

double prim(int s){
    init(s);
    priority_queue<pair<double,int> >Q;
    Q.push(make_pair(0,s));
    int u,v,num=0;
    double sum=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        sum+=dis[u];
        num++;
        if(num == n) return sum;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v] && edge[i].w<dis[v]){
                dis[v]=edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return sum;
}

int main(){
    double w;
    while(scanf("%d",&n) && n){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%lf%lf%lf%lf",&point[i].x,&point[i].y,&point[i].z,&point[i].r);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                w=getDis(point[i].x,point[i].y,point[i].z,point[j].x,point[j].y,point[j].z)-point[i].r-point[j].r;
                if(w>0){
                    addEdge(i,j,w);
                    addEdge(j,i,w);
                }
                else{
                    addEdge(i,j,0);
                    addEdge(j,i,0);
                }
            }
        }
        printf("%.3f\n",prim(1));
    }
    return 0;
}
*/
