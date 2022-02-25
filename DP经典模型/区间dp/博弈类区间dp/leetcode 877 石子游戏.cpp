/*
Alice 和 Bob 用几堆石子在做游戏。一共有偶数堆石子，排成一行；每堆都有 正 整数颗石子，数目为 piles[i] 。
游戏以谁手中的石子最多来决出胜负。石子的 总数 是 奇数 ，所以没有平局。
Alice 和 Bob 轮流进行，Alice 先开始 。 每回合，玩家从行的 开始 或 结束 处取走整堆石头。
 这种情况一直持续到没有更多的石子堆为止，此时手中 石子最多 的玩家 获胜 。
假设 Alice 和 Bob 都发挥出最佳水平，当 Alice 赢得比赛时返回 true ，当 Bob 赢得比赛时返回 false 。
2 <= piles.length <= 500
piles.length 是 偶数
1 <= piles[i] <= 500
sum(piles[i]) 是 奇数
链接：https://leetcode-cn.com/problems/stone-game
*/
/*
dp[i][j]表示从第i到j堆石头，Alex（先手）能领先Lee（后手）的最大分值。
    1.Alice拿走第j堆，则相当于变成：Alice初始分数为piles[j-1]，第i到j-1堆，且Bob先手。
        dp[i][j] = piles[j-1] + (-dp[i][j-1])
    2.Alice拿走第i堆，则相当于变成：Alice初始分数为piles[i-1]，第i+1到j堆，且Bob先手。
        dp[i][j] = piles[i-1] + (-dp[i+1][j])
    二者取大。
*/
//区间dp
class Solution {
public:
    int dp[510][510];
    bool stoneGame(vector<int>& piles) {
        int n=piles.size();
        //初始状态dp[i][i]=piles[i-1],因为总共有奇数堆石子,开始和结束都是Alice拿
        //即:dp[i][i]和dp[1][n]所表示的差值都是Alice石子数-Bob石子数
        //若dp[1][n]>0 则说明Alex赢
        for(int l=0;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                //博弈的Alice和Bob轮流拿 是通过-dp[i+1][j] -dp[i][j-1]来实现的
                //即上一状态和当前状态 是Alice-Bob和Bob-Alice交替进行的,但dp[1][n]是Alice-Bob
                //每个人拿的时候都是最优策略,实际区间dp只是模拟,在每一步Alice和Bob拿的时候都是取自己赢
                //这个游戏是先手必胜的
                dp[i][j]=max(piles[i-1]-dp[i+1][j],piles[j-1]-dp[i][j-1]);
            }
        }
        return dp[1][n]>0;
    }
};

//数学 Alice是有必胜策略的
// class Solution {
// public:
//     bool stoneGame(vector<int>& piles) {
//         return true;
//     }
// };
