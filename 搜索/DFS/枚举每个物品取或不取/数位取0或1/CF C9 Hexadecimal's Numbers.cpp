/*
����:����1~n�������ж��ٸ���ʮ����ֻ��1��0���.
n<=10^9.
����:https://codeforces.ml/problemset/problem/9/C
˼·:dfs,��1��ʼö����һλҪô��0,Ҫô��1.
*/
//ac 62ms
//���Ӷ�2^10
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
bfsҲ������
*/
