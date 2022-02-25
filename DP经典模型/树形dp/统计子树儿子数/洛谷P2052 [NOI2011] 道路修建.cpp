/*
题意:在W星球上有n个国家。为了各自国家的经济发展，他们决定
在各个国家之间建设双向道路使得国家之间连通。但是每个国家的
国王都很吝啬，他们只愿意修建恰好n−1条双向道路。
每条道路的修建都要付出一定的费用，这个费用等于道路长度乘以道路两端
的国家个数之差的绝对值。例如，在下图中，虚线所示道路两端分别有2个、4个国家，
如果该道路长度为1，则费用为 1×|2 - 4|=2。
对于给定的建造方案，计算出所需要的费用。
n<=10^6.
链接:https://www.luogu.com.cn/problem/P2052
思路:树形dp.
*/
//ac 3.77
#include<cstdio>
#include<cmath>
#include<cstring>
#define N 1001000
using namespace std;
typedef long long ll;
int n,head[N],cnt,son[N];
ll sum;
struct Node{
    int to,next,w;
}edge[N<<1];


void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    son[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u);
        son[u]+=son[v];
        //注意乘的过程会溢出要强制转换,(ll)后面对这个结果不能再扩个括号ll)(abs(n-2*son[v])*edge[i].w)这样会wa
        sum+=(ll)abs(n-2*son[v])*edge[i].w;
    }
}

int main(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    dfs(1,0);
    printf("%lld",sum);
    return 0;
}
