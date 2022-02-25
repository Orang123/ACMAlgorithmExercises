#include<cstdio>
#include<cmath>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 1e18
using namespace std;
//prim 514ms
//输入为稠密图 用kruskal 会TLE
/*
题意:1个发电站(编号为1),n-1个宿舍,现在要在宿舍和发电站间铺设电缆,电缆造价k元/米,
使其相互连通,但是现在有2个宿舍间不能铺设新的高负荷电缆,但并不清楚是哪两个宿舍,
现在电缆最多要准备多少钱才能使得宿舍和发电站相互连通.
注意发电站和宿舍之间是一定可以铺设电缆的.
简化题意:
n个点的完全图,求出mst后删除mst中一条边后的mst权值和的最大值,
与1号结点相连的边不能删除.

链接:http://acm.hdu.edu.cn/showproblem.php?pid=4756
思路:因为并不清楚哪两个宿舍不能铺设高负荷电缆,所以要枚举删除任意两个宿舍间的连边.
就是求解删除某条边后最小生成树的权值和的最大值,但是原图是完全图,如果暴力枚举
删除原图中的每条边,n<=1000 O(n^2*nlog(n))肯定TLE,可以先求解出mst,再在mst的基础上,
删除mst中的边,求解最小生成树,再求出最大值,实际就是求解在不选入原先某条边的前提下最小生成树的最大值.
对于删除某条边后的最小树可由原先mst的权值和-删除边权+(分离出2个连通集连接起来的最小边权)求出,
分离出2个连通集连接起来的最小边权可由O(n^2)树形dp求出.
*/

int n,k,vis[N],cnt,head[N];
double mp[N][N],dis[N],dp[N][N],sum,ans;

struct state{
    int u,v;
    double w;
    state(int u=0,int v=0,double w=0):u(u),v(v),w(w){}
    bool operator < (const state &x)const{
        return w>x.w;
    }
};

struct Node{
    int from,to,next;
    double w;
}edge[N<<1];

void addEdge(int from,int to,double w){
    edge[cnt]=(Node){from,to,head[from],w};
    head[from]=cnt++;
}

struct Point{
    double x,y;
}point[N];

double getDis(double x1,double y1,double x2,double y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=i==s?0:INF;
}

void prim(int s){
    init(s);
    priority_queue<state>Q;
    Q.push(state(s,s,0));
    int u,num=0;
    state tmp;
    while(!Q.empty()){
        tmp=Q.top();
        u=tmp.v;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        if(dis[u]){
            addEdge(tmp.u,tmp.v,tmp.w);
            addEdge(tmp.v,tmp.u,tmp.w);
        }
        num++;
        sum+=tmp.w;
        if(num == n) return;
        for(int v=1;v<=n;v++){
            if(!vis[v] && mp[u][v]<dis[v]){
                dis[v]=mp[u][v];
                Q.push(state(u,v,dis[v]));
            }
        }
    }
}

double dfs1(int u,int fa,int rt){
    double res=INF;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        double tmp=dfs1(v,u,rt);
        res=min(res,tmp);
        dp[u][v]=dp[v][u]=min(dp[u][v],tmp);
    }
    if(rt!=fa) res=min(res,mp[rt][u]);
    return res;
}

void dfs2(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(u!=1)//和发电站(1号节点)相连的边不能删
            ans=max(ans,sum-edge[i].w+dp[u][v]);
        dfs2(v,u);
    }
}

int main(){
    int T;
    double w;
    scanf("%d",&T);
    while(T--){
        cnt=sum=0;
        memset(head,-1,sizeof head);
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
                dp[i][j]=dp[j][i]=INF;
        for(int i=1;i<=n;i++)
            scanf("%lf%lf",&point[i].x,&point[i].y);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                mp[i][j]=mp[j][i]=w;
            }
        }
        prim(1);
        for(int i=1;i<=n;i++)
            dfs1(i,-1,i);
        ans=sum;//有可能构造出的mst所有的边都和发电站(1节点)相连,此时无法删边,最大花费就是原mst的费用
        dfs2(1,-1);
        printf("%.2f\n",ans*k);
    }
    return 0;
}
