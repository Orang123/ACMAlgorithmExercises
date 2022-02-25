/*
题意:摘自网上
n个点的树，求任意两点间路径权值w异或的最大值。
n<=100000.w<2^31.
链接:http://poj.org/problem?id=3764
思路:dfs预处理出从0点出发到达每个点的异或值dp[v],
则任意两点(u,v)的间路径的异或值为dp[u]^dp[v],接下来
对所有点的异或值构建01字典树,之后枚举每个点的异或值
在01字典树查找和其异或值最大的点,计算最大的异或值.
*/

//ac 704ms
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 3200010
#define M 100010
using namespace std;

int n,tr[N][2],cnt,dp[M],ans;

int head[M],num;
struct Edge{
	int to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
	edge[num]=(Edge){to,head[from],w};
	head[from]=num++;
}

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=0;
    return cnt;
}

void insertWord(int val){
    int son,rt=0;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;//val 第i位为son(0或1)
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
}

int findWord(int val){
    int son,rt=0,res=0;
    for(int i=30;i>=0;i--){//最多31位,int就可以存储
        son=val>>i & 1;
        if(tr[rt][son^1]){//如果存在和其son值不同的,这第i位可以为1
            res|=1<<i;//记录路径异或最大值
            rt=tr[rt][son^1];
        }
        else
            rt=tr[rt][son];
    }
    return res;
}

void dfs(int u,int fa){
    insertWord(dp[u]);
    int v,w;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        w=edge[i].w;
        if(v == fa)
            continue;
        dp[v]=dp[u]^w;
        dfs(v,u);
    }
}

int main(){
    int u,v,w;
    while(scanf("%d",&n)!=EOF){
        ans=0;
        cnt=-1;
        newNode();
        memset(head,-1,sizeof(head));
        num=0;
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        dfs(0,-1);
        for(int i=0;i<n;i++)
            ans=max(ans,findWord(dp[i]));
        printf("%d\n",ans);
    }
    return 0;
}

/*
//TLE stl vector建图 常数时间超时
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 3200010
#define M 100010
using namespace std;

int n,tr[N][2],cnt,dp[M],ans;
vector<pair<int,int> > G[M];

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=0;
    return cnt;
}

void insertWord(int val){
    int son,rt=0;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;//val 第i位为son(0或1)
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
}

int findWord(int val){
    int son,rt=0,res=0;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;
        if(tr[rt][son^1]){
            res|=1<<i;
            rt=tr[rt][son^1];
        }
        else
            rt=tr[rt][son];
    }
    return res;
}

void dfs(int u,int fa){
    insertWord(dp[u]);
    int v,w;
    for(int i=0;i<G[u].size();i++){
        v=G[u][i].first;
        w=G[u][i].second;
        if(v == fa)
            continue;
        dp[v]=dp[u]^w;
        dfs(v,u);
    }
}

int main(){
    int u,v,w;
    while(scanf("%d",&n)!=EOF){
        ans=0;
        cnt=-1;
        newNode();
        for(int i=0;i<n;i++)
            G[i].clear();
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            G[u].push_back(make_pair(v,w));
            G[v].push_back(make_pair(u,w));
        }
        dfs(0,-1);
        for(int i=0;i<n;i++)
            ans=max(ans,findWord(dp[i]));
        printf("%d\n",ans);
    }
    return 0;
}
*/
