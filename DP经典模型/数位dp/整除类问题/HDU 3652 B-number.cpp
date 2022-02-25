/*
题意:给出一个n，求出n范围内含有13并且能被13整除的个数
n<=10^9.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=3652
思路:经典数位dp.多了一个前k-1位取模的余数作为dp的维度.
dp[k][mod][pre]表示n的数位从len到k-1位对13取模为mod(从右至左计算数位下标)
再从k位到末尾这部分能构成的所有不超过原始n的数字串满足不出现"13"的并且能被13整除的数字串的个数
*/
//ac 0ms 记忆化搜索
//dp[k][mod][pre]表示n的数位从len到k-1位对13取模为mod(从右至左计算数位下标)再从k位到末尾这部分能构成的所有不超过原始n的数字串满足不出现"13"的并且能被13整除的数字串的个数
//pre == 0表示上一位不是1
//pre == 1表示上一位是1
//pre == 2表示前面数位出现过13
//空间复杂度O(10*13*3)=390
//时间复杂度O(10*10*13*3)=3900
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
using namespace std;

int n,len,dp[N][13][3],a[N];

int dfs(int k,int mod,int pre,int limit){
    if(!k)
        return pre == 2 && !mod;
    if(!limit && dp[k][mod][pre]!=-1)
        return dp[k][mod][pre];
    int last=limit?a[k]:9;
    int ans=0;
    for(int i=0;i<=last;i++){
        int val=(mod*10+i)%13;
        if(!pre || (pre == 1 && i!=3))
            ans+=dfs(k-1,val,i == 1,limit && i == last);
        else
            ans+=dfs(k-1,val,2,limit && i == last);
    }
    if(!limit)
        dp[k][mod][pre]=ans;
    return ans;
}

int main(){
    memset(dp,-1,sizeof(dp));//dp数组只用初始化一次,多组样例可以公用之前计算的dp值
    while(scanf("%d",&n)!=EOF){
        len=0;
        while(n){
            a[++len]=n%10;
            n/=10;
        }
        printf("%d\n",dfs(len,0,0,1));
    }
    return 0;
}

/*
//ac 0ms 正向递推 没看
//摘自博客:https://blog.csdn.net/with_passion/article/details/50605223
#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int (i) = 0;i < (n);i++)
int f[15][3][13];
int bit[12];
void init()
{
    memset(f,0,sizeof(f));
    bit[1] = 1;
    for(int i = 2;i < 11;i++) bit[i] = bit[i-1]*10%13;
    f[0][0][0] = 1;
    for(int i = 0;i <= 10;i++)
    for(int k = 0;k < 13;k++){//直接按照需要的数来递推
        for(int j = 0;j <= 9;j++)
            f[i+1][0][(k+j*bit[i+1])%13] += f[i][0][k];
        f[i+1][0][(k+bit[i+1])%13] -= f[i][1][k];
        f[i+1][1][(k+bit[i+1]*3)%13] += f[i][0][k];//指定来加~~;
        f[i+1][2][(k+bit[i+1])%13] += f[i][1][k];
        for(int j = 0;j <= 9;j++)
            f[i+1][2][(k+bit[i+1]*j)%13] += f[i][2][k];
    }
}
int query(int n)
{
    int d[15]={},tot = 0;
    while(n){
        d[++tot] = n % 10;
        n /= 10;
    }
    int ans = 0,mod = 0,flag = 0;
    for(int i = tot;i > 0;mod = (mod + d[i]*bit[i])%13,i--){
        for(int j = 0;j < d[i];j++)
            ans += f[i-1][2][(13 - (mod + j*bit[i])%13)%13];
        if(flag){
            for(int k = 0;k < d[i];k++){
                ans += f[i-1][0][(13 - (mod + k * bit[i])%13)%13];
            }
            continue;
        }
        if(d[i] > 1) ans += f[i-1][1][(13 - (mod + bit[i])%13)%13];
        if(d[i+1] == 1 && d[i] > 3) ans += f[i][1][(13-mod)%13];
        if(d[i+1] == 1 && d[i] == 3) flag = 1;
    }
    return ans;
}
int main()
{
    init();
    int n;
    while(scanf("%d",&n) == 1){
        printf("%d\n",query(n+1));
    }
}
*/
