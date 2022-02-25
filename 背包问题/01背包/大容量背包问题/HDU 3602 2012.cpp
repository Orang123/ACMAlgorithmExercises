#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;
//ac 31ms 01背包+价值和容量调换 恰好装满背包
//此题的一个国家所有人必须防止在一搜飞艇上 这种连续思维和POJ 1976较相像
/*
题意:有n个国家和m艘飞艇,每艘飞艇的最多载k人,每个国家的人数为a[i]名保镖+1名总统,
要求每个国家的所有人必须在同一艘飞艇上,载该国家的人可获b[i]美元,但是要求必须使得
强国先登上飞艇,弱国后登,实际第一个国家是最强的,后续国家强度递减.问载n个国家的人
最多能获得多少金钱.
n,m<=100,k<=100000,a[i]<=100000,b[i]<=100.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3602
思路:因为m搜飞艇的最多承载人数可达100*100000=10^7,显然不能作为背包容量,
可以将每个国家获得的金钱作为背包容量,这样背包容量最多是100*100=10^4.
然后求解在获得金钱相同情况下,最少承载多少人,这样按照01背包求解,其余状态是INF,
初始状态dp[0]=0.最后按照钱数逆序遍历,当前dp[i]是否是合法状态即可.
*/
//dp[i][j] 表达前i个国家承载在m搜飞船上获得金钱j,最少需要承载的人数
//实际滚动数组优化掉一维.只有dp[j]
int n,m,k,a[N],b[N],dp[M],sum;

//num是已经用了m搜飞艇中的多少人数名额,实际并不是所有名额都用来承载人,而是因为不够装满一个国家的人 而空余的
int cal(int num,int curp){
    int tp=(num+k-1)/k;//求出当前承载的人数最少需要几艘飞艇 即最后一搜飞艇的编号
    //int tp=ceil(1.0*num/k);//ceil 都double向上取整
    if(num+curp<=tp*k)//判断已经承载的人数的最后一搜飞艇是否还能装下第i个国家的所有人,若能装下直接返回num+curp
        return num+curp;
    else//否则最后一搜飞艇tp不能全部装下 第i个国家的人,则需要把第i个国家的人单独放在第tp+1搜飞艇,这样实际所用到的人数名额为tp*k+curp
        return tp*k+curp;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(dp,0x3f,sizeof(dp));
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a[i],&b[i]);
            a[i]++;
            sum+=b[i];
        }
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=b[i];j--)
                dp[j]=min(dp[j],cal(dp[j-b[i]],a[i]));
        }
        int ans=0;
        for(int i=sum;i>=1;i--){
            if(dp[i]<=m*k){//逆序 第一个i获得的金钱i dp[i]是合法的 就暑记录最多获得的金钱
                ans=i;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//把人数作为背包容积 获得金钱作为物品价值 会错 而且主要是也开不了人数10^7那么大数组
//dp[i][j] 表达前i个国家承载在m搜飞船上承载人数为j时,最多获得的金钱
//实际滚动数组优化掉一维.只有dp[j]
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 110
#define M 10100
using namespace std;

int n,m,k,a[N],b[N],dp[M],sum;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(dp,-0x3f,sizeof(dp));
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a[i],&b[i]);
            a[i]++;
            sum+=a[i];
        }
        dp[0]=0;
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=a[i];j--){
                if(dp[j-a[i]]<0) continue;
                if(k-(j-a[i])%k>=a[i])
                    dp[j]=max(dp[j],dp[j-a[i]]+b[i]);
                else
                    dp[(int)(ceil(1.0*(j-a[i])/k*k+a[i]))]=max(dp[(int)(ceil(1.0*(j-a[i])/k*k+a[i]))],dp[j-a[i]]+b[i]);
            }
        }
        int ans=0;
        for(int i=sum;i>=1;i--){
            if(dp[i]>0){
                ans=dp[i];
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

