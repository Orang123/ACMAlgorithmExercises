/*
����:��a�����b��������������������(LCIS).
���鳤��<=500.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1423
˼·:O(n^2)��ȡLCISģ��.
dp[i][j]Ϊ����aȡǰi��Ԫ��ʱ(��Ϊa[1 ~ i]),�ҵ���b����������j��βʱ,���ǵ�����������г���.
dp[i][j]>=dp[i-1][j].
���鳤��Ϊ500,������O(n^3)��������TLE�Ŷ�,����Ҳ����.
�㷨�ο�����:https://blog.csdn.net/lycheng1215/article/details/78343769
*/
//ac 0ms LCIS ��ά����ʵ�� O(n*m)
//dp[i][j]Ϊ����aȡǰi��Ԫ��ʱ(��Ϊa[1 ~ i]),�ҵ���b����������j��βʱ,���ǵ�����������г���.
//dp[i][j]>=dp[i-1][j]
#include<cstdio>
#include<algorithm>
#define N 510
using namespace std;

int n,m,a[N],b[N],dp[N][N],ans;

int main(){
    int T,mx;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%d",&b[i]);
        for(int i=1;i<=n;i++){
            mx=0;//��¼����dp[i-1][1..j]��ֵ
            for(int j=1;j<=m;j++){
                dp[i][j]=dp[i-1][j];
                if(a[i]>b[j])//��¼������j��β֮ǰ���ַ���LIS
                    mx=max(mx,dp[i-1][j]);
                else if(a[i] == b[j])//������LCSʱ,dp[i][j]=֮ǰ��¼��j֮ǰ������LIS
                    dp[i][j]=mx+1;
            }
        }
        ans=0;
        for(int i=1;i<=m;i++)//��¼���LCIS,a�����ǰn��Ԫ��,ö��b������b[i]��β��LCIS ��¼��󳤶�
            ans=max(ans,dp[n][i]);
        printf("%d\n",ans);
        if(T)
            printf("\n");
    }
    return 0;
}

/*
//ac 0ms O(n*m) ���������Ż�,һά����ʵ��
//��Ϊdp[i][j]����ȡ֮��dp[i-1][j]�й�,��˵�һ��ά�ȿ���ʡ��,ֻ��Ҫ��ʼ��dpһά����,�����������,��һ�εĽ����Ӱ����һ�εĽ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
using namespace std;

int n,m,a[N],b[N],dp[N],ans;

int main(){
    int T,mx;
    scanf("%d",&T);
    while(T--){
    	memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%d",&b[i]);
        for(int i=1;i<=n;i++){
            mx=0;
            for(int j=1;j<=m;j++){
                if(a[i]>b[j])
                    mx=max(mx,dp[j]);
                else if(a[i] == b[j])
                    dp[j]=mx+1;
            }
        }
        ans=0;
        for(int i=1;i<=m;i++)
            ans=max(ans,dp[i]);
        printf("%d\n",ans);
        if(T)
            printf("\n");
    }
    return 0;
}
*/

/*
//ac 0ms ��ά����O(n*m^2)��������
//���鳤��Ϊ500,������O(n^3)��������TLE�Ŷ�,����Ҳ����.
//dp[i][j]Ϊ����aȡǰi��Ԫ��ʱ(��Ϊa[1 ~ i]),�ҵ���b����������j��βʱ,���ǵ�����������г���.
//dp[i][j]>=dp[i-1][j]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
using namespace std;

int n,m,a[N],b[N],dp[N][N],ans;

int main(){
    int T,mx;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%d",&b[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
            	dp[i][j]=dp[i-1][j];//dp[i][j]>=dp[i-1][j]
            	if(a[i] == b[j]){//���ʱ,˵������LCS,�ж����Ƿ񹹳�LIS
            		for(int k=0;k<j;k++){//k���½�Ҫ��0��ʼ,Ҫ��Ȼ���b���鶼�ǽ���,���޷��õ�����Ϊ1��LCIS
            			if(b[k]<b[j])//��¼����LIS
            				dp[i][j]=max(dp[i][j],dp[i-1][k]+1);
					}
				}
            }
        }
        ans=0;
        for(int i=1;i<=m;i++)//��¼���LCIS,a�����ǰn��Ԫ��,ö��b������b[i]��β��LCIS ��¼��󳤶�
            ans=max(ans,dp[n][i]);
        printf("%d\n",ans);
        if(T)
            printf("\n");
    }
    return 0;
}
*/
