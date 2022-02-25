/*
题意:多重背包模板题.n<=1000,v<=1000
不用二进制优化会TLE.
链接:https://www.acwing.com/problem/content/description/5/
思路:二进制枚举第i种物品组合方案.
*/
//ac 238ms 重背包二进制优化01背包做法
//复杂度O(∑log(num[i])*v) 1000*log(2000)*2000=11000*2000=2.2*10^7
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 2100
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
    int m,tw,tv;
    for(int i=1;i<=n;i++){
        m=num[i];
        for(int k=1;m>0;k<<=1){//枚举第i种物品可能的二进制组合
            m-=k;
            if(m<0) k+=m;
            tw=w[i]*k;
            tv=val[i]*k;
            for(int j=v;j>=tw;j--)
                dp[j]=max(dp[j],dp[j-tw]+tv);
        }
    }
    printf("%d\n",dp[v]);
    return 0;
}

/*
//ac 124ms 二进制优化 比背包九讲版本更优的做法 将多重背包转化为 二进制优化的01背包+完全背包精简版
//这里将背包九讲中对于完全背包的判定拓展为更宽泛的条件,即:v-num[i]*w[i]<w[i],第i种物品能尽可能多
//地装入到容量为v的背包,直到不能再装下一个为止.
//这是多重背包最优化问题复杂度仅次于单调队列优化的版本 比下面背包九讲版本的复杂度更低
//复杂度比标准的二进制优化这个时间界O(∑log(num[i])*v) 可能要低
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 2100
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&w[i],&val[i],&num[i]);
    int m,tw,tv;
    for(int i=1;i<=n;i++){
        if(v-num[i]*w[i]<w[i]){//第i种物品所有物品体积和不小于背包容积v时 完全背包
            for(int j=w[i];j<=v;j++)
                dp[j]=max(dp[j],dp[j-w[i]]+val[i]);
        }
        else{//否则 二进制优化 01背包
            for(int k=1;num[i]>0;k<<=1){
                num[i]-=k;
                if(num[i]<0) k+=num[i];
                tw=w[i]*k;
                tv=val[i]*k;
                for(int j=v;j>=tw;j--)
                    dp[j]=max(dp[j],dp[j-tw]+tv);
            }
        }
    }
    printf("%d",dp[v]);
    return 0;
}
*/

/*
//ac 170ms 二进制优化 背包九讲版本 将多重背包转化为 二进制优化的01背包+完全背包精简版
//这是多重背包最优化问题复杂度仅次于单调队列优化的版本
//复杂度比标准的二进制优化这个时间界O(∑log(num[i])*v) 可能要低
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 2100
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&w[i],&val[i],&num[i]);
    int m,tw,tv;
    for(int i=1;i<=n;i++){
        if(num[i]*w[i]>=v){//第i种物品所有物品体积和不小于背包容积v时 完全背包
            for(int j=w[i];j<=v;j++)
                dp[j]=max(dp[j],dp[j-w[i]]+val[i]);
        }
        else{//否则 二进制优化 01背包
            for(int k=1;num[i]>0;k<<=1){
                num[i]-=k;
                if(num[i]<0) k+=num[i];
                tw=w[i]*k;
                tv=val[i]*k;
                for(int j=v;j>=tw;j--)
                    dp[j]=max(dp[j],dp[j-tw]+tv);
            }
        }
    }
    printf("%d",dp[v]);
    return 0;
}
*/

/*
//ac 735ms 多重背包转化01背包做法 采用线性组合方案 降低物品个数的枚举次数
//在前面放入第i种物品个数基础上再放入比上一次数目多1的物品个数,最后一次如果有剩余,则放入物品个数较少
//复杂度在二进制优化O(∑log(num[i])*v)和朴素01背包O(∑num[i]*v)之间
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 2100
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
    int m,tw,tv;
    for(int i=1;i<=n;i++){
        m=num[i];
        for(int k=1;m>0;k++){
            m-=k;
            if(m<0) k+=m;
            tw=w[i]*k;
            tv=val[i]*k;
            for(int j=v;j>=tw;j--)
                dp[j]=max(dp[j],dp[j-tw]+tv);
        }
    }
    printf("%d\n",dp[v]);
    return 0;
}
*/

/*
//TLE 多重背包朴素01背包做法 在每个可能背包容量j下线性枚举[1,num[i]]个物品构成新的物品放入背包
//复杂度O(∑num[i]*v) 这是把所有物品都当成一个物品01背包的复杂度,这个做法的复杂度还是比这个要小一点的
//复杂度O(∑num[i]*v) 1000*2000*2000=4*10^9
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1100
#define M 2100
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&w[i],&val[i],&num[i]);
    int tw,tv;
    //复杂度O(∑num[i]*v)
    for(int i=1;i<=n;i++){
        for(int j=v;j>=w[i];j--){
            for(int k=1;k<=num[i];k++){
                tw=w[i]*k;
                if(j<tw) break;//如果当前容量已经装不下这个数目下的物品 就结束
                tv=val[i]*k;
                dp[j]=max(dp[j],dp[j-tw]+tv);
            }
        }
    }
    printf("%d\n",dp[v]);
    return 0;
}
*/

/*
//TLE 多重背包朴素01背包做法 直接转换成∑num[i]个物品进行01背包
//复杂度O(∑num[i]*v) 1000*2000*2000=4*10^9
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 2000100
#define M 2100
using namespace std;

int n,v,w[N],val[N],dp[M];

int main(){
    int a,b,m,id;
    id=0;
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&a,&b,&m);
        while(m--){
            w[++id]=a;
            val[id]=b;
        }
    }
    //实际物品个数是id,已经转化为一个标准的01背包了
    for(int i=1;i<=id;i++){
        for(int j=v;j>=w[i];j--)
            dp[j]=max(dp[j],dp[j-w[i]]+val[i]);
    }
    printf("%d\n",dp[v]);
    return 0;
}
*/


