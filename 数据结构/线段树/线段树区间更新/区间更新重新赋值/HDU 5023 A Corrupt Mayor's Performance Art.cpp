/*
题意:摘自网上
有最多30种颜色，一个长度为n的墙。一开始所有墙的颜色都是2。
两种操作：
P l r x ：把区间[l,r]中所有的墙的颜色都改为x
Q l r ：询问[l,r]里面的颜色，把颜色升序输出
链接:https://acm.hdu.edu.cn/showproblem.php?pid=5023
思路:线段树区间更新染色
*/
//ac 187ms 线段树区间更新染色
#include<cstdio>
#include<cstring>
#define N 1000010

int n,m,sum[N<<2],vis[31];

void pushup(int rt){
    if(sum[rt<<1] == sum[rt<<1|1])
        sum[rt]=sum[rt<<1];
    else
        sum[rt]=-1;
}

void pushdown(int rt){
    if(sum[rt]!=-1){
        sum[rt<<1]=sum[rt<<1|1]=sum[rt];
        sum[rt]=-1;
    }
}

void build(int rt,int l,int r){
    if(l == r){
        sum[rt]=2;
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

void update(int l,int r,int c,int rt,int curl,int curr){
    if(l<=curl && curr<=r){
        sum[rt]=c;
        return;
    }
    pushdown(rt);
    int mid=(curl+curr)/2;
    if(l<=mid)
        update(l,r,c,rt<<1,curl,mid);
    if(r>mid)
        update(l,r,c,rt<<1|1,mid+1,curr);
}

void query(int l,int r,int rt,int curl,int curr){
    if(sum[rt]!=-1){
        vis[sum[rt]]=1;
        return;
    }
    int mid=(curl+curr)/2;
    if(l<=mid)
        query(l,r,rt<<1,curl,mid);
    if(r>mid)
        query(l,r,rt<<1|1,mid+1,curr);
}

int main(){
    char p;
    int a,b,c;
    while(scanf("%d%d",&n,&m) && n+m){
        build(1,1,n);
        while(m--){
            scanf(" %c",&p);
            if(p == 'P'){
                scanf("%d%d%d",&a,&b,&c);
                update(a,b,c,1,1,n);
            }
            else{
                scanf("%d%d",&a,&b);
                memset(vis,0,sizeof(vis));
                query(a,b,1,1,n);
                int flag=0;
                for(int i=1;i<=30;i++){
                    if(vis[i]){
                        if(!flag){
                            printf("%d",i);
                            flag=1;
                        }
                        else
                            printf(" %d",i);
                    }
                }
                printf("\n");
            }
        }
    }
    return 0;
}
