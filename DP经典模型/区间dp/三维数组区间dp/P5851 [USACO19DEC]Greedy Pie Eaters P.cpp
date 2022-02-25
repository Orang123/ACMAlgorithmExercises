#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

/*
链接:https://www.luogu.com.cn/problem/P5851
思路:dp[i][j]代i~j的派别吃掉能得到的牛的体重最大值
w[i][j][k]代表在[i,j]内编号为k的派还没被吃,可以吃的牛的最大体重
*/

int dp[310][310],w[310][310][310],w0,n,m;

int main(){
    int l,r;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&w0,&l,&r);
        for(int j=l;j<=r;j++)
            w[l][r][j]=w0;
    }
    for(int k=1;k<=n;k++){
        for(int i=k;i>=1;i--){
            for(int j=k;j<=n;j++){
                if(i!=1)
                    w[i-1][j][k]=max(w[i][j][k],w[i-1][j][k]);//计算出吃的更大范围内 对于每个k派所能选择的最大牛体重
                if(j!=n)
                    w[i][j+1][k]=max(w[i][j][k],w[i][j+1][k]);
            }
        }
    }
    for(int l0=0;l0<n;l0++){
        for(int i=1;i+l0<=n;i++){
            int j=i+l0;
            for(int k=i;k<=j;k++)
                dp[i][j]=max(dp[i][j],max(dp[i][k]+dp[k+1][j],dp[i][k-1]+w[i][j][k]+dp[k+1][j]));
        }
    }
    printf("%d",dp[1][n]);
    return 0;
}
