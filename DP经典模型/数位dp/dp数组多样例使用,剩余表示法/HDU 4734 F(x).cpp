/*
题意:摘自网上
给一个数A (十进制表示形式为AnAn-1An-2 ... A2A1，定义函数
F(x) = An * 2^n-1 + An-1 * 2^n-2 + ... + A2 * 2 + A1 * 1，
给一个B,求B以内的i,满足F(i)<=F(A).
A,B<10^9.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=4734
思路:数位dp.只是T<=10^4组样例,dp数组要能够反复使用,不能
每次都初始化,因此要记录剩下可以累加的值,不能记录已经累加
的值,因为每组样例的A都不同.
*/
//ac 15ms 记忆化搜索+剪枝
//dp[k][val]表示数位从len到k-1位被A的sum减去剩余val能累加(从右至左计算数位下标)
//再从k位到末尾这部分能构成的所有不超过原始n的数位串满足不会使得剩余val小于0的数目
//空间复杂度O(10*20736)=207360
//时间复杂度O(10*10*20736)=2073600
#include<cstdio>
#include<cstring>
#define N 10
#define M 20736//2568*9*9

int A,B,len,dp[N][M],a[N],b[N],sum;

int dfs(int k,int val,int limit){
    if(!k)
        return val>=0;
    //不加这个剪枝影响也不大
    if(val<0)//如果当前剩余val已经被减少到小于0 则结束 等于0并不剪枝,因为后面所有位数字可以取0,并不会消耗val使其小于0
        return 0;
    if(!limit && dp[k][val]!=-1)
        return dp[k][val];
    int last=limit?a[k]:9;
    int ans=0;
    for(int i=0;i<=last;i++)
        ans+=dfs(k-1,val-i*b[k],limit && i == last);//这里是val减去当前位的值,这样表示的dp状态才能对多组样例进行记忆化
    if(!limit)
        dp[k][val]=ans;
    return ans;
}

void cal(int val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
}

int main(){
    int T,cas=0;
    memset(dp,-1,sizeof(dp));//dp数组只初始化一次
    b[1]=1;
    for(int i=2;i<N;i++)
        b[i]=b[i-1]*2;
    scanf("%d",&T);
    while(T--){
        cas++;
        sum=0;
        scanf("%d%d",&A,&B);
        cal(A);
        for(int i=1;i<=len;i++)
            sum+=a[i]*b[i];
        cal(B);
        printf("Case #%d: %d\n",cas,dfs(len,sum,1));//初始能减少的值为sum(A的f(x)总和)
    }
    return 0;
}

/*
//ac 15ms 记忆化记录 dp[k][sum-val],仍然是累加
#include<cstdio>
#include<cstring>
#define N 10
#define M 20736

int A,B,len,dp[N][M],a[N],b[N],sum;

int dfs(int k,int val,int limit){
    if(!k)
        return val<=sum;
    if(val>sum)
        return 0;
    if(!limit && dp[k][sum-val]!=-1)
        return dp[k][sum-val];
    int last=limit?a[k]:9;
    int ans=0;
    for(int i=0;i<=last;i++)
        ans+=dfs(k-1,val+i*b[k],limit && i == last);
    if(!limit)
        dp[k][sum-val]=ans;
    return ans;
}

void cal(int val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
}

int main(){
    int T,cas=0;
    b[1]=1;
    for(int i=2;i<N;i++)
        b[i]=b[i-1]*2;
    memset(dp,-1,sizeof(dp));
    scanf("%d",&T);
    while(T--){
        cas++;
        sum=0;
        scanf("%d%d",&A,&B);
        cal(A);
        for(int i=1;i<=len;i++)
            sum+=a[i]*b[i];
        cal(B);
        printf("Case #%d: %d\n",cas,dfs(len,0,1));
    }
    return 0;
}
*/

/*
//TLE
//dp[k][val]表示数位从len到k-1位权值累加和为val(从右至左计算数位下标)
//再从k位到末尾这部分能构成的所有不超过原始n的数位串满足不会使得val<=sum的数目
//这样只能对一组样例进行记忆化,因为每个样例A的sum值是不同的,不能直接使用上一组样例记录的dp值
#include<cstdio>
#include<cstring>
#define N 10
#define M 20736

int A,B,len,dp[N][M],a[N],b[N],sum;

int dfs(int k,int val,int limit){
    if(!k)
        return val<=sum;
    if(val>sum)
        return 0;
    if(!limit && dp[k][val]!=-1)
        return dp[k][val];
    int last=limit?a[k]:9;
    int ans=0;
    for(int i=0;i<=last;i++)
        ans+=dfs(k-1,val+i*b[k],limit && i == last);
    if(!limit)
        dp[k][val]=ans;
    return ans;
}

void cal(int val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
}

int main(){
    int T,cas=0;
    b[1]=1;
    for(int i=2;i<N;i++)
        b[i]=b[i-1]*2;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,-1,sizeof(dp));
        sum=0;
        scanf("%d%d",&A,&B);
        cal(A);
        for(int i=1;i<=len;i++)
            sum+=a[i]*b[i];
        cal(B);
        printf("Case #%d: %d\n",cas,dfs(len,0,1));
    }
    return 0;
}
*/
