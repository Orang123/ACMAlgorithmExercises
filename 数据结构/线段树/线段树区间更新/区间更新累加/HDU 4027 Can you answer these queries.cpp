/*
����:ժ������
����n���������ֲ�����0 i j��ʾ��i j��ε����ֶ������ţ�����ȡ������
1 i j��ʾ��ѯi j֮�������ֵ�ĺ͡����������еĺͶ�������64λ��..
n<=10^5.
����:https://acm.hdu.edu.cn/showproblem.php?pid=4027
˼·:��Ȼ�������޸�,�����Ƕ�������Ԫ�ؿ�����,�����޷���������,
ֻ�ܱ���������Ҷ�ӽڵ�����޸ĸ��ڵ�����,ֻ��ע���ڲ��Ͽ����Ź�����,
һ����֦�������Ѿ�Ϊ1,��û�б�Ҫ�ٿ�������.
*/
//ac 436ms �߶��������޸������ѯ
#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 100010
using namespace std;
typedef long long ll;

int n,m;
ll sum[N<<2];

void build(int rt,int l,int r){
    if(l == r){
        scanf("%lld",&sum[rt]);
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void update(int l,int r,int rt,int curl,int curr){
    //���������֦��TLE.
    if(sum[rt] == curr-curl+1)//��֦ [curl,curr]������Ԫ��ֵ��Ϊ1,��������ȻΪ1 ��˷���.
        return;
    if(curl == curr){//����Ҷ�ӽڵ� �����ŷ���
        sum[rt]=sqrt(sum[rt]);
        return;
    }
    int mid=(curl+curr)/2;
    if(l<=mid)
        update(l,r,rt<<1,curl,mid);
    if(r>mid)
        update(l,r,rt<<1|1,mid+1,curr);
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

ll query(int l,int r,int rt,int curl,int curr){
    if(l<=curl && curr<=r)
        return sum[rt];
    int mid=(curl+curr)/2;
    ll res=0;
    if(l<=mid)
        res+=query(l,r,rt<<1,curl,mid);
    if(r>mid)
        res+=query(l,r,rt<<1|1,mid+1,curr);
    return res;
}

int main(){
    int t,l,r;
    for(int cas=1;scanf("%d",&n)!=EOF;cas++){
        build(1,1,n);
        scanf("%d",&m);
        printf("Case #%d:\n",cas);
        while(m--){
            scanf("%d%d%d",&t,&l,&r);
            if(l>r)
                swap(l,r);
            if(!t)
                update(l,r,1,1,n);
            else
                printf("%lld\n",query(l,r,1,1,n));
        }
        printf("\n");
    }
    return 0;
}

/*
//ac 436ms ���²�ѯ  �ϸ��������
#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 100010
using namespace std;
typedef long long ll;

int n,m;
ll sum[N<<2];

void build(int rt,int l,int r){
    if(l == r){
        scanf("%lld",&sum[rt]);
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void update(int l,int r,int rt,int curl,int curr){
    if(sum[rt] == curr-curl+1)
        return;
    if(curl == curr){
        sum[rt]=sqrt(sum[rt]);
        return;
    }
    int mid=(curl+curr)/2;
    if(r<=mid)
        update(l,r,rt<<1,curl,mid);
    else if(l>mid)
        update(l,r,rt<<1|1,mid+1,curr);
    else{
    	update(l,mid,rt<<1,curl,mid);
    	update(mid+1,r,rt<<1|1,mid+1,curr);
	}
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

ll query(int l,int r,int rt,int curl,int curr){
    if(l == curl && r == curr)
        return sum[rt];
    int mid=(curl+curr)/2;
    if(r<=mid)
        return query(l,r,rt<<1,curl,mid);
    else if(l>mid)
        return query(l,r,rt<<1|1,mid+1,curr);
    else
        return query(l,mid,rt<<1,curl,mid)+query(mid+1,r,rt<<1|1,mid+1,curr);
}

int main(){
    int t,l,r;
    for(int cas=1;scanf("%d",&n)!=EOF;cas++){
        build(1,1,n);
        scanf("%d",&m);
        printf("Case #%d:\n",cas);
        while(m--){
            scanf("%d%d%d",&t,&l,&r);
            if(l>r)
                swap(l,r);
            if(!t)
                update(l,r,1,1,n);
            else
                printf("%lld\n",query(l,r,1,1,n));
        }
        printf("\n");
    }
    return 0;
}
*/
