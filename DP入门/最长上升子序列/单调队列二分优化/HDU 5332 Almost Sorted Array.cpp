/*
����:
����n�������ܷ�ɾ��һ����ʹ����Ϊ���½����߷�������
n<=100000.
����:https://acm.hdu.edu.cn/showproblem.php?pid=5532
˼·:�ж�LIS��LDS�ĳ����Ƿ���ڵ���n-1,�����,��"YES",����"NO".
*/
//ac 577ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],dp[N],len;

int main(){
    int T,pos;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        len=0;
        for(int i=1;i<=n;i++){
            if(a[i]>=dp[len])
                dp[++len]=a[i];
            else{
                pos=upper_bound(dp+1,dp+1+len,a[i])-dp;//������lower_bound ��Ϊ�ǲ��½�>=
                dp[pos]=a[i];
            }
        }
        if(len>=n-1){
            printf("YES\n");
            continue;
        }
        len=0;
        for(int i=n;i>=1;i--){
            if(a[i]>=dp[len])
                dp[++len]=a[i];
            else{
                pos=upper_bound(dp+1,dp+1+len,a[i])-dp;
                dp[pos]=a[i];
            }
        }
        if(len>=n-1){
            printf("YES\n");
            continue;
        }
        printf("NO\n");
    }
    return 0;
}

/*
//ac 655ms ��д����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],dp[N],len;

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
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        len=0;
        for(int i=1;i<=n;i++){
            if(a[i]>=dp[len])
                dp[++len]=a[i];
            else
            	erfen(a[i]);
        }
        if(len>=n-1){
            printf("YES\n");
            continue;
        }
        len=0;
        for(int i=n;i>=1;i--){
            if(a[i]>=dp[len])
                dp[++len]=a[i];
            else
            	erfen(a[i]);
        }
        if(len>=n-1){
            printf("YES\n");
            continue;
        }
        printf("NO\n");
    }
    return 0;
}
*/

/*
//wa upper_bound ��֪��ԭ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],dp[N],len;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;i++)
            *upper_bound(dp,dp+n,a[i])=a[i];

        len=upper_bound(dp,dp+n,INF)-dp;
        if(len>=n-1){
            printf("YES\n");
            continue;
        }
        memset(dp,0x3f,sizeof(dp));
        for(int i=n;i>=1;i--)
            *upper_bound(dp,dp+n,a[i])=a[i];
        len=upper_bound(dp,dp+n,INF)-dp;
        if(len>=n-1){
            printf("YES\n");
            continue;
        }
        printf("NO\n");
    }
    return 0;
}
*/
