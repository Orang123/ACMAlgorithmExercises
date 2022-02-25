#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 45
#define M 40100
using namespace std;
//ac 15ms 01背包统计方案数,再计算占所有可能的概率
/*
题意:n个问题,每个题只有两个选项,一个人随机答题,答对的概率为1/2,
要问另一个人必须至少有多少分才能保证有p的概率不会输.
注意:这n道题是全答对的,每到题的可能性只是到底答对还是答错.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4815
思路:对于第一个人随机答题所有可能得分的情况数为2^n种可能,
而答n道题得分j的概率为j这个分数在所有2^n可能性中出现次数
cnt(j)所占的比率,即P(j)=cnt(j)/2^n.可以按照01背包统计n道题
得分出现的次数,然后按照分数升序累加每个分数出现的次数,直到
次数总和/2^n不小于p时,此时的分数x就是另一个人至少应得到的分,
因为“至少有多少分才能保证有p的概率不会输”,现在第一个人得到
这些小于等于x的得分的概率为p,那么第二个人只要至少得x分,他就
有p的概率不会输,因为第一个人有p的概率的得分是小于等于p的.
刚好等于那个临界分数(概率刚好为p),实际就是第一个人得分概率
小于等于某个分数的概率,那就是所有低于这个分数的得分概率之和.
即p=P(x1)+P(x2)+P(x3)..+P(xn),x1,x2,..,xn得分都小于等于概率p
对应的分数.
*/
//dp[j]表示做n道题得分j出现的次数
int n,val[N],dp[M],sum;
double p,all;

int main(){
    int T;
    double cnt;
    scanf("%d",&T);
    while(T--){
        cnt=sum=0;
        memset(dp,0,sizeof(dp));
        scanf("%d%lf",&n,&p);
        for(int i=1;i<=n;i++){
            scanf("%d",&val[i]);
            sum+=val[i];
        }
        dp[0]=1;
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=val[i];j--)
                dp[j]+=dp[j-val[i]];
        }
        all=pow(2,n);//第一个人随机得分的所有情况
        for(int i=0;i<=sum;i++){//得0分也算一种情况,即:所有题全做错.
            if(!dp[i]) continue;
            cnt+=dp[i];
            if(cnt/all>=p){
                printf("%d\n",i);
                break;
            }
        }
    }
    return 0;
}

/*
//ac 31ms 二维01背包统计得分概率,再累加可能得分情况的概率
//每道题都要做,但要选择的是做对还是做错,但是要注意,这里概率
//是累加,第i道题做对,是在前i-1道题得分为j-val[i]的概率下将第
//i道题做对乘0.5,和在前i-1道题得分为j的概率下将第i道题做错的概率乘0.5累加.
//如果当前得分j小于第i道题得到的分数,那么第i题只能在前i-1道题得分为j的概率下将第i道题做错的概率
//dp[i][j]表示做前i道题得分为j所有情况的概率和
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 45
#define M 40100
using namespace std;

int n,val[N],sum;
double p,dp[N][M];

int main(){
    int T;
    double cnt;
    scanf("%d",&T);
    while(T--){
        cnt=sum=0;
        memset(dp,0,sizeof(dp));
        scanf("%d%lf",&n,&p);
        for(int i=1;i<=n;i++){
            scanf("%d",&val[i]);
            sum+=val[i];
        }
        dp[0][0]=1.0;//初始状态概率为1 0道题得分为0
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=0;j--){
                if(j>=val[i])
                    //2种情况
                    //1.在dp[i-1][j-val[i]]概率下第i题做对,得分为j
                    //2.dp[i-1][j]概率下第i题做错,得分仍然是j
                    //因为做对做错概率都为0.5,所以乘0.5
                    dp[i][j]=dp[i-1][j]*0.5+dp[i-1][j-val[i]]*0.5;
                else
                    //j得分小于第i题,那么第i题只能在dp[i-1][j]基础上做错
                    dp[i][j]=dp[i-1][j]*0.5;
            }
        }
        for(int i=0;i<=sum;i++){
            if(!dp[n][i]) continue;//不合法状态 不考虑
            cnt+=dp[n][i];//累加n道题得分下的各个概率之和,当第一次不小于p时,输出当前得分
            if(cnt>=p){
                printf("%d\n",i);
                break;
            }
        }
    }
    return 0;
}
*/

/*
//ac 15ms 一维01背包统计得分概率,再累加可能得分情况的概率
//dp[j]表示做n道题得分为j所有情况的概率和 滚动数组优化掉了第一维
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 45
#define M 40100
using namespace std;

int n,val[N],sum;
double p,dp[M];

int main(){
    int T;
    double cnt;
    scanf("%d",&T);
    while(T--){
        cnt=sum=0;
        memset(dp,0,sizeof(dp));
        scanf("%d%lf",&n,&p);
        for(int i=1;i<=n;i++){
            scanf("%d",&val[i]);
            sum+=val[i];
        }
        dp[0]=1.0;
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=0;j--){
                if(j>=val[i])
                    dp[j]=dp[j-val[i]]*0.5+dp[j]*0.5;
                else
                    dp[j]*=0.5;
            }
        }
        for(int i=0;i<=sum;i++){
            if(!dp[i]) continue;
            cnt+=dp[i];
            if(cnt>=p){
                printf("%d\n",i);
                break;
            }
        }
    }
    return 0;
}
*/

/*
//TLE 暴力枚举搜索 2^40=1099511627776 10^12 肯定TLE
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 45
#define M 40100
using namespace std;

int n,val[N],sum,ans[M];
double p,all;

//2^40=1099511627776 复杂度可达10^12 肯定TLE
void dfs(int k,int sum){
    if(k == n+1){
        ans[sum]++;
        return;
    }
    dfs(k+1,sum+val[k]);
    dfs(k+1,sum);
}

int main(){
    int T;
    double cnt;
    scanf("%d",&T);
    while(T--){
        cnt=sum=0;
        memset(ans,0,sizeof(ans));
        scanf("%d%lf",&n,&p);
        for(int i=1;i<=n;i++){
            scanf("%d",&val[i]);
            sum+=val[i];
        }
        all=pow(2,n);//第一个人随机得分的所有情况
        dfs(1,0);
        for(int i=0;i<=sum;i++){//得0分也算一种情况,即:所有题全做错.
            if(!ans[i]) continue;
            cnt+=ans[i];
            if(cnt/all>=p){
                printf("%d\n",i);
                break;
            }
        }
    }
    return 0;
}
*/

/*
//ac 15ms 二分查找做法
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
typedef  long long LL ;
int  x[48] ;
LL   dp[40008] ;
int  num[40008] ;
LL   cnt[40008] ;

int  main(){
     double p ;
     int  sum , n  , i , j , k  , t ;
     cin>>t ;
     while(t--){
          scanf("%d%lf" , &n , &p) ;
          sum = 0 ;
          for(i = 1 ; i <= n ; i++){
                scanf("%d" , &x[i]) ;
                sum += x[i] ;
          }
          memset(dp , 0 , sizeof(dp)) ;
          dp[0] = 1 ;
          for(i = 1 ; i <= n ; i++){
              for(j = sum ; j >= x[i] ; j--){
                  if(dp[j - x[i]]) dp[j] += dp[j-x[i]] ;
              }
          }
         k = 0 ;
         for(i = 0 ; i <= sum ; i++){
             if(dp[i] == 0)  continue ;
             k++ ;
             num[k] =  i ;
             cnt[k] =  dp[i] ;
         }
         double all = pow(2.0 , n)  , s ;
         int L = 0 , R = sum  , M  , ans  ;
         while(L <= R){
              M = (L + R) >> 1 ;
              s = 0 ;
              for(i = 1 ; i <= k ; i++){
                   if(num[i] > M) break ;
                   s += cnt[i] ;
              }
              if(s >= p * all){
                   ans = M ;
                   R = M-1 ;
              }
              else  L = M+1 ;
         }
         printf("%d\n" , ans) ;
     }
     return 0  ;
}
*/
