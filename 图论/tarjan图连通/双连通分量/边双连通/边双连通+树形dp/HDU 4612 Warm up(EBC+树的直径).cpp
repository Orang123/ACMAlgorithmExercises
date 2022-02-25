#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 200100
#define M 1000100
using namespace std;
//ac tarjan类scc算法 1123ms

/*
题意:对于无向图G,加入一条新边,使得无向图中剩下桥的数量最少.
输出最小剩余桥数.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4612
思路:tarjan求解边双连通分量 缩点构造无向树,无向树上的每条边都是桥,那么所加的边构成的环
必须包含更多的树边(桥),显然树的直径中边数最多,那么结果就是ebc_cnt-1-树的直径.
原图G中桥的个数为缩点后树中边数,树边数=点数-1=ebc_cnt-1.
*/

int n,m,dfn[N],low[N],num,cnt1,cnt2,head1[N],head2[N],block[N],ebc_cnt,rt,ans;
stack<int> s;

struct Edge{
    int from,to,next;
}edge1[M<<1],edge2[N<<1];

void addEdge1(int from,int to){
    edge1[cnt1]=(Edge){from,to,head1[from]};
    head1[from]=cnt1++;
}

void addEdge2(int from,int to){
    edge2[cnt2]=(Edge){from,to,head2[from]};
    head2[from]=cnt2++;
}

void tarjan(int u,int fa){
    dfn[u]=low[u]=++num;
    s.push(u);
    int v;
    for(int i=head1[u];i!=-1;i=edge1[i].next){
        v=edge1[i].to;
        if(!dfn[v]){
            tarjan(v,i);
            low[u]=min(low[u],low[v]);
        }
        else if((i^1)!=fa)
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        ebc_cnt++;
        do{
            v=s.top();
            s.pop();
            block[v]=ebc_cnt;
        }while(v!=u);
    }
}

void dfs(int u,int fa,int d){
    for(int i=head2[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        if(v == fa) continue;
        if(ans<d+1){
            rt=v;
            ans=d+1;
        }
        dfs(v,u,d+1);
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        ebc_cnt=cnt1=cnt2=num=0;
        memset(dfn,0,sizeof dfn);
        memset(head1,-1,sizeof head1);
        memset(head2,-1,sizeof head2);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge1(u,v);
            addEdge1(v,u);
        }
        tarjan(1,-1);
        for(int i=0;i<cnt1;i+=2){
            u=edge1[i].from;
            v=edge1[i].to;
            if(block[u]!=block[v]){
                addEdge2(block[u],block[v]);
                addEdge2(block[v],block[u]);
            }
        }
        ans=0;
        dfs(1,-1,0);
        dfs(rt,-1,0);
        //原图G中桥的个数为缩点后树中边数,树边数=点数-1=ebc_cnt-1.
        printf("%d\n",ebc_cnt-1-ans);
    }
    return 0;
}
