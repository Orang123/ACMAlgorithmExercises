/*
题意:摘自网上
给定区间[x,y]，求区间内平衡数的个数。所谓平衡数即有一位做平衡点，
左右两边数字的力矩想等。
x,y<=10^18.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=3709
思路:数位dp.
dp[k][pos][sum]表示支点在pos位置数位从len到k-1位力距和为sum(从右至左计算数位下标)
再从k位到末尾这部分能构成的所有不超过原始n的数位串满足使得力距和等于0的数目
*/
//ac 31ms 记忆化搜索+剪枝
//dp[k][pos][sum]表示支点在pos位置数位从len到k-1位力距和为sum(从右至左计算数位下标)
//再从k位到末尾这部分能构成的所有不超过原始n的数位串满足使得力距和等于0的数目
//空间复杂度O(20*3078)=61560
//时间复杂度O(10*20*3078)=615600
//每次solve都初始化dp数组 265ms
#include<cstdio>
#include<cstring>
#define N 20
#define M 3078//9*18*19
typedef long long ll;

int len,a[N];
ll x,y,dp[N][N][M];

ll dfs(int k,int pos,int sum,int limit){
    if(!k)
        return sum == 0;
    if(sum<0)//如果力距和已经小于0,再加上去只会更小 结束
        return 0;
    if(!limit && dp[k][pos][sum]!=-1)
        return dp[k][pos][sum];
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++)
        ans+=dfs(k-1,pos,sum+i*(k-pos),limit && i == last);
    if(!limit)
        dp[k][pos][sum]=ans;
    return ans;
}

ll solve(ll val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    ll ans=0;
    for(int i=len;i>=1;i--)//枚举每个位置i作为支点计算平衡数目
        ans+=dfs(len,i,0,1);
    return ans-len+1;//因为len个支点 每次都计算了一次数位全部为0的平衡,这个多加了len-1次全0的情况,因此要减掉
}

int main(){
    int T;
    memset(dp,-1,sizeof(dp));//只需初始化一次dp,多组样例重复使用计算好的dp值
    scanf("%d",&T);
    while(T--){
        scanf("%lld%lld",&x,&y);
        printf("%lld\n",solve(y)-solve(x-1));
    }
    return 0;
}
