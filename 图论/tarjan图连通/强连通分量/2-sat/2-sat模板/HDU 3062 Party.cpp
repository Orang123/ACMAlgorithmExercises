#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 1100 //1对是2个点 1000对2000点
#define M 4000400//最多的矛盾关系 按完全图来计算 2000*2000
using namespace std;
//ac 421ms tarjan求解scc 妻子编号x,丈夫编号2x+1
/*
相关概念:
1.SAT是适定性(Satisfiability)问题的简称.一般形式为k-适定性问题,简称 k-SAT.
而当k>2时该问题为NP完全的(无法在多项式时间求解.O(n^k)).所以我们只研究k=2的情况.以tarjan做法为主流,
刘汝佳的爆搜版本也能做,但爆搜能解决一些特定问题,如字典序输出
2.2-SAT,简单的说就是给出n个集合,每个集合有两个元素，已知若干个<a,b>表示a与b矛盾(其中a与b属于不同的集合).
然后从每个集合选择一个元素,判断能否一共选n个两两不矛盾的元素.显然可能有多种选择方案
(我自己感觉只有2种方案向对立,一种是妻子出席的,一种是丈夫出席的),一般题中只需要求出一种即可.

2-sat和二分图匹配的区别:
这个和二分图匹配是有区别的,二分图匹配是尽可能多地找匹配的对数,而2-sat是在一对里有排他性只能选派一个，
而且不同对相互之间还有矛盾性,能否续每一对都选出一个,尽可能多地选派
说明:
2-sat问题属于数学适定性问题,和布尔方程有关,这里暂时不做过多研究.
*/

/*
题意:有n对夫妻被邀请参加一个聚会,因为场地的问题,每对夫妻中只有1人可以列席.
在2n 个人中,某些人之间有着很大的矛盾(当然夫妻之间是没有矛盾的),有矛盾的2个人
是不会同时出现在聚会上的.有没有可能会有n个人同时列席？
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3062
思路:裸的2-sat问题.tarjan求解scc.
*/
struct Node{
    int to,next;
}edge[M];
int n,m,head[N<<1],dfn[N<<1],low[N<<1],num,cnt,block[N<<1],id,in[N<<1];
stack<int> s;
void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}
//Tarjan SCC 缩点  O(V+E)
void dfs(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);

    }
    if(low[u] == dfn[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            block[v]=id;
        }while(v!=u);
    }
}

bool judge(){
    for(int i=0;i<2*n;i++)//总共n对夫妻 2n个点 编号0~(2n-1)
        if(!dfn[i]) dfs(i);
    for(int i=0;i<n;i++)//这里枚举的是夫妻的对数编号
        //若妻子和丈夫同时出席,则一定含有矛盾关系的人也都会出席,因为妻子丈夫同时出席正是由于有矛盾关系人同时出席导致的
        if(block[2*i] == block[2*i+1]) return false;
    return true;
}

int main(){
    int a1,a2,c1,c2;
    while(scanf("%d",&n)!=EOF){
        id=num=cnt=0;
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(block,0,sizeof(block));
        memset(in,0,sizeof(in));
        scanf("%d",&m);
        while(m--){
            //这种2a,2a+1的做法 点的编号是从0开始的,最大编号为2n-1.
            scanf("%d%d%d%d",&a1,&a2,&c1,&c2);//a1 a2只是那对夫妻的编号0~n-1 0代表妻子 1代表丈夫
            a1=a1*2+c1;//a1*2是构造一堆夫妻的编号 2个点时紧挨着的 奇数是妻子,偶数是丈夫
            a2=a2*2+c2;
            addEdge(a1,a2^1);//选了a1,就一定对应的是a2的配偶,因为a1 a2是矛盾关系
            addEdge(a2,a1^1);//选了a2,就一定对应a1的配偶,a2 a1是矛盾关系,同上
        }
        if(judge()) printf("YES\n");//n个人同时出席的实际结果并不唯一,这里只判断是否能有n个人同时出席
        else printf("NO\n");
    }
    return 0;
}

/*
//ac 421ms tarjan求解scc+妻子x,丈夫x+n编号
#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 1100 //1对是2个点 1000对2000点
#define M 4000400//最多的矛盾关系 按完全图来计算 2000*2000
using namespace std;

struct Node{
    int to,next;
}edge[M];
int n,m,head[N<<1],dfn[N<<1],low[N<<1],num,cnt,block[N<<1],id,in[N<<1];
stack<int> s;
void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}
//Tarjan SCC 缩点  O(V+E)
void dfs(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);

    }
    if(low[u] == dfn[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            block[v]=id;
        }while(v!=u);
    }
}

bool judge(){
    for(int i=0;i<2*n;i++)//总共n对夫妻 2n个点 编号0~(2n-1)
        if(!dfn[i]) dfs(i);
    for(int i=0;i<n;i++)//这里枚举的是夫妻的对数编号
        //若妻子和丈夫同时出席,则一定含有矛盾关系的人也都会出席,因为妻子丈夫同时出席正是由于有矛盾关系人同时出席导致的
        if(block[i] == block[i+n]) return false;
    return true;
}

int main(){
    int a1,a2,c1,c2;
    while(scanf("%d",&n)!=EOF){
        id=num=cnt=0;
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(block,0,sizeof(block));
        memset(in,0,sizeof(in));
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d%d",&a1,&a2,&c1,&c2);//a1 a2只是那对夫妻的编号0~n-1 0代表妻子 1代表丈夫
            //a1,a1+n是构造一堆夫妻的编号 这里a1代表妻子,a1+n代表丈夫
            addEdge(a1+c1*n,a2+(1-c2)*n);//选了a1,就一定对应的是a2的配偶,而a2配偶为a2+(1-c2)*n,因为a1 a2是矛盾关系
            addEdge(a2+c2*n,a1+(1-c1)*n);//选了a2,就一定对应a1的配偶,a1配偶为a1+(1-c1)*n,a2 a1是矛盾关系,同上
        }
        if(judge()) printf("YES\n");//n个人同时出席的实际结果并不唯一,这里只判断是否能有n个人同时出席
        else printf("NO\n");
    }
    return 0;
}
*/

/*
//ac 436ms 刘汝佳 dfs爆搜版本 暂时还未理解
#include<cstdio>
#include<cstring>
#include<vector>
#define maxn 1000 //1对是2个点 1000对2000点
using namespace std;
// 来源：刘汝佳的白书第 323 页 爆搜的效率和tarjan效率差不多 tarjan405ms 爆搜421ms  不过大多还是会选用tarjan做法
struct Twosat {
  int n;
  vector<int> g[maxn * 2];
  bool mark[maxn * 2];
  int s[maxn * 2], c;
  bool dfs(int x) {
    if (mark[x ^ 1]) return false;
    if (mark[x]) return true;
    mark[x] = true;
    s[c++] = x;
    for (int i = 0; i < (int)g[x].size(); i++)
      if (!dfs(g[x][i])) return false;
    return true;
  }
  void init(int n) {
    this->n = n;
    for (int i = 0; i < n * 2; i++) g[i].clear();
    memset(mark, 0, sizeof(mark));
  }
  void add_clause(int x, int y) {  // 这个函数随题意变化
    g[x].push_back(y ^ 1);         // 选了 x 就必须选 y^1
    g[y].push_back(x ^ 1);
  }
  bool solve() {//O(V*E)
    for (int i = 0; i < n * 2; i += 2)
      if (!mark[i] && !mark[i + 1]) {
        c = 0;
        if (!dfs(i)) {//这里为什么i结点 出矛盾了后,还要继续判定i+1结点出矛盾才能判定 整体不能有n个人同时出席？
          while (c > 0) mark[s[--c]] = false;
          if (!dfs(i + 1)) return false;
        }
      }
    return true;
  }
}tmp;

int main(){
    int n,m,a1,a2,c1,c2;
    while(scanf("%d",&n)!=EOF){
        tmp.init(n);
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d%d",&a1,&a2,&c1,&c2);//a1 a2只是那对夫妻的编号0~n-1 0代表妻子 1代表丈夫
            a1=a1*2+c1;//a1*2是构造一堆夫妻的编号 2个点时紧挨着的 奇数是妻子,偶数是丈夫
            a2=a2*2+c2;
            tmp.add_clause(a1,a2);
            tmp.add_clause(a2,a1);
        }
        if(tmp.solve()) printf("YES\n");//n个人同时出席的实际结果 并不唯一,这里只判断是否能有n个人同时出席
        else printf("NO\n");
    }
    return 0;
}
*/
