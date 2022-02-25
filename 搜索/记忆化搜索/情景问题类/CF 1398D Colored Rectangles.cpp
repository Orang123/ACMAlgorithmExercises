/*
题意:摘自网上
给出R对红色木棍,G对绿色木棍,B对蓝色木棍的长度r[i]、g[i]、b[i],
每次可以选出两对颜色不同的木棍对边颜色相同,邻边颜色不同组成一个矩形,
每对木棍只能使用一次,木棍可以有剩余.请最大化所有组成的矩形的面积.
R,G,B<=200
链接:https://codeforces.com/contest/1398/problem/D
思路:首先要尽可能要大的边和大的边组合在一起 面积才能最大,这是个贪心的思路.
因此对三种颜色的木棍长度降序排序,枚举优先选择长度较大的木棍去组合,但是对于
剩余木棍在枚举的过程中会产生重叠子问题,因此记忆化搜索,结束条件是三种木棍个数
为0或只剩下1个木棍无法组成矩形.结束状态是不确定的.
dp[i][j][k]表示在红色木棍剩下i对,绿色木棍剩下j对,蓝色木棍剩下k对时,所能组成的
矩形的最大面积.
*/
//ac 77ms 记忆化搜索
//dp[i][j][k]表示在红色木棍剩下i对,绿色木棍剩下j对,蓝色木棍剩下k对时,所能组成的
//矩形的最大面积.
//时间复杂度O(200*200*200)=8*10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
using namespace std;

int R,G,B,r[N],g[N],b[N],dp[N][N][N];

int dfs(int ri,int gi,int bi){
    int &res=dp[ri][gi][bi];
    if(res)
        return res;
    if(ri && gi)
        res=max(res,r[ri]*g[gi]+dfs(ri-1,gi-1,bi));
    if(ri && bi)
        res=max(res,r[ri]*b[bi]+dfs(ri-1,gi,bi-1));
    if(gi && bi)
        res=max(res,g[gi]*b[bi]+dfs(ri,gi-1,bi-1));
    return res;//结束条件是res=0,就是剩下木棍无法再组成矩形
}

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d",&R,&G,&B);
    for(int i=1;i<=R;i++)
        scanf("%d",&r[i]);
    for(int i=1;i<=G;i++)
        scanf("%d",&g[i]);
    for(int i=1;i<=B;i++)
        scanf("%d",&b[i]);
    sort(r+1,r+1+R);
    sort(g+1,g+1+G);
    sort(b+1,b+1+B);
    printf("%d",dfs(R,G,B));
    return 0;
}
