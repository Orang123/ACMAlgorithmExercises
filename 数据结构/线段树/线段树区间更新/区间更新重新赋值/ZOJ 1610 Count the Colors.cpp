/*
题意:摘自网上
有n次操作，每次都是对一根线中的一段区间进行染色（颜色并不相同），
有时候后面的颜色有可能覆盖前面的颜色，问最后涂完色，能看到的颜色有几种，
每种颜色能被分成不连续的段数.
链接:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827365109
思路:线段树区间更新,每次更新直接重新赋值.统计颜色不同颜色时遍历
按照优先遍历左子树遍历整个线段树,这样得到的序列刚好就是原始递增的序列,
对于sum[rt]!=-1 表示已经染色,比较和之前左端的颜色是否相同,不相同则统计
颜色计数+1.
*/
//ac 22ms
//这个题的第一个样例有问题,如果按照单点染色,结果只有2种颜色,只有按线段染色才是3种颜色
//区间线段染色,而不是对点染色,严格来讲 线段树解决这类问题 部分区间线段染色的情况 无法在线段树上表示
#include<cstdio>
#include<cstring>
#define N 8100
#define maxn 8000

int n,sum[N<<2],tp,cnt[N];

void pushup(int rt){
    if(sum[rt<<1] == sum[rt<<1|1])//子树颜色相同时,父节点整体更新为子树的颜色
        sum[rt]=sum[rt<<1];
    else//否则父节点大区间标记为-1
        sum[rt]=-1;
}

void pushdown(int rt){
    if(sum[rt]!=-1){
        sum[rt<<1]=sum[rt<<1|1]=sum[rt];
        sum[rt]=-1;
    }
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
    pushup(rt);
}

//查询时无需懒惰标记下推
void query(int rt,int l,int r){
    //结束条件是当前区间已经染色 或 到达叶子节点
    if(sum[rt]!=-1 || l == r){
        if(sum[rt]!=tp && sum[rt]!=-1)//和之前颜色不同,并且当前区间已染色(sum[rt]!=-1)
            cnt[sum[rt]]++;
        tp=sum[rt];//记录上一次颜色为当前区间颜色,可能为-1 没染色.
        return;
    }
    int mid=(l+r)/2;
    query(rt<<1,l,mid);
    query(rt<<1|1,mid+1,r);
}

int main(){
    int x1,x2,c,siz;
    while(scanf("%d",&n)!=EOF){
        memset(sum,-1,sizeof(sum));
        memset(cnt,0,sizeof(cnt));
        tp=-1;
        siz=0;
        while(n--){
            scanf("%d%d%d",&x1,&x2,&c);
            if(siz<c)
                siz=c;
            //x1+1  这样才能使得第一个样例统计到[2,3]本身左右子树之间的间隔颜色
            //这个线段树区间更新染色的问题,本身就有缺陷,某些区间可能刚好左右子树之间长度为1[mid,mid+1]会被遗漏
            update(x1+1,x2,c,1,1,maxn);
        }
        query(1,1,maxn);
        for(int i=0;i<=siz;i++){
            if(cnt[i])
                printf("%d %d\n",i,cnt[i]);
        }
        printf("\n");
    }
    return 0;
}
