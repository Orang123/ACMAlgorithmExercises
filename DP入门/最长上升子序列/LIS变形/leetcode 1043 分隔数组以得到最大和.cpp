/*
给你一个整数数组 arr，请你将该数组分隔为长度最多为 k 的一些（连续）子数组。
分隔完成后，每个子数组的中的所有值都会变为该子数组中的最大值。
返回将数组分隔变换后能够得到的元素最大和。
注意，原数组和分隔后的数组对应顺序应当一致，也就是说，你只能选择分隔数组的位置而不能调整数组中的顺序。
链接：https://leetcode-cn.com/problems/partition-array-for-maximum-sum
*/
//dp[i]表示以arr[i-1]结尾的分割长度为k的 子数组最大值之和
class Solution {
public:
    int dp[510];
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int maxn,n=arr.size();
        for(int i=1;i<=n;i++){//下标不能从i=0开始
            maxn=-1;
            for(int j=i-1;j>=max(i-k,0);j--){
                maxn=max(maxn,arr[j]);
                dp[i]=max(dp[i],dp[j]+maxn*(i-j));
            }
        }
        return dp[n];
    }
};
