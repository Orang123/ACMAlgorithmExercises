#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;
int dp[110][110],a[110];
/*
����:�˷���Ϸ����һ������ģ�ÿһ���ƶ�����һ�������������ƶ������У�
��Ҵ�һ������ȡ��һ���ƣ��÷ֵ�����ѡ���ϵ�������������������������ֵĳ˻���
������ȡ����һ�ź����һ���ơ����һ�й�����һ��ֻʣ�������ơ�
ÿ��ȡ��,��֤�����඼�����Ƶ�.
ע��:��HDU 5115 ��ͬ����,ֽ����Ҫ���µ�1���ƺ����һ����,��HDU 5115���ǿ���ȫ��ɱ����
����:http://poj.org/problem?id=1651
˼·:��һ��ȡ��ʱ��һ����ԭ�ȵ�����������������,������С����״̬����������������ȡ�м��Ǹ������,
Ȼ�󲻶�ת�Ƶ�������,ö������ķָ��k,dp[i][j]=dp[i][k]+dp[k][j]+a[i]*a[k]*a[j],�����k��֮ǰ������״̬�ı߽��,
�ٺͱ���������,����dp[i][k]��dp[k][j]�м�������ϸ�����len��ö�����Ѿ����Ϳ�,���ų������ӣ���Խ��Խ����.

�����⻹��ת���ɾ�����������.
*/

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int l=2;l<n;l++){
        for(int i=1;i+l<=n;i++){
            int j=i+l;
            dp[i][j]=INF;
            for(int k=i+1;k<j;k++){
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]+a[i]*a[k]*a[j]);
            }
        }
    }
    printf("%d",dp[1][n]);
	return 0;
}
/*
����dp ö�����Ҷ˵�ת��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;
int dp[110][110],a[110];

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=n-2;i>=1;i--){
        for(int j=i+2;j<=n;j++){
            dp[i][j]=INF;
            for(int k=i+1;k<j;k++){
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]+a[i]*a[k]*a[j]);
            }
        }
    }
    printf("%d",dp[1][n]);
	return 0;
}
*/
/*
���仯����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;
int dp[110][110],a[110];

int dfs(int st,int ed){
    if(ed-st==1) return 0;//��С��������ǵ�һ��ȡ��������������,������������2��������0,��һ��dfs����������������
    if(dp[st][ed]!=INF) return dp[st][ed];
    for(int i=st+1;i<ed;i++)//���ȷָ������,�Ǿ����ȵݹ���С����������
        dp[st][ed]=min(dp[st][ed],dfs(st,i)+dfs(i,ed)+a[st]*a[i]*a[ed]);
    return dp[st][ed];
}

int main(){
    int n;
    memset(dp,INF,sizeof(dp));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    printf("%d",dfs(1,n));
	return 0;
}
*/
