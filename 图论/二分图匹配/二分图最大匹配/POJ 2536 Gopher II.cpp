#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 110
using namespace std;
//ac 32ms
/*
����:n������,m������,����͵��󶴵�λ����(x,y)�����ʾ,
һֻӥ����,�������е�����Ҫ�ӵ����ﱣ��,����һ����ֻ����
һ������,����������ٶ�Ϊvm/s,�����������s���ӵ�����,��
�ᱻӥ�Ե�,����Ҫ�������м�������ᱻӥ�Ե�.
����:http://poj.org/problem?id=2536
˼·:��Ϊһ������ֻ����һ������,Ҳ���ǲ���������·�߲����й�����,
�����Ե����ӵ������ﹹ����һ��ƥ��,���ھ���������͵���֮���
���ƥ��,���Ե�����͵��󶴵ľ���С�ڵ���s*vʱ�ͽ����󵽵��󶴵������,
Ȼ��n-���ƥ����Ǵ�.
*/
int cnt,head[N];
int n,m,vis[N],match[N],ans;
double s,v;
struct Point{
    double x,y;
}point1[N],point2[N];
struct Edge{
    int to,next;
}edge[N*N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

double getDis(double x1,double y1,double x2,double y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=cnt=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
}

int main(){
    double w;
    while(scanf("%d%d%lf%lf",&n,&m,&s,&v)!=EOF){
        init();
        for(int i=1;i<=n;i++)
            scanf("%lf%lf",&point1[i].x,&point1[i].y);
        for(int i=1;i<=m;i++)
            scanf("%lf%lf",&point2[i].x,&point2[i].y);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                w=getDis(point1[i].x,point1[i].y,point2[j].x,point2[j].y);
                if(w/v <= s)
                    addEdge(i,j);
            }
        }
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",n-ans);
    }
    return 0;
}
