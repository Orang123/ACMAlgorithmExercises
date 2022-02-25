/*
题意:摘自网上
给出一t,n,再给出的n个数中，输出所有的可能使几个数的和等于t
注意不能输出重复组合,题目给出的序列默认是降序排列的.
n<=12,t<=1000.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1258
思路:dfs回溯枚举 每个数取与不取,注意下一个数和上一个数相同时,
避免重复选取,产生重复组合.
*/
//ac 0ms dfs+回溯枚举每个数字选与不选,去除重复的组合
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
using namespace std;

int t,n,a[N],vis[N],ok;

void dfs(int k,int sum){
    if(sum>t)
        return;
    if(sum == t){
        ok=1;
        int flag=0;
        for(int i=1;i<=n;i++){
            if(vis[i]){
                if(!flag){
                    printf("%d",a[i]);
                    flag=1;
                }
                else
                    printf("+%d",a[i]);
            }
        }
        printf("\n");
        return;
    }
    if(k == n+1)
        return;
    vis[k]=1;
    //如果第k-1个数和第k个数不等,则无需判断
    //如果第k-1个数和第k个数相等,则必须是第k-1个数选取才能再选取第k个数,
    //否则如果第k-1个数不选取,第k个数选取,这里必然会和第k-1个数选取,第k个数不选取 重复
    if(a[k]!=a[k-1] || (a[k] == a[k-1] && vis[k-1]))
        dfs(k+1,sum+a[k]);
    vis[k]=0;
    dfs(k+1,sum);
}

int main(){
    while(scanf("%d%d",&t,&n) && t+n){
        ok=0;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        printf("Sums of %d:\n",t);
        dfs(1,0);
        if(!ok)
            printf("NONE\n");
    }
    return 0;
}

/*
//ac 0ms dfs循环线性枚举
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 15
using namespace std;

int t,n,a[N],vis[N],ok;

void dfs(int k,int sum){
    if(sum>t)
        return;
    if(sum == t){
        ok=1;
        int flag=0;
        for(int i=1;i<=n;i++){
            if(vis[i]){
                if(!flag){
                    printf("%d",a[i]);
                    flag=1;
                }
                else
                    printf("+%d",a[i]);
            }
        }
        printf("\n");
        return;
    }
    if(k == n+1)
        return;
    //这个做法 实际第n个数 是肯定会取到的,因此dfs结束条件不能是k == n+1,直接就是在k在任意时刻下判断是否sum == t即可,此时可能还未累加第n个数
    for(int i=k;i<=n;i++){
    	if(i-1>=k && a[i] == a[i-1])//枚举下一位不能和之前上一位相同,这样会产生重复 组合
    		continue;
    	vis[i]=1;
    	dfs(i+1,sum+a[i]);
    	vis[i]=0;
	}
}

int main(){
    while(scanf("%d%d",&t,&n) && t+n){
        ok=0;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        printf("Sums of %d:\n",t);
        dfs(1,0);
        if(!ok)
            printf("NONE\n");
    }
    return 0;
}
*/
