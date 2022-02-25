#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11000
#define M 100
using namespace std;
//ac 547ms 4284K 背包的前i-1个数状态去递推前i个数状态
/*
题意:n个数,相邻两个数a[i],a[i+1]之间的运算符只能是'+'或'-',问
是否存在一种运算顺序使得n个数的运算结果能被k整除,n个数的计算
顺序只能是给定的顺序.
链接:http://poj.org/problem?id=1745
思路:n<=10^4,显然暴力枚举运算符号的可能组合(O(2^(n-1)))显然会TLE,因此
可以考虑状态转移dp,已知:(a+b)%mod=(a%mod+b%mod)%mod.
可以考虑采用背包问题的前i-1个数的运算模k结果去递推前i个数的运算模k
结果,那么对于第i个数就有2种转移,一种是对于加法,一种是对于减法.
设dp[i][j]表示前i个数运算结果对k取模余数是否为j,dp[i][j]=1表示为真,
dp[i][j]=0表示为假.那么如果dp[i-1][j]=1,对应的就可以根据前i-1个数的
运算取模结果与第i个数再运算取模得到前i个数运算取模的可能状态,即
dp[i][(j+a[i]%k)%k]=1,因为j已经是取模后的余数了所以不再取模,
而这个公式只是针对a[i]为正数,(j+a[i]%k)也为正数的情况,如果要取模的数
为负数还需要将取模得到的负数再加上k,这里为了统一正负数的结果正数性,统一
都在加上k的结果后再对k取模,即:
a[i]=(a[i]%k+k)%k;
dp[i][((j+a[i])%k+k)%k]=1;
dp[i][((j-a[i])%k+k)%k]=1;
不能用滚动数组优化成一维,因为
dp[cal(j+a[i])]=1;
dp[cal(j-a[i])]=1;
有两种+或-,无论j升序还是降序,dp[j]不能保证是前i-1个数的状态
*/
int n,k,a[N],dp[N][M];

int cal(int x){
    return (x%k+k)%k;
}

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i]=cal(a[i]);
    }
    dp[1][a[1]]=1;
    for(int i=2;i<=n;i++){
        //因为是二维dp,能够保证前i-1个状态永远是没有和第i个数运算的结果,因此这里j 升序 降序都是可以的
        for(int j=0;j<k;j++){
            if(dp[i-1][j]){//前i-1个数运算预算对k取模 余数为j,在余数为j的基础上和第i个数再取模运算 可得到前i个数取模运算余数的状态
                //+/- 2个可能的状态
                dp[i][cal(j+a[i])]=1;
                dp[i][cal(j-a[i])]=1;
            }
        }
    }
    if(dp[n][0])
        printf("Divisible");
    else
        printf("Not divisible");
    return 0;
}

/*
//ac 438ms 4672K 背包容量是按照前i-1个状态的去逆推的 这个和01背包的思维更相像
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11000
#define M 100
using namespace std;

int n,k,a[N],dp[N][M];

int cal(int x){
    return (x%k+k)%k;
}

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<k;j++){
            //这是取模的逆运算吧,假设前i个数运算后取模的余数j成立,
            //那么((j+/-a[i])%k+k)%k的前i-1个数的运算余数肯定也是成立的.
            //这个和背包的思维已经很接近了
            dp[i][j]=dp[i-1][cal(j+a[i])] || dp[i-1][cal(j-a[i])];
        }
    }
    if(dp[n][0])
        printf("Divisible");
    else
        printf("Not divisible");
    return 0;
}
*/

/*
//ac 454ms 640K 滚动数组优化空间dp[2][Max]
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int Max = 205;
const int temp = 100;



int main(){
    int n, k, i, j, num, val;
    bool dp[2][Max];
   while(scanf("%d %d", &n, &k) != EOF){
       memset(dp, false, sizeof(dp));
       scanf("%d", &num);
       dp[1][num % k + temp] = true;
       for(i = 2; i <= n; i ++){
           scanf("%d", &num);
           for(j = 0; j < Max; j ++)
               dp[i%2][j] = false;
           for(j = 0; j < Max; j ++)
               if(dp[1 - i%2][j]){
                   val = j - temp + num;
                  val %= k;
                  dp[i%2][val + temp] = true;
                   val = j - temp - num;
                   val %= k;
                   dp[i%2][val + temp] = true;
                }
        }
        if(dp[n%2][temp]) cout << "Divisible" << endl;
       else cout << "Not divisible" << endl;
    }
    return 0;
}
*/

/*
//TLE 暴力枚举搜索 时间复杂度O(2^(n-1)) n个数之间有n-1个运算符(+/-)
//每个运算符只有2种可能 加法或减法,n个数是必修都取的,所以也无法剪枝
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11000
#define M 100
using namespace std;

int n,k,a[N],dp[N][M],flag;

int cal(int x){
    return (x%k+k)%k;
}

int dfs(int i,int sum){
    if(i == n+1){
        if(sum%k == 0)//只要n个数运算结果取模k余数为0 就退出dfs不再搜索
            return 1;
        else
            return 0;
    }
    if(dfs(i+1,sum+a[i])) return 1;
    if(dfs(i+1,sum-a[i])) return 1;
    return 0;//考虑上一个数 另一种运算符
}

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    if(dfs(2,a[1]))//只需枚举n-1个中间的运算符
        printf("Divisible");
    else
        printf("Not divisible");
    return 0;
}
*/

/*
//不是很理解这种直接对a[i]数值绝对值取正的取模做法 可能数学上有对应证明吧
//参考博客:https://blog.csdn.net/Li_O_Liu/article/details/105443987
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int N,K,i,j,t;
    int num[10010];
    bool dp[10010][110];
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&N,&K);
    for(i=0;i<N;i++){
        scanf("%d",&t);
        num[i]=abs(t)%K;
    }
    dp[0][num[0]]=1;
    for(i=1;i<N;i++)
    {
        for(j=0;j<K;j++)//遍历余数0~K-1的情况
        {
            if(dp[i-1][j])//上一轮存在余数j的情况
            {
                t=abs(j+num[i])%K;
                dp[i][t]=1;
                t=abs(j-num[i])%K;
                dp[i][t]=1;
            }
        }
    }
    if(dp[N-1][0])
        printf("Divisible\n");
    else
        printf("Not divisible\n");
    return 0;
}
*/
