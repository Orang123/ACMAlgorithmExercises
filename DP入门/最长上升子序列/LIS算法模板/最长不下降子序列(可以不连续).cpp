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
    dp[1]=1;//初始值单个元素构成一个上升序列
    for(int i=2;i<=n;i++){
        dp[i]=1;
        for(int j=1;j<i;j++){
            if(a[i]>=a[j]) dp[i]=max(dp[i],dp[j]+1);//这里是a[i]大于等于a[j]
        }
        ans=max(ans,dp[i]);
    }
    printf("%d",ans);
    return 0;
}

/*
//最精简版本 O(n^2)
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
            if(a[i]>=a[j]) dp[i]=max(dp[i],dp[j]+1);//这里是a[i]大于等于a[j]
        }
        ans=max(ans,dp[i]);
    }
    printf("%d",ans);
    return 0;
}
*/

/*
LIS单调队列二分搜索法 O(NlogN)
//最长不下降子序列
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
        if(a[i]>=b[k-1]) b[k++]=a[i];//这里是a[i]>=b[k-1] 如果问严格单调上升则是a[i]>b[k-1]
        else
            erfen(1,k-1,a[i]);
    }
    printf("%d",k-1);
    return 0;
}
*/

/*
采用stl lower_bound()函数实现二分搜索的LIS
//最长不下降子序列
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
            pos=lower_bound(b+1,b+k,a[i])-b;//第二个参数是b+1+k-1=b+k
            b[pos]=a[i];
        }
    }
    printf("%d",k-1);
    return 0;
}
*/

