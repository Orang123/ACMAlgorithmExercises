/*
����:
����ƽ���߼����㣬Ҫ���߲������ǰ���¾����ܶ�����ߣ�
����������������ߡ������ʽ�Ǳ�ʾ���p��Ҫ�Ӹ���r������Դ
��:a[p]=r,���p��һ���ᰴ�����������.
n<=500000.
����:https://acm.hdu.edu.cn/showproblem.php?pid=1025
˼·:O(nlogn_���LIS.ֻ��ע������.
*/
//ac 187ms �������ж����Ż�
#include<cstdio>
#define N 500010

int n,m,a[N],dp[N],len;

void erfen(int val){
    int l=1,r=len,mid;
    while(l<r){
        mid=(l+r)/2;
        if(val<dp[mid])
            r=mid;
        else
            l=mid+1;
    }
    dp[l]=val;
}

int main(){
    int cas=0,p;
    while(scanf("%d",&n)!=EOF){
        cas++;
        len=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&m);
            a[p]=m;
        }
        for(int i=1;i<=n;i++){
            if(a[i]>dp[len])
                dp[++len]=a[i];
            else
                erfen(a[i]);
        }
        printf("Case %d:\n",cas);
        if(len == 1)
            printf("My king, at most %d road can be built.\n\n",len);
        else
            printf("My king, at most %d roads can be built.\n\n",len);
    }
    return 0;
}

/*
//ac 202ms lower_bound
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 500010
#define INF 0x3f3f3f3f
using namespace std;

int n,m,a[N],dp[N],len;

int main(){
    int cas=0,p;
    while(scanf("%d",&n)!=EOF){
        cas++;
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&m);
            a[p]=m;
        }
        for(int i=1;i<=n;i++)
        	*lower_bound(dp,dp+n,a[i])=a[i];
        len=lower_bound(dp,dp+n,INF)-dp;
        printf("Case %d:\n",cas);
        if(len == 1)
            printf("My king, at most %d road can be built.\n\n",len);
        else
            printf("My king, at most %d roads can be built.\n\n",len);
    }
    return 0;
}
*/
