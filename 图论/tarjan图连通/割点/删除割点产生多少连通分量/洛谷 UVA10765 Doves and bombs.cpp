#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
#define M 1000100
using namespace std;
//ac 0ms
//注意初始化 id 否则num相等时 会出错,不是割点的id就不确定,排序会出错按道理不初始化也不应该错啊
/*
题意:给定一个n个点的连通的无向图,一个点的“鸽子值”定义为将它从图中删去后连通块的个数.
求“鸽子值”按降序排列的前m个.若鸽子值一样则按标号升序排列.
链接:https://www.luogu.com.cn/problem/UVA10765
思路:tarjan求解割点计数
*/

int n,m,dfn[N],low[N],clock,cnt,head[N];
struct Cut{
    int id,num;
    bool operator < (const Cut &x)const{
        if(num == x.num) return id<x.id;
        else return num>x.num;
    }
}cut[N];

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v])
                cut[u].num++;
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(fa == -1) cut[u].num--;//注意根节点删除后实际连通分量 要少算一个
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        for(int i=0;i<n;i++){
            cut[i].id=i;//注意这里 所有的id一定要初始化,否则num有可能相同时,不是割点的id没有初始化,排序结果可能是错误的
            cut[i].num=1;
        }
        while(scanf("%d%d",&u,&v) && (u!=-1||v!=-1)){
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=0;i<n;i++){
            if(!dfn[i])
                dfs(i,-1);
        }
        sort(cut,cut+n);
        for(int i=0;i<m;i++)
            printf("%d %d\n",cut[i].id,cut[i].num);
        printf("\n");
    }
    return 0;
}
