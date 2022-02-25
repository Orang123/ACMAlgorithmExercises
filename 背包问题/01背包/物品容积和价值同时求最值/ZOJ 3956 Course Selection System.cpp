#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510//500*100=50000
#define M 50100//500*100=50000
typedef long long ll;
using namespace std;
//ac 90ms 01背包 背包容量尽可能多地装

/*
题意:n门课,第i门课给出两个值Hi、Ci(代表快乐度和学分),
对于每门课可以选也可以不选,最后要求算一个结果,其计算公式如图,
其中m是所有选的课,求最大的结果.
Hi之和的平方-Hi之和*Ci之和-Ci之和的平方
链接:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827370070
思路:参考博客:https://blog.csdn.net/u011815404/article/details/89761481
看到C[i]的数据范围,c[i]<=500,而h[i]<=10000,因此在这个式子中很明显h[i]之和
对整体取值占绝对因素,发现当∑Ci一定的时候Hi越大越好,这样的话我们可以直接把题目
转化成一个01背包问题去求解.当∑C[i]一定时,如何获得最大的∑Hi.即将所有课程的Ci之和
作为背包容积,课程快乐度作为物品价值.这个∑C[i]一定时应尽可能多地选择课程的h[i]
之和,存在未装满的情形,因此背包容量尽可能多地装满.主要原因也是Hi之和太大也没法作为
背包容量.

参考博客:https://blog.csdn.net/u011815404/article/details/89761481
化简后有:res=-C^2+H(H-C)可视为开口向下的抛物线,故只要令 H(H-C)尽量大即可
对H(H-C)化简,有:H(H-C)=H^2-HC要使H^2-HC那么就要让H^2尽量大,HC尽量小,即令H
尽量大,C尽量小.

//其实应该是恰好装满背包,但是这里结果也不会错,因为尽可能多地装满,i会偏大,这个公式结果本身也只会更小,不会影响答案的正确性.
*/

ll n,c[N],h[N],dp[M],sum;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&h[i],&c[i]);
            sum+=c[i];
        }
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=c[i];j--)
                dp[j]=max(dp[j],dp[j-c[i]]+h[i]);
        }
        ll ans=0;//dp[i]*dp[i]-dp[i]*i-i*i比较大
        //求解在各个给定选择课程学分之和(背包容量)下,最多能获得的快乐度h[i]之和即dp[i]
        for(int i=0;i<=sum;i++)//虽然dp[i]可能并未装满,但dp[i]就是实际各个课程的快乐度之和
            //其实应该是恰好装满背包,但是这里结果也不会错,因为尽可能多地装满,i会偏大,这个结果本身也只会更小,不会影响答案的正确性.
            ans=max(ans,dp[i]*dp[i]-dp[i]*i-i*i);//max 两个参数的类型必须一致
        printf("%lld\n",ans);
    }
    return 0;
}

/*
//ac 59ms 01背包 背包恰好装满
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510//500*100=50000
#define M 50100//500*100=50000
typedef long long ll;
using namespace std;

ll n,c[N],h[N],dp[M],sum;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&h[i],&c[i]);
            sum+=c[i];
        }
        dp[0]=0;//只有dp[0]=0,其余都是-INF
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=c[i];j--)
                dp[j]=max(dp[j],dp[j-c[i]]+h[i]);
        }
        ll ans=0;
        //求解在各个给定选择课程学分之和(背包容量)下,最多能获得的快乐度h[i]之和即dp[i]
        for(int i=0;i<=sum;i++){
            if(dp[i]>0)
                ans=max(ans,dp[i]*dp[i]-dp[i]*i-i*i);//max 两个参数的类型必须一致
        }
        printf("%lld\n",ans);
    }
    return 0;
}
*/
