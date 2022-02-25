#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 110
#define M 5000
using namespace std;
//kruskal 62ms
/*
����:n��С��,����Ҫ��С����������ʹ��С��ȫ��ͨ,
�޽����ų��Ȳ���С��10��,Ҳ���ܴ���1000��,���ŷ���Ϊ100Ԫ/��,
�����ٷ���.�������n��С��������.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1875
˼·:mst kruskal
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
    int x,y,cnt=0,flag=0;
    double sum=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n-1){
                flag=1;
                break;
            }
        }
    }
    if(!flag) sum=-1;//˵��С������ı߼�����ʹ����ͨ �ӱ���δ�ﵽn-1 ����-1
    return sum;
}

int main(){
    int T;
    double w,ans;
    scanf("%d",&T);
    while(T--){
        m=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&point[i].x,&point[i].y);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                if(w>=10 && w<=1000)
                    edge[++m]=Edge(i,j,w*100);
            }
        }
        ans=kruskal();
        if(ans!=-1)
            printf("%.1f\n",ans);
        else
            printf("oh!\n");
    }
    return 0;
}
