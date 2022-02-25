#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 100100
#define M 300010
#define INF 0x3f3f3f3f
#define Mod 1000000007
using namespace std;
//ac 135ms tarjan求解scc缩点+乘法原理
/*
题意:这里有n座电影院,n对情侣分别在每座电影院里,然后电影院里都有汽油,
但是要使用它需要一定的费用.m条单向通道连接相邻的两对情侣所在电影院.
HXY 有个绝技,如果她能从一个点开始烧,最后回到这个点,
那么烧这条回路上的情侣的费用只需要该点的汽油费即可.
并且每对情侣只需烧一遍,电影院可以重复去.然后她想花尽可能少的费用烧掉所有的情侣.
现在问烧掉所有情侣最少花费是多少,以及共有多少方案.
链接:https://www.luogu.com.cn/problem/P2194
思路:对于环中的点只需烧花费最少的一个点即可,方案数按照乘法原理,即每个scc
中最少花费的点有几个,这样累乘即是答案.tarjan求解scc缩点+乘法原理
*/

int n,m,head[N],cnt,sum,ans;
int id,dfn[N],low[N],clock,block[N],val[N],minval[N],num[N];
stack<int> s;

struct Edge{
    int to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(block[v]) continue;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            if(minval[id]>val[v]){
                num[id]=1;
                minval[id]=val[v];
            }
            else if(minval[id] == val[v])//最小花费相等时
                num[id]++;//最小花费的个数++
        }while(v!=u);
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    memset(minval,0x3f,sizeof(minval));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i);
    }
    ans=1;
    for(int i=1;i<=id;i++){
        sum+=minval[i];
        ans*=num[i]%Mod;//要对结果取模
    }
    printf("%d %d",sum,ans);
    return 0;
}
