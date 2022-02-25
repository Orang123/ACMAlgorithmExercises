/*
你现在手里有一份大小为 n x n 的 网格 grid，上面的每个 单元格 都用 0 和 1 标记好了。
其中 0 代表海洋，1 代表陆地，请你找出一个海洋单元格，这个海洋单元格到离它最近的陆地
单元格的距离是最大的。如果网格上只有陆地或者海洋，请返回 -1。
我们这里说的距离是「曼哈顿距离」（ Manhattan Distance）：(x0, y0) 和 (x1, y1) 这两个
单元格之间的距离是 |x0 - x1| + |y0 - y1| 。
链接：https://leetcode-cn.com/problems/as-far-from-land-as-possible
*/
//多起点 bfs 将所有1同时入队计算到达 0的最小距离 如果当前距离不能比之前更小,则不会入度
//时间复杂度O(n^2)
class Solution {
public:
    struct State{
        int x,y,s;
        State(int x=0,int y=0,int s=0):x(x),y(y),s(s){}
    };
    int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
    int dp[110][110];
    int maxDistance(vector<vector<int>>& grid) {
        memset(dp,0x3f,sizeof(dp));
        queue<State> Q;
        int n=grid.size(),m=grid[0].size();
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j] == 1){
                    dp[i][j]=0;
                    Q.push(State(i,j,0));
                }
            }
        }
        int ans=-1;
        State tp;
        while(!Q.empty()){
            tp=Q.front();
            Q.pop();
            int nx,ny;
            for(int i=0;i<4;i++){
                nx=tp.x+dir[i][0];
                ny=tp.y+dir[i][1];
                if(nx<0 || nx>=n || ny<0 || ny>=m || tp.s+1>=dp[nx][ny])
                    continue;
                dp[nx][ny]=tp.s+1;
                ans=max(ans,tp.s+1);
                Q.push(State(nx,ny,tp.s+1));
            }
        }
        return ans;
    }
};

//dp
// class Solution {
// public:
//     static constexpr int MAX_N = 100 + 5;
//     static constexpr int INF = int(1E6);

//     int f[MAX_N][MAX_N];
//     int n;

//     int maxDistance(vector<vector<int>>& grid) {
//         this->n = grid.size();
//         vector<vector<int>>& a = grid;

//         for (int i = 0; i < n; ++i) {
//             for (int j = 0; j < n; ++j) {
//                 f[i][j] = (a[i][j] ? 0 : INF);
//             }
//         }

//         for (int i = 0; i < n; ++i) {
//             for (int j = 0; j < n; ++j) {
//                 if (a[i][j]) {
//                     continue;
//                 }
//                 if (i - 1 >= 0) {
//                     f[i][j] = min(f[i][j], f[i - 1][j] + 1);
//                 }
//                 if (j - 1 >= 0) {
//                     f[i][j] = min(f[i][j], f[i][j - 1] + 1);
//                 }
//             }
//         }

//         for (int i = n - 1; i >= 0; --i) {
//             for (int j = n - 1; j >= 0; --j) {
//                 if (a[i][j]) {
//                     continue;
//                 }
//                 if (i + 1 < n) {
//                     f[i][j] = min(f[i][j], f[i + 1][j] + 1);
//                 }
//                 if (j + 1 < n) {
//                     f[i][j] = min(f[i][j], f[i][j + 1] + 1);
//                 }
//             }
//         }

//         int ans = -1;
//         for (int i = 0; i < n; ++i) {
//             for (int j = 0; j < n; ++j) {
//                 if (!a[i][j]) {
//                     ans = max(ans, f[i][j]);
//                 }
//             }
//         }

//         if (ans == INF) {
//             return -1;
//         } else {
//             return ans;
//         }
//     }
// };
