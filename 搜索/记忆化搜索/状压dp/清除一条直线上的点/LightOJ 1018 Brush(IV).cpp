/*
题意:摘自网上
二分平面上有N个点，现在有一把可沿着任何方向走的刷子可以刷去这些点，
问最少需要刷出多少条直线可以把点刷完？
n<=16.
链接:http://www.lightoj.com/volume_showproblem.php?problem=1018
思路:可以枚举出任意两点确定的直线连接起来,然后再连接剩余不在当前
直线上的点尝试连接,因为n<=16,可以看出未连接在直线的点状态的标识需要用二进制.
在用直线枚举连接点的过程中,剩下未连接的点会出现重复的状态.因此记忆化搜索.
s[i][j]表示i点与j点连接的直线不在这条直线上的点的二进制位状态.
dp[sta]=k表示sta中还未用直线连接的点 最少需要用的直线条数才能完全覆盖所有的点.
需要注意的是 因为所有点都要被连接完,实际影响最优结果的主要问题在于每一个点该和
其余哪些组合的点连接直线,和枚举连接点的顺序无关,因此记忆化搜索时只需找到第一个
还未连接的点即可.但是如果并没有要求将所有点都连接起来,就需要考虑枚举直线连接第一个
点连接的顺序,这会影响较优解.如UVA11008 Antimatter Ray Clearcutting.
*/
//ac 135ms 记忆化搜索+状压
//s[i][j]表示i点与j点连接的直线不在这条直线上的点的二进制位状态.
//dp[sta]=k表示sta中还未用直线连接的点 最少需要用的直线条数才能完全覆盖所有的点.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
#define INF 0x3f3f3f3f
using namespace std;

int n,x[N],y[N],dp[1<<16],s[N][N];

int judge(int x1,int y1,int x2,int y2){
    return x1*y2 == x2*y1;
}

int bitCount(int val){
    int cnt=0;
    while(val){
        if(val & 1)
            cnt++;
        val>>=1;
    }
    return cnt;
}

int dfs(int sta){
    if(dp[sta]!=INF)
        return dp[sta];
    int k=bitCount(sta);//还未被直线连接的点的个数
    if(!k)
        return dp[sta]=0;
    if(k<=2)//有可能刚好只剩下一个点,需要特判 用1条直线 连接起来,2个点也需要1条直线连接.
        return dp[sta]=1;
    for(int i=0;i<n;i++){//只需找到第一个还未连接的点即可
        if(sta & 1<<i){
            for(int j=i+1;j<n;j++){
                if(sta & 1<<j)
                    dp[sta]=min(dp[sta],dfs(sta & s[i][j])+1);
            }
            //这里不结束会超时,因为所有点都是要被直线连接的,实际影响结果的 主要问题
            //在于每一个点该和其余哪些组合的点连接直线,和枚举连接点的顺序无关
            break;
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
        printf("Case %d: %d\n",cas,dfs((1<<n)-1));//开始 所有点都未连接
    }
    return 0;
}
