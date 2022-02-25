//记忆化搜索 8ms
#define INF 0x3f3f3f3f
class Solution {
public:
    int dir[3][2]={{1,-1},{1,0},{1,1}};
    int dp[110][110],n,m;

    int dfs(vector<vector<int>>& matrix,int x,int y){
        if(x == n-1)
            return matrix[x][y];
        if(dp[x][y]!=INF)
            return dp[x][y];
        int nx,ny;
        for(int i=0;i<3;i++){
            nx=x+dir[i][0];
            ny=y+dir[i][1];
            if(ny<0 || ny>=m)
                continue;
            dp[x][y]=min(dp[x][y],matrix[x][y]+dfs(matrix,nx,ny));
        }
        return dp[x][y];
    }

    int minFallingPathSum(vector<vector<int>>& matrix) {
        memset(dp,0x3f,sizeof(dp));
        n=matrix.size(),m=matrix[0].size();
        int ans=INF;
        for(int i=0;i<m;i++)
            ans=min(ans,dfs(matrix,0,i));
        return ans;
    }
};

/*
//正向dp 12ms
#define INF 0x3f3f3f3f
class Solution {
public:
    int dir[3][2]={{-1,-1},{-1,0},{-1,1}};
    int dp[110][110];
    int minFallingPathSum(vector<vector<int>>& matrix) {
        memset(dp,0x3f,sizeof(dp));
        int n=matrix.size(),m=matrix[0].size(),ans=INF;
        for(int i=0;i<m;i++){
            dp[0][i]=matrix[0][i];
            ans=min(ans,dp[0][i]);
        }
        if(n == 1)//只有一行
            return ans;
        ans=INF;//否则ans再初始化为INF
        for(int i=1;i<n;i++){
            for(int j=0;j<m;j++){
                int x,y;
                for(int k=0;k<3;k++){
                    x=i+dir[k][0];
                    y=j+dir[k][1];
                    if(y<0 || y>=m)
                        continue;
                    dp[i][j]=min(dp[i][j],dp[x][y]+matrix[i][j]);
                }
                if(i == n-1)
                    ans=min(ans,dp[i][j]);
            }
        }
        return ans;
    }
};
*/

/*
// 正向dp 12ms 一维滚动数组优化空间
#define INF 0x3f3f3f3f
class Solution {
public:
    int dp[110];
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n=matrix.size(),m=matrix[0].size(),ans=INF;
        memset(dp,0x3f,sizeof(dp));
        for(int i=0;i<m;i++){
            dp[i]=matrix[0][i];
            ans=min(ans,dp[i]);
        }
        if(n == 1)//只有一行
            return ans;
        ans=INF;
        for(int i=1;i<n;i++){
            for(int j=0;j<m;j++){
                int tp,pre;
                tp=dp[j];
                if(!j)
                    dp[j]=min(dp[j],dp[j+1])+matrix[i][j];
                else if(j == m-1)
                    dp[j]=min(pre,dp[j])+matrix[i][j];//pre是dp[j-1] 因为dp[j-1]应被更新了,所以每次会记录下来
                else
                    dp[j]=min(pre,min(dp[j],dp[j+1]))+matrix[i][j];
                pre=tp;
                if(i == n-1)
                    ans=min(ans,dp[j]);
            }
        }
        return ans;
    }
};
*/

/*
//bfs 小根堆优化 928ms
#define INF 0x3f3f3f3f
class Solution {
public:
    struct State{
        int x,y,sum;
        State(int x=0,int y=0,int sum=0):x(x),y(y),sum(sum){}
        bool operator<(const State &x)const{
            return sum>x.sum;
        }
    };
    int dir[3][2]={{1,-1},{1,0},{1,1}};
    int dp[110][110];
    int bfs(vector<vector<int>>& matrix){
        int n=matrix.size(),m=matrix[0].size();
        int ans=INF;
        priority_queue<State> Q;
        for(int i=0;i<m;i++){
            dp[0][i]=matrix[0][i];
            Q.push(State(0,i,dp[0][i]));
        }
        int nx,ny;
        State tp;
        while(!Q.empty()){
            tp=Q.top();
            Q.pop();
            if(tp.x == n-1){
                ans=min(ans,tp.sum);
                continue;
            }
            for(int i=0;i<3;i++){
                nx=tp.x+dir[i][0];
                ny=tp.y+dir[i][1];
                if(ny<0 || ny>=m || dp[nx][ny]<=dp[tp.x][tp.y]+matrix[nx][ny])
                    continue;
                dp[nx][ny]=dp[tp.x][tp.y]+matrix[nx][ny];
                Q.push(State(nx,ny,dp[nx][ny]));
            }
        }
        return ans;
    }
    int minFallingPathSum(vector<vector<int>>& matrix) {
        memset(dp,0x3f,sizeof(dp));
        return bfs(matrix);
    }
};
*/
