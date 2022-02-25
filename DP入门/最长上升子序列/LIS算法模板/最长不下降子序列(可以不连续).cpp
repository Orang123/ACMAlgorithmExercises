#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1100],dp[1100];
//dp O(N^2)
int main(){
    int n,ans=1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    dp[1]=1;//��ʼֵ����Ԫ�ع���һ����������
    for(int i=2;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<i;j++){
            if(a[i]>=a[j]) dp[i]=max(dp[i],dp[j]+1);//������a[i]���ڵ���a[j]
        }
        ans=max(ans,dp[i]);
    }
    printf("%d",ans);
    return 0;
}

/*
//���汾 O(n^2)
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1100],dp[1100];
//dp O(N^2)
int main(){
    int n,ans=1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<i;j++){
            if(a[i]>=a[j]) dp[i]=max(dp[i],dp[j]+1);//������a[i]���ڵ���a[j]
        }
        ans=max(ans,dp[i]);
    }
    printf("%d",ans);
    return 0;
}
*/

/*
LIS�������ж��������� O(NlogN)
//����½�������
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1100],b[1100];
void erfen(int l,int r,int val){
    int mid;
    while(l<r){
        mid=(l+r)/2;
        if(val>b[mid]) l=mid+1;
        else r=mid;
    }
    b[l]=val;
}

int main(){
    int n,k=2;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    b[1]=a[1];
    for(int i=2;i<=n;i++){
        if(a[i]>=b[k-1]) b[k++]=a[i];//������a[i]>=b[k-1] ������ϸ񵥵���������a[i]>b[k-1]
        else
            erfen(1,k-1,a[i]);
    }
    printf("%d",k-1);
    return 0;
}
*/

/*
����stl lower_bound()����ʵ�ֶ���������LIS
//����½�������
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[1100],b[1100];

int main(){
    int n,k=2,pos;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    b[1]=a[1];
    for(int i=2;i<=n;i++){
        if(a[i]>=b[k-1]) b[k++]=a[i];
        else{
            pos=lower_bound(b+1,b+k,a[i])-b;//�ڶ���������b+1+k-1=b+k
            b[pos]=a[i];
        }
    }
    printf("%d",k-1);
    return 0;
}
*/

