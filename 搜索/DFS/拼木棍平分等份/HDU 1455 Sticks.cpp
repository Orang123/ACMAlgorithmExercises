/*
题意:
乔治拿来一组等长的木棒，将它们随机的砍掉，得到若干根小木棍，
并使每一节小棍的长度都不超过50个单位。然后他又想把这些木棍
拼接起来，恢复到裁剪前的状态，但他忘记了初始时有多少木棒以
及木棒的初始长度。请你设计一个程序，帮助乔治计算木棒的可能
最小长度，每一节木棍的长度都用大于零的整数表示。
输入包含多组数据，每组数据包括两行。第一行是一个不超过64的整数，
表示砍断之后具有多少节木棍。第二行是截断以后，所得到的各节木棍的长度。
在最后一组数据之后。是一个零。
对于每组数据，分别输出原始木棒的可能最小长度。
木棍个数<=64,初始木棍长度<=50.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1455
https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=9
思路:首先最小长度的下界是n个木棍中最长的,然后依次线性递增枚举木棍的
长度len,计算出要拼成的木棍数量num=tot/len.看是否能将n个木棍恰好拼成
num个长度为len的木棍.此外在枚举时,要先排序 降序枚举,这样会使dfs效率更快,
先加较大的木棍相比先加较小的木棍,搜索树递归分支减小.枚举时对于同一根要凑
的len的木棍,段内是组合问题,而不同根长度为len的木棍之间是排列问题.
有4个剪枝.如下代码.
*/
//ac 0ms dfs for循环线性枚举每个木棍是否选取
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
using namespace std;

int n,a[N],vis[N],tot,len,num;

int dfs(int pos,int sum,int k){
    //剪枝1:已经凑够num-1个了,剩下的一定能拼成成长度为len的木棍
    if(k == num-1)
        return 1;
    for(int i=pos;i<=n;i++){
        if(vis[i])
            continue;
        vis[i]=1;
        //实际是对于同一根拼成的木棍len段内是组合问题,而对于不同根要凑的长度为len的木棍来说是排列问题.
        if(sum+a[i]<len){
            if(dfs(i+1,sum+a[i],k))//一根还未凑成,接着当前i+1枚举后面的凑
                return 1;
        }
        else if(sum+a[i] == len){//已经凑成一根了,枚举下标从头开始枚举
            if(dfs(1,0,k+1))
                return 1;
        }
        vis[i]=0;
        //剪枝2:如果上次是从初始长度为0开始拼凑还没拼出num个,则返回
        //剪枝3:如果上次恰好拼成的长度为len,还不能拼出num个木棍,则返回.
        //对于剪枝2、3实际可以这么理解,本身凑整的不行,而当前的a[i]是较大不用来拼凑的,
        //而选择后面的a[i+1]、a[i+2]来拼凑,那么对于剩下的木棍对于a[i]这个较大的,
        //只会更难凑成一个整的len,因为少了之前较小的长度的木棍已经被选了. 这两种情况都会导致重复搜索
        if(!sum || sum+a[i] == len)//不加这个剪枝会TLE
            return 0;
        //剪枝4:如果下一个木棍和当前失败的木棍长度相同,则不必重复枚举.
        while(i+1<=n && a[i] == a[i+1])
            i++;
    }
    return 0;
}

int main(){
    while(scanf("%d",&n) && n){
        tot=0;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            tot+=a[i];
        }
        //降序枚举 不排序124ms(要加剪枝),这样能较早dfs搜索到满足情况的方案
        //否则从小到达,所有小的拼成len,大的木棍就不容易拼成len了,这样dfs搜索的深度就加深了,复杂度就加大
        sort(a+1,a+1+n,greater<int>());
        for(int i=a[1];;i++){
            if(tot%i == 0){//必须能整除当前长度i
                len=i;
                num=tot/i;
                if(dfs(1,0,0)){
                    printf("%d\n",i);
                    break;
                }
            }
        }
    }
    return 0;
}

/*
//ac 0ms dfs枚举每个木棍是否选取
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
using namespace std;

int n,a[N],vis[N],tot,len,num;

int dfs(int i,int sum,int k){
    if(k == num)
        return 1;
    if(i == n+1)
    	return 0;
    if(!vis[i]){
    	vis[i]=1;
    	if(sum+a[i]<len){
    		if(dfs(i+1,sum+a[i],k))
    			return 1;
		}
		else if(sum+a[i] == len){
    		if(dfs(1,0,k+1))
    			return 1;
		}
		vis[i]=0;
		if(!sum || sum+a[i] == len)
            return 0;
        //这个要放在if内,放在if外,要判断a[i]是否刚枚举过,只有刚枚举过才能i++ 去重,否则会出错
		while(i+1<=n && a[i] == a[i+1])
			i++;
	}
	if(dfs(i+1,sum,k))
		return 1;
    return 0;
}

int main(){
    while(scanf("%d",&n) && n){
        tot=0;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            tot+=a[i];
        }
        sort(a+1,a+1+n,greater<int>());
        for(int i=a[1];;i++){
            if(tot%i == 0){
                len=i;
                num=tot/i;
                if(dfs(1,0,0)){
                    printf("%d\n",i);
                    break;
                }
            }
        }
    }
    return 0;
}
*/

/*
leetcode 698. 划分为k个相等的子集
链接:https://leetcode-cn.com/problems/partition-to-k-equal-sum-subsets/
给定一个整数数组  nums 和一个正整数 k，找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。
//状压dp
class Solution {
public:
    int dp[65536],len;
    int dfs(vector<int>& nums,int k,int sum,int sta){
        if(k == 1)
            return 1;
        if(dp[sta]!=-1)
            return dp[sta];
        dp[sta]=0;
        for(int i=0;i<nums.size();i++){//状压dp为了表示状态的唯一性,这里每层dfs int i的起点需要都是相同的
            if(sta & (1<<i))
                continue;
            if(sum+nums[i]<len){
                if(dfs(nums,k,sum+nums[i],sta|1<<i))
                    return 1;
            }
            else if(sum+nums[i] == len){
                if(dfs(nums,k-1,0,sta|1<<i))
                    return 1;
            }
            if(!sum || sum+nums[i] == len)
                return 0;
            while(i+1<nums.size() && nums[i] == nums[i+1])
                i++;
        }
        return 0;
    }
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end(),greater<int>());
        int sum=0;
        for(auto &val : nums)
            sum+=val;
        if(sum%k)
            return false;
        len=sum/k;
        for(auto &val : nums){
            if(val>len)//如果某个长度比len还长 则肯定分不出
                return false;
        }
        memset(dp,-1,sizeof(dp));
        return dfs(nums,k,0,0);
    }
};

//回溯+剪枝
// class Solution {
// public:
//     int len;
//     int dfs(vector<int>& nums,int k,int st,int sum,int sta){
//         if(k == 1)
//             return 1;
//         for(int i=st;i<nums.size();i++){
//             if(sta & (1<<i))
//                 continue;
//             if(sum+nums[i]<len){
//                 if(dfs(nums,k,i+1,sum+nums[i],sta|1<<i))
//                     return 1;
//             }
//             else if(sum+nums[i] == len){
//                 if(dfs(nums,k-1,0,0,sta|1<<i))
//                     return 1;
//             }
//             if(!sum || sum+nums[i] == len)
//                 return 0;
//             while(i+1<nums.size() && nums[i] == nums[i+1])
//                 i++;
//         }
//         return 0;
//     }
//     bool canPartitionKSubsets(vector<int>& nums, int k) {
//         sort(nums.begin(),nums.end(),greater<int>());
//         int sum=0;
//         for(auto &val : nums)
//             sum+=val;
//         if(sum%k)
//             return false;
//         len=sum/k;
//         for(auto &val : nums){
//             if(val>len)//如果某个长度比len还长 则肯定分不出
//                 return false;
//         }
//         return dfs(nums,k,0,0,0);
//     }
// };
*/
