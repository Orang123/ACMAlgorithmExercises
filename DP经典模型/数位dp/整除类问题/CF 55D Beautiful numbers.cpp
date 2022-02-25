/*
����:ժ������
����һ������l��r������l��r��Χ�ڵ������ж��ٸ���������
��ÿһ�����ֶ�����������������λ����
l,r<=9*10^18.
����:https://codeforces.com/contest/55/problem/D
˼·:��λdp.
��n����������n�ķ���10������λ,ʵ�ʾ���nҪ����������n
�ķ���10����������С������.
dp[k][mod][lcm[val]]��ʾ��λ��len��k-1λ��2520ȡģΪmod,���Ӧ��lcm��ֵΪval,lcm���Ϊlcm[val]
(�������������λ�±�)�ٴ�kλ��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn����λ������ȡģ������mod������kλ����lcm�ĸ���
֮����Ҫ��lcm�������Ϊ1~9����С������ ��Ч��ֻ��50��,��1~9��lcm���Ϊ2520.
���ֱ�ӽ�lcm��ֵ����dp����,�ռ临�Ӷ�Ϊ20*2520*2520=1.27*10^8,��MLE��.
*/
//ac 530ms ���仯����
//dp[k][mod][lcm[val]]��ʾ��λ��len��k-1λ��2520ȡģΪmod,���Ӧ��lcm��ֵΪval,lcm���Ϊlcm[val]
//(�������������λ�±�)�ٴ�kλ��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn����λ������ȡģ������mod������kλ����lcm�ĸ���
//�ռ临�Ӷ�O(20*2520*51)=2570400
//ʱ�临�Ӷ�O(10*20*2520*51)=25704000
#include<cstdio>
#include<cstring>
#define N 20
#define M 2520
typedef long long ll;

int len,a[N],lcm[M];
ll l,r,dp[N][M][60];//lcm�ĸ���ʵ��ֻ��50��

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
        int val=(mod*10+i)%M;//ÿ�·�һ���µ���λҪ�����lcm2520ȡģ,��������Ӱ�����յĽ��
        if(i)//������ ��lcm
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
            lcm[i]=++id;//��¼1~9���ܲ��������п���lcm�ı��
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
