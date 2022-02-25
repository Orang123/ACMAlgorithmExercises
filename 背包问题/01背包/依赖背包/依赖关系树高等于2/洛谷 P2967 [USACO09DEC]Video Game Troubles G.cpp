/*
题意:农夫约翰的奶牛们打游戏上瘾了！本来约翰是想要按照调教兽的做法拿她们去电击戒瘾的,
可后来他发现奶牛们玩游戏之后比原先产更多的奶.很明显,这是因为满足的牛会产更多的奶.
但是,奶牛们因何者为最好的游戏主机而吵得不可开交.约翰想要在给定的预算内购入一些游戏
平台和一些游戏,使他的奶牛们生产最多的奶牛以养育最多的小牛.约翰考察了n种游戏主机,
第i种主机的价格是p,该主机有g个独占游戏.很明显,奶牛必须先买进一种游戏主机,才能买进在
这种主机上运行的游戏.在每种主机中,游戏k的价格为w[k],每头奶牛在玩了该游戏后的牛奶产量
为val[k].农夫约翰的预算为v.请帮助他确定应该买什么游戏主机和游戏,使得他能够获得的产出值的和最大.
链接:https://www.luogu.com.cn/problem/P2967
思路:和HDU 3449 一模一样10年多校,应该说HDU 3449完全抄袭的[USACO09DEC]Video Game Troubles G,
要买游戏就必须买这个游戏对应的主机,如果不买主机那么这个主机上的游戏就都不能买.
dp[i][j]前i台主机买对应游戏最多能获得的产出值.
先对主机内的游戏在dp[i-1][j]基础上继续01背包,对于主机当做有花费无价值的物品,也是在游戏01背包
完后的状态上继续01背包,只是对于不购买主机的的上一状态是前i-1台主机的最优解dp[i-1][j],因为不购
买主机当前主机的游戏就一定都不能买.
*/
//ac 898ms 依赖背包 一维数组实现
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 55
#define M 100010
using namespace std;

int n,v,tp[M],dp[M];

int main(){
    int p,g,w,val;
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&p,&g);
        for(int j=0;j<=v;j++)
            tp[j]=dp[j];
        for(int k=1;k<=g;k++){
            scanf("%d%d",&w,&val);
            for(int j=v-p;j>=w;j--)
                tp[j]=max(tp[j],tp[j-w]+val);
        }
        for(int j=v;j>=p;j--)
            dp[j]=max(dp[j],tp[j-p]);
    }
    printf("%d",dp[v]);
    return 0;
}

/*
//ac 100分 2.04s 分组背包当前组至少取一件(必须二维数组)和当前组一件也不选 求最优值
//复杂度O(nvmax(num[i]))=50*10^5*10=5*10^7
//初始化-INF 无需判断上一状态是否合法
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w,val,dp[N][M];

int main(){
    scanf("%d%d",&n,&v);
    memset(dp,-1,sizeof(dp));
    for(int i=0;i<=v;i++)
        dp[0][i]=0;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&p,&num);
        for(int k=1;k<=num;k++){
            scanf("%d%d",&w,&val);
            for(int j=v;j>=w;j--){
                //注意:这个题目各个物品价钱不会为0,判断转移顺序 可以任意 但是HDU 3449那题 调换顺序还是会wa,感觉可能输入数据仍旧存在体积为0的情况
                //第i组中的物品在前i-1组物品基础上至少放一个,需要付箱子和物品的价钱 箱子不产生价值
                if(j>=p+w && dp[i-1][j-p-w]!=-1)
                    dp[i][j]=max(dp[i][j],dp[i-1][j-p-w]+val);
                //第i组中的物品物品已经选过基础上在选别的物品 01背包,箱子的钱已经付过 无需再付
                if(dp[i][j-w]!=-1)
                    dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
            }
        }
        //比较至少选一个第i组物品和第i组物品一个也不选(前i-1组物品最优解dp[i-1][j])哪个价值更大
        for(int j=0;j<=v;j++)
            dp[i][j]=max(dp[i][j],dp[i-1][j]);
    }
    printf("%d\n",dp[n][v]);
    return 0;
}
*/

/*
滚动数组优化 两个数组dp[M]和tp[M]
分组背包当前组至少取一件(必须二维数组)和当前组一件也不选 求最优值
先考虑购买主机,再在已购买主机基础上购买对应的游戏
做法参见HDU 3449
*/

/*
//TLE 78分 分组背包 每组物品至多选一个,每组物品可能选取情况 dfs暴力枚举+剪枝
//复杂度 50*10^5*1024=5*10^9 在这个基础上会降低一点 但还是TLE了
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 55
#define M 100010
using namespace std;

int n,v,p,num,w[11],val[11],dp[M];
struct Node{
    int w,val;
    Node(int w=0,int val=0):w(w),val(val){}
};
vector<Node> a[N];

void dfs(int i,int k,int tw,int tv){
    if(k == num+1){
        //剪枝 如果第i组之前选取的游戏组合情况 存在相对当前组合,体积并不大于当前组合体积
        //价值也并不低于当前组合,那就没必要选取当前这种组合,并没有比之前的组合情况更优
        //简而言之就是体积大而价值小的组合对于最优解的求取没有帮助
        for(Node & x : a[i]){
            if(x.w<=tw && x.val>=tv)
                return;
        }
        a[i].push_back(Node(tw,tv));
        return;
    }
    if(tw+w[k]<=v)
        dfs(i,k+1,tw+w[k],tv+val[k]);
    dfs(i,k+1,tw,tv);
}

int main(){
    scanf("%d%d",&n,&v);
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++)
        a[i].clear();
    for(int i=1;i<=n;i++){
        scanf("%d%d",&p,&num);
        for(int k=1;k<=num;k++)
            scanf("%d%d",&w[k],&val[k]);
        //暴力搜索第i组主机的持有游戏可能选取情况
        dfs(i,1,p,0);//第i组主机要买 必须先买主机,才能买游戏,主机不产生价值
    }
    //每组物品至多选取一个
    for(int i=1;i<=n;i++){
        for(int j=v;j>=1;j--){
            for(Node & k :  a[i]){
                if(j>=k.w)
                    dp[j]=max(dp[j],dp[j-k.w]+k.val);
            }
        }
    }
    printf("%d",dp[v]);
    return 0;
}
*/

/*
//TLE 62分 分组背包做法
//可以将每个主机和其所能持有游戏的所有组合情况单独作为一组,这样就能保证购买游戏一定先购买了主机.
//因为每个主机最多只有10个游戏可以二进制枚举子集构造出所有组合构成的单独物品的体积、价值,做分组背包.
//但这个复杂度有点大 50*10^5*1024=5*10^9
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 55
#define M 100010
using namespace std;

int n,v,gp[11],pv[11],w[N][1050],val[N][1050],num[N],dp[M];

int main(){
    int p,g;
    memset(num,0,sizeof(num));
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&p,&g);
        for(int j=1;j<=g;j++)
            scanf("%d%d",&gp[j],&pv[j]);
        int k=(1<<g)-1;
        //枚举 主机+2^g种可能的游戏组合 单独作为第i组内的物品
        for(int j=1;j<=k;j++){
            int tp=j,t=1;
            num[i]++;
            while(tp){
                if(tp & 1){
                    w[i][num[i]]+=gp[t];
                    val[i][num[i]]+=pv[t];
                }
                tp>>=1;
                t++;
            }
            w[i][num[i]]+=p;//当前游戏组合加上主机的价钱
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=v;j>=1;j--){
            for(int k=1;k<=num[i];k++){
                if(j>=w[i][k])
                    dp[j]=max(dp[j],dp[j-w[i][k]]+val[i][k]);
            }
        }
    }
    printf("%d",dp[v]);
    return 0;
}
*/
