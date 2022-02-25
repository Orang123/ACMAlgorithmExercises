#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100100
using namespace std;
int head[N],fa[N][20],lg[N],dep[N],cnt;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to]};
    head[to]=cnt++;
}

void dfs(int u,int fath){
    dep[u]=dep[fath]+1;
    fa[u][0]=fath;
    for(int i=1;i<=lg[dep[u]];i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fath)
            dfs(v,u);
    }
}

int lca(int x,int y){
    if(dep[x]<dep[y])
        swap(x,y);
    while(dep[x]>dep[y])
        x=fa[x][lg[dep[x]-dep[y]]];
    if(x == y) return x;
    for(int i=lg[dep[x]];i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

bool inPath(int x,int a,int b,int c){
    /*
    ����·����lca����Ȳ��ܱ���һ��·����lca���С,��С��,
    ��Ȼ����lca(x,a) == x || lca(x,b) == x,��ʵ�ʲ�û�н���
    */
    if(dep[x]<dep[c]) return false;
    return lca(x,a) == x || lca(x,b) == x;
}

/*
Ҳ�ɷֱ��ж�����·���ϵ�lca����һ��·���ϵ����˵��lca�Ƿ�����Լ�����·���ϵ�lca
�����,��˵������·����lca����һ��·����,������·���н���.
*/
bool judge(int a,int b,int c,int d){
    int e=lca(a,b),f=lca(c,d);
    if(inPath(e,c,d,f) || inPath(f,a,b,e)) return true;
    else return false;
}

int main(){
    int n,q,u,v,a,b,c,d;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&q);
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    dep[0]=-1;
    dfs(1,0);
    while(q--){
        scanf("%d%d%d%d",&a,&b,&c,&d);
        if(judge(a,b,c,d)) printf("Y\n");
        else printf("N\n");
    }
    return 0;
}
