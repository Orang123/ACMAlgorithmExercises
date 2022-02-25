#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2100
#define M 4000100
using namespace std;
//ac 1344ms
/*
题意:原图为混合图,既有无向边,也有有向边,
现在要将无向边改为有向边,使得有向图中任意两点之间仍旧
连通相互可达,现在要输出每条无向边更改后的方向性,
对于仍旧是双向输出两端点和2,对于是单向的输出有向边的
两端点(必须是实际的方向)和1.
链接:http://poj.org/problem?id=1438
思路:因为是混合图,所以原图不一定连通,对于这个改法,
实际对于桥可能不一定是无向边了,有可能有向边也会作为桥,
这里只需将图更改为任意两点都互相连通可达的有向图即可.
所以为了遍历双向边输出的方便,可以将有向边和无向边都建2条,但对于有向边
的另一条要做标记作为虚边,实际tarjan并不经过即可.
但实际为了使得任意点连通,无向边的数目其实可以更少,
这个标程输出的无向边是按照桥的数目来确定的,可能无向边会多一些.
就是输出的答案也不是绝对最优的.
*/
int n,m,dfn[N],low[N],clock,cnt,head[N];

struct Edge{
    int from,to,next,flag,sta;
}edge[M];

void addEdge(int from,int to,int flag){
    edge[cnt]=(Edge){from,to,head[from],flag,-1};//sta标记-1代表这条边的方向还未被确定
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        //如果是虚边并不存在 或者状态不为-1说明这个边的方向之前已经确定过
        if(!edge[i].flag || edge[i].sta!=-1) continue;
        edge[i].sta=1;//标记当前方式为要保留的有向边反向
        edge[i^1].sta=0;//反方向可以不需要 实际这个反向边可能是虚边
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            //对于桥要保证其双向性,但实际这里有可能是本身并不存在的有向边的虚边,这主要还是取决于原图的回边连接情况
            //这个原因主要是 桥的求法需要限定在无向图上,这里如果原图的输入能保证任意点可达,那这里的桥一定本身就是双向的
            //如果输入不能保证任意点可达,这里的桥有可能会是有向边.
            //但实际为了使得任意点连通,无向边的数目其实可以更少,这个标程输出的无向边是按照桥的数目来确定的,可能无向边会多一些.
            if(dfn[u]<low[v])
                edge[i^1].sta=1;
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void init(){
    clock=cnt=0;
    memset(head,-1,sizeof head);
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v,flag;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        while(m--){
            scanf("%d%d%d",&u,&v,&flag);
            if(flag == 1){
                addEdge(u,v,1);
                addEdge(v,u,0);//建立虚边 实际并不存在,只是为了遍历时+2方便点,判断双向边的方便
            }
            if(flag == 2){
                addEdge(u,v,2);
                addEdge(v,u,2);
            }
        }
        for(int i=1;i<=n;i++){//原图混合图 可能并不连通
            if(!dfn[i])
                dfs(i,-1);
        }
        for(int i=0;i<cnt;i+=2){
            if(edge[i].flag){
                if(edge[i].flag == 2 && edge[i].sta && edge[i^1].sta)//该边为无向边
                    printf("%d %d 2\n",edge[i].from,edge[i].to);
                else if(edge[i].flag == 2 && edge[i].sta && !edge[i^1].sta)//只需保留edge[i]
                    printf("%d %d 1\n",edge[i].from,edge[i].to);
                else if(edge[i].flag == 2 && edge[i^1].sta && !edge[i].sta)//只需保留edge[i^1]
                    printf("%d %d 1\n",edge[i^1].from,edge[i^1].to);
            }
        }
    }
    return 0;
}

/*
//这组数据
input
5 5
1 3 2
1 2 2
2 5 2
4 5 1
3 4 2

output
1 3 2
1 2 2
2 5 2
3 4 1

而实际可能并不需要无向边
最优的结果
output
1 3 1
2 1 1
5 2 1
3 4 1

input
4 4
1 2 2
2 3 1
3 4 2
4 2 1

output
1 2 2
3 4 1
*/
