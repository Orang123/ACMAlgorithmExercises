#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
/*
题意:折叠的定义如下：
一个字符串可以看成它自身的折叠。记作S = S
X(S)是X(X>1)个S连接在一起的串的折叠。记作X(S) = SSSS…S(X个S)。
如果A = A’, B = B’，则AB = A’B’ 例如，因为3(A) = AAA, 2(B) = BB，
所以3(A)C2(B) = AAACBB，而2(3(A)C)2(B) = AAACAAACBB
给一个字符串，求它的最短折叠。例如AAAAAAAAAABABABCCD的最短折叠为：9(A)3(AB)CCD。
链接:https://www.luogu.com.cn/problem/P4302
思路:dp[i][j]代表i~j内的字符串折叠后的最短字符数
digit[i]记录数字i的位数,用来判断折叠字符串前面数字的长度
感觉如果问直接输出这个折叠的字符串不太容易
*/
int dp[110][110],digit[110];

int judge(int n,int len,char *s){
    for(int k=len;k<n;k++)
        //s[k]是实际[i,j]中的字符,s[k%len]为[i,k]中的字符
        if(s[k] != s[k%len]) return 0;
    return 1;
}

int main(){
    char s[110];
    int n;
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<110;i++){
        if(i<10) digit[i]=1;
        else if(i<100) digit[i]=2;
        else digit[i]=3;
    }
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)
        dp[i][i]=1;//单个字符无法折叠,最短长度就是1
    for(int l=1;l<n;l++){
        for(int i=1;i+l<=n;i++){
            int j=i+l;
            for(int k=i;k<j;k++){
                //枚举分割点重组最优分割字符串方案
                //将[i,j]分割成两段[i,k] [k+1,j] 组合,折叠未必一定比不折叠的好,如aa折叠后2(a)长度为4,原先为长度2
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
                int len=k-i+1;//[i,k]子串的长度
                /*
                若[i,k]的长度不能被[i,j]的长度整除,[i,k]就无法通过循环节拼接成[i,j],
                所以实际这里判断[i,k]循环构成[i,j]只有当l+1为len的整除因子时 才行,
                一个数n的因子差不多有log(n)个,下面的if判断实际可以忽略为常数时间
                */
                if((l+1)%len) continue;
                //判断[i,k]是否能作为循环节构成[i,j]以便进一步折叠
                if(judge(l+1,len,s+i))
                    //digit[(l+1)/len]代表几个[i,k]能构成[i,j]折叠前面的数字,2为2个括号,dp[i][k]为原先[i,k]折叠的最少字符数
                    dp[i][j]=min(dp[i][j],digit[(l+1)/len]+2+dp[i][k]);
            }
        }
    }
    printf("%d",dp[1][n]);
    return 0;
}

/*
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char s[110];
int dp[110][110],digit[110];

int judge(int i,int j,int len){
    //判断[i,k]中的每一位将其每次增加len判断[i,j]中的是否相等
    for(int k=i;k<i+len;k++)
        for(int t=k+len;t<=j;t+=len)
            if(s[k] != s[t]) return 0;
    return 1;
}

int main(){
    int n;
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<110;i++){
        if(i<10) digit[i]=1;
        else if(i<100) digit[i]=2;
        else digit[i]=3;
    }
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)
        dp[i][i]=1;
    for(int l=1;l<n;l++){
        for(int i=1;i+l<=n;i++){
            int j=i+l;
            for(int k=i;k<j;k++){
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
                int len=k-i+1;
                if((l+1)%len) continue;
                if(judge(i,j,len))
                    dp[i][j]=min(dp[i][j],digit[(l+1)/len]+2+dp[i][k]);
            }
        }
    }
    printf("%d",dp[1][n]);
    return 0;
}
*/
