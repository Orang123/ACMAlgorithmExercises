/*
����:ժ������
����L��ľ����ÿ��1cm����ʼ����ɫ��Ϊ1������T����ɫ������O��������
C l r c ��l��r�ڵ�ľ��������ɫ����Ϊx �� P l r ����l��r���ж�������ɫ��
L<=10^5,T<=30,O<=10^5.
����:http://poj.org/problem?id=2777
˼·:�߶�������Ⱦɫ�����޸� ������,����������ZOJ 1610,
ZOJ 1610������Ⱦɫ,Ⱦɫ�Ƕ����������,��POJ 2777���������
�ڵĵ����Ⱦɫ����,�߶�������POJ 2777���������,���Ƕ��������
��ȾɫZOJ 1610��һ�����������,��������ĳЩ����.
*/
//ac 469ms �߶�������Ⱦɫ�����޸� ������
#include<cstdio>
#include<cstring>
#define N 100010

int sum[N<<2],L,T,O,vis[31],cnt;

void pushup(int rt){
    if(sum[rt<<1] == sum[rt<<1|1])//������ɫ��ͬʱ,���ڵ��������Ϊ��������ɫ
        sum[rt]=sum[rt<<1];
    else//���򸸽ڵ��������Ϊ-1
        sum[rt]=-1;
}

void pushdown(int rt){
    if(sum[rt]!=-1){
        sum[rt<<1]=sum[rt<<1|1]=sum[rt];
        //sum[rt]=-1;���������Ǹ��ڵ���ɫΪ-1,��Ϊpushupʱ �����sum[rt]
    }
}

void build(int rt,int l,int r){
    if(l == r){
        sum[rt]=1;//��ʼ��ɫ��1
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

void update(int l,int r,int rt,int curl,int curr,int c){
    if(l<=curl && curr<=r){
        sum[rt]=c;
        return;
    }
    pushdown(rt);//��Ҫ������������,��Ϊrt���ڵ���ɫ���ӽڵ�����Ѿ���һ����
    int mid=(curl+curr)/2;
    if(l<=mid)
        update(l,r,rt<<1,curl,mid,c);
    if(r>mid)
        update(l,r,rt<<1|1,mid+1,curr,c);
    pushup(rt);
}

void query(int l,int r,int rt,int curl,int curr){
    //��ѯ��ɫ,��Ϊ��ʼ��ɫ����1,�ڲ��ҹ�����һ��������sum[rt]����ɫ�����,�������������Ҷ�ӽڵ㻹�������������.
    if(sum[rt]!=-1){
        if(!vis[sum[rt]]){
            vis[sum[rt]]=1;
            cnt++;//[l,r]�����ڲ�ͬ��ɫ��+1
        }
        return;
    }
    //if(l == r) return;//��Ϊ��ʼ��ɫ����1,�������Ҷ�ӽڵ� sum[rt]== -1�����
    //������������������,��ΪֻҪ���ڵ�����ɫ,�ͻ�ֱ��ͳ��������ɫ,������������������
    int mid=(curl+curr)/2;
    if(l<=mid)
        query(l,r,rt<<1,curl,mid);
    if(r>mid)
        query(l,r,rt<<1|1,mid+1,curr);
}

int main(){
    int l,r,c;
    char p;
    scanf("%d%d%d",&L,&T,&O);
    build(1,1,L);
    while(O--){
        scanf(" %c",&p);
        if(p == 'C'){
            scanf("%d%d%d",&l,&r,&c);
            update(l,r,1,1,L,c);
        }
        else{
            scanf("%d%d",&l,&r);
            memset(vis,0,sizeof(vis));
            cnt=0;
            query(l,r,1,1,L);
            printf("%d\n",cnt);
        }
    }
    return 0;
}

/*
//ac 438ms ������״ѹ��ѯ����[l,r]�ڵ���ɫ
//ժ�Բ���:https://blog.csdn.net/winddreams/article/details/38375799
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
#define maxn 110000
#define lmin 1
#define rmax n
#define lson l,(l+r)/2,rt<<1
#define rson (l+r)/2+1,r,rt<<1|1
#define root lmin,rmax,1
#define now l,r,rt
#define int_now int l,int r,int rt
#define INF 0x3f3f3f3f
#define eqs 1e-6
#define LL __int64
#define mod 10007
#define zero(x) ( fabs(x) < eqs ? 0 : x )
#define mem(a,b) (memset(a),b,sizeof(a))
int cl[maxn<<2] ;
int lazy[maxn<<2] ;
void push_up(int_now)
{
    cl[rt] = cl[rt<<1] | cl[rt<<1|1] ;
}
void push_down(int_now)
{
    if( lazy[rt] )
    {
        lazy[rt<<1] = lazy[rt<<1|1] = lazy[rt] ;
        cl[rt<<1] = cl[rt<<1|1] = lazy[rt] ;
        lazy[rt] = 0 ;
    }
}
void creat(int_now)
{
    cl[rt] = lazy[rt] = 0 ;
    if( l != r )
    {
        creat(lson);
        creat(rson);
        push_up(now);
    }
    else
        cl[rt] = 1 ;
}
void update(int ll,int rr,int x,int_now)
{
    if( ll > r || rr < l )
        return ;
    if( ll <= l && r <= rr )
    {
        cl[rt] = lazy[rt] = 1<<(x-1);
        return ;
    }
    push_down(now);
    update(ll,rr,x,lson);
    update(ll,rr,x,rson);
    push_up(now);
}
int query(int ll,int rr,int_now)
{
    if(ll > r || rr < l)
        return 0;
    if(ll <= l && r <= rr)
        return cl[rt] ;
    push_down(now);
    return query(ll,rr,lson) | query(ll,rr,rson);
}
int ans(int x)
{
    int aa = 0 ;
    while(x)
    {
        if(x & 1)
            aa++ ;
        x >>= 1 ;
    }
    return aa ;
}
int main()
{
    int n , ls , m ;
    int l , r , x ;
    char str[10] ;
    while(~scanf("%d %d %d", &n, &ls, &m))
    {
        creat(root);
        while(m--)
        {
            scanf("%s", str);
            if(str[0] == 'C')
            {
                scanf("%d %d %d", &l, &r, &x);
                if(l > r)
                    swap(l,r);
                update(l,r,x,root);
            }
            else
            {
                scanf("%d %d", &l, &r);
                if(l > r)
                    swap(l,r);
                printf("%d\n",ans( query(l,r,root) ) );
            }
        }
    }
    return 0;
}
*/
