#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 110
using namespace std;
//ac 32ms
/*
题意:n个地鼠,m个地鼠洞,地鼠和地鼠洞的位置用(x,y)坐标表示,
一只鹰来了,现在所有地鼠都需要逃到洞里保命,但是一个洞只能有
一个地鼠,地鼠的逃跑速度为vm/s,如果地鼠不能在s秒逃到洞里,就
会被鹰吃掉,现在要求最少有几个地鼠会被鹰吃掉.
链接:http://poj.org/problem?id=2536
思路:因为一个地鼠洞只能有一个地鼠,也就是不会有逃跑路线不会有公共点,
很明显地鼠逃到地鼠洞里构成了一个匹配,现在就是求解地鼠和地鼠洞之间的
最大匹配,所以当地鼠和地鼠洞的距离小于等于s*v时就建地鼠到地鼠洞的有向边,
然后n-最大匹配就是答案.
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
