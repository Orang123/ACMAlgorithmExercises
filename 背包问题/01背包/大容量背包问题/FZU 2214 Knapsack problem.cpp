#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5100
using namespace std;
//ac 01背包 恰好装满背包 背包容积和价值调换逆向求解最大价值
//FZUOJ 不能判题一直Queuing...
/*
题意:n(n<=500)个物品,每个物品有一定体积w[i](w[i]<=10^9)
和价值val[i],现在有背包容量为v(v<=10^9)的背包,问在背包容
量v的限制下最多能装入物品的最大价值和,输出这个最大价值和.
val[1]+val[2]+...+val[n]<=5000.
链接:http://acm.fzu.edu.cn/problem.php?pid=2214
思路:显然是01背包问题,只是背包容量v最大可达10^9,这个空间dp数组
无法开出来,因此可以逆向思维,求得对应价值下最小的容积,即dp[i]表示
总价值为i的最小容积是多少,则dp[j]=min(dp[j],dp[j-val[i]]+w[i]);
最后从sum(物品总价值开始判断)开始,找到第一个小于等于v(容量)的v即可.
*/
int n,v,w[N],val[N],dp[M],sum;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d",&n,&v);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&w[i],&val[i]);
            sum+=val[i];//将价值总和作为 背包容积
        }
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=val[i];j--)
                dp[j]=min(dp[j],dp[j-val[i]]+w[i]);
        }
        for(int i=sum;i>=0;i--){//逆序 判断dp[i],价值i的体积dp[i]是否合法,输出最大价值i
            if(dp[i]<=v){
                printf("%d\n",i);
                break;
            }
        }
    }
    return 0;
}
