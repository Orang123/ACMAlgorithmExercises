//�Զ�����dp ʱ�临�Ӷ�O(N^2)
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110];
/*
����:ÿһ���һ����ֻ�ܳ�����һ������»�������,�ʴӶ����ߵ���ײ�����е�Ȩֵ����
����:http://poj.org/problem?id=1163
*/

int main(){
    int n,ans=-1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++)
            scanf("%d",&dp[i][j]);
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<=i;j++){
            dp[i][j]+=max(dp[i-1][j-1],dp[i-1][j]);
        }
    }
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[n][i]);
    printf("%d",ans);
    return 0;
}

/*
�Ե�����dp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110];

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++)
            scanf("%d",&dp[i][j]);
    }
    for(int i=n;i>=2;i--){
        for(int j=1;j<i;j++){
            dp[i-1][j]+=max(dp[i][j],dp[i][j+1]);
        }
    }
    printf("%d",dp[1][1]);
    return 0;
}
*/
/*
���仯���� �ӵ�n����n-1��...1��ֽ�
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110],a[110][110];

int dfs(int i,int j){
    if(!j) return 0;
    if(j>i) return 0;
    if(dp[i][j]) return dp[i][j];
    dp[i][j]=a[i][j]+max(dfs(i-1,j-1),dfs(i-1,j));
    return dp[i][j];
}

int main(){
    int n,ans=-1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++)
            scanf("%d",&a[i][j]);
    }
    for(int i=1;i<=n;i++)
        ans=max(ans,dfs(n,i));
    printf("%d",ans);
    return 0;
}
*/
/*
���仯���� �ӵ�1�����n��ֽ�
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,dp[110][110],a[110][110];

int dfs(int i,int j){
    if(i==n) return a[i][j];
    if(dp[i][j]) return dp[i][j];
    dp[i][j]=a[i][j]+max(dfs(i+1,j),dfs(i+1,j+1));
    return dp[i][j];
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++)
            scanf("%d",&a[i][j]);
    }
    printf("%d",dfs(1,1));
    return 0;
}
*/

/*
//ʱ�临�Ӷ� O(n*2^n) n ��ͳ�ı����������� ��TLE
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,a[110][110],ans;

void dfs(int i,int j,int sum){
    if(i == n){
        ans=max(ans,sum);
        return;
    }
    dfs(i+1,j,sum+a[i+1][j]);
    dfs(i+1,j+1,sum+a[i+1][j+1]);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++)
            scanf("%d",&a[i][j]);
    }
    dfs(1,1,a[1][1]);
    printf("%d",ans);
    return 0;
}
*/

