/*
题意:如果序列 X_1, X_2, ..., X_n 满足下列条件，就说它是 斐波那契式 的：
n >= 3 对于所有 i + 2 <= n，都有 X_i + X_{i+1} = X_{i+2}
给定一个严格递增的正整数数组形成序列 arr ，找到 arr 中最长的斐波那契式的子序列的长度。
如果一个不存在，返回  0 。（回想一下，子序列是从原序列 arr 中派生出来的，它从 arr 中
删掉任意数量的元素（也可以不删），而不改变其余元素的顺序。例如， [3, 5, 8] 是 
[3, 4, 5, 6, 7, 8] 的一个子序列）
链接：https://leetcode-cn.com/problems/length-of-longest-fibonacci-subsequence
*/
/*
定义状态
dp[j][i]表示以A[j]，A[i]结尾的最长斐波那契子序列长度。
转移方程
dp[j][i] = MAX(dp[k][j] + 1) 满足 k < j < i，且A[k] = A[i] - A[j]。
使用一个map，将A[i]与i映射起来。即 map[A[i]] = i。
*/
//复杂度O(n^2*log(n))
class Solution {
public:
    int dp[1100][1100];
    int lenLongestFibSubseq(vector<int>& arr) {
        unordered_map<int,int> mp;
        for(int i=0;i<arr.size();i++)
            mp[arr[i]]=i;
        int ans=0;
        for(int i=0;i<arr.size();i++){
            for(int j=0;j<i;j++){
                dp[j][i]=2;//初始状态长度为2
                int val=arr[i]-arr[j];
                if(mp.count(val) && mp[val]<j){//val的下标必须小于j 题目保证了数组升序 实际arr[i]-arr[j]<arr[j]就行
                    int k=mp[val];//arr[k]<arr[j]<arr[i]
                    dp[j][i]=max(dp[j][i],dp[k][j]+1);
                }
                ans=max(ans,dp[j][i]);
            }
        }
        return ans>=3?ans:0;
    }
};
