#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5100
using namespace std;
//ac 46ms 01背包 尽可能多地装满+贪心排序
//dp二维循环下界 j>=max(goods[i].p,goods[i].q)
/*
题意:给出n个物品,和容量为m的背包,第i个物品的体积为p[i],价值为v[i],
但必须当前背包的容量大于q[i]才可以放这个物品呢,求最大的价值.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3466
思路:是在01背包经典模型基础上,加上了当前背包剩余容量必须大于q[i]才能,
并且背包剩余容量也不小于p[i],才能将该物品装入背包.那么实际每个背包装载
的顺序不同背包剩余容积就不同,那么就会影响后续物品的装入与否.因此要尽可能
先放入p-q较大的,不然到了后面背包剩余容积越小,就可放不进去了,因此可以按照
p-q降序排序,或者q-p升序排序.

参考博客:https://blog.csdn.net/the_love_story/article/details/52179575
解释1:以前的01背包不用排序,dp[j] = max(dp[j],dp[j-w[i]]+v[i])表达的是这
第i个物品要不要买,但同时也在判断第i个物品要不要先买,如果先买剩下的空间随便放,看是否得到的价值会更大。
A物品p1,q1,v1;
B物品p2,q2,v2
若先买A,至少需要p1+q2 (p1 == q1情况下）若现买B,至少需要p2+q1;
若A<B,应先买A,即 q1-p1 > q2-p2;即差值大的先买,所以先买的应排到后面

参考博客:https://blog.csdn.net/qq_21057881/article/details/49976813
解释2:动态规划无后效性,某阶段的状态一旦确定,则此后过程的演变不再受
此前各种状态及决策的影响,简单的说,就是“未来与过去无关”,当前的状态是
此前历史的一个完整总结,此前的历史只能通过当前的状态去影响过程未来的演变.
那么看01背包最原始的状态转移方程dp[i][j]=max(dp[i-1][j],dp[i-1][j-c[i]]+w[i]);
那么什么时候能转移呢,j-c[i]是花费,那么剩下的钱就是m-(j-c[i]),当m-(j-c[i])>q[i]时
能转移,整理一下有j<m+p[i]-q[i],那么如果动态规划满足无后效性的话,则每一次更新转移的
范围应该都要比前一次要小,这样才能更新时不丢失状态,所以有了一开始不知所云的按p1-q1>p2-q2排序然后背包搞起
*/

int n,m,dp[M];

struct Goods{
    int p,q,v;
    bool operator < (const Goods &x)const{
        return p-q>x.p-x.q;//等价于q-p<x.q-x.p
    }
}goods[N];

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&goods[i].p,&goods[i].q,&goods[i].v);
        sort(goods+1,goods+1+n);
        for(int i=1;i<=n;i++){
            //j>=max(goods[i].p,goods[i].q)作为下界 可保证dp[j-goods[i].p]数组下标不为负
            for(int j=m;j>=max(goods[i].p,goods[i].q);j--)
                dp[j]=max(dp[j],dp[j-goods[i].p]+goods[i].v);
        }
        printf("%d\n",dp[m]);
    }
    return 0;
}

/*
//ac 46ms 01背包 尽可能多地装满+排序
//dp二维循环下界 j>=goods[i].q
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5100
using namespace std;

int n,m,dp[M];

struct Goods{
    int p,q,v;
    bool operator < (const Goods &x)const{
        return q-p<x.q-x.p;
    }
}goods[N];

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&goods[i].p,&goods[i].q,&goods[i].v);
        sort(goods+1,goods+1+n);
        for(int i=1;i<=n;i++){
            //j>=goods[i].q 有可能q<p,,当j=q时,dp[j-p] 数组下标j-p为负数,
            //但是并不影响结果,因为较大的p下限本身已经遍历过了
            for(int j=m;j>=goods[i].q;j--)
                dp[j]=max(dp[j],dp[j-goods[i].p]+goods[i].v);
        }
        printf("%d\n",dp[m]);
    }
    return 0;
}
*/

/*
贪心排序+暴力枚举搜索 TLE
*/
