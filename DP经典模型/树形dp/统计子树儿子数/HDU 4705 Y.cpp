#pragma comment(linker, "/STACK:16777216")//按照题目要求手动扩大堆栈空间
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;
typedef long long ll;

/*
题意:一棵n个节点的树,求出三个点都不在同一条路径上的三元组(A,B,C)点对有多少种
三个点不在同一条路径上指的是,三个点分别在三个分支的子树上.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4705
思路:可以从反面考虑,dfs求出三个点在同一条路径上和2个点在同一条路径上的种类数,
也就是三个点在一个分支上或2个点在同一分支上.
再用C[n][3]减去这个结果便是三个点都不在用一条路径上的可能.
*/

int cnt,n,head[N],siz[N];
ll sum;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    siz[u]=1;
    ll tmp=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        //tmp代表已经遍历的子树的节点个数
        tmp+=siz[v];
        /*
        这里是选择siz[v]子树中的一个节点,再选择u节点,
        再选择其余节点(这里包括u的父亲结点以上或u的其它还未遍历的子树节点),
        若选择的是向上的父亲结点则三个点都在同一条路径上,
        若选择未遍历的子树中节点则两个点在同一条路径上.
        */
        sum+=siz[v]*1*(n-tmp-1);
    }
}

int main(){
    int u,v;
    while(scanf("%d",&n)!=EOF){
        cnt=sum=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        dfs(1,-1);
        //n*(n-1)*(n-2)/6 从n个点中取出任意3个有多少可能
        printf("%lld\n",(ll)n*(n-1)*(n-2)/6-sum);
    }
    return 0;
}
