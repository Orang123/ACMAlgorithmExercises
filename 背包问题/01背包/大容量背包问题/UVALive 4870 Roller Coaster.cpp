#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 21000
#define INF 0x3f3f3f3f
using namespace std;
//Regionals 2010 North America - Southeast USA
//ac 822ms 01背包 物品容积和价值交换 恰好装满背包
/*
题意:有n个过山车,贝西按顺序坐过山车,贝西有眩晕度和快乐度,
对于每个眼前的过山车如果贝西睁开眼睛,她的快乐度会增加f[i],
同时它的眩晕度也会增加d[i],如果她闭上眼睛,那么她的快乐度不变,
而她的眩晕度会减少k,但是在整个过程中贝西的眩晕度也不会低于0,
如果贝西坐完n个过山车后,她的眩晕度高于l,她就会生病,现在问在
贝西坐完n个过山车后,在她不生病的情况下,她最多能获得多少快乐度.
n<=1000,1<=f[i]<=20,1<=d[i]<=500.
链接:https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2871
思路:很明显是一个01背包问题,如果考虑将眩晕度作为物品体积,快乐度作为物品价值,
那么状态转移方程无法很好地表示当贝西闭眼时,其快乐度不变 眩晕度减少,因为一旦
减少背包容积(眩晕度),其快乐度dp[j]数值也一定会变化,即:dp[j-k]!=dp[j],总之就
是不好表示这个转移,而且眩晕度作为物品体积,背包容积最大可达10^3*500=5*10^5,
O(nv)=5*10^8,会TLE.但是如果将将快乐度作为物品体积,眩晕度作为物品价值,对于第i个
过山车闭眼,其快乐度不变,眩晕度减少k就可表示为dp[j]-=k(dp[j]-k>=0,否则dp[j]=0),
这样就得到了在相同快乐度j的情况下使得眩晕度最小化,而且快乐度f[i]<=20作为体积后,
背包总容积也得以减低,时间和空间复杂度也得以降低.因为快乐度和眩晕度同等增长,相互
对等的,不能说是有快乐度剩余的情况,因此需要初始化dp 为INF,初始状态dp[0]=0,状态转移
方程为在相同快乐度的情况下求解最小的眩晕度,即:dp[j]=min(dp[j],dp[j-f[i]]+d[i]).
*/
int n,k,l,f[N],d[N],dp[M],sum;

int main(){
    while(scanf("%d%d%d",&n,&k,&l) && n+k+l){
        sum=0;
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&f[i],&d[i]);
            sum+=f[i];//所有过山车获得的快乐度之和为背包总容积
        }
        dp[0]=0;
        for(int i=1;i<=n;i++){
            //注意这里背包容积下界不能是f[i],因为这样会导致 当闭上眼,降低眩晕度时,
            //前i-1个物品的合法的背包容积可能是比当前的f[i]要小的,就不能更新背包容积小于f[i]的眩晕度,最优解就会出错
            //因为每个过山车至少能获得1快乐度,所以下界定义为1
            for(int j=sum;j>=1;j--){
                if(dp[j]!=INF){
                    if(dp[j]-k>0)//相同快乐度 闭上眼使得眩晕度更小
                        dp[j]-=k;
                    else
                        dp[j]=0;//眩晕度最小为0
                }
                if(dp[j-f[i]]+d[i]<=l)//当睁开眼 增加后的眩晕度 不超过规定的l时,更新最优解
                    dp[j]=min(dp[j],dp[j-f[i]]+d[i]);
            }
        }
        int ans;
        for(int i=sum;i>=0;i--){//降序枚举 快乐度,第一个合法状态 即眩晕度肯定不超过规定的l
            if(dp[i]!=INF){
                ans=i;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
n<=1000,暴力搜索会tle,写是能写出来
*/
