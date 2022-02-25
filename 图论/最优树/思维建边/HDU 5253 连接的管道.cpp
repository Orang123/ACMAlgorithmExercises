#include<cstdio>
#include<algorithm>
#define N 1100
#define M 1000100
using namespace std;
//kruskal ac 421ms
/*
题意:http://acm.hdu.edu.cn/showproblem.php?pid=5253
n*m个网状农田输入为农田高度,每个农田只能跟它上下左右四块相邻的农田相连通,
相邻农田之间的需要的管道长度为2农田高度差,问使得所有农田连通的最少管道长度时多少.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=5253
思路:因为每个农田只能跟它上下左右四块相邻的农田相连通,所以n*m个农田需要的管道个数
上界为n*m*2,共有n*m个点,注意建边从左至右从上至下每次建右、下2个方向的连边,避免重复建边,
之后直接kruskal去最小树即可.
*/

int n,m,k,len,fa[N*N],mp[N][N];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M<<1];

void init(){
    int k=n*m;
    for(int i=1;i<=k;i++)
        fa[i]=i;
    sort(edge+1,edge+1+len);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    init();
    int x,y,cnt=0,sum=0;
    for(int i=1;i<=len;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == k-1) break;
        }
    }
    return sum;
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        len=0;
        scanf("%d%d",&n,&m);
        k=n*m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                scanf("%d",&mp[i][j]);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(j!=m)//右边的连边到达右边界就不用建
                    edge[++len]=Edge((i-1)*m+j,(i-1)*m+j+1,abs(mp[i][j]-mp[i][j+1]));
                if(i!=n)//下边的连边到达下边界就不用建
                    edge[++len]=Edge((i-1)*m+j,i*m+j,abs(mp[i][j]-mp[i+1][j]));
            }
        }
        printf("Case #%d:\n",cas);
        printf("%d\n",kruskal());
    }
    return 0;
}
