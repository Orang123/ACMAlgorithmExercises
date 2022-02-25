/*
题意:摘自网上
给出长度为n的字符串，字符串由‘1’，‘0’，‘*’组成，
其中‘*’可以任意替换为‘1’，‘0’，求不存在连续3个
相同子串的字符串的最多个数。
n<31.
链接:https://www.luogu.com.cn/problem/UVA11127
思路:按照'*'位置枚举两种可能一种'0'一种'1',但是
枚举出所有的字符串再判断是否存在连续3个相同子串
肯定会超时,字符串的个数最大可能为2^30=1073741824个.
因此要在枚举的过程中对[1,k]的子串判断是否存在连续3个
相同子串,如果存在,则停止搜索.
*/
//ac 100ms dfs回溯
//复杂度O(2^n) n为'*'的个数
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 35
using namespace std;

int n,ans;
char str[N];//str小标从1开始

//判断[1,k]的子串判断是否存在连续3个相同子串
//这个判断只会考虑新加入末尾的字符str[k]能否和前面子串构成连续3个相同子串
//因为[1,k-1] [1,k-2] [1,k-3] 的子串之前已经判断过了.
int check(int k){
    int flag;
    for(int i=1;i*3<=k;i++){//枚举子串的长度
        flag=0;
        //第三连续个子串的下标范围为 [k-i+1,k],从子串中的每一位和第二个子串 第一个子串相应位置单独判断
        for(int j=k;j>=k-i+1;j--){
            if(str[j] != str[j-i] || str[j] != str[j-2*i]){//只要某一位不同 就可以说明当前长度i下不存在连续3个子串相等,直接结束
                flag=1;
                break;
            }
        }
        if(!flag)//如果在某一长度i下 存在连续3个相等子串 就直接返回0 不可继续搜索下去了
            return 0;
    }
    return 1;
}

void dfs(int k){
    if(k == n+1){
        ans++;//数目加1
        return;
    }
    if(str[k] == '0' || str[k] == '1'){
        if(check(k))
            dfs(k+1);
    }
    else{
        str[k]='0';
        if(check(k))
            dfs(k+1);
        str[k]='1';
        if(check(k))
            dfs(k+1);
        str[k]='*';
    }
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        if(!n)
            break;
        scanf("%s",str+1);
        cas++;
        ans=0;
        dfs(1);
        printf("Case %d: %d\n",cas,ans);
    }
    return 0;
}

/*
//ac 30ms 二进制位运算优化 不太理解这个做法
//摘自博客:https://blog.csdn.net/u011345461/article/details/38660695
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 32;

char str[MAXN];
int n, ans;

bool judge(int s, int d) {
    int k = (1 << d) - 1;
    int a = s & k;
    s = s >> d;
    int b = s & k;
    s = s >> d;
    int c = s & k;
    if (a == b && b == c)
        return true;
    else
        return false;
}//利用位运算，右移d位，判断是否存在3个子串相同

void dfs(int s, int cnt) {
    int num = cnt / 3;
    int t = n - cnt - 1;
    for (int i = 1; i <= num; i++) {
        if (judge(s >> (t + 1), i))
            return;
    }
    if (cnt == n) {
        ans++;
        return;
    }
    else if (str[cnt] == '0') {
         dfs(s, cnt + 1);
    }
    else if (str[cnt] == '1') {
         dfs(s + (1 << t), cnt + 1);
    }
    else if (str[cnt] == '*') {
         dfs(s, cnt + 1);
         dfs(s + (1 << t), cnt + 1);
    }
    return;
}

int main() {
    int cas = 1;
    while (scanf("%d", &n) && n) {
        scanf("%s", str);
        ans = 0;
        dfs(0, 0);
        printf("Case %d: %d\n", cas++, ans);
    }
    return 0;
}
*/
