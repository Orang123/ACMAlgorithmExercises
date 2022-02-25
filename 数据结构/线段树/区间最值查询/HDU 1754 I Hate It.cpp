/*
����:
�ܶ�ѧУ����һ�ֱȽϵ�ϰ�ߡ���ʦ�Ǻ�ϲ��ѯ�ʣ���ĳĳ��ĳĳ���У�
������ߵ��Ƕ��١����úܶ�ѧ���ܷ��С�
������ϲ��ϲ����������Ҫ�������ǣ����ǰ�����ʦ��Ҫ��дһ������
ģ����ʦ��ѯ�ʡ���Ȼ����ʦ��ʱ����Ҫ����ĳλͬѧ�ĳɼ���
����Ŀ����������ԣ��봦���ļ�������
��ÿ�����Եĵ�һ�У������������� N �� M ( 0<N<=200000,0<M<5000 )��
�ֱ����ѧ������Ŀ�Ͳ�������Ŀ��
ѧ��ID��ŷֱ��1�ൽN��
�ڶ��а���N��������������N��ѧ���ĳ�ʼ�ɼ������е�i��������IDΪi��ѧ���ĳɼ���
��������M�С�ÿһ����һ���ַ� C (ֻȡ'Q'��'U') ��������������A��B��
��CΪ'Q'��ʱ�򣬱�ʾ����һ��ѯ�ʲ�������ѯ��ID��A��B(����A,B)��ѧ�����У��ɼ���ߵ��Ƕ��١�
��CΪ'U'��ʱ�򣬱�ʾ����һ�����²�����Ҫ���IDΪA��ѧ���ĳɼ�����ΪB��
����:https://acm.hdu.edu.cn/showproblem.php?pid=1754
˼·:�߶����������������ֵ��ѯ.
*/
//ac 702ms �߶����������������ֵ��ѯ
#include<cstdio>
#include<algorithm>
#define N 200010
using namespace std;

int sum[N<<2],n,m;

void pushup(int rt){
    sum[rt]=max(sum[rt<<1],sum[rt<<1|1]);
}

void build(int rt,int l,int r){
    if(l == r){
        scanf("%d",&sum[rt]);
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

void update(int pos,int rt,int l,int r,int c){
    if(l == r){
        sum[rt]=c;
        return;
    }
    int mid=(l+r)/2;
    if(pos<=mid)
        update(pos,rt<<1,l,mid,c);
    else
        update(pos,rt<<1|1,mid+1,r,c);
    pushup(rt);
}

int query(int l,int r,int rt,int curl,int curr){
    if(l<=curl && curr<=r)
        return sum[rt];
    int mid=(curl+curr)/2;
    if(r<=mid)
        return query(l,r,rt<<1,curl,mid);
    else if(l>mid)
        return query(l,r,rt<<1|1,mid+1,curr);
    else
        return max(query(l,r,rt<<1,curl,mid),query(l,r,rt<<1|1,mid+1,curr));
}

int main(){
    char p;
    int a,b;
    while(scanf("%d%d",&n,&m)!=EOF){
        build(1,1,n);
        while(m--){
            scanf(" %c%d%d",&p,&a,&b);
            if(p == 'U')
                update(a,1,1,n,b);
            else
                printf("%d\n",query(a,b,1,1,n));
        }
    }
    return 0;
}
