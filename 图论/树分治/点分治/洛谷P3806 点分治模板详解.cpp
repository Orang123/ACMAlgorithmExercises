#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 10100
#define M 110
#define limit 10000100
using namespace std;
/*
siz[u]:以u节点为根的子树节点总个数(包括u节点本身).
maxn[u]:记录u节点中各子树中节点数目最多的子树的总结点数目.
rt:记录重心,对于树上的每一个点,计算其所有子树中最大的子树节点数,这个值最小的点就是这棵树的重心.
sum:记录从根节点开始的这棵树的结点总个数.
vis:记录以哪个结点为根的子树已被分治过,做标记.
judge[dis]:判断经过重心的距离为dis的路径是否存在.
dis[u]:记录从重心到u节点的路径距离.
d[num]:记录经过重心的各个路径长度,num为其下标
ans[i]记录q[i]的询问距离点对是否存在.
*/
int head[N],cnt,siz[N],maxn[N],vis[N],sum,rt,judge[limit],q[M],dis[N],num,d[N],ans[M],m;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}
//计算重心和siz数组
void getrt(int u,int fa){
    siz[u]=1;//该根节点的个数为1
    maxn[u]=0;//因为要计算最大值 为了避免之前getrt计算出的maxn[u]保存的值有影响,初始化为最小值0
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa && !vis[v]){//vis是为了避免之前所确定得到重心也是不能作为儿子的
            getrt(v,u);
            siz[u]+=siz[v];//根节点累加各个子树节点的个数
            maxn[u]=max(maxn[u],siz[v]);//记录子树中最多的结点个数
        }
    }
    /*
    sum-siz[u]为u结点之前的祖先节点所构成的子树
    maxn[u]比较u结点之后的子树和u结点之前祖先节点所构成子树最大结点个数
    记录最大的那个
    */
    maxn[u]=max(maxn[u],sum-siz[u]);
    if(maxn[u]<maxn[rt]) rt=u;//在各个枚举的根节点中确定一个最大子树节点数最小的那个根节点作为重心
}
//统计经过重心的距离
void getdis(int u,int fa){
    /*
    题目最大只会询问10^7距离的点对,因此超过这个距离就结束返回,优化时间开销.
    若这里不设置if剪枝条件 limit需设置15000000 第七个测试点才不会RE 感觉挺奇怪的
    因为下面q[j]>=d[i]这个条件是不会数组越界的
    */
    if(dis[u]>limit) return;
    d[++num]=dis[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        /*
        同样 vis是为了避免之前所确定得到重心也是不能作为儿子的,因为以新的重心作为根节点开始遍历
        是可以遍历到之前确定过的重心的,而之前确定过的重心,经过其重心的路径已经统计过.
        */
        if(v!=fa && !vis[v]){
            dis[v]=dis[u]+edge[i].w;//更新dis[v]路径距离
            getdis(v,u);//继续深度向下遍历儿子,直到叶子节点结束遍历.
        }
    }
}
//统计询问的路径距离是否存在
void solve(int u){
    queue<int> Q;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!vis[v]){//vis同样避免之前确定的重心再度统计其经过路径 会重复统计.
            num=0;
            dis[v]=edge[i].w;
            getdis(v,u);
            /*
            枚举每个询问距离,看经过该重心的路径距离是否达到了询问距离,
            或和之前统计经过该重心的路径能连接拼成新构成的路径距离达到询问的距离
            */
            for(int i=1;i<=num;i++){
                for(int j=1;j<=m;j++)
                    /*
                    第一次遍历judge没有任何标记时,ans此刻并没标记为1,并不影响结果,
                    因为假如另一条分支经过重心的路径有q[j]-d[i]距离,转换到另一条路径时,
                    这里q[j]-d[i]就是之前的已经记录如judge的'd[i]'是相对的,此时ans有会被标记为1.
                    */
                    if(q[j]>=d[i])
                    /*
                    按位或已经有了d[i]只要之前经过重心的分支距离有q[j]-d[i],即judge[q[j]-d[i]]为1,
                    若d[i]恰好等于q[j],因为judge[0]本身就是1,那么ans[j]也是1.
                    */
                        ans[j]|=judge[q[j]-d[i]];
            }
            for(int i=1;i<=num;i++){
                judge[d[i]]=1;//将这个分支统计出的经过重心的距离在judge中都标记为1,代表由这条距离的路径
                Q.push(d[i]);//将d[i]计入队列中,方便遍历完所有经过重心的分支后O(n)还原judge数组.
            }
        }
    }
    //还原judge数组
    while(!Q.empty()){//不能memset 否则时间复杂度O(N^2)
        judge[Q.front()]=0;
        Q.pop();
    }
}
/*
感觉这个题目这样分治,好像意义并不大,因为分治的层数越深,计算经过重心的路径最大距离就越短,
而层数越浅的分治,经过重心的路径最大距离越大,似乎已经把所有询问中的路径距离覆盖到了.
感觉没必要再分治到层数更深的子树中去了.但事实上每个子树的重心不同,经过重心所构成的路径距离
数值就可能不用,尽可能地分治直到分治到叶子节点的目的是为了尽可能多地枚举可能的路径距离,这样
才会覆盖到所有询问距离,保证结果不出错.

分治的目的就是在O(nlogn)时间界下不断枚举重心 枚举重心作为根节点的不同分支的子树,再依次计算经过重心的路径距离
为什么分治要从树得到重心开始?
因为假如树退化成一条链(有n个节点),我们每次取链首作为根,那么这样分治每次统计经过根节点的路径(经过重心的各个分支组合)最大距离实际上都是n,
那这样分治的时间复杂度就是O(N^2).而如果选择重心,拆出来的子树的大小就会尽可能平均，那分治的层数也就尽可能的小了，
那么第一次分治的点必然在这条长链的中点上,再按照递归分治这时的层数为之前的一半(这里类似二分,而二分就是分治的思想),
这样可以保证分治的层数大约是logn,这样总的时间复杂度就是O(NlogN).

点分治过程中,每一层的所有递归过程合计对每个点处理一次,假设共递归h层,则总时间复杂度为O(N*h).
若我们每次选择子树的重心作为根节点,可以保证递归层数最少,时间复杂度为O(NlogN).
*/
void divide(int u){
    vis[u]=1;
    solve(u);
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!vis[v]){
            /*
            要分治,就要找重心,要找重心,就要用到siz
            */
            maxn[rt=0]=sum=siz[v];//sum需记录的是以v为根的子树的节点个数,rt要再次设置为0记录这个子树的所有节点个数,而rt会在后续更新中记录最小值
            getrt(v,0);//计算以v为根的子树的重心
            /*
            重新计算以重心为根开始的siz数组,rt必然还是之前的rt,重心是不变的,
            这个重新计算后的siz在下次divide时设置sum时有用,否则siz的错误会间接导致sum错误会影响重心的选取,进而影响时间界.
            */
            getrt(rt,0);
            divide(rt);//再次以重心作为根节点进行点分治
        }
    }
}

int main(){
    int n,u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    for(int i=1;i<=m;i++)
        scanf("%d",&q[i]);
    judge[0]=1;
    maxn[0]=sum=n;//第一次统计整棵树的重心,sum为所有节点个数,maxn[u]为最大值用来更新最小值的
    getrt(1,0);//计算重心
    getrt(rt,0);//重新计算以重心为根的子节点的siz
    divide(rt);//从重心rt开始进行点分治
    for(int i=1;i<=m;i++){
        if(ans[i])
            printf("AYE\n");
        else
            printf("NAY\n");
    }
    return 0;
}
