/*
题意:给出一个n,从1到n的不同面值的硬币不限数量有多少方式凑成n,如果又给出一个l1,
代表用小于等于l1数量的从1到n面值的硬币有多少方式凑成n,如果又给了l2代表数量大于
等于l1小于等于l2数量的从1到n面值的硬币有多少种方式组成n.
0<=n<=300,0<=l1,l2<=1001
链接:https://www.luogu.com.cn/problem/UVA10313
思路:二维费用完全背包统计指定数目物品装满背包方案数.
dp[k][j]+=dp[k-1][j-i],升序枚举第二层循环,第三层循环升序,降序皆可.
*/
//ac 70ms 二维费用完全背包 统计指定物品数目恰好装满背包方案数
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 310
#define M 310
typedef long long ll;
using namespace std;

int n,l1,l2;
ll dp[N][M],ans;
char str[20];

int main(){
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int i=1;i<N;i++){
        for(int j=i;j<M;j++){//背包容量j和指定物品个数k 顺换顺序可以颠倒
            for(int k=1;k<N;k++)
                dp[k][j]+=dp[k-1][j-i];
        }
    }
    while(gets(str)!=NULL){
        ans=0;
        l1=l2=-1;
        sscanf(str,"%d %d %d",&n,&l1,&l2);
        l1=min(l1,300);
        l2=min(l2,300);
        if(l1 == -1){
            for(int i=0;i<=n;i++)
                ans+=dp[i][n];
            printf("%lld\n",ans);
        }
        else if(l2 == -1){
            for(int i=0;i<=l1;i++)
                ans+=dp[i][n];
            printf("%lld\n",ans);
        }
        else{
            for(int i=l1;i<=l2;i++)
                ans+=dp[i][n];
            printf("%lld\n",ans);
        }
    }
    return 0;
}

/*
//ac 30ms
//f[i][j] += f[i - j][j] + f[i][j - 1] (使用面值j和不使用面值j)。
//摘自博客:https://blog.csdn.net/hyczms/article/details/41965129
#include <stdio.h>
#include <string.h>
const int N = 305;
int n, l1, l2;
char str[100];
long long f[N][N];

int main() {
	f[0][0] = 1;
	for (int i = 0; i <= 300; i++)
		for (int j = 1; j <= 300; j++) {
			if (i >= j)
				f[i][j] += f[i - j][j];
			if (j >= 1)
				f[i][j] += f[i][j - 1];
		}
	while (gets(str)) {
		int a = sscanf(str, "%d%d%d", &n, &l1, &l2);
		l1 = l1 < 300 ? l1 : 300;
		l2 = l2 < 300 ? l2 : 300;
		if (a == 1)
			printf("%lld\n", f[n][n]);
		else if (a == 2)
			printf("%lld\n", f[n][l1]);
		else
			printf("%lld\n", f[n][l2] - f[n][l1 - 1]);
	}
	return 0;
}
*/
