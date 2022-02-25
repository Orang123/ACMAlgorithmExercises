/*
题意:有 n 个城市通过一些航班连接。给你一个数组 flights ，
其中 flights[i] = [fromi, toi, pricei] ，表示该航班都从城市 fromi 开始，
以价格 pricei 抵达 toi。现在给定所有的城市和航班，以及出发城市 src 和目的地 dst，
你的任务是找到出一条最多经过 k 站中转的路线，使得从 src 到 dst 的 价格最便宜 ，并返回该价格。
 如果不存在这样的路线，则输出 -1。
链接：https://leetcode-cn.com/problems/cheapest-flights-within-k-stops
*/
//记忆化搜索 140ms
//dp[u][k]表示从u节点到达dst节点最多经过k个站点所需花费的最小费用
#define INF 0x3f3f3f3f
class Solution {
public:
    int dp[110][110];
    int dfs(vector<vector<int>>& flights,int u,int k,int ed){
        int &ans=dp[u][k];
        if(u == ed)
            return ans=0;
        if(ans!=-1)
            return ans;
        if(!k)
            return INF;
        ans=INF;
        for(auto &e : flights){
            if(e[0] == u)
                ans=min(ans,dfs(flights,e[1],k-1,ed)+e[2]);
        }
        return ans;
    }
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        memset(dp,-1,sizeof(dp));
        dfs(flights,src,k+1,dst);
        return dp[src][k+1] != INF ? dp[src][k+1] : -1;
    }
};

/*
//阶段性 dp 32ms
// dp[i][k]表示从src至多经过k站到达i的最少费用
#define INF 0x3f3f3f3f
class Solution {
public:
    int dp[110][110];
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        memset(dp,0x3f,sizeof(dp));
        for(int i=0;i<=k+1;i++)
            dp[src][i]=0;
        for(int i=1;i<=k+1;i++){
            for(auto &e : flights){
                if(dp[e[0]][i-1]!=INF)//对dp[e[1]][i]赋值,会导致dp[e[1]]的上一状态被覆盖,所以不能用滚动数组优化
                    dp[e[1]][i]=min(dp[e[1]][i],dp[e[0]][i-1]+e[2]);
            }
        }
        return dp[dst][k+1] != INF ? dp[dst][k+1] : -1;
    }
};
*/

/*
//bfs 小根堆优化 TLE
class Solution {
public:
    struct State{
        int u,dis,k;
        State(int u=0,int dis=0,int k=0):u(u),dis(dis),k(k){}
        bool operator < (const State &x)const{
            return dis>x.dis;
        }
    };
    struct Edge{
        int to,next,w;
    }edge[5000];
    int cnt,head[110];
    void addEdge(int from,int to,int w){
        edge[cnt]={to,head[from],w};
        head[from]=cnt++;
    }
    int bfs(int st,int ed,int k){
        priority_queue<State> Q;
        Q.push(State(st,0,k));
        State tp;
        while(!Q.empty()){
            tp=Q.top();
            Q.pop();
            if(tp.u == ed)
                return tp.dis;
            if(tp.k<0)
                continue;
            for(int i=head[tp.u];i!=-1;i=edge[i].next){
                int v=edge[i].to;
                Q.push(State(v,tp.dis+edge[i].w,tp.k-1));
            }
        }
        return -1;
    }
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        memset(head,-1,sizeof(head));
        for(auto &e : flights)
            addEdge(e[0],e[1],e[2]);
        return bfs(src,dst,k);
    }
};
*/

/*
//暴力dfs TLE 因为没有自环 所以无需vis标记
class Solution {
public:
    struct Edge{
        int to,next,w;
    }edge[5000];
    int cnt,head[110],ans=INT_MAX;
    void addEdge(int from,int to,int w){
        edge[cnt]={to,head[from],w};
        head[from]=cnt++;
    }
    void dfs(int u,int sum,int k,int ed){
        if(u == ed){
            if(k+1>=0)//终点不算中间点
                ans=min(ans,sum);
            return;
        }
        if(k<0 || sum>=ans)
            return;
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].to;
            dfs(v,sum+edge[i].w,k-1,ed);
        }
    }
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        memset(head,-1,sizeof(head));
        for(auto &e : flights)
            addEdge(e[0],e[1],e[2]);
        dfs(src,0,k,dst);
        return ans !=INT_MAX ? ans : -1;
    }
};
*/
