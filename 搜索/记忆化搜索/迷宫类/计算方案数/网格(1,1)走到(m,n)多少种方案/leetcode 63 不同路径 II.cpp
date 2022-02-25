/*
����:һ��������λ��һ�� m x n ��������Ͻ� ����ʼ������ͼ�б��Ϊ��Start�� ����
������ÿ��ֻ�����»��������ƶ�һ������������ͼ�ﵽ��������½ǣ�����ͼ�б��Ϊ��Finish������
���ڿ������������ϰ����ô�����Ͻǵ����½ǽ����ж�������ͬ��·����
1<=m,n<=100.
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������
����:https://leetcode-cn.com/problems/unique-paths-ii/
*/
//���仯����
//ʱ�临�Ӷ� �ռ临�Ӷ� O(m*n)
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
//����dp
//ʱ�临�Ӷ� �ռ临�Ӷ� O(m*n)
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
