/*
����:��n���ź���,�����Ĳ��ཻ���ź��߸���,
����������ǵ�i�����Ҳ��Ķ˿ںţ�Ӧ�����ӵ�����ĵ�i���˿ڡ�
n<=40000.
����:http://poj.org/problem?id=1631
˼·:n<=40000.O(n^2)��������TLE,��Ҫ�õ������ж����Ż�,
O(nlogn).
*/
//ac 94ms �������ж����Ż�
//ʱ�临�Ӷ�O(nlogn)=40000*15=6*10^5
#include<cstdio>
#define N 41000

int n,a[N],b[N],len;

void erfen(int val){
    int l=1,r=len,mid;
    while(l<r){
        mid=(l+r)/2;
        if(val<b[mid])
            r=mid;
        else
            l=mid+1;
    }
    b[l]=val;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        len=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++){
            if(a[i]>b[len])
                b[++len]=a[i];
            else
                erfen(a[i]);
        }
        printf("%d\n",len);
    }
    return 0;
}

/*
//ac 110ms
//lower_bound
#include<cstdio>
#include<algorithm>
#define N 41000
using namespace std;

int n,a[N],b[N],len;

int main(){
    int T,pos;
    scanf("%d",&T);
    while(T--){
        len=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        b[++len]=a[1];
        for(int i=2;i<=n;i++){
            if(a[i]>b[len])
                b[++len]=a[i];
            else{
            	pos=lower_bound(b+1,b+1+len,a[i])-b;
            	b[pos]=a[i];
			}
        }
        printf("%d\n",len);
    }
    return 0;
}
*/

/*
//ac 125ms
//lower_bound b�����±��0��ʼ,Ϊ�˷���ͳ��ĩβ�Ϸ�λ��b�����ʼ��ΪINF
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 41000
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],b[N];

int main(){
    int T,pos;
    scanf("%d",&T);
    while(T--){
        memset(b,0x3f,sizeof(b));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
        	*lower_bound(b,b+n,a[i])=a[i];
        printf("%d\n",lower_bound(b,b+n,INF)-b);
    }
    return 0;
}
*/

/*
//ac 110ms
//lower_bound b�����±��1��ʼ,Ϊ�˷���ͳ��ĩβ�Ϸ�λ��b�����ʼ��ΪINF
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 41000
#define INF 0x3f3f3f3f
using namespace std;

int n,a[N],b[N];

int main(){
    int T,pos;
    scanf("%d",&T);
    while(T--){
        memset(b,0x3f,sizeof(b));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
        	*lower_bound(b+1,b+n+1,a[i])=a[i];
        printf("%d\n",lower_bound(b+1,b+n+1,INF)-b-1);//��Ϊ�±��1��ʼ,�������󳤶�+1,���Ҫ��1
    }
    return 0;
}
*/

/*
//TLE O(n^2) dp
#include<cstdio>
#include<algorithm>
#define N 41000
using namespace std;

int n,a[N],dp[N],ans;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=1;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++){
        	dp[i]=1;
        	for(int j=1;j<i;j++){
        		if(a[j]<a[i])
        			dp[i]=max(dp[i],dp[j]+1);
			}
			ans=max(ans,dp[i]);
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
