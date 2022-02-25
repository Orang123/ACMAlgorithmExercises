#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510//500*100=50000
#define M 50100//500*100=50000
typedef long long ll;
using namespace std;
//ac 90ms 01���� �������������ܶ��װ

/*
����:n�ſ�,��i�ſθ�������ֵHi��Ci(������ֶȺ�ѧ��),
����ÿ�ſο���ѡҲ���Բ�ѡ,���Ҫ����һ�����,����㹫ʽ��ͼ,
����m������ѡ�Ŀ�,�����Ľ��.
Hi֮�͵�ƽ��-Hi֮��*Ci֮��-Ci֮�͵�ƽ��
����:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827370070
˼·:�ο�����:https://blog.csdn.net/u011815404/article/details/89761481
����C[i]�����ݷ�Χ,c[i]<=500,��h[i]<=10000,��������ʽ���к�����h[i]֮��
������ȡֵռ��������,���ֵ���Ciһ����ʱ��HiԽ��Խ��,�����Ļ����ǿ���ֱ�Ӱ���Ŀ
ת����һ��01��������ȥ���.����C[i]һ��ʱ,��λ�����ġ�Hi.�������пγ̵�Ci֮��
��Ϊ�����ݻ�,�γ̿��ֶ���Ϊ��Ʒ��ֵ.�����C[i]һ��ʱӦ�����ܶ��ѡ��γ̵�h[i]
֮��,����δװ��������,��˱������������ܶ��װ��.��Ҫԭ��Ҳ��Hi֮��̫��Ҳû����Ϊ
��������.

�ο�����:https://blog.csdn.net/u011815404/article/details/89761481
�������:res=-C^2+H(H-C)����Ϊ�������µ�������,��ֻҪ�� H(H-C)�����󼴿�
��H(H-C)����,��:H(H-C)=H^2-HCҪʹH^2-HC��ô��Ҫ��H^2������,HC����С,����H
������,C����С.

//��ʵӦ����ǡ��װ������,����������Ҳ�����,��Ϊ�����ܶ��װ��,i��ƫ��,�����ʽ�������Ҳֻ���С,����Ӱ��𰸵���ȷ��.
*/

ll n,c[N],h[N],dp[M],sum;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&h[i],&c[i]);
            sum+=c[i];
        }
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=c[i];j--)
                dp[j]=max(dp[j],dp[j-c[i]]+h[i]);
        }
        ll ans=0;//dp[i]*dp[i]-dp[i]*i-i*i�Ƚϴ�
        //����ڸ�������ѡ��γ�ѧ��֮��(��������)��,����ܻ�õĿ��ֶ�h[i]֮�ͼ�dp[i]
        for(int i=0;i<=sum;i++)//��Ȼdp[i]���ܲ�δװ��,��dp[i]����ʵ�ʸ����γ̵Ŀ��ֶ�֮��
            //��ʵӦ����ǡ��װ������,����������Ҳ�����,��Ϊ�����ܶ��װ��,i��ƫ��,����������Ҳֻ���С,����Ӱ��𰸵���ȷ��.
            ans=max(ans,dp[i]*dp[i]-dp[i]*i-i*i);//max �������������ͱ���һ��
        printf("%lld\n",ans);
    }
    return 0;
}

/*
//ac 59ms 01���� ����ǡ��װ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510//500*100=50000
#define M 50100//500*100=50000
typedef long long ll;
using namespace std;

ll n,c[N],h[N],dp[M],sum;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&h[i],&c[i]);
            sum+=c[i];
        }
        dp[0]=0;//ֻ��dp[0]=0,���඼��-INF
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=c[i];j--)
                dp[j]=max(dp[j],dp[j-c[i]]+h[i]);
        }
        ll ans=0;
        //����ڸ�������ѡ��γ�ѧ��֮��(��������)��,����ܻ�õĿ��ֶ�h[i]֮�ͼ�dp[i]
        for(int i=0;i<=sum;i++){
            if(dp[i]>0)
                ans=max(ans,dp[i]*dp[i]-dp[i]*i-i*i);//max �������������ͱ���һ��
        }
        printf("%lld\n",ans);
    }
    return 0;
}
*/
