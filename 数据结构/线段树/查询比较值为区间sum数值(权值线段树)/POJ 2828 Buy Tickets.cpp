/*
题意:摘自网上
插队的问题，每个案例给出n，代表有n个插队的，每个给出pos,val，
意思是代号为val的人前面有pos个人，问最后的队伍的排列?
n<=200000
链接:http://poj.org/problem?id=2828
思路:线段树单点更新.
因为最后一个人选定的位置一定是不会被改变的,因此要倒着插入节点.
注意插入时pos值要加1,因为前面有pos个人,实际要插在pos+1的位置.
*/
//ac 3594ms 线段树单点更新
#include<cstdio>
#define N 200010

//sum[rt]表示线段树当前位置之前还有多少空位
int n,sum[N<<2],ans[N],pos[N],val[N];

void pushup(int rt){
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}

void build(int rt,int l,int r){
    if(l == r){
        sum[rt]=1;
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

void update(int p,int rt,int l,int r,int c){
    if(l == r){
        sum[rt]=0;
        ans[l]=c;
        return;
    }
    int mid=(l+r)/2;
    if(p<=sum[rt<<1])//空位个数左子树不少于p个,搜索左子树
        update(p,rt<<1,l,mid,c);
    else//空位个数左子树少于p个,搜索右子树,并且实际确定的空位数为p-sum[rt<<1]
        update(p-sum[rt<<1],rt<<1|1,mid+1,r,c);
    pushup(rt);
}

int main(){
    while(scanf("%d",&n)!=EOF){
        build(1,1,n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&pos[i],&val[i]);
            //插入时pos值要加1,因为前面有pos个人,实际要插在pos+1的位置.
            pos[i]++;
        }
        for(int i=n;i>=1;i--)
            update(pos[i],1,1,n,val[i]);
        for(int i=1;i<n;i++)
            printf("%d ",ans[i]);
        printf("%d\n",ans[n]);
    }
    return 0;
}
