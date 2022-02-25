#include<cstdio>
#include<cstring>
#define N 500
using namespace std;
//ac 0ms ����ͼ��ż���ϻ��� mp��¼����ż����
/*
����ͼ���ʶ���:
�߸���:��ͼG��ÿ�����㶼��L������һ���߹���,���L��G�ı߸���.
���߸���L���κ����Ӽ�������G�ı߸���,���L��G�ļ�С�߸���.
G�ĺ��������ٵı߸��ǳ�ΪG����С�߸���,�������ߵ���Ŀ��ΪG�ı߸�����.
ͨ�׵ؽ� ��С�߸���:ʵ���Ǹ��߼�,���������ı��ܸ������еĵ�,��С�߸�����
�������Ҫ������б߼��б������ٵ�һ��.
����ͼ����С�߸���=������-���ƥ����.
*/

/*
����:һ��n*m������,��'*'��'o'���,'*'�������,'o������յ�,
����Ҫ�ڳ���'*'�Ϳյ�'o'����û�վ,һ����վ���ͬʱ����4�����ڵ�
һ��λ��,���ź�ֻ��ͬʱ����������һ��1*2��2*1λ��,����������Ҫ��
'*'��'o'����ö��ٸ���վ����ʹ�����е�'*'�����źŵ��Ա�����.
ע��:��һ������û�վ�����ź����Ҳֻ�ܸ���2��λ��,��ֻ����4�ܷ���һ��λ�ø���.
����:http://poj.org/problem?id=3020
˼·:���������ƥ��,��Ϊ���ƥ�����п��ܸ���㲢û������ƥ���еĵ㼯,
��������������������ټ����߲���ʹ�����е�'*'���ܱ�����,��˾������
���е�'*'���ɵĶ���ͼ�е���С�߸���.
������ͼ����С�߸���=������-���ƥ����
*/
int head[N],cnt;
int n,m,mp[50][12],odd,even,vis[N],link[N],num,ans;
struct Edge{
    int to,next;
}edge[N*4];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || dfs(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    ans=odd=even=num=cnt=0;
    memset(link,0,sizeof(link));
    memset(head,-1,sizeof(head));
}
int main(){
    int T;
    char x;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&x);
                if(x == '*'){
                    if((i+j) & 1) mp[i][j]=++odd;
                    else mp[i][j]=++even;
                    num++;
                }
                else
                    mp[i][j]=0;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!((i+j) & 1)) continue;
                if(j<n && mp[i][j+1])
                    addEdge(mp[i][j],mp[i][j+1]);
                if(i<n && mp[i+1][j])
                    addEdge(mp[i][j],mp[i+1][j]);
                if(j>1 && mp[i][j-1])
                    addEdge(mp[i][j],mp[i][j-1]);
                if(i>1 && mp[i-1][j])
                    addEdge(mp[i][j],mp[i-1][j]);
            }
        }
        for(int i=1;i<=odd;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",num-ans);//�����С�߸���
    }
    return 0;
}

/*
//ac 0ms ��ż����������node�����¼����,��mp��¼����
#include<cstdio>
#include<cstring>
#include<vector>
#define N 500
using namespace std;
int n,m,odd,even,vis[N],link[N],ans;
vector<int> G[N];
struct Node{
    int x,y;
    Node(int x=0,int y=0):x(x),y(y){}
}node1[N],node2[N];

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!link[v] || dfs(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

int check(int i,int j){
    if(node1[i].x == node2[j].x && node1[i].y == node2[j].y+1) return 1;
    if(node1[i].x == node2[j].x && node1[i].y == node2[j].y-1) return 1;
    if(node1[i].x == node2[j].x+1 && node1[i].y == node2[j].y) return 1;
    if(node1[i].x == node2[j].x-1 && node1[i].y == node2[j].y) return 1;
    return 0;
}

void init(){
    ans=odd=even=0;
    memset(link,0,sizeof(link));
    for(int i=1;i<N;i++) G[i].clear();
}

int main(){
    int T;
    char x;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf(" %c",&x);
                if(x == '*'){
                    if((i+j) & 1) node1[++odd]=Node(i,j);
                    else node2[++even]=Node(i,j);
                }
            }
        }
        for(int i=1;i<=odd;i++){
            for(int j=1;j<=even;j++){
                if(check(i,j))
                    G[i].push_back(j);
            }
        }
        for(int i=1;i<=odd;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",odd+even-ans);
    }
    return 0;
}
*/
