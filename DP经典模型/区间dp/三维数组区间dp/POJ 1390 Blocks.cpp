#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;


/*
题意:给你一排颜色块，每次可以删除相邻的相同颜色块，本次的积分为数量的平方
问将所有的颜色块序列删除完,最大积分是多少？
原题是一道OI原题 祖玛
链接:http://poj.org/problem?id=1390
思路:可以初步统计出所有相邻相同颜色块的数目,dp[i][j][k],i~j之间都是颜色一样的颜色块,
k表示j之后又几个颜色块与j块的颜色相同,可以一起等中间的消除后,再统一消除j和后面的相同颜色块.
当然dp[i][j][k]的k也可以代表和i和左边块相同颜色的数目去求解

这个问题只能拿记忆化搜索递归解决,正向的dp 因为对于第三维的k从小的开始转移大的区间,k是不确定的,
若是考虑二维数组转移,小的区间的最优解实质不能涵盖更左端和更右端有没有相同颜色得到块,解也是有问题的.
*/
int dp[210][210][210],a[210],col[210],num[210],n;

int cal(int x){
    return x*x;
}

int dfs(int i,int j,int k){
    if(dp[i][j][k]) return dp[i][j][k];
    if(i == j) return dp[i][j][k]=cal(num[j]+k);//剩下一个颜色时算上这个块的数目和右边相同颜色块的数目一起删除
    //if(i>j) return 0;因为相邻的两个块颜色永远都不同 所以不可能出现t=j-1时 进入这个递归dfs(t+1,j-1) 导致i>j
    //直接先将j的颜色块和后面的k个相同颜色块删除
    dp[i][j][k]=dfs(i,j-1,0)+cal(num[j]+k);
    //考虑i~j-2中是否有和j颜色相同块,若有,可以先将t+1~j-1中间的块删除,再一起删除两边的相同颜色的块
    for(int t=i;t<j-1;t++)//<j-1是因为 j-1和j颜色时肯定不同的
        if(col[t] == col[j])
            dp[i][j][k]=max(dp[i][j][k],dfs(i,t,k+num[j])+dfs(t+1,j-1,0));
    return dp[i][j][k];
}

int main(){
    int T,tmp,len,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        memset(num,0,sizeof(num));
        scanf("%d",&n);
        len=0;
        tmp=-1;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            if(a[i]!=tmp){
                tmp=col[++len]=a[i];//num记录相邻块相同颜色的数目
                num[len]++;
            }
            else
                num[len]++;
        }
        printf("Case %d: %d\n",cas,dfs(1,len,0));
    }
    return 0;
}
