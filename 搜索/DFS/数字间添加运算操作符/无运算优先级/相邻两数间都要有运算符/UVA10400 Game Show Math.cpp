/*
题意:
给出p个数值，可以任意的在数值之间添加+，- ，*  ，/，运算，
要求找到一个算式可以使得算式的值等于目标值，不用考虑运算符
的优先级,永远按照从左至右的顺序一次结合计算.
要求在结合过程中计算的结果必须在[-32000,32000]范围内,并且应用
除法时,必须整除才能应用.
0<n<=100.
链接:https://www.luogu.com.cn/problem/UVA10400
思路:暴力回溯枚举每两个数之间间隔的运算符(+、-、*、/),只是因为
n<=100,直接计算会TLE.可以发现在运算的过程中对于前k-1个数得到的
运算结果为sum,这个状态可能会重复搜索到,如果之前不能得到目标值,
下次再次搜索到时就不必重复搜索.
因此记忆化搜索.
dp[i][j]=1表示前i-1个数得到运算结果为j 这个状态是无法得到目标值的.
初始状态设置为-1,因为数组下标不能为负,对运算结果统一加上最大的负数范围
32000.这样dp数组的空间复杂度为100*64000=6.4*10^6
*/
//ac 80ms 记忆化搜索
//dp[i][j]=1表示前i-1个数得到运算结果为j 这个状态是无法得到目标值的.
//复杂度O(100*64000)=6.4*10^6
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
#define M 65000
#define maxn 32000
using namespace std;

int p,a[N],res,cnt,dp[N][M];
char ans[210];

int check(int val){
    return val>=-maxn && val<=maxn;
}

int dfs(int k,int sum){
    if(dp[k][sum+maxn]!=-1)
        return 0;
    dp[k][sum+maxn]=1;
    if(k == p+1){
        if(sum == res)
            return 1;
        else
            return 0;
    }
    ans[cnt++]='+';
    if(check(sum+a[k]) && dfs(k+1,sum+a[k]))
        return 1;
    cnt--;
    ans[cnt++]='-';
    if(check(sum-a[k]) && dfs(k+1,sum-a[k]))
        return 1;
    cnt--;
    ans[cnt++]='*';
    if(check(sum*a[k]) && dfs(k+1,sum*a[k]))
        return 1;
    cnt--;
    ans[cnt++]='/';
    if(sum%a[k] == 0 && dfs(k+1,sum/a[k]))//除法因为越除越小,只需判断是否整除 无需判断是否超过[-32000,32000]这个范围
        return 1;
    cnt--;
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cnt=0;
        memset(dp,-1,sizeof(dp));
        scanf("%d",&p);
        for(int i=1;i<=p;i++)
            scanf("%d",&a[i]);
        scanf("%d",&res);
        if(dfs(2,a[1])){
            for(int i=1,j=0;i<=p;i++,j++){
                printf("%d",a[i]);
                if(i!=p)
                    printf("%c",ans[j]);
                else
                    printf("=");
            }
            printf("%d\n",res);
        }
        else
            printf("NO EXPRESSION\n");
    }
    return 0;
}
