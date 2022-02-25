/*
题意:n种点心,每种点心有一定的能量t[i],体积u[i]和数量v[i],现在要用m种卡车搬运
这些点心,每种卡车有一定的容量x[i],花费y[i]和数量z[i],在运算过程中你可以把一个
甜点分成几个部分,然后放在不同的卡车上,然后在游戏场地组装这些部件.现在问将至少
运送总能量为p的点心的最小花费.
n,m<=200,t[i],u[i],v[i],x[i],y[i],z[i]<=100
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5445
思路:2次多重背包,第一次对点心,将能量作为背包容积,求出总能量不小于p的最小体积minv,
第二次对卡车,花费作为背包容积,求出在花费给定时的最大体积,遍历从dp[1..50000]判断
dp[i]不小于minv的最小花费i,第一遍背包上限p+100,第二遍背包上限50000.
因为物品最大个数200*100=2*10^4,背包容积大于10^4,所以需要二进制优化.

几点说明:
1.为什么第一次背包容积是p+100
因为点心最大体积是100,取极端情况下点心只能装满p-1容量的背包,那么再装入一个点心
能量就能大于等于p,而再装一个的最大能量是100.

2.为什么这里不可以将体积作为背包容量计算给定体积下的最大能量结果从dp[1..v]遍历
第一个dp[i]>=p的体积i作为答案.

因为这样体积作为背包容积并不清楚最大上界是什么,要考虑极端情况下,所有将所有点心都
装上才能获得能量p,此时体积最大可达100*100*200=2*10^6.而在二进制优化的复杂度下 实际
时间界O(∑log(num[i])*v)=200*6*2*10^6=2400*10^6=2.4*10^9 2s时限肯定会TLE.

3.同样第二次对卡车为什么不把最小体积作为背包容积,计算最小花费,遍历minv~minv+100之间
的最小的花费.
因为第一次求得的最小体积可能非常大,最坏情况可达2*10^6,这个时间界肯定会TLE,因为题目给出
最大花费不会超过50000,所以就以最大花费50000作为背包容量,计算给定花费时的最大体积,这样
总复杂度为O(∑log(num[i])*v)=200*6*5*10^4=6000*10^4=6*10^7 2s时限可接受.
*/

//ac 764ms 两次多重背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define M 50110//最大背包容量为p+100=50100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,p,t[N],u[N],v[N],x[N],y[N],z[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&m,&p);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&t[i],&u[i],&v[i]);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&x[i],&y[i],&z[i]);
        int tw,tv;
        memset(dp,0x3f,sizeof(dp));
        dp[0]=0;
        //对点心做多重背包,将能量作为背包容积,求出总能量不小于p的最小体积minv
        for(int i=1;i<=n;i++){
            for(int k=1;v[i]>0;k<<=1){
                v[i]-=k;
                if(v[i]<0) k+=v[i];
                tw=t[i]*k;
                tv=u[i]*k;
                for(int j=p+100;j>=tw;j--)
                    dp[j]=min(dp[j],dp[j-tw]+tv);
            }
        }
        int ans1=INF;
        for(int i=p;i<=p+100;i++){//大于p时 的体积情况 都不同,要遍历求取最小体积
            if(dp[i]!=INF)
                ans1=min(ans1,dp[i]);
        }
        if(ans1 == INF){
            printf("TAT\n");
            continue;
        }
        memset(dp,0,sizeof(dp));
        dp[0]=0;
        //第二次对卡车,花费作为背包容积,求出在花费给定时的最大体积,遍历从dp[1..50000]判断
        //dp[i]不小于minv的最小花费i
        for(int i=1;i<=m;i++){
            for(int k=1;z[i]>0;k<<=1){
                z[i]-=k;
                if(z[i]<0) k+=z[i];
                tw=y[i]*k;
                tv=x[i]*k;
                for(int j=M-1;j>=tw;j--)
                    dp[j]=max(dp[j],dp[j-tw]+tv);
            }
        }
        int ans2=0;
        for(int i=1;i<M;i++){//找到第一个体积dp[i]不小于ans1的 i就是最小花费
            if(dp[i]>=ans1){
                ans2=i;
                break;
            }
        }
        if(!ans2)
            printf("TAT\n");
        else
            printf("%d\n",ans2);
    }
    return 0;
}
