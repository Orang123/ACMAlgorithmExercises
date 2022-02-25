/*
题意:摘自网上
Alice和Bob玩一个游戏，有两个长度为N的正整数数字序列，每次他们两个
仅仅能从当中一个序列，选择两端中的一个拿走。他们都希望能够拿到尽量大
的数字之和，而且他们都足够聪明。每次都选择最优策略。Alice先选择，问
终于Alice拿到的数字总和是多少？
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4597
思路:博弈+记忆化搜索
第二个样例 没太看懂,为啥是105,为啥不是130,对于"他们都希望能够拿到尽量大
的数字之和",这句话如何理解,此题主要难在博弈,记忆化搜索重叠子问题 很简单能
想到.
*/
//我自己写的代码 只能求出最大的分数,但是和题意描述不符,没理解对于"他们都希望能够拿到尽量大的数字之和"
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
using namespace std;

//dp[l1s][l1d][l2s][l2d]表示 第一堆取[l1s,l1d] 第二堆去[l2s,l2d]中Alice能获得的最大分数
int n,a[N],b[N],dp[N][N][N][N];

int dfs(int l1s,int l1d,int l2s,int l2d,int k){
    if(l1s>l1d && l2s>l2d)
        return 0;
    if(dp[l1s][l1d][l2s][l2d])
        return dp[l1s][l1d][l2s][l2d];
    int res=0;
    if(k){
        if(l1s<=l1d){
            res=max(res,a[l1s]+dfs(l1s+1,l1d,l2s,l2d,!k));
            res=max(res,a[l1d]+dfs(l1s,l1d-1,l2s,l2d,!k));
        }
        if(l2s<=l2d){
            res=max(res,b[l2s]+dfs(l1s,l1d,l2s+1,l2d,!k));
            res=max(res,b[l2d]+dfs(l1s,l1d,l2s,l2d-1,!k));
        }
    }
    else{
        if(l1s<=l1d){
            res=max(res,dfs(l1s+1,l1d,l2s,l2d,!k));
            res=max(res,dfs(l1s,l1d-1,l2s,l2d,!k));
        }
        if(l2s<=l2d){
            res=max(res,dfs(l1s,l1d,l2s+1,l2d,!k));
            res=max(res,dfs(l1s,l1d,l2s,l2d-1,!k));
        }
    }
    return dp[l1s][l1d][l2s][l2d]=res;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&b[i]);
        printf("%d\n",dfs(1,n,1,n,1));
    }
    return 0;
}

/*
//摘自博客:https://blog.csdn.net/imzxww/article/details/76598668
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int dp[25][25][25][25],a[25],b[25];
int dfs(int x1,int y1,int x2,int y2,int sum)
{
    int maxn=0;
    if(x1>y1&&x2>y2)return 0;
    if(dp[x1][y1][x2][y2])return dp[x1][y1][x2][y2];
    if(x1<=y1)
    {
        maxn=max(maxn,sum-dfs(x1+1,y1,x2,y2,sum-a[x1]));
        maxn=max(maxn,sum-dfs(x1,y1-1,x2,y2,sum-a[y1]));
    }
    if(x2<=y2)
    {
        maxn=max(maxn,sum-dfs(x1,y1,x2+1,y2,sum-b[x2]));
        maxn=max(maxn,sum-dfs(x1,y1,x2,y2-1,sum-b[y2]));
    }
    dp[x1][y1][x2][y2]=maxn;
    return maxn;
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n;
        scanf("%d",&n);
        memset(dp,0,sizeof(dp));
        int i;
        int sum=0;
        for(i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            sum+=a[i];
        }
        for(i=1;i<=n;i++)
        {
            scanf("%d",&b[i]);
            sum+=b[i];
        }
        int z=dfs(1,n,1,n,sum);
        cout<<z<<endl;
    }
    return 0;
}
*/
