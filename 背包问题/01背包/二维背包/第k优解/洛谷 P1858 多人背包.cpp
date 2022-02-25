#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define M 5100
using namespace std;
//ac 888ms 01背包 第k优解恰好装满 次有解可以相同,前k优解的和
//只初始化dp[0][1]=0
/*
题意:求01背包前k优解的价值和
DD和好朋友们要去爬山啦！他们一共有K个人,每个人都会背一个包.
这些包的容量是相同的,都是V.可以装进背包里的一共有N种物品,每种
物品都有给定的体积和价值.在DD看来,合理的背包安排方案是这样的:
每个人背包里装的物品的总体积恰等于包的容量.每个包里的每种物品
最多只有一件,但两个不同的包中可以存在相同的物品.任意两个人,他们
包里的物品清单不能完全相同.在满足以上要求的前提下,所有包里的所有
物品的总价值最大是多少呢？
链接:https://www.luogu.com.cn/problem/P1858
思路:实际就是求k个背包下恰好装满的情况最大价值和,就是前k优解之和,
k个解的值可以有相同,但背包必须恰好装满.
*/
int n,v,k,w[N],val[N],dp[M][55],A[55],B[55];

int main(){
    memset(dp,-0x3f,sizeof(dp));
    scanf("%d%d%d",&k,&v,&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&w[i],&val[i]);
    /*
    因为是恰好装满,所以只初始化最优解(1)为0
    因为如果将各个次有解dp[0][1..k]都初始化为0,
    最终答案dp[v][1..k]存放的各个次优解全是最优解
    的情况,如果dp时判断dp[j][c]!=dp[j][c-1] c++,次
    优解里就不能含有相等的值,但此题可以相等,不合题意,
    只是要最优解的中实际选择的物品不完全相同,取最大
    最优解的值即可.
    而只初始化dp[0][1]=0,最后dp[v][1..k]中存放的次优解,
    实际是在各个j=v下的次优解(恰好装满的情况).
    */
    dp[0][1]=0;
    int t;
    for(int i=1;i<=n;i++){
        for(int j=v;j>=w[i];j--){
            //优化1:如果最优解都不能恰好装满其余次优解更不可能恰好装满
            if(dp[j-w[i]][1]<0) continue;
            for(t=1;t<=k;t++){
                A[t]=dp[j-w[i]][t]+val[i];
                B[t]=dp[j][t];
            }
            A[t]=B[t]=-1;
            int a,b,c;
            a=b=c=1;
            while(c<=k && (A[a]!=-1 || B[b]!=-1)){
                if(A[a]>B[b])
                    dp[j][c]=A[a++];
                else
                    dp[j][c]=B[b++];
                c++;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=k;i++)//累加各个 背包容量下恰好装满的最优解,即dp[v][1..k]下的各个次优解
        ans+=dp[v][i];
    printf("%d",ans);
    return 0;
}

/*
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+100;
int d[55][maxn],tmp[55];
int main()
{
    int k,V,n;
    cin>>k>>V>>n;
    memset(d,-0x3f,sizeof(d));
    d[1][0]=0;
    for(int i=1;i<=n;i++)
    {
        int v,w;
        cin>>v>>w;
        for(int j=V;j>=v;j--)
        {
            int t1=1,t2=1,t3=k,cnt=0;
            while(t3--)
            {
                if(d[t1][j]>d[t2][j-v]+w)
                    tmp[++cnt]=d[t1++][j];
                else tmp[++cnt]=d[t2++][j-v]+w;
            }
            for(int l=1;l<=k;l++)d[l][j]=tmp[l];
        }
    }
    int ans=0;
    for(int i=1;i<=k;i++)ans+=d[i][V];
    printf("%d\n",ans);
    return 0;
}
*/

/*
//来自博客:https://blog.csdn.net/u012350533/article/details/12361147
//另一种不初始化dp[0][1]=0,而是全部初始化dp为0,背包剩余容量采用j=min(v,cur+g[i].a),
//没看太懂,需要排序
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn=5000+5;

int a[maxn],b[maxn];
int dp[maxn][50];

int n,k,v;


struct Goods
{
     int a, b;
     bool operator < (const Goods& r) const
     {
        return a < r.a;
     }
} g[maxn];


inline void debug()
{
     printf("where is wrong?\n");
}

inline int max(int a,int b)
{
    return a>b?a:b;
}

inline int min(int a,int b)
{
    return a<b?a:b;
}

inline void solve()
{
     int x,y,z,i,j,t;
     memset(dp,0,sizeof(dp));
     a[k+1]=b[k+1]=-1;
     int cur=0;
     for(i=0;i<n;i++)//n种物品；
     {
         for(j=min(v,cur+g[i].a);j>=g[i].a;j--)//why? j=min(v,cur+g[i].a)
         {
             for(t=1;t<=k;t++)
             {
                 a[t]=dp[j-g[i].a][t]||j==g[i].a&&t==1?dp[j-g[i].a][t]+g[i].b:0;
                 b[t]=dp[j][t];
             }
             x=y=z=1;
             while(z<=k&&(x<=k||y<=k))
             {
                 if(a[x]>b[y])
                 {
                     dp[j][z]=a[x];
                         x++;
                 }
                 else
                 {
                     dp[j][z]=b[y];
                     y++;
                 }
                // cout << dp[j][z] << endl;//不能去重；
                // if(dp[j][z]!=dp[j][z-1])
                z++;//此时dp[v][k]保存第k优解；
            }
         }
         cur=min(v,cur+g[i].a);//why? cur=min(v,cur+g[i].a)
     }
     int res=0;
     for(int kk=1;kk<=k;kk++)
     {
         res+=dp[v][kk];
     }
     printf("%d\n",res);
}

int main()
{
     while(scanf("%d%d%d",&k,&v,&n)!=EOF)
     {
         for(int i=0;i<n;i++)
         scanf("%d%d",&g[i].a,&g[i].b);
         sort(g, g+n);//为什么要排序
         solve();
     }
     return 0;
}
*/
