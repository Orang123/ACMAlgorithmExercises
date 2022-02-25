/*
有 n 个气球，编号为0 到 n - 1，每个气球上都标有一个数字，这些数字存在数组 nums 中。
现在要求你戳破所有的气球。戳破第 i 个气球，你可以获得 nums[i - 1] * nums[i] * nums[i + 1] 枚硬币。
 这里的 i - 1 和 i + 1 代表和 i 相邻的两个气球的序号。如果 i - 1或 i + 1 超出了数组的边界，
那么就当它是一个数字为 1 的气球。
求所能获得硬币的最大数量。
链接：https://leetcode-cn.com/problems/burst-balloons
*/
//区间dp dp[i][j]表示戳破[i,j]内所有气球能获得最多硬币
class Solution {
public:
    int dp[510][510],a[510];
    int maxCoins(vector<int>& nums) {
        int n=nums.size();
        for(int i=1;i<=n;i++)
            a[i]=nums[i-1];
        a[0]=a[n+1]=1;//连段空余的设置为1
        //不能按照l=0是最后一个取,因为这样相邻的取法,只能是连续的a[k-1]*a[k]*a[k+1],显然不符合实际的中间先取 不相邻的变相邻的
        for(int l=0;l<n;l++){//第一个取的是l=0的情况,最后一个取的是l=n-1
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                for(int k=i;k<=j;k++)//[i,k-1]和[k+1,j]都已经取过了,所以相邻的是a[i-1]和a[j+1]
                    dp[i][j]=max(dp[i][j],dp[i][k-1]+dp[k+1][j]+a[i-1]*a[k]*a[j+1]);
            }
        }
        return dp[1][n];
    }
};
