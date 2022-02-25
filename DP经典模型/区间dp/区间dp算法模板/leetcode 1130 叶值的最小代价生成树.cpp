/*
题意:给你一个正整数数组 arr，考虑所有满足以下条件的二叉树：
每个节点都有 0 个或是 2 个子节点。
数组 arr 中的值与树的中序遍历中每个叶节点的值一一对应。（知识回顾：如果一个节点有 0 个子节点，那么该节点为叶节点。）
每个非叶节点的值等于其左子树和右子树中叶节点的最大值的乘积。
在所有这样的二叉树中，返回每个非叶节点的值的最小可能总和。这个和的值是一个 32 位整数。
2 <= arr.length <= 40
1 <= arr[i] <= 15
答案保证是一个 32 位带符号整数，即小于 2^31。
链接:https://leetcode-cn.com/problems/minimum-cost-tree-from-leaf-values/
思路:dp[i][j]表示数组arr小标i~j内所能生成二叉树非叶节点最小值累加和
c[i][j]表示数组arr i~j内最大的叶子节点的数值
*/
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int dp[50][50],c[50][50],n=arr.size()-1;
        memset(c,0,sizeof(c));
        for(int i=0;i<=n;i++){
            for(int j=i;j<=n;j++){
                for(int k=i;k<=j;k++)
                    c[i][j]=max(c[i][j],arr[k]);
            }
        }
        memset(dp,0x3f,sizeof(dp));
        for(int i=0;i<=n;i++)
            dp[i][i]=0;
        for(int l=1;l<=n;l++){
            for(int i=0;i+l<=n;i++){
                int j=i+l;
                for(int k=i;k<j;k++)
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+c[i][k]*c[k+1][j]);
            }
        }
        return dp[0][n];
    }
};

/*
//单调栈没看懂
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int res = 0;
        stack<int> s;
        s.push(INT_MAX);
        int n = arr.size();
        for (auto& a : arr) {
            while (s.top() <= a) {
                int temp = s.top();
                s.pop();
                res += temp * min(s.top(), a);
            }
            s.push(a);
        }
        while (s.size() > 2) {
            int temp = s.top();
            s.pop();
            res += temp * s.top();
        }
        return res;
    }
};
*/
