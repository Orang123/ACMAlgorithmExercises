/*
����:�����½�������.
n<=5000.
����:http://poj.org/problem?id=1887
˼·:����O(n^2)��O(nlogn)��������.
������O(n^2)��TLE��.ֻ��ע��stl��lower_bound
�������ڶ��ֲ�ѯ���� Ҫ���ò�������������.
*/
//ac 0ms �������ж����Ż�
#include<cstdio>
#define N 5000

int m,dp[N],len;

void erfen(int val){
    int l=1,r=len,mid;
    while(l<r){
        mid=(l+r)/2;
        if(val<dp[mid])//ע��dp�����ǽ���,��˺�����ʱ,l,r�Ĳ����պ��෴.
            l=mid+1;
        else
            r=mid;
    }
    dp[l]=val;
}

int main(){
    int cas=0;
    while(scanf("%d",&m) && m!=-1){
        cas++;
        len=0;
        dp[++len]=m;
        while(scanf("%d",&m) && m!=-1){
            if(m<=dp[len])
                dp[++len]=m;
            else
                erfen(m);
        }
        printf("Test #%d:\n",cas);
        printf("  maximum possible interceptions: %d\n\n",len);
    }
    return 0;
}

/*
//ac 0ms
//lower_bound dp���齵��
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 5000
using namespace std;

int n,a[N],dp[N];

int main(){
    int cas=0;
    while(scanf("%d",&a[++n]) && a[n]!=-1){
        cas++;
        memset(dp,0,sizeof(dp));
        while(scanf("%d",&a[++n]) && a[n]!=-1);
        n--;
        for(int i=1;i<=n;i++)//lower_bound ģʽ�Ƕ�������������,���ǽ��� ��Ҫ����greater<int>()����
        	*lower_bound(dp,dp+n,a[i],greater<int>())=a[i];
        printf("Test #%d:\n",cas);
        //��Ϊdp�����ǵ����½���,����dp����Ҫ��ʼ��Ϊ0,��ⵥ�����г���Ҫ��0���Ƚ�
        printf("  maximum possible interceptions: %d\n\n",lower_bound(dp,dp+n,0,greater<int>())-dp);
        n=0;
    }
    return 0;
}
*/

/*
//ac 0ms
//lower_bound dp����reverse����Ϊ����
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 5000
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],dp[N];

int main(){
    int cas=0;
    while(scanf("%d",&a[++n]) && a[n]!=-1){
        cas++;
        memset(dp,0x3f,sizeof(dp));
        while(scanf("%d",&a[++n]) && a[n]!=-1);
        n--;
        reverse(a+1,a+1+n);
        for(int i=1;i<=n;i++)
        	*lower_bound(dp,dp+n,a[i])=a[i];
        printf("Test #%d:\n",cas);
        //��Ϊdp�����ǵ���������,����dp����Ҫ��ʼ��ΪINF,��ⵥ�����г���Ҫ��INF���Ƚ�
        printf("  maximum possible interceptions: %d\n\n",lower_bound(dp,dp+n,INF)-dp);
        n=0;
    }
    return 0;
}
*/

/*
//ac 47ms O(n^2)����
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 5000
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],dp[N],ans;

int main(){
    int cas=0;
    while(scanf("%d",&a[++n]) && a[n]!=-1){
        cas++;
        while(scanf("%d",&a[++n]) && a[n]!=-1);
        n--;
        ans=1;
        for(int i=1;i<=n;i++){
        	dp[i]=1;
        	for(int j=1;j<i;j++){
        		if(a[j]>a[i])
        			dp[i]=max(dp[i],dp[j]+1);
			}
			ans=max(ans,dp[i]);
		}
        printf("Test #%d:\n",cas);
        printf("  maximum possible interceptions: %d\n\n",ans);
        n=0;
    }
    return 0;
}
*/
