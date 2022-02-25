#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 35
#define M 300100
using namespace std;
//ac 31ms l-t��������+01����
/*
����:��n����,����ÿ�������ʱt[i]�͵÷�v[i],������l[i]ʱ��֮ǰ
��������i����ᱻ��Ϊ���ײ��÷�,����һ���ⲻ�ֿܷ�������,������
�õ�w����Ҫ�����ö೤ʱ��.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5188
˼·:���ÿ����û��Ҫ������l[i]ʱ��֮ǰ����,�����һ�����͵�01��������,
������������i,j,v[i]==v[j],������ʱ�����,���l[i]<l[j],��i��j��ֱ�����
��l[i]��l[j]֮ǰ������,��ʱ�����������j��,����i��ᵼ������i��ʱ,ֻ�ܿ���
����j��֮��,�����ᵼ��ʵ�ʻ����ͬ����ʱ��ʱ�ϳ�.eg:������
3 6
4 1 8
6 8 10
1 5 2   ������,��������һ��4 1 8,������4ʱ�̿�ʼ��,�պ�8ʱ������÷�1,��������
ֻ����8ʱ����ʱ,9ʱ������÷�5,�ܵ÷�6,��������Ҫ9ʱ����ܵ÷�6,��ʵ���������
������,��1ʱ�̿�ʼ��,2ʱ�������3ʱ����4ʱ������,֮��������4ʱ������һ��,8ʱ��
����,���ܵ÷�6,������Ϊÿ�����l[i]��Ӱ��dp[j-t[i]]���������ѡȡ,���������һ��,
��ôj-t[i]��Сֻ���4ʱ�̿�ʼ,Ҳ����dp[0..4]��û��ֵ,��˾ͻ�Ӱ�����������������
j-t[i]ֻ�иպ�ѡ��8ʱ�̿�ʼ���������÷�.
�������˳���Ӱ�쵽���յĽ��,���Ǿ���Ҫ����l-t������˳���������.

�ܽ�:ʵ��������Ҫ�������,�����޷�ֱ�ӿ�����Ҫ����ʲô��������,���������������01����
��������,һ�������𰸻����,�ٷ����������������,ȥ���� �����ĳ��ѡȡ��˳��ı����Ƿ�
���ܶ�,��ȥ������˳��ĸı��ǻ���ʲô����ı��.
˵��:"zhx is naive!"�����,//����涨ʱ��Ӧ�þ���ָsum��l�����ֵ,Ҫ��Ȼ,ʵ��ʱ�����������,
//ֻҪ������Ŀ�ĵ÷ִ���m,��һ���ܰ�������Ŀ����,��������Ŀ�����ϻ�����һ��©��.
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
        memset(dp,0,sizeof(dp));//�����Ǿ����ܶ��װ��,ÿ���⿪ʼʱ��ſ��Բ���β���������һ��
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&pro[i].t,&pro[i].v,&pro[i].l);
            sum+=pro[i].t;//sum��ʾ�����������ʱ��
            l=max(l,pro[i].l);//����������ǰ����������ʱ������
        }
        sum=max(sum,l);//��ȡ���ֵ,������1 ֻ��1��,����ʱ����1,��l[i]=7,ʵ����������ʱ����7,���ȡ1��7���ֵ7��Ϊ��������
        sort(pro+1,pro+1+n);
        for(int i=1;i<=n;i++){
            int tp=max(pro[i].t,pro[i].l);//ȡ���ֵ ��֤j-pro[i].t>=0 �����±겻Ϊ��
            for(int j=sum;j>=tp;j--)//j>=pro[i].l,����ʵ������ʱ���>=pro[i].l
                dp[j]=max(dp[j],dp[j-pro[i].t]+pro[i].v);
        }
        /*
        for(int i=1;i<=n;i++){
            int tp=max(pro[i].t,pro[i].l);
            for(int j=sum;j>=pro[i].l;j--)//j>=pro[i].l,����ʵ������ʱ���>=pro[i].l
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
        //����涨ʱ��Ӧ�þ���ָsum��l�����ֵ,Ҫ��Ȼ,ʵ��ʱ�����������,
        //ֻҪ������Ŀ�ĵ÷ִ���m,��һ���ܰ�������Ŀ����,��������Ŀ�����ϻ�����һ��©��.
        if(!flag)//�涨ʱ���ڲ��ܻ��m��
            printf("zhx is naive!\n");
    }
    return 0;
}

/*
//ac 15ms ������Сʱ��+dfs��֤
//�ο�����:https://blog.csdn.net/weixin_30510153/article/details/98550997
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
     if(va+sum[p]<w) return 0;   //�������ʣ�µļ�ֵ��С��w
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
         int l=0,r=100000*n;  //�����ʱ
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
//ac 31ms ������Сʱ��+dfs��֤
//�ο�����:https://blog.csdn.net/u011663071/article/details/44307273
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
//���Լ�д�Ķ�����Сʱ��+dfs��֤
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
