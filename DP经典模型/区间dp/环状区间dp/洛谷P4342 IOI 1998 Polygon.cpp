#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;

/*
����:����һ�������,ÿ�����϶�һ�������(�ӷ���˷�),ÿ���������и�����,
��ʼʱ��ɾ��һ���ߵ�����,֮���������������ϲ�Ϊһ������,ֱ��ֻʣ��һ������ʱ,
�����յ��������ö�������ֵ,����������Ļ��� ��ʼʱɾ���������ܻ��.
����:https://www.luogu.com.cn/problem/P4342
˼·:��ʵ���ǻ�״��ʯ�Ӻϲ�,��Ҫ����������2��,��ʼɾ���ı�ʵ���Ͼ��ǽ���״�п�,ת������ʽ����,
ѡ���ĸ���ʽ����[i,i+n-1]����ֵ,���������ֵʱ,�ӷ��Ĳ����Ƚϼ�,���˷���״̬ת��,��Ϊ���ڸ���
�������������,��˳˷����ֵ�����֮ǰ״̬�����ֵ�йػ�����Сֵ�й�,��dp1[1][j]Ҳ��������
dp2[i][k]*dp2[k+1][j],dp1[i][k]*dp2[k+1][j],dp2[i][k]*dp1[k+1][j]ת�ƶ���.��Сֵ��ת��Ҳ�����ֵ�й�.
���ڳ˷��ķ���ʵ����9�����,���ܽ�����״̬ת��ֻ��4������.
*/

char a[110];
int dp1[110][110],dp2[110][110],b[60],n;

int main(){
    int ans=-1;
    memset(dp1,-INF,sizeof(dp1));
    memset(dp2,INF,sizeof(dp2));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        cin >> a[i] >> b[i];
        dp1[i][i]=dp1[i+n][i+n]=b[i];
        dp2[i][i]=dp2[i+n][i+n]=b[i];
        a[i+n]=a[i];
    }
    for(int l=1;l<n;l++){
        for(int i=1;i+l<2*n;i++){
            int j=i+l;
            for(int k=i;k<j;k++){
                if(a[k+1] == 't'){//�ӷ�����ת��
                    dp1[i][j]=max(dp1[i][j],dp1[i][k]+dp1[k+1][j]);//���ֵֻ�����ֵ�й�
                    dp2[i][j]=min(dp2[i][j],dp2[i][k]+dp2[k+1][j]);//��Сֵ֮����Сֵ�й�
                }
                else{//�˷�����ת�� ���ֵ��ת�ƺ����ֵ ��Сֵ���й���
                    dp1[i][j]=max(dp1[i][j],max(dp1[i][k]*dp1[k+1][j],max(dp2[i][k]*dp2[k+1][j],max(dp1[i][k]*dp2[k+1][j],dp2[i][k]*dp1[k+1][j]))));
                    dp2[i][j]=min(dp2[i][j],min(dp1[i][k]*dp1[k+1][j],min(dp2[i][k]*dp2[k+1][j],min(dp1[i][k]*dp2[k+1][j],dp2[i][k]*dp1[k+1][j]))));
                }
            }
        }
    }
    for(int i=1;i<n;i++)//�жϿ�ʼɾ�������ߵ����ֵ���
        ans=max(ans,dp1[i][i+n-1]);
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)//���ɾ���ı�
        if(dp1[i][i+n-1] == ans)
            printf("%d ",i);
    return 0;
}
