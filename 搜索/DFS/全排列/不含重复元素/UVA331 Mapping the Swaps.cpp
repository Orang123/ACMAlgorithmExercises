/*
题意:给出一个长度小于5的序列，你需要对这些序列分别排好序，
你每一次操作只能对一个序列中的某两个元素进行交换，
请你算出最小交换次数有多少种方案。
链接:https://www.luogu.com.cn/problem/UVA331
思路:冒泡法,交换相邻两个a[i]>a[i+1]的逆序对,步骤一定是最少的.
*/
//ac 0ms
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 6
using namespace std;

int n,a[N],ans;

int check(){
    for(int i=1;i<n;i++){
        if(a[i]>a[i+1])
            return 0;
    }
    return 1;
}

void dfs(){
    if(check()){
        ans++;
        return;
    }
    for(int i=1;i<n;i++){
        if(a[i]>a[i+1]){
            swap(a[i],a[i+1]);
            dfs();
            swap(a[i],a[i+1]);
        }
    }
}

int main(){
    int cas=0;
    while(scanf("%d",&n) && n){
        cas++;
        ans=0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        if(check()){//初始如果 本身就是升序,步骤数为0.
            printf("There are 0 swap maps for input data set %d.\n",cas);
            continue;
        }
        dfs();
        printf("There are %d swap maps for input data set %d.\n",ans,cas);
    }
    return 0;
}
