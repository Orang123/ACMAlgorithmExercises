/*
题意:给出n克的面和m种馅,如果只用面做面包,花费c0克的面,做一个价值为d0的馒头.
给出的m种馅每种都有a、b、c、d种属性,a表示馅有多少克,b为做一个含有该馅的面包
所需的馅的量,c是做含有该馅的面包所需的面的量,d为做出的面包具有的价值,问n克面
m种馅制作面包最多能得到多少价值.
1<=a,b,c,d<=100 n<=1000,m<=10
链接:http://codeforces.com/problemset/problem/106/C
思路:无论面包是否用馅,要制作面包是一定要面的.所以面粉可作为制作面包的一个开销.
而背包容量就是面粉总量n克.
而时间需要考虑制作面包到底是只用面粉制作还是面粉+馅制作,而用面粉+馅的种类有m种,
只用面粉的只有1种,所以实际就是问有m+1种制作方案,问如何制作面包使得获得的价值最大.
而对于只用面粉制作的面包是一个完全背包,因为在n克面粉作为背包容量条件下,这些面粉可以
尽可能多地单独全部用来制成只有面粉的面包,会有面粉剩余,因此实际物品个数可以是无限.
实际判断完全背包不必再局限于物品数量无线,实际只要能用这种物品尽可能多地装满背包后,
即:装完后,背包所剩余容积不足这种物品的体积.
而其余面粉+馅构成 每种物品实际的物品数量是a/b.是一个多重背包问题,而实际
O(nv)=(10*100+1)*1000=10^6.1s时限可以直接用01背包求解.
*/
//ac 60ms 混合背包(完全背包+多重背包)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,c0,d0,a,b,c,d,num,dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d%d",&n,&m,&c0,&d0);
    /*
    //贪心
    for(int j=c0;j<=n;j++)
        dp[j]=j/c0*d0;
    */
    for(int i=c0;i<=n;i++)
        dp[i]=max(dp[i],dp[i-c0]+d0);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d%d",&a,&b,&c,&d);
        num=a/b;
        for(int k=1;k<=num;k++){
            for(int j=n;j>=c;j--)
                dp[j]=max(dp[j],dp[j-c]+d);
        }
    }
    printf("%d",dp[n]);
    return 0;
}

/*
//ac 62ms 完全背包+二进制拆分的01背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,c0,d0,a,b,c,d,num,dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d%d",&n,&m,&c0,&d0);
    for(int i=c0;i<=n;i++)
        dp[i]=max(dp[i],dp[i-c0]+d0);
    int tw,tv;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d%d",&a,&b,&c,&d);
        num=a/b;
        for(int k=1;num>0;k<<=1){
            num-=k;
            if(num<0) k+=num;
            tw=c*k;
            tv=d*k;
            for(int j=n;j>=tw;j--)
                dp[j]=max(dp[j],dp[j-tw]+tv);
        }
    }
    printf("%d",dp[n]);
    return 0;
}
*/
