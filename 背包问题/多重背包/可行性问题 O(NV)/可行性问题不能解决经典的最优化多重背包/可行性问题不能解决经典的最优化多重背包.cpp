//����������O(nv)���ܽ����������Ż����ر���

/*
һ���Լ������
����ȫ������˵�����Ʒ������Ϊ�������Ƶ�,����ܱ�֤�����ı����ݻ�����ת��
���һ���������ŵ�.

���Ƕ��ر��������Ʒ�����ڸտ�ʼ ���ݻ���Сʱ��Ʒ������û��������,
������������i����Ʒ�ܹ��õ����ŵĽ�����ȷ��,����һ�����󱳰��ݻ�Խ��
dp[j]<dp[j-w[i]]+val[i]�ٴη����i����Ʒ�������ܸ��ŵ�,�����������i��
��Ʒ�������������Ѿ������ٷ�����,Ҳ�������dp[j]����Ҫ����ǰi����Ʒ��dp[j-1]
��ǰi-1����Ʒ��dp[j]�����ĸ�����,���Ǽ�ʹ������ ��Ȼ����������,����֮����01����
��˼ά�Ǳ����ݻ�����,���ܿ���ȫ������,������������������Ʒ��������,�����
������������,��������Ҫ���ǵ������ѵ�i����Ʒ����ܶ����ʱ��,���Ѿ���֮ǰ��
dp[0..j]ǰi-1����Ʒ��״̬�ı���,����һά����ʹ���,���Ǹ�ɶ�ά����Ҳ���Ǵ��.

֪������ ���ѵ����:
"������ÿ��λ�ö����⿪һά��¼��������൱�ڡ�̰�ġ���"
leetcode ���紨�����:
"��Ϊ�㲻֪��f[i][j-v]�ǲ����Ѿ������˵�i����Ʒ.���������,f[i][j]�Ͳ��ܴ�f[i][j-v]ת�ƹ�����."
*/
//���������Լ���ά��������� ���ֻ��ˮ��AcWing�Ǹ����ر�����ˮ��
//����:https://www.acwing.com/problem/content/description/4/
//ʵ������������Ǵ��
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 110
#define M 110
using namespace std;

int n,v,w[N],val[N],num[N],dp[N][M],sum[M];

int main(){
	int T;
	//scanf("%d",&T);
	//while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
        for(int i=1;i<=n;i++){
            memset(sum,0,sizeof(sum));
            for(int j=0;j<=v;j++)
                dp[i][j]=dp[i-1][j];
            for(int j=w[i];j<=v;j++){
                if(dp[i][j]<dp[i][j-w[i]]+val[i]){
                    if(sum[j-w[i]]+1<=num[i]){
                        dp[i][j]=dp[i][j-w[i]]+val[i];
                        sum[j]=sum[j-w[i]]+1;
                        //printf("dp[%d]+val[%d]=%d dp[%d]=%d sum[%d]=%d\n",j-w[i],i,dp[j-w[i]]+val[i],j,dp[j],j,sum[j]);
                    }
                    else{
                        if(dp[i-1][j-w[i]]+val[i]>max(dp[i][j],dp[i][j-1])){
                            dp[i][j]=dp[i-1][j-w[i]]+val[i];
                        }
                        else{

                        if(dp[i][j]<dp[i][j-1]){
                            dp[i][j]=dp[i][j-1];
                            sum[j]=sum[j-1];
                    //printf("dp[%d]+val[%d]=%d dp[%d]=%d sum[%d]=%d\n",j-w[i],i,dp[j-w[i]]+val[i],j,dp[j],j,sum[j]);
                        }
                        }
                    }
                }
            }
        }
        printf("%d\n",dp[n][v]);
    //}
    return 0;
}
