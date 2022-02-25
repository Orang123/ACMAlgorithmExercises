/*
����:��k�����͵Ĺ��ߵļ۸�ֱ�Ϊ1~k,ÿ�ֹ��������޸��ɳ���,
������nԪǮ,���ж����ַ�ʽ�ܽ�nԪǮ����.
����:http://poj.org/problem?id=3181
˼·:��ȫ����ͳ�Ʒ�����
ֻ������Ϊ n=1000,k=100ʱ,ʵ�ʽ����:15658181104580771094597751280645
��32λ��,��long long�����ΧΪ9223372036854775807 ��19λ��,������Ҫ
�߾��ȼӷ�,������������dp����,dp1��ʾ��λ,dp2��ʾ��λ.��Ϊ��λdp1���
ֻ�ܷ�19λ��,���Ե�λdp2������Ҫ��32-19=13λ��.ʵ��ת��ʱ ֻ��ʼ����λ
dp2[0]=1,��λdp1�ǵ�λ��Ӻ�����Ľ�λ,��:dp1[j]=dp1[j]+dp1[j-i]+(dp2[j]+dp2[j-i])/INF;
����λ��dp2[j]=(dp2[j]+dp2[j-i])%INF,��Ӻ�������������ĵ�λ���.
��:(65+79)/100=1 (65+79=144)%100=44 ���Լ���INF=1e18,��ô��λʵ����ӽ���Ͳ��ܳ���19λ
��,����ʱ����λ���ڸ�λ��,�����ĵ�λ����ڵ�λ��.
*/
//ac 16ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define M 1100
typedef long long ll;
const ll INF=1e18;//���ｫ��λ�����ܶ�ط� ����19λ��
using namespace std;

int n,k;
ll dp1[M],dp2[M];

int main(){
    memset(dp1,0,sizeof(dp1));
    memset(dp2,0,sizeof(dp2));
    scanf("%d%d",&n,&k);
    dp2[0]=1;
    for(int i=1;i<=k;i++){
        for(int j=i;j<=n;j++){
            //û�н�λʱdp1���鼴:dp2[j]+dp2[j-i]<INFʱ,��λΪ0,ֻ��dp2��λ��ֵ,
            dp1[j]=dp1[j]+dp1[j-i]+(dp2[j]+dp2[j-i])/INF;
            dp2[j]=(dp2[j]+dp2[j-i])%INF;
        }
    }
    if(dp1[n])//�и�λ�������λ
        printf("%lld",dp1[n]);
    printf("%lld\n",dp2[n]);
    return 0;
}
