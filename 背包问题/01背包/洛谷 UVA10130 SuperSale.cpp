#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 35
using namespace std;
//ac 30ms 01���� �����ܶ��װ������,��m��01����
/*
����:��������n����Ʒ,ÿ����Ʒ��������,�����Լ��������ͼ�ֵ,
��m����,ÿ����ÿ����Ʒֻ��ȡһ��,����ÿ���˶����Լ�����ܳ��ܵ�����,
Ҫ����m�������Լ��ĳ���������Χ��,ȡ������Ʒ��ֵ�ܺ����.
����:https://www.luogu.com.cn/problem/UVA10130
˼·:"ÿ����ÿ����Ʒֻ��ȡһ��",��Ȼ����ÿ������ȡ������ֵ��һ��01����,
���Զ�ÿ������һ��01����,�ۼ�����ֵ��.
*/
int n,m,v,w[N],val[N],dp[M],ans;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&val[i],&w[i]);
        scanf("%d",&m);
        while(m--){//m���� ÿ������һ��01����
            scanf("%d",&v);
            memset(dp,0,sizeof(dp));
            for(int i=1;i<=n;i++){
                for(int j=v;j>=w[i];j--)
                    dp[j]=max(dp[j],dp[j-w[i]]+val[i]);
            }
            ans+=dp[v];
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 0ms ��Ϊʵ�ʶ���ÿ������˵������01������Ʒ������ֵ���������ͬ��,���б���������ͬ
//���԰���ÿ���˵ĳ�������30,ֻ��һ��01����,֮�����ÿ���˵ĳ�������v(�����ݻ�)ֻ�ۼ�dp[v]����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 35
using namespace std;

int n,m,v,w[N],val[N],dp[M],ans;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&val[i],&w[i]);
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=30;j>=w[i];j--)
                dp[j]=max(dp[j],dp[j-w[i]]+val[i]);
        }
        scanf("%d",&m);
        while(m--){//m���� ÿ������һ��01����
            scanf("%d",&v);
            ans+=dp[v];
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
