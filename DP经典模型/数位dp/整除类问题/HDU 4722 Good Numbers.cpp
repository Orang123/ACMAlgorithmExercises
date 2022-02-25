/*
����:ժ������
����һ����ÿλ����֮���ܱ�10�������������Ϊ����������������A,B��
���������Χ[A,B]�ڵĺ���.
A,B<=10^18.
����:https://acm.hdu.edu.cn/showproblem.php?pid=4722
˼·:��λdp.
dp[k][mod]��ʾ��λ��len��k-1λ��λ֮�Ͷ�10ȡģΪmod,
(�������������λ�±�)�ٴ�kλ��ĩβ�ⲿ���ܹ��ɵ�����
������ԭʼn����λ���ۼ���λ����������10�����ָ���.
*/
//ac 31ms ���仯����
//dp[k][mod]��ʾ��λ��len��k-1λ��λ֮�Ͷ�10ȡģΪmod,(�������������λ�±�)�ٴ�kλ��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn����λ���ۼ���λ
//����������10�����ָ���
#include<cstdio>
#include<cstring>
#define N 20
typedef long long ll;

int len,a[N];
ll A,B,dp[N][10];

ll dfs(int k,int mod,int limit){
    if(!k)
        return mod == 0;
    if(!limit && dp[k][mod]!=-1)
        return dp[k][mod];
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++)
        ans+=dfs(k-1,(mod+i)%10,limit && i == last);
    if(!limit)
        dp[k][mod]=ans;
    return ans;
}

ll solve(ll val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    return dfs(len,0,1);
}

int main(){
    int T,cas=0;
    memset(dp,-1,sizeof(dp));
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%lld%lld",&A,&B);
        printf("Case #%d: %lld\n",cas,solve(B)-solve(A-1));
    }
    return 0;
}
