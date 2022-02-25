/*
题意:你持有n种货币,每种货币的面值为val[i],每种货币的数量为num[i],
现在要购买价钱为T的商品,因为你持有的货币不一定能恰好凑够T元,可能
需要给售货员大于T的钱M,M不会大于20000,然后售货员会找给你M-T元钱,
其中售货员也有这n种货币,并且每种货币数量无限制,现在问购买价格为
T的商品时,你给售货员的硬币数目+售货员找他的硬币数目最少是多少.
其中T<=10000,n<=100,num[i]<=10^4,val[i]<=120,v<=20000
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3591
思路:很明显是个恰好装满背包需最少放置几个货币的问题.对于售货员
来说是完全背包,对于客户来说是多重背包,为了统计最少货币数目,需要
考虑10000~20000之间的所有情况下的货币数目,因为刚好凑够10000元买
商品所需的硬币数不一定比14564等其它大于T的钱所需硬币数少.即:
ans=max(ans,dp1[i]+dp2[i-T]),其中dp1是多重背包,dp2是完全背包,
只是主要需要二进制优化多重背包,即复杂度=100*log(10^4)*20000=2.6*10^7,
对于二进制拆分的物品组合实际物品的个数是二进制位k,转移方程是加上k个
第i种物品.

虽然这个问题中物品的属性只有价值,体积等同价值,但因为要求解最小数目,所以
也不能应用可行解O(nv)的解法.
*/
//ac 78ms 混合背包 多重背包+完全背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 20001
#define INF 0x3f3f3f3f
using namespace std;

int cas,n,T,val[N],num[N],dp1[M],dp2[M];

int main(){
    while(scanf("%d%d",&n,&T) && n+T){
        cas++;
        memset(dp1,0x3f,sizeof(dp1));
        memset(dp2,0x3f,sizeof(dp2));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&num[i]);
        dp1[0]=0;
        int tw,tv;
        for(int i=1;i<=n;i++){
            for(int k=1;num[i]>0;k<<=1){
                num[i]-=k;
                if(num[i]<0) k+=num[i];
                tw=val[i]*k;
                tv=k;
                for(int j=M-1;j>=tw;j--)
                    //第i种货币 要加上k个,而不是1
                    dp1[j]=min(dp1[j],dp1[j-tw]+tv);
            }
        }
        dp2[0]=0;
        for(int i=1;i<=n;i++){
            for(int j=val[i];j<M-1-T;j++)
                dp2[j]=min(dp2[j],dp2[j-val[i]]+1);
        }
        int ans=INF;
        for(int i=T;i<M;i++){
            if(dp1[i]<INF && dp2[i-T]<INF)
                //售货员找的钱是i-T
                ans=min(ans,dp1[i]+dp2[i-T]);
        }
        if(ans!=INF)
            printf("Case %d: %d\n",cas,ans);
        else
            printf("Case %d: -1\n",cas);
    }
    return 0;
}
