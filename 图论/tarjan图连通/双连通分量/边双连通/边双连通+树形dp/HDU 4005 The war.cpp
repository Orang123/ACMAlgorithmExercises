#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 10100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;
//The 36th ACM/ICPC Asia Regional Dalian Site
//ac 46ms tarjan求解scc缩点+树形dp
//参考博客:https://blog.csdn.net/Weiguang_123/article/details/7918311
//一般原图会用链式前向星存储(点边很多),为避免建两个head,edge.cnt,缩点后的图可以用vector,因为本身点边就很少,而且这里是树
/*
题意:n个点m条边带权的无向图,摧毁一条边的花费为边权,
现在要增加一条连边,问摧毁一条边使得图不连通至少需要
多少花费.
注意:输入数据应该是有重边的,这会影响ebc的求取,要考虑重边能构成的ebc.
原图应该是保证了是连通图的.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4005
思路:显然必须摧毁桥才能使其不连通,但是对于新加的连边并不能确定,
增加一条边会成环使得边两端点内路径上的桥不再是桥,只能考虑摧毁环之外
的桥,那就从最坏的情况去考虑,增加的边构成的环内尽可能多地包含了边权较
小的桥,那么剩余的桥边权自然较大,我们只要取剩余桥中边权最小的桥摧毁就好,
那么首先tarjan求解ebc缩点构造无向树(每条边都是原图中的桥),我们可以贪心选择
将边权最小的桥包括进去,从这个最小桥的两端点向外延伸对于子树分支中的边权
尽可能选择最小边作为新加边构成环内的边,使其不再是桥,这样剩下的桥边权自然
就是较大的(这就满足了极端情况),同时求解出子树分支中的次小边权,我们要记录的
就是每棵子树分支中次小边权的最小值,这个过程可以通过树形dp(即从最小桥的
两端点分别作为根节点dp遍历子树)实现,为什么只需要记录每棵子树分支中次小边权的
最小值就行呢,因为现在我们已经选定最小桥是从最小桥开始延伸环的,那么所加的边
无论怎么加,它都不可能同时将子树分支中的最小边和次小边同时包括进环里,如果环
包括了最小边,那么显然剩下次小边,那么环外的次小边的最小值就是答案,如果环包括了次小边,
那么需要比较环外次小边最小值和当前分支最小边,选择较小的删除即可使其不连通,达到摧毁目的.

注意:实际所成的环中可能不见得恰好将所有的最小边都放进去,也就是说次小边的最小值大多数情况
是比环外最小割边要大的,但是当前并不确定加边时哪条,环内的边也不确定,所以除了环外次小边的
最小值是确定的外,其余割边的存在与否都是不确定的,所以支取极端情形下加边所形成外内全是各个
子树分支中的最小边,虽然这种情况在缩点树中并不成立,但我们只取至少的花费,就是次小值的最小值,
这能在其余非极端情况下,满足摧毁非极端情况下最小的割边.
*/

int n,m,dfn[N],low[N],clock,cnt,ebc_cnt,head[N],block[N],de[N],ans;
stack<int> s;
vector<pair<int,int> > G[N];

struct Edge{
    int from,to,next,w;
}edge[M<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){from,to,head[from],w};
    head[from]=cnt++;
}

void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if((i^1) == fa) continue;//重边不影响,可以返回父亲节点.
        if(!dfn[v]){
            tarjan(v,i);
            low[u]=min(low[u],low[v]);
        }
        else
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
//也可以用dp[u][0] dp[u][1]分别代表 最小、次小边权
int dfs(int u,int fa){
    //minw1记录u节点分支中最小边权,minw2记录u节点分支中次小边权 包括u-v的边权
    //sonw记录v子树中最小边权 不包括u-v的边权
    int minw1=INF,minw2=INF,sonw;
    for(pair<int,int> &v : G[u]){
        if(v.first == fa) continue;
        sonw=dfs(v.first,u);
        sonw=min(sonw,v.second);//比较和u-v的边权哪个更小
        //如果v子树中最小边权比当前u子树分支中记录过的最小边权还小
        //更新次小边权为之前的最小边,在更新最小边为sonw
        if(sonw<minw1){
            minw2=minw1;
            minw1=sonw;
        }
        else if(sonw<minw2) minw2=sonw;//否则如果sonw比最小边大,比次小边小,就更新次小边
    }
    ans=min(ans,minw2);//记录环外次小边的最小值 作为催毁桥至少需要的代价
    return minw1;//返回子树分支中最小边权
}

int main(){
    int u,v,w,s,t;
    while(scanf("%d%d",&n,&m)!=EOF){
        ebc_cnt=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        memset(de,0,sizeof(de));
        for(int i=1;i<=n;i++) G[i].clear();
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        tarjan(1,-1);
        if(ebc_cnt == 1){//如果本身就是EBG(边双连通图),则不存在桥
            printf("-1\n");
            continue;
        }
        w=INF;
        for(int i=0;i<cnt;i+=2){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v]){
                de[block[u]]++;
                de[block[v]]++;
                G[block[u]].push_back(make_pair(block[v],edge[i].w));//构造无向树
                G[block[v]].push_back(make_pair(block[u],edge[i].w));
                if(w>edge[i].w){//记录最小边权的桥的两端点 s、t
                    w=edge[i].w;
                    s=block[u],t=block[v];
                }
            }
        }
        int res=0;
        for(int i=1;i<=ebc_cnt;i++)
            if(de[i] == 1) res++;//对于度为1的叶子节点+1
        //如果无向树度为1的点只有2个点,也就是一棵直链,那么在添加一条首位相接的边就能直接成为EBG,之后就不存在桥了.
        if(res == 2) printf("-1\n");
        else{//这种情况下一定是有解的,因为度为1的点至少为3,也就是一定会有2个分支的节点,那么就一定存在次小边
            //有些做法还在这里判断ans为INF,原图不连通,不考虑重边是有问题的.
            ans=INF;
            dfs(s,t);//从s点dp遍历
            dfs(t,s);//从t点dp遍历
            printf("%d\n",ans);
        }
    }
    return 0;
}
/*
//草稿纸上的样例
input
8 7
1 2 4
2 3 1
3 4 2
4 5 3
3 7 5
3 6 6
4 8 4

output
4
*/
