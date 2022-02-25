/*
题意:求a数组和b数组的最长公共上升子序列(LCIS).
数组长度<=500.
链接:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827365931
思路:O(n^2)求取LCIS并输出
dp[i][j]为当串a取前i个元素时(设为a[1 ~ i]),且当串b的子序列以j结尾时,它们的最长公共子序列长度.
dp[i][j]>=dp[i-1][j].
path[i][j].i path[i][j].j 分别记录串a取前i个元素时,串b的子序列以j结尾时,其LCIS上一状态记录的
是a串前path[i][j].i个元素,b数组以path[i][j].j结尾
这个做法因为要输出方案,所以只能二维数组O(n^2)实现.
*/
//ac 38ms LCIS 二维数组实现 O(n^2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 510
using namespace std;

int n,m,a[N],b[N],dp[N][N],ans;
struct Node{
    int i,j;
}path[N][N];
vector<int> res;

int main(){
    int T,mx,ti,tj,id;
    scanf("%d",&T);
    while(T--){
        res.clear();
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%d",&b[i]);
        for(int i=1;i<=n;i++){
            mx=0;
            ti=tj=0;//这里要初始化为0,有可能不存在上升序列,上一状态就是dp[0][0] 避免输出方案时死循环
            for(int j=1;j<=m;j++){
                dp[i][j]=dp[i-1][j];
                path[i][j].i=i-1;//初始状态直接继承上一状态
                path[i][j].j=j;
                if(a[i]>b[j] && mx<dp[i-1][j]){
                    mx=dp[i-1][j];
                    ti=i-1,tj=j;
                }
                else if(a[i] == b[j]){
                    dp[i][j]=mx+1;
                    path[i][j].i=ti;
                    path[i][j].j=tj;
                }
            }
        }
        ans=0;
        for(int i=1;i<=m;i++){
            if(ans<dp[n][i]){
                ans=dp[n][i];
                id=i;
            }
        }
        printf("%d\n",ans);
        int ni=n,nj=id;
        while(dp[ni][nj]!=0){
            int tpi,tpj;
            tpi=path[ni][nj].i,tpj=path[ni][nj].j;
            if(dp[ni][nj]!=dp[tpi][tpj])//有可能i增大,但实际 LCIS长度是不变的,这时并没有新的元素加入
                res.push_back(nj);
            ni=tpi,nj=tpj;
        }
        for(int i=res.size()-1;i>=0;i--)
            printf("%d ",b[res[i]]);
        if(T)
            printf("\n");
    }
    return 0;
}
