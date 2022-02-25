/*
题意:在一个圆形操场的四周摆放N堆石子,现要将石子有次序地合并成一堆.
规定每次只能选相邻的2堆合并成新的一堆，并将新的一堆的石子数，记为该次合并的得分。
试设计出一个算法,计算出将N堆石子合并成1堆的最小得分和最大得分。
N<=100.
链接:https://www.luogu.com.cn/problem/P1880
思路:
枚举区间长度后枚举起始端点
此题石子堆呈圆形环装排列,在此之前是链状.
那么就存在第1堆石子和第n堆石子合并的情形,但与此同时,第1堆也不可能和第2堆有合并,
事实上即使排列成环状,我们发现相比原先链状排列,它只是多余出第1堆与第n堆有可能合并这种情况,但无论怎么合并,
当剩下最后两堆的时候,这两堆相邻的就是绝对没有合并的,这本身就是一个链状的问题.
最终都存在着2堆没有和相邻的合并,那实际上我们可以将这个环状 枚举分割点转化成一个链状的问题.
如以1为分割点 区间变成[2,n+1](1 2不相邻),2为分割点区间变成[3,n+2](2 3不相邻).
n-1为分割点区间变成[n,2n-1](n n-1不相邻) [1,n](1 n不相邻)
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp1[220][220],dp2[220][220],sum[220];
int main(){
    int minc=INF,maxc=-1;
    memset(dp1,INF,sizeof(dp1));//dp1计算最小值
    memset(dp2,-1,sizeof(dp2));//dp2计算最大值
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i+n]=sum[i];//第i堆与第i+n堆是一样的,如第n堆与第n+1对相邻,实际就是第n堆与第1堆相邻.
        dp1[i][i]=dp1[i+n][i+n]=0;
        dp2[i][i]=dp2[i+n][i+n]=0;
    }
    for(int i=1;i<=2*n-1;i++)//可能的链状区间[1,n] [2,n+1] [3,n+2] ...[n,2n-1] [n+1,2n]和[1,n]是重复的区间
        sum[i]+=sum[i-1];
    for(int l=1;l<=n-1;l++){
        for(int i=1;i+l<=2*n-1;i++){//区间的起点上界2n-1,这个子问题是为更大长度包含n~2n-1这些点的大区间而合并的
            int j=i+l;
            for(int k=i;k<j;k++){//枚举区间分割点,这个区间可以由几组2个最终子区间合并而成,计算最优解.
                dp1[i][j]=min(dp1[i][j],dp1[i][k]+dp1[k+1][j]+sum[j]-sum[i-1]);
                dp2[i][j]=max(dp2[i][j],dp2[i][k]+dp2[k+1][j]+sum[j]-sum[i-1]);
            }
        }
    }
    /*
    [1,n] [2,n+1] [3,n+2] 它们分别忽略了相邻的1 n合并 1 2合并 2 3合并等情况,
    实际就是将环状问题拆分成n条链状的问题,暴力比较更新最优解.
    */
    for(int i=1;i<=n;i++){
        minc=min(minc,dp1[i][i+n-1]);
        maxc=max(maxc,dp2[i][i+n-1]);
    }
    printf("%d\n",minc);
    printf("%d\n",maxc);
    return 0;
}
/*
先枚举区间左端点,后枚举右端点
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp1[220][220],dp2[220][220],sum[220];
int main(){
    int minc=INF,maxc=-1;
    memset(dp1,INF,sizeof(dp1));
    memset(dp2,-1,sizeof(dp2));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i+n]=sum[i];
        dp1[i][i]=dp1[i+n][i+n]=0;
        dp2[i][i]=dp2[i+n][i+n]=0;
    }
    for(int i=1;i<=2*n-1;i++)
        sum[i]+=sum[i-1];
    for(int i=2*n-2;i>=1;i--){//枚举区间左端点 每一次都是新的区间
        for(int j=i+1;j<=2*n-1;j++){//枚举区间右端点 区间大小不断递增,但都是新的区间因为右端点不同,由小状态向打状态转移
            for(int k=i;k<j;k++){
               dp1[i][j]=min(dp1[i][j],dp1[i][k]+dp1[k+1][j]+sum[j]-sum[i-1]);
               dp2[i][j]=max(dp2[i][j],dp2[i][k]+dp2[k+1][j]+sum[j]-sum[i-1]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        minc=min(minc,dp1[i][i+n-1]);
        maxc=max(maxc,dp2[i][i+n-1]);
    }
    printf("%d\n",minc);
    printf("%d\n",maxc);
    return 0;
}
*/

/*
先枚举区间右端点,再枚举左端点
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp1[220][220],dp2[220][220],sum[220];
int main(){
    int minc=INF,maxc=-1;
    memset(dp1,INF,sizeof(dp1));
    memset(dp2,-1,sizeof(dp2));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i+n]=sum[i];
        dp1[i][i]=dp1[i+n][i+n]=0;
        dp2[i][i]=dp2[i+n][i+n]=0;
    }
    for(int i=1;i<=2*n-1;i++)
        sum[i]+=sum[i-1];
    for(int j=2;j<=2*n-1;j++){//枚举区间右端点 每一次都是新的区间
        for(int i=j-1;i>=1;i--){//枚举区间左端点 区间大小不断递增,但都是新的区间因为左端点不同,由小状态向打状态转移
            for(int k=i;k<j;k++){
               dp1[i][j]=min(dp1[i][j],dp1[i][k]+dp1[k+1][j]+sum[j]-sum[i-1]);
               dp2[i][j]=max(dp2[i][j],dp2[i][k]+dp2[k+1][j]+sum[j]-sum[i-1]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        minc=min(minc,dp1[i][i+n-1]);
        maxc=max(maxc,dp2[i][i+n-1]);
    }
    printf("%d\n",minc);
    printf("%d\n",maxc);
    return 0;
}
*/
/*
记忆化搜索分n次计算dfs(i,i+n-1)
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp1[220][220],dp2[220][220],sum[220];

void dfs(int st,int ed){//O(n^3)
    if(dp1[st][ed]|| dp2[st][ed]) return;//实际只需判断dp1即可,因为dp1和dp2是同时更新的.
    if(st == ed){
        dp1[st][ed]=dp2[st][ed]=0;
        return;
    }
    int ans1=INF,ans2=-1;
    for(int i=st+1;i<=ed;i++){
        dfs(st,i-1),dfs(i,ed);
        ans1=min(ans1,dp1[st][i-1]+dp1[i][ed]+sum[ed]-sum[st-1]);
        ans2=max(ans2,dp2[st][i-1]+dp2[i][ed]+sum[ed]-sum[st-1]);
    }
    dp1[st][ed]=ans1;
    dp2[st][ed]=ans2;
}

int main(){
    int minc=INF,maxc=-1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i+n]=sum[i];
    }
    for(int i=1;i<=2*n-1;i++)
        sum[i]+=sum[i-1];
    for(int i=1;i<=n;i++){//O(n^4)
        dfs(i,i+n-1);//前面求得的某些dp值会保存起来再次使用
        minc=min(minc,dp1[i][i+n-1]);
        maxc=max(maxc,dp2[i][i+n-1]);
    }
    printf("%d\n",minc);
    printf("%d\n",maxc);
    return 0;
}
*/
/*
记忆化搜索直接求1~2n-1 区间,虽然[1,2*n-1]不是我们要求的,但因为分治法,它的区间内任意小区间必然也会求出来.dfs(1,2*n-1);
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n,dp1[220][220],dp2[220][220],sum[220];

void dfs(int st,int ed){
    if(dp1[st][ed]|| dp2[st][ed]) return;//实际只需判断dp1即可,因为dp1和dp2是同时更新的.
    if(st == ed){
        dp1[st][ed]=dp2[st][ed]=0;
        return;
    }
    int ans1=INF,ans2=-1;
    for(int i=st+1;i<=ed;i++){
        dfs(st,i-1),dfs(i,ed);
        ans1=min(ans1,dp1[st][i-1]+dp1[i][ed]+sum[ed]-sum[st-1]);
        ans2=max(ans2,dp2[st][i-1]+dp2[i][ed]+sum[ed]-sum[st-1]);
    }
    dp1[st][ed]=ans1;
    dp2[st][ed]=ans2;
}

int main(){
    int minc=INF,maxc=-1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sum[i]);
        sum[i+n]=sum[i];
    }
    for(int i=1;i<=2*n-1;i++)
        sum[i]+=sum[i-1];
    //虽然合理的区间大小是n,但是因为dfs是分治法,我们直接求[1,2*n-1],那么这个区间内任意区间长度的小区间都分治求解出来
    dfs(1,2*n-1);
    for(int i=1;i<=n;i++){
        minc=min(minc,dp1[i][i+n-1]);
        maxc=max(maxc,dp2[i][i+n-1]);
    }
    printf("%d\n",minc);
    printf("%d\n",maxc);
    return 0;
}
*/
