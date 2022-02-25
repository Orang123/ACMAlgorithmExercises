#include<cstdio>
#include<cstring>
#define N 510
//ac 93ms 最大独立集 暴力建双向边,每个点考虑配对 结果除2
/*
最小顶点覆盖、最大独立集参考博客:https://www.cnblogs.com/jianglangcaijin/p/6035945.html
相关概念:
1.独立集:选出一些顶点使得这些顶点两两不相邻(无连边),则这些点构成的集合称为独立集.
2.最大独立集:找出一个包含顶点数最多的独立集称为最大独立集.
3.对于任意图G,点覆盖和独立集互补,即:独立集=顶点数-点覆盖.
证明:
因为图G任意边的两端点不会同时属于独立集,而任意一条边必然至少有一个端点
属于点覆盖集中,而点覆盖集覆盖了图G所有的边,因此从点覆盖集发出的边的另一端点,
这些点之间必然是无边连接的,所以点覆盖集的补集也就是点覆盖发出边的另一端点构成了点独立集.
对应地:最大独立集=顶点数-最小点覆盖.

4.而对于二分图中最小点覆盖=最大匹配
所以对于在二分图中最大独立集=顶点数-最小点覆盖=顶点数-最大匹配
注意:即使二分图中含有孤立点,该定理仍然成立.
5.二分图中最小边覆盖=最大独立集=顶点数-最大匹配.

6.自己通过HDU 3829和POJ 3020的草稿得出:二分图中的最小边覆盖恰巧就是最大独立集
中的点所发出的一条边构成的集合.注意的这个最大独立集点发出的一条边,需要尽可能地选
之前还没覆盖到的点作为边覆盖中的边,并不是随便选一条边,直到所有最大独立集出发的点发出
的边将所有点都覆盖,这时就构成了最小边覆盖.
证明:因为最大独立集发出的边连接的另一端点恰好就是最小顶点覆盖中的点,因此只有选择性地
选择最大独立集发出的一条边去覆盖还未覆盖的最小顶点覆盖中的点,这样最终选出的边集的端点
恰好就有最小顶点覆盖和最大独立集中的点相并构成,这恰好就是图中的所有点,因此这些边集就是
最小边覆盖.

7.对于二分图中:
最大独立集中点的个数应大于等于最小顶点覆盖中点的个数.即:最大独立集>=最小顶点覆盖.
证明:因为在二分图中最小顶点覆盖=最大匹配,而匹配中的边集之间不会含有公共顶点,
因此最大匹配<=顶点数/2,所以最小顶点覆盖<=顶点数/2,因此最大独立集>=顶点数/2,
所以最大独立集>=最小顶点覆盖.
*/

/*
题意:n只猫m只狗,有p个孩子,每个孩子都有一组喜欢和不喜欢的
动物,如果喜欢的是猫,那么讨厌的必然是狗,反之亦然.
现在需要移走一些动物,如果一个孩子喜欢的动物被保留,
不喜欢的动物被移走,那么这个孩子就是快乐的.现在要运走
哪些动物,可以使得快乐孩子的数目最多,输出最大的快乐孩子数目.
注:C代表猫,D代表狗.喜欢的动物和讨厌的动物同时存在,这个孩子仍然是不快乐的.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3829
思路:可以根据每个孩子之间的喜欢与不喜欢动物的矛盾关系建图,
如果孩子i喜欢的动物是孩子j讨厌的动物或孩子i讨厌的动物是孩子j喜欢
的动物,就建立孩子i到孩子j之间的双向边.这样建边最终建成的图中一定
是没有长度为奇数的环的,eg:1(C1D1)-2(D2C1)-3(C2D2),这种情形如果1-3
节点有连边就形成了奇数环,但是1节点和3节点喜欢和讨厌的动物都是猫狗
这样排放1和3不可能有1喜欢的猫==3讨厌的狗或1讨厌的狗==3喜欢猫这种形式,
因为喜欢的和讨厌的不是同一种类型不可能相等,因此1-3之间不可能有连边因此
不可能存在长度为奇数的环,但可以存在长度为偶数的环eg:1(C1D1)-2(D2C1)-3(C2D2)-4(D1C2),
这时1(猫狗)和4(狗猫)节点因为喜欢的和讨厌的动物是同一种类型动物,
所以1和4之间存在连边,而这时1-2-3-4-1构成环的长度为4是偶数.
因此综上所述,所建立的矛盾关系一定不存在长度为奇数的环,
因此可以将所有孩子代表的点划分成2个集合,构成二分图.
实际因为每个孩子喜欢和讨厌的动物必然是一个猫一个狗,而矛盾关系又是
喜欢和讨厌的动物相同或讨厌和喜欢的动物相同,这本身就是按照交叉染色法
构建的矛盾关系,任意相邻两点的颜色必然是不同的,所以一定可以划分为二分图.

要使得一个孩子快乐就得移走它不喜欢的动物,而二分图中的每条边代表的是一条矛盾关系,
选择移走一条边中某一端点代表的孩子不喜欢的动物,都会造成另一端点的孩子不快乐.
但是若点与点之间没有连边即没有矛盾关系,那么移走任意一个点代表人的不喜欢动物,
不可能有其它点代表的人喜欢的动物被移走,显然问题转化为求解二分图中任意两点之间
无边连接点构成集合的数目最多的那个集合,显然就是求解二分图的最大点独立集,
而最大点独立集=顶点数-最小点覆盖=顶点数-最大匹配.
*/
int n,m,p,cnt,head[N],vis[N],link[N],ans;
char str1[N][10],str2[N][10];
struct Edge{
    int to,next;
}edge[N*N*2];//极坏情况 每个人都和其余人存在矛盾关系 因此N*(N-1)*2 要建双向边

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || dfs(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=0;
    memset(head,-1,sizeof(head));
    memset(link,0,sizeof(link));
}

int main(){
    while(scanf("%d%d%d",&n,&m,&p)!=EOF){
        init();
        for(int i=1;i<=p;i++)
            scanf("%s %s",str1[i],str2[i]);
        for(int i=1;i<=p;i++){
            for(int j=i+1;j<=p;j++){//或j=1 if(i == j) continue;每次只建一个方向的i->j,i j会颠倒再建一条j->i所以也是无向图的双向边
            //如果孩子i喜欢的动物是孩子j讨厌的动物或孩子i讨厌的动物是孩子j喜欢的动物,就建立孩子i到孩子j之间的双向边.
                if(!strcmp(str1[i],str2[j]) || !strcmp(str2[i],str1[j])){
                    addEdge(i,j);
                    addEdge(j,i);
                }
            }
        }
        for(int i=1;i<=p;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        //因为是无向图每个点都考虑配对,因此除2
        printf("%d\n",p-ans/2);//最大独立集=顶点数-最小顶点覆盖=顶点数-最大匹配
    }
    return 0;
}

/*
//ac 31ms 最大独立集 交叉染色法划分2个集合,匈牙利算法只跑一个集合的最大匹配,无需除2
#include<cstdio>
#include<cstring>
#define N 510

int n,m,p,cnt,head[N],vis[N],color[N],link[N],ans;
char str1[N][10],str2[N][10];
struct Edge{
    int to,next;
}edge[N*N*2];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int col){
    color[u]=col;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(color[v]!=-1) continue;
        dfs(v,col^1);
    }
}

int hungary(int u,int clock){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v] == clock) continue;
        vis[v]=clock;
        if(!link[v] || hungary(link[v],clock)){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=0;
    memset(head,-1,sizeof(head));
    memset(link,0,sizeof(link));
    memset(color,-1,sizeof(color));
    memset(vis,0,sizeof(vis));
}

int main(){
    while(scanf("%d%d%d",&n,&m,&p)!=EOF){
        init();
        for(int i=1;i<=p;i++)
            scanf("%s %s",str1[i],str2[i]);
        for(int i=1;i<=p;i++){
            for(int j=1;j<=p;j++){
                if(i == j) continue;
                if(!strcmp(str1[i],str2[j]) || !strcmp(str2[i],str1[j]))
                    addEdge(i,j);
            }
        }
        for(int i=1;i<=p;i++){
            if(color[i] == -1)
                dfs(i,0);
        }
        for(int i=1;i<=p;i++){
            if(color[i]) continue;
            if(hungary(i,i)) ans++;
        }
        printf("%d\n",p-ans);
    }
    return 0;
}
*/
