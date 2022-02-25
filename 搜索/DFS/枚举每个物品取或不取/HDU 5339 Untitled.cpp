/*
题意:摘自网上
给出一个a,还有n个数字b[1..n];
然后从n个数字中选出r个排列;
要求a % c1 % c2 % c3......%cr = 0;
问最少选几个;
n<=20,a<=10^6
链接:https://acm.hdu.edu.cn/showproblem.php?pid=5339
思路:对于取余,如果除数大于a,取余后的结果还是被除数
本身,因此要把除数大于a得的值删去,在取余过程中如果先
对较小数取余,再对较大数取余是没有意义的,因为较小数
取余的结果一定小于后面较大的余数,后面取余的结果一定是
这个数本身,无意义.因此取余只要从较大数开始取余,再对较小数
取余,将b数组按照从大到小排序,对每个b[1..n]中的b[i]都存在两种情况
要么取余要么不取余,这样就能遍历所有取余的所有情况.
*/
//ac 0ms dfs回溯从较大b[i]开始取余
//复杂度O(2^20)=1048576
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int n,a,b[N],ans,cnt;

void dfs(int i,int k,int val){
    if(k>=ans)
        return;
    if(!val){
        if(k<ans)
            ans=k;
        return;
    }
    if(i == n+1)
        return;
    dfs(i+1,k+1,val%b[i]);
    dfs(i+1,k,val);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        scanf("%d%d",&n,&a);
        for(int i=1;i<=n;i++){
            scanf("%d",&b[i]);
            if(b[i]>a){
                n--;
                i--;
            }
        }
        sort(b+1,b+1+n,greater<int>());
        dfs(1,0,a);
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("-1\n");
    }
    return 0;
}

/*
//ac 15ms dfs回溯 枚举排列,对余数大于被除数的情况要过滤
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int n,a,b[N],vis[N],cnt,ans;

void dfs(int k,int val){
    if(k>=ans)
        return;
    if(!val){
        if(k<ans)
            ans=k;
        return;
    }
    if(k == cnt+1)
        return;
    for(int i=1;i<=cnt;i++){
        if(!vis[i] && val>=b[i]){
            vis[i]=1;
            dfs(k+1,val%b[i]);
            vis[i]=0;
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=INF;
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&n,&a);
        for(int i=1;i<=n;i++)
            scanf("%d",&b[i]);
        sort(b+1,b+1+n);
        cnt=n;
        for(int i=1;i<=n;i++){
            if(b[i]>a){
                cnt=i-1;
                break;
            }
        }
        dfs(0,a);
        if(ans!=INF)
            printf("%d\n",ans);
        else
            printf("-1\n");
    }
    return 0;
}
*/
