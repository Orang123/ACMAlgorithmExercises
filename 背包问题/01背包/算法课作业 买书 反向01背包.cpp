#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1100
using namespace std;

/*
题意:Sheldon到Comic book store买书,发现书店推出了买满W美元赠送限量版闪电侠T恤的活动.
书店里有n不同的图书,给定每种图书的价格用数组p[i]表示,且p[i]整数.Sheldon从来不买重复的书.
请为他设计算法,求出他最少用多少钱可以拿到限量版闪电侠T恤.
n<=100,p[i]<=10.
链接:算法课留的作业
思路:实际就是问购买n本书使得花费不小于W美元的最小花费,所有书总花费为sum.
那么原问题中对于剩下没有买的书就是尽可能大的花费了,所以这个问题可以看成用
sum-w的钱尽可能多地买书,最多能花费多少钱,那么此时剩下的没买书的花费一定可以
保证不小于W,那么剩下书总花费就是sum-dp[sum-W].
*/
int n,w,p[N],dp[M],sum;

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&w);
    for(int i=1;i<=n;i++){
        scanf("%d",&p[i]);
        sum+=p[i];
    }
    if(sum<w){//所有书全买花费都小于w,不能拿到限量版闪电侠T恤
        printf("-1");
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=sum-w;j>=p[i];j--)
            dp[j]=max(dp[j],dp[j-p[i]]+p[i]);
    }
    printf("%d",sum-dp[sum-w]);
    return 0;
}

/*
//另一种做法 在01背包转移过程中,对于买书大于等于W花费时记录最小的花费
//dp[j]=1表示买前i本书花费j元是存在情况
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,w,p[N],dp[M],ans;

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&w);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i]);
    ans=INF;
    dp[0]=1;//恰好装满背包
    for(int i=1;i<=n;i++){
        for(int j=w;j>=0;j--){//这里下界是0,因为是从dp[j]向dp[j+p[i]]转移,花费再不断增加,初始状态是dp[0]
            if(dp[j]){//若上一个状态 合法 则在上一个状态基础上 买第i本书
                if(j+p[i]>=w)//如果花费超过w,则记录超过W时的最小花费
                    ans=min(ans,j+p[i]);
                else//花费小于W,标记这个状态,为了得到下一状态
                    dp[j+p[i]]=1;
            }
        }
    }
    if(ans != INF)
        printf("%d",ans);
    else//所有书的花费加起来也比W小 输出-1 代表不能拿到限量版闪电侠T恤
        printf("-1");
    return 0;
}
*/

/*
也可以以所有书的价格总和为背包容量,恰好装满背包,最后判断在容量大于等于w时,输出最小的合法状态即是答案
*/

/*
测试样例
input
5 8
2 4 7 9 10

output
9

显然最优方案可以有2 种：最少可以用9元购买物品获得赠送的限量版T恤
第一种：购买第1个物品和第3个物品即2 +7=9>8
第二种：直接购买第4个物品9> 8
*/
