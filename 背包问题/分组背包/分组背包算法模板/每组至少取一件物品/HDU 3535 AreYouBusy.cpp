#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;
//ac 46ms 混合背包=分组背包(2种类型)+01背包 初始化-1
//s=0 if判断顺序颠倒会wa,不知何原因
/*
题意:有n种工作,有T个单位时间可用.给出m和s,代表当前这种工作有m件项目可以做,
s代表该种工作的要求,(s=0表示这m件项目中至少得做一件,s=1表示这m件项目中最多做
一件,s=2表示这m件项目可以做也可以不做).再给出w和val表示你做这件项目用w的时间,
能获得val的快乐值.求在T的时间内你能获得的最大快乐值.
0<=n,T<=100.
0<=w,val<=100.
注意:
1.项目的时间和快乐值都有可能为0,时间为0时要注意每种工作至少做一个项目,
转移顺序是先考虑第i种工作项目选取多个dp[i][j-w],再考虑前i-1种工作dp[i-1][j-w]
基础上至少选一个第i种工作的项目.
2.快乐值为0时,如果题目有对 不合法状态的判断 即:如果n种工作有要求每种工作都要至少
选取一个时,如果有某种工作一件也选取不了,那最终结果就是不合法的,此时dp初始化不能
初始化为0,因为合法状态也可能是0(项目快乐度为0),所以初始化为-INF,初始状态dp[0][0..T]=0
对于前i种工作是恰好装满,而总时间是尽可能多地装满.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3535
思路:很明显属于01背包问题,只是对每种工作中的可做项目有要求,dp[i][j]表示前
i种工作在j时间内做能获得的最大价值.

对于s=0,至少做一件的,dp[i][j]初始化不能直接继承dp[i-1][j],初始状态是至少在
前i-1种工作基础上dp[i-1][j],做第i种工作总的一个项目,作为dp[i][j]的初始合法
状态,这样后续的第i+1..n种工作只能在已经选定了第i种工作的一个项目基础上去求
解后续的最优解,保证了第i种工作中至少做一个项目,要注意的是必选先考虑前i种工作
状态已经做过一个项目基础上dp[i][j-w],后考虑在前i-1状态基础上至少做一个第i种工
作中的项目dp[i-1][j-w]否则会wa,因为存在第i种工作的项目所用时间为0,如果先考虑
前i-1种工作基础上转移,dp[i][j]=dp[i-1][j-0]+val之后再考虑前i种工作基础上转移,
dp[i][j]=dp[i][j-0]+val,这会导致第i种工作中的当前这个项目被选取2次,显然与题意不符.
对应分组背包每组至少选一件.必须用二维数组,不能一维.

对于s=1,最多做一件,因为可以一件也不做,那么初始合法状态可以直接继承dp[i-1][j],
因为最多做一件所以,只能在dp[i-1][j-w]+val 前i-1种工作上更新最优解.
对应分组背包每组至多选一件.

对于s=2,由于没有直接限制,第i种工作内是普通的01背包问题.初始合法状态可以直接
继承dp[i-1][j].
对应01背包.

*/
int n,T,m,s,dp[N][M];

int main(){
    int w,val;
    while(scanf("%d%d",&n,&T)!=EOF){
        //因为前i种工作的初始合法状态 会根据s的类别继承前i-1种工作
        //所以除了前0种工作初始状态都合法外,其余都先假设非法
        memset(dp,-1,sizeof(dp));//物品价值可能为0,dp初始化不能初始化为0 否则不合法状态与合法状态无法区分
        memset(dp[0],0,sizeof(dp[0]));//初始状态背包容量是尽可能多地装满 dp[0][0..T]=0
        for(int i=1;i<=n;i++){
            scanf("%d%d",&m,&s);
            if(!s){//对应分组背包每组至少选一件. 必须用二维数组,不能一维.
                for(int k=1;k<=m;k++){
                    scanf("%d%d",&w,&val);
                    for(int j=T;j>=w;j--){
                        //必须先考虑第i种工作中可做项目做多个累加,后考虑在前i-1种工作中至少做一个第i种工作的项目
                        //因为存在项目花费时间为0,先考虑在dp[i-1][j-0]转移,会导致dp[i][j]已经选了一个当前项目,
                        //等到再考虑在dp[i][j-0]转移时这个项目已经放入一次了,这样选取最优解 可能会导致这个项目选2次.
                        if(dp[i][j-w]!=-1)//第i组的项目已经保证至少做过一个 在做过一个的基础上累加
                            dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
                        if(dp[i-1][j-w]!=-1)//前i-1种工作状态合法 第i种工作的项目至少要做一个 上一状态是前i-1种工作的状态
                            dp[i][j]=max(dp[i][j],dp[i-1][j-w]+val);
                    }
                }
            }
            else if(s == 1){//对应分组背包每组至多选一件.
                for(int j=0;j<=T;j++)
                    dp[i][j]=dp[i-1][j];
                for(int k=1;k<=m;k++){
                    scanf("%d%d",&w,&val);
                    for(int j=T;j>=w;j--){
                        if(dp[i-1][j-w]!=-1)
                            dp[i][j]=max(dp[i][j],dp[i-1][j-w]+val);
                    }
                }
            }
            else if(s == 2){//随便选 01背包
                for(int j=0;j<=T;j++)
                    dp[i][j]=dp[i-1][j];
                for(int k=1;k<=m;k++){
                    scanf("%d%d",&w,&val);
                    for(int j=T;j>=w;j--){
                        if(dp[i][j-w]!=-1)
                            dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
                    }
                }
            }
        }
        printf("%d\n",dp[n][T]);
    }
    return 0;
}

/*
//ac 15ms 混合背包 初始化-INF
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;
int n,T,m,s,dp[N][M];

int main(){
    int w,val;
    while(scanf("%d%d",&n,&T)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        memset(dp[0],0,sizeof(dp[0]));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&m,&s);
            if(!s){
                for(int k=1;k<=m;k++){
                    scanf("%d%d",&w,&val);
                    for(int j=T;j>=w;j--)
                        dp[i][j]=max(dp[i][j],max(dp[i][j-w]+val,dp[i-1][j-w]+val));
                }
            }
            else if(s == 1){
                memcpy(dp[i],dp[i-1],sizeof(dp[i]));
                for(int k=1;k<=m;k++){
                    scanf("%d%d",&w,&val);
                    for(int j=T;j>=w;j--)
                        dp[i][j]=max(dp[i][j],dp[i-1][j-w]+val);
                }
            }
            else if(s == 2){
                memcpy(dp[i],dp[i-1],sizeof(dp[i]));
                for(int k=1;k<=m;k++){
                    scanf("%d%d",&w,&val);
                    for(int j=T;j>=w;j--)
                        dp[i][j]=max(dp[i][j],dp[i][j-w]+val);
                }
            }
        }
        if(dp[n][T]>0)
            printf("%d\n",dp[n][T]);
        else
            printf("-1\n");
    }
    return 0;
}
*/
