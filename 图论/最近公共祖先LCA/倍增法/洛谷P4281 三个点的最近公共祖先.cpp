#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 500100
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

int dis(int x,int y){
    int z=lca(x,y);
    return dep[x]+dep[y]-2*dep[z];
}

int main(){
    int n,m,a,b,x,y,z,xyz;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    lg[0]=-1;
    for(int i=1;i<=n;i++)
        lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&a,&b);
        addEdge(a,b);
    }
    dep[0]=-1;
    dfs(1,0);
    while(m--){
        scanf("%d%d%d",&x,&y,&z);
        //�����������tarjan�ͺ��鷳,��Ϊÿ���ش�Ҫ�õ�����lca,���ֲ�������鷳
        int xy=lca(x,y);
        int yz=lca(y,z);
        int xz=lca(x,z);
        /*
        ��ʵ��Ŀ�����,׼ȷ�����������������lca,
        ���Ǿ���������������Ǹ��㣬ʹ�����������õ�
        �����ܺ���С�����ϻ�����͵ĵ�.
        ��������������ת��Ϊlca����.
        ����������lca,��Ȼ���������lca����ͬ��,
        ��ô���������������ĵ�ͱ�Ȼ������֮�ⲻͬ������2�����lca
        */
        if(xy == yz) xyz=xz;
        else if(xy == xz) xyz=yz;
        else if(yz == xz) xyz=xy;
        printf("%d %d\n",xyz,dis(x,xyz)+dis(y,xyz)+dis(z,xyz));//���������ֱ����ü��ϵ�ľ���֮��
        /*
        Ҳ���Բ��������Ⱥ�lca���֮��Ĺ�ϵ,���������������֮���ٰ��غ�����lca��Ⱦ����޳���.
        */
        //printf("%d %d\n",xyz,dep[x]+dep[y]+dep[z]-dep[xy]-dep[yz]-dep[xz]);
    }
    return 0;
}
