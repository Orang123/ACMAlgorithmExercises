#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 510
using namespace std;
//ac 31ms 01背包计算能装入物品最大个数的方案数 二维数组实现 尽可能多地装满背包,不要求恰好装满
//枚举枚举背包剩余容量第二层循环降序 物品个数第三层循环升序
//如果问尽可能多地装k个物品恰好装满背包容量M的方案数,那么初始条件 dp[0..k][0]=1
/*
题意:给出钱数和各个物品的价格,让求出能买出最多物品的方案数.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2126
思路:在01背包滚动数组基础上再增加一个维度,用来表示买了几个物品.
即dp[j][k],代表容量为j的背包买k个物品的最多方案数.那么状态转移
方程就是dp[j][k]=dp[j][k]+dp[j-val[i]][k-1],dp[j][k]只和本身的
方案数和上一个状态装入k-1个物品的最大方案数有关,在k-1个物品背包
中再放入第i个物品就表示装入k个物品时的最大方案数,所以是累加,初始状态
是dp[j][0]=1,因为一个物品也不放只有一种方案,都是合法状态.

总结:这个三重循环dp,注意第二层循环既可以是枚举背包剩余容量也可以是
枚举当前容量下放入物品个数k,但都需要逆序降序枚举,因为只有这样才能保证
dp[j-val[i]][k-1]是前i-1个物品时的dp值,如果升序枚举会导致第i个物品重复
放入背包,导致dp[j-val[i]][k-1]是放入第i个物品时的前i个物品时的状态而不是前i-1
个物品的状态.另外第三层循环无论是背包容积还是放入背包物品个数,既可升序也可降序.

注意:此题和POJ 3093都是求解尽可能多地装满背包的方案数,但是POJ 3093并没有指定具体
物品个数,做法依然只能按照恰好装满背包的做法 枚举出剩下物品中体积最小的也放不进去时就是
背包装不下的情况.而此题 有一个指定物品个数的要求,实际只要初始化物品个数为0对应的各个背包
容量dp[j][0]=1即可,这样只要从物品最大个数i逆序遍历 dp[m][i]是否是合法状态即可,就能找到最
多能放入物品的方案数. 虽然各个可能的背包容积在物品个数为0时初始值都是1,但并不会重复累加,
因为物品个数是第二个维度它能保证恰好装满物品个数,即物品个数为0,依次向物品个数为1、2、...、n
去转移,dp[1..n][j]本身是0(不合法),而上一个状态dp[i-1][j-val[i]]才是合法状态,而这样就能求出
尽可能装满容量为m,dp[i][m]下的方案数,这里m不一定是装满的,此题并没有要求恰好装满背包,只求方案数.
*/
//代码实现 参考博客:https://blog.csdn.net/zhouzi2018/article/details/86564824
//dp[j][k]代表容量为j的背包装入k个物品的总方案数,j不一定装满,可能有剩余
int n,m,val[N],dp[M][N];//也可以dp[N][M]

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));//尽可能多地装入背包
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=0;i<=m;i++)
            dp[i][0]=1;//初始状态是装入物品个数0个,背包容积任意,算一个方案个数
        //若要求恰好装满只初始化dp[0][0]=1 还可以加上if(dp[j-val[i]][k-1]) dp[j][k]+=dp[j-val[i]][k-1];
        //每次放入的物品都不同,若前i-1个物品状态是有效的,就能和当前的第i个物品组合构成新的方案,
        //每个物品都会更新一遍dp[j][k] j的上界都是m,i的下界都是从1开始,的所有可能值,因此是加法原理累加方案个数
        for(int i=1;i<=n;i++){
            //这里第二层循环 无论是枚举背包容量还是放入背包物品个数 都必须是降序,
            //这样才能保证dp[j-val[i]][k-1]是前i-1个物品的状态
            for(int j=m;j>=val[i];j--){
                //这里 k,k-1,k+1之间并不进行状态转移,没有直接关系,dp[i][j][k]的上一个状态是前i-1个物品的dp[i-1][j][k],这里因为滚动数组优化掉了第一维度的i
                for(int k=1;k<=i;k++)//枚举 放入几个物品,前i个物品,最多放i个 k降序结果也正确
                    //因为是前面k-1个物品dp[j-val[i]][k-1]个方案分别和第i个物品组合,所以是加法原理
                    dp[j][k]+=dp[j-val[i]][k-1];//放入k个物品只和k-1个物品的状态有关
            }
        }
        int flag=0;
        for(int i=n;i>=1;i--){//逆序考虑放入最多物品
            if(dp[m][i]){
                printf("You have %d selection(s) to buy with %d kind(s) of souvenirs.\n",dp[m][i],i);
                flag=1;
                break;
            }
        }
        if(!flag)
            printf("Sorry, you can't buy anything.\n");
    }
    return 0;
}

/*
//ac 31ms 枚举背包剩余容量第二层循环降序 物品个数第三层循环降序
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 510
using namespace std;
int n,m,val[N],dp[N][M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));//尽可能多地装入背包
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=0;i<=m;i++)
            dp[0][i]=1;
        for(int i=1;i<=n;i++){
            for(int j=m;j>=val[i];j--){
                for(int k=i;k>=1;k--)//枚举 放入几个物品,前i个物品,最多放i个 k升序结果也正确
                    dp[k][j]+=dp[k-1][j-val[i]];//放入k个物品只和k-1个物品的状态有关
            }
        }
        int flag=0;
        for(int i=n;i>=1;i--){//逆序考虑放入最多物品
            if(dp[i][m]){
                printf("You have %d selection(s) to buy with %d kind(s) of souvenirs.\n",dp[i][m],i);
                flag=1;
                break;
            }
        }
        if(!flag)
            printf("Sorry, you can't buy anything.\n");
    }
    return 0;
}
*/

/*
//ac 31ms 枚举物品个数第二层循环降序 背包剩余容量第三层循环降序
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 510
using namespace std;
int n,m,val[N],dp[M][N];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));//尽可能多地装入背包
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=0;i<=m;i++)
            dp[i][0]=1;
        for(int i=1;i<=n;i++){
            for(int k=i;k>=1;k--){//枚举 放入几个物品,前i个物品,最多放i个 这里只能降序,升序结果会错
                for(int j=m;j>=val[i];j--)//这里背包容积 升序降序 都可,j和j-val[i]并没有直接的状态转移,上一个状态是前i-1个物品,因为是二维数组,所以j升序还是降序并不影响其前i-1个物品的状态
                    dp[j][k]+=dp[j-val[i]][k-1];//放入k个物品只和k-1个物品的状态有关
            }
        }
        int flag=0;
        for(int i=n;i>=1;i--){//逆序考虑放入最多物品
            if(dp[m][i]){
                printf("You have %d selection(s) to buy with %d kind(s) of souvenirs.\n",dp[m][i],i);
                flag=1;
                break;
            }
        }
        if(!flag)
            printf("Sorry, you can't buy anything.\n");
    }
    return 0;
}
*/

/*
//ac 31ms 枚举物品个数第二层循环降序 背包剩余容量在第三层循环升序
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 510
using namespace std;
int n,m,val[N],dp[M][N];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));//尽可能多地装入背包
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=0;i<=m;i++)
            dp[i][0]=1;
        for(int i=1;i<=n;i++){
            for(int k=i;k>=1;k--){//枚举 放入几个物品,前i个物品,最多放i个 这里只能降序,升序结果会错
                for(int j=val[i];j<=m;j++)//背包剩余容量升序
                    dp[j][k]+=dp[j-val[i]][k-1];//放入k个物品只和k-1个物品的状态有关
            }
        }
        int flag=0;
        for(int i=n;i>=1;i--){//逆序考虑放入最多物品
            if(dp[m][i]){
                printf("You have %d selection(s) to buy with %d kind(s) of souvenirs.\n",dp[m][i],i);
                flag=1;
                break;
            }
        }
        if(!flag)
            printf("Sorry, you can't buy anything.\n");
    }
    return 0;
}
*/

/*
//ac 15ms 01背包计算能装入物品最大个数的方案数 二维数组实现dp[j][2]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 510
using namespace std;

//dp[j][0]表示容量为j的背包最多能装入物品个数
//dp[j][1]表示容量为j的背包最多能装入物品个数的方案数
//代码实现参考博客:https://blog.csdn.net/know_heng/article/details/53635476
int n,m,val[N],dp[M][2];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));//尽可能多地装入背包
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        //如果是问恰好装满,只初始化dp[0][1]=1,这样如果memset(dp)是0,那么dp[j][0]的值仍然表示的是尽可能多地装最多个物品
        //在dp之前加上if(!dp[j-val[i]][1]) continue;这样dp[j][0]的值表示的是恰好装满背包的最多个物品
        for(int i=0;i<=m;i++)
        //注意这个做法并不会像一维数组dp[j]那样重复累加方案
        //因为更新方案数的转移是dp[j][1]=dp[j-val[i]][1] 在一个物品还没装入时,是直接赋值,而不是累加
            dp[i][1]=1;//初始状态各个背包容量下的装入物品最大个数的方案数为1
        for(int i=1;i<=n;i++){
            for(int j=m;j>=val[i];j--){
                //if(!dp[j-val[i]][1]) continue;//恰好装满背包 若方案数为0,则说明不是恰好装满的情形(不是从dp[0][1]转移而来)
                if(dp[j][0] == dp[j-val[i]][0]+1)//和j-val[i]上一个状态装入物品个数+1相等时,就累加上一个状态的方案数
                    dp[j][1]+=dp[j-val[i]][1];
                if(dp[j][0] < dp[j-val[i]][0]+1){//上一个状态j-val[i]装入物品个数较多时,更新当前装入物品个数的最大值和装入物品个数最大值的方案数
                    dp[j][0]=dp[j-val[i]][0]+1;
                    //能保证 dp[j][1] 在一个物品没装入时,不累加自己本身的 值1,这里是赋值
                    dp[j][1]=dp[j-val[i]][1];
                }
            }
        }
        if(dp[m][0])//若dp[m][0]不为0,则说明至少能装入一个物品,不能用dp[m][1]判断,因为dp[m][1]已经初始化过了
            printf("You have %d selection(s) to buy with %d kind(s) of souvenirs.\n",dp[m][1],dp[m][0]);
        else
            printf("Sorry, you can't buy anything.\n");
    }
    return 0;
}
*/
