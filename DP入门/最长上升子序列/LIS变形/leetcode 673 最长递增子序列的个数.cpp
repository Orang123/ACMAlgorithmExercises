/*
����һ��δ������������� nums �� ��������������еĸ��� ��
ע�� ������б����� �ϸ� �����ġ�
����:https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/
*/
//LIS
class Solution {
public:
    int dp[2100],cnt[2100];
    int findNumberOfLIS(vector<int>& nums) {
        int ans=0;
        for(int i=0;i<nums.size();i++){
            cnt[i]=dp[i]=1;
            for(int j=0;j<i;j++){
                if(nums[i]>nums[j]){
                    if(dp[i]<dp[j]+1){
                        dp[i]=dp[j]+1;
                        cnt[i]=cnt[j];
                    }
                    else if(dp[i] == dp[j]+1)
                        cnt[i]+=cnt[j];
                }
            }
            ans=max(ans,dp[i]);
        }
        int res=0;
        for(int i=0;i<nums.size();i++){
            if(dp[i] == ans)
                res+=cnt[i];
        }
        return res;
    }
};
