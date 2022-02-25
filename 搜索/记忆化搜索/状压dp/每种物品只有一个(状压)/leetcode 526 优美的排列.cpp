/*
假设有从 1 到 n 的 n 个整数。用这些整数构造一个数组 perm（下标从 1 开始），
只要满足下述条件 之一 ，该数组就是一个 优美的排列 ：
perm[i] 能够被 i 整除
i 能够被 perm[i] 整除
给你一个整数 n ，返回可以构造的 优美排列 的 数量 。
链接：https://leetcode-cn.com/problems/beautiful-arrangement
*/
//状压dp 复杂度O(1<<n -1) 前面的排列不同,但是组合的状态相同,但是未选取的数 存在重叠子问题 存在最优子结构,因此状压dp
class Solution {
public:
    int a[16],dp[32768],ans;
    int dfs(int n,int k,int sta){
        if(sta == (1<<n)-1)
            return dp[sta]=1;
        if(dp[sta])
            return dp[sta];
        for(int i=1;i<=n;i++){
            if(sta & (1<<(i-1)))
                continue;
            a[k]=i;
            if(a[k]%k == 0 || k%a[k] == 0)
                dp[sta]+=dfs(n,k+1,sta|1<<(i-1));
        }
        return dp[sta];
    }
    int countArrangement(int n) {
        return dfs(n,1,0);
    }
};

//枚举全排列+剪枝 复杂度O(n!)
// class Solution {
// public:
//     int a[16],ans;
//     void dfs(int n,int k,int sta){
//         if(k == n+1){
//             ans++;
//             return;
//         }
//         for(int i=1;i<=n;i++){
//             if(sta & (1<<i))
//                 continue;
//             a[k]=i;
//             if(a[k]%k == 0 || k%a[k] == 0)
//                 dfs(n,k+1,sta|1<<i);
//         }
//     }
//     int countArrangement(int n) {
//         dfs(n,1,0);
//         return ans;
//     }
// };
