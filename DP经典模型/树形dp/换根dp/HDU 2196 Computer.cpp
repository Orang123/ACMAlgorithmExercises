#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10010
using namespace std;
typedef long long ll;

/*
ac 31ms
����:���һ�����ϸ����ڵ���������ڵ����Զ����
����:http://acm.hdu.edu.cn/showproblem.php?pid=2196
˼·:����dp
dp[u][0]����u���������������ڵ������������.
dp[u][1]����u���������������ڵ������δ����
dp[u][2]����u�����߹��ĸ��ڵ����ϵķ���������
dp[u][0],dp[u][1]��������δ���������������һ������u�ڵ�
�Ĳ�ͬ�����е�,��Ϊ�����dp[v][2]ʱ�Ƚϵ���v�ڵ�Ĳ�ͬ��֧,���������ʹδ���붼��һ��������,��ô�δ����Ҳ�޷���ʾ������.�޷��Ƚ�.
����ÿ�����Ĵ𰸾���max(dp[u][0],dp[u][2])
*/

int cnt,n,head[N],path[N];
ll dp[N][3];
struct Node{
    ll to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}
//�ӽڵ��򸸽ڵ�ת��
void dfs1(int u,int fa){
    dp[u][0]=dp[u][1]=dp[u][2]=path[u]=0;//dp[u][2]������ֻ��Ϊ����dfs2֮ǰ��һ���ʼ��
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs1(v,u);
        //��������������
        if(dp[u][0]<dp[v][0]+edge[i].w){
            //�δ������������ڲ�ͬ������·����
            dp[u][1]=dp[u][0];//ͬʱ˵����ǰ�������������Ѿ����������,��ɴδ���.
            dp[u][0]=dp[v][0]+edge[i].w;
            path[u]=v;//��¼�����������·�� ��������·��
        }//���ĳЩ�����ķ�֧������û����ǰ�������,���Ǳ�֮ǰ������δ����Ҫ��,�͸��´δ����
        else if(dp[u][1]<dp[v][0]+edge[i].w)
            dp[u][1]=dp[v][0]+edge[i].w;
    }
}
//����dp,�Ӹ��ڵ����ӽڵ�ת��
void dfs2(int u,int fa){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        //v�ڵ�������������·���� ��Ƚ�v�����ڵ�ķ����������v��u�ڵ�u�ڵ�������δ����
        if(path[u] == v) dp[v][2]=max(dp[u][2],dp[u][1])+edge[i].w;
        //��v��������������·����,��Ƚ�v�����ڵ�ķ����������v��u�ڵ�u�ڵ�������������
        else dp[v][2]=max(dp[u][2],dp[u][0])+edge[i].w;
        dfs2(v,u);//�����ǰ�游�ڵ�ķ���������,����������ӽڵ��
    }
}

int main(){
    int v,w;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=2;i<=n;i++){//�����Ǵӵ�2����㿪ʼ��v�����ߵ�
            scanf("%d%d",&v,&w);
            addEdge(i,v,w);
            addEdge(v,i,w);
        }
        dfs1(1,-1);
        dfs2(1,-1);
        for(int i=1;i<=n;i++)
            printf("%lld\n",max(dp[i][0],dp[i][2]));
    }
    return 0;
}

/*
����ֱ������
ֻ��һ��dis���� ��¼�������˵�����ֵ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10100
using namespace std;


int cnt,n,head[N],dis[N],ans,st;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}
//sum�����st������������ߵ�Ȩֵ��
void dfs(int u,int fa,int sum){
    if(sum>ans){
        st=u;
        ans=sum;
    }
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dis[v]=max(dis[v],sum+edge[i].w);//dis[v]ȡ����ֱ�����˵��������
        dfs(v,u,sum+edge[i].w);
    }
}

int main(){
    int v,w;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=2;i<=n;i++){
            scanf("%d%d",&v,&w);
            addEdge(i,v,w);
            addEdge(v,i,w);
        }
        ans=-1;
        dfs(1,-1,0);
        ans=-1;//����ֱ��Ȩֵ��û��֮ǰ��,����¼����ֱ������һ�˵�
        dfs(st,-1,0);
        dfs(st,-1,0);
        for(int i=1;i<=n;i++)
            printf("%d\n",dis[i]);
    }
    return 0;
}
*/

/*
���仯���� û����
��ͳ�ļ��仯�������� ����ÿ���㶼��Ҫ��һ��,��n���ɴ�10000,�����ᳬʱ,
��������������� mapӳ�������
#include<bits/stdc++.h>//���仯���� ac 124ms
#define MAXN 10010
using namespace std;
typedef pair<int, int > P;
vector <P > a[MAXN];
map <P, int> dp;
void Init(int n){
    dp.clear();
    for(int i = 1; i <= n; i++) a[i].clear();
}
void add_edge(int u, int v, int len){
    a[u].push_back(make_pair(v, len));
    a[v].push_back(make_pair(u, len));
}
int dfs(int now, int now_p){
    P edge = make_pair(now_p, now);
    if(dp[edge]) return dp[edge];
    for(int i = 0; i < a[now].size(); i++){
        int u = a[now][i].first, len = a[now][i].second;
        if(u == now_p) continue;
        dp[edge] = max(dp[edge], dfs(u, now) + len);
    }
    return dp[edge];
}
int main(){
    int n;
    while(scanf("%d", &n) != EOF){
        Init(n);
        int u, len;
        for(int i = 2; i <= n; i++){
            scanf("%d%d", &u, &len);
            add_edge(u, i, len);
        }
        for(int i = 1; i <= n; i++) printf("%d\n", dfs(i, -1));
    }
    return 0;
}
*/
