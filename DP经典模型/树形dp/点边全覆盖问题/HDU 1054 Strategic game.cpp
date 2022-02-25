#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
//ac 202ms 树形dp O(V+E)
/*
题意:一个呈树形的城市,每个地区之间的道路需要派士兵看守,士兵被安置在道路的交点上,
士兵能同时看守相邻的所有道路,问最少放置几个士兵可以看守玩所有道路.
释义:就是一棵树 用尽可能少的点覆盖所有的边.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1054
思路:树形dp O(V+E) dp[i][0] dp[i][1]分别代表 结点i不放置士兵和结点i放置士兵看守所有子树中道路需要放置的最少士兵数.
也可以转化为二分图中的 最小顶点覆盖=最大匹配 O(VE)
*/

int head[1600],cnt,dp[1600][2];
struct Node{
    int to,next;
}edge[3200];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}
//O(V+E)
void dfs(int u,int fa){
    dp[u][0]=0;//不放置
    dp[u][1]=1;//放置 算上自己本身
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v==fa) continue;
        dfs(v,u);
        dp[u][0]+=dp[v][1];//若该点不放置士兵则u->v这条边必然需要v这个点的士兵看守,所以v点一定要放置士兵
        /*
        在u点放置条件下,v点不放置不一定比v点不放置答案更优.
        列如u->v v->a v->b v->c v->d  如果u点放置v点不放置士兵,
        那么a b c d四个点都需要放置士兵,但是如果v点也放置士兵,
        a b c d四个点便都不需要放置士兵.
        */
	//若该点放置士兵,则v点可放置也可不放置
	//假如v点儿子很多,那么v点放置士兵,v的很多儿子就不必放,如果v点就一个儿子,那么v点就可以不放,让v的儿子来放
        dp[u][1]+=min(dp[v][0],dp[v][1]);
    }
}

int main(){
    int n,m,u,v;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        while(n--){
            scanf("%d:(%d)",&u,&m);
            while(m--){
                scanf("%d",&v);
                addEdge(u,v);
                addEdge(v,u);
            }
        }
        dfs(0,-1);
        printf("%d\n",min(dp[0][0],dp[0][1]));
    }
    return 0;
}
/*
//ac 202ms 记忆化搜索
//u点不放置士兵dp[u][0]和放置士兵dp[u][1] 其子树分支中节点v
//都会有2种状态,要么放置士兵dp[v][1],要么不放置士兵dp[v][0],所以对于重叠子问题只需求解一次.
//树形dp是会产生重叠子问题的
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int head[1600],cnt,dp[1600][2];
struct Node{
    int to,next;
}edge[3200];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u,int k,int fa){
    int ans=k;
    if(dp[u][k]) return dp[u][k];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v==fa) continue;
        if(k)//这里k==0 和k==1里的 dfs(v,1,u)会重复遍历.所以开头要if(dp[u][k]) 判断
            ans+=min(dfs(v,0,u),dfs(v,1,u));
        else
            ans+=dfs(v,1,u);

    }
    return dp[u][k]=ans;
}

int main(){
    int n,m,u,v;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(dp,0,sizeof(dp));
        memset(head,-1,sizeof(head));
        while(n--){
            scanf("%d:(%d)",&u,&m);
            while(m--){
                scanf("%d",&v);
                addEdge(u,v);
                addEdge(v,u);
            }
        }
        printf("%d\n",min(dfs(0,0,-1),dfs(0,1,-1)));
    }
    return 0;
}
*/

/*
//ac 202ms 最小顶点覆盖=最大匹配 时间戳优化的hungary 和交叉染色法划分集合 支配对一个集合中的点
//O(VE)
#include<cstdio>
#include<cstring>
#define N 2000

int n,m,cnt,head[N],color[N],vis[N],link[N],ans;
struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa,int col){
    color[u]=col;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u,col^1);
    }
}

int hungary(int u,int clock){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v] == clock) continue;
        vis[v]=clock;
        if(link[v] == -1 || hungary(link[v],clock)){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=0;
    memset(head,-1,sizeof(head));
    memset(link,-1,sizeof(link));
    memset(vis,-1,sizeof(vis));
}

int main(){
    int u,v;
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            scanf("%d:(%d)",&u,&m);
            while(m--){
                scanf("%d",&v);
                addEdge(u,v);
                addEdge(v,u);
            }
        }
        dfs(0,-1,0);
        for(int i=0;i<n;i++){//O(VE)
            if(color[i]) continue;
            if(hungary(i,i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 343ms 最小顶点覆盖=最大匹配 暴力建边 跑所有点的配对,结果除2
#include<cstdio>
#include<cstring>
#define N 2000

int n,m,cnt,head[N],vis[N],link[N],ans;
struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int hungary(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(link[v] == -1 || hungary(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=0;
    memset(head,-1,sizeof(head));
    memset(link,-1,sizeof(link));
}

int main(){
    int u,v;
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            scanf("%d:(%d)",&u,&m);
            while(m--){
                scanf("%d",&v);
                addEdge(u,v);
                addEdge(v,u);
            }
        }
        for(int i=0;i<n;i++){//O(VE)
            memset(vis,0,sizeof(vis));
            if(hungary(i)) ans++;
        }
        printf("%d\n",ans/2);
    }
    return 0;
}
*/
