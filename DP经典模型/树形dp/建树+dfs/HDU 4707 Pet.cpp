/*
题意:摘自网上
给出一个具有N（0<N<=100000）个节点的树（节点编号从0到N-1），
然后给出一个距离D(0<D<N),求出距离0号节点的距离大于D的节点个数。
树中相邻节点的距离为1。
链接:https://acm.hdu.edu.cn/showproblem.php?pid=4707
思路:建树+dfs
*/
//ac 405ms 计算在d距离范围内的点的个数,n-sum即是大于d的点的个数.
#include<cstdio>
#include<cstring>
#define maxn 100002
struct node{
    int to;//to是代表a这个点出发边所连接的结点,next指向下一个a结点连接的结点的下标
    int next;
}edge[maxn<<1];//树n个结点 联通无回路 有(n-1)条边对于有向树而言,现在因为是无向树,是双向的,所以边数是2(n-1),因此maxn<<1 要乘2
int head[maxn],n,d,index,sum;//head[i] 编号为i的点所连接点对应的数组下标,index表示数组当前指针

void add_edge(int from,int to){
    edge[index].to=to;
    edge[index].next=head[from];
    head[from]=index;
    index++;
}
void dfs(int u,int fa,int d0){
    if(d0 == d)
        return;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa)
            continue;
        sum++;
        dfs(v,u,d0+1);
    }
}
int main(){
    int T,a,b;
    scanf("%d",&T);
    while(T--){
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&d);
        index=0;
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);
            add_edge(a,b);//为了让dfs()从哪个点作为起点开始,结果都一样才建立双向边的,也是连通图的概念
            add_edge(b,a);
        }
        sum=1;//0号点本身不算 如个数
        dfs(0,-1,0);
        printf("%d\n",n-sum);
    }
    return 0;
}

/*
//ac 421ms 直接判断距离大于d的点的个数
#include<cstdio>
#include<cstring>
#define maxn 100002
struct node{
    int to;//to是代表a这个点出发边所连接的结点,next指向下一个a结点连接的结点的下标
    int next;
}edge[maxn<<1];//树n个结点 联通无回路 有(n-1)条边对于有向树而言,现在因为是无向树,是双向的,所以边数是2(n-1),因此maxn<<1 要乘2
int head[maxn],n,d,index,sum;//head[i] 编号为i的点所连接点对应的数组下标,index表示数组当前指针

void add_edge(int from,int to){
    edge[index].to=to;
    edge[index].next=head[from];
    head[from]=index;
    index++;
}
void dfs(int u,int fa,int d0){
    if(d0>d)
        sum++;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa)
            continue;
        dfs(edge[i].to,u,d0+1);
    }
}
int main(){
    int T,a,b;
    scanf("%d",&T);
    while(T--){
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&d);
        n--;
        index=0;
        while(n--){
            scanf("%d%d",&a,&b);
            add_edge(a,b);//为了让dfs()从哪个点作为起点开始,结果都一样才建立双向边的,也是连通图的概念
            add_edge(b,a);
        }
        sum=0;
        dfs(0,-1,0);
        printf("%d\n",sum);
    }
    return 0;
}
*/
