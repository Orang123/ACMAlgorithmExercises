/*
题意:摘自网上
给出要买可乐的数量c，以及1元，5元和10元硬币的数量n1、n5、n10，
每瓶可乐8元，每次照钱会按照最少硬币的方式找回，问如何投币可使
得投入的硬币数最少，输出投入最少的硬币数量。
1<=c<=150,n1<=500,n5<=100,n10<=50.
链接:https://www.luogu.com.cn/problem/UVA10626
思路:记忆化搜索.
可以投入硬币方案有5种
1.投8个1元的.
2.投3个1元的+1个5元的.
3.投1个10元的,找回2个1元的.
4.投2个5元的,找回2个1元的.
5.投3个1元的和1个10元的,找回1个5元的.
dp[n1][n5][n10]表示在有n1个1元,n5个5元,n10个10元的硬币时,将剩余的可乐购买
完,最少需要投入的硬币个数.
注意因为1元和5元硬币都会再找回,所以n1,n5应该开的大一点,
实测n1至少要700,n5 110,不然会数组越界异常.
这个题有个疑点 就是n1、n5、n10回到之前重复的状态时,所剩余的可乐数是怎么保持
一致的,可乐数应该是能保持一致的,但是不知是如何证明的.
*/
//ac 160ms 记忆化搜索
//dp[n1][n5][n10]表示在有n1个1元,n5个5元,n10个10元的硬币时,将剩余的可乐购买
//完,最少需要投入的硬币个数.
//时间复杂度(710*110*60)=4686000
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 710
#define M 110
#define L 60
#define INF 0x3f3f3f3f
using namespace std;

int c,m1,m5,m10,dp[N][M][L];

int dfs(int k,int n1,int n5,int n10){
    int &res=dp[n1][n5][n10];
    if(res!=INF)
        return res;
    if(!k)
        return res=0;
    if(n1>=8)
        res=min(res,dfs(k-1,n1-8,n5,n10)+8);
    if(n1>=3 && n5>=1)
        res=min(res,dfs(k-1,n1-3,n5-1,n10)+4);
    if(n10>=1)
        res=min(res,dfs(k-1,n1+2,n5,n10-1)+1);
    if(n5>=2)
        res=min(res,dfs(k-1,n1+2,n5-2,n10)+2);
    if(n1>=3 && n10>=1)
        res=min(res,dfs(k-1,n1-3,n5+1,n10-1)+4);
    return res;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d%d%d",&c,&m1,&m5,&m10);
        printf("%d\n",dfs(c,m1,m5,m10));
    }
    return 0;
}
