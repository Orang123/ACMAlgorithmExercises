#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;
//ac 31ms 01背包+贪心 背包容量尽可能多地装满

/*
题意:电子科大本部食堂的饭卡有一种很诡异的设计,即在购买之前判断余额.
如果购买一个商品之前,卡上的剩余金额大于或等于5元,就一定可以购买成功
(即使购买后卡上余额为负),否则无法购买(即使金额足够).所以大家都希望尽
量使卡上的余额最少.某天,食堂中有n种菜出售,每种菜可购买一次.已知每种菜
的价格以及卡上的余额,问最少可使卡上的余额为多少.
注意:买每一件物品都需保证卡上余额>=5,即使物品的价格小于5,卡余额小于5,
此时也不能购买该件物品.
eg:3个物品价格都为1,卡上初始余额6元,实际只能买2件物品,因为买第三件物品时,
只剩下4元,不够5元无法购买,最终卡上剩余钱为4元.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2546
思路:很明显卡可以有余额,属于01背包背包容量没有直接装满的情形,可以先贪心用
最低的5元买最贵的,之后对剩下的物品用01背包求解最多能买多少钱,那么最终剩下的
钱就是m-5-dp[m-5]+5-tp,m-5-dp[m-5]是买剩下物品所剩余的钱,tp为最贵物品的价格,
5-tp为买最贵物品剩下的钱,m-5-dp[m-5]为买剩下物品剩余的钱.
*/
int n,m,dp[N],val[N],tp,id;
int main(){
    while(scanf("%d",&n) && n){
        memset(dp,0,sizeof(dp));
        tp=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&val[i]);
            if(tp<val[i]){
                tp=val[i];
                id=i;//记录最贵物品编号
            }
        }
        scanf("%d",&m);
        if(m<5){//注意卡上初始余额 如果本身就小于5,则也无法购买,直接输出初始余额
            printf("%d\n",m);
            continue;
        }
        for(int i=1;i<=n;i++){
            for(int j=m-5;j>=val[i];j--){
                if(i!=id)//最贵物品已贪心处理过 不再购买
                    dp[j]=max(dp[j],dp[j-val[i]]+val[i]);
            }
        }
        printf("%d\n",m-5-dp[m-5]+5-tp);
    }
    return 0;
}

/*
//ac 15ms 01背包+贪心 背包容量恰好装满
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int n,m,dp[N],val[N],tp,id;
int main(){
    while(scanf("%d",&n) && n){
        memset(dp,-0x3f,sizeof(dp));
        tp=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&val[i]);
            if(tp<val[i]){
                tp=val[i];
                id=i;//记录最贵物品编号
            }
        }
        scanf("%d",&m);
        if(m<5){//注意卡上初始余额 如果本身就小于5,则也无法购买,直接输出初始余额
            printf("%d\n",m);
            continue;
        }
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int j=m-5;j>=val[i];j--){
                if(i!=id)//最贵物品已贪心处理过 不再购买
                    dp[j]=max(dp[j],dp[j-val[i]]+val[i]);
            }
        }
        int ans=0;//ans初始化为0 有可能m-5剩下的钱 不够买任何一件物品
        for(int i=m-5;i>=1;i--){//恰好装满 最少是花1元买一元的物品 所以下限是1
            if(dp[i]>0){//只有dp[i]>0的才是合法状态 恰好装满的情形
                ans=dp[i];
                //ans=i;//恰好装满,dp[i]和i是相等的ans=i,ans=dp[i]都是等价的
                break;
            }
        }
        //ans不初始化为0,for循环下限判断到0,dp[i]判断条件修改为dp[i]>=0也是可以的,如下
        //int ans;
        //for(int i=m-5;i>=0;i--)
            //if(dp[i]>=0)
        printf("%d\n",m-5-ans+5-tp);
    }
    return 0;
}
*/

/*
//ac 31ms 01背包 背包容量尽可能多装,排序,最贵的放在最后
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max(i,j) i>j?i:j
int dp[1000],a[1005];
int main(){
    int n,m;
    while(scanf("%d",&n)&&n){
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;i++)
            scanf("%d",a+i);
        sort(a,a+n);//把最贵的取出来
        scanf("%d",&m);
        if(m<5){
            printf("%d\n",m);
            continue;
        }
        m-=5;
        for(int i=0;i<n-1;i++){//先不买最贵的
            for(int j=m;j>=a[i];j--)
                    dp[j]=max(dp[j],dp[j-a[i]]+a[i]);
        }
        printf("%d\n",m-dp[m]+5-a[n-1]);//看差值+5剩下的与最贵的差值
    }
    return 0;
}
*/

/*
//TLE 暴力枚举搜索(未剪枝)
#include<cstdio>
#include<algorithm>
#define N 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,val[N],ans;

//2个剪枝未写
//剪枝1 m-5全部用完,即ans为0时可直接返回结果
//剪枝2 后缀剪枝
void dfs(int k,int curV,int sum){
    if(m-5-sum<ans)
        ans=m-5-sum;
    if(k == n) return;//最贵的物品不再购买
    if(curV>=val[k])
        dfs(k+1,curV-val[k],sum+val[k]);
    dfs(k+1,curV,sum);
}
int main(){
    while(scanf("%d",&n) && n){
        ans=INF;
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        scanf("%d",&m);
        if(m<5){//注意卡上初始余额 如果本身就小于5,则也无法购买,直接输出初始余额
            printf("%d\n",m);
            continue;
        }
        sort(val+1,val+1+n);
        dfs(1,m-5,0);
        printf("%d\n",ans+5-val[n]);
    }
    return 0;
}
*/
