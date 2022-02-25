#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 10000
using namespace std;
//ac 0ms ̰��+01���� ǡ��װ������
//dp[j]������jʱ�䳪��dp[j]�׸�,����jʱ��ʱ��.
/*
����:��t����,n+1�׸�ɹ�ѡ��,���С�������������678s��ʱ����ĸ�,
������ʱ�����ᳬ��3����,��KTV����t���ӵ���,Ҳ������ֹ�����ڳ�����
��һ�׸�.����Ҫ��Ҫ�����ܳ������ܶ���Ŀ�ĸ�,���ҳ���ʱ�価���ܵؾ�,
�����೪����Ŀ�ͳ���ʱ��.����n+1�ܸ��ʱ���ܺͱ�֤����t.
n<=50
����:https://www.luogu.com.cn/problem/UVA12563
˼·:��Ȼ��󳪵ĸ�һ�����ǡ�������������ʹ����ʱ���,��ô���Խ�����ת��Ϊ
��t-1���ڳ������ܶ����������ܳ�ʱ���ĸ�,���1s����������������,����һ��ǡ��װ
��������01��������.dp[j]������jʱ����೪��dp[j]�׸�,ǡ�ó���jʱ��ʱ��.
���ڶ�Ŀ��������01��������.
*/
int cas,n,v,w[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;i++)
            scanf("%d",&w[i]);
        dp[0]=0;//ֻ��dp[0]�ǺϷ�״̬
        for(int i=1;i<=n;i++){
            for(int j=v-1;j>=w[i];j--){//���1������������������,t-1����������
                if(dp[j-w[i]]>=0)
                    //��ts��ѡ���������ܶ������ĸ�
                    dp[j]=max(dp[j],dp[j-w[i]]+1);
            }
        }
        int ans=0;
        for(int i=v-1;i>=1;i--){
            //����Ҫ��֤������Ŀ���,����������Ŀ����������ʱ���,������ϸ���ڲ��ܴ��ڵ���
            if(dp[i]>0 && dp[i]>dp[ans])
                ans=i;
        }
        printf("Case %d: %d %d\n",cas,dp[ans]+1,ans+678);
    }
    return 0;
}

/*
//ac 0ms 01����
//�趨num[j]��ʾʱ��j��,����������Ŀ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 10000
using namespace std;
//num[j]��ʾʱ��j��,����������Ŀ
int cas,n,v,w[N],dp[M],num[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(num,0,sizeof(num));
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;i++)
            scanf("%d",&w[i]);
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int j=v-1;j>=w[i];j--){
                if(dp[j-w[i]]>=0){
                    if(num[j-w[i]]+1>num[j])//������ĿҪ���
                        num[j]=num[j-w[i]]+1;
                    dp[j]=dp[j-w[i]]+w[i];
                }
            }
        }
        int ans=0;
        for(int i=v-1;i>=1;i--){
            if(dp[i]>0 && num[i]>num[ans])
                ans=i;
        }
        printf("Case %d: %d %d\n",cas,num[ans]+1,ans+678);
    }
    return 0;
}
*/
