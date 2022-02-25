//ac 124ms 先枚举攻击方式 再枚举j生命值
/*
题意:度度熊为了拯救可爱的公主,于是与邪恶大魔王战斗起来.
邪恶大魔王的麾下有n个怪兽,每个怪兽有a[i]的生命值,以及b[i]的防御力.
度度熊一共拥有m种攻击方式,第i种攻击方式,需要消耗k[i]的晶石,造成p[i]点伤害.
当然,如果度度熊使用第i个技能打在第j个怪兽上面的话,会使得第j个怪兽的生命值
减少p[i]-b[j],当然如果伤害小于防御,那么攻击就不会奏效.如果怪兽的生命值降为
0或以下,那么怪兽就会被消灭.当然每个技能都可以使用无限次.请问度度熊最少携带
多少晶石,就可以消灭所有的怪兽.
1<=n<=100000
1<=m<=1000
1<=a[i]<=1000
0<=b[i]<=10
0<=k[i]<=100000
0<=p[i]<=1000
链接:http://acm.hdu.edu.cn/showproblem.php?pid=6082
思路:可以将n个怪兽看做n个背包,背包容量为怪兽的生命值,m个攻击方式看做数量无
限制的物品,物品花费为技能的伤害值p[i],物品价值为消耗晶石数目k[i].可以做n次
完全背包求解出答案.
但是朴素的完全背包复杂度 n*O(mv)=10^5*10^3*10^3=10^11,复杂度太大.事实上不同
怪兽在生命值这个属性上都是同一种怪兽,也就是在生命值这个背包容积维度上事实上
只需做一次完全背包即可,区分不同怪兽种类的关键点在于怪兽间的防御力b[i],因为b[i]
会直接影响没个技能消耗怪兽的生命值为多少,而实际0<=b[i]<=10,也就是说实际最多只有
11种怪兽,那么实际最多只有11种背包,这样完全背包的复杂度骤减为 11*O(mv)=1.1*10^7.
所以定义dp[i][j]代表怪兽防御力为i时,消灭生命值为j的怪兽最少需要的晶石.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define M 1100
#define INF 0x3f3f3f3f3f3f3f3f//long long有64位,所以INF 16进制是16位 不然判断INF会出错
typedef long long ll;
using namespace std;

int n,m,a[N],b[N],p[M];
//dp[i][j]代表怪兽防御力为i时,消灭生命值为j的怪兽最少需要的晶石.
ll dp[11][M],k[M];

int main(){
    int maxa,maxb;
    while(scanf("%d%d",&n,&m)!=EOF){
        maxa=1,maxb=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a[i],&b[i]);
            //降低dp时的dp[i][j] i、j的维度
            maxa=max(maxa,a[i]);//求出最大的生命值 j
            maxb=max(maxb,b[i]);//求出最大的怪兽防御力 i
        }
        for(int i=1;i<=m;i++)
            scanf("%d%d",&k[i],&p[i]);
        memset(dp,0x3f,sizeof(dp));
        //每种防御力对应一种类型的怪兽,一种新的类型的背包
        //每个背包初始状态均是 消灭生命值为0时需要晶石为0
        for(int i=0;i<=maxb;i++)
            dp[i][0]=0;
        for(int i=0;i<=maxb;i++){
            for(int t=1;t<=m;t++){
                if(p[t]<=i) continue;//伤害值p[t]不大于防御力i时 无法消减怪兽生命值
                for(int j=1;j<=maxa;j++){
                    //减少的声明值是p[t]-i(伤害值-防御力)
                    if(j-(p[t]-i)<0)//第t种技能伤害值远大于生命值,那么上一状态可以认为是 生命值为0 晶石为0
                        dp[i][j]=min(dp[i][j],k[t]);
                    else
                        dp[i][j]=min(dp[i][j],dp[i][j-(p[t]-i)]+k[t]);
                }
            }
        }
        ll ans=0;
        for(int i=1;i<=n;i++){
            if(dp[b[i]][a[i]]!=INF)
                ans+=dp[b[i]][a[i]];
            else{//只要有一种怪兽没被消灭 就输出-1
                ans=-1;
                break;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}

/*
//ac 156ms 先枚举j生命值 再枚举攻击方式
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define M 1100
#define INF 0x3f3f3f3f3f3f3f3f
typedef long long ll;
using namespace std;

int n,m,a[N],b[N],p[M];
ll dp[11][M],k[M];

int main(){
    int maxa,maxb;
    while(scanf("%d%d",&n,&m)!=EOF){
        maxa=1,maxb=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a[i],&b[i]);
            maxa=max(maxa,a[i]);
            maxb=max(maxb,b[i]);
        }
        for(int i=1;i<=m;i++)
            scanf("%d%d",&k[i],&p[i]);
        memset(dp,0x3f,sizeof(dp));
        for(int i=0;i<=maxb;i++)
            dp[i][0]=0;
        for(int i=0;i<=maxb;i++){
            for(int j=1;j<=maxa;j++){
                for(int t=1;t<=m;t++){
                    if(p[t]<=i) continue;
                    if(j-(p[t]-i)<0)
                        dp[i][j]=min(dp[i][j],k[t]);
                    else
                        dp[i][j]=min(dp[i][j],dp[i][j-(p[t]-i)]+k[t]);
                }
            }
        }
        ll ans=0;
        for(int i=1;i<=n;i++){
            if(dp[b[i]][a[i]]!=INF)
                ans+=dp[b[i]][a[i]];
            else{
                ans=-1;
                break;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
*/
