/*
����:�������Σ����һ���൱��Ļ��⡣��Щ�˱ȽϷ��ɣ�
����һЩ�����൱���ǡ�Լ����������֮һ�����ǳ���ע֤ȯ���������ݱ䡣
��ÿ����ٹɼۣ�Ѱ���������ơ����������Ʊ�۸���������� p1, p2,...,pn��
���������������� pi1 < pi2 < ... < pik������ i1 < i2 < ... < ik��John
�������ǿ����ҵ�����������ơ�
n<=10^5.
����:http://poj.org/problem?id=3903
˼·:n<=10^5.O(n^2)��������TLE,��Ҫ�õ������ж����Ż�,
O(nlogn).
*/
//ac 63ms �������ж����Ż�
#include<cstdio>
#define N 100010
using namespace std;

int n,m,dp[N],len;

void erfen(int val){
    int l=1,r=len,mid;
    while(l<r){
        mid=(l+r)/2;
        if(val>dp[mid])//val<dp[mid] r=mid ��wa
            l=mid+1;
        else
            r=mid;
    }
    dp[l]=val;
}

int main(){
    while(scanf("%d",&n)!=EOF){
        len=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&m);
            if(m>dp[len])
                dp[++len]=m;
            else
                erfen(m);
        }
        printf("%d\n",len);
    }
    return 0;
}

/*
//ac 63ms
//lower_bound
#include<cstdio>
#include<algorithm>
#define N 100010
using namespace std;

int n,a[N],b[N],len;

int main(){
    int pos;
    while(scanf("%d",&n)!=EOF){
        len=0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++){
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
//ac 79ms
//lower_bound b�����±��0��ʼ,Ϊ�˷���ͳ��ĩβ�Ϸ�λ��b�����ʼ��ΪINF
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dp[N];

int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;i++){
        	scanf("%d",&m);
        	*lower_bound(dp,dp+n,m)=m;
		}
        printf("%d\n",lower_bound(dp,dp+n,INF)-dp);
    }
    return 0;
}
*/
