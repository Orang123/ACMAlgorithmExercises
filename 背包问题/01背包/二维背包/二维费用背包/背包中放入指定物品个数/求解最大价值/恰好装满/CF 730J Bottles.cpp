#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;
//2016-2017 ACM-ICPC, NEERC, Southern Subregional Contest (Online Mirror, ACM-ICPC Rules)
//ac 156ms 二维01背包 装入指定物品个数的最大价值
//这题的做法还是有点不太理解
/*
题意:有n瓶水第i瓶水的水量为a[i],容量为b[i].将1单位水
从一个瓶子转移到另一个瓶子所消耗时间为1秒,且可以进行
无限次转移.求储存所有水所需最小瓶子数num以及该情况下所用最小时间t.
链接:http://codeforces.com/contest/730/problem/J
思路:首先装所有水需要的最小瓶子数可以通过贪心按照杯子容量从大到小排序,
从第一个最大的开始装水,直到将水装完,就能计算出num,t实际上就是移动了的
部分的总体积和,t最小就意味着没有移动的部分体积最大.
总的倒入时间=水的总体积-选定最后要倒入的瓶子的没有移动的水的总体积.水的总
体积是一个定值,所以我们要最大化最后要倒入的瓶子的没有移动的水的总体积.
"最后要倒入的瓶子的没有移动的水的总体积"可以通过二维指定物品个数的01背包求解,
而且必须是恰好装满背包,因为杯子的容积和原本杯子中装的水 是本身就没有移动的,固定的,
一定是等价 恒等对应的,不可能多余出来.
*/
//dp[i][j]表示选了i个瓶子,一共的容积为j的时候,这i个瓶子里本身没有移动水的最大值.
int n,num,dp[N][M],sum1,sum2;
struct Bottle{
    int a,b;
    bool operator < (const Bottle &x)const{
        return b>x.b;
    }
}bot[N];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&bot[i].a);
        sum1+=bot[i].a;
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&bot[i].b);
        sum2+=bot[i].b;
    }
    sort(bot+1,bot+1+n);
    int sum=0;
    while(sum<sum1) sum+=bot[++num].b;
    memset(dp,-0x3f,sizeof(dp));
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int k=num;k>=1;k--){
            for(int j=sum2;j>=bot[i].b;j--)
                dp[k][j]=max(dp[k][j],dp[k-1][j-bot[i].b]+bot[i].a);
        }
    }
    int ans=0;
    //这里有点不理解,为什么不能逆序从sum2开始 第一个合法状态不就是最大值吗,这样逆序遍历会wa
    for(int i=sum1;<=sum2;i++)
        ans=max(ans,dp[num][i]);
    printf("%d %d",num,sum1-ans);
    return 0;
}

/*
//ac 156ms 背包容量放第二层降序
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;

int n,num,dp[N][M],sum1,sum2;
struct Bottle{
    int a,b;
    bool operator < (const Bottle &x)const{
        return b>x.b;
    }
}bot[N];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&bot[i].a);
        sum1+=bot[i].a;
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&bot[i].b);
        sum2+=bot[i].b;
    }
    sort(bot+1,bot+1+n);
    int sum=0;
    while(sum<sum1) sum+=bot[++num].b;
    memset(dp,-0x3f,sizeof(dp));
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=sum2;j>=bot[i].b;j--){
            for(int k=1;k<=num;k++)
                dp[k][j]=max(dp[k][j],dp[k-1][j-bot[i].b]+bot[i].a);
        }
    }
    int ans=0;
    for(int i=sum1;i<=sum2;i++)
        ans=max(ans,dp[num][i]);
    printf("%d %d",num,sum1-ans);
    return 0;
}
*/

/*
//参考博客:https://blog.csdn.net/stay_accept/article/details/53464425
//ac 124ms 杯子的容积作为价值,杯子中本身装的水作为重量
//dp[i][j]表示选了i个瓶子,已经装了j体积,i个瓶子的最大容量.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
int dp[105][10005];
struct node{
    int le,val;
    friend bool operator<(node a,node b){
        if(a.val==b.val)
        return a.le>b.le;
        return a.val>b.val;
    }
}s[105];
int main(){
    int n,i,j,k,ans1,ans2,tmp,sum;
    while(scanf("%d",&n)!=EOF){
        sum=0;
        for(i=1;i<=n;i++){
            scanf("%d",&s[i].le);
            sum+=s[i].le;
        }
        for(i=1;i<=n;i++)
        scanf("%d",&s[i].val);
        sort(s+1,s+n+1);                        //因为要求瓶子数目最小。所以
        tmp=0;                                  //直接排序求前缀，求出最小的
        for(i=1;i<=n;i++){                      //瓶子数目，但是不一定就用这
            tmp+=s[i].val;                      //几个瓶子，因此用dp判断
            if(tmp>=sum){
                ans1=i;
                break;
            }
        }
        memset(dp,-1,sizeof(dp));
        dp[0][0]=0;                             //dp[i][j]表示选了i个瓶子，已经
        for(i=1;i<=n;i++){                      //装了j体积，i个瓶子的最大容量
            for(j=sum;j>=0;j--){
                for(k=1;k<=i;k++){
                    if(j>=s[i].le&&dp[k-1][j-s[i].le]!=-1)
                    dp[k][j]=max(dp[k][j],dp[k-1][j-s[i].le]+s[i].val);
                }
            }
        }
        for(i=sum;i>=0;i--){                    //找出ans1个瓶子能装所有水时间的最小值
            if(dp[ans1][i]>=sum){
                ans2=sum-i;
                break;
            }
        }
        printf("%d %d\n",ans1,ans2);
    }
    return 0;
}
*/
