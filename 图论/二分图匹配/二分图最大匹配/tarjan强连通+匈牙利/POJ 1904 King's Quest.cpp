#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 4100
#define M 4000100
using namespace std;
//ac 9844ms 二分图概念+tarjan求解scc
//HDU 4685是POJ 1904 加强版 没给出初始完美匹配,需要匈牙利先求出完美匹配
/*
题意:一个国王有n个儿子,现在对应有n个女孩,现在需要为
n个儿子都找到一位喜欢的女孩,每个儿子都有一些自己喜欢
的女孩,现在巫师根据各个儿子喜欢的情况,为每个儿子挑选出
一个女孩,即:一份完美匹配,但国王并不满意,国王想知道对于
每个儿子都可以选取哪些女孩作为配偶,而不至于使得其它儿子
喜欢的女孩都被选取而导致这个儿子没有喜欢的女孩可选的情况.
输出每个儿子可以选取女孩的个数,和这些女孩的编号(升序).
注意:输入数据一定保证存在完美匹配.
链接:http://poj.org/problem?id=1904
思路:显然儿子和女孩分为左右2集合构成二分图,但此题输入是肯定会
保证存在完美匹配的,因此这个问题用不到匈牙利算法求解最大匹配,
可以每个儿子i和喜欢的女生j,建i->(j+n)的单向边,而对于巫师给出
的完美匹配,儿子i和女孩j,建(j+n)->i的单向边.之后tarjan求解scc.
以下摘自网上.
对于每个儿子和女孩,如果他们都在同一个强连通分量内,则他们可以结婚.
因为每个儿子只能和喜欢的女孩结婚,初始完美匹配中的丈夫和妻子之间有
两条方向不同的边可以互达,则同一个强连通分量中的儿子数和女孩数一定
是相等的,若儿子x可以和另外的一个女孩a结婚,女孩a的原配儿子y肯定能
找到另外一个女孩b结婚,因为如果找不到的话,则x和a必不在同一个强连通分量中.
所以一个王儿子可以和所有与他同一强连通分量的女孩结婚,而这不会导致同一
强连通分量中的其他儿子找不到女孩结婚.
*/
/*
此题得到算法正确性是有问题的,这组数据能hack
input
3
2 1 2
3 1 2 3
2 2 3
1 2 3
output
2 1 2
3 1 2 3
2 2 3
如果第一个王子选第2个女子,第二个王子选第3个女子,第三个王子 不是没得选了吗
*/
int n,m,dfn[N],low[N],clock,cnt,head[N],block[N],id;
stack<int> s;
vector<int> seq;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!block[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
        }while(v!=u);
    }
}

void init(){
    clock=id=cnt=0;
    memset(head,-1,sizeof head);
    memset(dfn,0,sizeof(dfn));
    memset(block,0,sizeof(block));
}

int main(){
    int v;
    init();
    scanf("%d",&n);//n个儿子
    for(int i=1;i<=n;i++){
        scanf("%d",&m);//儿子i 喜欢m个女孩
        while(m--){
            scanf("%d",&v);
            addEdge(i,v+n);//男孩到女孩建边
        }
    }
    for(int i=1;i<=n;i++){//巫师给出的初始完美匹配
        scanf("%d",&v);
        addEdge(v+n,i);//女孩到儿子建边
    }
    for(int i=1;i<=2*n;i++){//儿子和女孩总共2n个 事实上i<=n也可以过,因为每个儿子发出的边至少都能覆盖到一个scc
        if(!dfn[i])
            dfs(i);
    }
    for(int u=1;u<=n;u++){
        seq.clear();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(block[u] == block[v])//儿子u和女孩v在同一scc,则可以结婚不影响其它儿子选取配偶
                seq.push_back(v-n);//女孩实际编号减n
        }
        sort(seq.begin(),seq.end());
        printf("%d",seq.size());
        for(int i=0;i<seq.size();i++)
            printf(" %d",seq[i]);
        printf("\n");
    }
    return 0;
}
