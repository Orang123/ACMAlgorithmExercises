#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;

/*
����:��һЩ�ǣ����������У�ÿֻ����һ���˺���ɱ��һֻ�ǵ�ʱ��
���ܵ���ֻ�ǵ��˺�����ֻ���������ߵ��ǵĶ����˺��ĺ͡�����ֻ��֮
����Ƕ���ɱ�ˣ�����ֻ�Ǿͳ��µ������ǡ���ɱ��һ���ǵ���С���ۡ�
ɱ��һֻ������������ǿ��ܲ�����,�����˺���Ϊ0.
ע��:��POJ 1651 ��ͬ����,���ǿ���ȫ��ɱ����,��POJ 1651 ��Ҫ���µ�1���ƺ����һ����
����:http://acm.hdu.edu.cn/showproblem.php?pid=5115
˼·:����dp,dp[i][j]���� ɱ��i~j����Ⱥ���ܵ�����С�˺�
*/
int n,a[210],b[210],dp[210][210];

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&b[i]);
        b[n+1]=0;//����n+1��λ��Ҫ����Ϊ0,����������ǰ���n�ϴ�,�����С,b[n+1]λ�õ�ֵ�ͻ�Ӱ�������ǵĶ��⹥��ֵ
        for(int i=1;i<=n;i++)
            for(int j=i;j<=n;j++)
                dp[i][j]=INF;//��ʼ��,ֵ��ʼ��j>=iʱ��ֵΪINF,i>j��ֵΪ0,����dp״̬ת�Ƽ���
	//��һ��ɱ���ǳ�ʼ״̬���� l=0��ʱ��,���ɱ������l=n-1��ʱ��
        for(int l=0;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                for(int k=i;k<=j;k++)//ö�ٶ�����Ⱥ[i,j]����ֻ��Ϊ����Ҫɱ����,������ֳ�������[i,k-1] [k+1,j] ����dp[i][j] i>jʱֵΪ0,�������
                    //dp[i][k-1] dp[k+1][j]�е��Ƕ���֮ǰdp��״̬�Ѿ���ɱ��
                    dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k+1][j]+a[k]+b[i-1]+b[j+1]);
            }
        }
        printf("Case #%d: %d\n",cas,dp[1][n]);
    }
    return 0;
}


