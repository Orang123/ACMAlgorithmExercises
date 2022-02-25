/*
����:����N����Ai(i=1..n)��Q�����(N��Q<=100000)
����������
Q x y ��ʾ��ѯsum(Ai) (i=x..y)
C x y d ��ʾ Ai += d (i=x..y)
����:http://poj.org/problem?id=3468
˼·:�߶����������������
�߶���������¡������ѯ�ο�����:
https://blog.csdn.net/henulmh/article/details/98756541
https://blog.csdn.net/charles1e/article/details/53363144
������
��ǵĺ��壺�������Ѿ������¹��ˣ�����������ȴû�б����¹���
�����µ���Ϣ��ʲô,���ľ������ǿ���ֱ���޸�һ���������ֵ��
������Ҫ�޸������ӽڵ㣬��������Ҫ����������ӽڵ���Ϣ��ʱ��
���´��������ǲ��޸�����ӽڵ�.

���������������,���������ָ����ĳ�������ڵ�Ҷ�ӽڵ��ֵ��
��Ϊ�漰����Ҷ�ӽڵ㲻ֹһ������Ҷ�ӽڵ��Ӱ������Ӧ�ķ�Ҷ���ڵ㣬
��ô������Ҫ���µķ�Ҷ�ӽڵ�Ҳ���кܶ࣬���һ���Ը����꣬������ʱ��
���Ӷȿ϶�����O(lgn)�����統����Ҫ��������[0,3]�ڵ�Ҷ�ӽڵ�ʱ����Ҫ����
����Ҷ�ӽڵ�3,9������������ڵ㡣Ϊ���������߶����е��ӳٱ�Ǹ����Ҳ���߶����ľ������ڡ�

�ӳٱ�ǣ�ÿ���ڵ�������һ����ǣ���¼����ڵ��Ƿ������ĳ���޸�(�����޸Ĳ�����Ӱ�����ӽڵ�)��
��������������޸ģ������Ȱ��������ѯ�ķ�ʽ���仮�ֳ��߶����еĽڵ㣬Ȼ���޸���Щ�ڵ����Ϣ��
������Щ�ڵ����ϴ��������޸Ĳ����ı�ǡ����޸ĺͲ�ѯ��ʱ��������ǵ���һ���ڵ�p�����Ҿ���
�������ӽڵ㣬��ô���Ǿ�Ҫ���ڵ�p�Ƿ񱻱�ǣ�����У���Ҫ���ձ���޸����ӽڵ����Ϣ�����Ҹ���
�ڵ㶼������ͬ�ı�ǣ�ͬʱ�����ڵ�p�ı�ǡ�
*/
//ac 2657ms �߶����������������
#include<cstdio>
#define N 100010
typedef long long ll;

int n,q;
struct Node{
    int l,r;
    ll sum,lazy;
}segTree[N<<2];

void pushup(int rt){
    segTree[rt].sum=segTree[rt<<1].sum+segTree[rt<<1|1].sum;
}

//O(nlog(n))
void build(int rt,int l,int r){
    segTree[rt].l=l,segTree[rt].r=r;
    if(l == r){
        scanf("%lld",&segTree[rt].sum);
        segTree[rt].lazy=0;
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

void pushdown(int rt){//O(1)����ʱ��
    if(segTree[rt].lazy){//֮ǰ�ĸ��ڵ㱻�޸Ĺ�,��Ҫ�����µ���ֵ�������䴫��
        segTree[rt<<1].lazy+=segTree[rt].lazy;//������������lazy
        segTree[rt<<1].sum+=segTree[rt].lazy*(segTree[rt<<1].r-segTree[rt<<1].l+1);
        segTree[rt<<1|1].lazy+=segTree[rt].lazy;//�Ҷ����������lazy
        segTree[rt<<1|1].sum+=segTree[rt].lazy*(segTree[rt<<1|1].r-segTree[rt<<1|1].l+1);
        segTree[rt].lazy=0;//���ڵ����������,���ٸ���
    }
}

//���������ǵ�������¸��Ӷ�Ϊ O((r-l+1)*log(n)),[l,r]ΪҪ�޸ĵ�����,(r-l+1)ʵ�ʾ���Ҫ�޸ĵ�Ҷ�ӽڵ�ĸ���.
//�����������ǲ��������ȫ�����ݹ鵽���е�Ҷ�ӽڵ�,�ʶ�ʱ�併��.
void update(int rt,int l,int r,ll x){//O(log(n))
    if(l<=segTree[rt].l && segTree[rt].r<=r){//��ǰ�����ڴ��������䷶Χ��
        //�����������������Ԫ�ض�����,���µ�Ԫ�ظ���Ϊ(segTree[rt].r-segTree[rt].l+1),������ֵΪx
        segTree[rt].sum+=(segTree[rt].r-segTree[rt].l+1)*x;
        segTree[rt].lazy+=x;// ����Ҫ���»��ѯ������������ʱ ��lazy��¼����ֵ����������
        return;
    }
    pushdown(rt);//��Ҫ�ж�������ʱ,�жϵ�ǰ����rt֮ǰ�Ƿ���¹�,������¹�����lazy��û���´���,����lazy[rt]����������
    int mid=(segTree[rt].l+segTree[rt].r)/2;
    if(l<=mid)
        update(rt<<1,l,r,x);
    if(r>mid)
        update(rt<<1|1,l,r,x);
    pushup(rt);
}

ll query(int rt,int l,int r){//O(log(n))
    if(l<=segTree[rt].l && segTree[rt].r<=r)
        return segTree[rt].sum;
    pushdown(rt);//��ǰ����rt������¹�,��ѯʱ��������仹δ����֮ǰ������rt��lazy���,���ȸ���
    int mid=(segTree[rt].l+segTree[rt].r)/2;
    ll res=0;
    if(l<=mid)
        res+=query(rt<<1,l,r);
    if(r>mid)
        res+=query(rt<<1|1,l,r);
    return res;
}

int main(){
    int a,b;
    ll c;
    char p;
    scanf("%d%d",&n,&q);
    build(1,1,n);
    while(q--){
        scanf(" %c",&p);
        if(p == 'C'){
            scanf("%d%d%lld",&a,&b,&c);
            update(1,a,b,c);
        }
        else{
            scanf("%d%d",&a,&b);
            printf("%lld\n",query(1,a,b));
        }
    }
    return 0;
}

/*
//ac 2860ms �߶���������������Ǿ����
#include<cstdio>
#define N 100010
typedef long long ll;

int n,q;
ll sum[N<<2],lazy[N<<2];

void pushdown(int rt,int l,int r){
    if(lazy[rt]){
    	int mid=(l+r)/2;
        lazy[rt<<1]+=lazy[rt];
        sum[rt<<1]+=lazy[rt]*(mid-l+1);
        lazy[rt<<1|1]+=lazy[rt];
        sum[rt<<1|1]+=lazy[rt]*(r-mid);
        lazy[rt]=0;
    }
}

void update(int l,int r,int rt,int curl,int curr,ll x){
    if(l<=curl && curr<=r){
        sum[rt]+=(curr-curl+1)*x;
        lazy[rt]+=x;
        return;
    }
    pushdown(rt,curl,curr);
    int mid=(curl+curr)/2;
    if(l<=mid)
        update(l,r,rt<<1,curl,mid,x);
    if(r>mid)
        update(l,r,rt<<1|1,mid+1,curr,x);
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

ll query(int l,int r,int rt,int curl,int curr){
    if(l<=curl && curr<=r)
        return sum[rt];
    pushdown(rt,curl,curr);
    int mid=(curl+curr)/2;
    ll res=0;
    if(l<=mid)
        res+=query(l,r,rt<<1,curl,mid);
    if(r>mid)
        res+=query(l,r,rt<<1|1,mid+1,curr);
    return res;
}

int main(){
    int a,b;
    ll c,x;
    char p;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
    	scanf("%lld",&x);
    	update(i,i,1,1,n,x);
	}
    while(q--){
        scanf(" %c",&p);
        if(p == 'C'){
            scanf("%d%d%lld",&a,&b,&c);
            update(a,b,1,1,n,c);
        }
        else{
            scanf("%d%d",&a,&b);
            printf("%lld\n",query(a,b,1,1,n));
        }
    }
    return 0;
}
*/

/*
//ac 1728ms ��״�������� ��ʱû������������
//ժ�Բ���:https://www.cnblogs.com/Newdawn/p/4197324.html
//���ص���״�����޸����� ʱ�临�Ӷ�Ϊ(r-l+1)*log(N),ʵ���������ڵ�ÿ���� �����е����޸�,���ʵ������ܴ� ��������q�ܶ�,������Ӷ�q*(r-l+1)*log(N) ����ƽ�����Ӷ�
#include<cstdio>
#include<cstring>
#define lowbit(x) ((x)&-(x))
typedef long long LL;
const int maxn= 100003;
LL org[maxn+3];

struct tree{
    LL c[maxn+3];
    void clear() {    memset(c,0,sizeof(c));    }
    LL sum(int x) const {
        LL res= 0;
        while(x){
            res+= c[x];
            x-= lowbit(x);
        }
        return res;
    }
    void add(int x, LL d){
        while(x<=maxn){
            c[x]+= d;
            x+= lowbit(x);
        }
    }
} d1,d2;

inline LL sum(int x) {
    return org[x]+(x+1)*d1.sum(x)-d2.sum(x);
}

int main(){
    int n,q,a,b;
    LL x,c;
    while(~scanf("%d%d",&n,&q)){
        memset(org,0,sizeof(org));
        d1.clear();
        d2.clear();
        for(int i=1; i<=n; ++i){
            scanf("%lld",&x);
            org[i]= org[i-1]+x;
        }
        while(q--){
            getchar();
            if(getchar()=='Q'){
                scanf("%d%d",&a,&b);
                printf("%lld\n",sum(b)-sum(a-1));
            }
            else {
                scanf("%d%d%lld",&a,&b,&c);
                d1.add(a,c);
                d1.add(b+1,-c);
                d2.add(a,c*a);
                d2.add(b+1,-c*(b+1));
            }
        }
    }
    return 0;
}
*/
