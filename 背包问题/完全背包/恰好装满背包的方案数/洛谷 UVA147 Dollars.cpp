/*
����:�����������ƶȰ���100��Ԫ,50��Ԫ,20��Ԫ,10��Ԫ,
5��Ԫ,2��Ԫ,1��Ԫ,50����,20����,10���ֺ�5����.
��дһ������ȷ��,��������һ��Ǯ,���ж����ַ�������������Ǯ
(�ı�����˳����ͬһ��)����20���ֿ�����4�ַ������:1*20,2*10,10+2*5,4*5.

�����ʽҪ��:
ÿ����������ĵ�һ�а�����������(������С��λ,�ڿ��Ϊ6���ֶ����Ҷ���),
������������ɸ������ݵķ�����,�ڿ��Ϊ17���ֶ����Ҷ���.
����:https://www.luogu.com.cn/problem/UVA147
˼·:��ȫ����ͳ��ǡ��װ��������,��Ϊ�����±겻����С��,����Ҫ�Ƚ�,11�ֻ���
�е���Ԫ��ת�������ּ�������100��.Ȼ�����v��Ҫ��������100��,��Ϊv��С��,
�������ڼ������������Чλ����ָ��λ����,ĳЩ���������ܲ��ܾ�ȷ��ʾ,����456
ʵ�ʴ洢������455.99999,���ֱ�ӳ�100ǿ��ת����int�����455,���Ҫ����0.5
������100��ǿתintȥ��С��λ����Ǳ���v����ʾ��ʵ��������ֵ.
���������и��������ܾ�ȷ��ʾ,ĳЩ������ֻ�ܱ�ʾһ������ֵ.
*/
//ac 0ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 12
#define M 30100
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;

int w[N]={0,10000,5000,2000,1000,500,200,100,50,20,10,5};
ll dp[M];
double v;

int main(){
    memset(dp,0,sizeof(dp));
    dp[0]=1;
    for(int i=1;i<N;i++){
        for(int j=w[i];j<=30000;j++)
            dp[j]+=dp[j-w[i]];
    }
    while(scanf("%lf",&v) && v)
        printf("%6.2f%17lld\n",v,dp[(int)(v*100+0.5)]);
    return 0;
}

/*
//ac 0ms ��ά����ʵ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 12
#define M 30100
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;

int w[N]={0,10000,5000,2000,1000,500,200,100,50,20,10,5};
ll dp[N][M];
double v;

int main(){
    memset(dp[0],0,sizeof(dp[0]));
    dp[0][0]=1;//��ʼ״̬��һ����ƷҲ��װʱ,ֻ�б�������Ϊ0�ǺϷ�״̬ ����dp[0][1..N]���ǲ��Ϸ���,���memset��Ϊ0
    for(int i=1;i<N;i++){
        for(int j=0;j<=30000;j++){
            if(j>=w[i])
                dp[i][j]=dp[i-1][j]+dp[i][j-w[i]];
            else
                dp[i][j]=dp[i-1][j];
        }
    }
    while(scanf("%lf",&v) && v)
        printf("%6.2f%17lld\n",v,dp[11][(int)(v*100+0.5)]);
    return 0;
}
*/
