#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1000100
using namespace std;
//dfs+贪心
/*
题意:一棵n个节点的树,现在要将树中的某些边断开再连接,
使得树构成一个n个节点n条边每个点的度为2的环,已知
断开或连接一条边的花费为1,现在求将树变成环的最小花费是多少.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4714
思路:dfs+贪心,考虑对于一棵树有n个分支,做法肯定是要把它尽可能变成一条链,
但是变成链的切法,随着切割的位置不同,所用的花费肯定也不一样.根据观察发现,
如果尽量选择断开与父亲节点的连边将其再次连接合并到别的子树上,这样总体切割连接的花费会比较小.
所以方案就是贪心断开与父亲的连边合并到别的子树上使得父亲节点的分支越来越少,直到没有分支成为一条链为止.
*/

int cnt,n,head[N],ans;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u,int fa){
    int son=0;//计算父亲节点u有多少个分支
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        son+=dfs(v,u);
    }
    if(son>=2){//若这里的分支数大于2
        /*
        如果u不是根节点,那么所需的花费就是(分支数-1)x2,
        x2是断开一条边必须要再连接所以花费是2 这个花费里花费1是用来断开当前u节点与父亲的连边的,
        剩余的花费用来将子树断开合并成一条链并连接到另一个分支上.
        */
        if(u!=1) ans+=(son-1)<<1;
        //若u是1根节点,则花费为(分支数-2)x2,因为根节点可以剩下2个分支,等到最终成为一条直链时再连接链的两端点,ans+1
        else ans+=(son-2)<<1;
        return 0;//因为u的子树已经脱离父节点变成一条链连接到别的分支上了,所以这里已经没有分支了 返回0.
    }
    return 1;//当没有分支或只有一个分支时,统一当做一条链有一个分支处理 返回1
}

int main(){
    int u,v,T;
    scanf("%d",&T);
    while(T--){
        cnt=ans=0;
        memset(head,-1,sizeof(head));
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        dfs(1,-1);
        printf("%d\n",ans+1);//最后再将最终的一条直链两端点连接成为题目要求的环,因此ans+1
    }
    return 0;
}

/*
树形dp做法 不理解
#pragma comment(linker,"/STACK:1024000000,1024000000")
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
vector<int> G[1000005];
int dp[1000005][3],vis[1000005];                //dp[i][j]表示以i为根节点的子树，可用度
void dfs(int s){                                //为j时树的分支数，也就是还可以连j个节点
    int i,tmp;                                  //时树的分支数
    vis[s]=1;
    dp[s][0]=dp[s][1]=dp[s][2]=1;
    for(i=0;i<G[s].size();i++){
        tmp=G[s][i];
        if(!vis[tmp]){
        dfs(tmp);                               //两个分支合并则减1
        dp[s][0]=min(dp[s][0]+dp[tmp][0],dp[s][1]+dp[tmp][1]-1);
        dp[s][1]=min(dp[s][1]+dp[tmp][0],dp[s][2]+dp[tmp][1]-1);
        dp[s][2]=dp[s][2]+dp[tmp][0];           //保证s节点为根的子树可用度为2，则不能在向上添加节点
        }
    }
}
int main(){
    int i,j,t,u,v,n,ans;
    scanf("%d",&t);
    while(t--){
        ans=0;
        memset(dp,0,sizeof(dp));
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(i=1;i<=n;i++)
        G[i].clear();
        for(i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1);
        ans=min(min(dp[1][0],dp[1][1]),dp[1][2]);
        printf("%d\n",2*ans-1);                 //知道分支数，则答案就是分支数-1+分支数，也就是
    }                                           //先分离在合并
    return 0;
}
*/
