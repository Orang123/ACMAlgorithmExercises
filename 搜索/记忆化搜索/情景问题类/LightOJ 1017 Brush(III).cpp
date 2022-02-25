/*
题意:摘自网上
n个点,给出刷子的宽w和最多横扫次数k,问被扫除最多的点是多少个.
1<=n<=100,1<=w<=10000,1<=k<=100.
说明:水平方向扫除是可以任意扫的,就是y值相同的点 一定可以一次性扫除.
链接:http://www.lightoj.com/volume_showproblem.php?problem=1017
思路:实际只和点的y值有关,可以按照y坐标将点排序,这样就可利用数组下标计算
不同y值间所有点的最大个数.然后需要枚举在刷子宽为w时到底扫除哪一范围的y值
的点.显然有两种可能,该w范围内y值扫还是不扫,显然这会在搜索时产生重叠子问题.
因此记忆化搜索,dp[i][j]代表刷子下边界为i剩余j次横扫次数时能扫除的点的最大个数.
决策为扫和跳过。

补充:LightOJ 1016 Brush(II)就是此题if(y[t]-y[i]<=w)的贪心求解部分
*/
//ac 5ms 记忆化搜索
//dp[i][j]代表刷子下边界为i剩余j次横扫次数时能扫除的点的最大个数.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF -0x3f3f3f3f
using namespace std;

int n,w,k,y[N],dp[N][N];

int dfs(int i,int j){
    int &ans=dp[i][j];
    if(ans)
        return ans;
    if(i == n+1 || j<=0)//结束条件是n个点都遍历完毕或 横扫次数刚好用完
        return ans=0;
    int t,cnt,res1,res2;
    for(t=i;t<=n;t++){
        if(y[t]-y[i]<=w)
            cnt=t-i+1;
        else
            break;
    }
    //扫除当前w范围的点 扫除次数j-1
    res1=cnt+dfs(t,j-1);//t是第一个不满足y[t]-t[i]<=w的点,并未算进记录的cnt里
    //不扫除当前w范围内的点 重新从i+1开始判断 扫除次数还是j
    res2=dfs(i+1,j);
    ans=max(res1,res2);//求取决策的最大值
    return ans;
}

int main(){
    int T,x;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        memset(dp,0,sizeof(dp));
        scanf("%d%d%d",&n,&w,&k);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&x,&y[i]);
        sort(y+1,y+1+n);
        printf("Case %d: %d\n",cas,dfs(1,k));
    }
    return 0;
}
