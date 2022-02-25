#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

/*
题意及思路:https://blog.csdn.net/qq_39599067/article/details/80335949
*/

int dp[5100][5100],f[5100][5100],n,q,a[5100];

int main(){
    int l,r;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        f[i][i]=dp[i][i]=a[i];
    for(int l=1;l<n;l++){
        for(int i=1;i+l<=n;i++){
            int j=i+l;
            f[i][j]=f[i+1][j]^f[i][j-1];
            dp[i][j]=max(f[i][j],max(dp[i+1][j],dp[i][j-1]));
        }
    }
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&l,&r);
        printf("%d\n",dp[l][r]);
    }
    return 0;
}
