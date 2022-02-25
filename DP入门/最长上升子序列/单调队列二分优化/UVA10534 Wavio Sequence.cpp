/*
����:ժ������
����һ���ַ������ҳ�һ�������������У������е�ǰ�벿��Ҫ������
��벿��Ҫ�ݼ����ҵ����͵ݼ��ĳ���Ҫ��ȣ�Ҫ���������������������еĳ��ȡ�
�����г���<=10010.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1475
˼·:���������LIS,ö�ٳ�a[i]Ϊ���ĵ�,��ʵ�ʶԳư뾶Ϊmin(dp1[i],dp2[i]),
���ֵΪans=max(ans,min(dp1[i],dp2[i])*2-1);
*/
//ac 50ms stl lower_bound
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;

//dp1[i]��ʾ��1��ʼ,��a[i]��β��Ԫ�ص�LIS�ĳ���
//dp2[i]��ʾ��n��ʼ,��a[i]��β��Ԫ�ص�LIS�ĳ���
int n,x[N],a[N],dp1[N],dp2[N],len,ans;

int main(){
    int pos;
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++)
            scanf("%d",&x[i]);
        len=0;
        for(int i=1;i<=n;i++){
            if(x[i]>a[len]){
                a[++len]=x[i];
                dp1[i]=len;
            }
            else{
                pos=lower_bound(a+1,a+1+len,x[i])-a;
                a[pos]=x[i];
                dp1[i]=pos;
            }
        }
        len=0;
        for(int i=n;i>=1;i--){
            if(x[i]>a[len]){
                a[++len]=x[i];
                dp2[i]=len;
            }
            else{
                pos=lower_bound(a+1,a+1+len,x[i])-a;
                a[pos]=x[i];
                dp2[i]=pos;
            }
        }
        ans=1;
        for(int i=1;i<=n;i++)
            ans=max(ans,min(dp1[i],dp2[i])*2-1);
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 40ms ��д����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;

//dp1[i]��ʾ��1��ʼ,��a[i]��β��Ԫ�ص�LIS�ĳ���
//dp2[i]��ʾ��1��ʼ,��a[i]��β��Ԫ�ص�LDS�ĳ���
int n,x[N],a[N],dp1[N],dp2[N],len,ans;

int erfen(int val){
	int l=1,r=len,mid;
	while(l<=r){
		mid=(l+r)/2;
		if(val == a[mid])
			return mid;
		if(val<a[mid])
			r=mid-1;
		else
			l=mid+1;
	}
	return l;
}

int main(){
    int pos;
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++)
            scanf("%d",&x[i]);
        len=0;
        for(int i=1;i<=n;i++){
            if(x[i]>a[len]){
                a[++len]=x[i];
                dp1[i]=len;
            }
            else{
                pos=erfen(x[i]);
                a[pos]=x[i];
                dp1[i]=pos;
            }
        }
        len=0;
        for(int i=n;i>=1;i--){
            if(x[i]>a[len]){
                a[++len]=x[i];
                dp2[i]=len;
            }
            else{
                pos=erfen(x[i]);
                a[pos]=x[i];
                dp2[i]=pos;
            }
        }
        ans=1;
        for(int i=1;i<=n;i++)
            ans=max(ans,min(dp1[i],dp2[i])*2-1);
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//TLE O(n^2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;

//dp1[i]��ʾ��1��ʼ,��a[i]��β��Ԫ�ص�LIS�ĳ���
//dp2[i]��ʾ��1��ʼ,��a[i]��β��Ԫ�ص�LDS�ĳ���
int n,x[N],dp1[N],dp2[N],ans;

int main(){
    int pos;
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++)
            scanf("%d",&x[i]);
        for(int i=1;i<=n;i++){
        	dp1[i]=1;
        	for(int j=1;j<i;j++){
        		if(x[i]>x[j])
        			dp1[i]=max(dp1[i],dp1[j]+1);
			}
        }
        for(int i=n;i>=1;i--){
        	dp2[i]=1;
        	for(int j=n;j>i;j--){
        		if(x[i]>x[j])
        			dp2[i]=max(dp2[i],dp2[j]+1);
			}
        }
        ans=1;
        for(int i=1;i<=n;i++)
            ans=max(ans,min(dp1[i],dp2[i])*2-1);
        printf("%d\n",ans);
    }
    return 0;
}
*/
