/*
����:Matrix67Ҫ���¸��½�����ʦnƪ����,���ĵ����ݿ��Դ�m��������ѡ��.
���ڿ���������,Matrix67���ò��ظ�ѡ��һЩ����.��ɲ�ͬ���������������ʱ�䲻ͬ.
�����˵,����ĳ������i,�� Matrix67�ƻ�һ��дxƪ����,����ɸÿ���������ܹ���Ҫ
���� a[i]*x^b[i] ��ʱ�䵥λ������ÿһ���������Ӧ��a[i]��b[i]��ֵ,�����Matrix67
��������ѡ�����ĵĿ���ʹ�������Ի������ٵ�ʱ�������nƪ����.
����:https://www.luogu.com.cn/problem/P1336
˼·:����ÿ���������ѡ�����1ƪ���ġ�2ƪ���ġ�...��nƪ����,ֻ��ѡȡ����һ������,
���԰��տ������,ÿ����Ʒ�ǿ���������ĵ�����1~n.
*/
//ac 37ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 21
#define M 210
typedef long long ll;
using namespace std;

int n,m,a[N],b[N];
ll dp[M];

ll cal(int x,int b){
    ll tp=1;
    for(int i=1;i<=b;i++)
        tp*=x;
    return tp;
}

int main(){
    memset(dp,0x3f,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&a[i],&b[i]);
    dp[0]=0;
    for(int i=1;i<=m;i++){
        for(int j=n;j>=1;j--){
            for(int k=1;k<=j;k++)
                dp[j]=min(dp[j],dp[j-k]+a[i]*cal(k,b[i]));
        }
    }
    printf("%lld",dp[n]);
    return 0;
}
