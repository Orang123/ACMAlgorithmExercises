/*
题意:有n种物品和一个容量为v的背包.第i种物品最多有num[i]件可用,
每件耗费的空间是w[i],价值是val[i].求解将哪些物品装入背包可使这
些物品的耗费的空间总和不超过背包容量,且价值总和最大.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2191
思路:
*/

//ac 0ms 多重背包二进制优化01背包做法
//复杂度O(∑log(num[i])*v)
/*
二进制优化做法:
将第i种物品分成若干件01背包中的物品,其中每件物品有一个系数.
这件物品的费用和价值均是原来的费用和价值乘以这个系数令这些系数分别为
2^0=1,2^1,2^2 ,2^(k-1);nmu[i]-2^k+1,且k是满足num[i]-2^k+1>0的最大整数.
num[i]=13,则相应的k = 3,这种最多取13件的物品应被分成系数分别为1,2,4,6的
四件物品.
分成的这几件物品的系数和为num[i],表明不可能取多于num[i]件的第i种物品.另外
这种方法也能保证对于[0,num[i]]间的每一个整数,均可以用若干个系数的和表示.
这里算法正确性的证明可以分[0,2^(k-1)]和[2^k,num[i]]两段来分别讨论得出.
*/
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 110
#define M 110
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&v,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
        int m,tw,tv;
        //复杂度O(∑log(num[i])*v)
        for(int i=1;i<=n;i++){
            m=num[i];
            //和完全背包一样这里第i种物品个数必须在第二层循环、背包容量在第三层循环
            //只有这样才能保证较多数目的第i种物品个数可以在较低数目的第i种物品基础上累加
            //才能达到第i种物品个数上限的物品个数放入背包,否则颠倒循环顺序实际装入的第i种物品个数可能并达不到物品上限
            for(int k=1;m>0;k<<=1){//枚举第i种物品可能的二进制组合
                //这里就是从组合的角度加的,总之就是1、2、4、8..这样的数
                //可以组合完所有可能的件数 直到这件物品的件数达到上限为止
                //保证之后01背包对于第i种物品的件数组合累加也不会超过第i种物品原本数量上限
                m-=k;
                //这里是当k左移的结果超出m后,只取m本身剩下的部分作为件数
                if(m<0) k+=m;
                tw=w[i]*k;
                tv=val[i]*k;
                //第i种物品二进制件数组合单独作为一个物品进行01背包
                for(int j=v;j>=tw;j--)
                    dp[j]=max(dp[j],dp[j-tw]+tv);
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}

/*
//ac 0ms 二进制优化 背包九讲版本 将多重背包转化为 二进制优化的01背包+完全背包
//这是多重背包最优化问题复杂度仅次于单调队列优化的版本
//复杂度比标准的二进制优化这个时间界O(∑log(num[i])*v) 可能要低
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 110
#define M 110
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

void ZeroOnePack(int tw,int tv){
    for(int j=v;j>=tw;j--)
        dp[j]=max(dp[j],dp[j-tw]+tv);
}

void CompletePack(int tw,int tv){
    for(int j=tw;j<=v;j++)
        dp[j]=max(dp[j],dp[j-tw]+tv);
}

void MultiplePack(int i){
    //当第i种物品 所有物品的体积总和不低于背包总容量时,
    //可以认为在背包容量v的前提下,第i种物品可以放入无限个,即:第i种物品数量无上限.
    //可以转化为完全背包问题,否则num[i]*w[i]<v,则第i种物品并不能在数量限制下填满容量v,需要考虑数量限制因素
    //实际这个条件可以拓展地更为宽泛为:v-num[i]*w[i]<w[i],也就是将第i种物品全部放入容量为v的背包,背包所剩余
    //的容量比第i种物品的体积小,也就是可以尽可能多地装第i种物品,装到不能再装为止.它的正确性就在于当使用背包
    //容量升序转移时最多所能装入的第i种物品个数肯定不会超过第i种物品的数量上限.
    if(num[i]*w[i]>=v)//v-num[i]*w[i]<w[i]这个条件也是可以的
        CompletePack(w[i],val[i]);
    else{//否则就采用二进制优化的01背包去求解
        int tw,tv;
        for(int k=1;num[i]>0;k<<=1){
            num[i]-=k;
            if(num[i]<0)
                k+=num[i];
            tw=k*w[i];
            tv=k*val[i];
            ZeroOnePack(tw,tv);
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&v,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
        for(int i=1;i<=n;i++)//判断每种物品 采用多重背包还是01背包求解
            MultiplePack(i);
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 0ms 多重背包朴素01背包做法 在每个可能背包容量j下线性枚举[1,num[i]]个物品构成新的物品放入背包
//复杂度O(∑num[i]*v) 这是把所有物品都当成一个物品01背包的复杂度,这个做法的复杂度还是比这个要小一点的
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 110
#define M 110
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&v,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
        int tw,tv;
        //复杂度O(∑num[i]*v)
        for(int i=1;i<=n;i++){
            //这里背包容量必须在第二层循环,物品个数必须在第三层循环,
            //枚举每个背包容量下尝试放入所有可能的第i种物品的个数,注意此时dp[j-tw]永远是前i-1种物品的最优解,是没有第i种物品的
            //如果包容量必须在第三层循环,物品个数必须在第二层循环,那么后面的物品个数组合就会累加在前面物品个数组合上
            //但最多的物品个数是num[i]上限,这样可能实际第i种物品拿了超过num[i]个上限,就wa
            for(int j=v;j>=w[i];j--){
                for(int k=1;k<=num[i];k++){//k<=num[i] && k*w[i]<=j
                    tw=w[i]*k;
                    if(j<tw) break;//如果当前容量已经装不下这个数目下的物品 就结束
                    tv=val[i]*k;
                    dp[j]=max(dp[j],dp[j-tw]+tv);
                }
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 0ms 多重背包转化01背包做法 采用线性组合方案 降低物品个数的枚举次数
//在前面放入第i种物品个数基础上再放入比上一次数目多1的物品个数,最后一次如果有剩余,则放入物品个数较少
//复杂度在二进制优化O(∑log(num[i])*v)和朴素01背包O(∑num[i]*v)之间
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 110
#define M 110
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&v,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
        int m,tw,tv;
        //复杂度在二进制优化O(∑log(num[i])*v)和朴素01背包O(∑num[i]*v)之间
        for(int i=1;i<=n;i++){
            m=num[i];
            //每个新的物品只比上一次物品个数多1个,
            for(int k=1;m>0;k++){
                m-=k;
                //最后一个有剩余,则此次放入物品个数会少一点
                if(m<0) k+=m;
                tw=w[i]*k;
                tv=val[i]*k;
                for(int j=v;j>=tw;j--)
                    dp[j]=max(dp[j],dp[j-tw]+tv);
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 0ms 多重背包朴素01背包做法 直接转换成∑num[i]个物品进行01背包
//复杂度O(∑num[i]*v)
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 2100
#define M 110
using namespace std;

int n,v,w[N],val[N],dp[M];

int main(){
    int T,a,b,m,id;
    scanf("%d",&T);
    while(T--){
        id=0;
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&v,&n);
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
    }
    return 0;
}
*/

/*
//ac 0ms 多重背包朴素01背包做法 直接转换成∑num[i]个物品进行01背包
//复杂度O(∑num[i]*v)
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 110
#define M 110
using namespace std;

int n,v,w[N],val[N],num[N],dp[M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&v,&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&w[i],&val[i],&num[i]);
        //实际物品个数是id,已经转化为一个标准的01背包了
        for(int i=1;i<=n;i++){
            for(int k=1;k<=num[i];k++)//连续k个物品都是第i种物品 做01背包
                for(int j=v;j>=w[i];j--)
                    dp[j]=max(dp[j],dp[j-w[i]]+val[i]);
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
*/

/*
注意:可行性问题O(nv)不能解决经典的物品有两个属性体积和价值的最优化价值的多重背包问题
*/

/*
暴力dfs搜索做法就是转化为01背包问题,进行暴力枚举 O(2^n)
当然可以应用二进制拆分减少同种物品的物品组合个数.
*/
