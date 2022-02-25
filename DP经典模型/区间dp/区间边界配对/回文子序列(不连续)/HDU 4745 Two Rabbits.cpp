#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
/*
����:����һ�����У���ֻ���ӷֱ�˳ʱ�롢��ʱ���ߣ�
ͬһʱ�����ǵ���ʯͷ�ϵ���ֵҪ��ͬ�����ܻص����,������߹�����ʯͷ��
����:http://acm.hdu.edu.cn/showproblem.php?pid=4745
˼·:����dp��⻷״����������г���.
dp[i][j]��ʾ����[i,j]������������еĳ���.
ʵ�ʾ�����⻷״�������������,�ͻ�״ʯ�Ӻϲ�����һ��,����������2n.
ֻ��Ҫע����ֻ�����п���һ��ʼ����ͬһ���,����0ʱ��ʯͷ��ֵ������ͬ��,
������������õ�������,dp[i+n-2]+1,��ʾ��ͬһ��㵥������һ��,ֻ���ǳ���Ϊn-1
����������������г���.
*/
int a[2100],dp[2100][2100];

int main(){
    int n;
    while(scanf("%d",&n)&&n){
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            a[i+n]=a[i];
            dp[i][i]=dp[i+n][i+n]=1;
        }
        for(int l=1;l<n;l++){
            for(int i=1;i+l<2*n;i++){
                int j=i+l;
                if(a[i] == a[j])
                    dp[i][j]=dp[i+1][j-1]+2;
                else
                    dp[i][j]=max(dp[i][j-1],dp[i+1][j]);
            }
        }
        int ans=1;
        for(int i=1;i<n;i++){
            ans=max(ans,dp[i][i+n-1]);//��ֻ������㲻ͬ dp[i][i+n-1]����Ϊn����
            ans=max(ans,dp[i][i+n-2]+1);//dp[i][i+n-2]+1 ��ֻ����0ʱ�������ͬ,ֻ���ǳ���Ϊn-1����
        }
        printf("%d\n",ans);
    }
    return 0;
}
