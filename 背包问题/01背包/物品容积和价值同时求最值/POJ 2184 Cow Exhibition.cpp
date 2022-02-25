#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 200001
#define INF -0x3f3f3f3f
using namespace std;
//ac 391ms 01��������Ϊ���� ƽ����������Ϊ����,ǡ��װ������
//��������Ϊs[i]֮��,��Ʒ��ֵΪf[i]
/*
����:����nͷ��ţ,ÿͷ��ţ�и�����ֵs[i]��һ����Ȥֵf[i].���������
ȡ������ͷ��ţ,ʹ����Щ��ţ��s[i]+f[i]����ͬʱs[i]���ܺ�>=0,fi��
�ܺ�Ҳ>=0,������ֵ.
1<=n<=100,-1000<=s[i],f[i]<=1000
����:http://poj.org/problem?id=2184
˼·:��ΪҪ�õ������Ⱥ���Ȥֵ֮�͵����ֵ,���Խ�������s[i]֮����Ϊ
�����ݻ�,��Ȥֵf[i]��Ϊ��Ʒ��ֵ,s[i]��Ϊ��Ʒ�ݻ�.��Ϊ������s[i]����
Ϊ����,��:-1000<=s[i]<=1000,100��s[i]֮�͵�������Ϊ[-100000,100000],
�������ݻ�����Ϊ����,��Ϊ�����±겻��Ϊ��,��������������޻������ټ�
100000,��Ϊ[100000,200000],ԭ�ȵĳ�ʼ״̬0��Ϊ100000,����µĳ�ʼ״̬
Ϊdp[100000]=0,�������01����,��s[i]��f[i]֮�͵����ֵΪi+dp[i]-100000.
����ע���s[i]Ϊ����ʱ,dp�����ݻ�jӦ������ö����Ϊj-s[i]>j,������ճ���
����ö��,�����dp[j-s[i]]���ظ��ۼ�,��һ��״̬�ᱻ�ظ�����,��������һ��״̬
�Ѿ�����ǰ�ı���.��Ϊi+dp[i]Ϊs[i]֮�ͼ�f[i]֮��,i��dp[i]��������ʵ�ʵ�������
��ȡֵ,��������Ӧ����ǡ��װ��,�����ܾ����ܶ��װ.
*/
int n,s[N],f[N],dp[M];

int main(){
    memset(dp,INF,sizeof(dp));//��ʼ��������
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&s[i],&f[i]);
    dp[100000]=0;//��ʼ״̬��0��λ��100000
    for(int i=1;i<=n;i++){
        if(s[i]>=0){//s[i]Ϊ����,������������
            for(int j=2e5;j>=s[i];j--)
                if(dp[j-s[i]]!=INF)//ǡ��װ��,�ж���һ״̬�Ƿ�Ϸ�
                    dp[j]=max(dp[j],dp[j-s[i]]+f[i]);
        }
        else{//s[i]Ϊ����,������������,��Ϊ����ᵼ����һ��״̬d[i-1][j]���º� �ٶȱ���Ϊ��һ��״̬,��ʵ�����Ѿ�����ԭʼ����һ��״̬
            //����������s[i]֮�����ٴ�0��ʼ,�����½�0;
            //�����������Ϊ2e5,�����Ͻ�Ϊj-s[i]<=2e5.
            for(int j=0;j-s[i]<=2e5;j++)//j���½粻��Ϊ��,�����½�Ϊ0,��j-s[i]���Ϊ2e5,����j���Ͻ���s[i]+2e5
                if(dp[j-s[i]]!=INF)//j-s[i]>j,��һ��״̬��j-s[i],��s[i]֮�ͽϴ�,��Ϊs[i]������Ǹ���,����ֻ�ǽ�<0�Ĳ���ƽ�Ƶ���ԭ���Ҳ�
                    dp[j]=max(dp[j],dp[j-s[i]]+f[i]);
        }
    }
    int ans=0;
    //s[i]֮�ͱ������0,���Դ�ƫ�ƺ��ԭ��100000��ʼ����,
    for(int i=1e5;i<=2e5;i++){//��Ϊs[i]֮�ʹ�,f[i]֮��Ҳ�п���С,����Ҫ�������н��ȡ���ֵ
        if(dp[i]>0)//dp[i]����f[i]֮��ҪΪ����
            ans=max(ans,i-100000+dp[i]);//��Ϊs[i]֮��ʵ�������ұ�����100000,����ʵ��ֵҪ��ȥ100000
    }
    printf("%d",ans);
    return 0;
}

/*
//ac 422ms �����ݻ�Ϊf[i]֮��,��Ʒ��ֵΪs[i]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 200001
#define INF -0x3f3f3f3f
using namespace std;

int n,s[N],f[N],dp[M];

int main(){
    memset(dp,INF,sizeof(dp));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&s[i],&f[i]);
    dp[100000]=0;
    for(int i=1;i<=n;i++){
        if(f[i]>=0){
            for(int j=2e5;j>=f[i];j--)
                if(dp[j-f[i]]!=INF)
                    dp[j]=max(dp[j],dp[j-f[i]]+s[i]);
        }
        else{
            for(int j=0;j-f[i]<=2e5;j++)
                if(dp[j-f[i]]!=INF)
                    dp[j]=max(dp[j],dp[j-f[i]]+s[i]);
        }
    }
    int ans=0;
    for(int i=1e5;i<=2e5;i++){
        if(dp[i]>0)
            ans=max(ans,i+dp[i]-100000);
    }
    printf("%d",ans);
    return 0;
}
*/

/*
//MLE ģ����ƽƽ�� ��ά�������� ����Կռ���Ҫ��N*M=2*10^7
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 200100
#define INF -0x3f3f3f3f
using namespace std;

int n,s[N],f[N],dp[N][M],sum;

int main(){
    memset(dp,-0x3f,sizeof(dp));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&s[i],&f[i]);
        sum+=abs(f[i]);//�п���f[i]֮��Ϊ��,��������ȫ������ֵȡ�������ֵ
    }
    sum<<=1;
    dp[0][sum/2]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum;j++)
            dp[i][j]=dp[i-1][j];
        for(int j=0;j<=sum;j++){//���������� j+f[i]����Ϊ����
            if(dp[i-1][j]>INF){//���s[i]�п���Ϊ������ֻҪ �ȸ������ ��Ϊ�Ϸ�״̬
                dp[i][j+f[i]]=max(dp[i][j+f[i]],dp[i-1][j]+s[i]);
            }
        }
    }
    int ans=0;
    for(int i=sum/2;i<=sum;i++){
        if(dp[i]>0)
            ans=max(ans,i-sum/2+dp[n][i]);
    }
    printf("%d",ans);
    return 0;
}
*/

/*
����ö������ n<=100,TLE
*/
