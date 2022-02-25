/*
����:��Ǯ������VΪF-E,��n��Ӳ��,ÿ��Ӳ�ҵļ�ֵΪval[i],����Ϊw[i].
��ǡ��װ����Ǯ����ɵ�Ӳ�ҵ���С��ֵ��.
����:http://poj.org/problem?id=1384
˼·:��ȫ����ǡ��װ����������С��ֵ.
*/
//ac 63ms ��ȫ���� һά����j����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 10010
#define INF 0x3f3f3f3f
using namespace std;

int E,F,n,v,val[N],w[N],dp[M];
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d",&E,&F);
        v=F-E;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&val[i],&w[i]);
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int j=w[i];j<=v;j++)
                dp[j]=min(dp[j],dp[j-w[i]]+val[i]);
        }
        if(dp[v]!=INF)
            printf("The minimum amount of money in the piggy-bank is %d.\n",dp[v]);
        else
            printf("This is impossible.\n");
    }
    return 0;
}

/*
//ac 188ms �������Ż�ģ��01����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 10010
#define INF 0x3f3f3f3f
using namespace std;

int E,F,n,v,val[N],w[N],dp[M];
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d",&E,&F);
        v=F-E;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&val[i],&w[i]);
        dp[0]=0;
        int tw,tv;
        //ac �������Ż� 188ms ÿ����Ʒö�� log(v/w[i])�����ܵ���Ʒ
        for(int i=1;i<=n;i++){
            for(tw=w[i],tv=val[i];tw<=v;tw<<=1,tv<<=1){
                for(int j=v;j>=tw;j--)
                    dp[j]=min(dp[j],dp[j-tw]+tv);
            }
        }
        //TLE ����01���� ÿ����Ʒö��v/w[i] �����ܵ���Ʒ
        //for(int i=1;i<=n;i++){
            //for(tw=w[i],tv=val[i];tw<=v;tw+=w[i],tv+=val[i]){
                //for(int j=v;j>=tw;j--)
                    //dp[j]=min(dp[j],dp[j-tw]+tv);
            //}
        //}
        if(dp[v]!=INF)
            printf("The minimum amount of money in the piggy-bank is %d.\n",dp[v]);
        else
            printf("This is impossible.\n");
    }
    return 0;
}
*/

/*
//MLE ��ά���� N*M=5*10^6*4 byte=5*10^3*4=2*10^4KB>1000KB
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 10010
#define INF 0x3f3f3f3f
using namespace std;

int E,F,n,v,val[N],w[N],dp[N][M];
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d",&E,&F);
        v=F-E;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&val[i],&w[i]);
        dp[0][0]=0;
        for(int j=0;j<=v;j++)
            for(int i=1;i<=n;i++){
                if(j>=w[i])
                    dp[i][j]=min(dp[i-1][j],dp[i][j-w[i]]+val[i]);
                else
                    dp[i][j]=dp[i-1][j];
        }
        if(dp[n][v]!=INF)
            printf("The minimum amount of money in the piggy-bank is %d.\n",dp[n][v]);
        else
            printf("This is impossible.\n");
    }
    return 0;
}
*/

