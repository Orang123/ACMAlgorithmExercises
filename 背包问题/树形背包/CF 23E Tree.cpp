/*
题意:给出一棵树,求删除某些边使得树被分割独立出的各个连通分量对应的顶点数乘积最大.
1<=n<=700
链接:http://codeforces.com/contest/23/problem/E
思路:树上分组背包.
dp[i][j]代表以i为根节点的子树所在连通块整体节点数为j时的最大乘积.注意这个i根节点所在
连通块只是相连的部分(只有一块,一个整体),剩下被分割孤立出去的连通分量只统计了其节点个
数算入到了最大乘积里.注意dp[i][j]中j!=0时,乘积数值中并不包括与i相连的j个连通块的数值因子.
显然当j=0时,代表将原先i节点与其子树相连通的连通块也独立出去,即所有的连通块都将大小当做
累乘因子贡献出去,因此dp[i][0]=max(dp[i][1..j]*j),dp[i][0]由dp[i][1..j]转移而来,将最后剩余的
与i节点相连的连通块也独立出来,贡献j个点的个数作为乘积因子.因此最终的答案为dp[rt][0],最终
肯定要将所有的连通块都独立出来.

父子节点间的连通分量是有依赖关系的,对于dp[u][j]来说 要得到v的连通块,必须要保留父节点u才行.
*/
//没有加高精度 结果会溢出 dp转移没问题
//不加高精度 第13个测试样例wa了
//dp[u][j+k]=max(dp[u][j+k],dp[u][j]*dp[v][k]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 710
#define M 710
using namespace std;

int cnt,head[N],n,siz[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    siz[u]=1;
    //初始状态 u根节点本身作为一个连通块,大小为1
    dp[u][1]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        //siz[u]是之前兄弟子树节点总个数,不包括当前v的子树节点,siz[u]延迟累加siz[v]
        //j必须降序,j的下界是1,因为这里统计的连通块要连通u的各个子树,必须将u节点作为
        //连接媒介,u节点必选才能将u的各个子树的连通块连接合并成一个更大的连通块.
        //主要dp[u][0]在dp阶段永远都是0 也没意义
        for(int j=siz[u];j>=1;j--){
            //这里k降序的原因是,如果升序,先计算k=0时,dp[u][j]=max(dp[u][j],dp[u][j]*dp[v][0])
            //等k处于1..siz[v]时,dp[u][j]=max(dp[u][j+k],dp[u][j]*dp[v][k]),dp[u][j]*dp[v][k]
            //中的dp[u][j]在k=0时已经将v子树中的各个独立分割出的连通块的因子大小累乘过了,这样
            //dp[u][j]已经包含v子树了,而不是u之前遍历的兄弟子树的连通块累乘的结果了.因此k=0的
            //情况必须最后计算.
            for(int k=siz[v];k>=0;k--)
                //这里是将u之前遍历的兄弟子树中连通块大小为j的块和v子树中连通块大小为k的块,
                //合并成一个连通块大小为j+k的块,当然这些块都包含u节点.
                dp[u][j+k]=max(dp[u][j+k],dp[u][j]*dp[v][k]);
        }
        /*
        //另一种k升序的转移,k=0放在最后单独转移即可.
        for(int j=siz[u];j>=1;j--){
            for(int k=1;k<=siz[v];k++)
                dp[u][j+k]=max(dp[u][j+k],dp[u][j]*dp[v][k]);
            dp[u][j]=max(dp[u][j],dp[u][j]*dp[v][0]);
        }
        */
        siz[u]+=siz[v];
    }
    //计算dp[u][0] 将u子树中的本身保留的最后一块连通块独立出来,
    //即;dp[u][0]是由dp[u][1..siz[u]]*i(当前dp[u][i]保留的最后一块连通块的大小)转移而来,取其最大乘积值
    for(int i=1;i<=siz[u];i++)
        dp[u][0]=max(dp[u][0],dp[u][i]*i);
}

int main(){
    int u,v;
    cnt=0;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    memset(siz,0,sizeof(siz));
    memset(dp,0,sizeof(dp));
    //哪个点作为根节点都不影响结果,只是最终结果是dp[rt][0]
    //dp[rt][0] 整棵树的所有连通块都独立出去,作为累乘因子累乘能得到的最大乘积
    dfs(1,-1);
    printf("%d",dp[1][0]);
    return 0;
}

/*
//没有加高精度 结果会溢出 但是方法没问题
//另一种转移 复杂度大点,同样第13个样例 结果溢出 wa 方法没问题
//dp[u][j]=max(dp[u][j],dp[u][j-k]*dp[v][k]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 710
#define M 710
using namespace std;

int cnt,head[N],n,siz[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    siz[u]=1;
    dp[u][1]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        for(int j=siz[u];j>=1;j--){
            //k的上界是min(siz[v],j-1) 之所以j-1是因为dp[u][0]不考虑,单独在最后转移
            for(int k=0;k<=siz[v] && k<j;k++)
                //在j较大时,k较小时,dp[u][j-k]可能实际就诶呦那么多节点,是无意义的,
                //但这并不影响结果的正确性
                dp[u][j]=max(dp[u][j],dp[u][j-k]*dp[v][k]);
        }
    }
    for(int i=1;i<=siz[u];i++)
        dp[u][0]=max(dp[u][0],dp[u][i]*i);
}

int main(){
    int u,v;
    cnt=0;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    memset(siz,0,sizeof(siz));
    memset(dp,0,sizeof(dp));
    dfs(1,-1);
    printf("%d",dp[1][0]);
    return 0;
}
*/

/*
//ac 216ms 高精度+树形背包
//摘自博客:https://blog.csdn.net/yellowdesk/article/details/51959498
//f[x][j+k]=max(f[x][j]*f[e[i].to][k],f[x][j+k]);
#include <cstdio>
#include <cstring>
#define bit 10000
struct edge{ int to,nxt;}e[2000];
struct number{ int a[100];}ans,f[705][705];
int n,cnt,s[1000],fi[1000];
    number operator*(number x,number y)
    {
        number z;
        memset(z.a,0,sizeof(z.a));
        for (int i=1;i<=x.a[0];++i)
            for (int j=1;j<=y.a[0];++j) z.a[i+j-1]+=x.a[i]*y.a[j];
        z.a[0]=x.a[0]+y.a[0]-1;
        for (int i=1;i<=z.a[0];++i)
        {
            z.a[i+1]+=z.a[i]/bit;
            z.a[i]%=bit;
        }
        if (z.a[z.a[0]+1]) ++z.a[0];
        return z;
    }
    number max(number x,number y)
    {
        if (x.a[0]>y.a[0]) return x;
        if (x.a[0]<y.a[0]) return y;
        for (int i=x.a[0];i;--i)
            if (x.a[i]>y.a[i]) return x;
            else if (x.a[i]<y.a[i]) return y;
        return x;
    }
    number change(int x){ number a;a.a[0]=1;a.a[1]=x;return a;}
    void add(int u,int v)
    {
        e[++cnt].to=v;e[cnt].nxt=fi[u];fi[u]=cnt;
    }
    void dp(int x,int fa)
    {
        s[x]=1;f[x][1].a[0]=f[x][1].a[1]=1;
        for (int i=fi[x];i;i=e[i].nxt)
            if (e[i].to!=fa)
            {
                dp(e[i].to,x);
                for (int j=s[x];j>=1;--j)
                    for (int k=s[e[i].to];k>=0;--k)
                        f[x][j+k]=max(f[x][j]*f[e[i].to][k],f[x][j+k]);
                s[x]+=s[e[i].to];
            }
        f[x][0]=change(s[x]);
        for (int i=1;i<=s[x];++i) f[x][0]=max(f[x][0],f[x][i]*change(i));
    }
    void print(number x)
    {
        printf("%d",x.a[x.a[0]]);
        for (int i=x.a[0]-1;i;--i) printf("%.4d",x.a[i]);
    }
int main()
{
    scanf("%d\n",&n);
    for (int i=1;i<n;++i)
    {
        int u,v;
        scanf("%d%d\n",&u,&v);
        add(u,v);add(v,u);
    }
    dp(1,0);ans=f[1][0];
    print(ans);
    return 0;
}
*/

/*
//TLE 高精度+树形背包 f[x][j-k]*f[e[i].to][k]转移背包容量上界每次都会多出siz[v] 复杂度较大
//第15个样例 n=700TLE
//摘自博客:https://blog.csdn.net/yellowdesk/article/details/51959498
//f[x][j]=max(f[x][j-k]*f[e[i].to][k],f[x][j]);
#include <cstdio>
#include <cstring>
#define bit 10000
struct edge{ int to,nxt;}e[2000];
struct number{ int a[100];}ans,f[705][705];
int n,cnt,s[1000],fi[1000];
    number operator*(number x,number y)
    {
        number z;
        memset(z.a,0,sizeof(z.a));
        for (int i=1;i<=x.a[0];++i)
            for (int j=1;j<=y.a[0];++j) z.a[i+j-1]+=x.a[i]*y.a[j];
        z.a[0]=x.a[0]+y.a[0]-1;
        for (int i=1;i<=z.a[0];++i)
        {
            z.a[i+1]+=z.a[i]/bit;
            z.a[i]%=bit;
        }
        if (z.a[z.a[0]+1]) ++z.a[0];
        return z;
    }
    number max(number x,number y)
    {
        if (x.a[0]>y.a[0]) return x;
        if (x.a[0]<y.a[0]) return y;
        for (int i=x.a[0];i;--i)
            if (x.a[i]>y.a[i]) return x;
            else if (x.a[i]<y.a[i]) return y;
        return x;
    }
    number change(int x){ number a;a.a[0]=1;a.a[1]=x;return a;}
    void add(int u,int v)
    {
        e[++cnt].to=v;e[cnt].nxt=fi[u];fi[u]=cnt;
    }
    void dp(int x,int fa)
    {
        s[x]=1;f[x][1].a[0]=f[x][1].a[1]=1;
        for (int i=fi[x];i;i=e[i].nxt)
            if (e[i].to!=fa)
            {
                dp(e[i].to,x);
                s[x]+=s[e[i].to];
                for (int j=s[x];j>=1;--j)
                    for (int k=0;k<=s[e[i].to] && k<j;k++)
                        f[x][j]=max(f[x][j-k]*f[e[i].to][k],f[x][j]);
            }
        f[x][0]=change(s[x]);
        for (int i=1;i<=s[x];++i) f[x][0]=max(f[x][0],f[x][i]*change(i));
    }
    void print(number x)
    {
        printf("%d",x.a[x.a[0]]);
        for (int i=x.a[0]-1;i;--i) printf("%.4d",x.a[i]);
    }
int main()
{
    scanf("%d\n",&n);
    for (int i=1;i<n;++i)
    {
        int u,v;
        scanf("%d%d\n",&u,&v);
        add(u,v);add(v,u);
    }
    dp(1,0);ans=f[1][0];
    print(ans);
    return 0;
}
*/

