/*
����:����һ��n,ֻ����ʹ��2���ݴ���,���ж����ֲ�ͬ�ķ������n.
����:http://poj.org/problem?id=2229
˼·:��ȫ����
*/
//ac 422ms ��ȫ����ͳ�Ʒ�����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 21
#define M 1000010
#define mod 1000000000
typedef long long ll;
using namespace std;

int n,val[N],dp[M];

int main(){
    val[0]=1;
    //n���ֻ��10^6,��2��20�η�Ϊ1048576 ������ֻ����㵽2��19�η�,����ֻ�㵽2^19�η���wa,�����ƶ�n���ܴ���10^6
    for(int i=1;i<N;i++)
        val[i]=val[i-1]*2;
    scanf("%d",&n);
    memset(dp,0,sizeof(dp));
    dp[0]=1;
    for(int i=0;val[i]<=n;i++){
        for(int j=val[i];j<=n;j++){
            dp[j]+=dp[j-val[i]];
            if(dp[j]>mod)//ֱ��ȡģ���Ӷ�̫��,����ʱ����mod�ͺ�
                dp[j]-=mod;
        }
    }
    printf("%d\n",dp[n]);
    return 0;
}
