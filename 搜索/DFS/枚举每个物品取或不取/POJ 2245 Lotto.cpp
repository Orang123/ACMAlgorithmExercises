/*
题意:摘自网上
给你n个数（递增顺序），从中选择6个数，打印所有的组合方案。
k=0表示输入结束，打印时每两个数之间才有空格，并且每个测试之间有一个空行。
6<n<13.
链接:http://poj.org/problem?id=2245
思路:实际给出的n个数本身就是升序的,要求选取的6个数也必须是升序,
因此这个排列问题,退化成了一个组合问题,实际就是每个数选取与否,dfs暴力枚举.
一个剪枝:如果当前选取的数加上剩余还未选取的所有的数个数小于6则返回.
*/
//ac 32ms dfs每个数选取与否
//复杂度O(2^13)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
using namespace std;

int n,a[N],vis[N];

void dfs(int k,int num){
    if(num == 6){
        int flag=0;
        for(int i=1;i<=n;i++){
            if(vis[i]){
                if(!flag){
                    flag=1;
                    printf("%d",a[i]);
                }
                else
                    printf(" %d",a[i]);
            }
        }
        printf("\n");
        return;
    }
    if(k == n+1)
        return;
    if(num+n-k+1<6)
        return;
    vis[k]=1;
    dfs(k+1,num+1);
    vis[k]=0;
    dfs(k+1,num);
}

int main(){
    while(scanf("%d",&n) && n){
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        dfs(1,0);
        printf("\n");
    }
    return 0;
}

/*
//ac 32ms dfs循环线性枚举
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
using namespace std;

int n,a[N],vis[N];

void dfs(int k,int num){
    if(num == 6){
        int flag=0;
        for(int i=1;i<=n;i++){
            if(vis[i]){
                if(!flag){
                    flag=1;
                    printf("%d",a[i]);
                }
                else
                    printf(" %d",a[i]);
            }
        }
        printf("\n");
        return;
    }
    if(k == n+1)
        return;
    if(num+n-k+1<6)
        return;
    for(int i=k;i<=n;i++){
    	vis[i]=1;
    	dfs(i+1,num+1);
    	vis[i]=0;
	}
}

int main(){
    while(scanf("%d",&n) && n){
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        dfs(1,0);
        printf("\n");
    }
    return 0;
}
*/
