/*
题意:对于吃货来说,过年最幸福的事就是吃了,没有之一！
但是对于女生来说,卡路里（热量）是天敌啊！资深美女湫湫
深谙“胖来如山倒,胖去如抽丝”的道理,所以她希望你能帮忙制
定一个食谱,能使她吃得开心的同时,不会制造太多的天敌.
当然,为了方便你制作食谱,湫湫给了你每日食物清单,上面描述
了当天她想吃的每种食物能带给她的幸福程度a[i],以及会增加的卡路里量b[i].
求解在满足卡路里吸收量的同时,湫湫可获得的最大幸福值.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4508
思路:裸题的完全背包
*/
//ac 46ms 一维数组
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;
int n,m,a[N],b[N],dp[M];
int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&m);
        for(int i=1;i<=n;i++)
            for(int j=b[i];j<=m;j++)
                dp[j]=max(dp[j],dp[j-b[i]]+a[i]);
        printf("%d\n",dp[m]);
    }
    return 0;
}

/*
//ac 140ms 一维数组 dp第一阶段升序枚举背包容量
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;
int n,m,a[N],b[N],dp[M];
int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&m);
        for(int j=0;j<=m;j++){
            for(int i=1;i<=n;i++){
                if(j>=b[i])
                    dp[j]=max(dp[j],dp[j-b[i]]+a[i]);
            }
        }
        printf("%d\n",dp[m]);
    }
    return 0;
}
*/

/*
//ac 171ms 朴素01背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;
int n,m,a[N],b[N],dp[M];
int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&m);
        int tb,ta;
        for(int i=1;i<=n;i++){
            for(tb=b[i],ta=a[i];tb<=m;tb+=b[i],ta+=a[i]){
                for(int j=m;j>=tb;j--)
                    dp[j]=max(dp[j],dp[j-tb]+ta);
            }
        }
        printf("%d\n",dp[m]);
    }
    return 0;
}
*/

/*
//ac 187ms 朴素01背包 背包容量在第二层和物品种类个数在第三层循环,顺序颠倒
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;
int n,m,a[N],b[N],dp[M];
int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&m);
        int tb,ta;
        for(int i=1;i<=n;i++){
            for(int j=m;j>=b[i];j--){
                for(tb=b[i],ta=a[i];tb<=j;tb+=b[i],ta+=a[i])
                    dp[j]=max(dp[j],dp[j-tb]+ta);
            }
        }
        printf("%d\n",dp[m]);
    }
    return 0;
}
*/

/*
//ac 93ms 01背包 二进制优化
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;
int n,m,a[N],b[N],dp[M];
int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&m);
        int tb,ta;
        for(int i=1;i<=n;i++){
            for(tb=b[i],ta=a[i];tb<=m;tb<<=1,ta<<=1){
                for(int j=m;j>=tb;j--)
                    dp[j]=max(dp[j],dp[j-tb]+ta);
            }
        }
        //背包容量在前,物品种类在后 就会出错,因为在二进制左移最大值大于m不恰好等于m的情况时
        //无法满足在背包容量=m最大时,放入背包容量限制下 最多数量的第i种物品的可能,
        //for(int i=1;i<=n;i++){
            //for(int j=m;j>=b[i];j--)
                //for(tb=b[i],ta=a[i];tb<=j;tb<<=1,ta<<=1)
                    //dp[j]=max(dp[j],dp[j-tb]+ta);
        //}
        printf("%d\n",dp[m]);
    }
    return 0;
}
*/

/*
//MLE 二维数组 空间开销10^7
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;
int n,m,a[N],b[N],dp[N][M];
int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&m);
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++){
                if(j>=b[i])
                    dp[i][j]=max(dp[i-1][j],dp[i][j-b[i]]+a[i]);
                else
                    dp[i][j]=dp[i-1][j];
            }
        }
        printf("%d\n",dp[n][m]);
    }
    return 0;
}
*/

/*
//ac 717ms bfs广搜暴力枚举状态进行转移
//不加if(tp.a+a[i]>dp[tp.b+b[i]]) 剪枝会MLE,枚举的状态点太多压入队列,自然也是tle
//每个状态都有n种可能的转移,最坏情况下,每个物品体积为1,最坏时间复杂度 感觉也不是个多项式时间
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;
//dp[i]=j,代表当前所选物品所占体积为i时所获得的最大价值为j.
int n,m,a[N],b[N],dp[M],ans;

struct State{
    int a,b;
    State(int a=0,int b=0):a(a),b(b){}
};

//每个状态都有n种可能的转移,最坏情况下,每个物品体积为1,最坏时间复杂度 感觉也不是个多项式时间
void bfs(){
    queue<State> Q;
    Q.push(State(0,0));
    State tp;
    while(!Q.empty()){
        tp=Q.front();
        Q.pop();
        if(ans<tp.a)
            ans=tp.a;
        for(int i=1;i<=n;i++){
            //体积超过背包容量m 也不必入队
            if(tp.b+b[i]>m) continue;
            //剪枝 如果当前状态下tp所选物品占体积为tp.b+b[i]所能获得的价值比之前记录的dp[tp.b+b[i]]最优值还小就不必入队.
            if(tp.a+a[i]>dp[tp.b+b[i]]){
                dp[tp.b+b[i]]=tp.a+a[i];
                Q.push(State(tp.a+a[i],tp.b+b[i]));
            }
        }
    }
}

int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        ans=0;
        for(int i=1;i<=n;i++)
            scanf("%d%d",&a[i],&b[i]);
        scanf("%d",&m);
        bfs();
        printf("%d\n",ans);
    }
    return 0;
}
*/
