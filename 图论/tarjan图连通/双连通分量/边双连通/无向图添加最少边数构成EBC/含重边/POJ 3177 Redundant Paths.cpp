#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 5500
#define M 10100
using namespace std;
//ac 0ms tarjan������scc�����ebc
/*
����:һ������ͼ(���ر�),����Ҫ��Ӽ����߲���ʹ��ͼ��û�и��,��Ϊ��˫��ͨͼ.
ͬһ���ֶ�֮������Ѿ��ж��·��(���ر�).
����:http://poj.org/problem?id=3177
˼·:tarjan������scc���ebc.ֻ���������ر�ҲҪ��ʹ��ص����׽ڵ�,
��������low[u]=min(low[u],dfn[v]).
���رߵ�����ͬ�����ò����رߵ�����,���鲻�ܺ������ر�,�������رߵ������Դ�.
*/

int n,m,dfn[N],low[N],in[N],num,cnt,head[N],block[N],ebc_cnt,de[N];
stack<int> s;

struct Edge{
    int from,to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}
//��Ϊ������ͼ,���ͼ��������ͨ��,��ôһ��dfs���ܷ��������ebc,������dfn�����С���ڷ���ebcʱ,
//����������ѷ������ebc�ĵ���ر�,��ôlowֵ����ͱ��ѷ����dfnС,����in�ж�Ҳ���������,�������û���ر�,
//��ô�͸��������ڷ��ʵ��ѷ����ebc�ĵ�.���Կ��Բ�����in�ж��Ƿ���ջ��.
//���ԭͼ����ͨ,��ôһ����ͨ����ebc������,�ڷ�����һ����ͨ������ebcҲ���������֮ǰ�Ѿ��ֳ�ebc�еĵ�.
//����dfs����dfn[v]!=0,�ǲ���Ҫ�ж�in[v]��ջ��,���Ƕ������رߵ�������߼��Ͼ��û���Ӧ�ü���in[v]���ж�
//(��Ȼ����in�ж����Ҳ�ǶԵ�,��Ϊlowֵ����ͱ��ѷ����ebc��dfnС),û���ر��ǿ�����ȫ���ӵ�
void dfs(int u,int fa){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,i);//�����¼���Ǹ��׽ڵ��������ߵı��
            low[u]=min(low[u],low[v]);
        }
        else if(in[v] && (i^1)!=fa)//i^1���䷴���ֻҪ����֮ǰ���׽ڵ������߾Ϳ���,��Ϊ�������ر�������Ҫ�����׺��ӽڵ㿴��һ��ebc
            low[u]=min(low[u],dfn[v]);//����low[u]=min(low[u],low[v])Ҳ�ǿ��Ե�
    }
    if(dfn[u] == low[u]){//dfn��low���ʱ,˵��û�лر߻ص�ʱ�������Ľڵ�,��ʼ��ջ ����һ��EBC
        ebc_cnt++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            block[v]=ebc_cnt;//���õ�ǰ��������ebc�ı��
        }while(v!=u);
    }
}

int main(){
    int u,v,ans;
    ans=ebc_cnt=cnt=num=0;
    memset(dfn,0,sizeof dfn);
    memset(de,0,sizeof de);
    memset(head,-1,sizeof head);
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    //������ʵ��֤��ԭͼ����ͨ�� ֱ��dfs(1,-1)
    dfs(1,-1);
    for(int i=0;i<cnt;i+=2){//��Ϊ��˫���+2,���˵�ȶ�+1
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v]){
            de[block[u]]++;
            de[block[v]]++;
        }
    }
    for(int i=1;i<=ebc_cnt;i++){
        if(de[i] == 1)
            ans++;
    }
    printf("%d",(ans+1)/2);//����ԭͼ���������,ֻ�����һ����λ��ӵı߼��ɳ�Ϊ��˫��ͨͼ.
    return 0;
}
/*
�����ر�1-2 ������,�����֪Ϊʲôtarjan+���鼯�������������ر�,
����������2,ʵ��ֻ�����1����,����POJȴ��ͨ��.
input
4 4
1 2
1 2
1 3
1 4
output
1
*/
/*
//ac 0ms tarjan�����i^1!=father�����ر߹��ɵ�ebc+���鼯����ebc
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5500
#define M 10100
using namespace std;

int n,m,fa[N],dfn[N],low[N],num,cnt,cut_num,head[N],ebc_cnt,de[N];

struct Edge{
    int to,next;
    Edge(int to=0,int next=0):to(to),next(next){}
}edge[M<<1],cut_edge[M];

void addEdge(int from,int to){
    edge[cnt]=Edge(to,head[from]);
    head[from]=cnt++;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void dfs(int u,int father){
    dfn[u]=low[u]=++num;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            dfs(v,i);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])//��¼���,����dfn[u]<low[v]
                cut_edge[++cut_num]=Edge(u,v);
            else
                fa[find(u)]=find(v);//����u��vδ�ϲ�֮ǰ��Ȼ�ǲ�ͬ����,��Ϊtarjan ����㶼��δ������.
        }
        else if((i^1)!=father)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int u,v,ans;
    ans=ebc_cnt=cnt=num=0;
    memset(dfn,0,sizeof dfn);
    memset(de,0,sizeof de);
    memset(head,-1,sizeof head);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,-1);
    for(int i=1;i<=cut_num;i++){
        u=cut_edge[i].to;
        v=cut_edge[i].next;
        de[find(u)]++;//����Ͳ����ǲ��鼯���Ƚڵ�ı��,û��ȥ���ebc�ĸ���,�����n����Ķȶ���һ��
        de[find(v)]++;
    }
    for(int i=1;i<=n;i++){//����ÿ���㶼��,��Ϊ��֪������ÿ��ebc�������ȸ��ڵ�ı��
        if(de[i] == 1)
            ans++;
    }
    printf("%d",(ans+1)/2);
    return 0;
}
*/


/*
//ac 16ms tarjan�����bridge[u][v]�������ر�+���鼯����ebc
//�������bridge[u][v]��¼����,�����ر�,POJ��֪Ϊ��Ҳ����,��������������,�������Ӧ����1,������������2,�ͺ����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5500
#define M 10100
using namespace std;

int n,m,fa[N],dfn[N],low[N],num,cnt,cut_num,head[N],ebc_cnt,de[N],bridge[N][N];

struct Edge{
    int to,next;
    Edge(int to=0,int next=0):to(to),next(next){}
}edge[M<<1],cut_edge[M];

void addEdge(int from,int to){
    edge[cnt]=Edge(to,head[from]);
    head[from]=cnt++;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void dfs(int u,int father){
    dfn[u]=low[u]=++num;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v] && bridge[u][v] == 1)//��¼���,����dfn[u]<low[v]��������û���ر�,������bridge[u][v]=1
                cut_edge[++cut_num]=Edge(u,v);
            else
                fa[find(u)]=find(v);//����u��vδ�ϲ�֮ǰ��Ȼ�ǲ�ͬ����,��Ϊtarjan ����㶼��δ������.
        }
        else if(v!=father)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int u,v,ans;
    ans=ebc_cnt=cnt=num=0;
    memset(dfn,0,sizeof dfn);
    memset(de,0,sizeof de);
    memset(head,-1,sizeof head);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
        bridge[u][v]++;
        bridge[v][u]++;
    }
    dfs(1,-1);
    for(int i=1;i<=cut_num;i++){
        u=cut_edge[i].to;
        v=cut_edge[i].next;
        de[find(u)]++;//����Ͳ����ǲ��鼯���Ƚڵ�ı��,û��ȥ���ebc�ĸ���,�����n����Ķȶ���һ��
        de[find(v)]++;
    }
    for(int i=1;i<=n;i++){//����ÿ���㶼��,��Ϊ��֪������ÿ��ebc�������ȸ��ڵ�ı��
        if(de[i] == 1)
            ans++;
    }
    printf("%d",(ans+1)/2);
    return 0;
}
*/
