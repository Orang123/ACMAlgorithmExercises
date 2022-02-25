/*
给你一个大小为 m x n 的网格和一个球。球的起始坐标为 [startRow, startColumn] 。
你可以将球移到在四个方向上相邻的单元格内（可以穿过网格边界到达网格之外）。
你 最多 可以移动 maxMove 次球。给你五个整数 m、n、maxMove、startRow 以及 startColumn ，
找出并返回可以将球移出边界的路径数量。因为答案可能非常大，返回对 109 + 7 取余 后的结果。
链接：https://leetcode-cn.com/problems/out-of-boundary-paths
*/
class Solution {
public:
    int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
    //到达相同点时 步数不同,所以要加一维步数的限制 三维
    int dp[55][55][55];//dp[x][y][s]表示到达(x,y)点时k步 能走到边界外的方案数
    int dfs(int m,int n,int maxMove,int s,int x,int y){
        if(x<0 || x>=m || y<0 || y>=n)
            return 1;
        int &ans=dp[x][y][s];
        if(ans!=-1)
            return ans;
        ans=0;
        int nx,ny;
        for(int i=0;i<4;i++){
            nx=x+dir[i][0];
            ny=y+dir[i][1];
            if(s<maxMove)
                ans=(ans+dfs(m,n,maxMove,s+1,nx,ny))%1000000007;
        }
        return ans;
    }
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        memset(dp,-1,sizeof(dp));//初始状态要设置为-1,因为0也是 合法方案
        return dfs(m,n,maxMove,0,startRow,startColumn);
    }
};
