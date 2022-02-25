/*
你有一个凸的 n 边形，其每个顶点都有一个整数值。给定一个整数数组 values ，
其中 values[i] 是第 i 个顶点的值（即 顺时针顺序 ）。
假设将多边形 剖分 为 n - 2 个三角形。对于每个三角形，该三角形的值是顶点标记的乘积，
三角剖分的分数是进行三角剖分后所有 n - 2 个三角形的值之和。
返回 多边形进行三角剖分后可以得到的最低分 。
链接：https://leetcode-cn.com/problems/minimum-score-triangulation-of-polygon
*/
//区间dp dp[i][j]表示子数组[i,j]内分割的三角形最小乘积和
class Solution {
public:
    int dp[55][55];
    int minScoreTriangulation(vector<int>& values) {
        int n=values.size();
        for(int l=2;l<n;l++){
            for(int i=0;i+l<n;i++){
                int j=i+l;
                dp[i][j]=0x3f3f3f3f;//区间长度小于3,即长度最小为2 初始为0
                for(int k=i+1;k<j;k++)
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]+values[i]*values[k]*values[j]);
            }
        }
        return dp[0][n-1];
    }
};
