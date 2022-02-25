#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1000100
using namespace std;
typedef long long ll;
//ac 109ms
/*
题意:n个炸弹,每个炸弹有坐标和爆炸半径范围、引爆成本,如果炸弹A距离
炸弹B的距离小于等于炸弹A爆炸半径,则引爆炸弹A可同时引爆炸弹B,依次类推.
现在问将所有炸弹都引爆所需的最小花费.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5934
思路:首先暴力O(N^2)枚举完全图所有可能的边,就是炸弹A、B之间的距离小于等于A的爆炸半径,
则建单向边A->B.之后考虑tarjan求解出SCC 并求出各个SCC中的引爆炸弹的最小化费,那么这个
SCC内只需引爆这个最小花费的炸弹,其余炸弹就都会引爆,之后缩点统计各个点的入度.计算入度
为0的点,那么只需要累加所有入度为0的点的SCC中的最小花费就是引爆所有炸弹的最小花费,因为
入度为0的点没有边指向它,不可能通过其它点来引爆它.
*/

int n,dfn[N],low[N],in[N],num,cnt,head[N],id,block[N],minVal[N],inde[N];
stack<int> s;

struct Edge{
    int from,to,next;
}edge[M];

struct Point{
    double x,y,r;
    int c;
}point[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

double getDis(double x1,double y1,double x2,double y2){
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

void dfs(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            block[v]=id;
            minVal[id]=min(minVal[id],point[v].c);//记录SCC中的最小花费
        }while(v!=u);
    }
}

int main(){
    int T,u,v,cas=0;
    double w;
    scanf("%d",&T);
    while(T--){
        cas++;
        id=cnt=num=0;
        memset(dfn,0,sizeof dfn);
        memset(inde,0,sizeof inde);
        memset(minVal,0x3f,sizeof minVal);
        memset(head,-1,sizeof head);
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%lf%lf%lf%d",&point[i].x,&point[i].y,&point[i].r,&point[i].c);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                if(w<=point[i].r*point[i].r) addEdge(i,j);//i j间的距离小于等于i的爆炸半径,则建i->j
                if(w<=point[j].r*point[j].r) addEdge(j,i);
            }
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i);
        }
        for(int i=0;i<cnt;i++){
            u=edge[i].from,v=edge[i].to;
            if(block[u]!=block[v])
                inde[block[v]]++;
        }
        ll sum=0;
        for(int i=1;i<=id;i++){
            if(!inde[i])//累加入度为0的SCC的最小花费
                sum+=minVal[i];
        }
        printf("Case #%d: %lld\n",cas,sum);
    }
    return 0;
}
