/*
题意:给你n种不同价值的硬币，价值为val[1],val[2]...val[n]，每种价值的硬币有num[1],num[2]...num[n]个，
问使用这n种硬币可以凑齐[1,m]内多少价值（换句话说，就是可以恰好支付的价格有多少）
链接:http://poj.org/problem?id=1742
思路:
*/
//ac POJ 1742 2610ms HDU 2844 483ms 滚动数组的可行性问题 完全背包
//每种有若干件的物品能否填满给定容量的背包”,只须考虑填满背包的可行性,
//不需考虑每件物品的价值时,即:实际物品体积和价值2个属性都是等价的,多重背包问题复杂度可以是O(nv)
//复杂度O(n*v)=10^2*10^5=10^7
//注意:可行性问题O(nv)并不能求解多重背包的最优解
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;

//dp[i][j]表示用了前i种物品填满容量为j的背包后,最多还剩下几个第i种物品可用
int n,m,val[N],num[N],dp[M];

int main(){
    while(scanf("%d%d",&n,&m)&& n+m){
        memset(dp,-1,sizeof(dp));//初始化-1都是不合法
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&num[i]);
        dp[0]=0;//初始状态0是合法
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++){//这里下界是0,第i个物品可以从任意容积基础上添加
                //注意:dp[j]=0是合法状态代表前i-1种物品填满容量为j的背包最多还剩下0个第i-1种物品,
                //即:刚好把第i-1种物品用完,但对于第i种物品可以在j容量这个基础上最多在放num[i]个第i种物品
                //-1才是实际没有凑出的价值
                if(dp[j]!=-1)
                    dp[j]=num[i];
            }
            for(int j=val[i];j<=m;j++)
                //将第i种物品加入背包容量为j-val[i]的背包,是否能得到之前没凑出过的价值
                //若之前价值没凑出过,这里dp[j]原始-1,即更新后dp[j]=dp[j-val[i]]-1
                //否则若之前dp[j]本身就凑出过,则不更新因为dp[j]本身就为num[i],可以在前i-1种物品上最多再添加num[i]个第i种物品
                //若dp[j-val[i]]=0,则说明第i个物品已经不能再放入背包了,如果dp[j]本身就为-1,则dp[j]最大值还是-1,若dp[j]本身是可达的则dp[j]>=0.
                dp[j]=max(dp[j],dp[j-val[i]]-1);//dp[j-val[i]]最多能放入第i种物品个数-1
            /*
            //ac 2594ms
            for(int j=0;j+val[i]<=m;j++)
                dp[j+val[i]]=max(dp[j+val[i]],dp[j]-1);
            */
        }
        int cnt=0;
        for(int i=1;i<=m;i++){
            if(dp[i]!=-1)
                cnt++;
        }
        printf("%d\n",cnt);
    }
    return 0;
}

/*
//ac POJ 1742 2454ms HDU 2844 499ms 可行性问题最简化版本 完全背包
//复杂度O(n*v)=10^2*10^5=10^7
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;

//dp[i][j]表示用了前i种物品填满容量为j的背包后,最多还剩下几个第i种物品可用
int n,m,val[N],num[N],dp[M];

int main(){
    while(scanf("%d%d",&n,&m)&& n+m){
        memset(dp,-1,sizeof(dp));//初始化-1都是不合法
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&num[i]);
        dp[0]=0;//初始状态0是合法
        for(int i=1;i<=n;i++){
            for(int j=0;j<=m;j++){
                if(dp[j]!=-1)
                    dp[j]=num[i];
                if(j>=val[i])
                    dp[j]=max(dp[j],dp[j-val[i]]-1);
            }
        }
        int cnt=0;
        for(int i=1;i<=m;i++){
            if(dp[i]!=-1)
                cnt++;
        }
        printf("%d\n",cnt);
    }
    return 0;
}
*/

/*
//ac POJ 1742 1344ms HDU 2844 452ms 限制物品数量的完全背包做法
//复杂度O(n*v)=10^2*10^5=10^7
//不过这个做法有时会wa,详情HDU 1059 Dividing,建议用背包九讲中的版本.
//这个做法还可以在转移时计算最小/最大数目 POJ 1787,方案数(目前没做过题,应该是可以的).
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 100010
using namespace std;

//dp[i][j]=1代表前i种物品价值和为j是存在的
//cnt[i][j]=k代表前i种物品价值和为j时,第i种物品已经加入了k个,k<=num[i],k不能超过第i种物品数量上限
int n,m,val[N],num[N],dp[M],cnt[M];

int main(){
    while(scanf("%d%d",&n,&m)&& n+m){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&num[i]);
        dp[0]=1;//初始状态
        for(int i=1;i<=n;i++){
            //每次都要初始化cnt数组,第i种物品刚开始还没装入 数目为0
            memset(cnt,0,sizeof(cnt));
            for(int j=val[i];j<=m;j++){
                //上一状态dp[j-val[i]]必须是可行的,并且之前 前i-1种物品为转移到j这个状态,即:dp[j]=0
                //并且加入第i种物品的数量不能超出上限
                //如果dp[j]前i-1种物品已经推出过,这里就不再转移,其cnt就是0,代表可以直接在前i-1种物品基础上最多再加入num[i]个第i种物品
                if(dp[j-val[i]] && !dp[j] && cnt[j-val[i]]+1<=num[i]){
                    dp[j]=1;
                    cnt[j]=cnt[j-val[i]]+1;
                }
            }
        }
        int ans=0;
        for(int i=1;i<=m;i++){
            if(dp[i])
                ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/


/*
//POJ 1742 会TLE HDU 2844 ac 546ms 二进制优化枚举方案数
//复杂度O(∑log(num[i])*v)=100*log(1000)*100000=10^8 s3时限 按道理不会TLE啊,可能POJ数据更强
#include<cstdio>
#include<cstring>
#define N 110
#define M 100010

int n,m,val[N],num[N],dp[M];

int main(){
    while(scanf("%d%d",&n,&m)&& n+m){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&num[i]);
        dp[0]=1;
        int tv;
        for(int i=1;i<=n;i++){
            for(int k=1;num[i]>0;k<<=1){
                num[i]-=k;
                if(num[i]<0) k+=num[i];
                tv=val[i]*k;
                for(int j=m;j>=tv;j--){
                    if(dp[j-tv])
                        dp[j]=1;
                }
            }
        }
        int cnt=0;
        for(int i=1;i<=m;i++){
            if(dp[i])
                cnt++;
        }
        printf("%d\n",cnt);
    }
    return 0;
}
*/

/*
//ac HDU 2844 249ms POJ 1742 TLE 多重背包+单调队列优化
//POJ有点奇怪...
//复杂度O(nv)=10^2*10^5=10^7
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m;
int a[110],c[110];
queue<int>q;//建立一个FIFO的队列q(此题的单调队列只进不出)
bool f[100100];
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        if(n==0&&m==0)return 0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&c[i]);
        memset(f,0,sizeof(f));
        f[0]=1;
        for (int i=1;i<=n;i++)//如下进行01背包，完全背包，多重背包的分解
        {
            int maxl=a[i]*c[i];
            if (c[i]==1)//如果只有一件物品， 则进行01背包
            {
                for(int j=m;j>=a[i];j--)
                if(f[j-a[i]])
                f[j]=1;
            }
            else if(m<=maxl)//如果物品总面值大于最大面值，则进行完全背包
            {
                for(int j=a[i];j<=m;j++)
                if (f[j-a[i]])
                f[j]=1;
            }//如下才是重头戏，完全背包的单调队列优化
            else for(int j=0;j<a[i];j++)//避免重复
            {
                while(q.size()>0) q.pop();//清空队列
                for(int k=j;k<=m;k+=a[i])//充分利用大小
                {
                    while(q.size()>0&&k-q.front()>maxl) q.pop();//始末两点之间的距离应小于第i种物品的总价值
                    if(!f[k])//由此对于枚举c[i]和m有了较大的提升
                    {
                        if(q.size()>0)//只有队列不为空，即可以从某点到达
                        f[k]=1;
                    }
                    else q.push(k);//如果等于0，则入队尾
                }
            }
        }
        int ans=0;
        for(int i=1;i<=m;i++)
            if(f[i])ans++;//统计可行的面值数
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 405ms 多重背包+bitset
//暂时没看bitset
//参考博客:https://blog.csdn.net/Paulliant/article/details/80837276
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<bitset>
#define FOR(i,x,y) for(int i=(x);i<=(y);i++)
#define DOR(i,x,y) for(int i=(x);i>=(y);i--)
typedef long long LL;
using namespace std;
struct Pack
{
    bitset<100003>dp;
    Pack(){dp.reset();dp[0]=1;}
    void load(int c,int m)
    {
        for(int k=1;k<=m;k<<=1)
        {
            dp|=(dp<<c*k);
            m-=k;
        }
        dp|=(dp<<c*m);
        return;
    }
};

int main()
{
    int m,n;
    while(scanf("%d%d",&m,&n),m||n)
    {
        Pack P;
        int a[103],b[103],ans=0;
        FOR(i,1,m)scanf("%d",&a[i]);
        FOR(i,1,m)scanf("%d",&b[i]);
        FOR(i,1,m)P.load(a[i],b[i]);
        FOR(i,1,n)ans+=P.dp[i];
        printf("%d\n",ans);
    }
    return 0;
}
*/
