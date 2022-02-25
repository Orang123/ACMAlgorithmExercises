/*
题意:我们正在玩一个猜数游戏，游戏规则如下：
我从 1 到 n 之间选择一个数字。
你来猜我选了哪个数字。
如果你猜到正确的数字，就会 赢得游戏 。
如果你猜错了，那么我会告诉你，我选的数字比你的 更大或者更小 ，并且你需要继续猜数。
每当你猜了数字 x 并且猜错了的时候，你需要支付金额为 x 的现金。如果你花光了钱，就会 输掉游戏 。
给你一个特定的数字 n ，返回能够 确保你获胜 的最小现金数，不管我选择那个数字 。
链接:https://leetcode-cn.com/problems/guess-number-higher-or-lower-ii
思路:dp[i][j]表示从[i,j]中猜出正确数字所需要的最少花费金额.(dp[i][i] = 0)
假设在范围[i,j]中选择x, 则选择x的最少花费金额为: max(dp[i][x-1], dp[x+1][j]) + x
用max的原因是我们要计算最坏反馈情况下的最少花费金额(选了x之后, 正确数字落在花费更高的那侧)
*/
//区间dp
class Solution {
public:
    int dp[210][210];
    int getMoneyAmount(int n) {
        for(int l=0;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                if(!l)
                    dp[i][j]=0;
                else{
                    dp[i][j]=0x3f3f3f3f;
                    for(int k=i;k<=j;k++)
                        dp[i][j]=min(dp[i][j],max(dp[i][k-1],dp[k+1][j])+k);
                }
            }
        }
        return dp[1][n];
    }
};
