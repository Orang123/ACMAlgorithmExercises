/*
题意:给了两个字符串，找出它们的最长公共子序列和剩下的两部分拼接后的串
字符串长度<=100.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1503
思路:输出可以用pos[i][j]记录实际 LCS所处的位置,递归输出.
*/
//ac 31ms
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110],pos[110][110];
char a[110],b[110];
//打印LCS字符串
void printLCS(int st,int ed){
    if(!st){//有可能LCS输出完a字符串输出完了,b字符串还剩下前面的一部分,单独再都输出出来.
        for(int i=1;i<=ed;i++)
            printf("%c",b[i]);
        return;
    }
    if(!ed){//有可能LCS输出完b字符串输出完了,a字符串还剩下前面的一部分,单独再都输出出来.
        for(int i=1;i<=st;i++)
            printf("%c",a[i]);
        return;
    }

    if(pos[st][ed] == 1){
        printLCS(st-1,ed-1);
        printf("%c",a[st]);//a[st]属于LCS单独输出 一次
    }
    else if(pos[st][ed] == 2){
        printLCS(st-1,ed);
        printf("%c",a[st]);//a[st]没有算入LCS,单独输出
    }
    else if(pos[st][ed] == 3){
        printLCS(st,ed-1);
        printf("%c",b[ed]);//a[ed]没有算入LCS,单独输出
    }
}
//31ms
int main(){
    int len1,len2;
    while(scanf("%s %s",a+1,b+1)!=EOF){
        len1=strlen(a+1);
        len2=strlen(b+1);
        for(int i=1;i<=len1;i++){
            for(int j=1;j<=len2;j++){
                if(a[i] == b[j]){
                    dp[i][j]=dp[i-1][j-1]+1;
                    pos[i][j]=1;
                }
                else{
                    //这里当dp[i-1][j]==dp[i][j-1]时,对于a b字符串不属于LCS的那部分,输出的先后顺序可能不同,但OJ特判同样是AC的
                    if(dp[i-1][j]>dp[i][j-1]){
                        dp[i][j]=dp[i-1][j];
                        pos[i][j]=2;
                    }
                    else{//dp[i-1][j]==dp[i][j-1]时,会从后往前会先输出b字符串不属于LCS那部分
                        dp[i][j]=dp[i][j-1];
                        pos[i][j]=3;
                    }
                }
            }
        }
        printLCS(len1,len2);
        printf("\n");
    }
    return 0;
}

/*
//ac 15ms 不采用pos数组
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int dp[110][110];
char a[110],b[110];
//打印LCS字符串
void printLCS(int st,int ed){
    if(!st){//有可能LCS输出完a字符串输出完了,b字符串还剩下前面的一部分,单独再都输出出来.
        for(int i=1;i<=ed;i++)
            printf("%c",b[i]);
        return;
    }
    if(!ed){//有可能LCS输出完b字符串输出完了,a字符串还剩下前面的一部分,单独再都输出出来.
        for(int i=1;i<=st;i++)
            printf("%c",a[i]);
        return;
    }

    if(a[st] == b[ed]){
        printLCS(st-1,ed-1);
        printf("%c",a[st]);//a[st]属于LCS单独输出 一次
    }
    else if(dp[st-1][ed]>dp[st][ed-1]){
        printLCS(st-1,ed);
        printf("%c",a[st]);//a[st]没有算入LCS,单独输出
    }
    else if(dp[st-1][ed]<=dp[st][ed-1]){
        printLCS(st,ed-1);
        printf("%c",b[ed]);//a[ed]没有算入LCS,单独输出
    }
}
//31ms
int main(){
    int len1,len2;
    while(scanf("%s %s",a+1,b+1)!=EOF){
        len1=strlen(a+1);
        len2=strlen(b+1);
        for(int i=1;i<=len1;i++){
            for(int j=1;j<=len2;j++){
                if(a[i] == b[j])
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                	dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        printLCS(len1,len2);
        printf("\n");
    }
    return 0;
}
*/

/*
//ac 15ms 记忆化搜索
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110],pos[110][110];
char a[110],b[110];
//打印LCS字符串
void printLCS(int st,int ed){
    if(!st){//有可能LCS输出完a字符串输出完了,b字符串还剩下前面的一部分,单独再都输出出来.
        for(int i=1;i<=ed;i++)
            printf("%c",b[i]);
        return;
    }
    if(!ed){//有可能LCS输出完b字符串输出完了,a字符串还剩下前面的一部分,单独再都输出出来.
        for(int i=1;i<=st;i++)
            printf("%c",a[i]);
        return;
    }

    if(pos[st][ed] == 1){
        printLCS(st-1,ed-1);
        printf("%c",a[st]);//a[st]不属于LCS单独输出
    }
    else if(pos[st][ed] == 2){
        printLCS(st-1,ed);
        printf("%c",a[st]);//
    }
    else if(pos[st][ed] == 3){
        printLCS(st,ed-1);
        printf("%c",b[ed]);
    }
}

int dfs(int st,int ed){
    if(!st || !ed) return dp[st][ed]=0;
    if(dp[st][ed]!=-1) return dp[st][ed];
    if(a[st] == b[ed]){
        dp[st][ed]=dfs(st-1,ed-1)+1;
        pos[st][ed]=1;
    }
    else{
        dfs(st-1,ed);
        dfs(st,ed-1);
        if(dp[st-1][ed]>dp[st][ed-1]){
            dp[st][ed]=dp[st-1][ed];
            pos[st][ed]=2;
        }
        else{
            dp[st][ed]=dp[st][ed-1];
            pos[st][ed]=3;
        }
    }
    return dp[st][ed];
}

int main(){
    int len1,len2;
    while(scanf("%s %s",a+1,b+1)!=EOF){
        memset(dp,-1,sizeof(dp));
        memset(pos,0,sizeof(pos));
        len1=strlen(a+1);
        len2=strlen(b+1);
        dfs(len1,len2);
        printLCS(len1,len2);
        printf("\n");
    }
    return 0;
}
*/
