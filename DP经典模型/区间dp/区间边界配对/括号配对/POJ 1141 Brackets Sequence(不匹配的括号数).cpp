#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define INF 0x3f3f3f3f
/*
题意:给定一串括号序列,输出需要填补最少的括号序列使得其成为合法括号序列.
链接:http://poj.org/problem?id=1141
思路:dp[i][j]表示i到j最少添加几个括号使其成为合法括号序列。同时用pos[i][j]记录最少需要补全括号数目的区间分割点,方便递归输出补全的括号序列。
*/
int dp[300][300],pos[300][300];
char str[300];
void printStr(int l,int r){
    if(l>r)
        return;
    else if(l==r){//若剩下的某一点一定是单独不匹配的
        if(str[l]=='['||str[l]==']')
            printf("[]");
        else
            printf("()");
    }
    else if(pos[l][r]==-1){//说明str[l]和str[r]时配对的
        printf("%c",str[l]);//输出左括号
        printStr(l+1,r-1);//这里递归输出里边的区间
        printf("%c",str[r]);//回溯时输出右括号
    }
    else{//按照之前记录的区间最少需要补全括号数的分割点k分开遍历,才能输出正确的需要补全的括号序列
        printStr(l,pos[l][r]);//有分割点就按分割点输出
        printStr(pos[l][r]+1,r);
    }
}

bool match(char x,char y){
    if(x=='['&&y==']')
        return true;
    if(x=='('&&y==')')
        return true;
    return false;
}
int main(){
    int len;
    while(gets(str)!=NULL){//这里poj用scanf 判断文件结束符返回EOF会报WrongAnswer但是gets!=NULL就没事
        memset(dp,0,sizeof(dp));
        len=strlen(str);
        for(int i=0;i<len;i++)
           dp[i][i]=1;
        for(int l=1;l<len;l++){
            for(int i=0;i+l<len;i++){
                int j=i+l;
                dp[i][j]=INF;//这里因为后面要枚举分割点 更新所以标记为INF
                if(match(str[i],str[j])){//如果当前位置匹配，那么pos置-1,说明这个大区间两端点不需要补全直接正常输出
                    dp[i][j]=dp[i+1][j-1];
                    pos[i][j]=-1;//记录没有分割点,输出时直接将区间2端点和中部按中序遍历输出即可
                }
                for(int k=i;k<j;k++){//枚举括号匹配的分割点,记录最少需要补全的括号数目的区间分割方案
                    if(dp[i][j]>dp[i][k]+dp[k+1][j]){
                        dp[i][j]=dp[i][k]+dp[k+1][j];//更新最小的匹配数,这样分割的区间需要补全的括号序列(不匹配的括号)才是正确的.
                        pos[i][j]=k;//记录区间[i,j]最少需要补全括号数目的分割点k
                    }
                }
            }
        }
        printStr(0,len-1);
        printf("\n");
    }
    return 0;
}

/*
如果只是求解填补最少的括号序列使得其成为合法括号序列的字符个数,而不是输出填补后的合法序列,
可以在线性时间用栈求解.
leetcode 921 使括号有效的最少添加
https://leetcode-cn.com/problems/minimum-add-to-make-parentheses-valid/
给定一个由 '(' 和 ')' 括号组成的字符串 S，我们需要添加最少的括号（ '(' 或是 ')'，可以在任何位置），以使得到的括号字符串有效。
从形式上讲，只有满足下面几点之一，括号字符串才是有效的：
它是一个空字符串，或者
它可以被写成 AB （A 与 B 连接）, 其中 A 和 B 都是有效字符串，或者
它可以被写作 (A)，其中 A 是有效字符串。
给定一个括号字符串，返回为使结果字符串有效而必须添加的最少括号数。

class Solution {
public:
    int minAddToMakeValid(string s) {
        stack<char> sk;
        for(char &val : s){
            if(val == '(')
                sk.push(val);
            else if(val == ')'){
                if(!sk.empty() && sk.top() == '(')
                    sk.pop();
                else
                    sk.push(val);
            }
        }
        return sk.size();
    }
};

class Solution {
public:
    int minAddToMakeValid(string s) {
        int l=0,r=0;
        for(char &val : s){
            if(val == '(')
                l++;
            else if(val == ')'){
                if(l)
                    l--;
                else
                    r++;
            }
        }
        return l+r;
    }
};

*/
