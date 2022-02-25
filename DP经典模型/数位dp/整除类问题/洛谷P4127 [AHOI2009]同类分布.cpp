/*
����:
����������l,r,���[l,r]�и�λ����֮��������ԭ�������ĸ���.
1<=l,r<=10^18.
����:https://www.luogu.com.cn/problem/P4127
˼·:��Ϊö����λ�Ĺ�����,����λ֮���ǲ��ϱ仯��,�����Ҫö��
�������ܵ���λ֮���ٽ�����λdp.Ҫע��ÿ����λdp�������һ��ȷ��
�õ���λ֮��mod,��ͬ��λdp ��λ֮��mod�ǲ�ͬ��,���ÿ�ζ���Ҫ��ʼ��dp����.
*/
//ac 3.37s ���仯����
#include<cstdio>
#include<cstring>
#define N 20
#define M 171//19*9
typedef long long ll;

int len,a[N],mod;
ll l,r,dp[N][M][M];

ll dfs(int k,int sum1,int sum2,int limit){
    if(!k)
        return sum1 == mod && !sum2;
    if(!limit && dp[k][sum1][sum2]!=-1)
        return dp[k][sum1][sum2];
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++)
        ans+=dfs(k-1,sum1+i,(sum2*10+i)%mod,limit && i == last);
    if(!limit)
        dp[k][sum1][sum2]=ans;
    return ans;
}

ll solve(ll val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    ll ans=0;
    int sum=len*9;//ȷ����λ֮�͵����ֵ,�����ʵ��val��,dfs���صĽ��ҲΪ0,��Ӱ��
    for(mod=1;mod<=sum;mod++){
        memset(dp,-1,sizeof(dp));//ÿ��dp mod��ͬ,���Ҫ��ʼ��dp����
        ans+=dfs(len,0,0,1);
    }
    return ans;
}

int main(){
    scanf("%lld%lld",&l,&r);
    printf("%lld",solve(r)-solve(l-1));
    return 0;
}
