#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

/*
题意:给你一棵n个点的树,点带权,对于每个节点求出距离它不超过k的所有节点权值和m.
链接:https://www.luogu.com.cn/problem/P3047
思路:换根dp+容斥原理
dp[u][k]代表距离u节点为长度k的点的权值和.
两次dfs,dfs1求出每个节点距离所有子树节点的权值和
dfs2由父节点向子节点转移,将每个节点向上反向距离祖父节点中的点权累加更新.
*/

int cnt,n,k,head[N],dp[N][25],ans;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

//求出每个节点距离所有子树节点的权值和
void dfs1(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs1(v,u);
        //由子节点向父节点转移,相同的点距离父节点k,距离子节点就是k-1
        for(int j=1;j<=k;j++)
            dp[u][j]+=dp[v][j-1];
    }
}

//由父节点向子节点转移,将每个节点向上反向距离祖父节点中的点权累加更新.
void dfs2(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        /*
        这里减掉重复值必须倒序,否则2-0 4-2 这样会减得不完整,
        下界是2,dp[v][1]加的是u父亲的点权,是不会重复累加的.
        */
        for(int j=k;j>=2;j--)
            dp[v][j]-=dp[v][j-2];
        /*
        u->v之间本身距离为1,要计算v祖父链上距离v距离为k的点权和,因为u与v之间本身就相距1,
        可以转移为累加距离父节点u距离为k-1的点权和,这个值是dfs1计算u子树节点中的距离点权已经算出的,
        实际就是v的兄弟节点及其兄弟子树中的节点.
        这里除过dp[v][1]+=dp[u][0]是v加上距离v为1的父亲结点u的点权没有重复累加外,
        其余累加祖父链上的反向距离节点点权时,会重复累加v节点本身的这条链上距离u父亲节点k-1的点权,
        所以实际重复累加的是距离v k-2的点权,因为距离v节点正向的点权已经在dfs1中累加过了.因此重复累加的
        值在v更新之前先减掉后续父亲转移时重复的部分.
        eg:1->2,1->3,1->4,2->5,5->6 当u=1,v=2时 dp[2][2]=dp[1][1],这时dp[1][1]包括2、3、4三点的点权,
        但是2的点权是作为距离2为0的点权已经在dfs1中计算过了.2所要累加的祖父链上距离为2的点权只有3 4两个节点.
        */
        for(int j=1;j<=k;j++)
            dp[v][j]+=dp[u][j-1];
        //这里不需要复原dp[v][k],因为v本身就是更新正确的.
        dfs2(v,u);
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",&dp[i][0]);//每个节点距离为0的点权和是节点本身的点权.
    dfs1(1,-1);
    dfs2(1,-1);
    for(int i=1;i<=n;i++){
        ans=0;
        for(int j=0;j<=k;j++)
            ans+=dp[i][j];
        printf("%d\n",ans);
    }
    return 0;
}

/*
另一种换根dp,非容斥做法,提前先把父节点距离子树中会多算的距离减掉,再遍历别的儿子时再恢复.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
//换根dp
int cnt,n,k,head[N],dp[N][25],ans[N];

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}
//将u节点距离v所在链的重复部分减掉
void cut(int u,int v){
    for(int i=1;i<=k;i++)
        dp[u][i]-=dp[v][i-1];
}
//利用u节点的dfs1计算的
void link(int u,int v){
    for(int i=1;i<=k;i++)
        dp[v][i]+=dp[u][i-1];
}

void dfs1(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs1(v,u);
        for(int j=1;j<=k;j++)
            dp[u][j]+=dp[v][j-1];
    }
}

void dfs2(int u,int fa){
    //还没累加之前u节点的dp值都是完整的,记录如ans数组
    for(int i=0;i<=k;i++)
        ans[u]+=dp[u][i];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        //这里因为v累加u祖父链上的点权时,v本身所在的链会重复累加
        //所以在累加之前先把u节点距离v节点所在链的点权减掉
        //先减掉u重复的点权,v再加上距离u的儿子的点权
        cut(u,v),link(u,v);
        dfs2(v,u);
        //因为要遍历u的下一个儿子,因此要再把u节点距离v这条链的点权还原
        //先让v之前加上的祖父链上的点权先减掉,再加上u节点距离v这条链上的点权
        cut(v,u),link(v,u);
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",&dp[i][0]);
    dfs1(1,-1);
    dfs2(1,-1);
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[i]);
    return 0;
}

*/

