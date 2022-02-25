/*
题意:求解一个串中次长上升子序列的的长度
序列长度<=1000.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=5087
思路:对于有多个最长的子序列,那么次长就是最长的长度,如果
最长的子序列只有唯一的一个,那么次长就是原先最长的基础上减1.
*/
//ac 93ms
#include<cstdio>
#include<algorithm>
#define N 1100
using namespace std;

//num[i]记录以a[i]结尾的数字的LIS的个数
int n,a[N],dp[N],num[N],ans,sum;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=1;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++){
            dp[i]=num[i]=1;//初始值为1
            for(int j=1;j<i;j++){
                if(a[j]<a[i]){
                    if(dp[i]<dp[j]+1){
                        dp[i]=dp[j]+1;
                        num[i]=num[j];
                    }
                    else if(dp[i] == dp[j]+1)
                        num[i]+=num[j];
                }
            }
            ans=max(ans,dp[i]);
        }
        sum=0;
        for(int i=1;i<=n;i++){
            if(ans == dp[i])
                sum+=num[i];
        }
        if(sum!=1)//这里写成sum>1 就会wa,不知何原因
            printf("%d\n",ans);
        else
            printf("%d\n",ans-1);
    }
    return 0;
}

