#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 500100
int head[N],fa[N][21],dep[N],lg[N],n,m,s,cnt;//lg[i]为i以2为底的对数,实际就是深度i的向上第2^k个父亲的上界 最大的k fa[N][21] 实际二维下标只能取到20 也就是100W个结点满足题目50W要求
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to]};
    head[to]=cnt++;
}

/*不设置0结点,直接以s作为初始根节点做法
void dfs(int u){
    for(int i=1;i<=lg[dep[u]]-1;i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa[u][0]){
            fa[v][0]=u;
            dep[v]=dep[u]+1;
            dfs(v);
        }
    }
}
*/

void dfs(int u,int fath){
    fa[u][0]=fath;
    dep[u]=dep[fath]+1;
    for(int i=1;i<=lg[dep[u]]-1;i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fath)
            dfs(v,u);
    }
}

int lca(int x, int y){
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y])
        /*
        这里如果dep[x]-dep[y]如果是偶数的话,属于刚好2^k次方就等于dep[x]-dep[y],那么只需跳一步便可使得dep[x]=dep[y](刚好跳满),
        若为奇数 因为lg[7]-1=2它是不够2^3次方的(若跳2^3次方则会跳得比y的深度还小,这是不合理的),
        因此在向上跳只会跳长度为2^2=4的深度而不会跳跃到和y结点同深度,跳上去后和y还差7-4=3的长度,之后一次选择2^1、2^0次方 因此7的二进制表示(111)
        每次跳跃都是步长都是选择lg[dep[x]-dep[y]]-1,x与y之间深度之差 以2为底对数上所能跳的最大距离
        再比如若最先开始x与y深度之差5,那么依次选用的跳远步长为2^2、2^0次方,而5=(101)正确,这个过程其实省略了2^1次方的枚举,每次都枚举的是x与5深度差值所能跳跃的最大的2的倍率,
        忽略掉了多余的步长
        */
        x=fa[x][lg[dep[x]-dep[y]]-1];//lg[dep[x]-dep[y]]-1代表x与y之间深度之差数值上所能向上跳的最大的第2^k次方个祖先,k是最大上界 这里x与y的深度之差是实时计算的,因此每一次的步长选择都是选择尽可能最大的,而忽略掉了一些不符合条件的步长
    if(x == y) return x;
    for(int i =lg[dep[x]]-1;i>=0;i--){//lg[dep[x]]-1代表x结点深度所能向上跳的第2^k次方个祖先的 k的最大上界
        if(fa[x][i]!=fa[y][i]){//这里相等的情况，有可能在真正lca的上面,所以会一直按照最小的跳跃距离跳,直到跳跃到最后之差一个单位距离时 返回fa[x][0]
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

int main(){
    int x,y;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&x,&y);
        addEdge(x,y);
    }
    /*
    这里需要从1开始计算,并且lg[1]=1,因为计算lg[i]时会用到1<<lg[i-1]是否等于i,
    也只有lg[i-1]比本身的值多1时1<<lg[i-1]才会等于i,因此最终的结果里需要减去1,
    对于3、5、6、7这些本身1<<lg[i-1]不等于i的,lg[i]还是lg[i-1] 即lg[3]=lg[2],lg[5]、lg[6]、lg[7]、都等于lg[4].
    这里只是为了后续的递推而特意多出来这一个1的
    */
    for(int i=1;i<=n;i++)
        lg[i]=lg[i-1]+(1<<lg[i-1] == i);//lg[0]=-1; lg[i]=lg[i>>1]+1; 这种递推公式结果不会多出一个1
    dfs(s,0);
    while(m--){
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x,y));
    }
    return 0;
}
/*
不设置0结点,直接以s作为初始根节点做法
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 500100
int head[N],fa[N][21],dep[N],lg[N],n,m,s,cnt;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to]};
    head[to]=cnt++;
}

void dfs(int u){
    for(int i=1;i<=lg[dep[u]]-1;i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa[u][0]){
            fa[v][0]=u;
            dep[v]=dep[u]+1;
            dfs(v);
        }
    }
}

int lca(int x, int y){
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y])
        x=fa[x][lg[dep[x]-dep[y]]-1];
    if(x == y) return x;
    for(int i =lg[dep[x]]-1;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

int main(){
    int x,y;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&x,&y);
        addEdge(x,y);
    }
    for(int i=1;i<=n;i++)
        lg[i]=lg[i-1]+(1<<lg[i-1] == i);
    dfs(s);
    while(m--){
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x,y));
    }
    return 0;
}
*/
