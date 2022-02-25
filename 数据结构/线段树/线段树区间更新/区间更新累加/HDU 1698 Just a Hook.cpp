/*
题意:我们将钩子的连续金属棒编号从1到n。
对于每次操作，Pudge 可以将编号从X到Y的连续金属棒更改为铜棒、银棒或金棒。
钩子的总值计算为n个金属棒的值之和。更准确地说，每种棍子的值计算如下：
对于每根铜棍，数值为 1。
对于每根银棍，数值为 2。
对于每根金棍，数值为 3。
帕吉想知道执行操作后钩子的总值。
您可能会认为原始钩子是由铜棒制成的。
n<=10^5.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1698
思路:线段树区间更新懒惰标记.
*/
//ac 826ms 线段树区间更新懒惰标记
#include<cstdio>
#include<cstring>
#define N 100010

int n,q,sum[N<<2],lazy[N<<2];

void pushup(int rt){
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void pushdown(int rt,int l,int r){
    if(lazy[rt]!=-1){
        int mid=(l+r)/2;
        lazy[rt<<1]=lazy[rt<<1|1]=lazy[rt];
        sum[rt<<1]=(mid-l+1)*lazy[rt];
        sum[rt<<1|1]=(r-mid)*lazy[rt];
        lazy[rt]=-1;
    }
}

void update(int l,int r,int rt,int curl,int curr,int c){
    if(l<=curl && curr<=r){
        sum[rt]=(curr-curl+1)*c;
        lazy[rt]=c;
        return;
    }
    pushdown(rt,curl,curr);
    int mid=(curl+curr)/2;
    if(l<=mid)
        update(l,r,rt<<1,curl,mid,c);
    if(r>mid)
        update(l,r,rt<<1|1,mid+1,curr,c);
    pushup(rt);
}

int main(){
    int T,x,y,z;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++){
        memset(lazy,-1,sizeof(lazy));
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;i++)
            update(i,i,1,1,n,1);
        while(q--){
            scanf("%d%d%d",&x,&y,&z);
            update(x,y,1,1,n,z);
        }
        printf("Case %d: The total value of the hook is %d.\n",cas,sum[1]);//[1,n]的区间和就是sum[1]
    }
    return 0;
}
