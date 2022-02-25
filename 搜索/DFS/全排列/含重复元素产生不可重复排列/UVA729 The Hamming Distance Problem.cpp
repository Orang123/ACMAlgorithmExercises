/*
题意:
一个长度为n的字符串包含了h个1（其他全为0）,求其全排列，注意要按照字典序。
0<n<=16,0<h<=16.
链接:https://www.luogu.com.cn/problem/UVA729
思路:
方法1:dfs枚举每一位取0还是1,记录01的数量是否符合要求.
方法2:直接从初始字典序排列枚举不可重复的全排列.
*/
//ac 10ms dfs枚举每一位取0还是1,记录01的数量是否符合要求
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
using namespace std;

int n,h,vis[N];
char a[N];

void dfs(int k,int num){
    if(k == n+1){
        a[k]='\0';
        printf("%s\n",a+1);
        return;
    }
    if(k-num<=n-h){
        a[k]='0';
        dfs(k+1,num);
    }
    if(num+1<=h){
        a[k]='1';
        dfs(k+1,num+1);
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&h);
        dfs(1,0);
        if(T)
            printf("\n");
    }
    return 0;
}

/*
//ac 20ms 枚举不可重复排列,判断第k位枚举不能和之前枚举的重复
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
using namespace std;

int n,h,vis[N];
char a[N],b[N];

void dfs(int k){
    if(k == n+1){
        b[k]='\0';
        printf("%s\n",b+1);
        return;
    }
    for(int i=1;i<=n;i++){
    	if(!vis[i] && b[k]!=a[i]){
    		vis[i]=1;
    		b[k]=a[i];
    		dfs(k+1);
    		vis[i]=0;
		}
	}
	b[k]='\0';
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&h);
        for(int i=1;i<=n;i++){//初始序列必须保证是字典序
        	if(i<=n-h)
        		a[i]='0';
        	else
        		a[i]='1';
		}
        dfs(1);
        if(T)
            printf("\n");
    }
    return 0;
}
*/
