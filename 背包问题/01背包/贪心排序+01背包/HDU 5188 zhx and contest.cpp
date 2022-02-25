#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 35
#define M 300100
using namespace std;
//ac 31ms l-t升序排序+01背包
/*
题意:有n道题,给出每道题的用时t[i]和得分v[i],并且在l[i]时间之前
做出来第i道题会被认为作弊不得分,而且一道题不能分开几次做,问至少
得到w分需要最少用多长时间.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5188
思路:如果每到题没有要求不能再l[i]时间之前做出,这就是一个典型的01背包问题,
考虑若两道题i,j,v[i]==v[j],即做出时间相等,如果l[i]<l[j],即i题j题分别不能在
在l[i]、l[j]之前做出来,此时如果考虑先做j题,后做i题会导致做第i题时,只能考虑
放在j题之后,这样会导致实际获得相同分数时用时较长.eg:样例中
3 6
4 1 8
6 8 10
1 5 2   三道题,若先做第一道4 1 8,最早在4时刻开始做,刚好8时刻做完得分1,第三道题
只有在8时刻做时,9时刻做完得分5,总得分6,这样至少要9时间才能得分6,而实际如果先做
第三题,在1时刻开始做,2时刻做完或3时刻做4时刻做完,之后立即在4时刻做第一道,8时刻
做完,就能得分6,这是因为每道题的l[i]会影响dp[j-t[i]]对子问题的选取,如果先做第一道,
那么j-t[i]最小只会从4时刻开始,也就是dp[0..4]并没有值,因此就会影响后续第三题子问题
j-t[i]只有刚好选在8时刻开始才能有最大得分.
因此做题顺序会影响到最终的结果,我们就需要按照l-t对做题顺序进行排序.

总结:实际这类需要排序的题,可能无法直接看出需要按照什么规则排序,可以试着先用裸的01背包
跑跑样例,一般样例答案会出错,再分析出错的问题在哪,去考虑 如果将某个选取的顺序改变结果是否
就能对,再去想这种顺序的改变是基于什么规则改变的.
说明:"zhx is naive!"的情况,//这里规定时间应该就是指sum和l的最大值,要不然,实际时间如果无限制,
//只要所以题目的得分大于m,就一定能把所有题目做完,本题在题目描述上还是有一定漏洞.
*/
int n,m,dp[M],sum;
struct Pro{
    int t,v,l;
    bool operator <(const Pro &x)const{
        return l-t<x.l-x.t;
    }
}pro[N];

int main(){
    int l;
    while(scanf("%d%d",&n,&m)!=EOF){
        l=sum=0;
        memset(dp,0,sizeof(dp));//必须是尽可能多地装满,每道题开始时间才可以不必尾随紧接着上一题
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&pro[i].t,&pro[i].v,&pro[i].l);
            sum+=pro[i].t;//sum表示做完所有题的时间
            l=max(l,pro[i].l);//所以题中提前做出题最大的时间限制
        }
        sum=max(sum,l);//求取最大值,如样例1 只有1题,做题时间是1,而l[i]=7,实际最早做出时间是7,因此取1和7最大值7作为背包容量
        sort(pro+1,pro+1+n);
        for(int i=1;i<=n;i++){
            int tp=max(pro[i].t,pro[i].l);//取最大值 保证j-pro[i].t>=0 数组下标不为负
            for(int j=sum;j>=tp;j--)//j>=pro[i].l,标明实际做出时间点>=pro[i].l
                dp[j]=max(dp[j],dp[j-pro[i].t]+pro[i].v);
        }
        /*
        for(int i=1;i<=n;i++){
            int tp=max(pro[i].t,pro[i].l);
            for(int j=sum;j>=pro[i].l;j--)//j>=pro[i].l,标明实际做出时间点>=pro[i].l
                if(j>=pro[i].t)
                    dp[j]=max(dp[j],dp[j-pro[i].t]+pro[i].v);
        }
        */
        int flag=0;
        for(int i=0;i<=sum;i++){
            if(dp[i]>=m){
                flag=1;
                printf("%d\n",i);
                break;
            }
        }
        //这里规定时间应该就是指sum和l的最大值,要不然,实际时间如果无限制,
        //只要所以题目的得分大于m,就一定能把所有题目做完,本题在题目描述上还是有一定漏洞.
        if(!flag)//规定时间内不能获得m分
            printf("zhx is naive!\n");
    }
    return 0;
}

/*
//ac 15ms 二分最小时间+dfs验证
//参考博客:https://blog.csdn.net/weixin_30510153/article/details/98550997
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=35;
long long sum[maxn];
int n,w;
struct node
{
     int t,v,l;
     void input()
     {
         scanf("%d%d%d",&t,&v,&l);
     }
     friend bool operator<(node a,node b)
     {
         return a.l-a.t<b.l-b.t;
     }
 }q[maxn];
 bool dfs(int p,int tot,long long va)
 {
     if(va>=w)   return 1;
     if(p<0) return 0;
     if(va+sum[p]<w) return 0;   //如果加上剩下的价值仍小于w
     if(tot-q[p].l>=0&&tot-q[p].t>=0)    if(dfs(p-1,tot-q[p].t,va+q[p].v))   return 1;
     if(dfs(p-1,tot,va)) return 1;
     return 0;
 }
 int main()
 {
     #ifndef ONLINE_JUDGE
     #endif
     int i,j,k;
     while(scanf("%d%d",&n,&w)!=EOF)
     {
         for(i=0;i<n;i++)    q[i].input();
         sort(q,q+n);
         for(i=0;i<n;i++)
         {
             if(i==0)    sum[i]=q[i].v;
             else sum[i]=sum[i-1]+q[i].v;
         }
         if(sum[n-1]<w)
         {
             printf("zhx is naive!\n");
             continue;
         }
         int l=0,r=100000*n;  //最高用时
         int ans;
         while(l<=r)
         {
             int mid=(l+r)>>1;
             if(dfs(n-1,mid,0))  r=mid-1,ans=mid;
             else l=mid+1;
         }
         printf("%d\n",ans);
     }
 }
*/

/*
//ac 31ms 二分最小时间+dfs验证
//参考博客:https://blog.csdn.net/u011663071/article/details/44307273
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>
#include <vector>
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define delf int m=(l+r)>>1
#define ll long long int

using namespace std;

int n,w;
int ans;
int sum[31];

struct node
{
    int t,v,l;
} a[31];

bool cmp(node a1,node b1)
{
    return a1.l-a1.t<b1.l-b1.t;
}

void dfs(int s,int t,int p)
{
    if (ans==1)
        return ;
    if (p>=w)
    {
        ans=1;
        return ;
    }
    if (s<=0||t<1)
        return ;
    if (p+sum[t]<w)
        return ;
    if (s>=a[t].l&&s>=a[t].t)
        dfs(s-a[t].t,t-1,p+a[t].v);
    dfs(s,t-1,p);
    return ;
}

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    while (~scanf("%d%d",&n,&w))
    {
        memset(sum,0,sizeof(sum));
        int s1=0;
        int s2=0;
        int p=0;
        for (int i=1;i<=n;i++)
        {
            scanf("%d%d%d",&a[i].t,&a[i].v,&a[i].l);
            s1+=a[i].v;
            s2+=a[i].t;
            p=max(p,a[i].l);
        }
        sort(a+1,a+n+1,cmp);
        s2+=p;
        sum[0]=0;
        for (int i=1;i<=n;i++)
        {
            sum[i]=sum[i-1]+a[i].v;
        }
        if (s1<w)
        {
            printf("zhx is naive!\n");
            continue ;
        }
        int l=1;
        int h=s2;
        while (l<=h)
        {
            int m=(l+h)>>1;
            ans=0;
            dfs(m,n,0);
            if (ans==1)
                h=m-1;
            else
                l=m+1;
        }
        printf("%d\n",l);
    }
}
*/

/*
//我自己写的二分最小时间+dfs验证
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 35
#define M 300100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,ans;
struct Pro{
    int t,v,l;
    bool operator <(const Pro &x)const{
        return l-t<x.l-x.t;
    }
}pro[N];

void dfs(int k,int t,int sum){
    if(sum>=m)
        ans=min(ans,t);
    if(k == n+1)
        return;
    if(t+pro[k].t>=pro[k].l)
        dfs(k+1,t+pro[k].t,sum+pro[k].v);
    dfs(k+1,t,sum);
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&pro[i].t,&pro[i].v,&pro[i].l);
        sort(pro+1,pro+1+n);
        int l=0,r=M,mid;
        while(l<r){
            mid=(l+r)/2;
            ans=INF;
            printf("l=%d r=%d\n",l,r);
            dfs(1,mid,0);
            if(ans!=INF)
                r=mid-1;
            else
                l=mid+1;
        }
        //if(ans!=INF)
            printf("%d\n",mid+1);
        //else
            //printf("zhx is naive!\n");
    }
    return 0;
}
*/
