/*
题意:
给定两个正整数l和r,求在[l,r]中的所有整数中,每个数码(digit)各出现了多少次.
1<=l,r<=10^12.
注意:对于11,1出现了2次.
链接:https://www.luogu.com.cn/problem/P2602
思路:数位dp,注意有误前导0会影响到 记忆化搜索的判定,
因此记忆化搜索要设置为3个维度,当前数位k,digit数位出现次数num,
有误前导0 lead.
列如:num=0的情况,有前导0 num是为0的,但是没有前导0,数位i没有一个
是digit,num也会为0,因此需要记录前导0进dp数组.
*/
//ac 20ms 记忆化搜索
#include<cstdio>
#include<cstring>
#define N 14
#define M 14
typedef long long ll;

int len,a[N],digit;
ll l,r,dp[N][M][2],b1[10],b2[10];

ll dfs(int k,int num,int lead,int limit){
    if(!k)
        return num;
    if(!limit && dp[k][num][lead]!=-1)
        return dp[k][num][lead];
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++){
        if(lead){//有前导0
            if(i)//第k位取非零数,没有前导0,lead设置为0,num是否加1 取决于是否i是否等于digit
                ans+=dfs(k-1,num+(i == digit),0,limit && i == last);
            else//第k位取零,num依然为0,依然存在前导0,因此num=0,lead=1
                ans+=dfs(k-1,0,1,limit && i == last);
        }
        else//没有前导0 lead=0,num是否加1 取决于是否i是否等于digit
            ans+=dfs(k-1,num+(i == digit),0,limit && i == last);
    }
    if(!limit)
        dp[k][num][lead]=ans;
    return ans;
}

void solve(ll val,ll *b){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    for(digit=0;digit<=9;digit++){//枚举要判定的数位digit 0~9
        memset(dp,-1,sizeof(dp));
        b[digit]=dfs(len,0,1,1);//有前导0 lead初始设置为1
    }
}

int main(){
    scanf("%lld%lld",&l,&r);
    solve(r,b2);
    solve(l-1,b1);
    for(int i=0;i<=9;i++){
        if(i)
            printf(" ");
        printf("%lld",b2[i]-b1[i]);
    }
    return 0;
}
