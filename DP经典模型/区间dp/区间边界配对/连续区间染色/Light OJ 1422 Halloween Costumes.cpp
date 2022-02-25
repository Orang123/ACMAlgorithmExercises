#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

/*
����:n����� ��˳��μ�,ÿ�����Ҫ���ض���ɫ���·�,�·��������Ÿ����Ŵ�,
����һ���·�һ�����¾Ͳ����ٴ�����(��ָ����·�,������������ɫ���·�),�ʰ�
˳��μ��������������Ҫ�����ټ��·�.
����:http://lightoj.com/volume_showproblem.php?problem=1422
˼·:��ʵ����CQOI2007Ⱦɫ��Ŀ���˸�����,һ���Ż�,�������i<j���Ҫ�󴩵��·���ɫ��ͬ��a[i]==a[j],
��ôij������������ֻ��һ��������ɫ���·�,���԰�����·�������ײ�,�����i���������,���ڽ���
���������Ҫʲô��ɫ���·�����������,�����j���,�Ǽ�a[i]���·���Ȼ�������²�,����������ɫ���·�
��ֻ����һ��.dp[i][j]����i~j��������贩�������������·�
*/

int a[110],dp[110][110],n;

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int l=0;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                dp[i][j]=dp[i+1][j]+1;//���Ի���a[i]��a[k]û���·���ɫ��ͬ,�򵥶��ٴ�һ��a[i]��ɫ���·�
                for(int k=i+1;k<=j;k++)
                    if(a[i] == a[k])//��i����k��ᴩ����ɫ��ͬ,��ô������ɫ���·������ظ�����,����������ײ�,����ֻ��ֻ����dp[i+1][k]��k��������·�
                        dp[i][j]=min(dp[i][j],dp[i+1][k]+dp[k+1][j]);
            }
        }
        printf("Case %d: %d\n",cas,dp[1][n]);
    }
    return 0;
}

/*
dp[i][j]=dp[i][j-1]+1;
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int a[110],dp[110][110],n;

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int l=0;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                dp[i][j]=dp[i][j-1]+1;
                for(int k=i;k<j;k++)
                    if(a[j] == a[k])
                        dp[i][j]=min(dp[i][j],dp[i][k-1]+dp[k][j-1]);
            }
        }
        printf("Case %d: %d\n",cas,dp[1][n]);
    }
    return 0;
}
*/

/*
dp[i][j]=min(dp[i+1][j],dp[i][j-1]);
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int a[110],dp[110][110],n;

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            dp[i][i]=1;
        for(int l=1;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                if(a[i] == a[j])
                    dp[i][j]=min(dp[i+1][j],dp[i][j-1]);
                else{
                    for(int k=i;k<j;k++)
                        dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
                }
            }
        }
        printf("Case %d: %d\n",cas,dp[1][n]);
    }
    return 0;
}
*/





