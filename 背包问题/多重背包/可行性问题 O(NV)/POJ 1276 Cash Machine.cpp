/*
����:�и��ֲ�ͬ��ֵ�Ļ��ң�ÿ����ֵ�Ļ����в�ͬ�����������ҳ�������Щ���ҿ��Դճɵ���ӽ���С�ڵ��ڸ���������cash�Ľ�
����:http://poj.org/problem?id=1276
˼·:
*/
//ac 32ms ��������� ��ȫ����
//���Ӷ�O(nv)=10*10^5=10^6
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 11
#define M 100010
using namespace std;

int v,n,w[N],num[N],dp[M];

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&num[i],&w[i]);
        if(!v||!n){
            printf("0\n");
            continue;
        }
        dp[0]=0;
        int ans=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=v;j++){
                if(dp[j]!=-1)
                    dp[j]=num[i];
                if(j>=w[i]){
                    dp[j]=max(dp[j],dp[j-w[i]]-1);
                    if(dp[j]!=-1)
                        ans=max(ans,j);
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 16ms ������Ʒ��������ȫ����
//���Ӷ�O(nv)=10*10^5=10^6
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 11
#define M 100010
using namespace std;

int v,n,w[N],num[N],dp[M],cnt[M];

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&num[i],&w[i]);
        if(!v||!n){
            printf("0\n");
            continue;
        }
        int ans=0;
        dp[0]=1;
        for(int i=1;i<=n;i++){
            memset(cnt,0,sizeof(cnt));
            for(int j=w[i];j<=v;j++){
                if(dp[j-w[i]] && !dp[j] && cnt[j-w[i]]+1<=num[i]){
                    dp[j]=1;
                    cnt[j]=cnt[j-w[i]]+1;
                    ans=max(ans,j);
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 47ms �����Ž� �������Ż��� ��ȫ����+01���� �����Ա������׼�Ķ������Ż�(79ms)Ҫ��
//���Ӷȱȱ�׼�Ķ������Ż����ʱ���O(��log(num[i])*v) ����Ҫ��
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 11
#define M 100010
using namespace std;

int v,n,w[N],num[N],dp[M];

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&num[i],&w[i]);
        if(!v||!n){
            printf("0\n");
            continue;
        }
        int tw;
        for(int i=1;i<=n;i++){
            if(num[i]*w[i]>=v){//��i����Ʒ������Ʒ����Ͳ�С�ڱ����ݻ�vʱ ��ȫ����
                for(int j=w[i];j<=v;j++)
                    dp[j]=max(dp[j],dp[j-w[i]]+w[i]);
            }
            else{//���� �������Ż� 01����
                for(int k=1;num[i]>0;k<<=1){
                    num[i]-=k;
                    if(num[i]<0) k+=num[i];
                    tw=w[i]*k;
                    for(int j=v;j>=tw;j--)
                        dp[j]=max(dp[j],dp[j-tw]+tw);
                }
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 79ms �������Ż���01����
//���Ӷ�O(��log(num[i])*v)=10*log(1000)*10^5=10^7
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 11
#define M 100010
using namespace std;

int v,n,w[N],num[N],dp[M];

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&num[i],&w[i]);
        if(!v||!n){
            printf("0\n");
            continue;
        }
        int tw;
        for(int i=1;i<=n;i++){
            for(int k=1;num[i]>0;k<<=1){
                num[i]-=k;
                if(num[i]<0) k+=num[i];
                tw=w[i]*k;
                for(int j=v;j>=tw;j--)
                    dp[j]=max(dp[j],dp[j-tw]+tw);
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//TLE ����01����
//���Ӷ�O(��num[i]*v)=10*1000*10^5=10^9
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 11
#define M 100010
using namespace std;

int v,n,w[N],num[N],dp[M];

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&num[i],&w[i]);
        if(!v||!n){
            printf("0\n");
            continue;
        }
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int k=1;k<=num[i];k++){
                for(int j=v;j>=w[i];j--)
                    dp[j]=max(dp[j],dp[j-w[i]]+w[i]);
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/
