/*
����:����һ�������Ǹ������� m x n ���� grid ��
���ҳ�һ�������Ͻǵ����½ǵ�·����ʹ��·���ϵ������ܺ�Ϊ��С��
˵����ÿ��ֻ�����»��������ƶ�һ����
1<=m,n<=200.
����:https://leetcode-cn.com/problems/minimum-path-sum/
*/
//���仯����
#define INF 0x3f3f3f3f
class Solution {
public:
    int dp[210][210];

    int dfs(vector<vector<int>>& grid,int x,int y){
        if(!x && !y)
            return grid[x][y];
        if(dp[x][y])
            return dp[x][y];
        int res1=INF,res2=INF;
        if(x>0)
            res1=dfs(grid,x-1,y);
        if(y>0)
            res2=dfs(grid,x,y-1);
        dp[x][y]=grid[x][y]+min(res1,res2);
        return dp[x][y];
    }

    int minPathSum(vector<vector<int>>& grid) {
        int n=grid.size(),m=grid[0].size();
        return dfs(grid,n-1,m-1);
    }
};

/*
//����dp
#define INF 0x3f3f3f3f
class Solution {
public:
    int dp[210][210];

    int minPathSum(vector<vector<int>>& grid) {
        int n=grid.size(),m=grid[0].size();
        dp[0][0]=grid[0][0];
        int res1,res2;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(!i && !j)
                    continue;
                res1=i>0?dp[i-1][j]:INF;
                res2=j>0?dp[i][j-1]:INF;
                dp[i][j]=grid[i][j]+min(res1,res2);
            }
        }
        return dp[n-1][m-1];
    }
};
*/
