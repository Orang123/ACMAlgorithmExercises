/*
题意:一个环由n个圆组成.将自然数1、2、...、n分别放入每个圆中,
相邻两个圆内数之和应为素数.
注意:第一个圆圈的数应始终为1.按照字典序输出所有序列.
n<20.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1016
思路:因为n<20,直接枚举全排列肯定会TLE,需要在枚举全排列的过程中
直接判断和相邻的数的和是否为素数,这样复杂度就会降低.
*/
//ac 343ms 筛素数+dfs枚举全排列
#include<cstdio>
#include<cstring>
int a[50];
bool visit[50],prime[50];
void prim(){
    for (int i = 1; i < 50; i++)
        prime[i] = true;
    prime[1] = false;
    for (int i = 2; i <25; i++){
        if (prime[i])
        for (int j = 2 * i; j < 50; j += i)
            prime[j] = false;
    }
}
void DFS(int n,int num){
    if (num == n + 1&&prime[a[1]+a[n]]){
        printf("%d", a[1]);
        for (int i = 2; i <= n; i++)
            printf(" %d", a[i]);
        putchar('\n');
    }
    else{
        for (int i = 2; i <= n;i++)
        if (!visit[i]&&prime[i+a[num-1]]){
            visit[i] = true;
            a[num] = i;
            DFS(n, num + 1);
            visit[i] = false;
        }
    }
}
int main(){
    int n,cnt=1;
    prim();
    a[1] = 1;
    while (scanf("%d", &n) != EOF){
        printf("Case %d:\n", cnt);
        DFS(n, 2);
        putchar('\n');
        cnt++;
    }
    return 0;
}

/*
//ac 265ms 线性判断素数
#include<cstdio>
#include<cmath>
#include<cstring>
int a[50];
bool visit[50];

int check(int x){
	int low=sqrt(x);
	for(int i=2;i<=low;i++){
		if(x%i == 0)
			return 0;
	}
	return 1;
}

void DFS(int n,int num){
    if (num == n + 1){
        printf("%d", a[1]);
        for (int i = 2; i <= n; i++)
            printf(" %d", a[i]);
        putchar('\n');
    }
    else{
        for (int i = 2; i <= n;i++)
        if (!visit[i]&& check(i+a[num-1])){
        	if(num == n && !check(1+i))
        		continue;
            visit[i] = true;
            a[num] = i;
            DFS(n, num + 1);
            visit[i] = false;
        }
    }
}

int main(){
    int n,cnt=1;
    a[1] = 1;
    while (scanf("%d", &n) != EOF){
        printf("Case %d:\n", cnt);
        DFS(n, 2);
        putchar('\n');
        cnt++;
    }
    return 0;
}
*/
