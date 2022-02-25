/*
����:ժ������
ͳ������[l,r]��������λ�ϵ�������������������ż����ż������Ϊ���������ĸ�����
l,r<=9*10^18.
����:https://acm.hdu.edu.cn/showproblem.php?pid=5898
˼·:��λdp.
dp[k][odd][even]��ʾ��λ��len��k-1λ��λ(�������������λ�±�)
������������λ����Ϊodd,����ż����λ����Ϊeven�ٴ�kλ��ĩβ�ⲿ��
�ܹ��ɵ����в�����ԭʼn����λ����������ż������Ϊ����,������������Ϊż�������ִ���Ŀ.
*/
//ac 0ms ���仯����
//dp[k][odd][even]��ʾ��λ��len��k-1λ��λ(�������������λ�±�)������������λ����Ϊodd,����ż����λ����Ϊeven
//�ٴ�kλ��ĩβ�ⲿ���ܹ��ɵ����в�����ԭʼn����λ����������ż������Ϊ����,������������Ϊż�������ִ���Ŀ
#include<cstdio>
#include<cstring>
#define N 20
typedef long long ll;

int len,a[N];
ll l,r,dp[N][N][N];

//odd����������λ�ĸ���,even����ż����λ�ĸ���,
//flag=0��ʾ��ǰ��λȫΪ0,����ǰ��0,Ϊ1��ʾ������ǰ��0,��ǰ��λ��ʾ������Ϊ0
ll dfs(int k,int odd,int even,int flag,int limit){
    if(!k){
        //ֻ��������������Ϊż��,����ż������Ϊ�������������ǺϷ���,����1
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
        if(i%2){//��kλ����Ϊ����
            if(even%2 || !even)//Ҫ��֤֮ǰ��ż����λΪ����,��ż������Ϊ0,��ʼͳ��������������ʱ,����ż������evenҪ����Ϊ0
                ans+=dfs(k-1,odd+1,0,1,limit && i == last);
        }
        else{//��kλ����Ϊż��
            if(!i && !flag)//��ǰ��kλȡ0,��ǰ�涼��ǰ��0,��odd even flag������Ϊ0
                ans+=dfs(k-1,0,0,0,limit && i == last);
            //����ż��,Ҫ��֤֮ǰ��������������Ϊż��,0%2ҲΪ0,���Բ������ж�!odd,����oddҪ������0
            else if(odd%2 == 0)//����ǰ�����־flag���ܼ̳�֮ǰ��flag,i���ܲ�Ϊ0,��ʱҪ����Ϊ1,����flagҪ��Ϊ1,��ʱ����1 wa������þ� --
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
