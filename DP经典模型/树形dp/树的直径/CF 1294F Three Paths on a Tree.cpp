#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200100
using namespace std;

/*
题意:求一棵n个节点的树,选出三个节点使其三点连成的路径边相并的值最大.
链接:https://codeforces.ml/problemset/problem/1294/F
思路:三个点构成的路径中一定含有树的直径,所以先求出直径的两个端点,
再在其余节点中选取距离直径两端点距离和最大的一点.
*/

int cnt,n,head[N],dis1[N],dis2[N],ans,st,d;

struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    if(dis1[u]>=ans){//这里必须是大于等于,因为第二次dfs,有可能找不到比之前更大的ans,但是直径的另一个端点还是需要记录的
        ans=dis1[u];
        st=u;
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dis1[v]=dis1[u]+1;
        dfs(v,u);
    }
}

int main(){
    int u,v,a,b,c;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    ans=-1;
    dfs(1,-1);
    a=st;
    dis1[st]=0;
    dfs(st,-1);//搜索直径
    b=st;
    d=ans;
    for(int i=1;i<=n;i++)
        dis2[i]=dis1[i];//dis2记录距离直径a端点的距离
    dis1[st]=0;
    dfs(st,-1);//dis1记录距离直径b端点的距离
    dis1[st]=0;
    ans=-1;
    for(int i=1;i<=n;i++){
        if(i == a || i == b) continue;//有可能树本身是一条直链,选取的三个点都是不同的三个点,直链有可能会选取2个相同的点但结果仍然是最大的
        if(dis1[i]+dis2[i]+d>ans){
            ans=dis1[i]+dis2[i]+d;
            c=i;
        }
    }
    printf("%d\n",ans/2);//只计算实际路径边的并集权,而dis1[i]+dis2[i]+d刚好重复计算了2遍
    printf("%d %d %d\n",a,b,c);
    return 0;
}
