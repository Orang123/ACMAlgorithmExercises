#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define INF 0x3f3f3f3f
using namespace std;
//ac 93ms
/*
题意:n个岛屿,m座桥将n座岛屿连通,每座桥连接2个岛屿,两个岛屿间不止一座桥,
每座桥派一定士兵把守(岛屿把守士兵人数可能为0),现在需要炸掉一座桥使得
原岛屿不连通,炸掉一座桥应该派的人数必须大于等于桥上把守士兵的人数.
现在问最少需要派多少人去炸桥,才能使得岛屿分散断开连接.

释义:n个点,m条边的无向图,含有重边,每条边有权值,现在需要找到权值最小的割边.
注意:
1.如果岛屿本身就不连通,则无需派人去炸桥.
2.如果边权最小为0,至少也应派一人去炸桥.
3.如果不存在割边,则输出-1.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4738
思路:tarjan求解连通无向图割边.注意下再判断割边时需要判断两点之间是否
有重边,需要用二维数组bridge记录下两点之间连边的数量.
下面(i^1)!=fa的做法更好一些.
*/

struct node{
    int to,next,w;
}edge[N*N];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int bridge[N+1][N+1];//记录u-v之间连边的数量
int ans;

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            //只有当u-v之间只有一座桥时,即没有重边时该边才是割边,
            //因为如果有2条边,删掉这条边,还有一条边能够使其连通,
            if(dfn[u]<low[v] && bridge[u][v] == 1)
                ans=min(ans,edge[i].w);
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int n,m,a,b,w;
    while(scanf("%d%d",&n,&m) && n || m){
        cnt=num=0;
        ans=INF;
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(bridge,0,sizeof(bridge));
        while(m--){
            scanf("%d%d%d",&a,&b,&w);
            addEdge(a,b,w);
            bridge[a][b]++;//记录a-b之间桥的数量
            addEdge(b,a,w);
            bridge[b][a]++;
        }
        int k=0;
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                k++;//记录连通分量的个数
                dfs(i,-1);
            }
        }
        if(k>1) printf("0\n");//如有2个即2个以上连通分量,则不需要派士兵,本身就是分开的
        else{
            if(ans == 0) printf("1\n");//若割边桥的警卫数最少是0,也还是需要派一个士兵去轰炸
            else printf("%d\n",ans==INF?-1:ans);//若ans==INF说明没有割边,则输出-1,否则输出那座桥的警卫人数
        }
    }
    return 0;
}

/*
//ac 93ms
//(i^1)!=fa 考虑重边导致的某些边不再是割边
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define INF 0x3f3f3f3f
using namespace std;

struct node{
    int to,next,w;
}edge[N*N];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int ans;

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if((i^1) == fa) continue;//考虑重边更新low[u]=min(low[u],dfn[v])导致u-v这样的边不是重边
        if(!dfn[v]){
            dfs(v,i);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
                ans=min(ans,edge[i].w);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int n,m,a,b,w;
    while(scanf("%d%d",&n,&m) && n || m){
        cnt=num=0;
        ans=INF;
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        while(m--){
            scanf("%d%d%d",&a,&b,&w);
            addEdge(a,b,w);
            addEdge(b,a,w);
        }
        int k=0;
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                k++;//记录连通分量的个数
                dfs(i,-1);
            }
        }
        if(k>1) printf("0\n");//如有2个即2个以上连通分量,则不需要派士兵,本身就是分开的
        else{
            if(ans == 0) printf("1\n");//若割边桥的警卫数最少是0,也还是需要派一个士兵去轰炸
            else printf("%d\n",ans==INF?-1:ans);//若ans==INF说明没有割边,则输出-1,否则输出那座桥的警卫人数
        }
    }
    return 0;
}
*/
