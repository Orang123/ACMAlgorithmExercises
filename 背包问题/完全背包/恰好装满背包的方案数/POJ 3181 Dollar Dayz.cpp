/*
题意:有k种类型的工具的价格分别为1~k,每种工具有无限个可出售,
现在有n元钱,求有多少种方式能将n元钱花完.
链接:http://poj.org/problem?id=3181
思路:完全背包统计方案数
只不过因为 n=1000,k=100时,实际结果是:15658181104580771094597751280645
有32位数,而long long的最大范围为9223372036854775807 有19位数,所以需要
高精度加法,可以设置两个dp数组,dp1显示高位,dp2显示低位.因为高位dp1最多
只能放19位数,所以低位dp2至少需要放32-19=13位数.实际转移时 只初始化低位
dp2[0]=1,高位dp1是低位相加后产生的进位,即:dp1[j]=dp1[j]+dp1[j-i]+(dp2[j]+dp2[j-i])/INF;
而低位是dp2[j]=(dp2[j]+dp2[j-i])%INF,相加后余留下来后面的低位结果.
如:(65+79)/100=1 (65+79=144)%100=44 所以假设INF=1e18,那么低位实际相加结果就不能超过19位
数,超过时将进位放在高位上,余留的低位存放在低位上.
*/
//ac 16ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define M 1100
typedef long long ll;
const ll INF=1e18;//这里将低位尽可能多地放 最多放19位数
using namespace std;

int n,k;
ll dp1[M],dp2[M];

int main(){
    memset(dp1,0,sizeof(dp1));
    memset(dp2,0,sizeof(dp2));
    scanf("%d%d",&n,&k);
    dp2[0]=1;
    for(int i=1;i<=k;i++){
        for(int j=i;j<=n;j++){
            //没有进位时dp1数组即:dp2[j]+dp2[j-i]<INF时,高位为0,只有dp2低位有值,
            dp1[j]=dp1[j]+dp1[j-i]+(dp2[j]+dp2[j-i])/INF;
            dp2[j]=(dp2[j]+dp2[j-i])%INF;
        }
    }
    if(dp1[n])//有高位先输出高位
        printf("%lld",dp1[n]);
    printf("%lld\n",dp2[n]);
    return 0;
}
