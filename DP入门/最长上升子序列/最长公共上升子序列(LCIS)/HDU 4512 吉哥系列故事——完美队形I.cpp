/*
题意:吉哥这几天对队形比较感兴趣。
有一天，有n个人按顺序站在他的面前，他们的身高分别是h[1], h[2] ... h[n]，
吉哥希望从中挑出一些人，让这些人形成一个新的队形，新的队形若满足以下三点要求，则称之为完美队形：
1、挑出的人保持他们在原队形的相对顺序不变；
2、左右对称，假设有m个人形成新的队形，则第1个人和第m个人身高相同，第2个人和第m-1个人身高相同，
依此类推，当然，如果m是奇数，中间那个人可以任意；
3、从左到中间那个人，身高需保证递增，如果用H表示新队形的高度，则H[1]<H[2]<H[3]....<H[mid]。
现在吉哥想知道：最多能选出多少人组成完美队形？
释义:就是让你求出给定序列的最长的一个左右对称的并且左边递增右边递减的子序列。
序列长度<=200.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=4512
思路:O(n^2)求取LCIS并输出.
要注意有可能出现两个序列的最长公共子序列在原序列中有重叠部分。
就是正序和逆序的LCIS可能会共用对称中心,直接将dp[j]*2会多算一次.
因此要区分.
当分界点不被两个序列共用时：
首先我们枚举当前序列的分解点i，然后我们求a[1..i]与序列a[n..i+1]的LCIS长度*2的值就是一个可能的最大值。
当分界点被两个序列共用时：
首先我们枚举当前序列的分解点i，然后我们求a[1..i]与序列a[n..i]的LCIS长度*2-1的值就是一个可能的最大值。
*/
//ac 0ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
using namespace std;

int n,a[N],b[N],dp[N],ans;

int main(){
    int T,mx;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            b[i]=a[n-i+1];
        for(int i=1;i<=n;i++){
            mx=0;
            for(int j=1;j<=n-i+1;j++){//逆序j的上界n-i+1 表示 b数组下标可以和a数组下标重叠,即回文子序列对称中心被共用
                if(a[i]>b[j])
                    mx=max(mx,dp[j]);
                else if(a[i] == b[j])
                    dp[j]=mx+1;
                if(i<n-j+1)//回文子序列 左侧和右侧没有重叠共用元素
                    ans=max(ans,dp[j]*2);
                else//a b数组共用回文子序列的中心,dp[j]*2将回文对称中心多算了一次,所以要减1 n偶数和奇数都可以出现共用元素,因为是子序列 不一定连续
                    ans=max(ans,dp[j]*2-1);//如果a[i]和b[j]实际没有相等的,和上一状态i-1的dp[j]相比 这里只可能更小 因为减1 对结果无影响
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 15ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
using namespace std;

int n,a[N],b[N],dp[N],ans;

int main(){
    int T,mx;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++){//a数组正序
            mx=0;
            for(int j=n;j>=i;j--){//a数组逆序,下界是i,表示回文对称中心被共用
                if(a[i]>a[j])
                    mx=max(mx,dp[j]);
                else if(a[i] == a[j])
                    dp[j]=mx+1;
                if(j>i)
                    ans=max(ans,dp[j]*2);
                else
                    ans=max(ans,dp[j]*2-1);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
