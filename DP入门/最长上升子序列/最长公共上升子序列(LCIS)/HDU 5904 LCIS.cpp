/*
题意:摘自网上
求两数串的最长公共子序列，且子序列为1的递增
数串长度<=10^5.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=5904
思路:LCIS.
*/
//ac 343ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

//a[x]表示a串子序列递增+1至截止到数值x的最大长度
//b[x]表示b串子序列递增+1至截止到数值x的最大长度
int n,m,a[N],b[N],ans;

int main(){
    int T,x;
    scanf("%d",&T);
    while(T--){
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        ans=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%d",&x);
            a[x]=a[x-1]+1;
        }
        for(int i=1;i<=m;i++){
            scanf("%d",&x);
            b[x]=b[x-1]+1;
            //min(a[x],b[x])的最小值表示在递增子序列中公共的子序列的最大长度
            ans=max(ans,min(a[x],b[x]));
        }
        printf("%d\n",ans);
    }
    return 0;
}
