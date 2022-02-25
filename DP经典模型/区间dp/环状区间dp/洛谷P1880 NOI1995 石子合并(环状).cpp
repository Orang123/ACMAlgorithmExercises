/*
����:��һ��Բ�βٳ������ܰڷ�N��ʯ��,��Ҫ��ʯ���д���غϲ���һ��.
�涨ÿ��ֻ��ѡ���ڵ�2�Ѻϲ����µ�һ�ѣ������µ�һ�ѵ�ʯ��������Ϊ�ôκϲ��ĵ÷֡�
����Ƴ�һ���㷨,�������N��ʯ�Ӻϲ���1�ѵ���С�÷ֺ����÷֡�
N<=100.
����:https://www.luogu.com.cn/problem/P1880
˼·:
ö�����䳤�Ⱥ�ö����ʼ�˵�
����ʯ�Ӷѳ�Բ�λ�װ����,�ڴ�֮ǰ����״.
��ô�ʹ��ڵ�1��ʯ�Ӻ͵�n��ʯ�Ӻϲ�������,�����ͬʱ,��1��Ҳ�����ܺ͵�2���кϲ�,
��ʵ�ϼ�ʹ���гɻ�״,���Ƿ������ԭ����״����,��ֻ�Ƕ������1�����n���п��ܺϲ��������,��������ô�ϲ�,
��ʣ��������ѵ�ʱ��,���������ڵľ��Ǿ���û�кϲ���,�Ȿ�����һ����״������.
���ն�������2��û�к����ڵĺϲ�,��ʵ�������ǿ��Խ������״ ö�ٷָ��ת����һ����״������.
����1Ϊ�ָ�� ������[2,n+1](1 2������),2Ϊ�ָ��������[3,n+2](2 3������).
n-1Ϊ�ָ��������[n,2n-1](n n-1������) [1,n](1 n������)
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp1[220][220],dp2[220][220],sum[220];
int main(){
    int minc=INF,maxc=-1;
    memset(dp1,INF,sizeof(dp1));//dp1������Сֵ
    memset(dp2,-1,sizeof(dp2));//dp2�������ֵ
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i+n]=sum[i];//��i�����i+n����һ����,���n�����n+1������,ʵ�ʾ��ǵ�n�����1������.
        dp1[i][i]=dp1[i+n][i+n]=0;
        dp2[i][i]=dp2[i+n][i+n]=0;
    }
    for(int i=1;i<=2*n-1;i++)//���ܵ���״����[1,n] [2,n+1] [3,n+2] ...[n,2n-1] [n+1,2n]��[1,n]���ظ�������
        sum[i]+=sum[i-1];
    for(int l=1;l<=n-1;l++){
        for(int i=1;i+l<=2*n-1;i++){//���������Ͻ�2n-1,�����������Ϊ���󳤶Ȱ���n~2n-1��Щ��Ĵ�������ϲ���
            int j=i+l;
            for(int k=i;k<j;k++){//ö������ָ��,�����������ɼ���2������������ϲ�����,�������Ž�.
                dp1[i][j]=min(dp1[i][j],dp1[i][k]+dp1[k+1][j]+sum[j]-sum[i-1]);
                dp2[i][j]=max(dp2[i][j],dp2[i][k]+dp2[k+1][j]+sum[j]-sum[i-1]);
            }
        }
    }
    /*
    [1,n] [2,n+1] [3,n+2] ���Ƿֱ���������ڵ�1 n�ϲ� 1 2�ϲ� 2 3�ϲ������,
    ʵ�ʾ��ǽ���״�����ֳ�n����״������,�����Ƚϸ������Ž�.
    */
    for(int i=1;i<=n;i++){
        minc=min(minc,dp1[i][i+n-1]);
        maxc=max(maxc,dp2[i][i+n-1]);
    }
    printf("%d\n",minc);
    printf("%d\n",maxc);
    return 0;
}
/*
��ö��������˵�,��ö���Ҷ˵�
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp1[220][220],dp2[220][220],sum[220];
int main(){
    int minc=INF,maxc=-1;
    memset(dp1,INF,sizeof(dp1));
    memset(dp2,-1,sizeof(dp2));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i+n]=sum[i];
        dp1[i][i]=dp1[i+n][i+n]=0;
        dp2[i][i]=dp2[i+n][i+n]=0;
    }
    for(int i=1;i<=2*n-1;i++)
        sum[i]+=sum[i-1];
    for(int i=2*n-2;i>=1;i--){//ö��������˵� ÿһ�ζ����µ�����
        for(int j=i+1;j<=2*n-1;j++){//ö�������Ҷ˵� �����С���ϵ���,�������µ�������Ϊ�Ҷ˵㲻ͬ,��С״̬���״̬ת��
            for(int k=i;k<j;k++){
               dp1[i][j]=min(dp1[i][j],dp1[i][k]+dp1[k+1][j]+sum[j]-sum[i-1]);
               dp2[i][j]=max(dp2[i][j],dp2[i][k]+dp2[k+1][j]+sum[j]-sum[i-1]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        minc=min(minc,dp1[i][i+n-1]);
        maxc=max(maxc,dp2[i][i+n-1]);
    }
    printf("%d\n",minc);
    printf("%d\n",maxc);
    return 0;
}
*/

/*
��ö�������Ҷ˵�,��ö����˵�
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp1[220][220],dp2[220][220],sum[220];
int main(){
    int minc=INF,maxc=-1;
    memset(dp1,INF,sizeof(dp1));
    memset(dp2,-1,sizeof(dp2));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i+n]=sum[i];
        dp1[i][i]=dp1[i+n][i+n]=0;
        dp2[i][i]=dp2[i+n][i+n]=0;
    }
    for(int i=1;i<=2*n-1;i++)
        sum[i]+=sum[i-1];
    for(int j=2;j<=2*n-1;j++){//ö�������Ҷ˵� ÿһ�ζ����µ�����
        for(int i=j-1;i>=1;i--){//ö��������˵� �����С���ϵ���,�������µ�������Ϊ��˵㲻ͬ,��С״̬���״̬ת��
            for(int k=i;k<j;k++){
               dp1[i][j]=min(dp1[i][j],dp1[i][k]+dp1[k+1][j]+sum[j]-sum[i-1]);
               dp2[i][j]=max(dp2[i][j],dp2[i][k]+dp2[k+1][j]+sum[j]-sum[i-1]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        minc=min(minc,dp1[i][i+n-1]);
        maxc=max(maxc,dp2[i][i+n-1]);
    }
    printf("%d\n",minc);
    printf("%d\n",maxc);
    return 0;
}
*/
/*
���仯������n�μ���dfs(i,i+n-1)
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp1[220][220],dp2[220][220],sum[220];

void dfs(int st,int ed){//O(n^3)
    if(dp1[st][ed]|| dp2[st][ed]) return;//ʵ��ֻ���ж�dp1����,��Ϊdp1��dp2��ͬʱ���µ�.
    if(st == ed){
        dp1[st][ed]=dp2[st][ed]=0;
        return;
    }
    int ans1=INF,ans2=-1;
    for(int i=st+1;i<=ed;i++){
        dfs(st,i-1),dfs(i,ed);
        ans1=min(ans1,dp1[st][i-1]+dp1[i][ed]+sum[ed]-sum[st-1]);
        ans2=max(ans2,dp2[st][i-1]+dp2[i][ed]+sum[ed]-sum[st-1]);
    }
    dp1[st][ed]=ans1;
    dp2[st][ed]=ans2;
}

int main(){
    int minc=INF,maxc=-1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i+n]=sum[i];
    }
    for(int i=1;i<=2*n-1;i++)
        sum[i]+=sum[i-1];
    for(int i=1;i<=n;i++){//O(n^4)
        dfs(i,i+n-1);//ǰ����õ�ĳЩdpֵ�ᱣ�������ٴ�ʹ��
        minc=min(minc,dp1[i][i+n-1]);
        maxc=max(maxc,dp2[i][i+n-1]);
    }
    printf("%d\n",minc);
    printf("%d\n",maxc);
    return 0;
}
*/
/*
���仯����ֱ����1~2n-1 ����,��Ȼ[1,2*n-1]��������Ҫ���,����Ϊ���η�,��������������С�����ȻҲ�������.dfs(1,2*n-1);
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp1[220][220],dp2[220][220],sum[220];

void dfs(int st,int ed){
    if(dp1[st][ed]|| dp2[st][ed]) return;//ʵ��ֻ���ж�dp1����,��Ϊdp1��dp2��ͬʱ���µ�.
    if(st == ed){
        dp1[st][ed]=dp2[st][ed]=0;
        return;
    }
    int ans1=INF,ans2=-1;
    for(int i=st+1;i<=ed;i++){
        dfs(st,i-1),dfs(i,ed);
        ans1=min(ans1,dp1[st][i-1]+dp1[i][ed]+sum[ed]-sum[st-1]);
        ans2=max(ans2,dp2[st][i-1]+dp2[i][ed]+sum[ed]-sum[st-1]);
    }
    dp1[st][ed]=ans1;
    dp2[st][ed]=ans2;
}

int main(){
    int minc=INF,maxc=-1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i+n]=sum[i];
    }
    for(int i=1;i<=2*n-1;i++)
        sum[i]+=sum[i-1];
    //��Ȼ����������С��n,������Ϊdfs�Ƿ��η�,����ֱ����[1,2*n-1],��ô����������������䳤�ȵ�С���䶼����������
    dfs(1,2*n-1);
    for(int i=1;i<=n;i++){
        minc=min(minc,dp1[i][i+n-1]);
        maxc=max(maxc,dp2[i][i+n-1]);
    }
    printf("%d\n",minc);
    printf("%d\n",maxc);
    return 0;
}
*/
