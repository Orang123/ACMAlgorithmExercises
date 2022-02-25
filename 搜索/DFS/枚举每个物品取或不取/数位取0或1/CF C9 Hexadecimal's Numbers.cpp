/*
题意:计算1~n的数内有多少个数十进制只由1和0组成.
n<=10^9.
链接:https://codeforces.ml/problemset/problem/9/C
思路:dfs,从1开始枚举下一位要么是0,要么是1.
*/
//ac 62ms
//复杂度2^10
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n,cnt;
void dfs(int x){
    if(x>n) return;
    cnt++;
    dfs(x*10);
    dfs(x*10+1);
}

int main(){
    scanf("%d",&n);
    dfs(1);
    printf("%d",cnt);
    return 0;
}

/*
bfs也很容易
*/
