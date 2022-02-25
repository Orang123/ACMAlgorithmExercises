#include<cstdio>
#include<cstring>
#define N 110
#define M 1100
using namespace std;
//ac 0ms 最小顶点覆盖
/*
题意:2个机器A、B分别有n、m种模式,模式编号为0~n-1和0~m-1,
初始时2台机器都处于模式0,有k个作业,每个作业i由一个三元组
(i,u,v)来表示代表作业i可在A机器的模式u运转或B机器的模式v运转,
但是每次调整机器的工作模式都需要手动重启,现在问至少需要重启
多少次机器才能完成所有作业.
链接:http://poj.org/problem?id=1325
思路:摘自https://blog.csdn.net/wangjian8006/article/details/7963546
A,B两台机器构成一个二分图,左边代表A机器,
有n个点,代表有n个模式右边代表B机器,有m个点,
代表有m个模式,现在对于每个作业,i,a,b都使左边
a点指向右边b点即可,这样如果我们要把所有的作业做完,
是不是找出最小的点覆盖将所有的边都覆盖掉即可,
然后最小点覆盖等于最大匹配.

注意:机器初始状态在模式0,对于作业运转处于模式0的情况不建边.
*/
int n,m,k,cnt,head[N],vis[N],match[N],ans;
struct Edge{
    int to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(match[v] == -1 || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=0;
    memset(match,-1,sizeof(match));
    memset(head,-1,sizeof(head));
}

int main(){
    int i,u,v;
    while(scanf("%d",&n) && n){
        scanf("%d%d",&m,&k);
        init();
        while(k--){
            scanf("%d%d%d",&i,&u,&v);
            //实际只判断!v即可,因为重启机器是由A机器到B机器切换,而B机器初始在模式0
            if(!u || !v) continue;//机器初始状态在模式0,对于作业运转处于模式0的情况不建边.
            addEdge(u,v);
        }
        for(int i=1;i<n;i++){//A机器的模式范围0~n-1 因为A机器初始状态就是模式0,所以不考虑状态0.
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
