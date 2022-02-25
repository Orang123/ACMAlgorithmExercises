/*
题意:摘自网上
要求写一个函数 w( a, b, c) 处理输入数据（多测试）；
①如果 a < 0 || b < 0 || c < 0；直接返回w( a, b, c )；
②如果 a > 20 || b > 20 || c > 20；返回w( 20, 20, 20 )；
③如果 a < b && b < c ；返回 w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c)；
④ 其他情况返回w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1) ；
链接:http://poj.org/problem?id=1579
思路:通过题意:
w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c)
和
w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1)
可以看出递归函数有很多重叠子问题在重复计算,因此需要对重叠子问题w(a,b,c)
用dp[a][b][c]来标记.
*/
//ac 0ms 记忆化搜索
#include<cstdio>
#include<cstring>
int dp[30][30][30];
int dfs(int a,int b,int c){
    if(a<=0||b<=0||c<=0)
        return 1;
    if(a>20||b>20||c>20)
        return dfs(20,20,20);
    if(dp[a][b][c])//不是很清楚这里为什么一定要放置在第三个if里才能计算出50 50 50 的样例,应该是只对abc<20的情况记忆化
        return dp[a][b][c];
    if(a<b&&b<c)
        return dp[a][b][c]=dfs(a,b,c-1)+dfs(a,b-1,c-1)-dfs(a,b-1,c);
    else
        return dp[a][b][c]=dfs(a-1,b,c)+dfs(a-1,b-1,c)+dfs(a-1,b,c-1)-dfs(a-1,b-1,c-1);
}

int main(){
    int a,b,c;
    while(scanf("%d%d%d",&a,&b,&c)&&(a!=-1||b!=-1||c!=-1)){
        memset(dp,0,sizeof(dp));
        printf("w(%d, %d, %d) = %d\n",a,b,c,dfs(a,b,c));
    }
    return 0;
}
