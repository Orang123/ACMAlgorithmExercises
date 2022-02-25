#include<cstdio>
#include<functional>
#include<algorithm>
#define N 100100
#define M 100100
using namespace std;
//ac 499ms
/*
题意:一个n个节点m条双向边的图G,每条边被染成白色(边权为1)或黑色(边权为0),
现在问图G的所有生成树中有没有可能白色边的数目为一个斐波那契数,若有输出
Yes,若没有输出No.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=4786
思路:首先考虑这个生成树中白色边数目就是生成树的边权和,对于一棵生成树将未加入mst的边加入mst会产生
一个闭环,那么需要减掉闭环路径上的一条边使其再度变成一棵树,但是闭环上面黑边和白边并不能确定,
有可能只有白边也有可能只有黑边,但也有可能黑白边都有,实际白边的增加或减少还取决于所加的边颜色,
可以求出图G的最小生成树和最大生成树,那么对于最小树和最大树之间的树的状态是一定可以通过加边变环再减边
来使得白边数目减少或增加的,因为最小树和最大树提供了一个白边数目的下界和上界,如果中间树的状态不存在,那么
上下界就是无意义的.那么如果最小生成树和最大生成树权值之间存在斐波那契数,
那么这个生成树就可以通过调整使得白色边数目达到这个斐波那契数,那么就存在
fibonacci树.
*/

/*
摘自 https://blog.csdn.net/u013618229/article/details/18996219
数学归纳法证明次算法的正确性:
对图中的顶点数目进行归纳， n = 2, 显然成立；
假设n <= k时成立，下面来考虑n = k + 1时
的生成树，考虑T的任意一条黑边，去除这条黑边得到2个联通区域T1(V1)，  T2(V2),
如果{V1，V2}的割边有一条白边，替换掉即可。
否则因为存在最大值为M（大于m)的生成树， 必然在某个联通区域，不妨设为T1存在一个生成树T3，
满足T3的白边数量大于T1。下面我们来证明原图G1中必定包含一个白边数量为m(T1)+1的最小生成树,
因为v(T1) <= k, min(G1)  <= m(T1) , MAX(G1) >= m(T3)由数学归纳法知，
G1中一定存在一个白边数目大于等于min(G1)小于等于max(G1）的最小生成树，
因为m(T1) + 1 >= m(T1) >= min(G1) m(T1) + 1 <= m(T3)<=max(G1), 所以成立.
*/

int n,m,fa[N],dp[N],vis[N];

struct Edge{
    int u,v,w;
}edge[M];

bool cmp1(Edge x,Edge y){
    return x.w<y.w;
}

bool cmp2(Edge x,Edge y){
    return x.w>y.w;
}

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}

int kruskal(){
    init();
    int x,y,cnt=0,sum=0,flag=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n-1){
                flag=1;
                break;
            }
        }
    }
    if(!flag) sum=-1;
    return sum;
}

int main(){
    int T,minsum,maxsum,cas=0;
    vis[1]=dp[1]=dp[2]=1;
    for(int i=3;i<N;i++){
        dp[i]=dp[i-1]+dp[i-2];
        if(dp[i]>=N) break;
        vis[dp[i]]=1;//标记dp[i]为斐波那契数
    }
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        sort(edge+1,edge+1+m,cmp1);
        minsum=kruskal();
        if(minsum == -1){
            printf("Case #%d: No\n",cas);
            continue;
        }
        sort(edge+1,edge+1+m,cmp2);
        maxsum=kruskal();
        int flag=0;
        for(int i=minsum;i<=maxsum;i++){
            if(vis[i]){//判断i属于[minsum,maxsum]是否存在斐波那契数
                flag=1;
                break;
            }
        }
        if(flag)
            printf("Case #%d: Yes\n",cas);
        else
            printf("Case #%d: No\n",cas);
    }
    return 0;
}
/*
//线性判断斐波那契数的办法
#include<cstdio>
#include<functional>
#include<algorithm>
#define N 100100
#define M 100100
using namespace std;

int n,m,fa[N],dp[N];

struct Edge{
    int u,v,w;
}edge[M];

bool cmp1(Edge x,Edge y){
    return x.w<y.w;
}

bool cmp2(Edge x,Edge y){
    return x.w>y.w;
}

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}

int kruskal(){
    init();
    int x,y,cnt=0,sum=0,flag=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n-1){
                flag=1;
                break;
            }
        }
    }
    if(!flag) sum=-1;
    return sum;
}

int main(){
    int T,minsum,maxsum,cas=0;
    dp[1]=dp[2]=1;
    for(int i=3;i<N;i++)
        dp[i]=dp[i-1]+dp[i-2];
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        sort(edge+1,edge+1+m,cmp1);
        minsum=kruskal();
        if(minsum == -1){
            printf("Case #%d: No\n",cas);
            continue;
        }
        sort(edge+1,edge+1+m,cmp2);
        maxsum=kruskal();
        for(int i=1;i<=n;i++){
            if(dp[i] == minsum){//找到第一个比minsum大的fib 再判断它是否小于等于maxsum若是则存在,否则不存在
                printf("Case #%d: Yes\n",cas);
                break;
            }
            else if(dp[i]>minsum){
                if(dp[i]<=maxsum)
                    printf("Case #%d: Yes\n",cas);
                else//若这个数比maxsum大 后面的数会比maxsum更大 不用再比较了
                    printf("Case #%d: No\n",cas);
                break;
            }
        }
    }
    return 0;
}
*/
