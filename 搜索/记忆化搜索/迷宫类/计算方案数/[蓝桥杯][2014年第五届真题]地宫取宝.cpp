/*
题意:X国王有一个地宫宝库.是n*m个格子的矩阵.每个格子放一件宝贝.
每个宝贝贴着价值标签.地宫的入口在左上角,出口在右下角.
小明被带到地宫的入口,国王要求他只能向右或向下行走.
走过某个格子时,如果那个格子中的宝贝价值比小明手中任意宝贝价值都大,
小明就可以拿起它(当然，也可以不拿).当小明走到出口时,如果他手中的宝
贝恰好是k件,则这些宝贝就可以送给小明.请你帮小明算一算,在给定的局面下,
他有多少种不同的行动方案能获得这k件宝贝.
1< =n,m< =50,1<=k<=12.
每个宝贝的价值0<=Ci<=12.
链接:https://www.dotcpp.com/oj/problem1436.html
思路:记忆化搜索,不同的是 对于每个点状态的计算,需要同时考虑
在该点处所拥有的宝贝数量和手中最大的宝贝价值,
这2个因素会影响后续搜索的唯一因素,所以状态的标识,重叠子问题需要
用四维数组dp[x][y][num][maxVal]来标识.
dp[x][y][num][maxVal]表示到达点(x,y)时取得num个宝贝,并且当前手中
宝贝的最大价值为maxVal时到达(n,m)点的方案数.
dp[x][y][num][maxVal]=-1表示这种情况还未遍历过,需要继续搜索下去.

较详细的博客讲解:https://www.cnblogs.com/fate-/p/12337083.html
*/
//ac 4ms 记忆化搜索
//dp[x][y][num][maxVal]表示到达点(x,y)时取得num个宝贝,并且当前手中宝贝的最大价值为maxVal时到达(n,m)点的方案数
//dp[x][y][num][maxVal]=-1 表示这种情况还未遍历过,需要继续搜索下去
#include<cstdio>
#include<cstring>
#define N 60
#define mod 1000000007
typedef long long ll;

int n,m,k,mp[N][N],dp[N][N][15][15],dir[2][2]={{0,1},{1,0}};

int dfs(int x,int y,int num,int maxVal){
    if(dp[x][y][num][maxVal+1]!=-1)//当前情况还未遍历 maxVal+1是因为,maxVal有可能为-1,数组下标不能为负
        return dp[x][y][num][maxVal+1];
    if(x == n && y == m){
        //到达(n,m)点恰好有k件宝贝,算一种方案返回1
        if(num ==k)
            return dp[x][y][num][maxVal+1]=1;
        //到达(n,m)点恰好有k-1件宝贝,考虑是否能将(n,m)点的宝贝拿起,
        //只要(n,m)点宝贝mp[n][m]比当前手中最大价值还大,则手中宝贝数量达到k件,返回1
        else if(num == k-1 && maxVal<mp[x][y])
            return dp[x][y][num+1][maxVal+1]=1;
        else//其余情况 手中宝贝数一定不足k件,并不算如方案数
            return dp[x][y][num][maxVal+1]=0;
    }
    if(num>k)
        return 0;
    int nx,ny;
    ll res=0;
    for(int i=0;i<2;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>n || ny>m)
            continue;
        if(maxVal<mp[x][y])//如果当前手中最大价值小于(x,y)价值,考虑拿起当前(x,y)的宝贝
            res=(res+dfs(nx,ny,num+1,mp[x][y]))%mod;
        //考虑不拿起(x,y)的宝贝
        res=(res+dfs(nx,ny,num,maxVal))%mod;
    }
    return dp[x][y][num][maxVal+1]=res;
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            scanf("%d",&mp[i][j]);
    }
    memset(dp,-1,sizeof(dp));//需要初始化为-1,因为方案数为0 也是一种结果
    printf("%d",dfs(1,1,0,-1));//maxVal设置为-1是因为,有可能宝贝价值为0
    return 0;
}

/*
//ac 4ms 记忆化搜索,(1,1)点分两种情况 取还是不取 宝贝价值
#include<cstdio>
#include<cstring>
#define N 60
#define mod 1000000007
typedef long long ll;

int n,m,k,mp[N][N],dp[N][N][15][15],dir[2][2]={{0,1},{1,0}};

int dfs(int x,int y,int num,int maxVal){
    if(dp[x][y][num][maxVal+1]!=-1)
        return dp[x][y][num][maxVal+1];
    if(x == n && y == m){
        if(num ==k)
            return dp[x][y][num][maxVal+1]=1;
        else//其余情况 手中宝贝数一定不足k件,并不算如方案数
            return dp[x][y][num][maxVal+1]=0;
    }
    if(num>k)
        return 0;
    int nx,ny;
    ll res=0;
    for(int i=0;i<2;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>n || ny>m)
            continue;
        if(maxVal<mp[nx][ny])//如果当前手中最大价值小于(x,y)价值,考虑拿起当前(x,y)的宝贝
            res=(res+dfs(nx,ny,num+1,mp[nx][ny]))%mod;
        //考虑不拿起(x,y)的宝贝
        res=(res+dfs(nx,ny,num,maxVal))%mod;
    }
    return dp[x][y][num][maxVal+1]=res;
}

int main(){
    int ans=0;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            scanf("%d",&mp[i][j]);
    }
    memset(dp,-1,sizeof(dp));//需要初始化为-1,因为方案数为0 也是一种结果
    ans=(ans+dfs(1,1,0,-1))%mod;
    ans=(ans+dfs(1,1,1,mp[1][1]))%mod;
    printf("%d",ans);
    return 0;
}
*/
