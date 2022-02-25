/*
����:ժ������
��������[x,y]����������ƽ�����ĸ�������νƽ��������һλ��ƽ��㣬
�����������ֵ�������ȡ�
x,y<=10^18.
����:https://acm.hdu.edu.cn/showproblem.php?pid=3709
˼·:��λdp.
dp[k][pos][sum]��ʾ֧����posλ����λ��len��k-1λ�����Ϊsum(�������������λ�±�)
�ٴ�kλ��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn����λ������ʹ������͵���0����Ŀ
*/
//ac 31ms ���仯����+��֦
//dp[k][pos][sum]��ʾ֧����posλ����λ��len��k-1λ�����Ϊsum(�������������λ�±�)
//�ٴ�kλ��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn����λ������ʹ������͵���0����Ŀ
//�ռ临�Ӷ�O(20*3078)=61560
//ʱ�临�Ӷ�O(10*20*3078)=615600
//ÿ��solve����ʼ��dp���� 265ms
#include<cstdio>
#include<cstring>
#define N 20
#define M 3078//9*18*19
typedef long long ll;

int len,a[N];
ll x,y,dp[N][N][M];

ll dfs(int k,int pos,int sum,int limit){
    if(!k)
        return sum == 0;
    if(sum<0)//���������Ѿ�С��0,�ټ���ȥֻ���С ����
        return 0;
    if(!limit && dp[k][pos][sum]!=-1)
        return dp[k][pos][sum];
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++)
        ans+=dfs(k-1,pos,sum+i*(k-pos),limit && i == last);
    if(!limit)
        dp[k][pos][sum]=ans;
    return ans;
}

ll solve(ll val){
    len=0;
    while(val){
        a[++len]=val%10;
        val/=10;
    }
    ll ans=0;
    for(int i=len;i>=1;i--)//ö��ÿ��λ��i��Ϊ֧�����ƽ����Ŀ
        ans+=dfs(len,i,0,1);
    return ans-len+1;//��Ϊlen��֧�� ÿ�ζ�������һ����λȫ��Ϊ0��ƽ��,��������len-1��ȫ0�����,���Ҫ����
}

int main(){
    int T;
    memset(dp,-1,sizeof(dp));//ֻ���ʼ��һ��dp,���������ظ�ʹ�ü���õ�dpֵ
    scanf("%d",&T);
    while(T--){
        scanf("%lld%lld",&x,&y);
        printf("%lld\n",solve(y)-solve(x-1));
    }
    return 0;
}
