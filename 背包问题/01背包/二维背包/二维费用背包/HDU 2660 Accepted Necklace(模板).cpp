/*
题意:摘自网上
给出宝石的数目n，制成项链所需的宝石个数k，然后再给出每个宝石的价值a[i]与重量b[i]，
还有母亲会接受的最大重量w，求出在最大重量限制下，项链的价值尽可能大。
n<=20,k<=n,a[i],b[i]<=1000,w<=1000.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2660
思路:
两种解法:
1.dfs暴力枚举所有宝石选取的情况.2^n
2.二维费用背包.O(n^2*w)
*/
//ac 0ms dfs
//时间复杂度(2^n)=2^20=1048576 n太大就会TLE
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int n,k,w,a[N],b[N],ans;

void dfs(int i,int num,int suma,int sumb){
    if(num == k){
        if(suma>ans)
            ans=suma;
        return;
    }
    if(i == n+1)
        return;
    //num+n-i+1<k
    if(k-num>n-i+1)//剪枝:把后面的物品全部选上 数量还是达不到k,则返回
        return;
    if(sumb+b[i]<=w)
        dfs(i+1,num+1,suma+a[i],sumb+b[i]);
    dfs(i+1,num,suma,sumb);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&w);
        dfs(1,0,0,0);
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 0ms dfs+强剪枝(类背包) 最接近动态规划思想的暴力做法
//dp[i][sumb]表示前i个物品在重量为sumb时,最多能获得的价值
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int n,k,w,a[N],b[N],ans,dp[N][21000];

void dfs(int i,int num,int suma,int sumb){
    if(suma<=dp[i][sumb])
    	return;
    dp[i][sumb]=suma;
    if(num == k){
    	if(suma>ans)
    		ans=suma;
    	return;
	}
    if(i == n+1)
        return;
    if(sumb+b[i]<=w)
        dfs(i+1,num+1,suma+a[i],sumb+b[i]);
    dfs(i+1,num,suma,sumb);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        memset(dp,-1,sizeof(dp));
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&w);
        dfs(1,0,0,0);
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 0ms 二维费用01背包
//数量恰好装满,重量尽可能多地装满
//时间复杂度O(n^2*w)=20*20*1000=400000
//空间复杂度O(n*w)=20*1000=20000
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int n,k,w,a[N],b[N],dp[N][21000];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
    	memset(dp,-0x3f,sizeof(dp));
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&w);
        for(int i=0;i<=w;i++)
        	dp[0][i]=0;//物品数量恰好装满,物品重量尽可能多地装满
        for(int i=1;i<=n;i++){
        	for(int j=k;j>=1;j--){
        		for(int t=b[i];t<=w;t++)
        			dp[j][t]=max(dp[j][t],dp[j-1][t-b[i]]+a[i]);
			}
		}
        printf("%d\n",dp[k][w]);
    }
    return 0;
}
*/

/*
//ac 0ms 二维费用01背包
//数量、重量尽可能多地装满
//时间复杂度O(n^2*w)=20*20*1000=400000
//空间复杂度O(n*w)=20*1000=20000
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int n,k,w,a[N],b[N],dp[N][21000];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
    	//对于物品个数因为一个物品的属性就是数量1,恰好装满和尽可能多地装满含义是一样的
    	memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&w);
        for(int i=1;i<=n;i++){
        	for(int j=k;j>=1;j--){
        		for(int t=b[i];t<=w;t++)
        			dp[j][t]=max(dp[j][t],dp[j-1][t-b[i]]+a[i]);
			}
		}
        printf("%d\n",dp[k][w]);
    }
    return 0;
}
*/

/*
//循环模拟枚举物品组合方案 摘自博客:https://www.cnblogs.com/neverchanje/p/3552463.html
//因为stone个数才30，尝试看看暴力dfs解决此题（枚举）

#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=30;
const int maxc=1005;

int c,n,k,w,ans;
int a[maxn],b[maxn]; //a表示价值，b表示重量

//dfs（已经遍历的stone，necklace上的stone，necklace上stone的总重量，当前总价值）
void dfs(int curt,int curn,int curw,int curv){

    if(curn>k || curt>n || curw>w )
        return;
    if(curv>ans)
        ans=curv;
    for(int i=curt+1;i<=n;i++)//curt前面的一定无需遍历
        dfs(i,curn+1,curw+b[i],curv+a[i]);
}

int main (){
    cin>>c;
    while(c--){

        cin>>n>>k;//n为stone总个数，k为necklace所能容纳的个数
        for(int i=1;i<=n;i++)
            cin>>a[i]>>b[i];
        cin>>w;
        ans=0;
        dfs(0,0,0,0);
        cout<<ans<<endl;
    }
    return 0;
}
*/

/*
//ac 78ms 二进制枚举
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 25
#define INF 0x3f3f3f3f
using namespace std;

int n,k,w,a[N],b[N],ans;

int main(){
    int T,m,suma,sumb,id,cnt,flag,sta;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d%d",&n,&k);
        for(int i=0;i<n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&w);
        m=(1<<n)-1;
        for(int i=0;i<=m;i++){
        	flag=cnt=id=suma=sumb=0;
        	sta=i;
        	while(sta){
        		if(sta & 1){
        			cnt++;
        			suma+=a[id];
        			sumb+=b[id];
        			if(cnt>k|| sumb>w){
        				flag=1;
        				break;
					}
				}
				sta>>=1;
				id++;
			}
			if(cnt!=k)
				flag=1;
			if(!flag)
				ans=max(ans,suma);
		}
        printf("%d\n",ans);
    }
    return 0;
}
*/
