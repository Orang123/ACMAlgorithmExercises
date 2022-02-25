/*
题意:摘自网上
给定N个数（1 ≤ N ≤ 50,000），询问Q次（1 ≤ Q ≤ 200,000），
每次询问某一区间[l,r]内的最大值和最小值的差。
链接:http://poj.org/problem?id=3264
思路:线段树求解区间最值.也可以RMQ实现.
*/
//ac 3297ms 线段树区间最值查询
#include<cstdio>
#include<algorithm>
#define N 50010
#define INF 0x3f3f3f3f
using namespace std;

int sum1[N<<2],sum2[N<<2],n,q,minh,maxh;

void pushup(int rt){
    sum1[rt]=max(sum1[rt<<1],sum1[rt<<1|1]);
    sum2[rt]=min(sum2[rt<<1],sum2[rt<<1|1]);
}

void build(int rt,int l,int r){
    if(l == r){
        scanf("%d",&sum1[rt]);
        sum2[rt]=sum1[rt];
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

void query(int l,int r,int rt,int curl,int curr){
    if(l<=curl && curr<=r){
        maxh=max(maxh,sum1[rt]);
        minh=min(minh,sum2[rt]);
        return;
    }
    int mid=(curl+curr)/2;
    if(l<=mid)
        query(l,r,rt<<1,curl,mid);
    if(r>mid)
        query(l,r,rt<<1|1,mid+1,curr);
}

int main(){
    int l,r;
    scanf("%d%d",&n,&q);
    build(1,1,n);
    while(q--){
        scanf("%d%d",&l,&r);
        minh=INF;
        maxh=0;
        query(l,r,1,1,n);
        printf("%d\n",maxh-minh);
    }
    return 0;
}
