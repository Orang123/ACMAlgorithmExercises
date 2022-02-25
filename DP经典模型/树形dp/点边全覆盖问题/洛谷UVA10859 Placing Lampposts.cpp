#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

/*
题意:给定一个n个点m条边的无向无环图,在尽量少的节点上放灯,使得所有边都与灯相邻(被灯照亮).
在灯的总数最小的前提下,被两盏灯同时照亮的边数应该尽可能大.
链接:https://www.luogu.com.cn/problem/UVA10859
思路:
dp1[u][0/1]代表u节点不放灯/放灯,子树节点边集都被覆盖照亮所放置的最少的灯的数量.
dp2[u][0/1]代表在dp1[u][0/1]最小的条件下,即放置灯数最少的前提下,被两盏灯同时照亮的边数.
只被一盏灯照亮的边数=m-被两盏灯同时照亮的边数.
*/

int n,m,head[N],cnt,dp1[N][2],dp2[N][2],ans1,ans2;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dp1[u][1]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        dp1[u][0]+=dp1[v][1];
        dp1[u][1]+=min(dp1[v][0],dp1[v][1]);
        /*
        u节点不放置灯,但为了使两边都被照亮边数最多,
        这里要加上子节点放置灯两边都被照亮的数目,
        (dp2[v][1]本身就是在dp1[v][0/1]最小基础上转移的).
        */
        dp2[u][0]+=dp2[v][1];
        //dp2要在dp1较小值的基础上求解最大值
        if(dp1[v][0]<dp1[v][1])//较小值是v节点不放置灯,因此dp2就要取dp2[v][0]
            dp2[u][1]+=dp2[v][0];
        else if(dp1[v][0]>dp1[v][1])//较小值是v节点放置灯,因此dp2就要取dp2[v][1]
            dp2[u][1]+=dp2[v][1]+1;//这里因为u、v节点都放置灯,新增u->v这条被2盏灯同时照亮的边
        else//若dp1[v][0]==dp1[v][1],则dp2取 dp2[v]中数值较大的,因为dp2[v][0] dp2[v][1]+1都是在放置灯数较小的前提下
            dp2[u][1]+=max(dp2[v][0],dp2[v][1]+1);
    }
}

int main() {
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        cnt=ans1=ans2=0;
        memset(dp1,0,sizeof(dp1));
        memset(dp2,0,sizeof(dp2));
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){
            if(!dp1[i][1]){//原图可能不是连通图,可能是森林
                dfs(i,-1);
                ans1+=min(dp1[i][0],dp1[i][1]);
                if(dp1[i][0]<dp1[i][1])
                    ans2+=dp2[i][0];//ans2(被两盏灯照亮的最大边数)依然要在dp1放置最少灯的前提下求解
                else if(dp1[i][0]>dp1[i][1])
                    ans2+=dp2[i][1];
                else
                    ans2+=max(dp2[i][0],dp2[i][1]);//因为i已经没有父节点了,所以dp2[i][1]不加1
            }
        }
        //输出最小灯数、被两盏灯同时照亮的边数、只被一盏灯照亮的边数
        printf("%d %d %d\n",ans1,ans2,m-ans2);
    }
    return 0;
}

/*
将最小值+最大值问题转化为最小值+最小值,用一个dp解决,简化做法
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define N0 2000
using namespace std;

//题目要求的是最小灯数、被两盏灯同时照亮的最大边数,可以将被两盏灯同时照亮的最大边数
//转化为只被一盏灯照亮的最小边数,这样树形dp就可以同时求解出两个最小值,就可以只用过一个dp来完成
//否则之前一个求解最小值一个最大值(被两盏灯同时照亮的最大边数)转移时相互矛盾
//可以转化为ans=M∗x+y,x是放置的灯数,y是只被一盏灯照亮的最小边数,x可通过ans/M求得,y可通过ans%M求得
//其中Ｍ应该是一个比“x的最大值和y的最小值之差”还要大的数,对于每个节点放灯初始化为M 此题N最大1000,因此M可取2000
//M取得太小,在除、余时就会出错,取太小会导致M*x有y混合起来,除法会过大
int n,m,head[N],cnt,dp[N][2],ans1,ans2;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dp[u][1]=N0;//选灯初始化为N0
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        //u不放灯 v放灯 u->v只被一盏灯照亮所以加1,这个1的个数可通过最终ans%N0求得
        dp[u][0]+=dp[v][1]+1;
        //u放灯 v不放灯 u->v只被一盏灯照亮
        //这里的转移不能求解同时被两盏灯照亮的最多边,这样会和放置最少灯转移相矛盾
        //但可以同时求解最小值,被一盏灯照亮的最少边,不过这里也不一定能求被一盏灯照亮的最少边,最终要和dp[u][0]结合起来判断
        dp[u][1]+=min(dp[v][0]+1,dp[v][1]);
    }
}

int main() {
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        cnt=ans1=ans2=0;
        memset(dp,0,sizeof(dp));
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){
            if(!dp[i][1]){
                dfs(i,-1);
                ans1+=min(dp[i][0],dp[i][1])/N0;//求出放置最少灯数
                ans2+=min(dp[i][0],dp[i][1])%N0;//求出被一盏灯照亮的最少边
            }
        }
        printf("%d %d %d\n",ans1,m-ans2,ans2);//m-ans2 为同时被两盏灯照亮的最多边
    }
    return 0;
}

*/
