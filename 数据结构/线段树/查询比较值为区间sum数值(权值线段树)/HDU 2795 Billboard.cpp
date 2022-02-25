/*
题意:摘自网上
一块h*w的广告板上贴广告，每条广告均为1*wi；
如果能贴，输出贴的位置（即第几行，位置尽量靠上，靠左）；否则输出-1.
h,w<=10^9,n<=2*10^5.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2795
思路:将h作为线段树的区间标号,w的最大值作为区间的最大值,构建线段树,
查询时因为要尽量放置在靠上的位置,因此优先比较左子树的最大宽度是否能放下,
不能放下再递归遍历右子树.
*/
//ac 2230ms 线段树单点查询
#include<cstdio>
#include<algorithm>
#define N 200010
using namespace std;

int h,w,n,sum[N<<2];

void pushup(int rt){
    sum[rt]=max(sum[rt<<1],sum[rt<<1|1]);
}

void build(int rt,int l,int r){
    if(l == r){
        sum[rt]=w;
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

int query(int rt,int l,int r,int c){
    if(l == r){
        sum[rt]-=c;
        return l;
    }
    int mid=(l+r)/2,res;
    if(c<=sum[rt<<1])
        res=query(rt<<1,l,mid,c);
    else
        res=query(rt<<1|1,mid+1,r,c);
    pushup(rt);
    return res;
}

int main(){
    int x;
    while(scanf("%d%d%d",&h,&w,&n)!=EOF){
        if(h>n)
            h=n;
        build(1,1,h);
        for(int i=1;i<=n;i++){
            scanf("%d",&x);
            if(x>sum[1])
                printf("-1\n");
            else
                printf("%d\n",query(1,1,h,x));
        }
    }
    return 0;
}
