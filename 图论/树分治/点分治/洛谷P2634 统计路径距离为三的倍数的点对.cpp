#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 20100
#define M 110
using namespace std;
int head[N],cnt,siz[N],maxn[N],vis[N],sum,rt,dis[N],num[3],ans;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void getrt(int u,int fa){
    siz[u]=1;
    maxn[u]=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa && !vis[v]){
            getrt(v,u);
            siz[u]+=siz[v];
            maxn[u]=max(maxn[u],siz[v]);
        }
    }
    maxn[u]=max(maxn[u],sum-siz[u]);
    if(maxn[u]<maxn[rt]) rt=u;
}

void getdis(int u,int fa){
    num[dis[u]]++;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa && !vis[v]){
            dis[v]=(dis[u]+edge[i].w)%3;
            getdis(v,u);
        }
    }
}

int calc(int u,int d){
    num[0]=num[1]=num[2]=0;
    dis[u]=d%3;
    getdis(u,0);
    /*
    num[0]代表从重心开始增长路径距离和本身就是3的倍数的个数 num[0]*num[0]是点对的个数
    num[1]代表从重心开始增长路径距离和取模3余1的增长路径的个数
    num[1]代表从重心开始增长路径距离和取模3余2的增长路径的个数
    num[1]*num[2]*2是余1的路径和余2的路径拼接构成的路径距离为3的倍数的点对的个数
    这里求解余1和余2路径拼接构成距离为3的倍数的点对,某个点对若满足,则它的对位点对,
    即颠倒过来也满足,*2就是这个目的.
    */
    return num[0]*num[0]+num[1]*num[2]*2;
}

void divide(int u){
    vis[u]=1;
    ans+=calc(u,0);//第一次从重心计算的这个结果值会多出来. 从点自身自环开始统计,而这一个0是为了解决掉一些，有重复计算的结果
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!vis[v]){
            ans-=calc(v,edge[i].w);//第二次从子节点v开始,ans再减去多出来的值 减去重复的路径距离为3的倍数的点的自环那一部分 类似与容斥原理
            maxn[rt=0]=sum=siz[v];
            getrt(v,0);
            getrt(rt,0);
            divide(rt);
        }
    }
}

int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}

int main(){
    int n,u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    maxn[0]=sum=n;
    getrt(1,0);
    getrt(rt,0);
    divide(rt);
    int k=gcd(ans,n*n);//n*n代表所有点对 所构成的路径个数 包括点自身的自环
    printf("%d/%d\n",ans/k,n*n/k);
    return 0;
}
