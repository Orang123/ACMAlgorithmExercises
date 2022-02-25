/*
题意:摘自网上
从x-y这个区间找满足条件的整数的个数：这个数恰好等于k个不相等b的整数幂之和
释义:求（x--y）区间转化为 b 进制 1 的个数为 k 的数的出现次数。
x,y<=2^31-1.
链接:https://vjudge.net/problem/URAL-1057
思路:数位dp.
dp[k][num]表示数位从len到k-1位数位(从右至左计算数位下标)剩下num个数才能构成以B为底的幂次K个数
再从k位到末尾这部分能构成的所有不超过原始n的数位串满足恰好构成k个数的个数.
为了dp只初始化一次,使用多样例,num表示的一定是剩余的个数,因为每个样例k值是不同的.
*/
//ac 1ms 记忆化搜索
//dp[k][num]表示数位从len到k-1位数位(从右至左计算数位下标)剩下num个数才能构成以B为底的幂次K个数
//再从k位到末尾这部分能构成的所有不超过原始n的数位串满足恰好构成k个数的个数.
#include<cstdio>
#include<cstring>
#define N 33

int len,a[N];
int X,Y,B,K,dp[N][N];

int dfs(int k,int num,int limit){
    if(!k)
        return num == 0;
    if(num<0)
        return 0;
    if(!limit && dp[k][num]!=-1)
        return dp[k][num];
    int last=limit?a[k]:B-1;
    int ans=0;
    //这里只判断B进制数码中1的个数,实际只可以取01 所以对于不同样例 虽然B进制不同,但i最大也只取到1,因此dp值多组样例可以公用
    for(int i=0;i<=last && i<=1;i++)
        ans+=dfs(k-1,num-i,limit && i == last);
    if(!limit)
        dp[k][num]=ans;
    return ans;
}

int solve(int val){
    len=0;
    while(val){
        a[++len]=val%B;
        val/=B;
    }
    return dfs(len,K,1);
}

int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d%d",&X,&Y);
    scanf("%d%d",&K,&B);
    printf("%d",solve(Y)-solve(X-1));
    return 0;
}
