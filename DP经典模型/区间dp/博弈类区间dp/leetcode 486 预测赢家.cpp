/*
给你一个整数数组 nums 。玩家 1 和玩家 2 基于这个数组设计了一个游戏。
玩家 1 和玩家 2 轮流进行自己的回合，玩家 1 先手。开始时，两个玩家的初始分值都是 0 。
每一回合，玩家从数组的任意一端取一个数字（即，nums[0] 或 nums[nums.length - 1]），
取到的数字将会从数组中移除（数组长度减 1 ）。玩家选中的数字将会加到他的得分上。
当数组中没有剩余数字可取时，游戏结束。
如果玩家 1 能成为赢家，返回 true 。如果两个玩家得分相等，同样认为玩家 1 是游戏的赢家，
也返回 true 。你可以假设每个玩家的玩法都会使他的分数最大化。
1 <= nums.length <= 20
0 <= nums[i] <= 107
链接：https://leetcode-cn.com/problems/predict-the-winner
*/
//区间dp 复杂度O(n^2) 0ms
//dp[i][j]表示数组下标第i到j，玩家1（先手）能领先玩家2（后手）的最大分值。
class Solution {
public:
    int dp[510][510];
    bool PredictTheWinner(vector<int>& nums) {
        int n=nums.size();
        //初始状态dp[i][i]=nums[i-1],如果数组大小是奇数则是玩家1最后一个拿,如果是偶数则是玩家2最后一个拿
        //但最终dp[1][n]开始都是玩家1下手拿
        //若dp[1][n]>=0 则说明玩家1赢
        for(int l=0;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                dp[i][j]=max(nums[i-1]-dp[i+1][j],nums[j-1]-dp[i][j-1]);
            }
        }
        return dp[1][n]>=0;
    }
};

/*
//暴力 递归 O(2^n) 168ms
class Solution {
public:
    int dfs(vector<int>& nums,int l,int r,int flag){
        if(l == r)
            return nums[l]*flag;
        int res1=nums[l]*flag+dfs(nums,l+1,r,-flag);
        int res2=nums[r]*flag+dfs(nums,l,r-1,-flag);
         //之所以max里边乘flag,是为了要求取数值上的最大值,因为玩家1和2都是尽可能分数最大化的取法,要恢复成本身的正负,求完后再恢复还得再乘flag
        return max(res1*flag,res2*flag)*flag;
    }
    bool PredictTheWinner(vector<int>& nums) {
        return dfs(nums,0,nums.size()-1,1)>=0;
    }
};
*/
