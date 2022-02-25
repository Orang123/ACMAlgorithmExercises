#include<cstdio>
#include<iostream>
#include<vector>
#include<map>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;
//171ms �Ż�����
/*
����:n������,m����ϵ,��ϵ�����Է���,����u->v����v->u,
ÿ����ϵ��������Ϊ1,����Ҫ�����Ĺ�ϵ��,�������һ��
�˺�ĳ���˲����ڹ�ϵ��,�����-1.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4460
˼·:���Դ�ÿ����u,bfs��ʼ,���u�����������̾���,�Ƚ����������,
n��bfsʱ��� O(n^2),�������ac786ms,��ʵ����һ������ͼ������֮�����Զ����,
��������������ֱ����˼·ȥ���,����bfs,һ�δ�u��bfs��������ĵ�v,�ڶ���
��v�㿪ʼbfs�����Զ����dis,���dis���������ͨͼ�е���Զ����,�����������,������
�������,vis1,vis2,vis1�����Щ�㱻���ʱ���,�����ѷ��ʵĵ㲻��bfs,vis2�Ƕ���ÿ����ͨͼ,
bfsʱ�ı������,���������bfs����vis1δ�����,��˵��ԭͼ�ǲ���ͨ��,�����-1.
*/

int n,m,cnt,vis1[N],vis2[N],dis[N],ans;
map<string,int> mp;
//������������ֱ�����Ż���������ʽǰ���ǻ�wa,ԭ����
vector<int> G[N];

void init(int s){
    memset(vis2,0,sizeof(vis2));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

int bfs(int s){
    int res=s;
    init(s);
    queue <int>Q;
    vis1[s]=vis2[s]=1;
    Q.push(s);
    /*
    ���ﲻ��ֱ����ans��¼��Զ����,�������ܵ�һ��bfs���Ѿ������Զ����,
    ���ڶ���bfsû�б�ans�����,��᷵�س�ʼ��s,dis[s]=0,�𰸻����.
    */
    int u,v,maxdis=0;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        if(maxdis<dis[u]){
            maxdis=dis[u];
            res=u;
            ans=max(ans,maxdis);
        }
        for(int i=0;i<G[u].size();i++){
            v=G[u][i];
            if(!vis2[v]){
                dis[v]=dis[u]+1;
                vis1[v]=vis2[v]=1;//����vis�����
                Q.push(v);
            }
        }
    }
    return res;
}

int work(int i){
    int u=bfs(i);//��i�㿪ʼbfs,��������i����Զ�ĵ�u
    //��u�㿪ʼbfs,��������i����Զ�ĵ�v,dis[v]���Ǵ���ͨͼ�����е�Լ����Զ����
    int v=bfs(u);
    return dis[v];
}

int main(){
    int u,v;
    string str1,str2;
    while(scanf("%d",&n)&&n){
        ans=cnt=0;
        mp.clear();
        memset(vis1,0,sizeof(vis1));
        for(int i=1;i<=n;i++){
            cin >> str1;
            mp[str1]=i;
            G[i].clear();
        }
        scanf("%d",&m);
        while(m--){
            cin >> str1 >> str2;
            u=mp[str1],v=mp[str2];
            G[u].push_back(v);
            G[v].push_back(u);
        }
        work(1);//�ӵ�1��ʼ ����bfs.
        for(int i=2;i<=n;i++){
            if(!vis1[i]){//�����е�û���� ��ԭͼ����ͨ���-1
                ans=-1;
                break;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

/*
//748ms n��bfs  O(n^2)
#include<cstdio>
#include<iostream>
#include<map>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],vis[N],dis[N],ans;
map<string,int> mp;
struct Node{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}


void init(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
        dis[i]=(i==s?0:INF);
}

void bfs(int s){
    init(s);
    queue <int>Q;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v]){
                dis[v]=dis[u]+1;
                vis[v]=1;
                Q.push(v);
            }
        }
    }
}

int main(){
    int u,v;
    string str1,str2;
    while(scanf("%d",&n)&&n){
        ans=cnt=0;
        mp.clear();
        memset(vis,0,sizeof(vis));
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++){
            cin >> str1;
            mp[str1]=i;
        }
        scanf("%d",&m);
        while(m--){
            cin >> str1 >> str2;
            u=mp[str1],v=mp[str2];
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=1;i<=n;i++){
            bfs(i);
            for(int j=1;j<=n;j++)
                ans=max(ans,dis[j]);
        }
        if(ans == INF) printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}
*/
