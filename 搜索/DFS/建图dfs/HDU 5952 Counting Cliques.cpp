/*
完全图:每对不同的顶点之间都恰连有一条边相连.
题意:计算图中结点数为s的完全子图个数.
列如样例1:1->2 2->3 3->43个结点数为2的完全子图
链接:https://acm.hdu.edu.cn/showproblem.php?pid=5952
思路:dfs,枚举每个点尝试加入完全子图,判断和之前的点是否都存在边邻接.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n,m,s,head[120],mp[120][120],cnt,q[120],sum;
struct Node{
    int to,next;
}edge[2100];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

int judge(int v,int len){
    for(int i=1;i<=len;i++){
        if(!mp[v][q[i]]) return 0;
    }
    return 1;
}

void dfs(int u,int num){
    if(num == s){//节点数够s个结束
        sum++;
        return;
    }
    q[num]=u;//将u结点作为放入完全子图
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;//因为构建边的时候就是只构建从小到大单向边,所以不需要vis数组判重
        //对于已经访问过的加入完全子图的点,实际因为mp[i][i]本身是0,所以不会重复访问. 因此没有用visz数组标记
        if(!judge(v,num)) continue;//判断该点是否和已经在完全子图中的点都有边连接,若都有则加入完全子图
        dfs(v,num+1);
    }
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        sum=cnt=0;
        memset(head,-1,sizeof head);
        memset(mp,0,sizeof(mp));
        scanf("%d%d%d",&n,&m,&s);
        while(m--){
            scanf("%d%d",&u,&v);
            //这里为了避免重复计算完全子图如样例1:1->2 2->1会计算2次相同的完全子图. 只构建节点编号较小到节点编号较大的单向边
            if(u>v) swap(u,v);
            addEdge(u,v);
            mp[u][v]=1,mp[v][u]=1;//记录的时候记录双向边
        }
        for(int i=1;i<=n;i++)
            dfs(i,1);
        printf("%d\n",sum);
    }
    return 0;
}
