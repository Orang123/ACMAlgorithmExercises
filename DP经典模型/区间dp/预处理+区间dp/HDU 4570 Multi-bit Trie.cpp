#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

/*
����:����һ������Ϊn�����У�����ֳ����ɶΣ�Ҫ������ֶ�����ֵ*2^(�ֶ������ֵ����)�ۼ���С��
ͬһ�ε��� Ҫ<=20��.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4570
˼·:dp[i][j]����i~j�ڷֳ����ɶ���͵���Сֵ
*/
ll dp[70][70],a[70],n,sum[70];

ll cal(int j){
    int tmp=1;
    for(int i=1;i<=j;i++)
        tmp*=2;
    return tmp;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%lld",&n);
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
            sum[i]=sum[i-1]+a[i];
        }
        //״̬ת��Ӧ����С����ת�Ƶ������� ����ʼ����С������ʱ,����һ���Ӷο��������ⳤ��,Ҫ��Ϊ<=20��>20,2�����
        for(int i=1;i<=n;i++){
            for(int j=i;j<=n;j++){
                if(j-i+1<=20)
                    dp[i][j]=a[i]*cal(j-i+1);
                else//������20Ĭ��ÿ����������һ��,������ŷֶλ���dp�ָ�����ʱ����
                    dp[i][j]=(sum[j]-sum[i-1])*2;
            }
        }
        for(int l=1;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                for(int k=i;k<j;k++)//�ָ�����Ĺ���ʵ�ʾ��ǲ��ϻ��ֶ��������ֵ�Ĺ���.���׷ֳɼ�����Ŀû��Ҫ��ֻҪ�������ֵ
                    dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
            }
        }
        printf("%lld\n",dp[1][n]);
    }
	return 0;
}
