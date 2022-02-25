/*
题意:摘自网上
在平面直角坐标系中，给定n个点的坐标，要求删去其中m个点，每次可以
将一条直线上所有点删去，问最少的操作次数。
n<=16.
注意:并没有要去恰好删去m个点,如果原先的点都在一条直线上,
一条直线就可以将所有点删掉,虽然删掉的点大于m个,但仍是合理的.
链接:https://www.luogu.com.cn/problem/UVA11008
思路:可以枚举出任意两点确定的直线连接起来,然后再连接剩余不在当前
直线上的点尝试连接,因为n<=16,可以看出未连接在直线的点状态的标识需要用二进制.
在用直线枚举连接点的过程中,剩下未连接的点会出现重复的状态.因此记忆化搜索.
s[i][j]表示i点与j点连接的直线不在这条直线上的点的二进制位状态.
dp[sta]=k表示sta中还未用直线连接的点 最少需要用的直线条数才能完全覆盖所有的点.
和LightOJ 1018 Brush(IV)不同的是,只需要删掉m个点就可以,因此结束条件是未删掉的
点的个数小于等于n-m,返回0,如果剩下的点刚好等于1个,返回1.
需要注意的是因为 并没有要求删掉所有的点,所以开始选取删去点的顺序也会影响实际
需要直线的最小操作次数.所以记忆化搜索时,对于第一个点的选取 需要在回溯时枚举所有
可能未删掉的点.
*/
//ac 170ms 记忆化搜索+状压
//s[i][j]表示i点与j点连接的直线不在这条直线上的点的二进制位状态.
//dp[sta]=k表示sta中还未用直线连接的点 最少需要用的直线条数才能完全覆盖所有的点.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
#define INF 0x3f3f3f3f
using namespace std;

int n,m,x[N],y[N],dp[1<<16],s[N][N];

int judge(int x1,int y1,int x2,int y2){
    return x1*y2 == x2*y1;
}

int dfs(int sta){
    if(dp[sta]!=INF)
        return dp[sta];
    int k=__builtin_popcount(sta);//__builtin_popcount计算sta中二进制位1的个数
    if(k<=n-m)//可以删掉超过m个点
        return dp[sta]=0;
    else if(k == 1)
        return dp[sta]=1;
    //并没有要求删掉所有的点,所以开始选取删去点的顺序也会影响实际
    //需要直线的最小操作次数,因此要考虑直线第一个端点的所有可能情况求取最小值
    for(int i=0;i<n;i++){
        if(sta & 1<<i){
            for(int j=i+1;j<n;j++){
                if(sta & 1<<j)
                    dp[sta]=min(dp[sta],dfs(sta & s[i][j])+1);
            }
        }
    }
    return dp[sta];
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d",&n);
        scanf("%d",&m);
        for(int i=0;i<n;i++)
            scanf("%d%d",&x[i],&y[i]);
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                s[i][j]=0;
                for(int k=0;k<n;k++){
                    if(!judge(x[i]-x[k],y[i]-y[k],x[j]-x[k],y[j]-y[k]))//判断(i,k) (j,k)的斜率是否相同,不相同即不在一条直线上
                        s[i][j]|=1<<k;
                }
            }
        }
        if(cas!=1)
            printf("\n");
        printf("Case #%d:\n",cas);
        printf("%d\n",dfs((1<<n)-1));
    }
    return 0;
}
