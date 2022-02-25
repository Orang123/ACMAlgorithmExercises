/*
对应例题:leetcode 5 最长回文子串
给你一个字符串 s，找到 s 中最长的回文子串。
https://leetcode-cn.com/problems/longest-palindromic-substring/
*/

//这些做法是O(n^2)的做法,实际最长回文子串可以用manacher算法在O(n)线性时间内解决
#include<cstdio>//最长回文子串
#include<cstring>
#include<algorithm>
using namespace std;
int vis[1100][1100];
char a[1100];
//时间复杂度度O(N^2) 空间O(N^2) 1s以内 n>1000后可能就会TLE,2000以上的数据 感觉只能用Manacher(时间:O(N)空间:O(N))算法,超过4000vis数组也会TLE
int main(){
    int lt=1,rt=1,len;//如果最坏情况下,字符串中每个字符都不相同,则默认输出第一个字符作为长度为1的回文子串
    scanf("%s",a+1);
    len=strlen(a+1);
    for(int i=1;i<=len;i++)
        vis[i][i]=1;
    //先统计较小的区间的回文子串,再根据区间左右端点统计较大区间是否为回文串
    for(int l=1;l<len;l++){//O(N^2)
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            //前提是[i,j] 中间的[i+1,j-1]必须为回文串,[i,j]才可能是 区间长度为2时不存在中间子串
            if(a[i]==a[j] && (l==1 || vis[i+1][j-1])){//随着区间长度增大,记录更大长度的回文子串
                lt=i,rt=j;
                vis[i][j]=1;
            }
        }
    }
    printf("%d\n",rt-lt+1);
    for(int i=lt;i<=rt;i++)//这里答案若不唯一  输出的是下标序列较靠后的最长回文子串
        printf("%c",a[i]);
    return 0;
}

/*
同样可采用枚举左右端点dp使用滚动数组优化空间
*/

/*
O(N^3) 最原始的暴力做法,枚举每一个起点,再枚举起点开始的可能长度的子串,对每个子串正向和逆向对比判定,不断更新最大长度
*/

/*
区间dp做法可做离线区间查询,dp[i][j]表示[i,j]内最长回文子串的长度
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110],vis[110][110];//vis[i][j]代表[i,j]的字符串是否是回文串,若是为1
char a[110];
//时间复杂度O(N^2) 1s内数据最大为1000
int main(){
    int len;
    scanf("%s",a+1);
    len=strlen(a+1);
    for(int i=1;i<=len;i++)
        vis[i][i]=dp[i][i]=1;
    for(int l=1;l<len;l++){
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            //[i,j]为回文串的前提条件是[i+1,j-1]必须为回文串
            if(a[i] == a[j] && (l==1 || vis[i+1][j-1])){//[i,j]长度为2时没有中间的字符串无需判断 即l==1
                dp[i][j]=dp[i+1][j-1]+2;//[i,j]在[i+1,j-1]的基础上增加2
                vis[i][j]=1;//标记更大的回文串区间
            }
            //若a[i]!=a[j]或[i+1,j-1]不是回文,那么[i,j]的最长回文继承之前小区间[i,j-1]和[i+1,j]较大的长度
            else dp[i][j]=max(dp[i][j-1],dp[i+1][j]);
        }
    }
    printf("%d",dp[1][len]);//dp[i][j]代表任意区间[i,j]之间的最长回文子串的长度 对于给定一个字符串 输入不同左右端点 做离线输出答案有优势
    return 0;
}
*/

/*
//记忆化搜索 最长回文子串
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110],vis[110][110];
char a[110];

int dfs(int i,int j){
    if(i>j) return 0;
    if(dp[i][j]) return dp[i][j];
    dfs(i+1,j-1);//要根据a[i]和a[j]关系判断[i,j]是否为回文串,先得判断[i+1,j-1]是否为回文串
    if(a[i] == a[j] && (j-i==1 || vis[i+1][j-1])){//长度为2时没有中间子串
        dp[i][j]=dp[i+1][j-1]+2;
        vis[i][j]=1;
    }
    else
        dp[i][j]=max(dfs(i,j-1),dfs(i+1,j));
    return dp[i][j];
}

int main(){
    int len;
    scanf("%s",a+1);
    len=strlen(a+1);
    for(int i=1;i<=len;i++)
        dp[i][i]=vis[i][i]=1;
    printf("%d",dfs(1,len));
    return 0;
}
*/

/*
leetcode 647 统计回文子串的数目
链接:https://leetcode-cn.com/problems/palindromic-substrings/
//区间dp
//时间复杂度O(n^2) 空间复杂度O(n^2)
class Solution {
public:
    int dp[1100][1100];
    int countSubstrings(string s) {
        int ans=0;
        for(int l=0;l<s.size();l++){
            for(int i=0;i+l<s.size();i++){
                int j=i+l;
                if(s[i] == s[j] && (i+1>=j-1 || dp[i+1][j-1])){
                    dp[i][j]=1;
                    ans++;
                }
            }
        }
        return ans;
    }
};

//中心扩展法 双指针
//时间复杂度O(n^2) 空间复杂度O(1)
class Solution {
public:
    int ans;

    void cal(string &s,int l,int r){
        while(l>=0 && r<s.size() && s[l] == s[r]){
            l--;
            r++;
            ans++;
        }
    }

    int countSubstrings(string s) {
        for(int i=0;i<s.size();i++){
            cal(s,i,i+1);//长度为偶数 从s[i] == s[i+1]开始向外扩展
            cal(s,i,i);//长度为奇数 对称中心位s[i]
        }
        return ans;
    }
};
*/

