/*
题意:给出每个设备的价值和物体的数量,现在要将这些设备
分别分给A、B两个部门,如何分使得A,B所得价值最接近并且A的价值不能小于B.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1171
思路:实际就是要尽可能得将A、B所分得的设备价值和相等,并且A得到价值和不能比B少,
就是如何组合设备的问题,实际可以考虑如何分给B尽可能多的设备价值使其设备价值总和不超过
所有设备价值总和的一半.因为所有设备的价值总和<=50*100*50=250000,设备数量(50*100=5000)
并不算多,因此可以将一种设备的所有个数看成不同的物品,将其转化为01背包问题,
背包容量为物品价值总和的一半,物品体积和价值都是其价值,求解尽可能多地将设备分给B,
尽可能多地装满容量为sum/2的背包,那么dp[sum/2]所存放的价值一定<=sum/2,将其分给B,
另一半sum-dp[sum/2](价值)分给A即可,因为sum-dp[sum/2]>=sum/2.
*/
//ac 15ms 可行解问题 背包九讲解法
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 55
#define M 125010
using namespace std;

int n,val[N],num[N],dp[M],sum;

int main(){
    int ans,tp;
    while(scanf("%d",&n) && n>0){
        sum=0;
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&val[i],&num[i]);
            sum+=val[i]*num[i];
        }
        tp=sum/2;
        ans=0;
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=tp;j++){
                if(dp[j]!=-1)
                    dp[j]=num[i];
                if(j>=val[i])
                    dp[j]=max(dp[j],dp[j-val[i]]-1);
                if(dp[j]!=-1)
                    ans=max(ans,j);
            }
        }
        printf("%d %d\n",sum-ans,ans);
    }
    return 0;
}

/*
//ac 78ms 完全背包+二进制优化的01背包 背包九讲
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 55
#define M 125010
using namespace std;

int n,val[N],num[N],dp[M],sum;

int main(){
    int tp;
    while(scanf("%d",&n) && n>0){
        sum=0;
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&val[i],&num[i]);
            sum+=val[i]*num[i];
        }
        tp=sum/2;
        for(int i=1;i<=n;i++){
            if(num[i]*val[i]>=tp){
                for(int j=val[i];j<=tp;j++)
                    dp[j]=max(dp[j],dp[j-val[i]]+val[i]);
            }
            else{
                int tw;
                for(int k=1;num[i]>0;k<<=1){
                    num[i]-=k;
                    if(num[i]<0)
                        k+=num[i];
                    tw=k*val[i];
                    for(int j=tp;j>=tw;j--)
                        dp[j]=max(dp[j],dp[j-tw]+tw);
                }
            }
        }
        printf("%d %d\n",sum-dp[tp],dp[tp]);
    }
    return 0;
}
*/

/*
//ac 733ms 01背包 背包容量尽可能多地装
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

int dp[250005];//背包总容量上限<=50*100*50=250000
//用多重背包二进制优化的思想效率会高些46ms，这个700ms
int main(){
    int N,num,x,a[5500],sum,index;
    while(scanf("%d",&N)&&N>0){
        memset(dp,0,sizeof(dp));//背包容量尽可能多地装,所以状态都是合法的
        index=sum=0;
        for(int i=1;i<=N;i++){
            scanf("%d%d",&x,&num);
            while(num--){
                a[++index]=x;
                sum+=x;
            }
        }
        for(int i=1;i<=index;i++){
            for(int j=sum/2;j>=a[i];j--)
                dp[j]=max(dp[j],dp[j-a[i]]+a[i]);
        }
        printf("%d %d\n",sum-dp[sum/2],dp[sum/2]);
    }
    return 0;
}
*/

/*
//ac 1014ms 母函数做法
#include <iostream>
#include <cstring>
using namespace std;
const int maxn=3e5+100;
int n;
int c1[maxn],c2[maxn];
int num[55],data[55];int sum;
void init()
{
    sum=0;
    for(int i=1;i<=n;++i)
    {
        cin>>data[i]>>num[i];
        sum+=data[i]*num[i];
    }
}
void solve()
{
    memset(c1,0,sizeof(c1));
    memcpy(c2,c1,sizeof(c1));
    for(int i=0;i<=num[1];++i)
        c1[i*data[1]]=1;
    for(int i=2;i<=n;++i)
    {
        for(int j=0;j<=sum/2;++j)
        {
            if(c1[j])
            for(int k=0;k+j<=sum/2&&k/data[i]<=num[i];k+=data[i])
                c2[k+j]+=c1[j];
        }
        memcpy(c1,c2,sizeof(c2));
        memset(c2,0,sizeof(c2));
    }
    int i=1;
    for(i=sum/2;i>=0;--i)
        if(c1[i])
            break;
    cout<<sum-i<<" "<<i<<endl;
}
int main(int argc, const char * argv[])
{
    while(cin>>n&&n>=0)
    {
        init();
        solve();
    }
    return 0;
}
*/
/*
多重背包做法 如上可行解或二进制优化的01背包
*/

/*
//ac 717ms 01背包 背包容量容量恰好装满
#include<cstdio>
#include<algorithm>
#include<cstring>
#define INF -0x3f3f3f3f
using namespace std;

int dp[250005];//背包总容量上限<=50*100*50=250000
int main(){
    int N,num,x,a[5500],sum,index;
    while(scanf("%d",&N)&&N>0){
        memset(dp,-0x3f,sizeof(dp));//除了dp[0]合法其它状态都不合法,初始化为-INF
        index=sum=0;
        for(int i=1;i<=N;i++){
            scanf("%d%d",&x,&num);
            while(num--){
                a[++index]=x;
                sum+=x;
            }
        }
        dp[0]=0;//0状态合法 用来记录恰好装满的情况
        for(int i=1;i<=index;i++){
            for(int j=sum/2;j>=a[i];j--)
                dp[j]=max(dp[j],dp[j-a[i]]+a[i]);
        }
        int ans=0;//有可能只有一个设备,只能分给A或B的其中一个,所以ans初始化为0,因为dp[i]除了dp[0]都不合法
        for(int i=sum/2;i>=1;i--){//恰好装满 最少是将价值为1的设备分给B 所以下限是1
            if(dp[i]>0){//dp[i]>0的才属于恰好装满 背包的合法状态
                ans=i;
                //ans=dp[i];
                break;
            }
        }
        //ans不初始化为0,for循环下限判断到0,dp[i]判断条件修改为dp[i]>=0也是可以的,如下
        //int ans;
        //for(int i=m-5;i>=0;i--)
            //if(dp[i]>=0)
        printf("%d %d\n",sum-ans,ans);//ans 为0时,输出sum和0,因为此时只有一个设备,只能分给A或B的其中一个
    }
    return 0;
}
*/

/*
//TLE 暴力搜索枚举 (未添加后缀剪枝)
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 5100
#define INF -0x3f3f3f3f
using namespace std;

int n,num,t,val[N],sum,ans;

int dfs(int k,int res){
    if(res<=sum/2 && res>ans){
        ans=res;
        if(res == sum/2) return 1;
    }
    if(res>sum/2) return 0;
    if(k == num+1) return 0;
    if(dfs(k+1,res+val[k])) return 1;
    if(dfs(k+1,res)) return 1;
    return 0;
}

int main(){
    int x;
    while(scanf("%d",&n) && n>0){
        ans=sum=num=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&x,&t);
            while(t--){
                val[++num]=x;
                sum+=x;
            }
        }
        dfs(1,0);
        printf("%d %d\n",sum-ans,ans);//ans 为0时,输出sum和0,因为此时只有一个设备,只能分给A或B的其中一个
    }
    return 0;
}
*/

