/*
����:���һ�����дγ����������еĵĳ���
���г���<=1000.
����:https://acm.hdu.edu.cn/showproblem.php?pid=5087
˼·:�����ж�����������,��ô�γ�������ĳ���,���
���������ֻ��Ψһ��һ��,��ô�γ�����ԭ����Ļ����ϼ�1.
*/
//ac 93ms
#include<cstdio>
#include<algorithm>
#define N 1100
using namespace std;

//num[i]��¼��a[i]��β�����ֵ�LIS�ĸ���
int n,a[N],dp[N],num[N],ans,sum;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=1;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++){
            dp[i]=num[i]=1;//��ʼֵΪ1
            for(int j=1;j<i;j++){
                if(a[j]<a[i]){
                    if(dp[i]<dp[j]+1){
                        dp[i]=dp[j]+1;
                        num[i]=num[j];
                    }
                    else if(dp[i] == dp[j]+1)
                        num[i]+=num[j];
                }
            }
            ans=max(ans,dp[i]);
        }
        sum=0;
        for(int i=1;i<=n;i++){
            if(ans == dp[i])
                sum+=num[i];
        }
        if(sum!=1)//����д��sum>1 �ͻ�wa,��֪��ԭ��
            printf("%d\n",ans);
        else
            printf("%d\n",ans-1);
    }
    return 0;
}

