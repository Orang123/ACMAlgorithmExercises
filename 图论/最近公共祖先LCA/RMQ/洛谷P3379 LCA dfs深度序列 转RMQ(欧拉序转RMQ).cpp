#include<cstdio>
#include<ctype.h>
#include<algorithm>
#include<cstring>
#define N 500100
using namespace std;
/*
dfs遍历序列的总结点数为2n-1 这个可以根据每个叶子节点的dfs遍历序列只会遍历一次,
而父节点回溯时多余访问的那一次序列可以分给叶子节点，当做叶子节点访问了2次，
而对于祖先结点也依次这样向下推,最终向下推移的结果就是除过根节点外其余点都访问了2次.所以dfs遍历序列的总结点个数为2n-1(n为树的结点总数)
dfn[u]代表遍历序列中第一次访问到u结点的遍历序号,num为遍历序列的次序编号
*/
int head[N],lg[N<<1],dep[N],dfn[N],st[N<<1][20],cnt,num;//st[j][i]代表dfs遍历序号为j起始在内的2^i次方个结点中深度最小的结点编号
struct Node{
    int to,next;
}edge[N<<1];

//LCA 转RMQ 时间卡得很紧 需要读入优化处理
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to]};
    head[to]=cnt++;
}
//O(n)
void dfs(int u,int fa){
    dfn[u]=++num;
    st[num][0]=u;
    dep[u]=dep[fa]+1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa){
            dfs(v,u);
            /*
            回溯时父节点需要从新加入遍历序列,只有这样在统计lca(x,y)时 dfs访问的遍历序列区间[dfn[x],dfn[y]] 中
            才会包含x、y的最近公共祖先结点,lca(x,y)其实就是区间[dfn[x],dfn[y]]内深度最小的结点.
            (至于原因应该是这个深度最小的结点就是那个由x结点遍历转向y结点的拐点,即LCA)
            */
            st[++num][0]=u;
        }
    }
}

//预处理 将LCA问题转化为 关于深度序列的st表 RMQ问题 O((2n-1)*log(2n-1))
void RMQ(int n){
    lg[0]=-1;
    for(int i=1;i<=num;i++)//这里是预处理dfs遍历序列所有结点数的lg 注意是num
        lg[i]=lg[i>>1]+1;
    for(int i=1;i<=lg[num];i++){//O(log(2n))
        for(int j=1;j+(1<<i)-1<=num;j++){//O(2n)
            int a=st[j][i-1];
            int b=st[j+(1<<i-1)][i-1];
            /*
            这里比较以j为起始点在内的2^(i-1)次方个结点最小深度 与以j+(1<<i-1)为起始点在内的2^(i-1)次方个结点最小深度取它们之间的最小值，
            重新计算以j为起始点在内的2^i次方个结点的最小深度结点编号 记录最小深度结点编号赋值给st[j][i]
            */
            if(dep[a]<dep[b]) st[j][i]=a;
            else st[j][i]=b;
        }
    }
}

//st表查询 O(1) LCA转RMQ约束 属于在线算法,每一个询问 对应一个O(1)的回答
int lca(int x,int y){
    x=dfn[x],y=dfn[y];//记录x、y结点第一次访问的遍历序号
    if(x>y) swap(x,y);//x编号为较小的左边界
    int k=lg[y-x+1];//计算以dfn[x]为左端点dfn[y]为右端点的dfs遍历序列区间的长度
    int a=st[x][k],b=st[y-(1<<k)+1][k];
    //依据st表将遍历区间分为以2^k次方为长度一左一右两部分,比较得出[dfn[x],dfn[y]]区间内深度最小的结点编号 便为原先x、y结点的最近公共祖先lca(x,y)
    if(dep[a]<dep[b]) return a;
    else return b;
}

int main(){
    int n,m,s,x,y;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1;i<=n-1;i++){
        x=read(),y=read();
        addEdge(x,y);//构造无向树
    }
    dep[0]=-1;//从根节点开始,深度从零开始.
    dfs(s,0);//根节点的父节点编号为零结点
    RMQ(n);
    while(m--){
        x=read(),y=read();
        printf("%d\n",lca(x,y));
    }
    return 0;
}
