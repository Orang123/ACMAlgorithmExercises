#include<cstdio>
#include<cstring>
#include<queue>
#define N 550
#define M 1000
using namespace std;
struct node{
    int to,next;
}edge[M];
int n,m,head[N],cnt,inde[N],arr[N];
/*
拓扑排序有两种思维,分别是Kahn算法、dfs算法,本题采用Kahn算法 是从更新入度为0的点考虑的,也更为广泛使用,dfs是通过拓扑排序最后一个点一定是出度为0的点这个角度考虑的,dfs可能要每个点都尝试,只要还没访问过
*/
void addEdge(int from,int to){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}
//O(v+E)
bool toposort(){
    /*对于拓扑排序而言 同时刻入度为0的点排序编号前后无所谓,无论是用队列或栈结果都是对的*/
    priority_queue<int,vector<int>,greater<int> > Q;//小根堆 题目要求同时刻入度为0时 序号较小的排在前面
    int index=0;
    for(int i=1;i<=n;i++)
        if(!inde[i])//初始化 将刚开始入度为0的点 作为排在最前面的
            Q.push(i);
    while(!Q.empty()){//O(V)
        int u=Q.top();
        arr[++index]=u;
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){//累计为O(E)
            int v=edge[i].to;
            if(!--inde[v])//将u点所连接的边的端点的入度都减1,当端点入度为0时,进入队列,说明它的前置条件都已达到,现在它也可以完成了,排在后面的次序
                Q.push(v);
        }
    }
    /*正常如果是DAG(有向无环图) 最终弹出堆的元素个数应为所有点的个数,若有环,
    则这个环的路径上的点都无法确定它们之间的前置 后置条件,没有一个点的入度会为0,
    因此无法入队列,a是b的前置条件,b也是a的前置条件,相互矛盾*/
    if(index < n)
        return false;
    return true;//DAG所有点都可入堆,都可排序
}

int main(){
    int a,b;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(inde,0,sizeof(inde));
        memset(head,-1,sizeof(head));
        cnt=0;
        while(m--){
            scanf("%d%d",&a,&b);
            addEdge(a,b);
            inde[b]++;
        }
        if(toposort()){
            printf("%d",arr[1]);
            for(int i=2;i<=n;i++)
                printf(" %d",arr[i]);
            printf("\n");
        }
        else
            printf("原图中含有回路无法排序\n");
    }
    return 0;
}
/*dfs版本 洛谷P2883
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
        if(!--inde[v])
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
            vis[i]=1;
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

*/

