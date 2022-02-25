/*
题意:n棵树排成一排,每棵树上有c[i]只鸟,在一棵树底下召唤一只鸟的会减少cost[i]魔法,
每召唤一只鸟,法力值上限会增加b,从一棵树走到另一棵树,会恢复x魔法值,初始时你站在第
一棵树下,拥有w法力值,法力值上限也是w,问最多能够召唤的鸟的个数.
n<=10^3,∑c[i]<=10^4,0<=w,b,x<=10^9.
注意:此题必须给定初始站在第一棵树下,移动按照树的编号递增移动这样才能保证答案的正确性.
链接:http://codeforces.com/contest/922/problem/E
思路:因为法力值最大可达10^9,所以并不能作为背包容量,可以将召唤的鸟作为背包容量.
而如果用01背包将所有鸟放在一堆无法描述从一棵树到另一棵树增加的法力值x.
可考虑将每棵树上的鸟作为分组背包的一组或多重背包的每一种类型的鸟.

2种做法.
做法1:分组背包 复杂度(n*∑c[i]*c[i])=10^3*10^4*O(10^4) 分组背包这个复杂度其实
很勉强.
每棵树上的鸟单独作为一组,这样从一棵树到另一棵树就可描述为第i-1组到第i组的转移,
这样就能方便表示增加的法力值x.每组中的物品为这棵树上的鸟分别召唤了1、2、...、c[i]只.
因为这个过程法力值会增加所以不好描述召唤指定数目的鸟最少花费的法力值,因此
dp[i][j]表示前i棵树召唤了j只鸟剩下的最多法力值.
转移方程dp[i][j]=max(dp[i][j],dp[i-1][j-k]-k*cost[i]),k是当前第i组中召唤k只鸟的物品.
第i组物品dp完成时需要对前i组状态加上到达第i+1棵树时恢复增加的法力值x,并且不能超过当前
召唤j只鸟更新后的法力值上限w+j*b.
dp[i][j]=min(dp[i][j]+x,w+j*b)

做法2:多重背包
第i棵树上的鸟作为第i种类型的鸟,第i种鸟的数量为c[i],显然需要对第i种鸟的数量c[i]进行二进制拆分,
复杂度O(nv∑log(c[i])) 10^3*10^4*13=10^8
dp[i][j]表示前i种类型的鸟在召唤了j只时剩下的最多法力值.
转移方程dp[i][j]=max(dp[i][j],dp[i-1][j-k]-k*cost[i]),k是当前第i种鸟中召唤k只鸟构成的二进制组合.
第i种鸟dp完成时需要对前i种状态加上到达第i+1种鸟时恢复增加的法力值x,并且不能超过当前
召唤j只鸟更新后的法力值上限w+j*b.
dp[i][j]=min(dp[i][j]+x,w+j*b)

标准做法应该就是多重背包.
*/
//ac 218ms 分组背包
//复杂度(n*∑c[i]*c[i])=10^3*10^4*O(10^4) 分组背包这个复杂度其实很勉强.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 10010
typedef long long ll;
using namespace std;

//dp[i][j]表示前i棵树召唤了j只鸟剩下的最多法力值.
ll n,w,b,x,c[N],cost[N],dp[M],sum;

int main(){
    scanf("%lld%lld%lld%lld",&n,&w,&b,&x);
    for(int i=1;i<=n;i++)
        scanf("%lld",&c[i]);
    for(int i=1;i<=n;i++)
        scanf("%lld",&cost[i]);
    //要求恰好召唤j只鸟
    memset(dp,-1,sizeof(dp));
    //初始时剩余法力值为w
    dp[0]=w;
    for(int i=1;i<=n;i++){
        //因为是恰好装满背包,所以大于实际前i棵树鸟数的容量无意义
        //必须在第i-1棵树合法状态下才能向第i棵树转移
        sum+=c[i];
        //j的下界 最少第i棵树考虑转换一只鸟,一只鸟也不召唤时再下面增加x法力值会考虑
        for(int j=sum;j>=1;j--){
            //k上限是min(c[i],j)
            for(int k=1;k<=c[i] && k<=j;k++){
                //dp[i-1][j-k]剩下的法力值必须能够召唤第i棵树上k只鸟,当dp[j-k]不合法 为负数时,dp[j-k]-k*cost[i]必然<0
                if(dp[j-k]-k*cost[i]>=0)
                    dp[j]=max(dp[j],dp[j-k]-k*cost[i]);
            }
        }
        //考虑从第i棵树到第i+1棵树 会增加x法力值,但是不会超过召唤j只鸟更新后的法力值上限 w+j*b
        //要考虑j=0,前i棵树一只鸟也不召唤 会增加的法力值w+i*x
        for(int j=sum;j>=0;j--){
            if(dp[j]!=-1)//注意这里必须是合法状态,才行,不然会影响到最后结果的dp[i]判断最多召唤的鸟的合法状态的判断
                dp[j]=min(dp[j]+x,w+j*b);
        }
    }
    int ans;
    for(int i=sum;i>=0;i--){
        if(dp[i]!=-1){
            ans=i;
            break;
        }
    }
    printf("%d",ans);
    return 0;
}

/*
//ac 62ms 多重背包
//复杂度O(nv∑log(c[i])) 10^3*10^4*13=10^8
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 10010
typedef long long ll;
using namespace std;

//dp[i][j]表示前i种类型的鸟在召唤了j只时剩下的最多法力值.
ll n,w,b,x,c[N],cost[N],dp[M],sum;

int main(){
    scanf("%lld%lld%lld%lld",&n,&w,&b,&x);
    for(int i=1;i<=n;i++)
        scanf("%lld",&c[i]);
    for(int i=1;i<=n;i++)
        scanf("%lld",&cost[i]);
    memset(dp,-1,sizeof(dp));
    dp[0]=w;
    for(int i=1;i<=n;i++){
        //枚举第i种类型鸟的组成数量 进行二进制拆分
        for(int k=1;c[i]>0;k<<=1){
            c[i]-=k;
            if(c[i]<0) k+=c[i];
            sum+=k;//因为是恰好装满背包,前i种鸟 能召唤的最大数量是前i-1种鸟的总数+第i种鸟的当前已有的二进制拆分数量
            for(int j=sum;j>=1;j--){
                if(j>=k && dp[j-k]-k*cost[i]>=0)
                    dp[j]=max(dp[j],dp[j-k]-k*cost[i]);
            }
        }
        //第i棵树到第i+1棵树,增加x法力值 不会超过上限当前召唤j只鸟法力值上限w+j*b
        for(int j=sum;j>=0;j--){
        	if(dp[j]!=-1)
            	dp[j]=min(dp[j]+x,w+j*b);
        }
    }
    int ans;
    for(int i=sum;i>=0;i--){
        if(dp[i]!=-1){
            ans=i;
            break;
        }
    }
    printf("%d",ans);
    return 0;
}
*/
