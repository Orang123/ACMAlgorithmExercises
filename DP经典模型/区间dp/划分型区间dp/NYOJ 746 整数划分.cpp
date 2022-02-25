/*
链接:http://nyoj.top/problem/746,http://acm.nyist.net/JudgeOnline/status.php?pid=746
整数划分
时间限制：1000 ms  |  内存限制：65535 KB
难度：3

描述
暑假来了，hrdv 又要留学校在参加ACM集训了，集训的生活非常Happy（ps：你懂得），可是他最近遇到了一个难题，
让他百思不得其解，他非常郁闷。亲爱的你能帮帮他吗？
问题是我们经常见到的整数划分，给出两个整数 n , m ,要求在 n 中加入m - 1 个乘号，将n分成m段，求出这m段的最大乘积

输入
第一行是一个整数T，表示有T组测试数据
接下来T行，每行有两个正整数 n，m ( 1<= n < 10^19, 0 < m <= n的位数)；

输出
输出每组测试样例结果为一个整数占一行

样例输入
2
111 2
1111 2
样例输出
11
121
*/
/*
num[i][j]记录s[i]~s[j]所代表的的10进制数值
dp[i][j] 代表1到j到加入i个乘号后连乘的最大数值
思路:首先传统的那种暴力枚举 m-1个乘号出现的位置,这个基本没法剪枝,复杂度太大,会TLE.
考虑dp或记忆化搜索.
推荐用记忆化搜索 写起来要容易很多
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll dp[50][50],num[50][50];
char s[50];
int main(){
    int T,m,len;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        memset(num,0,sizeof(num));
        scanf("%s",s+1);
        scanf("%d",&m);
        len=strlen(s+1);
        for(int i=1;i<=len;i++){//初始化num数组和dp[0][i]的值
            for(int j=i;j<=len;j++){
                num[i][j]=num[i][j-1]*10;
                num[i][j]+=s[j]-'0';
            }
            dp[0][i]=num[1][i];//[1,i]不加乘号的数值等于num[1][i]
        }
        /*
        这个题目,因为不管加入几个乘号,计算时都是所有数字都参与计算,所以状态的转移,
        必然不是由小区间到大区间,应该由区间内乘号的个数转移到乘号+1个数的区间,右端点区间长度
        仅仅只是转移过程中一个维度的枚举计算,转移的主要状态量应是乘号个数,不然不太好写dp.
        这里因为本身计算就会涉及到整个区间数字,所以无需枚举区间长度,只需枚举1~j,j这个右端点取
        在哪里.
        */
        //其实加入m-1个乘号,就是分割成m个部分,正向dp可以完全参考 leetcode 813 最大平均值和的分组
        //时间复杂度O(len^3)
        for(int i=1;i<=m-1;i++){//从1开始枚举加入乘号的个数
            for(int j=i+1;j<=len;j++){//枚举区间右端点[1,j],初始右端点为i+1,因为要加入i个乘号至少要有i+1个数
                //for(int k=i+1;k<=j;k++)//[k,j]作为第i部分 前k-1个数分i-1部分,至少需要i个数 即:k-1>=i,k>=i+1,k的下界i+1
                    //dp[i][j]=max(dp[i][j],dp[i-1][k-1]*num[k][j]);
                for(int k=i;k<j;k++)//dp[i-1][k]前k个数加入i-1个乘号,至少需要有i个数,k的下界为i 将[k+1,j]分成第i部分
                    dp[i][j]=max(dp[i][j],dp[i-1][k]*num[k+1][j]);
            }
        }
        printf("%lld\n",dp[m-1][len]);//输出连续len个数字中加入m-1个乘号所得到的最大值
    }
	return 0;
}

/*
//记忆化搜索 dp[st][k]表示在数组[st,len]范围内,添加k-1个乘号即:分成k个部分,所能求出的最大累乘结果
//空间复杂度o(n*m) 时间复杂度O(n^2*m)
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll dp[50][50],num[50][50];
int len,m;
char s[50];

ll dfs(int st,int k){
    if(k == 1)
        return num[st][len];
    if(st == len+1)//没有分够k个部分 但是数组已经分完 不合法状态
        return 0;
    ll &ans=dp[st][k];
    if(ans!=-1)//初始状态为-1
        return ans;
    for(int i=st;i<=len;i++)
        ans=max(ans,num[st][i]*dfs(i+1,k-1));
    return ans;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,-1,sizeof(dp));
        memset(num,0,sizeof(num));
        scanf("%s",s+1);
        scanf("%d",&m);
        len=strlen(s+1);
        for(int i=1;i<=len;i++){
            for(int j=i;j<=len;j++){
                num[i][j]=num[i][j-1]*10;
                num[i][j]+=s[j]-'0';
            }
        }
        printf("%lld\n",dfs(1,m));
    }
	return 0;
}
*/

/*
//记忆化搜索 dp[st][k]表示在数组[st,len]范围内,添加k-1个乘号即:分成k个部分,所能求出的最大累乘结果
//空间复杂度o(n*m) 时间复杂度O(n^2*m)
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
ll dp[50][50],num[50][50];
int len,m;
char s[50];

ll dfs(int st,int k){
    if(st == len+1){
        if(!k)
            return 1;//结束状态 因为累乘为1
        return 0;//不合法状态为0 不能是INF(-0x3f3f3f3f3f3f3f3f),这样会溢出
    }
    if(!k)//已经分成k个部分,但是数组没分为不合法状态
        return 0;
    ll &ans=dp[st][k];
    if(ans!=-1)//初始状态为-1
        return ans;
    for(int i=st;i<=len;i++)
        ans=max(ans,num[st][i]*dfs(i+1,k-1));
    return ans;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,-1,sizeof(dp));
        memset(num,0,sizeof(num));
        scanf("%s",s+1);
        scanf("%d",&m);
        len=strlen(s+1);
        for(int i=1;i<=len;i++){
            for(int j=i;j<=len;j++){
                num[i][j]=num[i][j-1]*10;
                num[i][j]+=s[j]-'0';
            }
        }
        printf("%lld\n",dfs(1,m));
    }
	return 0;
}
*/

