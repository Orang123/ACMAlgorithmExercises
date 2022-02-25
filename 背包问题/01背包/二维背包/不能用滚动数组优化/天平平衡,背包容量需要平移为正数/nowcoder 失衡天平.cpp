#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 20100
using namespace std;
//ac 12ms ���������������� [0,20000]
/*
����:����Alice�߳��˴�ħ��������,��������ɵɵ�������˴�������,�������Ǻ�???���ʱ��,
һ�����������ߵ�����ǰ��Ӧ�޳���������,�������и�����,��Ҫ����ѡ�����ֱ������ƽ������,
����ƽƽ������Խ���ƽ�ϵ�������������,���������ƽ�⼣�߰�,ֻҪ�����������С�ڵ���m��
�ᱣ��ƽ��,Aliceɵɵ����ΪԽ�ص�����Խ��,��Alice��������ߵ�����������.(���޲�������)
����:https://ac.nowcoder.com/acm/problem/19158?&headNav=acm
˼·:������ƽƽ��,ÿ����Ʒ���Է���ƽ���Ҳ���Է���ƽ�Ҳ�,Ҳ���Բ���.
������ƽ��������ǽ�����,������������������Ҳ�����,�������Ҳ�������
������m,��ôʵ��ƽ��Ŀ����������[sum/2-m,sum/2+m]
*/
//dp[i][j]��ʾ��i��������������ƽ�ϵõ���������������Ϊj-sum/2�������������������.
//j-sum/2Ϊ����ʾ�����,j-sum/2Ϊ����ʾ�Ҳ���
int n,m,w[N],sum,dp[N][M];

int main(){
    memset(dp,-0x3f,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&w[i]);
        sum+=w[i];
    }
    sum<<=1;
    dp[0][sum/2]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum;j++)
            dp[i][j]=dp[i-1][j];
        for(int j=sum;j>=0;j--){
            if(dp[i-1][j]<0) continue;
            dp[i][j-w[i]]=max(dp[i][j-w[i]],dp[i-1][j]+w[i]);
            dp[i][j+w[i]]=max(dp[i][j+w[i]],dp[i-1][j]+w[i]);
        }
    }
    int ans=0;
    //ƽ�����������������Ҳ���m��:[sum/2-m,sum/2],Ҳ�������Ҳ�������m��:[sum/2,sum/2+m]
    for(int i=sum/2-m;i<=sum/2+m;i++){
        if(dp[n][i]>0)
            ans=max(ans,dp[n][i]);
    }
    printf("%d",ans);
    return 0;
}

/*
//ac 9ms ���������� [0,10000]
//dp[i][abs(j-w[i])]=max(dp[i][abs(j-w[i])],dp[i-1][j]+w[i]);
//dp[i][j+w[i]]=max(dp[i][j+w[i]],dp[i-1][j]+w[i]);
//ʵ�ʶ��������Ҳ���m,�����Ҳ�������m,��������ֵ��û��Ӱ��.
//��˾���[0,sum]��ģ��01����,dp[0][0]Ϊ��ʼ״̬
//dp[i][j]��ʾ��i��������������ƽ�ϵõ���������������Ϊj�������������������.
//���ﲻ���ֵ���������ػ����Ҳ���
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;

int n,m,w[N],sum,dp[N][M];

int main(){
    memset(dp,-0x3f,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&w[i]);
        sum+=w[i];
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum;j++)
            dp[i][j]=dp[i-1][j];
        for(int j=0;j<=sum;j++){
            if(dp[i-1][j]<0) continue;
            //j-w[i]�������Ϊ��,��ʾ������,ȡ����ֵ��,�����ֵ�����������˭��,ֻ��ʾ���Ҳ�ֵ
            //ֻȡ������Ž�Ľ��
            //���ڱ�������Ϊ-2�ı��2��,ԭ��-2+2=0 �ڶ��η��Ҳ���ƽ��,���ڷ��Ҳ�2+2=4 ��ƽ��,����ÿ����Ʒ����ö�ٷ������Ҳ�,
            //�������ö�ٷ���� 2-2=0 �ͻ�ƽ��,��Ӱ����������ȷ��.
            dp[i][abs(j-w[i])]=max(dp[i][abs(j-w[i])],dp[i-1][j]+w[i]);
            dp[i][j+w[i]]=max(dp[i][j+w[i]],dp[i-1][j]+w[i]);
        }
    }
    int ans=0;
    for(int i=0;i<=m;i++){
        if(dp[n][i]>0)
            ans=max(ans,dp[n][i]);
    }
    printf("%d",ans);
    return 0;
}
*/

/*
//ac 22ms ������������2������ [0,20000]
//dp[i][j]=max(dp[i][j],dp[i-1][j+w[i]]+w[i]);
//dp[i][j]=max(dp[i][j],dp[i-1][j-w[i]]+w[i]);
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 20100
using namespace std;

int n,m,w[N],sum,dp[N][M];

int main(){
    memset(dp,-0x3f,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&w[i]);
        sum+=w[i];
    }
    sum<<=1;
    dp[0][sum/2]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum;j++){
            dp[i][j]=dp[i-1][j];
            if(j+w[i]<=sum && dp[i-1][j+w[i]]>=0)
                dp[i][j]=max(dp[i][j],dp[i-1][j+w[i]]+w[i]);
            if(j-w[i]>=0 && dp[i-1][j-w[i]]>=0)
                dp[i][j]=max(dp[i][j],dp[i-1][j-w[i]]+w[i]);
        }
    }
    int ans=0;
    for(int i=sum/2-m;i<=sum/2+m;i++){
        if(dp[n][i]>0)
            ans=max(ans,dp[n][i]);
    }
    printf("%d",ans);
    return 0;
}
*/

/*
//ac 11ms ���������� [0,10000]
//dp[i][j]=max(dp[i][j],dp[i-1][j+w[i]]+w[i]);
//dp[i][j]=max(dp[i][j],dp[i-1][abs(j-w[i])]+w[i]);
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;

int n,m,w[N],sum,dp[N][M];

int main(){
    memset(dp,-0x3f,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&w[i]);
        sum+=w[i];
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=sum;j++){
            dp[i][j]=dp[i-1][j];
            if(j+w[i]<=sum)
                dp[i][j]=max(dp[i][j],dp[i-1][j+w[i]]+w[i]);
            dp[i][j]=max(dp[i][j],dp[i-1][abs(j-w[i])]+w[i]);
        }
    }
    int ans=0;
    for(int i=0;i<=m;i++){
        if(dp[n][i]>0)
            ans=max(ans,dp[n][i]);
    }
    printf("%d",ans);
    return 0;
}
*/
