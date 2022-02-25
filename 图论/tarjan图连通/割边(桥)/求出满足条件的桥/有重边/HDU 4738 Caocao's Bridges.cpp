#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define INF 0x3f3f3f3f
using namespace std;
//ac 93ms
/*
����:n������,m���Ž�n��������ͨ,ÿ��������2������,��������䲻ֹһ����,
ÿ������һ��ʿ������(�������ʿ����������Ϊ0),������Ҫը��һ����ʹ��
ԭ���첻��ͨ,ը��һ����Ӧ���ɵ�����������ڵ������ϰ���ʿ��������.
������������Ҫ�ɶ�����ȥը��,����ʹ�õ����ɢ�Ͽ�����.

����:n����,m���ߵ�����ͼ,�����ر�,ÿ������Ȩֵ,������Ҫ�ҵ�Ȩֵ��С�ĸ��.
ע��:
1.������챾��Ͳ���ͨ,����������ȥը��.
2.�����Ȩ��СΪ0,����ҲӦ��һ��ȥը��.
3.��������ڸ��,�����-1.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4738
˼·:tarjan�����ͨ����ͼ���.ע�������жϸ��ʱ��Ҫ�ж�����֮���Ƿ�
���ر�,��Ҫ�ö�ά����bridge��¼������֮�����ߵ�����.
����(i^1)!=fa����������һЩ.
*/

struct node{
    int to,next,w;
}edge[N*N];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int bridge[N+1][N+1];//��¼u-v֮�����ߵ�����
int ans;

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            //ֻ�е�u-v֮��ֻ��һ����ʱ,��û���ر�ʱ�ñ߲��Ǹ��,
            //��Ϊ�����2����,ɾ��������,����һ�����ܹ�ʹ����ͨ,
            if(dfn[u]<low[v] && bridge[u][v] == 1)
                ans=min(ans,edge[i].w);
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int n,m,a,b,w;
    while(scanf("%d%d",&n,&m) && n || m){
        cnt=num=0;
        ans=INF;
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(bridge,0,sizeof(bridge));
        while(m--){
            scanf("%d%d%d",&a,&b,&w);
            addEdge(a,b,w);
            bridge[a][b]++;//��¼a-b֮���ŵ�����
            addEdge(b,a,w);
            bridge[b][a]++;
        }
        int k=0;
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                k++;//��¼��ͨ�����ĸ���
                dfs(i,-1);
            }
        }
        if(k>1) printf("0\n");//����2����2��������ͨ����,����Ҫ��ʿ��,������Ƿֿ���
        else{
            if(ans == 0) printf("1\n");//������ŵľ�����������0,Ҳ������Ҫ��һ��ʿ��ȥ��ը
            else printf("%d\n",ans==INF?-1:ans);//��ans==INF˵��û�и��,�����-1,������������ŵľ�������
        }
    }
    return 0;
}

/*
//ac 93ms
//(i^1)!=fa �����رߵ��µ�ĳЩ�߲����Ǹ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1010
#define INF 0x3f3f3f3f
using namespace std;

struct node{
    int to,next,w;
}edge[N*N];
int head[N],cnt;
int dfn[N];
int low[N];
int num;
int ans;

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if((i^1) == fa) continue;//�����ر߸���low[u]=min(low[u],dfn[v])����u-v�����ı߲����ر�
        if(!dfn[v]){
            dfs(v,i);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
                ans=min(ans,edge[i].w);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int n,m,a,b,w;
    while(scanf("%d%d",&n,&m) && n || m){
        cnt=num=0;
        ans=INF;
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        while(m--){
            scanf("%d%d%d",&a,&b,&w);
            addEdge(a,b,w);
            addEdge(b,a,w);
        }
        int k=0;
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                k++;//��¼��ͨ�����ĸ���
                dfs(i,-1);
            }
        }
        if(k>1) printf("0\n");//����2����2��������ͨ����,����Ҫ��ʿ��,������Ƿֿ���
        else{
            if(ans == 0) printf("1\n");//������ŵľ�����������0,Ҳ������Ҫ��һ��ʿ��ȥ��ը
            else printf("%d\n",ans==INF?-1:ans);//��ans==INF˵��û�и��,�����-1,������������ŵľ�������
        }
    }
    return 0;
}
*/
