/*
����:
��������������l��r,����[l,r]�е�����������,ÿ������(digit)�������˶��ٴ�.
1<=l,r<=10^12.
ע��:����11,1������2��.
����:https://www.luogu.com.cn/problem/P2602
˼·:��λdp,ע������ǰ��0��Ӱ�쵽 ���仯�������ж�,
��˼��仯����Ҫ����Ϊ3��ά��,��ǰ��λk,digit��λ���ִ���num,
����ǰ��0 lead.
����:num=0�����,��ǰ��0 num��Ϊ0��,����û��ǰ��0,��λiû��һ��
��digit,numҲ��Ϊ0,�����Ҫ��¼ǰ��0��dp����.
*/
//ac 20ms ���仯����
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
        if(lead){//��ǰ��0
            if(i)//��kλȡ������,û��ǰ��0,lead����Ϊ0,num�Ƿ��1 ȡ�����Ƿ�i�Ƿ����digit
                ans+=dfs(k-1,num+(i == digit),0,limit && i == last);
            else//��kλȡ��,num��ȻΪ0,��Ȼ����ǰ��0,���num=0,lead=1
                ans+=dfs(k-1,0,1,limit && i == last);
        }
        else//û��ǰ��0 lead=0,num�Ƿ��1 ȡ�����Ƿ�i�Ƿ����digit
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
    for(digit=0;digit<=9;digit++){//ö��Ҫ�ж�����λdigit 0~9
        memset(dp,-1,sizeof(dp));
        b[digit]=dfs(len,0,1,1);//��ǰ��0 lead��ʼ����Ϊ1
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
