/*
在一个 n x n 的国际象棋棋盘上，一个骑士从单元格 (row, column) 开始，并尝试进行 k 次移动。
行和列是 从 0 开始 的，所以左上单元格是 (0,0) ，右下单元格是 (n - 1, n - 1) 。
象棋骑士有8种可能的走法，如下图所示。每次移动在基本方向上是两个单元格，然后在正交方向上是一个单元格。
每次骑士要移动时，它都会随机从8种可能的移动中选择一种(即使棋子会离开棋盘)，然后移动到那里。
骑士继续移动，直到它走了 k 步或离开了棋盘。
返回 骑士在棋盘停止移动后仍留在棋盘上的概率 。
链接：https://leetcode-cn.com/problems/knight-probability-in-chessboard
*/
class Solution {
public:
    int dir[8][2]={{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}};
    double dp[30][30][110];
    double dfs(int n,int x,int y,int k){
        if(x<0 || x>=n || y<0 || y>=n)
            return 0;
        double &ans=dp[x][y][k];
        if(!k)
            return ans=1;
        if(ans!=-1.0)
            return ans;
        ans=0;
        int nx,ny;
        for(int i=0;i<8;i++){
            nx=x+dir[i][0];
            ny=y+dir[i][1];
            ans+=dfs(n,nx,ny,k-1);
        }
        ans/=8;
        return ans;
    }
    double knightProbability(int n, int k, int row, int column) {
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                for(int t=0;t<=k;t++)
                    dp[i][j][t]=-1;//初始化为-1,0也是合法状态
        return dfs(n,row,column,k);
    }
};
