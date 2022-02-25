#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
//ac 202ms ����dp O(V+E)
/*
����:һ�������εĳ���,ÿ������֮��ĵ�·��Ҫ��ʿ������,ʿ���������ڵ�·�Ľ�����,
ʿ����ͬʱ�������ڵ����е�·,�����ٷ��ü���ʿ�����Կ��������е�·.
����:����һ���� �þ������ٵĵ㸲�����еı�.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1054
˼·:����dp O(V+E) dp[i][0] dp[i][1]�ֱ���� ���i������ʿ���ͽ��i����ʿ���������������е�·��Ҫ���õ�����ʿ����.
Ҳ����ת��Ϊ����ͼ�е� ��С���㸲��=���ƥ�� O(VE)
*/

int head[1600],cnt,dp[1600][2];
struct Node{
    int to,next;
}edge[3200];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}
//O(V+E)
void dfs(int u,int fa){
    dp[u][0]=0;//������
    dp[u][1]=1;//���� �����Լ�����
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v==fa) continue;
        dfs(v,u);
        dp[u][0]+=dp[v][1];//���õ㲻����ʿ����u->v�����߱�Ȼ��Ҫv������ʿ������,����v��һ��Ҫ����ʿ��
        /*
        ��u�����������,v�㲻���ò�һ����v�㲻���ô𰸸���.
        ����u->v v->a v->b v->c v->d  ���u�����v�㲻����ʿ��,
        ��ôa b c d�ĸ��㶼��Ҫ����ʿ��,�������v��Ҳ����ʿ��,
        a b c d�ĸ���㶼����Ҫ����ʿ��.
        */
	//���õ����ʿ��,��v��ɷ���Ҳ�ɲ�����
	//����v����Ӻܶ�,��ôv�����ʿ��,v�ĺܶ���ӾͲ��ط�,���v���һ������,��ôv��Ϳ��Բ���,��v�Ķ�������
        dp[u][1]+=min(dp[v][0],dp[v][1]);
    }
}

int main(){
    int n,m,u,v;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        while(n--){
            scanf("%d:(%d)",&u,&m);
            while(m--){
                scanf("%d",&v);
                addEdge(u,v);
                addEdge(v,u);
            }
        }
        dfs(0,-1);
        printf("%d\n",min(dp[0][0],dp[0][1]));
    }
    return 0;
}
/*
//ac 202ms ���仯����
//u�㲻����ʿ��dp[u][0]�ͷ���ʿ��dp[u][1] ��������֧�нڵ�v
//������2��״̬,Ҫô����ʿ��dp[v][1],Ҫô������ʿ��dp[v][0],���Զ����ص�������ֻ�����һ��.
//����dp�ǻ�����ص��������
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int head[1600],cnt,dp[1600][2];
struct Node{
    int to,next;
}edge[3200];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

int dfs(int u,int k,int fa){
    int ans=k;
    if(dp[u][k]) return dp[u][k];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v==fa) continue;
        if(k)//����k==0 ��k==1��� dfs(v,1,u)���ظ�����.���Կ�ͷҪif(dp[u][k]) �ж�
            ans+=min(dfs(v,0,u),dfs(v,1,u));
        else
            ans+=dfs(v,1,u);

    }
    return dp[u][k]=ans;
}

int main(){
    int n,m,u,v;
    while(scanf("%d",&n)!=EOF){
        cnt=0;
        memset(dp,0,sizeof(dp));
        memset(head,-1,sizeof(head));
        while(n--){
            scanf("%d:(%d)",&u,&m);
            while(m--){
                scanf("%d",&v);
                addEdge(u,v);
                addEdge(v,u);
            }
        }
        printf("%d\n",min(dfs(0,0,-1),dfs(0,1,-1)));
    }
    return 0;
}
*/

/*
//ac 202ms ��С���㸲��=���ƥ�� ʱ����Ż���hungary �ͽ���Ⱦɫ�����ּ��� ֧���һ�������еĵ�
//O(VE)
#include<cstdio>
#include<cstring>
#define N 2000

int n,m,cnt,head[N],color[N],vis[N],link[N],ans;
struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa,int col){
    color[u]=col;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        dfs(v,u,col^1);
    }
}

int hungary(int u,int clock){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v] == clock) continue;
        vis[v]=clock;
        if(link[v] == -1 || hungary(link[v],clock)){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=0;
    memset(head,-1,sizeof(head));
    memset(link,-1,sizeof(link));
    memset(vis,-1,sizeof(vis));
}

int main(){
    int u,v;
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            scanf("%d:(%d)",&u,&m);
            while(m--){
                scanf("%d",&v);
                addEdge(u,v);
                addEdge(v,u);
            }
        }
        dfs(0,-1,0);
        for(int i=0;i<n;i++){//O(VE)
            if(color[i]) continue;
            if(hungary(i,i)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 343ms ��С���㸲��=���ƥ�� �������� �����е�����,�����2
#include<cstdio>
#include<cstring>
#define N 2000

int n,m,cnt,head[N],vis[N],link[N],ans;
struct Edge{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

int hungary(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(vis[v]) continue;
        vis[v]=1;
        if(link[v] == -1 || hungary(link[v])){
            link[v]=u;
            return 1;
        }
    }
    return 0;
}

void init(){
    cnt=ans=0;
    memset(head,-1,sizeof(head));
    memset(link,-1,sizeof(link));
}

int main(){
    int u,v;
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            scanf("%d:(%d)",&u,&m);
            while(m--){
                scanf("%d",&v);
                addEdge(u,v);
                addEdge(v,u);
            }
        }
        for(int i=0;i<n;i++){//O(VE)
            memset(vis,0,sizeof(vis));
            if(hungary(i)) ans++;
        }
        printf("%d\n",ans/2);
    }
    return 0;
}
*/
