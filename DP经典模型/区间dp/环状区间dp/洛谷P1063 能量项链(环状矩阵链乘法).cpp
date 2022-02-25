#include<cstdio>//区间dp
#include<cstring>
#include<algorithm>
using namespace std;

/*
链接:https://www.luogu.com.cn/problem/P1063
题意:就是环状的矩阵链连乘问题,数组扩展成2*n即可.
*/

int a[210],dp[210][210];

int main(){
    int n,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i+n]=a[i];
    }
    for(int l=1;l<n;l++){
        for(int i=1;i+l<2*n;i++){
            int j=i+l;
            for(int k=i;k<j;k++){
                dp[i][j]=max(dp[i][j],a[i]*a[k+1]*a[j+1]+dp[i][k]+dp[k+1][j]);
            }
        }
    }
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[i][i+n-1]);
    printf("%d",ans);
    return 0;
}

/*
记忆化搜索
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

//链接:https://www.luogu.com.cn/problem/P1063
int a[210],dp[210][210];

int dfs(int i,int j){
    if(i == j) return 0;
    if(dp[i][j]) return dp[i][j];
    for(int k=i;k<j;k++)
        dp[i][j]=max(dp[i][j],a[i]*a[k+1]*a[j+1]+dfs(i,k)+dfs(k+1,j));
    return dp[i][j];
}

int main(){
    int n,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i+n]=a[i];
    }
    dfs(1,2*n-1);
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[i][i+n-1]);
    printf("%d",ans);
    return 0;
}
*/

/*
设置l,r的结构体dp求解
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

//链接:https://www.luogu.com.cn/problem/P1063
struct Node{
    int l,r;
}node[220];

int a[210],dp[210][210];

int main(){
    int n,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&node[i].l);
    node[n+1].l=node[1].l;
    for(int i=1;i<=n;i++){
        node[i].r=node[i+1].l;
        node[i+n]=node[i];
    }
    for(int l=1;l<n;l++){
        for(int i=1;i+l<2*n;i++){
            int j=i+l;
            for(int k=i;k<j;k++){
                dp[i][j]=max(dp[i][j],node[i].l*node[k+1].l*node[j].r+dp[i][k]+dp[k+1][j]);
            }
        }
    }
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[i][i+n-1]);
    printf("%d",ans);
    return 0;
}
*/
/*
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

//链接:https://www.luogu.com.cn/problem/P1063

int a[210],dp[210][210];

int main(){
    int n,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i+n]=a[i];
    }
    for(int l=1;l<n;l++){
        for(int i=1;i+l<2*n;i++){
            int j=i+l;
            for(int k=i;k<j;k++){
                dp[i][j]=max(dp[i][j],a[i]*a[k+1]*a[j+1]+dp[i][k]+dp[k+1][j]);
            }
        }
    }
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[i][i+n-1]);
    printf("%d",ans);
    return 0;
}
*/


