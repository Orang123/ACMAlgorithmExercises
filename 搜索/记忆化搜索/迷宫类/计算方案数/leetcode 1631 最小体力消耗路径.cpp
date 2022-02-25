/*
你准备参加一场远足活动。给你一个二维 rows x columns 的地图 heights ，
其中 heights[row][col] 表示格子 (row, col) 的高度。一开始你在最左上角的格子 (0, 0) ，
且你希望去最右下角的格子 (rows-1, columns-1) （注意下标从 0 开始编号）。
你每次可以往 上，下，左，右 四个方向之一移动，你想要找到耗费 体力 最小的一条路径。
一条路径耗费的 体力值 是路径上相邻格子之间 高度差绝对值 的 最大值 决定的。
请你返回从左上角走到右下角的最小 体力消耗值 。
链接：https://leetcode-cn.com/problems/path-with-minimum-effort
思路:不能用记忆化搜索,因为题目叙述里 并没有处理 重复往回走的问题,这样记忆化
一直往回走就会死循环.
*/
// bfs+剪枝 788ms,因为在每个点会先考虑周围最近的路径,这样不会导致某个不好的路径先行dfs递归搜索 最坏情形下 需要搜索所有(0,0)到达(n-1,m-1)的路径
//用dfs会超时
class Solution {
public:
    struct State{
        int x,y,val;
        State(int x=0,int y=0,int val=0):x(x),y(y),val(val){}
    };
    int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
    int dp[110][110],n,m;
    void bfs(vector<vector<int>>& heights){
        queue<State> Q;
        dp[0][0]=0;
        Q.push(State(0,0,0));
        State tp;
        while(!Q.empty()){
            tp=Q.front();
            Q.pop();
            if(tp.x == n-1 && tp.y == m-1)
                continue;
            int nx,ny;
            for(int i=0;i<4;i++){
                nx=tp.x+dir[i][0];
                ny=tp.y+dir[i][1];
                if(nx<0 || ny<0 || nx == n || ny == m)
                    continue;
                int h=max(tp.val,abs(heights[tp.x][tp.y]-heights[nx][ny]));
                if(h>=dp[nx][ny])
                    continue;
                dp[nx][ny]=h;
                Q.push(State(nx,ny,h));
            }
        }
    }

    int minimumEffortPath(vector<vector<int>>& heights) {
        memset(dp,0x3f,sizeof(dp));
        n=heights.size(),m=heights[0].size();
        bfs(heights);
        return dp[n-1][m-1];
    }
};
//记忆化搜索 TLE
//因为题目叙述里 并没有处理 重复往回走的问题,这样记忆化一直往回走就会死循环.
// class Solution {
// public:
//     int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
//     int dp[110][110],n,m;
//     int dfs(vector<vector<int>>& heights,int x,int y){
//         if(x == n-1 && y == m-1)
//             return dp[x][y]=0;
//         if(dp[x][y]!=0x3f3f3f3f)
//             return dp[x][y];
//         int nx,ny;
//         for(int i=0;i<4;i++){
//             nx=x+dir[i][0];
//             ny=y+dir[i][1];
//             if(nx<0 || ny<0 || nx == n || ny == m)
//                 continue;
//             int tp=abs(heights[x][y]-heights[nx][ny]);
//             dp[x][y]=min(dp[x][y],max(tp,dfs(heights,nx,ny)));
//         }
//         return dp[x][y];
//     }
//     int minimumEffortPath(vector<vector<int>>& heights) {
//         memset(dp,0x3f,sizeof(dp));
//         n=heights.size(),m=heights[0].size();
//         return dfs(heights,0,0);
//     }
// };


// 并查集模板
// class UnionFind {
// public:
//     vector<int> parent;
//     vector<int> size;
//     int n;
//     // 当前连通分量数目
//     int setCount;

// public:
//     UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
//         iota(parent.begin(), parent.end(), 0);
//     }

//     int findset(int x) {
//         return parent[x] == x ? x : parent[x] = findset(parent[x]);
//     }

//     bool unite(int x, int y) {
//         x = findset(x);
//         y = findset(y);
//         if (x == y) {
//             return false;
//         }
//         if (size[x] < size[y]) {
//             swap(x, y);
//         }
//         parent[y] = x;
//         size[x] += size[y];
//         --setCount;
//         return true;
//     }

//     bool connected(int x, int y) {
//         x = findset(x);
//         y = findset(y);
//         return x == y;
//     }
// };

// class Solution {
// public:
//     int minimumEffortPath(vector<vector<int>>& heights) {
//         int m = heights.size();
//         int n = heights[0].size();
//         vector<tuple<int, int, int>> edges;
//         for (int i = 0; i < m; ++i) {
//             for (int j = 0; j < n; ++j) {
//                 int id = i * n + j;
//                 if (i > 0) {
//                     edges.emplace_back(id - n, id, abs(heights[i][j] - heights[i - 1][j]));
//                 }
//                 if (j > 0) {
//                     edges.emplace_back(id - 1, id, abs(heights[i][j] - heights[i][j - 1]));
//                 }
//             }
//         }
//         sort(edges.begin(), edges.end(), [](const auto& e1, const auto& e2) {
//             auto&& [x1, y1, v1] = e1;
//             auto&& [x2, y2, v2] = e2;
//             return v1 < v2;
//         });

//         UnionFind uf(m * n);
//         int ans = 0;
//         for (const auto [x, y, v]: edges) {
//             uf.unite(x, y);
//             if (uf.connected(0, m * n - 1)) {
//                 ans = v;
//                 break;
//             }
//         }
//         return ans;
//     }
// };
