#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 5010
#define M 50050
using namespace std;
//ac 37ms
/*
题意:有向图中,边分单向(输入1)的双向(输入0),求含有节点数最多的强连通分量,
若两个强连通分量节点数相同,按字典序输出.
链接:https://www.luogu.com.cn/problem/P1726
思路:tarjan,强连通分量求解完时,统计每个强连通分量的节点个数,记录最多个数
的强连通分量编号,最后按照点的字典序遍历是否在这个编号的强连通分量内,输出,
因为dfs时本身就是从编号靠前的点开始的,所以SCC编号越靠前的,它的第一个点的编号就越小.
*/

struct node{
    int to,next;
}edge[M];
struct arr{
    int val,s[N];
}arr0[N];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
stack<int> s;
bool in[N];
int id,block[N],amot[N];

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
        id++;
        do{
            v=s.top();
            in[v]=false;
            block[v]=id;
            amot[id]++;
            s.pop();
        }while(v != u);
    }
}
int main(){
    int n,m,a,b,t,ans=0;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d %d %d",&a,&b,&t);
        if(t == 1) addEdge(a,b);
        else{
            addEdge(a,b);
            addEdge(b,a);
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    //记录scc中最大个数
    for(int i=1;i<=id;i++){
        if(amot[i]>ans)
            ans=amot[i];
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;i++){//升序判断每个点所在scc的个数是否达到最大值,输出
        if(amot[block[i]] == ans)
            printf("%d ",i);
    }
    printf("\n");
    return 0;
}

/*
//思路:tarjan,入栈时记录点个个数,当强连通分量个数不同时,按照个数从大到小排,
//个数相同时,按照第一个点的编号从小到大排,因为两个强连通分量的点肯定是没有
//重复的,是各不一样的.
#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 5010
#define M 50050
using namespace std;


struct node{
    int to,next;
}edge[M<<1];
struct arr{
    int val,s[N];
    bool operator < (const arr &x)const{
        if(val == x.val) return s[1]<x.s[1];
        else return val>x.val;
    }
}arr0[N];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
stack<int> s;
bool in[N];
int id;

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
        arr0[++id].val=0;
        do{
            v=s.top();
            in[v]=false;
            arr0[id].val++;
            arr0[id].s[arr0[id].val]=v;
            s.pop();
        }while(v != u);
        sort(arr0[id].s+1,arr0[id].s+1+arr0[id].val);//每个强连通分量的字典序要在记录进数组后先排好
    }
}
int main(){
    int n,m,a,b,t;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d %d %d",&a,&b,&t);
        if(t == 1) addEdge(a,b);
        else{
            addEdge(a,b);
            addEdge(b,a);
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            dfs(i);
    }
    sort(arr0+1,arr0+1+id);
    printf("%d\n",arr0[1].val);
    for(int i=1;i<=arr0[1].val;i++)
        printf("%d ",arr0[1].s[i]);
    printf("\n");
    return 0;
}
*/
