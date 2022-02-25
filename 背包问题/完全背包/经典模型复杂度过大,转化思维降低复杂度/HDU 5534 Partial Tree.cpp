/*
题意:给定一颗无向树的节点数n和各个度i对应的权值val[i],定义酷度为
每个节点的度对应的权值的总和,求最大酷度.
n<=2015,val[i]<=10^4.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5534
思路:没有给出具体的树的结构,但树的所有节点度数之和为2*(n-1)=2n-2.
无法直接从树的所有结构形状去考虑,而这个问题只需考虑给每个节点分配
几个度使得所有节点的度之和为2n-2,这样就一定能构成一棵树,然后在所有
度数之和为2n-2的情况中求出每个节点度权值之和最大的,显然某种度数可以
分给很多节点,显然这是个二维费用完全背包问题.
dp[i][j]代表将所有可能度数分给恰好i个节点,这些节点度数之和恰好是j时
每个节点度数权值和的最大值.但这个做法显然复杂度O(n^3)=8*10^9会TLE.

尝试优化掉节点个数这个维度:
可以考虑先给每个节点分配1个度,那么初始状态就是n*val[1],这样就已经分配了
度数为n,而后续只要考虑将剩下的n-2的度全部分配出去,就一定能构成一棵树,
此时并不需要考虑这n-2个度分给了几个节点,因为每个节点已经假设它们作为叶子
节点分配了一个度,剩下的度可能的分法是1..n-2,每种度可以分很多次,只要保证
分够n-2度即可.这样就能优化掉之前的分配节点个数这个维度,所以优化后的一维dp
表示为dp[i]代表在每个节点已经分配一个度时,剩下的n-2度先分配i度所能获得的
最大权值.
*/
//ac 78ms 先枚举度数后枚举背包容量 一维数组实现
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2020
#define M 2020
using namespace std;

//dp[i]代表在每个节点已经分配一个度时,剩下的n-2度先分配i度所能获得的最大权值.
int n,val[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));//优化掉节点个数维度后,剩下n-2度一定能恰好装满,所以可以全初始化为0
        scanf("%d",&n);
        for(int i=1;i<n;i++)
            scanf("%d",&val[i]);
        //先给每个节点分配一个度,这样dp时就无需考虑剩下的n-2度给几个节点分配了,因为只要分配完n-2度就一定能构成树
        dp[0]=n*val[1];
        for(int i=1;i<=n-2;i++){//枚举能分配的度i,可能取值为1..n-2
            for(int j=i;j<=n-2;j++)//背包容量为剩余度n-2
                dp[j]=max(dp[j],dp[j-i]+val[i+1]-val[1]);
        }
        printf("%d\n",dp[n-2]);
    }
    return 0;
}

/*
//ac 62ms 先枚举背包容量 再枚举度数
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2020
#define M 2020
using namespace std;

int n,val[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<n;i++)
            scanf("%d",&val[i]);
        dp[0]=n*val[1];
        for(int j=1;j<=n-2;j++){
            for(int i=1;i<=j;i++)
                dp[j]=max(dp[j],dp[j-i]+val[i+1]-val[1]);
        }
        printf("%d\n",dp[n-2]);
    }
    return 0;
}
*/

/*
//TLE 二维完全背包 复杂度O(n^3)=8*10^9
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2020
#define M 2020
using namespace std;

//dp[i][j]代表将所有可能度数分给恰好i个节点,这些节点度数之和恰好是j时每个节点度数权值和的最大值.
int n,val[N],dp[N][M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<n;i++)
            scanf("%d",&val[i]);
        //对于树而言,只有恰好分配给n个节点度数之和为2*n-2才是合法的
        //初始状态只有0个节点度数之和为0才是合法的
        //如果全初始化为0,第一个样例会错误输出6,即:将度为1的f(1)分配三次,但度数之和只有3,未达到2*3-2=4
        dp[0][0]=0;
        for(int i=1;i<=n-1;i++){
            for(int j=i;j<=2*n-2;j++){
                for(int k=1;k<=n;k++)
                    dp[k][j]=max(dp[k][j],dp[k-1][j-i]+val[i]);
            }
        }
        printf("%d\n",dp[n][2*n-2]);
    }
    return 0;
}
*/
