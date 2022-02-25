#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
#define M 5000
#define INF 0x3f3f3f3f
using namespace std;
int n,m,fa[N];
//kruskal 130ms
/*
题意:求解一棵生成树中最大边权与最小边权之差的最小值.
链接:https://www.luogu.com.cn/problem/UVA1395
思路:先对边升序排序,枚举边集左边界的起点l,代表最小边权,
从左边界起点开始kruskal加边,当边数达到n-1时,此时第n-1条边
就是右边界,记录其最大边权减左边界边权,求取差值最小值即可.
实际的边集个数可能要小于完全图的边数,因为是O(n^2)复杂度
*/

struct Edge{
    int u,v,w;
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    sort(edge+1,edge+1+m);
    int x,y,num,maxd=INF,flag=0;;
    for(int l=1;l<=m;l++){//枚举左边界
        num=0;
        init();
        if(l+n-2>m) break;//当左边界起点+n-1条边超过边数总和时就退出
        for(int r=l;r<=m;r++){
            x=find(edge[r].u);
            y=find(edge[r].v);
            if(x!=y){
                fa[x]=y;
                num++;
                if(num == n-1){//到达右边界
                    flag=1;
                    maxd=min(maxd,edge[r].w-edge[l].w);//记录最小差值
                }
            }
        }
    }
    if(!flag) maxd=-1;
    return maxd;
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        printf("%d\n",kruskal());
    }
    return 0;
}

/*
试试lca的做法
*/
