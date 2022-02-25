#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define INF 1e18
using namespace std;
typedef long long ll;
//124ms prim 用链接前向星会MLE,这里用了邻接矩阵mp
/*
题解:n个城市每个城市都有一定人口,秦始皇要用n-1条道路将其连接起来并且使得总长度最小.
徐福可以用魔法免费修建一条道路,现在定义A:魔法免费修建道路连接的2个城市的人口,B:非
魔法修建的道路长度总和,现在秦始皇希望A/B是最大值,问最大值是多少.

有n个城市，秦始皇要修用n-1条路把它们连起来，要求从任一点出发，都可以到达其它的任意点。秦始皇希望这所有n-1条路长度之和最短。
然后徐福突然有冒出来，说是他有魔法，可以不用人力、财力就变出其中任意一条路出来。
秦始皇希望徐福能把要修的n-1条路中最长的那条变出来，但是徐福希望能把要求的人力数量最多的那条变出来。对于每条路所需要的人力，
是指这条路连接的两个城市的人数之和。
最终，秦始皇给出了一个公式，A/B，A是指要徐福用魔法变出的那条路所需人力， B是指除了徐福变出来的那条之外的所有n-2条路径长度之和，
选使得A/B值最大的那条。
思路:A/B最大,显然分母应尽可能小,那就是求解mst,但是会有一条免费的道路,显然对于完全图
枚举每条边免费求解n*(n-1)/2 n<=1000次mst显然TLE,那么可以考虑先求解出mst权值和以及mst,
任意两点之间的边权最大值,这样可以在原先mst的基础上直接得出对于每条免费魔法道路的A/B值.
对于魔法道路在mst上,B=sum-mp[i][j],非魔法道路只需要减去魔法道路本身的边权即可,
对于魔法道路不在mst上,B=sum-maxLen[i][j],魔法道路本身不需要花费,但是这会在原先mst的基础上,
在i到j的路径上构成一个环,那么需要在原先i到j路径上减去一个边,因为要求A/B最大,那么B越小A/B越大,
那么选择减去maxLen[i][j] i到j路径上的最大边,这也是为什么要求解任意两点之间的边权最大值的原因.
*/

int n,vis[N],used[N][N],pre[N];
double dis[N],val[N],maxLen[N][N],sum,mp[N][N];

struct Point{
    int x,y;
}point[N];

double getDis(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(used,0,sizeof(used));
    pre[s]=s;//第一个点s出队时,pre[s]是未知的,但此时并没有边加入
    for(int i=1;i<=n;i++){
        maxLen[i][i]=0;//计算时 maxLen[pre[u]][pre[u]]会用到,因此要初始化
        dis[i]=i==s?0:INF;
    }
    sum=0;
}

void prim(int s){
    init(s);
    priority_queue<pair<double,int> >Q;
    Q.push(make_pair(0,s));
    int u,num=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        num++;
        sum+=dis[u];
        used[pre[u]][u]=used[u][pre[u]]=1;
        for(int v=1;v<=n;v++){
            //dp求解已加入连通集的点到新加入连通集的点u的最大距离,其中已加入连通集的点到pre[u]的maxLen已在上一次pre[u]出队时计算出来
            if(vis[v] && v!=u)//v!=u 否则max[u][u]将不为0会被更改,在v点出队时,求解maxLen[pre[v]][v]时 maxLen[u][u]不为0会导致maxLen[pre[v]][v]可能不为dis[v]
                //因为是完全图 邻接矩阵,所以maxLen可以和Q.push放在一个循环里,如果不是完全图,
                //可能不能遍历到所有的已加入mst的点,用了链式前向星,maxLen一定要单独放在一个for里对已加入mst的点求解
                maxLen[v][u]=maxLen[u][v]=max(maxLen[v][pre[u]],dis[u]);
            if(!vis[v] && mp[u][v]<dis[v]){
                dis[v]=mp[u][v];
                pre[v]=u;
                Q.push(make_pair(-dis[v],v));
            }
        }
        if(num == n) return;//最后一个点出队结束前 要把maxLen[v][u]的值都计算一遍
    }
}

int main(){
    int T;
    double w,ans;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%lf",&point[i].x,&point[i].y,&val[i]);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                mp[i][j]=mp[j][i]=w;
            }
        }
        prim(1);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(used[i][j])//i->j在mst上
                    ans=max(ans,(val[i]+val[j])/(sum-mp[i][j]));
                else//i->j不在mst上
                    ans=max(ans,(val[i]+val[j])/(sum-maxLen[i][j]));
            }
        }
        printf("%.2f\n",ans);
    }
    return 0;
}
