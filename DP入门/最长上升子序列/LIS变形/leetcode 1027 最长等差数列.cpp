/*
给你一个整数数组 nums，返回 nums 中最长等差子序列的长度。
回想一下，nums 的子序列是一个列表 nums[i1], nums[i2], ..., nums[ik] ，且 0 <= i1 < i2 < ... < ik <= nums.length - 1。
并且如果 seq[i+1] - seq[i]( 0 <= i < seq.length - 1) 的值都相同，那么序列 seq 是等差的。
链接：https://leetcode-cn.com/problems/longest-arithmetic-subsequence
*/
//dp[i][diff]表示以nums[i]结尾差值为diff的等差数列的长度 100ms
class Solution {
public:
    int dp[1100][1000];
    int longestArithSeqLength(vector<int>& nums) {
        int ans=0;
        for(int i=0;i<nums.size();i++){
            for(int j=0;j<i;j++){
                int diff=nums[i]-nums[j];
                if(diff<0)//差值为负数 加上1000,实际数据只要加上501即可,但是错了,可能题目数据范围出错了
                    diff+=1000;
                dp[i][diff]=max(dp[i][diff],dp[j][diff]+1);
                ans=max(ans,dp[i][diff]);
            }
        }
        return ans+1;//这里初始值设置为0,所以最后结果要加1
    }
};
