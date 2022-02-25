#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 45
#define M 40100
using namespace std;
//ac 15ms 01����ͳ�Ʒ�����,�ټ���ռ���п��ܵĸ���
/*
����:n������,ÿ����ֻ������ѡ��,һ�����������,��Եĸ���Ϊ1/2,
Ҫ����һ���˱��������ж��ٷֲ��ܱ�֤��p�ĸ��ʲ�����.
ע��:��n������ȫ��Ե�,ÿ����Ŀ�����ֻ�ǵ��״�Ի��Ǵ��.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4815
˼·:���ڵ�һ��������������п��ܵ÷ֵ������Ϊ2^n�ֿ���,
����n����÷�j�ĸ���Ϊj�������������2^n�������г��ִ���
cnt(j)��ռ�ı���,��P(j)=cnt(j)/2^n.���԰���01����ͳ��n����
�÷ֳ��ֵĴ���,Ȼ���շ��������ۼ�ÿ���������ֵĴ���,ֱ��
�����ܺ�/2^n��С��pʱ,��ʱ�ķ���x������һ��������Ӧ�õ��ķ�,
��Ϊ�������ж��ٷֲ��ܱ�֤��p�ĸ��ʲ����䡱,���ڵ�һ���˵õ�
��ЩС�ڵ���x�ĵ÷ֵĸ���Ϊp,��ô�ڶ�����ֻҪ���ٵ�x��,����
��p�ĸ��ʲ�����,��Ϊ��һ������p�ĸ��ʵĵ÷���С�ڵ���p��.
�պõ����Ǹ��ٽ����(���ʸպ�Ϊp),ʵ�ʾ��ǵ�һ���˵÷ָ���
С�ڵ���ĳ�������ĸ���,�Ǿ������е�����������ĵ÷ָ���֮��.
��p=P(x1)+P(x2)+P(x3)..+P(xn),x1,x2,..,xn�÷ֶ�С�ڵ��ڸ���p
��Ӧ�ķ���.
*/
//dp[j]��ʾ��n����÷�j���ֵĴ���
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
        all=pow(2,n);//��һ��������÷ֵ��������
        for(int i=0;i<=sum;i++){//��0��Ҳ��һ�����,��:������ȫ����.
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
//ac 31ms ��ά01����ͳ�Ƶ÷ָ���,���ۼӿ��ܵ÷�����ĸ���
//ÿ���ⶼҪ��,��Ҫѡ��������Ի�������,����Ҫע��,�������
//���ۼ�,��i��������,����ǰi-1����÷�Ϊj-val[i]�ĸ����½���
//i�������Գ�0.5,����ǰi-1����÷�Ϊj�ĸ����½���i��������ĸ��ʳ�0.5�ۼ�.
//�����ǰ�÷�jС�ڵ�i����õ��ķ���,��ô��i��ֻ����ǰi-1����÷�Ϊj�ĸ����½���i��������ĸ���
//dp[i][j]��ʾ��ǰi����÷�Ϊj��������ĸ��ʺ�
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
        dp[0][0]=1.0;//��ʼ״̬����Ϊ1 0����÷�Ϊ0
        for(int i=1;i<=n;i++){
            for(int j=sum;j>=0;j--){
                if(j>=val[i])
                    //2�����
                    //1.��dp[i-1][j-val[i]]�����µ�i������,�÷�Ϊj
                    //2.dp[i-1][j]�����µ�i������,�÷���Ȼ��j
                    //��Ϊ����������ʶ�Ϊ0.5,���Գ�0.5
                    dp[i][j]=dp[i-1][j]*0.5+dp[i-1][j-val[i]]*0.5;
                else
                    //j�÷�С�ڵ�i��,��ô��i��ֻ����dp[i-1][j]����������
                    dp[i][j]=dp[i-1][j]*0.5;
            }
        }
        for(int i=0;i<=sum;i++){
            if(!dp[n][i]) continue;//���Ϸ�״̬ ������
            cnt+=dp[n][i];//�ۼ�n����÷��µĸ�������֮��,����һ�β�С��pʱ,�����ǰ�÷�
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
//ac 15ms һά01����ͳ�Ƶ÷ָ���,���ۼӿ��ܵ÷�����ĸ���
//dp[j]��ʾ��n����÷�Ϊj��������ĸ��ʺ� ���������Ż����˵�һά
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
//TLE ����ö������ 2^40=1099511627776 10^12 �϶�TLE
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 45
#define M 40100
using namespace std;

int n,val[N],sum,ans[M];
double p,all;

//2^40=1099511627776 ���Ӷȿɴ�10^12 �϶�TLE
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
        all=pow(2,n);//��һ��������÷ֵ��������
        dfs(1,0);
        for(int i=0;i<=sum;i++){//��0��Ҳ��һ�����,��:������ȫ����.
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
//ac 15ms ���ֲ�������
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
