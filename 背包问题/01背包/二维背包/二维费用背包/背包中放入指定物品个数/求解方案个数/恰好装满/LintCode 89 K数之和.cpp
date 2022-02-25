//ac 61ms 枚举k个数第三层循环升序
/*
题意:给定n个不同的正整数,整数k(k<=n)以及一个目标数字target.　
在这n个数里面找出k个数,使得这k个数的和等于目标数字,求问有多少种方案?
链接:https://www.lintcode.com/problem/k-sum/description
思路:就是求解背包放入k个物品价值和刚好为target的方案个数,很明显需要
恰好装满背包,所以初始化只有dp[0][0]=1.

总结:这个三重循环dp,注意第二层循环既可以是枚举背包剩余容量也可以是
枚举当前容量下放入物品个数k,但都需要逆序降序枚举,因为只有这样才能保证
dp[j-val[i]][k-1]是前i-1个物品时的dp值,如果升序枚举会导致第i个物品重复
放入背包,导致dp[j-val[i]][k-1]是放入第i个物品时的前i个物品时的状态而不是前i-1
个物品的状态.另外第三层循环无论是背包容积还是放入背包物品个数,既可升序也可降序.
*/

/*
如果没有要求k个数,只是找出几种数字组合之和恰好等于目标数字target,就是一个简单的01背包问题.对应例题洛谷P1164 小A点菜
注意:这个只能求解恰好等于目标数字的方案个数,不能求解尽可能多地装满背包的方案数(背包再也装不下的方案数)
背包再也装不下的方案数 对应POJ 3093 Margaritas on the River Walk的做法
题目链接:https://nanti.jisuanke.com/t/T1218
    int kSum(vector<int> &A, int k, int target) {
        int n = A.size();
        int dp[1000];
        memset(dp,0,sizeof(dp));
        dp[0] = 1;
        for (int i = 0; i < n; i ++) {
            for (int t = target; t >= A[i]; t --) {
                dp[t]+=dp[t-A[i]];
            }
        }
        return dp[target];
    }
*/
class Solution {
public:
    /**
     * @param A: An integer array
     * @param k: A positive integer (k <= length(A))
     * @param target: An integer
     * @return: An integera
     * dp[k][j]代表容量为j的背包恰好装入k个物品的总方案数,背包容量j没有剩余
     */
    int kSum(vector<int> &A, int k, int target) {
        // write your code here
        int n = A.size();
        int dp[1000][1000];
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;//恰好装满 只有背包容量为0,装入0个物品 是初始状态,初始化为1
        for (int i = 0; i < n; i ++) {
            for (int t = target; t >= A[i]; t --) {
                 for (int j = 1; j <= k; j ++) {//这里逆序 降序结果也正确
                    dp[j][t] += dp[j-1][t-A[i]];
                 }
            }
        }
        return dp[k][target];
    }
};
/*
//ac 61ms 枚举k个数第三层循环降序
class Solution {
public:
    int kSum(vector<int> &A, int k, int target) {
        // write your code here
        int n = A.size();
        int dp[1000][1000];
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        for (int i = 0; i < n; i ++) {
            for (int t = target; t >= A[i]; t --) {
                 for (int j = k; j >= 1; j --) {//这里升序结果也正确
                    dp[j][t] += dp[j-1][t-A[i]];
                 }
            }
        }
        return dp[k][target];
    }
};
*/
/*
//ac 102ms 枚举k个数第二层循环降序
class Solution {
public:
    int kSum(vector<int> &A, int k, int target) {
        // write your code here
        int n = A.size();
        int dp[1000][1000];
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        for (int i = 0; i < n; i ++) {
            for (int j = k; j >= 1; j --) {//这里必须逆序降序才正确
                for (int t = target; t >= A[i]; t --) {
                    dp[j][t] += dp[j-1][t-A[i]];
                }
            }
        }
        return dp[k][target];
    }
};
*/

/*
//ac 102ms 第三维[A[i],target] 升序
class Solution {
public:
    int kSum(vector<int> &A, int k, int target) {
        // write your code here
        int n = A.size();
        int dp[1000][1000];
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        for (int i = 0; i < n; i ++) {
            for (int j = k; j >= 1; j --) {//这里必须逆序降序才正确
                for (int t = A[i]; t <= target; t ++) {
                    dp[j][t] += dp[j-1][t-A[i]];
                }
            }
        }
        return dp[k][target];
    }
};
*/
