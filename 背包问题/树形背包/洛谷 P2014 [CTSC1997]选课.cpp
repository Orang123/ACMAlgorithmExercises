/*
题意:在大学里每个学生,为了达到一定的学分,必须从很多课程里选择一些课程来学习,
在课程里有些课程必须在某些课程之前学习,如高等数学总是在其它课程之前学习.
现在有N门功课,每门课有个学分,每门课有一门或没有直接先修课(若课程a是课程b的先修课即只有学完了课程 a,
才能学习课程 b).一个学生要从这些课程里选择m门课程学习,问他能获得的最大学分是多少?
链接:https://www.luogu.com.cn/problem/P2014
思路:树上分组背包、树形后序遍历01背包、左儿子右兄弟树记忆化搜索即可.
但注意是恰好装满背包,树上分组背包 会多算入一个0号虚拟根节点.
*/
//ac 47ms 树上分组背包+子树容量剪枝 精简版 O(n*v^2)
//注意是恰好装满背包 初始化 dp[u][1]=val[u];
//因为会多余算上0号虚拟节点 所以实际背包容量是m+1
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 310
#define M 310
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
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&k,&val[i]);
        addEdge(k,i);
    }
    dfs(0,m+1);
    printf("%d",dp[0][m+1]);//0号虚拟根节点会多余算上,所以总共要选m+1个节点
    return 0;
}

/*
//ac 47ms 树上分组背包 AcWing 闫神版本 O(n*v^2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 310
#define M 310
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

void dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        dfs(v);
        for(int j=m;j>=0;j--){
            for(int k=0;k<=j;k++)
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
        }
    }
    for(int i=m+1;i>=1;i--)
        dp[u][i]=dp[u][i-1]+val[u];
    for(int i=0;i<1;i++)
        dp[u][i]=0;
}

int main(){
    int k;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&k,&val[i]);
        addEdge(k,i);
    }
    dfs(0);
    printf("%d",dp[0][m+1]);
    return 0;
}
*/

/*
//ac 15ms 树形后序遍历01背包+剪枝 复杂度O(nv)
//这个做法背包容量是m,也是恰好装满所以 初始化dp[0..n][0]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 310
#define M 310
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
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&k,&val[i]);
        addEdge(k,i);
    }
    memset(dp,-0x3f,sizeof(dp));
    for(int i=0;i<=n;i++)
        dp[i][0]=0;
    //dp[0][0]=0;//其实只用初始化0号虚拟节点即可,因为子节点会继承父节点的状态
    //这个做法 0号节点并不计算进去,所以容量是m
    dfs(0,m);
    printf("%d",dp[0][m]);
    return 0;
}
*/

/*
//ac 71ms 记忆化搜索 多叉树用 左儿子右兄弟树表示 复杂度O(n*v^2)
//摘自洛谷网友caoyihong
//先将树转换成左儿子右兄弟树。对于每一个 i 节点，定义dp( i , j ) 为 i 的所有兄弟和 i 的所有儿子，
// 和 i 自己，学 j 门课的最大学分总和。
//那么，可以分成两种情况：
//不学 i 这门课，全部学兄弟的课程，dp( i , j ) = dp( bro[ i ] , j)
//学 i 以及以 i 为先修课的课程,dp( i , j ) = dp( bro[ i ] , j - 1 - k ) + dp( son[ i ] , k ) + v[ i ]
#include<bits/stdc++.h>
using namespace std;
const int maxn = 320;
int f[maxn][maxn] , bro[maxn] , son[maxn], v[maxn];
void add(int fa, int s)
{
    bro[s] = son[fa];//兄弟节点 头插法
    son[fa] = s;
}

int dp(int i, int j)
{
    if (i == -1) return 0;
    if (j == 0) return 0;
    if (f[i][j] != -1) return f[i][j];
    int m = -1<<30; //最小值

    // 全分兄弟
    m = max( m, dp(bro[i] , j));

    for (int k = 0; k <= j-1; k++)
    {
        m = max( m , dp(son[i] , k) + dp(bro[i] , j-1-k) + v[i]);
    }
    f[i][j] = m;
    return m;
}
int main()
{
    memset(son , -1, sizeof(son));
    memset(bro , -1, sizeof(bro));
    memset(f   , -1, sizeof(f  ));
    int n, m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int fa,vx;
        cin>>fa>>vx;
        add(fa,i);
        v[i] = vx;
    }
    cout<<dp(0, m+1);
    return 0;
}
*/
