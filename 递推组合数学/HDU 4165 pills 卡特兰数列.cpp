#include<cstdio>
__int64 dp[61][61];//数组长度开到
void init(){
    for(int i=0;i<61;i++)
        dp[i][0]=1;
    for(int i=1;i<61;i++){
        for(int j=1;j<=i;j++){
            dp[i][j]=dp[i-1][j-1]+dp[i-1][j];
        }
    }
}
int main(){
    int n;
    init();
    while(scanf("%d",&n)&&n)
        printf("%I64d\n",dp[n<<1][n]-dp[n<<1][n+1]);//卡特兰数 可采用组合数差值的方式计算:f(n)=C[2n][n]-C[2n][n+1]
    return 0;
}
