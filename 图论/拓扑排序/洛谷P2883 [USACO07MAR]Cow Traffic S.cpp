/*
题意:摘自网上
n个点,m条边的有向图,求从每个入度为零的点走到唯一的一个
出度为零的点的所有走法中，经过次数最多的一条边被经过的次数.
n<=5000,M<=50000.
链接:https://www.luogu.com.cn/problem/P2883
思路:构建正反图,从所有入度为0的点进行正向图的拓扑排序,
num1[v]记录入度为0的点到达v点的路径条数,再从n点在反向图
进行拓扑排序,num2[v]记录从v点出发到达n点的路径条数.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5100
#define M 50100
using namespace std;
int n,m,head1[N],head2[N],cnt1,cnt2,ans=-1,inde[N],outde[N],num1[N],num2[N],vis[N];
struct Node1{
    int from,to,next;
}edge1[M];
struct Node2{
    int from,to,next;
}edge2[M];

void addEdge1(int from,int to){
    edge1[cnt1]=(Node1){from,to,head1[from]};
    head1[from]=cnt1++;
}

void addEdge2(int from,int to){
    edge2[cnt2]=(Node2){from,to,head2[from]};
    head2[from]=cnt2++;
}

void dfs1(int u){
    for(int i=head1[u];i!=-1;i=edge1[i].next){
        int v=edge1[i].to;
        num1[v]+=num1[u];
        if(!--inde[v])//只有当v点入度为0 时才继续向后搜索,避免重复搜索后续路径,复杂度过大
            dfs1(v);
    }
}

void dfs2(int u){
    for(int i=head2[u];i!=-1;i=edge2[i].next){
        int v=edge2[i].to;
        num2[v]+=num2[u];
        if(!--outde[v])
            dfs2(v);
    }
}
//建两张正反图，分别处理出到每个点的路径数
int main(){
    int u,v;
    memset(head1,-1,sizeof(head1));
    memset(head2,-1,sizeof(head2));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdge1(u,v);
        addEdge2(v,u);
        inde[v]++;
        outde[u]++;
    }
    for(int i=1;i<=n;i++){
        if(!inde[i]){
            vis[i]=1;//vis记录入度为0的点,因为dfs1会增加入度为0的点
            num1[i]=1;
        }
    }
    for(int i=1;i<=n;i++){
        if(vis[i])
            dfs1(i);
    }
    num2[n]=1;
    dfs2(n);
    for(int i=0;i<m;i++)
        ans=max(ans,num1[edge1[i].from]*num2[edge1[i].to]);//计算这条路径 两端点(正向、反向)通过的次数 相乘即使答案 求取最大值
    printf("%d\n",ans);
    return 0;
}
