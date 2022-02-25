#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
using namespace std;

/*
题意:求无向树中子树权值和的最大值
链接:http://poj.org/problem?id=1192
思路:
dp[u][0]代表以u为根节点的子树不包括u节点的权值最大和
dp[u][1]代表以u为根节点的子树包括u节点的权值最大和
*/

int dp[N][2],head[N],a[N],b[N],val[N],cnt;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}
//O(V+E)
void dfs(int u,int fa){
    dp[u][0]=0;
    dp[u][1]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        /*
        若不选u节点权值,则选择u节点子树中权值和较大的子树作为dp[u][0]的值,
        对于某个子树中的v点 可能选也可能不选,总之是选取权值较大的情况
        */
        dp[u][0]=max(dp[u][0],max(dp[v][0],dp[v][1]));
        /*
        若选择u节点权值,那么对于子树的权值和只要不小于0则都加上,若dp[v][1]小于0,
        则dp[u][1]不加dp[v][1]这课子树.
        */
        dp[u][1]+=max(dp[v][1],0);
    }
}

int main(){
    int n;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&a[i],&b[i],&val[i]);
    //i和j=i+1开始比较是为了避免2节点之间重复连边
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(abs(a[i]-a[j])+abs(b[i]-b[j]) == 1){//横纵坐标差和不超过1的点之间连边
                addEdge(i,j);
                addEdge(j,i);
            }
        }
    }
    dfs(1,-1);
    printf("%d",max(dp[1][0],dp[1][1]));
    return 0;
}

/*
暴力遍历整棵树,尽可能多加每个节点的权值,求取最大权值和
和最大连续子序列和差不多
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define INF -0x3f3f3f3f
using namespace std;

int dp[N],head[N],a[N],b[N],cnt,ans=INF;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        dp[u]+=max(dp[v],0);//只要子树权值和不为负就加上
    }
    //记录以每一个节点为根节点的子树权值和的最大值 实际父节点可能不一定有子节点为根的子树权值和大,因为父节点本身权值可能是负数很小
    ans=max(ans,dp[u]);
}

int main(){
    int n;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&a[i],&b[i],&dp[i]);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(abs(a[i]-a[j])+abs(b[i]-b[j]) == 1){
                addEdge(i,j);
                addEdge(j,i);
            }
        }
    }
    dfs(1,-1);
    printf("%d",ans);
    return 0;
}
*/
