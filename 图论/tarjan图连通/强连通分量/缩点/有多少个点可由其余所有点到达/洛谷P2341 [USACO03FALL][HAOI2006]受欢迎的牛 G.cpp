#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 10100
#define M 50100
using namespace std;
//ac 133ms
/*
题意:每头奶牛都梦想成为牛棚里的明星.被所有奶牛喜欢的奶牛就是一头明星奶牛.
所有奶牛都是自恋狂,每头奶牛总是喜欢自己的.奶牛之间的“喜欢”是可以传递的——
如果A喜欢B,B喜欢C,那么A也喜欢C.牛栏里共有N头奶牛,
给定一些奶牛之间的爱慕关系,请你算出有多少头奶牛可以当明星.
链接:https://www.luogu.com.cn/problem/P2341
思路:可以先tarjan求解SCC,之后再将SCC缩点,将原图转换成一个DAG(有向无环图),
这样有向图中的关系将变得简洁明了,事实上,观察发现DAG中出度为0的点(SCC),如果
只有一个,那么这个SCC中的点就被其余所有点喜欢传递,该SCC中点的个数即为答案.
若出度为0的点个数大于1,那至少有两个点之间是没有传递关系的,那么也就不存在
"明星奶牛"即被所有奶牛所喜欢.
*/

struct node{
    int to,next;
}edge[M];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
stack<int> s;
bool in[N];
int block[N],id,SSG[N],de[N];

void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=true;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        ++id;
        do{
            v=s.top();
            in[v]=false;
            block[v]=id;
            SSG[id]++;
            s.pop();
        }while(v != u);
    }
}
int main(){
    int n,m,a,b;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d %d",&a,&b);
        addEdge(a,b);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    int deNum=0;
    for(int i=1;i<=n;i++){
        for(int j=head[i];j!=-1;j=edge[j].next){
            if(block[i]!=block[edge[j].to]){//两个结点对应的强连通分量编号不同,则可认为是两个缩点之间有连接
                de[block[i]]++;//统计i的出度 ++  这里不需要真正地重新建图
            }
        }
    }
    int ans;
    for(int i=1;i<=id;i++){
        if(!de[i]){
            deNum++;//统计出度为0的缩点数量
            ans=i;//记录id
        }
    }
    /*
    同一强连通分量中的所有牛之间都是相互喜欢的,因此只要强连通分量缩成的点
    直接与出度相连 列如缩点u->v 对于u中的所有牛都能连通v中所有的牛,
    则根据传递性u中所有牛都喜欢v中牛.
    */
    //若出度为0的点有且仅有1个,则这个缩点对应的强连通分量的节点个数即为答案
    //而且至少有一个不可能为0,最少是原图就是强连通图直接可以缩成一个点
    if(deNum == 1) printf("%d\n",SSG[ans]);
    //若大于一个 必然对于这些出度为0的缩点而言 他们的牛之间相互是没有关联,
    //相互不喜欢的,自然无法满足所有牛都喜欢的明星牛的说法
    else printf("0\n");
    printf("\n");
    return 0;
}
