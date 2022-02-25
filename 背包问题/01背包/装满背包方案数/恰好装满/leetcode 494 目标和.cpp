/*
给你一个整数数组 nums 和一个整数 target 。
向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：
例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。

链接：https://leetcode-cn.com/problems/target-sum
*/
/**
     * 494
     * 输入: nums: [1, 1, 1, 1, 1], S: 3
     * 输出: 5
     * 解释:
     * -1+1+1+1+1 = 3
     * +1-1+1+1+1 = 3
     * +1+1-1+1+1 = 3
     * +1+1+1-1+1 = 3
     * +1+1+1+1-1 = 3
     *
     * sum(P) 前面符号为+的集合；sum(N) 前面符号为减号的集合
     * 所以题目可以转化为
     * sum(P) - sum(N) = target
     * => sum(nums) + sum(P) - sum(N) = target + sum(nums)
     * => 2 * sum(P) = target + sum(nums)
     * => sum(P) = (target + sum(nums)) / 2
     * 因此题目转化为01背包，也就是能组合成容量为sum(P)的方式有多少种
     */
//dp 01背包 复杂度O((sum+target)*n)
class Solution {
public:
    int dp[21010];
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum=target;
        for(auto val : nums)
            sum+=val;
        if(sum<0|| sum%2)//sum小于0 或者不能整除 则方案数为0
            return 0;
        sum/=2;
        dp[0]=1;
        for(int i=0;i<nums.size();i++){
            for(int j=sum;j>=nums[i];j--)
                dp[j]+=dp[j-nums[i]];
        }
        return dp[sum];
    }
};


//暴力dfs 时间复杂度O(2^n)
// class Solution {
// public:
//     int ans;
//     void dfs(vector<int>& nums, int target,int i,int sum){
//         if(i == nums.size()){
//             if(sum == target)
//                 ans++;
//             return;
//         }
//         dfs(nums,target,i+1,sum+nums[i]);
//         dfs(nums,target,i+1,sum-nums[i]);
//     }
//     int findTargetSumWays(vector<int>& nums, int target) {
//         dfs(nums,target,0,0);
//         return ans;
//     }
// };

