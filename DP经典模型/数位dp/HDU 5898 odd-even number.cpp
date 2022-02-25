/*
题意:摘自网上
统计区间[l,r]内数字数位上的连续的奇数个数都是偶数，偶数个数为奇数的数的个数。
l,r<=9*10^18.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=5898
思路:数位dp.
dp[k][odd][even]表示数位从len到k-1位数位(从右至左计算数位下标)
连续奇数的数位个数为odd,连续偶数数位个数为even再从k位到末尾这部分
能构成的所有不超过原始n的数位串满足连续偶数个数为奇数,连续奇数个数为偶数的数字串数目.
*/
//ac 0ms 记忆化搜索
//dp[k][odd][even]表示数位从len到k-1位数位(从右至左计算数位下标)连续奇数的数位个数为odd,连续偶数数位个数为even
//再从k位到末尾这部分能构成的所有不超过原始n的数位串满足连续偶数个数为奇数,连续奇数个数为偶数的数字串数目
#include<cstdio>
#include<cstring>
#define N 20
typedef long long ll;

int len,a[N];
ll l,r,dp[N][N][N];

//odd连续奇数数位的个数,even连续偶数数位的个数,
//flag=0表示当前数位全为0,都是前导0,为1表示不存在前导0,当前数位表示的数不为0
ll dfs(int k,int odd,int even,int flag,int limit){
    if(!k){
        //只有连续奇数个数为偶数,连续偶数个数为奇数的数串才是合法的,返回1
        if((odd%2 == 0) && (even%2 || !even))
            return 1;
        else
            return 0;
    }
    if(!limit && dp[k][odd][even]!=-1)
        return dp[k][odd][even];
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++){
        if(i%2){//第k位设置为奇数
            if(even%2 || !even)//要保证之前的偶数数位为奇数,或偶数个数为0,开始统计连续奇数个数时,连续偶数个数even要设置为0
                ans+=dfs(k-1,odd+1,0,1,limit && i == last);
        }
        else{//第k位设置为偶数
            if(!i && !flag)//当前第k位取0,且前面都是前导0,则odd even flag都设置为0
                ans+=dfs(k-1,0,0,0,limit && i == last);
            //加入偶数,要保证之前的连续奇数个数为偶数,0%2也为0,所以不用再判断!odd,并且odd要重新置0
            else if(odd%2 == 0)//这里前导零标志flag不能继承之前的flag,i可能不为0,这时要更新为1,所以flag要恒为1,当时样例1 wa在这里好久 --
                ans+=dfs(k-1,0,even+1,1,limit && i == last);
        }
    }
    if(!limit)
        dp[k][odd][even]=ans;
    return ans;
}

ll solve(ll val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    return dfs(len,0,0,0,1);
}

int main(){
    int T;
    memset(dp,-1,sizeof(dp));
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        scanf("%lld%lld",&l,&r);
        printf("Case #%d: %lld\n",cas,solve(r)-solve(l-1));
    }
    return 0;
}
