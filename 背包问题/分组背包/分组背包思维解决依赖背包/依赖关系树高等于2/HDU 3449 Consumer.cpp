#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;
//ac 234ms 依赖背包 二维01背包实现
//这个二维做法它是提前考虑了 要放入第i组的附件,就必须先把主件的钱腾出来,假设已经先用p元买了主件,再去买附件的
//而我写的二维做法是把主件也完全当做一个价值为0的物品,先买附件后买主件,综合来讲我写的版本更易于理解
/*
我自己的思路:一维dp滚动数组的做法
//思路就是把所有物品都看成是一样的物品,只是对于主件只有价钱没有对应价值,然后所有物品01背包
//的顺序要按照后序遍历次序应该先放附件,后方主件,只是主件在进行01背包时,对于不选取主件其上一个
//状态并不是dp[i-1][j],因为不选主件所有附件件就都不能选,其上一个状态是除过这组所有num个子件之前
//的前i-num个物品的状态,因此此题输入数据已经将每组主件、附件区分开,所以每次在对每组物品进行01
//背包之前其前一组主件、附件的状态应该保留一份数组dp,用新的数组tp进行该组附件件的01背包,先对该组
//物品的附件件进行常规的01背包,之后对该组的主件进行01背包时,其前一状态是dp[j],当前放入主件的状态
//是tp[j-p]+0,因为其价值为0.
*/
/*
题意:n组物品,每组物品对应一个盒子,盒子的价格为p,每组物品有num个商品,
要购买商品必须购买该组物品对应的盒子才能将商品放入盒子,每个商品的价格
为w,价值为val,现在初始有v元钱,求购买商品最多能获得多少价值.
注意:购买盒子并不会获得价值.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3449
思路:和洛谷 P2967 [USACO09DEC]Video Game Troubles G 是同一道题
网上别人这个思路是要买商品获得价值,就必须先买盒子,每次在对商品进行
01背包之前,先假设买了主件,背包容量被腾空出p元,再去买商品的,最后再和
要购买商品必须先购买该组商品对应的盒子,而盒子本身没有价值.然后再比较
本身dp[i-1][j]和dp[i][j]的最优解,注意dp[i][j]是在dp[i-1][j-p]基础上进行01背包的,
所以比较的范围是[0,v]
属于依赖型背包可以用01背包来模拟.前i-1组的最优值先除去第i组盒子花费p
再继承前i-1组价钱减p后的最优值,并且初始状态对于j<p的状态设置为-1表示不合法.
之后再在第i组商品中建立在除去p元后的前i-1组物品最优值基础上进行01背包,
之后再比较新求解的前i组最优值dp[i][j]和前i-1组最优值dp[i-1][j]更新dp[i][j].

样例的最优解是选了第一组物品中的3件商品 价值80,花费300+25=325
第三组物品中的第2、3件商品 价值和70+60=130,花费400+40+35=475.
总价值=80+130=210,总花费=325+475=800.
*/
//dp[i][j]表示用j元购买前i组商品所能获得的最大价值
int n,v,p,num,w,val,dp[N][M];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        //对每组物品的盒子进行01背包
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            //第i组物品 首先要买盒子,在j<p时无法购买盒子 就无法购买该组中的商品,标记为-1(非法状态)
            for(int j=0;j<p;j++)//注意是<p,因为等于p已经可以买下第i组的盒子,是合法状态
                dp[i][j]=-1;//不合法状态初始化为-1,不能初始化为0,因为dp[i][p]=0是合法状态不好区分
            //第i组物品的最优解继承前i-1组物品的最优值,因为要买第i组的的盒子,
            //所以只继承价钱为j-p下的最优解,因为要在前i-1组状态的最优解腾出一部分钱用来买第i组的盒子
            //这样才能购买第i组内的商品
            //实际就是先买盒子只不过盒子价格为p,价值0
            for(int j=p;j<=v;j++)
                dp[i][j]=dp[i-1][j-p]+0;
            //对第i组物品内的商品进行01背包(仍然在前i-1组物品基础上)
            //注意这里dp[i][j]本身就是滚动数组优化过后的,这里的i是前i组,
            //dp[i-1][j]是前i-1组的状态,而现在是在第i组内进行01背包,所以只有第二维j是有用的
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                //dp[i][j]表示用j元购买在前i组物品基础上中对第i组前k个商品能获得的最大价值
                for(int j=v;j>=w;j--){
                    if(dp[i][j-w]!=-1)//j-w必须>=p,必须至少能够买下该组商品对应的盒子才能买该组内的商品
                        dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
                }
            }
            //这里是比较 前i-1组(dp[i-1][j])和在放入第i组商品dp[i][j]的最优值,
            //上述的01背包转移方程中只是比较第i组内前k个商品和前k-1个商品的值.
            //注意前i-1组,这里dp[i-1][j]中的j 并没有减去第i组盒子的费用p,最大价值和没有第i组的商品,
            //而dp[i][j]的最优值是在dp[i-1][j-p]基础上线腾出盒子的p元进行dp的,dp[i][j]中有可能混入了
            //前i-1组的商品和第i组的商品,现在只是比较求取dp[i][j]的最优值
            //因此j得到上下界为[0,v]
            for(int j=0;j<=v;j++)
                dp[i][j]=max(dp[i-1][j],dp[i][j]);
        }
        printf("%d\n",dp[n][v]);
    }
    return 0;
}
/*
//ac 249ms 二维数组 01背包 我自己理解的版本
//我写的二维做法是把主件也完全当做一个价值为0的物品,先买附件后买主件
//将上一组的状态保留为dp[i-1][j],先对附件进行01背包dp[i][j]滚动数组优化,
//再对主件进行01背包,这样在考虑不放入附件时,其上一组状态就是dp[i-1][j]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w,val,dp[N][M];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            //dp[i][j]继承上一组状态dp[i-1][j]
            for(int j=0;j<=v;j++)
                dp[i][j]=dp[i-1][j];
            //在该组商品内对附件进行01背包 采用滚动数组优化
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                for(int j=v-p;j>=w;j--){//j的上界可优化为v-p,因为在放入主件时,主件价格为p,dp[i][j-p],j-p最大只能是v-p
                    dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
                }
            }
            //在附件dp[i][j]基础上放入主件,对应的状态为dp[i][j-p]+0
            //若不放入主件,则所有的附件都不能放入,对应的上一状态是上一组的状态为dp[i-1][j]
            //将新的前i组物品的最优值赋值给dp[i][j],这里j必须降序才能保证dp[i][j-p]是没放入主件之前的状态
            for(int j=v;j>=0;j--){//这里j的下界是0,因为dp[i][j]中对附件进行01背包时,j<p的最优解也被更新了,但实际j<p是不能放入附件的,所以要重新继承上一状态dp[i-1][j]
                if(j>=p)
                    dp[i][j]=max(dp[i-1][j],dp[i][j-p]);
                else//如果不能放入主件,则继承上一组dp[i-1][j]的状态
                    dp[i][j]=dp[i-1][j];
            }
        }
        printf("%d\n",dp[n][v]);
    }
    return 0;
}
*/

/*
//ac 171me 依赖背包 滚动数组优化01背包实现
//滚动数组优化 前i组的维度,用2个数组实现,tp数组进行第i组内的01背包
//dp数组记录前i-1组的最优值,先
//将总价钱v直接先除去第i组的盒子钱,先进行裸的01背包
//之后将第i组状态tp[j-p]和前i-1组状态dp[j]比较最优值,因为在购买第i组商品需要先
//购买第i组的盒子,下限是p+1,小于等于p的直接按保持前i-1组的状态不变,因为根本买不了第i组的商品.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w,val,dp[M],tp[M];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            //将前i-1组的状态直接赋值给第i组状态
            memcpy(tp,dp,sizeof(dp));
            //第i组内商品除去盒子费用p进行裸的01背包
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                for(int j=v-p;j>=w;j--)//因为p元必须用来买盒子,所以最多能用v-p元买商品
                    tp[j]=max(tp[j],tp[j-w]+val);
            }
            //j<=p 根本不能买第i组商品,注意<p买不了盒子,=p只能买盒子,买不了商品,也无意义
            //现在要考虑在原先tp[j]最优值基础上除去买盒子的钱,即只能保留tp[j-p]
            //将前i组商品状态tp[j-p]与前i-1组商品dp[j]状态(不包含第i组的商品价值)比较求取最优值
            //新的前i组商品最优值赋值给dp[j]
            for(int j=p+1;j<=v;j++)
                dp[j]=max(tp[j-p],dp[j]);//因为对于第i组商品来说,要留出p元用来买盒子,所以前i组状态tp,支取tp[j-p]
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 171ms 我自己想到的最简单的01背包
//思路就是把所有物品都看成是一样的物品,只是对于主件只有价钱没有对应价值,然后所有物品01背包
//的顺序要按照后序遍历次序应该先放子件,后方主件,只是主件在进行01背包时,对于不选取主件其上一个
//状态并不是dp[i-1][j],因为不选主件所有子件就都不能选,其上一个状态是除过这组所有num个子件之前
//的前i-num个物品的状态,因此此题输入数据已经将每组主件、子件区分开,所以每次在对每组物品进行01
//背包之前其前一组主件、子件的状态应该保留一份数组dp,用新的数组tp进行该组子件的01背包,先对该组
//物品的子件进行常规的01背包,之后对该组的主件进行01背包时,其前一状态是dp[j],当前放入主件的状态
//是tp[j-p]+0,因为其价值为0.
//复杂度O(nvmax(num[i]))=50*10^5*10=5*10^7
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w,val,dp[M],tp[M];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            //将上一组物品状态赋值给tp,那tp进行该组物品的01背包
            //dp作为上一组物品的状态
            memcpy(tp,dp,sizeof(dp));
            //先对该组物品的子件进行01背包
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                for(int j=v;j>=w;j--)//这里其实j>=v-p的部分 tp[j],在放入主件并不能用到,所以可以考虑优化上界为j=v-p.
                    tp[j]=max(tp[j],tp[j-w]+val);
            }
            //再对该组物品的主件进行01背包
            //注意不选主件那么其所有子件都不能选,即:前上一状态是前一组物品的状态dp[j]
            for(int j=v;j>=p;j--)//这里j升序降序都是 不影响的
                dp[j]=max(dp[j],tp[j-p]);
            //j<p时,本身就不能放下第i组物品的主件,所以dp[j]还是上一组物品的dp[j],因此dp[j]更新完毕作为新的前i组物品的最优解
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//因为N*M<=5.6*10^7 MLE dfs按照依赖后序次序 进行01背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 560
#define M 100100
using namespace std;

//假设i节点在dfs后续遍历得到次序为k
//dp[i][j] 代表dfs后续遍历前k个次序的物品在j元钱限制下所能获得的最大价值
int cnt,head[N];
int n,m,p,num,k,w[N],val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        for(int j=0;j<=m;j++)
            dp[v][j]=dp[u][j];
        dfs(v);
        for(int j=m;j>=w[v];j--)
            //假设选取盒子,那么实际dp[v][j]中最优值只能选择dp[v][j-w[v]]时的最优值,因为需要腾出w[v]买盒子,才能买附件
            dp[u][j]=max(dp[u][j],dp[v][j-w[v]]+val[v]);//实际盒子的val[v]为0,但这并不影响最优值
    }
}

int main(){
    int rt;
    while(scanf("%d%d",&n,&m)!=EOF){
        k=0;
        memset(head,-1,sizeof(head));
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            k++;
            scanf("%d%d",&w[k],&num);
            rt=k;
            addEdge(0,rt);
            while(num--){
                k++;
                scanf("%d%d",&w[k],&val[k]);
                addEdge(rt,k);
            }
        }
        dfs(0);
        printf("%d\n",dp[0][m]);
    }
    return 0;
}
*/

/*
//ac 343ms 分组背包当前组至少取一件(但是主件必须买)和当前组一件也不选 求最优值
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
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        for(int i=0;i<=v;i++)
            dp[0][i]=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                for(int j=v;j>=w;j--){
                    //注意:虽然这个题目各个物品价钱不会为0,但是判断顺序还是不能从dp[i-1][j-p-w]转移 否则会wa 暂不清楚原因
                    //第i组中的物品物品已经选过基础上在选别的物品 01背包,箱子的钱已经付过 无需再付
                    dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
                    //第i组中的物品在前i-1组物品基础上至少放一个,需要付箱子和物品的价钱 箱子不产生价值
                    if(j>=p+w)
                        dp[i][j]=max(dp[i][j],dp[i-1][j-p-w]+val);
                }
            }
            //比较至少选一个第i组物品和第i组物品一个也不选(前i-1组物品最优解dp[i-1][j])哪个价值更大
            for(int j=0;j<=v;j++)
                dp[i][j]=max(dp[i][j],dp[i-1][j]);
        }
        printf("%d\n",dp[n][v]);
    }
    return 0;
}
*/

/*
//ac 390ms 分组背包每组至少取一件和当前组一件也不选 求最优值
//初始化为0 需判断上一状态是否合法
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w,val,dp[N][M];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                for(int j=v;j>=w;j--){
                    if(dp[i][j-w])//不判断 会导致直接从dp[i][j-w]=0开始累加,导致并没算上 第i组必须的箱子的钱,导致结果偏大 会wa
                        dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
                    //dp[i-1][j-p-w]本身就是>=0的,即: 但是等于0的情况除了背包容量本身为0外,其余等于0的状态其实是不合法的,但加上也不会影响结果
                    //因为不合法状态累加价值本身也就不是最优的
                    //实际这个初始化为0的做法 严格来讲是有问题的
                    //正解是memset(dp,-1,sizeof(dp)) dp[0][0..v]=0,判断dp[i][j-w]!=-1和dp[i-1][j-p-w]!=-1
                    if(j>=p+w)//dp[i-1][j-p-w]>=0可以不判断 因为如果本身dp[i-1][j-p-w]不合法累加 价值自然也不是最大的
                        dp[i][j]=max(dp[i][j],dp[i-1][j-p-w]+val);
                }
            }
            for(int j=0;j<=v;j++)
                dp[i][j]=max(dp[i][j],dp[i-1][j]);
        }
        printf("%d\n",dp[n][v]);
    }
    return 0;
}
*/

/*
//ac 249ms 分组背包当前组至少取一件物品与当前组一件物品也不选 比较求取较优值
//以箱子分组,每组的物品为箱子、物品1、物品2、..物品10
//先考虑购买箱子,再考虑在箱子已购买的状态下 对剩下的物品购买进行01背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w,val,dp[N][M];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        for(int i=0;i<=v;i++)
            dp[0][i]=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            //先买箱子 价钱为p,价值为0
            for(int j=v;j>=p;j--)
                dp[i][j]=max(dp[i][j],dp[i-1][j-p]);
            //再在买箱子的基础上 买该组剩下的物品 01背包
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                for(int j=v;j>=w;j--)
                    dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
            }
            //比较前i组最优解 在选取第i组物品(dp[i][j])和不选取第i组物品(前i-1组物品dp[i-1][j])状态比较 选取最优值
            for(int j=0;j<=v;j++)
                dp[i][j]=max(dp[i][j],dp[i-1][j]);
        }
        printf("%d\n",dp[n][v]);
    }
    return 0;
}
*/

/*
//ac 171ms 分组背包当前组至少取一件物品与当前组一件物品也不选 比较求取较优值
//采用滚动数组优化 2个数组一个数组只记录前i-1组状态tp,另一个数组记录前i组状态dp
//以箱子分组,每组的物品为箱子、物品1、物品2、..物品10
//先考虑购买箱子,再考虑在箱子已购买的状态下 对剩下的物品购买进行01背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 60
#define M 100100
using namespace std;

//tp[j]代表前i-1组的状态
//dp[j]代表前i组的状态
int n,v,p,num,w,val,dp[M],tp[M];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            //将前i-1组的最优解赋值给tp
            for(int j=0;j<=v;j++)
                tp[j]=dp[j];
            //前i组的状态初始化为-INF
            memset(dp,-0x3f,sizeof(dp));
            //先买箱子
            for(int j=v;j>=p;j--)
                dp[j]=max(dp[j],tp[j-p]);
            //再在买箱子的基础上 买该组剩下的物品 01背包
            for(int k=1;k<=num;k++){
                scanf("%d%d",&w,&val);
                for(int j=v;j>=w;j--)
                    dp[j]=max(dp[j],dp[j-w]+val);
            }
            //比较前i组最优解 在选取第i组物品(dp[j])和不选取第i组物品(前i-1组物品tp[j])状态比较 选取最优值
            for(int j=0;j<=v;j++)
                dp[j]=max(dp[j],tp[j]);
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 561ms 分组背包 每组物品至多选一个,每组物品可能选取情况 dfs暴力枚举+剪枝
//不剪枝肯定会TLE,因为每组物品组合情况的复杂度最大可达 2^10=1024 分组背包复杂度为O(nv*1024)=5*10^6*10^3=5*10^9
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w[11],val[11],dp[M];
struct Node{
    int w,val;
    Node(int w=0,int val=0):w(w),val(val){}
};
vector<Node> a[N];

void dfs(int i,int k,int tw,int tv){
    if(k == num+1){
        //剪枝 如果第i组之前选取的物品组合情况 存在相对当前组合,体积并不大于当前组合体积
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
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            a[i].clear();
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            for(int k=1;k<=num;k++)
                scanf("%d%d",&w[k],&val[k]);
            //暴力搜索第i组物品的可能选取情况
            dfs(i,1,p,0);//第i组箱子要买 物品必须先买箱子,箱子不产生价值
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
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//TLE 分组背包 每组物品至多选一个,二进制枚举每组物品选取的可能单独作为当前组独立的物品 箱子+(可能的当前组物品)
//每组物品组合情况的复杂度最大可达 2^10=1024 分组背包复杂度为O(nv*1024)=5*10^6*10^3=5*10^9
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 60
#define M 100100
using namespace std;

int n,v,p,num,w[11],val[11],dp[M];
struct Node{
    int w,val;
    Node(int w=0,int val=0):w(w),val(val){}
};
vector<Node> a[N];

int main(){
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            a[i].clear();
        for(int i=1;i<=n;i++){
            scanf("%d%d",&p,&num);
            for(int k=1;k<=num;k++)
                scanf("%d%d",&w[k],&val[k]);
            int k=(1<<num)-1;
            for(int j=1;j<=k;j++){
                int tp=j,cnt=1;
                Node goods=Node(0,0);
                while(tp){
                    if(tp & 1){
                        goods.w+=w[cnt];
                        goods.val+=val[cnt];
                    }
                    cnt++;
                    tp>>=1;
                }
                goods.w+=p;
                a[i].push_back(goods);
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=v;j>=1;j--){
                for(Node & k :  a[i]){
                    if(j>=k.w)
                        dp[j]=max(dp[j],dp[j-k.w]+k.val);
                }
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/
