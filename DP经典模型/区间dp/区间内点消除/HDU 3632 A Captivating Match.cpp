#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

/*
����:�ų�һ�е�n����ʿ,ÿ����������ļ�ֵ(������ͬ),�������ڵ�2�����ɽ��б���,
���˵Ļ��˳�����,����a.b.c,d  b��c���б���bӮ���˱��������abd,b��a��d����.
����������ʿ��(��һ������)�ı����Ľ��������Ĵ洢�����Ѹ���,��mp[i][j]=1����i��j���б���,i��Ӯ.
�����ھ���ֵ����Ƕ���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3632
˼·:dp[i][j]=1������ʿi����ʿj���ڿɽ��б���,i j֮�����ʿ�Ѿ���Ϊ���˱������˳���.
*/
int dp[110][110],a[110],mp[110][110];

int main(){
    int T,n,cas=0,ans;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        for(int i=1;i<=n;i++)
            //���� 2����ڵ�0��n+1������ʾ�����Ƿ�ֻ��ʣ��ĳһ����ʿ,0��n+1���κ���ʿ����������Ӯ,Ϊ�˱���dpʱ�жϴ���.
            mp[0][i]=mp[n+1][i]=0;
        for(int i=0;i<=n;i++)
            dp[i][i+1]=1;//��ʼʱ�������ڵ�2�����ɽ��б���,����2����ڵ�
        for(int l=2;l<=n+1;l++){//��Ϊ��ʼ״̬����Ϊ2�Ѿ�����,������㳤��Ϊ3������
            for(int i=0;i+l<=n+1;i++){
                int j=i+l;
                for(int k=i+1;k<j;k++){//k���ܺ�i j��ͬ,��ʿ�Լ����ܺ��Լ�����
                    if(dp[i][k] && dp[k][j]){//�� i����k���� �� k����j���� dp[i][k]��dp[k][j]����һ״̬,i~k k~j�м����ʿ�Ѿ��˳�
                        if(mp[i][k] || mp[j][k])//��i��Ӯk  ��j��Ӯk ������i�ͻ���j���ڿɽ��б���
                            dp[i][j]=1;
                    }
                }
            }
        }
        ans=-1;
        for(int i=1;i<=n;i++)
            //ö��1~n����ʿi �ж�1~i����ʿ������i~n����ʿ�����Ƿ�ֻ��ʣ�µ�i����ʿ ���μ�¼���ܵ�����ֵ
            if(dp[0][i] && dp[i][n+1] && a[i]>ans)
                ans=a[i];
        printf("Case %d: %d\n",cas,ans);
    }
    return 0;
}

/*
dp[i][j]��¼i~j֮����ʿ����,����ʣ�µ�����ֵ��ʿ�ı��
��ͬ��ʿ��ֵ����ȵ�ʱ������ ����������
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int dp[110][110],mp[110][110],val[110],n;

int main(){
    int T,cas=0,a,b,c;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        cas++;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        for(int i=1;i<=n;i++){
            dp[i][i]=i;
            if(mp[i][i+1]) dp[i][i+1]=i;
            else dp[i][i+1]=i+1;
        }
        for(int l=2;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                for(int k=i;k<j;k++){
                    a=dp[i][k],b=dp[k+1][j];
                    c=dp[i][j];
//��val[a]==val[c],��ʱdp[i][j]ȡa��ȡ֮ǰ��c,���a��ʿ��c��ʿ����������ʤ�ߵı�����ϵ�ǲ�ȷ����,
//����Ӱ������ʣ�µ���ʿ,���Լ�ֵҲ�Ͳ�һ����������,��˴���
                    if(mp[a][b] && val[a]>val[c])
                        dp[i][j]=a;
                    else if(!mp[a][b] && val[b]>val[c])
                        dp[i][j]=b;
                }
            }
        }
        printf("Case %d: %d\n",cas,val[dp[1][n]]);
    }
    return 0;
}
*/
