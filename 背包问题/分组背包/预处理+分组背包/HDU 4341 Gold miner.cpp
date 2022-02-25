/*
����:����ԭ��(0,0)ץ���,ץȡÿ������Ҫ��Ӧ��ʱ��t,�ܹ���ü�ֵv.
���ǵ�������ں�ԭ���������ͬһֱ����ʱ,����ֻ����ץ����,��ץԶ��.
����ڸ���ʱ��T��,���ܻ�õ�����ֵ.
n<=200,T<=40000.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4341
˼·:�����Ƕ������ͬһֱ����,�������������01����,����ʵ��ץȡ���
������ͬһֱ����(б����ͬ)�Ľ��,ֻ����ץ����,��ץ���ں����,���ܳ���ǰ���
ûץ,�ͰѺ����ץ��,���Խ����еĽ����б�ʷ���,����ͬһֱ���ϵĽ���Ϊ
һ����ץȡǰ1�����ǰ2�����...n�����,��:��������ڵĵ�i����Ʒ������ͼ�ֵ��
ǰi����Ʒ�������ֵ��ǰ׺��.����ʵ��ͬһֱ�߽��ץȡֻ��ץȡǰi�����,���������
����ÿ������Ʒ���ֻ��ȡһ��.
*/
//ac 124ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define M 40010
using namespace std;

int n,T,w[N][N],val[N][N],num[N],k,dp[M];

struct Node{
    int x,y,t,v;
    bool operator < (const Node &a)const{
        //���ս����ԭ��������ֱ�ߵ�б�ʷ���,ͬһֱ���ϰ�����ԭ������н���Զ����
        //��Ϊ�ø�����y/x < a.y/a/x ���ܻ���־������,���Ը���ʮ����˷��ж�
        return (y*a.x <a.y*x || (y*a.x == a.y*x && y<a.y));
    }
}node[N];

int main(){
    int cas=0;
    while(scanf("%d%d",&n,&T)!=EOF){
        cas++;
        memset(dp,0,sizeof(dp));
        memset(num,0,sizeof(num));
        k=0;
        for(int i=1;i<=n;i++)
            scanf("%d%d%d%d",&node[i].x,&node[i].y,&node[i].t,&node[i].v);
        sort(node+1,node+1+n);
        for(int i=1;i<=n;i++){
            //б����ͬ����һ��
            if(node[i].y*node[i-1].x == node[i-1].y*node[i].x && i!=1){
                num[k]++;
                w[k][num[k]]=w[k][num[k]-1]+node[i].t;//ÿ���i����Ʒ��ֱ����ǰi����Ʒ���������ֵǰ׺��
                val[k][num[k]]=val[k][num[k]-1]+node[i].v;
            }
            else{
                num[++k]++;
                w[k][num[k]]=node[i].t;
                val[k][num[k]]=node[i].v;
            }
        }
        for(int i=1;i<=k;i++){
            for(int j=T;j>=1;j--){//ÿ�����������Ҫʱ��1,���j�½���1
                for(int t=1;t<=num[i];t++){
                    if(j>=w[i][t])
                        dp[j]=max(dp[j],dp[j-w[i][t]]+val[i][t]);
                    else//ǰ׺�ͻ�Խ��Խ��,��ǰ�����j�� �ͽ���
                        break;
                }
            }
        }
        printf("Case %d: %d\n",cas,dp[T]);
    }
    return 0;
}
/*
//ac 156ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define M 40010
using namespace std;

int n,T,w[N][N],val[N][N],num[N],k,dp[M];

struct Node{
    double x,y;
    int t,v;
    bool operator < (const Node &a)const{
        return (x/y <a.x/a.y || (x/y == a.x/a.y && y<a.y));
    }
}node[N];

int main(){
    int cas=0;
    while(scanf("%d%d",&n,&T)!=EOF){
        cas++;
        memset(dp,0,sizeof(dp));
        memset(num,0,sizeof(num));
        k=0;
        for(int i=1;i<=n;i++)
            scanf("%lf%lf%d%d",&node[i].x,&node[i].y,&node[i].t,&node[i].v);
        sort(node+1,node+1+n);
        for(int i=1;i<=n;i++){
            if(node[i].x/node[i].y == node[i-1].x/node[i-1].y && i!=1){
                num[k]++;
                w[k][num[k]]=w[k][num[k]-1]+node[i].t;
                val[k][num[k]]=val[k][num[k]-1]+node[i].v;
            }
            else{
                num[++k]++;
                w[k][num[k]]=node[i].t;
                val[k][num[k]]=node[i].v;
            }
        }
        for(int i=1;i<=k;i++){
            for(int j=T;j>=1;j--){
                for(int t=1;t<=num[i];t++){
                    if(j>=w[i][t])
                        dp[j]=max(dp[j],dp[j-w[i][t]]+val[i][t]);
                    else
                        break;
                }
            }
        }
        printf("Case %d: %d\n",cas,dp[T]);
    }
    return 0;
}
*/

/*
//ac 124ms
//ת��Ϊ��������,������dfs�����01���� ���α�������
//ժ�Բ���:https://blog.csdn.net/ice_crazy/article/details/9236951
#include"iostream"
#include"cstdio"
#include"cmath"
#include"cstring"
#include"algorithm"
using namespace std;
const int N=205;
const int M=40005;

int n,m,now,pre,dp[2][M];
struct node{
    int x,y,dis2,cost,val;
}E[N];
struct Edge{
    int v,next;
}edge[N];
int tot,head[N];
void add(int a,int b){
    edge[tot].v=b;edge[tot].next=head[a];head[a]=tot++;
}

int cmp(node n1,node n2){
    return n1.dis2<n2.dis2;
}
void build()
{
    int i,l,ff;
    double k1,k2;
    tot=0;
    memset(head,-1,sizeof(head));
    for(i=0;i<n;i++)
    {
        scanf("%d%d%d%d",&E[i].x,&E[i].y,&E[i].cost,&E[i].val);
        E[i].dis2=E[i].x*E[i].x+E[i].y*E[i].y;
    }
    sort(E,E+n,cmp);
    for(i=n-1;i>=0;i--)
    {
        ff=0;
        if(!E[i].x) k1=123456;
        else        k1=1.0*E[i].y/E[i].x;
        for(l=i-1;l>=0;l--)
        {
            if(ff)    break;
            if(!E[l].x) k2=123456;
            else        k2=1.0*E[l].y/E[l].x;
            if(fabs(k1-k2)>1e-5)    continue;
            ff=1;
            add(l,i);
        }
        if(!ff) add(i,i);
    }
}
void dfs(int j,int k,int acc_val,int acc_cost)
{
    int l;
    int sum_val=acc_val+E[k].val;
    int sum_cost=acc_cost+E[k].cost;
    for(l=0;l<sum_cost;l++) dp[now][l]=dp[pre][l];
    for(;l<=m;l++)
    {
        dp[now][l]=dp[pre][l];
        if(dp[now][l] < dp[pre][l-sum_cost]+sum_val)
            dp[now][l]=dp[pre][l-sum_cost]+sum_val;
    }
    j=edge[j].next;
    if(j!=-1)   dfs(j,edge[j].v,sum_val,sum_cost);
}
void DP()
{
    int i,j;
    now=1;pre=0;
    memset(dp,0,sizeof(dp));
    for(i=0;i<n;i++)
    {
        j=head[i];
        if(j==-1) continue;
        if(edge[j].v!=i)  continue;
        now=(now+1)%2;
        pre=1-now;
        dfs(j,edge[j].v,0,0);
    }
}
int main()
{
    int Case=1;
    while(scanf("%d%d",&n,&m)!=-1)
    {
        build();
        DP();
        printf("Case %d: %d\n",Case++,dp[now][m]);
    }
    return 0;
}
*/
