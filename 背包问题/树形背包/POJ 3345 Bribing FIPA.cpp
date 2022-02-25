/*
题意:有n个国家来给你投票,想要获得第i个国家的赞成需要花费val[i],
如果某些国家是在国家i的统治下的,当获得国家i的赞成票后,那么他所
统治的其他国家都会投票给你(不再需要花费),求至少获得m赞成票的最小花费.
n<=200;
链接:http://poj.org/problem?id=3345
思路:城市与城市间的统治关系构成森林,树上分组背包.背包容量为城市数量.
dp[i][j]表示以i为根的子树在获得j个国家的赞成票时需要的最小花费.
需要注意的是对于j等于这棵子树的所有节点数时,实际只需要根节点i的花费,那么
i节点下的所有子节点就都会获得赞成票而无需额外花费.即:dp[i][siz[i]]=val[i].
初始状态为dp[i][0]=0,每棵子树所有子节点遍历完成后,dp[i][siz[i]]=val[i].
状态转移方程:dp[u][j]=min(dp[u][j],dp[u][j-t]+dp[v][t]);
注意:dp[u][1]可能并不是获得u节点的投票而是子节点v的1个投票,所以此题并没有严格的
父子节点依赖关系.

因为存在某些国家的统治关系不在任何国家的的统治下单独构成一棵树,因此要将独立的
子树都连向虚拟根节点0构成一棵多叉树.
*/
//ac 79ms
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#define N 210
#define M 210
#define INF 0x3f3f3f3f
using namespace std;

int cnt,head[N],id,n,m,dp[N][M],vis[N],val[N];
map<string,int> mp;

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    //初始为0,转移中不考虑根节点u,s因为对于根节点u的选定 恰好是获得子树所有节点赞成的情况,花费固定为val[u]
    int siz=0;//siz表示根节点为u的子树下总共有多少子节点
    dp[u][0]=0;//初始状态
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        siz+=dfs(v);//当前子树组背包容量是当前已遍历的子树子节点数(不包括根节点u)
        for(int j=siz;j>=1;j--){//下界是1,至少有一个子节点
            for(int t=1;t<=j;t++)//子节点至少为1
                dp[u][j]=min(dp[u][j],dp[u][j-t]+dp[v][t]);
        }
    }
    //siz加上最后的根节点u
    siz++;//最终获得子树所有节点赞成,实际就是只需获得根节点u的赞成,只需花费val[u]
    dp[u][siz]=val[u];
    return siz;
}

int main(){
    char str1[110],str2[110];
    while(gets(str1)){
        if(str1[0] == '#') break;
        id=cnt=0;
        memset(head,-1,sizeof(head));
        memset(vis,0,sizeof(vis));
        mp.clear();
        sscanf(str1,"%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%s",str1);
            if(!mp.count(str1))//国家可能名称会有重复 这里要判断 否则会RE
                mp[str1]=++id;
            scanf("%d",&val[mp[str1]]);
            while(getchar()!='\n'){
                scanf("%s",str2);
                if(!mp.count((string)str2))//国家可能名称会有重复 这里要判断 否则会RE
                    mp[str2]=++id;
                addEdge(mp[str1],mp[str2]);
                vis[mp[str2]]=1;
            }
        }
        for(int i=1;i<=n;i++){
            if(!vis[i])//将各个独立的子树连向虚拟根节点0 构成一棵新的树
                addEdge(0,i);
        }
        memset(dp,0x3f,sizeof(dp));
        dfs(0);
        int ans=INF;
        for(int i=m;i<=n;i++)//至少获得m个国家赞成的最小花费,赞成数小的不一定 花费小,因为赞成数较多的情况,可以通过只花费根节点的花费来获得所有子节点的赞成
            ans=min(ans,dp[0][i]);
        printf("%d\n",ans);
    }
    return 0;
}
