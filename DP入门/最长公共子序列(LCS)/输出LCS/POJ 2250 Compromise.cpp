/*
题意:摘自网上
给你两段由空格分隔的语句, 要你求该两段语句的最长公共子序列,并输出.
且随便输出一个解即可. 注意每个单词需要看成我们一般处理字符串
子序列的一个单独字符. 即每个单词是一个整体.
单词个数<=100,单个单词长度<=30.
链接:http://poj.org/problem?id=2250
思路:LCS裸题.但注意子序列中的单个元素是一个字符串,dp时比较需要用到
strcmp函数来比较两字符串是否相等.
*/
//ac 0ms 正向dp 下标从1开始
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,m,dp[N][N];
char a[N][35],b[N][35];

void print(int i,int j){
    if(!i || !j)
        return;
    if(!strcmp(a[i],b[j])){
        print(i-1,j-1);
        if(i != 1 && j != 1)
            printf(" ");
        printf("%s",a[i]);
    }
    else{
        if(dp[i-1][j]>dp[i][j-1])
            print(i-1,j);
        else
            print(i,j-1);
    }
}

int main(){
    while(scanf("%s",a[++n])!=EOF){
        while(scanf("%s",a[++n]) && a[n][0]!='#');
        n--;
        while(scanf("%s",b[++m]) && b[m][0]!='#');
        m--;
        //memset(dp,0,sizeof(dp));//无需初始化dp数组
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!strcmp(a[i],b[j]))
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        print(n,m);
        printf("\n");
        n=m=0;
    }
    return 0;
}
