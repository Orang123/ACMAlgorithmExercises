/*
题意:摘自网上
给定n个数，两种操作，0 i j表示将i j这段的数字都开根号（向下取整），
1 i j表示查询i j之间的所有值的和。。。（所有的和都不超过64位）..
n<=10^5.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=4027
思路:虽然是区间修改,但是是对区间内元素开根号,所以无法用懒惰标记,
只能暴力搜索到叶子节点回溯修改父节点区间,只是注意在不断开根号过程中,
一个剪枝如果结果已经为1,便没有必要再开根号了.
*/
//ac 436ms 线段树单点修改区间查询
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
    //不加这个剪枝会TLE.
    if(sum[rt] == curr-curl+1)//剪枝 [curl,curr]区间内元素值都为1,开根号仍然为1 因此返回.
        return;
    if(curl == curr){//到达叶子节点 开根号返回
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
//ac 436ms 更新查询  严格分三部分
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
