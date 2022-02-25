/*
题意:摘自网上
输入两个十进制正整数n和m，求闭区间[n ,m]内有多少个Round number
所谓的Round Number就是把一个十进制数转换为一个无符号二进制数，
若该二进制数中0的个数大于等于1的个数，则它就是一个Round Number
n<=2*10^9.
链接:http://poj.org/problem?id=3252
思路:数位dp.只是数位是二进制位01.状态标识,
要标注二进制位中0和1的个数,注意前导0不算入0的个数.
00110,这样会是0比1多,但是这个数实际应该是110.
虽然对于dp[k][zero][one]来说 有无前导零会影响后续
记忆化搜索,但是这个dfs只会在最先开始的情况 不断选择i=0,搜到全0的情况.
对于有前导0和没有前导0,其zero one一定是不同的,无前导0 one一定不为0,
而有前导0 one和zero一定都为0,两种情况不会重叠,因此dp数组可以不记录前导0.
这点不同于洛谷P2602 [ZJOI2010]数字计数.
*/
//ac 16ms 记忆化搜索
//dp[k][zero][one]表示n的二进制数位从len到k-1位0的数目为zero,1的数目为one(从右至左计算数位下标)
//再从k位到末尾这部分能构成的所有不超过原始n的二进制串满足0的个数不小于1的个数的二进制串的个数
//空间复杂度O(2*32*32)=1800
//时间复杂度O(2*2*32*32)=3600
#include<cstdio>
#include<cstring>
#define N 32

int n,m,len,dp[N][N][N],a[N];

int dfs(int k,int flag,int zero,int one,int limit){
    if(!k)
        return zero>=one;
    if(!limit && dp[k][zero][one]!=-1)
        return dp[k][zero][one];
    int last=limit?a[k]:1;
    int ans=0;
    for(int i=0;i<=last;i++){
        if(flag){//没有前导0,前面已经有1了
            if(!i)//取0 zero+1
                ans+=dfs(k-1,flag,zero+1,one,limit && i == last);
            else//取1 one+1
                ans+=dfs(k-1,flag,zero,one+1,limit && i == last);
        }
        else{//前面没有一个1,都是前导0,这些零并不算入0的个数里
            if(i)//当前位取1 就不存在前导0了,flag设置为1,one+1
                ans+=dfs(k-1,1,zero,one+1,limit && i == last);
            else//当前位取0 仍然是前导0 不算入0的个数,flag,zero,one都是0
                ans+=dfs(k-1,0,0,0,limit && i == last);
        }
    }
    if(!limit)
        dp[k][zero][one]=ans;
    return ans;
}

int solve(int val){
    len=0;
    while(val){
        a[++len]=val%2;
        val/=2;
    }
    return dfs(len,0,0,0,1);
}

int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d%d",&n,&m);
    printf("%d",solve(m)-solve(n-1));
    return 0;
}

/*
//ac 0ms 记忆化搜索
//dp[N][N][N][2] 将前导0也计入 dp数组
#include<cstdio>
#include<cstring>
#define N 32

int n,m,len,dp[N][N][N][2],a[N];

int dfs(int k,int flag,int zero,int one,int limit){
    if(!k)
        return zero>=one;
    if(!limit && dp[k][zero][one][flag]!=-1)
        return dp[k][zero][one][flag];
    int last=limit?a[k]:1;
    int ans=0;
    for(int i=0;i<=last;i++){
        if(flag){//没有前导0,前面已经有1了
            if(!i)//取0 zero+1
                ans+=dfs(k-1,flag,zero+1,one,limit && i == last);
            else//取1 one+1
                ans+=dfs(k-1,flag,zero,one+1,limit && i == last);
        }
        else{//前面没有一个1,都是前导0,这些零并不算入0的个数里
            if(i)//当前位取1 就不存在前导0了,flag设置为1,one+1
                ans+=dfs(k-1,1,zero,one+1,limit && i == last);
            else//当前位取0 仍然是前导0 不算入0的个数,flag,zero,one都是0
                ans+=dfs(k-1,0,0,0,limit && i == last);
        }
    }
    if(!limit)
        dp[k][zero][one][flag]=ans;
    return ans;
}

int solve(int val){
    len=0;
    while(val){
        a[++len]=val%2;
        val/=2;
    }
    return dfs(len,0,0,0,1);
}

int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d%d",&n,&m);
    printf("%d",solve(m)-solve(n-1));
    return 0;
}
*/
