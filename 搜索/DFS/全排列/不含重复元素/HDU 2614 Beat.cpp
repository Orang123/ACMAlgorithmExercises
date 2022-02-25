/*
题意:摘自网上
小A喜欢挑战难题，给你一个n*n的矩阵 ，a[i][j]，表示在做过第i题后去做j题，
将花费a[i][j]的时间，每次他选择j题目花费时间>=i的花费时间。
求出小A能解决的最大问题数.
n<15.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2614
思路:dfs暴力回溯
*/
//ac 46ms dfs回溯
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
using namespace std;

int n,a[N][N],vis[N],ans;

void dfs(int k,int num,int time){
    if(num>ans)
        ans=num;
    for(int i=0;i<n;i++){
        if(vis[i] || a[k][i]<time)
            continue;
        vis[i]=1;
        dfs(i,num+1,a[k][i]);
        vis[i]=0;
    }
}

int main(){
    while(scanf("%d",&n)!=EOF){
        ans=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                scanf("%d",&a[i][j]);
        }
        vis[0]=1;
        dfs(0,1,0);
        vis[0]=0;
        printf("%d\n",ans);
    }
    return 0;
}
