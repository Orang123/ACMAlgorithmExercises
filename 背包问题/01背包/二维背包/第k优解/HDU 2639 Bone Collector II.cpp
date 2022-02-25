#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 1100
using namespace std;
//ac 93ms 第k优解 要求不同次解值都是不同的 尽可能多地装满背包
/*
题意:有N件物品和一个容量为V的背包.放入第i件物品耗费的空间是W[i],得到的价值是val[i].
(N <= 100,V <= 1000),求解背包可装入的物品的最大价值和的第k优解,输出这个第k优解.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2639
思路:在01背包基础上,引入第二维第k优解,则dp[j][k]表示背包容量为j的情况下,
能装下最大价值的第k优解.思路是要求出放入前i个物品的第k优解,就需要在前i-1个物品
k优解的基础上枚举加入第i个物品,然后比较排序求出新的前i个物品的第k优解.

参考博客:https://blog.csdn.net/qq_40596572/article/details/100577284
https://blog.csdn.net/lulipeng_cpp/article/details/7584981
*/
int n,v,k,w[N],val[N],dp[M][35],A[35],B[35];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));//尽可能多地装满
        scanf("%d%d%d",&n,&v,&k);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&w[i]);
        int t;
        //O(NVK)
        for(int i=1;i<=n;i++){
            for(int j=v;j>=w[i];j--){
                for(t=1;t<=k;t++){//枚举第t优解
                    //第t优解只和前i-1个物品下的第t优解有关
                    //前i个物品的第t优解由两个状态组成
                    //分别是放置第i个物品和不放置第i个物品
                    //注意这里可能实际在i较小时没有第t优解,那实际赋值为0
                    A[t]=dp[j-w[i]][t]+val[i];//放置第i个物品
                    B[t]=dp[j][t];//不放置第i个物品
                }
                A[t]=B[t]=-1;//第k+1个下标设置为结束标志
                int a,b,c;//分别为A、B数组的下标 和前i个物品第k优解的下标 从1开始
                a=b=c=1;
                //类似归并排序中归并的思路
                //取A[a]和B[b]中较大的作为dp[j][c]中第c优解
                //A、B数组较后面的值 可能没有第k优解 会是0值,所以实际dp[j][k]如果没有第k优解 会被赋0值
                while(c<=k && (A[a]!=-1 || B[b]!=-1)){
                    if(A[a]>B[b])
                        dp[j][c]=A[a++];//较大值是放置i物品的A第a优解
                    else
                        dp[j][c]=B[b++];//较大值是不放置i物品的前i-1个物品的B第b优解
                    //保证第k优解中没有重复的值,实际这里如果不这样判断,那每个次优解里存的将全是最优解的值,这是重复的情况.
                    //所以必须要保证值不同,次优解值相同的情况只能是恰好装满背包只初始化dp[0][1]=0的情况.
                    if(dp[j][c]!=dp[j][c-1])
                        c++;//求解第c+1优解
                }
            }
        }
        printf("%d\n",dp[v][k]);
    }
    return 0;
}

/*
//恰好装满背包,次优解的值不能有相同值
memset(dp,-0x3f,sizeof(dp));
for(int i=1;i<=k;i++)
    dp[0][i]=0;
    int t;
    for(int i=1;i<=n;i++){
        for(int j=v;j>=w[i];j--){
            //优化1:如果最优解都不能恰好装满其余次优解更不可能恰好装满
            if(dp[j-w[i]][1]<0) continue;
            for(t=1;t<=k;t++){
                A[t]=dp[j-w[i]][t]+val[i];
                B[t]=dp[j][t];
            }
            A[t]=B[t]=-1;
            int a,b,c;
            a=b=c=1;
            while(c<=k && (A[a]!=-1 || B[b]!=-1)){
                if(A[a]>B[b])
                    dp[j][c]=A[a++];
                else
                    dp[j][c]=B[b++];
                if(dp[j][c]!=dp[j][c-1])//保证次优解的值都是不同的
                    c++;
            }
        }
    }
*/
