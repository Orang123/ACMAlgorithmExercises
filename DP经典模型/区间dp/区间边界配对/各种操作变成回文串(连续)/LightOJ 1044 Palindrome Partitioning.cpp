/*
题意:摘自网上
将一个字符串分割成最少的字符串，使得分割出的每个字符串都是回文串。输出最小的分割数。
字符串长度<=1000s.
链接:http://lightoj.com/volume_showproblem.php?problem=1044
思路:对于[l,r]内的字符串,枚举区间分割的方式,那么实际分割的回文串的
最优子结构为[l,r]=[l,i]+[i+1,r],因此dp[l][r]为区间[l,r]内可以分割的
最少的回文串的数目.
状态转移方程为if(check(l,i))([l,i]是回文串)
dp[l][r]=min(dp[l][r],1+dfs(i+1,r));
*/
//ac 151ms 记忆化搜索 区间dp
//dp[l][r]为区间[l,r]内可以分割的最少的回文串的数目.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int dp[N][N],len;
char str[N];

int check(int l,int r){//判断[l,r]是否为回文串
    while(l<r){
        if(str[l] == str[r]){
            l++;
            r--;
        }
        else
            return 0;
    }
    return 1;
}

int dfs(int l,int r){
    int &res=dp[l][r];
    if(res!=INF)
        return res;
    if(l>r)//结束
        return res=0;
    for(int i=l;i<=r;i++){
        if(check(l,i))//[l,i]是回文串 回文串数目+1
            res=min(res,1+dfs(i+1,r));
    }
    return res;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        memset(dp,0x3f,sizeof(dp));
        scanf("%s",str+1);
        len=strlen(str+1);
        printf("Case %d: %d\n",i,dfs(1,len));
    }
    return 0;
}

/*
//ac 正向dp
//摘自博客:https://blog.csdn.net/u011026037/article/details/23872821
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int dp[1005];
char str[1005];
bool find(int k,int r)
{
    while(k < r)
    {
        if(str[k] == str[r])  k++,r--;
        else  return false;
    }
    return true;
}
int main()
{
    int n,Case = 1;;
    scanf("%d",&n);
    getchar();
    while(n--)
    {
        scanf("%s",str);
        int l = strlen(str);
        for(int i = 0; i < l; i++)
        {
            dp[i] = i + 1;
            for(int j = 0; j <= i; j++)
            {
                if(find(j,i))
                {
                    if(j == 0)
                        dp[i] = 1;
                    else
                        dp[i] = min(dp[i],dp[j - 1] + 1);
                }
            }
        }
        printf("Case %d: %d\n",Case++,dp[l-1]);
    }
}
*/

/*
//TLE dp[l][r]=min(dp[l][r],dfs(l,i)+dfs(i+1,r))
//之所以TLE可能是 这个最优子结构 有2个dfs,都会产生重叠子问题,而len最大可达1000
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int dp[N][N],vis[N][N],len;
char str[N];

int dfs(int l,int r){
    int &res=dp[l][r];
    if(res!=INF)
        return res;
    if(vis[l][r])
        return res=1;
    if(l>r)
        return res=0;
    for(int i=l;i<=r;i++)
        res=min(res,dfs(l,i)+dfs(i+1,r));
    return res;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int i=1;i<=T;i++){
        memset(vis,0,sizeof(vis));
        memset(dp,0x3f,sizeof(dp));
        scanf("%s",str+1);
        len=strlen(str+1);
        for(int i=1;i<=len;i++){
            vis[i][i]=1;
            for(int l=i,r=i+1;l>=1 && r<=len;l--,r++){//判断偶数长度回文串
                if(str[l] == str[r])
                    vis[l][r]=1;
                else
                    break;
            }
            for(int l=i-1,r=i+1;l>=1 && r<=len;l--,r++){//判断奇数长度回文串
                if(str[l] == str[r])
                    vis[l][r]=1;
                else
                    break;
            }
        }
        printf("Case %d: %d\n",i,dfs(1,len));
    }
    return 0;
}
*/
