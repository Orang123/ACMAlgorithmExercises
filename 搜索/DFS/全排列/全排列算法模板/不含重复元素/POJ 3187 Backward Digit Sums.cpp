/*
题意:1到N(N<=10)的全排列中,按杨辉三角方式累加和为sum的字典序最小的排列.
eg:3 1 2 4 N=4
    4 3 6
     7 9
      16
链接:http://poj.org/problem?id=3187
思路:按字典序暴力枚举 可重复元素的排列
*/
//ac 79ms 含有重复元素,输出的排列会有重复的
#include<stdio.h>
bool visit[10];
int temp[10],n,sum;
bool permutation(int *a,int k)
{
    if(k==n)
    {
        for(int i=0; i<n; i++) temp[i]=a[i];
        for(int i=0; i<n-1; i++)
            for(int j=0; j<n-i-1; j++) temp[j]+=temp[j+1];
        if(*temp==sum)
        {
            for(int i=0; i<n-1; i++) printf("%d ",a[i]);
            printf("%d\n",a[n-1]);
            return true;
        }
        return false;
    }
    else
        for(int i=0; i<n; i++)
            if(visit[i]==false)
            {
                a[k]=i+1;//将当前位的值与上一次退栈的位的值交换
                visit[i]=true;
                if(permutation(a,k+1)) return true;//每次递归都会向低位前进发生相邻的交换，再依次向前交换
                visit[i]=false;//为下次的回溯做好准备
            }
    return false;
}
int main()
{
    int a[10];
    int k;
    scanf("%d%d",&n,&sum);
    k=0;
    permutation(a,k);
    return 0;
}

/*
//ac 0ms 利用最终总和可以表示成原序列与杨辉三角最后一行系数的乘积来 进行剪枝
//假设第一行的数为a,b,c,d,e,f
//那么n=4时 最后一行的累加结果sum可以表示成a+3b+3c+d
//n=5 a+4b+6c+4d+e
//n=6 a+5b+10c+10d+5e+f
#include<cstdio>
int a[13],c[12][12],n,sum,vis[13];
int dfs(int num,int ans){
    if(ans>sum) return 0;//剪枝如果当前系数乘积已经超过sum,进行剪枝
    if(num == n+1){
        if(ans == sum) return 1;
        else return 0;
    }
    for(int i=1;i<=n;i++){
        if(vis[i]) continue;
        a[num]=i;
        vis[i]=1;
        //i*c[n-1][num-1]表示sum的多项式中的一项这项的值等于 第n-1层杨辉三角中第num-1个数*该数(i)
        if(dfs(num+1,ans+i*c[n-1][num-1])) return 1;
        vis[i]=0;
    }
    return 0;
}

int main(){
    scanf("%d%d",&n,&sum);
    for(int i=0;i<12;i++)
        c[i][0]=1;//数组的两维 都是从0开始标号的
    for(int i=1;i<12;i++)
        for(int j=1;j<=i;j++)
            c[i][j]=c[i-1][j-1]+c[i-1][j];
    if(dfs(1,0)){
        printf("%d",a[1]);
        for(int i=2;i<=n;i++) printf(" %d",a[i]);
        printf("\n");
    }
    return 0;
}
*/

/*
//ac 32ms stl版本
//默认permutation 产生的全排列为按字典序顺序 是不可重复的全排列
//http://blog.csdn.net/desirepath/article/details/50447712
//http://blog.csdn.net/ac_gibson/article/details/45308645
#include<stdio.h>
#include<algorithm>
using namespace std;
int main()
{
    int n,sum;
    int a[10],temp[10];
    while(scanf("%d%d",&n,&sum)!=EOF)
    {
        for(int i=0;i<n;i++) a[i]=i+1;
        do
        {
            for(int i=0;i<n;i++)
            temp[i]=a[i];
            for(int i=0;i<n-1;i++)
                for(int j=0;j<n-i-1;j++)
                temp[j]=temp[j]+temp[j+1];
            if(temp[0]==sum)
            {
                printf("%d",a[0]);
                for(int i=1;i<n;i++)
                    printf(" %d",a[i]);
                putchar('\n');
                break;
            }
        }while(next_permutation(a,a+n));
    }
    return 0;
}
*/
