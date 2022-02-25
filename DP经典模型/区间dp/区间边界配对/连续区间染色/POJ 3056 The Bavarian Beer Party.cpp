#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 10007
using namespace std;
/*
����:��ż�����ˣ������˶����뻥�ྴ�ƣ�������ֻ����ͬ��ŵĲ��ܾ��ƣ�
���Ҳ��ܽ��棬������������£����ྴ�Ƶ���������ͬ��������
����:http://poj.org/problem?id=3056
˼·:��������ƥ��,ֻ������������[i,j]�����ж�a[i]==a[j] [xxxx]oooo=xxxx+oooo+1
���Ҳ���ÿ���˶�Ҫ����,���Ҳ��ܽ���,�������䳤�ȱ���Ϊż������
*/
int dp[1100][1100],a[1100],n;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int l=1;l<n;l+=2){//ÿ���˱��뾴��,���ܳ���dp[i][i]�Լ�����������������,��ĳ���˲����Ƶ����
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                dp[i][j]=dp[i+1][j];//��ʼ��dp[i+1][j]
                for(int k=i+1;k<=j;k+=2){//�ж�a[i]��a[k] (k>=i+1 k<=j) k������ͬ��Ҳ��ż������,������붼Ϊż������
                    if(a[i] == a[k])//ÿ���˾��Ʋ��ܽ���,����i k�߽�ָ����� ����� ���Ӷ�����Ҫ+1
                        dp[i][j]=max(dp[i][j],dp[i+1][k-1]+dp[k+1][j]+1);
                    else//�������,Ҳ���� ֻ������ͳ��������ͬ�ĸ���
                        dp[i][j]=max(dp[i][j],dp[i+1][k-1]+dp[k+1][j]);
                }
            }
        }
        printf("%d\n",dp[1][n]);
    }
	return 0;
}

/*
dp[i][j]=dp[i+1][j-1]+1
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 10007
using namespace std;
int dp[1100][1100],a[1100],n;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int l=1;l<n;l+=2){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                if(a[i] == a[j])
                    dp[i][j]=dp[i+1][j-1]+1;
                else//����� Ҳ���� ֻ������ͳ�����ӵĶ���
                    dp[i][j]=dp[i+1][j-1];//a[i]��a[j]����� ��ʼ��Ϊdp[i+1][j-1],�����ƾ����ķָ����� �⼯���ǲ���ȫ
                for(int k=i+1;k<j;k+=2)
                    dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]);
            }
        }
        printf("%d\n",dp[1][n]);
    }
	return 0;
}
*/

