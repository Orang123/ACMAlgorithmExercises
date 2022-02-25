/*
题意:ACboy很喜欢玩一种战略游戏，在一个地图上，有N座城堡，
每座城堡都有一定的宝物，在每次游戏中ACboy允许攻克M个城堡并
获得里面的宝物。但由于地理位置原因，有些城堡不能直接攻克，
要攻克这些城堡必须先攻克其他某一个特定的城堡。你能帮ACboy算出
要获得尽量多的宝物应该攻克哪M个城堡吗？
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1561
思路:树上分组背包、树形后序遍历01背包、左儿子右兄弟树记忆化搜索即可.
但注意是恰好装满背包,树上分组背包 会多算入一个0号虚拟根节点.
*/
//ac 78ms 树上分组背包+子树背包容量剪枝 精简版 O(n*v^2)
//注意是恰好装满背包 初始化 dp[u][1]=val[u];
//因为会多余算上0号虚拟节点 所以实际背包容量是m+1
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define M 210
using namespace std;

int head[N],cnt;
int n,m,val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int tot){
    if(tot<=0)
        return;
    //恰好装满背包
    dp[u][1]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        dfs(v,tot-1);
        //上界m+1
        for(int j=tot;j>=2;j--){
            for(int k=1;k<=j-1;k++)
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
        }
    }
}

int main(){
    int k;
    while(scanf("%d%d",&n,&m) && n+m){
        cnt=0;
        memset(head,-1,sizeof(head));
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&k,&val[i]);
            addEdge(k,i);
        }
        dfs(0,m+1);
        printf("%d\n",dp[0][m+1]);//0号虚拟根节点会多余算上,所以总共要选m+1个节点
    }
    return 0;
}

/*
//ac 15ms 树形后序遍历01背包+子树背包容量剪枝
//这个做法背包容量是m,也是恰好装满所以 初始化dp[0..n][0]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define M 210
using namespace std;

int head[N],cnt;
int n,m,val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int tot){
    if(tot<=0)
        return;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        for(int j=0;j<=tot-1;j++)
            dp[v][j]=dp[u][j];
        dfs(v,tot-1);
        for(int j=tot;j>=1;j--)
            dp[u][j]=max(dp[u][j],dp[v][j-1]+val[v]);
    }
}

int main(){
    int k;
    while(scanf("%d%d",&n,&m) && n+m){
        cnt=0;
        memset(head,-1,sizeof(head));
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&k,&val[i]);
            addEdge(k,i);
        }
        dfs(0,m);
        printf("%d\n",dp[0][m]);//0号虚拟根节点会多余算上,所以总共要选m+1个节点
    }
    return 0;
}
*/

/*
//左儿子有兄弟树结构 记忆化搜索
//摘自博客:https://blog.csdn.net/qq_39479426/article/details/81517925
#include<iostream>
#include<string.h>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
using namespace std;
const int INF = 1<<29;
const int MAX = 250;
int N, M;
int dp[MAX][MAX];   //dp[i][j]表示i结点为根结点,在i结点下选择j个城堡获得的最大收益
vector<int> G[MAX];
int val[MAX];
int tree[MAX][2];   //左孩子右兄弟
int visit[MAX][MAX];

void init()
{
    memset(tree, -1, sizeof(tree));
    memset(val, 0, sizeof(val));
    memset(dp, 0, sizeof(dp));
    memset(visit, 0, sizeof(visit));
    for (int i = 0; i <= N; i++)
        G[i].clear();
}

void extree()
{
    for (int i = 0; i <= N; i++)
    {
        int len = G[i].size();
        for (int j = 0; j < len; j++)
        {
            if (j == 0)
                tree[i][0] = G[i][j];   //tree[i][0]是结点i的儿子结点
            else
                tree[G[i][j-1]][1] = G[i][j];   //ree[G[i][j-1]][1]是结点G[i][j-1]的兄弟结点
        }
    }
}

//p结点下攻克m座城堡的价值
void dfs(int p, int m)
{
    if (visit[p][m])   //没有标记位会TLE
        return;
    visit[p][m] = 1;
    if (p == -1 || m <= 0)
        return;
    dfs(tree[p][1], m);
    dp[p][m] = max(dp[p][m], dp[tree[p][1]][m]);

    for (int i = 0; i <= m - 1; i++)//p结点占用1个
    {
        dfs(tree[p][1], i); //兄弟结点取i个
        dfs(tree[p][0], m - 1 - i); //儿子结点取(m-1-i)个
        dp[p][m] = max(dp[p][m], dp[tree[p][0]][m-1-i] + dp[tree[p][1]][i] + val[p]);
    }
}

int main()
{
    while ((cin >> N >> M) && N && M)
    {
        init();
        for (int i = 1; i <= N; i++)
        {
            int a, b;
            cin >> a >> b;
            G[a].push_back(i);
            val[i] = b;
        }
        extree();
        dfs(0, M + 1);
        cout << dp[0][M+1] << endl;
    }

    return 0;
}
*/
