/*
题意:我们将给定的数组 A 分成 K 个相邻的非空子数组 ，
我们的分数由每个子数组内的平均值的总和构成。计算我们所能得到的最大分数是多少。
注意我们必须使用 A 数组中的每一个数进行分组，并且分数不一定需要是整数。
链接：https://leetcode-cn.com/problems/largest-sum-of-averages
1 <= A.length <= 100.
1 <= A[i] <= 10000.
1 <= K <= A.length.
答案误差在 10^-6 内被视为是正确的。
*/
//记忆化搜索 8ms 复杂度O(n*k)
#define INF -1e18
class Solution {
public:
    int n;
    //dp[st][k]表示数组范围[st,n]分成k个部分各个部分平均值最大和
    double dp[110][110],presum[110];
    double dfs(int st,int k){
        if(st == n+1){//已经将数组分完
            if(!k)//恰好分成了k个部分 是合法状态
                return 0;
            return INF;//还未分够k个部分 不是合法状态
        }
        if(!k)//已经分够k个部分 但是数组没有完全分完 不是合法状态
            return INF;
        double &ans=dp[st][k];
        if(ans)//初始状态为0 INF不合法状态也是需要记录的
            return ans;
        ans=INF;//默认不合法状态为INF -1e18
          //当前部分枚举分割的范围
        for(int i=st;i<=n;i++)//当前部分分成[st,i],其平均值为(presum[i]-presum[st-1])/(i-st+1)
            ans=max(ans,(presum[i]-presum[st-1])/(i-st+1)+dfs(i+1,k-1));
        return ans;
    }
    double largestSumOfAverages(vector<int>& nums, int k) {
        n=nums.size();
        for(int i=1;i<=n;i++)
            presum[i]=presum[i-1]+nums[i-1];//计算前缀和
        return dfs(1,k);
    }
};

/*
//记忆化搜索 8ms
#define INF -1e18
class Solution {
public:
    int n;
    //dp[st][k]表示数组范围[st,n]分成k个部分各个部分平均值最大和
    //sum[i][j]表示[i,j]内元素累加和
    double dp[110][110],sum[110][110];
    double dfs(int st,int k){
        if(k == 1)//结束状态 只剩下一个部分时,[st,n]整体作为一个部分
            return sum[st][n]/(n-st+1);
        if(st == n+1)//没有分够k个部分 但是数组已经分完了 不合法状态
            return INF;
        double &ans=dp[st][k];
        if(ans)//初始状态为0 INF不合法状态也是需要记录的
            return ans;
        ans=INF;//默认不合法状态为INF -1e18
        //当前部分枚举分割的范围
        for(int i=st;i<=n;i++)//当前部分分成[st,i],其平均值为sum[st][i]
            ans=max(ans,sum[st][i]/(i-st+1)+dfs(i+1,k-1));
        return ans;
    }
    double largestSumOfAverages(vector<int>& nums, int k) {
        n=nums.size();
        for(int i=1;i<=n;i++)
            for(int j=i;j<=n;j++)
                sum[i][j]=sum[i][j-1]+nums[j-1];//不能在这里除以(j-i+1)算平均值,会有舍入误差
        return dfs(1,k);
    }
};
*/

/*
//正向dp
class Solution {
public:
    //dp[st][k]表示数组范围前st个数[1,st]分成k个部分各个部分平均值最大和
    double dp[110][110],presum[110];
    double largestSumOfAverages(vector<int>& nums, int k) {
        int n=nums.size();
        for(int i=1;i<=n;i++){
            presum[i]=presum[i-1]+nums[i-1];//计算前缀和
            dp[i][1]=presum[i]/i;//初始状态是dp[i][1]前i个数分成1部分
        }
        for(int t=2;t<=k;t++){//t从2开始,保证dp[j-1][t-1]至少是分了一部分,如果从1开始会导致dp[j-1][t-1]j不为0,但是t-1为0,即:前j-1个数分成了0部分 不符合实际意义
            for(int i=t;i<=n;i++){//前i个数分成t部分至少需要t个数
                for(int j=t;j<=i;j++)//枚举[j,i]分成第t部分,那么前j-1个数要能分成t-1个部分即j-1>=t-1,即j>=t,j的下界为t
                    dp[i][t]=max(dp[i][t],dp[j-1][t-1]+(presum[i]-presum[j-1])/(i-j+1));
            }
        }
        return dp[n][k];
    }
};
*/

/*
//正向dp
#define INF -1e18
class Solution {
public:
    //dp[st][k]表示数组范围前st个数[1,st]分成k个部分各个部分平均值最大和
    double dp[110][110],presum[110];
    double largestSumOfAverages(vector<int>& nums, int k) {
        int n=nums.size();
        for(int i=1;i<=n;i++){
            presum[i]=presum[i-1]+nums[i-1];//计算前缀和
            dp[i][1]=presum[i]/i;//初始状态
        }
        for(int i=1;i<=n;i++){
            //t从2开始保证 不会出现dp[j-1][t-1]=dp[3][0]没有实际意义
            for(int t=2;t<=min(i,k);t++){//前i个数最多分成min(i,k)部分
                for(int j=t;j<=i;j++)//前j-1个分成t-1部分,至少需要t-1个数,j的下界是t
                    dp[i][t]=max(dp[i][t],dp[j-1][t-1]+(presum[i]-presum[j-1])/(i-j+1));
            }
        }
        return dp[n][k];
    }
};
*/
