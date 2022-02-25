/*
题意:已知n个整数x1,x2,...,xn,以及1个整数k(k<n).
从n个整数中任选k个整数相加，可分别得到一系列的和。
现在，要求你计算出和为素数共有多少种。
n<=20,k<n.
链接:https://www.luogu.com.cn/problem/P1036
思路:dfs
*/
//ac 13ms 在线判断素数+dfs
#include<cstdio>
#include<cmath>
#define N 5000100
bool flag[N];
int a[N],n,k,cnt;

int check(int x){
    int low=sqrt(x);
    for(int i=2;i<=low;i++){
        if(x%i == 0)
            return 0;
    }
    return 1;
}

void dfs(int sum,int p,int j){
    if(j == k && check(sum)){
        cnt++;
        return;
    }
    if(p == n)
        return;
    dfs(sum+a[p],p+1,j+1);
    dfs(sum,p+1,j);
}

int main(){
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    dfs(0,0,0);
    printf("%d\n",cnt);
    return 0;
}

/*
//ac 301ms 筛素数+dfs
#include<cstdio>
#include<cmath>
#define N 5000100
bool flag[N];
int a[N],n,k,cnt;

void prim(){
    for(int i=0;i<N;i++)
        flag[i]=true;
    flag[0]=flag[1]=false;
    int h=sqrt(N);
    for(int i=2;i<=h;i++){
        if(flag[i])
            for(int j=i*i;j<N;j+=i) flag[j]=false;
    }
}

void dfs(int sum,int p,int j){
    if(j == k && flag[sum]){
        cnt++;
        return;
    }
    for(int i=p;i<n;i++)
        dfs(sum+a[i],i+1,j+1);
}

int main(){
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    prim();
    dfs(0,0,0);
    printf("%d\n",cnt);
    return 0;
}
*/
