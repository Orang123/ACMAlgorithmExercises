/*
题意:有n个物品和一个容量是m的背包.物品之间具有依赖关系,
且依赖关系组成一棵树的形状.如果选择一个物品,则必须选择它的父节点.
如果选择物品5,则必须选择物品1和2.这是因为2是5的父节点,1是2的父节点.
每件物品的编号是i,体积是w[i],价值是val[i],依赖的父节点编号是p[i].
物品的下标范围是1..n.求解在物品总体积不超过背包容量条件下,能获得的最大价值.
1<=n,v<=100
1<=w[i],val[i]<=100
链接:https://www.acwing.com/problem/content/description/10/
思路:树上分组背包.
按照子树分组,每组物品为每棵子树可以分0到j-w[u]任一个体积,等价于每一组中至多只能选一个体积.
*/
//ac 30ms 树上分组背包 精简版本 这个做法实际就是应用了泛化物品的概念
//属于泛化物品的和的思想
//复杂度O(n*v^2)=10^6
//按照子树分组,每组物品为每棵子树可以分0到j-w[u]任一个体积,等价于每一组中只能选一个体积
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int head[N],cnt;
//dp[u][j]代表选择以u为根节点的子树中所有物品,在容量不超过j时所获得的最大价值
int n,m,w[N],val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    //要选u的子树节点,则其父节点u是必须选的.
    //预处理dp[u][w[u]..m]=val[u]
    for(int i=w[u];i<=m;i++)
        dp[u][i]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        dfs(v);
        /*
        u的背包容量下限是w[u],小于w[u]时无法选择u节点,自然无法选择u的子树节点
        这里dp[u][j]实际对于每个子树分组采用了滚动数组优化,优化掉了dp[v][u][j]
        dp[v][u][j]代表在父节点为u,已遍历过的子树节点集合v,在背包容量为j时能获得的最大价值.
        每次dfs回溯回来,会将新遍历完的v子树作为新的一组,该组物品为对当前子树分配所有可能体积
        下对应的子树最大价值,而上一状态是之前已经遍历完的所有子树节点v'的在容量j下最大价值,
        现在是将u的子节点(兄弟节点)间的分组,dp的"组"的阶段优化掉了.
        */
        //因为采用滚动数组优化所以背包容量j必须降序,才能使得dp[u][j-k]表达的是上一状态以u为
        //根节点之前遍历过的子树集合v'容量为j时能获得的最大价值.否则升序会导致dp[u][j-k]已经
        //包括当前以v为根节点的子树的节点的价值,再加dp[v][k]会导致v子树节点重复累加.
        for(int j=m;j>=w[u];j--){
            //以v为根节点的子树,可分配的容量最大为j-w[u],必须保证u节点至少分配w[u],
            //才能保证u节点可以选的前提下,才能选u的子树节点,v子树容量最少可以为0
            //其实k的下界应该是w[v],因为dp[v][w[v]..tot]才是合法的,但是HDU 1011那题错了.但是金明预算方案那题下界写成w[v]是正确的
            //for(int k=w[v];k<=j-w[u];k++)//可以ac 10ms
            for(int k=0;k<=j-w[u];k++)//可升序、可降序 k的下界之所以取0是因为有些题里 物品体积可能为0.
                /*
                等号左边的dp[u][j]代表的是当前以u为根节点之前遍历过的子树集合v'与当前刚遍历完的子树v的
                所有节点并集在容量为j时能获得的最大价值.实际没滚动数组优化的表示法为dp[v'∪v][u][j]
                等号右边即不选当前以v为根节的子树dp[u][j]代表当前以u为根节点之前遍历过的子树集合v'
                容量为j时能获得的最大价值.实际没滚动数组优化的表示法为dp[v'][u][j]

                dp[u][j-k]代表上一状态即:以u为根节点,之前回溯遍历完的所有子树节点集合v'在容量为j-k时的最大价值.
                实际没滚动数组优化的表示为dp[v'][u][j-k].v'为u先前遍历过的所有子树节点的集合.
                dp[v][k]代表以v为根节点的所有子树节点在容量为k时的最大价值.
                */
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
        }
    }
}

int main(){
    int p;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));//初始状态全0,因为不确定哪一个节点是叶子节点会第一个dp
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&w[i],&val[i],&p);
        if(p == -1)//0为虚拟根节点连接 各个子树
            addEdge(0,i);
        else
            addEdge(p,i);//i节点的父节点为p节点
    }
    dfs(0);
    printf("%d",dp[0][m]);
    return 0;
}

/*
//ac 12ms 树上分组背包+剪枝(子树背包容量再不断减少)精简版本
//dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
//复杂度O(n*v^2)
//按照子树分组,每组物品为每棵子树可以分0到j-w[u]任一个体积,等价于每一组中只能选一个体积
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int head[N],cnt;
//dp[u][j]代表选择以u为根节点的子树中所有物品,在容量不超过j时所获得的最大价值
int n,m,w[N],val[N],dp[N][M];

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
    for(int i=w[u];i<=tot;i++)
        dp[u][i]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        //父节点u必选,才能选u的子节点,所以儿子节点的实际容量要减去其所有祖父节点的体积
        dfs(v,tot-w[u]);
        for(int j=tot;j>=w[u];j--){
            //其实k的下界应该是w[v],因为dp[v][w[v]..tot]才是合法的.原版下界是0
            //for(int k=w[v];k<=j-w[u];k++)//可以ac 10ms
            for(int k=w[v];k<=j-w[u];k++)//可升序、可降序
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
        }
    }
}

int main(){
    int p;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));//初始状态全0,因为不确定哪一个节点是叶子节点会第一个dp
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&w[i],&val[i],&p);
        if(p == -1)//0为虚拟根节点连接 各个子树
            addEdge(0,i);
        else
            addEdge(p,i);//i节点的父节点为p节点
    }
    dfs(0,m);
    printf("%d",dp[0][m]);
    return 0;
}
*/

/*
//ac 12ms 树上分组背包+剪枝(子树背包容量再不断减少)精简版本
//另一种转移方式
//dp[u][j+k]=max(dp[u][j+k],dp[u][j]+dp[v][k]);
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int head[N],cnt;
//dp[u][j]代表选择以u为根节点的子树中所有物品,在容量不超过j时所获得的最大价值
int n,m,w[N],val[N],dp[N][M];

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
    for(int i=w[u];i<=tot;i++)
        dp[u][i]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        //父节点u必选,才能选u的子节点,所以儿子节点的实际容量要减去其所有祖父节点的体积
        dfs(v,tot-w[u]);
        //这里j必修降序才能保证dp[u][j]是之前遍历的兄弟子树分组的状态
        for(int j=tot;j>=w[u];j--){
            //这里如果实际物品的体积不会为0,那么k的下界应该是1,那么升序降序都是可以的
            //但是如果物品体积存在为0的情况,那么从0开始升序就是错的,因为k=0时,
            //dp[u][j+0]=dp[u][j]=max(dp[u][j],dp[u][j]+dp[v][0])
            //当k在1~tot-j间时,转移方程中的dp[u][j]已经在k=0时包括了 当前v子树的情况,
            //dp[u][j]表示的已经不是u之前遍历的兄弟子树的状态了.
            //因此k=0的情况一定要最后计算,可以考虑从tot-j降序到0或升序从1到tot-j最后再考虑转移k=0的情况.
            for(int k=tot-j;k>=w[v];k--)//原版k的下界为0
                dp[u][j+k]=max(dp[u][j+k],dp[u][j]+dp[v][k]);
            //k从1升序,k=0放在二层循环退出后 单独转移计算
            //for(int k=1;k+j<=tot;k--)
                //dp[u][j+k]=max(dp[u][j+k],dp[u][j]+dp[v][k]);
            //dp[u][j]=max(dp[u][j],dp[u][j]+dp[v][0]);
        }
    }
}

int main(){
    int p;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));//初始状态全0,因为不确定哪一个节点是叶子节点会第一个dp
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&w[i],&val[i],&p);
        if(p == -1)//0为虚拟根节点连接 各个子树
            addEdge(0,i);
        else
            addEdge(p,i);//i节点的父节点为p节点
    }
    dfs(0,m);
    printf("%d",dp[0][m]);
    return 0;
}
*/

/*
//ac 22ms 树上分组背包 ACwing闫神代码版本
//复杂度O(n*v^2)
//按照子树分组,每组物品为每棵子树可以分0到j-w[u]任一个体积,等价于每一组中只能选一个体积
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int head[N],cnt;
int n,m,w[N],val[N],dp[N][M];

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
        //因为u是该v子树的根节点,所以必选,预留出u的空间 j上界是m-w[u]
        //因为已经在总容量m基础上预留出w[u]了,因此j下界可以为0
        for(int j=m-w[u];j>=0;j--){//滚动数组优化 必须降序
            //枚举该子树分配到的体积
            for(int k=w[v];k<=j;k++)//原版 k下界是0
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
        }
    }
    //将各个v子树的根节点加进去
    //注意这里背包容量i同样必须是降序,才能保证dp[u][i-w[u]]是预先腾出w[u]空间下的最优解
    for(int i=m;i>=w[u];i--)
        dp[u][i]=dp[u][i-w[u]]+val[u];
    //如果无法选u根节点则子树节点也都无法选,价值为0
    for(int i=0;i<w[u];i++)
        dp[u][i]=0;
}

int main(){
    int p;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&w[i],&val[i],&p);
        if(p == -1)
            addEdge(0,i);
        else
            addEdge(p,i);
    }
    dfs(0);
    printf("%d",dp[0][m]);
    return 0;
}
*/

/*
//ac 10ms dfs过程中后序遍历顺序进行01背包
//标准01背包复杂度O(nv)
//dp不选第i个物品的上一状态是i节点左侧兄弟节点所在子树 后序遍历的最后一个节点的状态
//即不选i节点,i节点的子树节点就都不能选
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int head[N],cnt;
int n,m,w[N],val[N],dp[N][M];

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
        for(int j=0;j<=m;j++)
            dp[v][j]=dp[u][j];
        dfs(v);
        for(int j=m;j>=w[v];j--)
            dp[u][j]=max(dp[u][j],dp[v][j-w[v]]+val[v]);
    }
}

int main(){
    int p;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&w[i],&val[i],&p);
        if(p == -1)
            addEdge(0,i);
        else
            addEdge(p,i);
    }
    dfs(0);
    printf("%d",dp[0][m]);
    return 0;
}
*/

/*
//ac 10ms dfs过程中后序遍历顺序进行01背包+剪枝 子树背包容量是不断减少得到
//参考自徐持衡《浅谈几类背包》中的做法
//标准01背包复杂度O(nv)
//dp不选第i个物品的上一状态是i节点左侧兄弟节点所在子树 后序遍历的最后一个节点的状态
//即不选i节点,i节点的子树节点就都不能选
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int head[N],cnt;
int n,m,w[N],val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int tot){
    //剪枝 u节点之前的所有祖父节点(必选)已经将背包容量耗费完,已经无法装下u节点 返回
    if(tot<=0)
        return;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        //要选v的子树中的节点,就得保证v节点必须选上,因此v子树中实际容量只有tot-w[v],
        //需要腾出w[v]空间使得v节点必须选上,dp[u][j]之前遍历子树的状态赋值给将要遍历的v节点子树作为初始状态
        for(int j=0;j<=tot-w[v];j++)
            dp[v][j]=dp[u][j];
        dfs(v,tot-w[v]);
        //v子树节点的状态已经遍历完,再加上v节点,此时背包容量是tot
        for(int j=tot;j>=w[v];j--)//降序、升序皆可
            dp[u][j]=max(dp[u][j],dp[v][j-w[v]]+val[v]);
    }
}

int main(){
    int p;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&w[i],&val[i],&p);
        if(p == -1)
            addEdge(0,i);
        else
            addEdge(p,i);
    }
    dfs(0,m);
    printf("%d",dp[0][m]);
    return 0;
}
*/

/*
//ac 10ms 徐持衡《浅谈几类背包问题》做法
//复杂度(nv)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int head[N],cnt;
int n,m,w[N],val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int tot){
    //剪枝 u节点之前的所有祖父节点(必选)已经将背包容量耗费完,已经无法装下u节点 返回
    if(tot<=0)
        return;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        //要选v的子树中的节点,就得保证v节点必须选上,因此v子树中实际容量只有tot-w[v],
        //需要腾出w[v]空间先分给v节点,dp[u][j]之前遍历子树的状态+v节点价值赋值给将要遍历的v节点子树作为初始状态
        //v子树的初始状态已经将v节点价值包括
        for(int j=0;j<=tot-w[v];j++)
            dp[v][j]=dp[u][j]+val[v];
        dfs(v,tot-w[v]);
        //v子树所有节点(包括v)的状态已经遍历完,在考虑实际背包容量为tot时的转移,dp[v][j]=dp[v][j-w[v]] j范围为tot..w[v]
        for(int j=tot;j>=w[v];j--)//降序、升序皆可
            dp[u][j]=max(dp[u][j],dp[v][j-w[v]]);
    }
}

int main(){
    int p;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&w[i],&val[i],&p);
        if(p == -1)
            addEdge(0,i);
        else
            addEdge(p,i);
    }
    dfs(0,m);
    printf("%d",dp[0][m]);
    return 0;
}
*/

/*
//ac 10ms dfs计算出后序遍历顺序再进行01背包
//标准01背包复杂度O(nv)
//dp不选第i个物品的上一状态是i节点左侧兄弟节点所在子树 后序遍历的最后一个节点的状态
//即不选i节点,i节点的子树节点就都不能选
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

int head[N],cnt,id;
int n,m,w[N],val[N],dp[N][M],pre[N],newid[N];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    int dfn=id;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        dfs(v);
    }
    newid[++id]=u;
    pre[id]=dfn;
}

int main(){
    int p;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&w[i],&val[i],&p);
        if(p == -1)
            addEdge(0,i);
        else
            addEdge(p,i);
    }
    dfs(0);
    for(int i=1;i<=n;i++){
        for(int j=m;j>=0;j--){
            if(j>=w[newid[i]])
                dp[i][j]=max(dp[pre[i]][j],dp[i-1][j-w[newid[i]]]+val[newid[i]]);
            else
                dp[i][j]=dp[pre[i]][j];
        }
    }
    printf("%d",dp[n][m]);
    return 0;
}
*/

/*
//ac 22ms 记忆化搜索 多叉树用左孩子兄弟节点表示 暂时未理解做法
//复杂度O(n*v^2)
//这个做法 本身背包问题 记忆化搜索做法 还是有点疑惑,正确性不一定能得到保障,因此暂时也没咋看这个记忆化搜索
//摘自 AcWing网友:福如东海 https://www.acwing.com/solution/content/5780/
#include <iostream>

using namespace std;

const  int C = 105;
int n, m;

int v[C], w[C];
int l[C], r[C]; //分别存储左孩子和右孩子,如果是多叉树，采用左孩子，右兄弟的方法存储
int bigson[C];

int f[C][C];

int dfs(int i, int j) {
    if (f[i][j] || i == 0 || j == 0) return f[i][j];
    f[i][j] = dfs(r[i], j);
    for (int k = 0; k <= j - v[i];  k ++)
        //dfs(l[i], j-v[i] - k) 给i的左儿子分 j-v[i] - k 体积
        //dfs(r[i], k) + w[i]) 给i的右儿子分 k体积
        f[i][j]  = max(f[i][j], dfs(l[i], j-v[i] - k)+ dfs(r[i], k) + w[i]);
     return f[i][j];
}

int main() {
    cin >> n >> m;
    int root = 0;
    for (int i = 1; i <= n; i ++) {
        int p;
        cin >> v[i] >> w[i] >> p;
        if (p == -1) root = i;
        else {
            if (bigson[p] == 0) l[p] = i;
            else r[bigson[p]] = i;
            bigson[p] = i;

        }
    }
    cout << dfs(root, m) << endl;
    return 0;
}
*/
