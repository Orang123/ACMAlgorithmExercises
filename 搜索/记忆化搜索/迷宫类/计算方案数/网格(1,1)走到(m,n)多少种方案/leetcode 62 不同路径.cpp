/*
题意:一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
问总共有多少条不同的路径？
1<=m,n<=100.
链接:https://leetcode-cn.com/problems/unique-paths/
思路:
*/
//记忆化搜索
//时间复杂度 空间复杂度 O(m*n)
class Solution {
public:
    int dp[110][110];
    int dfs(int x,int y){
        if(x == 1 && y == 1)
            return 1;
        if(!x || !y)
            return 0;
        if(dp[x][y])
            return dp[x][y];
        dp[x][y]=dfs(x-1,y)+dfs(x,y-1);
        return dp[x][y];
    }
    int uniquePaths(int m, int n) {
        return dfs(m,n);
    }
};

/*
//正向dp
//时间复杂度 空间复杂度 O(m*n)
class Solution {
public:
    int dp[110][110];
    int uniquePaths(int m, int n) {
        dp[1][1]=1;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(i == 1 && j == 1)//避免修改初始dp[1][1]=1的状态
                    continue;
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
        return dp[m][n];
        // vector<vector<int>> f(m, vector<int>(n));
        // for (int i = 0; i < m; ++i) {
        //     f[i][0] = 1;
        // }
        // for (int j = 0; j < n; ++j) {
        //     f[0][j] = 1;
        // }
        // for (int i = 1; i < m; ++i) {
        //     for (int j = 1; j < n; ++j) {
        //         f[i][j] = f[i - 1][j] + f[i][j - 1];
        //     }
        // }
        // return f[m - 1][n - 1];
    }
};
*/
