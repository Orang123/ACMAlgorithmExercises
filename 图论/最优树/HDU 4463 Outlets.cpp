#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 100
#define M 2500
using namespace std;

/*
题意:n个点的完全图,在p到q是直接连接的条件下求解mst.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4463
思路:先把p->q的边权加上,之后将其实际边权设为0,然后求解mst.
*/

int n,m,p,q,fa[N];

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

double kruskal(double w){
    init();
    int x,y,cnt=0;
    double sum=w;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            cnt++;
            sum+=edge[i].w;
            if(cnt == n-1) break;
        }
    }
    return sum;
}

int main(){
    double w,w0;
    while(scanf("%d",&n) && n){
        m=0;
        scanf("%d%d",&p,&q);
        if(p>q) swap(p,q);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&point[i].x,&point[i].y);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                if(i == p && j==q){
                    w0=w;
                    w=0;
                }
                edge[++m]=Edge(i,j,w);
            }
        }
        printf("%.2f\n",kruskal(w0));
    }
    return 0;
}
