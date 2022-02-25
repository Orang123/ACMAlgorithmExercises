/*
题意：找到一个只由0和1组成的数能把n整除；其实最大位有20位，用无符号 __int64 正好20位，
然后输入数据并不是最小值,题目输出只要满足能除进就行,下面这种届输出的是最小的解.
链接:http://poj.org/problem?id=1426
思路:枚举每一位要么取0,要么取1.
*/
//ac
//O(2^n)=2^20=10^%6
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef unsigned __int64 ll;
int n,flag;
void dfs(ll sum,int num){
    if(num == 19) return;
    if(flag) return;
    if(sum%n==0){
        printf("%I64d\n",sum);
        flag=1;
        return;
    }
    dfs(sum*10,num+1);//157ms
    dfs(sum*10+1,num+1);//貌似优先枚举这一位1 会较早搜索到解,0ms
}

int main(){
    while(scanf("%d",&n) && n){
        flag=0;
        dfs(1,0);
    }
    return 0;
}

/*
bfs也很容易
*/
