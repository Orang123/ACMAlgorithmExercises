/*
题意:摘自网上
给你一段区间l到r，问在l到r范围内的数，有多少个满足它的
的每一个数字都能整除它本身（非零位）。
l,r<=9*10^18.
链接:https://codeforces.com/contest/55/problem/D
思路:数位dp.
数n能整除构成n的非零10进制数位,实际就是n要能整除构成n
的非零10进制数的最小公倍数.
dp[k][mod][lcm[val]]表示数位从len到k-1位对2520取模为mod,其对应的lcm数值为val,lcm编号为lcm[val]
(从右至左计算数位下标)再从k位到末尾这部分能构成的所有不超过原始n的数位串满足取模的余数mod能整除k位数的lcm的个数
之所以要对lcm编号是因为1~9的最小公倍数 有效的只有50个,而1~9的lcm最大为2520.
如果直接将lcm数值放入dp数组,空间复杂度为20*2520*2520=1.27*10^8,会MLE的.
*/
//ac 530ms 记忆化搜索
//dp[k][mod][lcm[val]]表示数位从len到k-1位对2520取模为mod,其对应的lcm数值为val,lcm编号为lcm[val]
//(从右至左计算数位下标)再从k位到末尾这部分能构成的所有不超过原始n的数位串满足取模的余数mod能整除k位数的lcm的个数
//空间复杂度O(20*2520*51)=2570400
//时间复杂度O(10*20*2520*51)=25704000
#include<cstdio>
#include<cstring>
#define N 20
#define M 2520
typedef long long ll;

int len,a[N],lcm[M];
ll l,r,dp[N][M][60];//lcm的个数实际只有50个

int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}

int LCM(int a,int b){
    return a*b/gcd(a,b);
}

ll dfs(int k,int mod,int Lcm,int limit){
    if(!k)
        return mod%Lcm == 0;
    if(!limit && dp[k][mod][lcm[Lcm]]!=-1)
        return dp[k][mod][lcm[Lcm]];
    int last=limit?a[k]:9,tp;
    ll ans=0;
    for(int i=0;i<=last;i++){
        int val=(mod*10+i)%M;//每新放一个新的数位要用最大lcm2520取模,这样不会影响最终的结果
        if(i)//非零数 求lcm
            tp=LCM(Lcm,i);
        else
            tp=Lcm;
        ans+=dfs(k-1,val,tp,limit && i == last);
    }
    if(!limit)
        dp[k][mod][lcm[Lcm]]=ans;
    return ans;
}

ll solve(ll val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    return dfs(len,0,1,1);
}

void init(){
    int id=0;
    for(int i=1;i<=M;i++){
        if(M%i == 0)
            lcm[i]=++id;//记录1~9所能产生的所有可能lcm的编号
    }
}

int main(){
    int T;
    init();
    memset(dp,-1,sizeof(dp));
    scanf("%d",&T);
    while(T--){
        scanf("%lld%lld",&l,&r);
        printf("%lld\n",solve(r)-solve(l-1));
    }
    return 0;
}
