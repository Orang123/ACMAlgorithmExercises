#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 5100
#define M 5100
using namespace std;
//ac 3588ms
//2013 ACM-ICPC南京赛区全国邀请赛
/*
题意:无向图中删除2个点后所剩余的连通分量个数使其最大,输出最大的连通分量个数.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4587
思路:N,M<=5000.因为原图有可能根本不存在割点(直接求出所有割点,dfs再任选2个的
所有组合方案显然不行,基本也会TLE),所以我们可以枚举先删除一个点,然后tarjan求解
出剩余割点枚举删除第二个点,当然此时有可能仍旧是不存在割点的.对于原图本身存在
割点,那么第一次枚举的点有可能是割点也有可能不是,因为并不清楚原图是否存在割点,
所以要暴力枚举删除第一个点O(n^2)*O(tarjan(V+E)).
*/

int n,m,dfn[N],low[N],num,cnt,head[N],cut[N],ans;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa,int k){
    dfn[u]=low[u]=++num;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa || v == k) continue;//k点已删除,这样与k相连的边就都不会被遍历
        if(!dfn[v]){
            dfs(v,u,k);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v])
                cut[u]++;
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(fa < 0) cut[u]--;//fa == -1 时,是根节点 实际连通分量 是cut[u]减1,因为并没有父亲部分的连通分量.
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        cnt=0;
        memset(head,-1,sizeof head);
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        ans=1;//最终至少存在一个连通分量
        for(int i=0;i<n;i++){//先枚举删除一个点
            memset(dfn,0,sizeof dfn);
            memset(cut,0,sizeof cut);
            num=0;
            int sum=0;
            for(int j=0;j<n;j++){
                if(j == i) continue;//不能以i作为根节点 tarjan求割点 因为已经假定删除了
                if(!dfn[j]){
                    sum++;//本身割点祖父节点所剩余的一个连通分量
                    //i点作为已删除的点,tarjan遍历时遇到i点 continue 这样与i相连的边就都不会被遍历,就能模拟出删除i点的图的情况
                    dfs(j,-1,i);
                }
            }
            for(int k=0;k<n;k++){
                if(k!=i)//这里感觉即使不加k!=i的判定应该也是对的(i点的cut肯定为0),但是不加if 会wa
                    ans=max(ans,sum+cut[k]);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
