/*
题意:一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
1<=m,n<=100.
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
链接:https://leetcode-cn.com/problems/unique-paths-ii/
*/
//记忆化搜索
//时间复杂度 空间复杂度 O(m*n)
class Solution {
public:
    int dp[110][110];
    int dfs(vector<vector<int>>& obstacleGrid,int x,int y){
        if(!x && !y)
            return 1;
        if(dp[x][y])
            return dp[x][y];
        int res1=0,res2=0;
        if(x>0 && !obstacleGrid[x-1][y])
            res1=dfs(obstacleGrid,x-1,y);
        if(y>0 && !obstacleGrid[x][y-1])
            res2=dfs(obstacleGrid,x,y-1);
        dp[x][y]=res1+res2;
        return dp[x][y];
    }
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m=obstacleGrid.size(),n=obstacleGrid[0].size();
        if(obstacleGrid[m-1][n-1])
            return 0;
        return dfs(obstacleGrid,m-1,n-1);
    }
};
/*
//正向dp
//时间复杂度 空间复杂度 O(m*n)
class Solution {
public:
    int dp[110][110];
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m=obstacleGrid.size(),n=obstacleGrid[0].size();
        if(obstacleGrid[m-1][n-1] || obstacleGrid[0][0])
            return 0;
        dp[0][0]=1;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(obstacleGrid[i][j])
                    continue;
                if(i>0)
                    dp[i][j]+=dp[i-1][j];
                if(j>0)
                    dp[i][j]+=dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};
*/
