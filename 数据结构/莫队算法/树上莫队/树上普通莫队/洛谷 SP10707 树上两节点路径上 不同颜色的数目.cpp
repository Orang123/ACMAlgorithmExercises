#include<cstdio>
#include<ctype.h>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 40100
#define M 100100
using namespace std;
/*
此题已过,问题在pos数组大小应该是2*N,一般报wa,考虑是不是RE 数组没开够的问题.
此题求解树上两节点路径之间出现的颜色种类个数,路径之间节点的遍历序号需要通过
dfs遍历得到其欧拉序(括号序列)来表示转换,重复出现的点(出现两次)实际并不在两点之间的路径中,
再根据其lca与两点欧拉序的关系特判lca是否在两点之间的路径中,之后再按照普通莫队区间转移
统计颜色出现次数即可.这里lca采用倍增法求解.

这个欧拉序:因为某个子树的遍历序列会被其父节点在左右两侧包住,类似被括号括起来,所以得名括号序列

为什么出现两次的点不统计答案
树上路径的定义为：从x到y经过节点个数最少的路径.
若一个点k出现两次，说明我们可以先访问k，进入k的子树中，然后出来，再到y，很显然不访问k是更优的。因此出现两次的点不能统计入答案
*/

/*
b[N<<1]是dfs遍历得到的欧拉序(括号序列),因为每次遍历会分别在st、ed数组记录一次所以需要2*N的空间开销
st[u]是第一次遍历u点时的欧拉序号下标,这里的u对应的是实际输入数据的区间下标
ed[u]是u点和u点子树遍历完毕,准备回溯时,对应的欧拉序列.
used[u]是用来对欧拉序中的重复点序列统计出现颜色相异或将其抵消掉(一次add,一次sub)
tmp[N]是用来离散化a[N]颜色种类数组,这题颜色的权值有点大,不离散化会数组越界RE
*/
/*这里pos[N<<1]数组开销一定是2*N,因为分块是对欧拉序b数组分块,这个数组越界RE错误spoj给报的WA,看了好久不知道哪错了*/
int head[N],fa[N][20],dep[N],b[N<<1],st[N],ed[N],num,lg[N],used[N],a[N],tmp[N],pos[N<<1],cnt[N],ans[M],res,k;

struct Node{
    int to,next;
    Node(){}
    Node(int to,int next):to(to),next(next){}
}edge[N<<1];

struct seq{
    int l,r,lca,id;
    seq(){}
    seq(int l,int r,int lca,int id):l(l),r(r),lca(lca),id(id){}
    bool operator < (const seq &x)const{
        return pos[l]^pos[x.l]?l<x.l:(pos[l]&1?r<x.r:r>x.r);
    }
}q[M];

inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void init(int n){
    memset(head,-1,sizeof(head));
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
}

/*
离散化:通俗地讲就是当有些数据因为本身很大或者类型不支持，自身无法作为数组的下标来方便地处理，
而影响最终结果的只有元素之间的相对大小关系时，我们可以将原来的数据按照从大到小编号来处理问题，即离散化。

因为颜色种类的编号值过大,导致cnt数组下标空间开销无法满足会越界,
所以a数组需要离散化处理,就是将一个数值之间相差比较大的数组
即类似max - 次max > 1的数组转化成max - 次max = 1的数组，
也就是当数组中数的数值对算法影响不大，但是大小关系影响较大的时候，
我们把他们的大小关系用相差1的数表示。

a数组： 99 55 68 47 100 2888888888
离散化后得b数组
b数组： 4 2 3 1 5 6
可以看出数值范围就小了许多但是对应下标的各项大小关系是不变的。
*/
void discretization(int n){
    sort(tmp+1,tmp+1+n);
    /*
    就是不同的留下，相同的消失，该函数会去掉数组中重复出现的数值，只留下第一次出现的数值。
    unique需要在数组有序的情况下使用
    */
    int len=unique(tmp+1,tmp+1+n)-tmp-1;
    /*
    lower_bound是二分查找 upper_bound是大于(没有等于)
    lower_bound会返回查询数组(tmp)中第一个大于等于查询数值(a[i])的位置的数组下标
    */
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(tmp+1,tmp+1+len,a[i])-tmp;
}

//linux下代码里不能有index,否则编译会报错. edge[index]
void addEdge(int from,int to){
    edge[k]=Node(to,head[from]);
    head[from]=k++;
    edge[k]=Node(from,head[to]);
    head[to]=k++;
}

void dfs(int u){
    st[u]=++num;//st记录刚开始遍历u点时的欧拉序列下标
    b[num]=u;//同时将u记录欧拉序中
    for(int i=1;i<=lg[dep[u]];i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa[u][0]){
            fa[v][0]=u;
            dep[v]=dep[u]+1;
            dfs(v);
        }
    }
    ed[u]=++num;//ed记录u点及其子树遍历完毕后的欧拉序列下标
    b[num]=u;
}

int lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y])
        x=fa[x][lg[dep[x]-dep[y]]];
    if(x == y) return x;
    for(int i=lg[dep[x]];i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

void add(int x){
    if(!cnt[x]++) res++;
}

void sub(int x){
    if(!--cnt[x]) res--;
}

void calc(int x){
    if(!used[x]) add(a[x]);//used[x]=0时代表欧拉序列中第一次统计该颜色时,代表这个节点出现过,统计其颜色出现次数
    /*
    used[x]=1时代表欧拉序列中这个颜色的下标出现了两次,那么实际路径中并不包括该点,
    所以将之前累加的颜色再减掉抵消掉.
    */
    else sub(a[x]);
    used[x]^=1;//将used[x]与1异或,就由0变为了1,第二次出现计算时,就会调用sub将之前出现的次数减掉,刚好抵消掉,然后used[x]再异或就变为0方便下次add增加次数
}

int main(){
    int n,m,u,v,siz,_lca;
    n=read(),m=read();
    init(n);
    for(int i=1;i<=n;i++)
        a[i]=tmp[i]=read();
    discretization(n);
    for(int i=1;i<=n-1;i++){
        u=read(),v=read();
        addEdge(u,v);
    }
    dfs(1);//这题 以哪个结点为根节点 并不影响树上量路径包含的节点颜色类型
    siz=sqrt(num);//siz块大小 是括号序列的平方根,因为每条询问的l、r记录的是括号序列的下标
    for(int i=1;i<=num;i++)
        pos[i]=(i-1)/siz+1;
    for(int i=1;i<=m;i++){
        u=read(),v=read();
        _lca=lca(u,v);//求解两点颜色下标的lca
        if(st[u]>st[v]) swap(u,v);//u点永远表示欧拉序列中较早遍历的节点
        /*
        若u不是lca,则说明u、v两点分布在lca的两侧,那么欧拉序两点之中除过重复序列,
        刚好少算了lca节点,则需要记录两点之间的路径包括lca.
        而且这条询问区间的l端点所记录的应为u点在欧拉序回溯时的结束下标序号,因为若记录st开始序号,
        则会将u点之后的子树中的节点序号也记录进去,而实际这些点并不在树上两点之间的路径上.
        */
        if(_lca != u) q[i]=seq(ed[u],st[v],_lca,i);
        /*
        若u是lca,则说明v就在u的子树上,那么欧拉序里ed[v]在ed[u]左侧,
        而实际两点之间的路径只包括[st[u],st[v]]中除过出现两次的点.
        */
        else q[i]=seq(st[u],st[v],0,i);
    }
    sort(q+1,q+1+m);
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(l<q[i].l) calc(b[l++]);
        while(l>q[i].l) calc(b[--l]);
        while(r<q[i].r) calc(b[++r]);
        while(r>q[i].r) calc(b[r--]);
        if(q[i].lca) calc(q[i].lca);
        ans[q[i].id]=res;
        /*
        这里若询问中路径上还包括lca,那么每次颜色计数完了后一定要将其在res中去除,
        否则会影响下一个询问的结果,因为对于下一个询问的区间如果不包括lca那么res就多出来,
        如果下一个区间刚好包括lca这个点,那么根据used[x]的值为1,会抵消掉,
        res的值刚好减少了,res最终计算的结果会出错.
        */
        if(q[i].lca) calc(q[i].lca);//这里若询问中路径上还包括lca,那么每次颜色计数完了后一定要将其在res中去除,否则会影响下一个询问的结果,因为对于下一个询问的区间如果不包括lca那么res就多出来,如果下一个区间刚好包括lca这个点,那么根据used[x]的值为1,会抵消掉,res的值刚好减少了,res最终计算的结果都是有问题的
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return 0;
}
