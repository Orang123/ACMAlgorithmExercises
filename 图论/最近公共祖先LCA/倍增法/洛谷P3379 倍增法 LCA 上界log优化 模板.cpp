#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 500100
int head[N],fa[N][21],dep[N],lg[N],n,m,s,cnt;//lg[i]Ϊi��2Ϊ�׵Ķ���,ʵ�ʾ������i�����ϵ�2^k�����׵��Ͻ� ����k fa[N][21] ʵ�ʶ�ά�±�ֻ��ȡ��20 Ҳ����100W�����������Ŀ50WҪ��
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to]};
    head[to]=cnt++;
}

/*������0���,ֱ����s��Ϊ��ʼ���ڵ�����
void dfs(int u){
    for(int i=1;i<=lg[dep[u]]-1;i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa[u][0]){
            fa[v][0]=u;
            dep[v]=dep[u]+1;
            dfs(v);
        }
    }
}
*/

void dfs(int u,int fath){
    fa[u][0]=fath;
    dep[u]=dep[fath]+1;
    for(int i=1;i<=lg[dep[u]]-1;i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fath)
            dfs(v,u);
    }
}

int lca(int x, int y){
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y])
        /*
        �������dep[x]-dep[y]�����ż���Ļ�,���ڸպ�2^k�η��͵���dep[x]-dep[y],��ôֻ����һ�����ʹ��dep[x]=dep[y](�պ�����),
        ��Ϊ���� ��Ϊlg[7]-1=2���ǲ���2^3�η���(����2^3�η�������ñ�y����Ȼ�С,���ǲ������),
        �����������ֻ��������Ϊ2^2=4����ȶ�������Ծ����y���ͬ���,����ȥ���y����7-4=3�ĳ���,֮��һ��ѡ��2^1��2^0�η� ���7�Ķ����Ʊ�ʾ(111)
        ÿ����Ծ���ǲ�������ѡ��lg[dep[x]-dep[y]]-1,x��y֮�����֮�� ��2Ϊ�׶�������������������
        �ٱ��������ȿ�ʼx��y���֮��5,��ô����ѡ�õ���Զ����Ϊ2^2��2^0�η�,��5=(101)��ȷ,���������ʵʡ����2^1�η���ö��,ÿ�ζ�ö�ٵ���x��5��Ȳ�ֵ������Ծ������2�ı���,
        ���Ե��˶���Ĳ���
        */
        x=fa[x][lg[dep[x]-dep[y]]-1];//lg[dep[x]-dep[y]]-1����x��y֮�����֮����ֵ�����������������ĵ�2^k�η�������,k������Ͻ� ����x��y�����֮����ʵʱ�����,���ÿһ�εĲ���ѡ����ѡ�񾡿�������,�����Ե���һЩ�����������Ĳ���
    if(x == y) return x;
    for(int i =lg[dep[x]]-1;i>=0;i--){//lg[dep[x]]-1����x�����������������ĵ�2^k�η������ȵ� k������Ͻ�
        if(fa[x][i]!=fa[y][i]){//������ȵ�������п���������lca������,���Ի�һֱ������С����Ծ������,ֱ����Ծ�����֮��һ����λ����ʱ ����fa[x][0]
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

int main(){
    int x,y;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&x,&y);
        addEdge(x,y);
    }
    /*
    ������Ҫ��1��ʼ����,����lg[1]=1,��Ϊ����lg[i]ʱ���õ�1<<lg[i-1]�Ƿ����i,
    Ҳֻ��lg[i-1]�ȱ����ֵ��1ʱ1<<lg[i-1]�Ż����i,������յĽ������Ҫ��ȥ1,
    ����3��5��6��7��Щ����1<<lg[i-1]������i��,lg[i]����lg[i-1] ��lg[3]=lg[2],lg[5]��lg[6]��lg[7]��������lg[4].
    ����ֻ��Ϊ�˺����ĵ��ƶ�����������һ��1��
    */
    for(int i=1;i<=n;i++)
        lg[i]=lg[i-1]+(1<<lg[i-1] == i);//lg[0]=-1; lg[i]=lg[i>>1]+1; ���ֵ��ƹ�ʽ���������һ��1
    dfs(s,0);
    while(m--){
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x,y));
    }
    return 0;
}
/*
������0���,ֱ����s��Ϊ��ʼ���ڵ�����
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 500100
int head[N],fa[N][21],dep[N],lg[N],n,m,s,cnt;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to]};
    head[to]=cnt++;
}

void dfs(int u){
    for(int i=1;i<=lg[dep[u]]-1;i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa[u][0]){
            fa[v][0]=u;
            dep[v]=dep[u]+1;
            dfs(v);
        }
    }
}

int lca(int x, int y){
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y])
        x=fa[x][lg[dep[x]-dep[y]]-1];
    if(x == y) return x;
    for(int i =lg[dep[x]]-1;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

int main(){
    int x,y;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&x,&y);
        addEdge(x,y);
    }
    for(int i=1;i<=n;i++)
        lg[i]=lg[i-1]+(1<<lg[i-1] == i);
    dfs(s);
    while(m--){
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x,y));
    }
    return 0;
}
*/
