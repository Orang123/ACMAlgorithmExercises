#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define N 100100
#define M 100100
#define INF 0x3f3f3f3f
using namespace std;
//ac 274ms ���㹹��DAG�ϵķֲ�ͼ(˼ά����)+spfa�ҵ���(block[1]+id)����Ȩ�͵�·��
/*
����:Լ����n��ݳ�,���1��n,��Щ�ݳ������������е�����.
��ţ��������ζ���ݵļ��ͼ�,���뵽�ﾡ���ܶ�Ĳݳ�ȥƷ������.
�������Ǵ�1�Ųݳ�����,���ص�1�Ųݳ�.���뾭�������ܶ�Ĳݳ�,
������ͨһ���ݳ�ֻ��һ�β�,����һ���ݳ����Ծ������,��Ϊ�ݳ��ǵ��е�����,
���������Ʒ�����������˺ܴ�Ĳ���,������͵͵��������һ��,
�����ֻ����һ������.��,��������ܳԵ����ٸ��ݳ�������.
����:https://www.luogu.com.cn/problem/P3119
˼·:��Ϊֻ������һ��,���Կ��Կ��ǹ���ֲ�ͼ,����Ϊ�˼��ٸ��Ӷ�,��Ҫ������
ȥ����,�����ڹ���DAG��ͬʱ����2��ķֲ�ͼ����,���spfa�ܵ���(block[1]+id)��
����Ȩ��,����Ϊ�˱���ص�1���ڵ�sccʱ��Ȩ�ظ��ۼ�,�����ڸ��µ�Ȩ��ʱ�Ӻ��ۼ�,
�����ȱ����˵�Ȩ�ظ��ۼ�,Ҳ����˵�ʹ��һ����������ߵ��ֲ�ͼi+n��ŵĵ㽫֮ǰ�Ѿ�
�ۼӹ���Ȩ�ĵ��ظ��ۼӵ�����.
��Ҫע����Ƕ���ԭͼ�������ǿ��ͨͼʱ,��Ҫ����,��Ϊ�ӳ��ۼӵ�Ȩ������һ���ڵ���ۼ�
��ǰ�����ĵ�Ȩ,������û�б�,����Ҫ����ֱ�����block[1]�е���,����ֱ���ٹ���һ��,
block[1]����(block[1]+id)(�ڶ���ͼ�е�1����scc).
*/
//���������k��������ߵĻ���,�ǻ���ֻ���÷ֲ�ͼ�İ취,�����ٿ��Ƿ��򽨱�������spfaö�����,
//����ö����Ҫö�ٺü���������,�ͺü���ѭ��
//��ΪҪ����2��DAG,��������Ҫ����2N
int n,m,head[N],cnt;
int id,dfn[N],low[N],clock,block[N],num[N<<1],vis[N<<1],dis[N<<1];
stack<int> s;
vector<int> G[N<<1];

struct Edge{
    int from,to,next;
}edge[M*3];//����ͼ+�м������� 3M

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(block[v]) continue;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            num[id]++;
        }while(v!=u);
    }
}

void spfa(int s){
    queue<int> Q;
    vis[s]=1;
    //��ʼ��Ȩ�����ۼ�,Ϊ�˱����ظ��ۼ�
    Q.push(s);
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int v : G[u]){
            //�ӳ��ۼӵ�Ȩ,����v��ʱ �ۼӵ���ǰ��u�ĵ�Ȩ,���Ա���ص�block[1]+idʱblock[1]��Ȩ�ظ��ۼ�
            //��ʵҲ�����ۼ�num[v]�ĵ�Ȩ,�����ص�block[1]ʱ,�Ϳ��԰ѳ�ʼʱû�ۼӵ�block[1]����,
            //ֻ����������û�лص�block[1]��·�����ټ���block[1]�ĵ�Ȩ
            if(dis[v]<dis[u]+num[u]){
                dis[v]=dis[u]+num[u];
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++){//���һ��Ҫ�����е㶼���scc,��Ϊ������һ�������
        if(!dfn[i])
            tarjan(i);
    }
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v]){
            G[block[u]].push_back(block[v]);
            G[block[u]+id].push_back(block[v]+id);//�ڶ���DAG
            G[block[v]].push_back(block[u]+id);//�����������
            num[block[u]+id]=num[block[u]];//��ʼ���ڶ���ͼ�ĵ�Ȩ
            num[block[v]+id]=num[block[v]];
        }
    }
    //��ԭͼ�������ǿ��ͨͼʱ,1���ڵ�scc�ĸ������Ǵ�,����Ϊ��Ȩ���Ӻ��ۼӵ�,
    //����Ҫֱ�ӹ���һ��block[1]��block[1]+id�ı�,������Ȩ�����ۼӵ�block[1]+id��.
    G[block[1]].push_back(block[1]+id);
    //num[block[1]+id]=num[block[1]];//����ǵ��ӳټӵ�Ȩ �ӵ���num[v]��Ҫ��ʼ��num[block[1]+id],����ԭͼΪSCGʱ���Ϊ0
    spfa(block[1]);
    printf("%d",dis[block[1]+id]);//����Ҫ��ص�block[1],��Ϊ��DAG,��ôdis[block[1]+id]���Ǵ�
    return 0;
}

/*
//tarjan����DAG+������dp��·������Ȩ�� ������
//�����Ŀ��Ϊ������1�������,����Ҫ����ͼ��Ҫtarjan����scc����DAG,���һ�Ҫ���s����,�����޷������������,
//��Ϊ���е��DAG��������,��Щ��1���޷������,����������Ϊ0���ʼ��,�����޷���֤�������Ƿ���s,���Խ�����;
//���ֻ��s�����,��ô�������ȿ������м������Զ��Ϊ0
*/

/*
//ac 274ms �ֲ�ͼ��dpö��״̬��ʽ
//ע�����ﲻ����Dijkstra(),��Ϊ��������������Ȩ��,�����ȶ����ȵ����� �Ͳ����ٸ�����,
//���������ܻ��и��ŵ�,������Ϊbfs�������������Ȩ����ì�ܵ��µ�
#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define N 100100
#define M 100100
#define INF 0x3f3f3f3f

using namespace std;
int n,m,head[N],cnt;
//dis[u][0]������u�㲻��������ܳԵ�������
//dis[u][1]������u��ֻ��1��������ܳԵ�������
int id,dfn[N],low[N],clock,block[N],num[N],vis[N][2],dis[N][2];
stack<int> s;
//first��ʾ���� ��ı�� second��ʾ�ߵķ���,0��������,1����ʵ�ʲ����ڵ������
vector<pair<int,int> > G[N];

struct Edge{
    int from,to,next;
}edge[M];
struct state{
    int u,cnt;//cnt�ǵ�ǰ���˼��������cnt<=1
    state(int u=0,int cnt=0):u(u),cnt(cnt){}
};

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(block[v]) continue;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            num[id]++;
        }while(v!=u);
    }
}

void spfa(int s){
    queue<state> Q;
    vis[s][0]=1;
    //���ﲢû���ۼӳ�ʼblock[1]�ĵ�Ȩ,��Ϊ����ӵ���num[v],
    //�ص���ʼ��block[1]ʱ�Ჹ�Ͽ�ʼû�ۼӵ�num[block[1]]�����ظ��ۼ�
    Q.push(state(s,0));
    state tmp;
    int u,v,nowcnt,flag;
    while(!Q.empty()){
        tmp=Q.front();
        u=tmp.u,nowcnt=tmp.cnt;
        Q.pop();
        vis[u][nowcnt]=0;
        for(pair<int,int> e : G[u]){
            v=e.first,flag=e.second;
            //����� ֻҪȨֵ���ܸ��¸���͸���
            if(!flag && dis[v][nowcnt]<dis[u][nowcnt]+num[v]){//�����ӳټӵ�Ȩ���Լ�num[u]
                dis[v][nowcnt]=dis[u][nowcnt]+num[v];
                if(!vis[v][nowcnt]){
                    vis[v][nowcnt]=1;
                    Q.push(state(v,nowcnt));
                }
            }
            //����� ��ǰ������ߵĴ�����Ϊ0 ����Ȩֵ�ͻ��ܸ���Ÿ���
            else if(flag && !nowcnt && dis[v][nowcnt+1]<dis[u][nowcnt]+num[v]){
                dis[v][nowcnt+1]=dis[u][nowcnt]+num[v];//dis[v][nowcnt+1] ����v����ͨ����һ�������ʵ��
                if(!vis[v][nowcnt+1]){
                    vis[v][nowcnt+1]=1;
                    Q.push(state(v,nowcnt+1));
                }
            }
        }
    }
}

int main(){
    int u,v;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i);
    }
    if(id == 1){
        printf("%d",num[1]);
        return 0;
    }
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v]){//����DAG
            G[block[u]].push_back(make_pair(block[v],0));//������� ���0
            G[block[v]].push_back(make_pair(block[u],1));//������� ���1
        }
    }
    spfa(block[1]);
    printf("%d",dis[block[1]][1]);
    return 0;
}
*/

/*
//ac 220ms ���򽨱�,������spfa,Ȼ��ö��ÿһ���� ����������
//dis1[block[v]]+dis2[block[u]]-num[block[1]] ���Ǵ�,�������block[1]���ۼ�������,
//������ǲ����ظ��ۼӵ�,��Ϊ�Ѿ����㹹���DAG,������е��ظ��ۼ�,����ֻ���,��Ȼ��ǰ��DAG��ì��.
#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define N 100100
#define M 100100
#define INF 0x3f3f3f3f

using namespace std;
int n,m,head[N],cnt;
int id,dfn[N],low[N],clock,block[N],num[N],vis[N],dis1[N],dis2[N];
stack<int> s;
vector<int> G1[N],G2[N];

struct Edge{
    int from,to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(block[v]) continue;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            block[v]=id;
            num[id]++;
        }while(v!=u);
    }
}

void spfa1(int s){
    queue<int> Q;
    vis[s]=1;
    dis1[s]=num[s];
    Q.push(s);
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int v : G1[u]){
            if(dis1[v]<dis1[u]+num[v]){
                dis1[v]=dis1[u]+num[v];
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

void spfa2(int s){
    queue<int> Q;
    vis[s]=1;
    dis2[s]=num[s];
    Q.push(s);
    int u;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int v : G2[u]){
            if(dis2[v]<dis2[u]+num[v]){
                dis2[v]=dis2[u]+num[v];
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    int u,v,ans;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i);
    }
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v]){//����DAG
            G1[block[u]].push_back(block[v]);
            G2[block[v]].push_back(block[u]);//����ͼ-DAG
        }
    }
    spfa1(block[1]);//�������
    spfa2(block[1]);//�ܷ����
    //��Ϊ��1�����,�������ٳԵĲ���1���ڵ�scc�е�ĸ���,��ԭͼ����ǿ��ͨͼʱ,Ҳ�ܱ�֤ans���г�ʼֵ ��֤�����ȷ
    ans=num[block[1]];
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(block[u]!=block[v]){
            //����һ����block[v]������ߵ���,block[u]�÷���ߵ���,
            //����block[v]����,block[u]����,�����ڱ���block[u]->block[v],
            //���������˻�,��DAG���ǲ����ڻ���,��û��һ���߻�ͬʱ����dis1[block[v]] && dis2[block[u]],�󲻳���.
            //��ʵ����ͨ��ö��ÿһ����,Ȼ��ٶ���������������ʹ����ص�block[1]��.�����ǲ����ɻ���.
            if(dis1[block[v]] && dis2[block[u]])//block[u] block[v]һ�����ǿɴ��
                ans=max(ans,dis1[block[v]]+dis2[block[u]]-num[block[1]]);
        }
    }
    printf("%d",ans);
    return 0;
}
*/

/*
//���仯���� ��ʱ��û�� https://www.luogu.com.cn/problem/solution/P3119
#include<iostream>
#include<cstdio>
#include<vector>
#include<stack>
#include<cstring>
using namespace std;
long long read()
{
    long long x=0,f=1; char c=getchar();
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int N=100000+100;
struct road
{
    int to,IsBack;
    road (int A,int B)
    {
        to=A,IsBack=B;
    }
};
vector <int> e[N];
vector <road> e2[N];
int belong[N],nd_tot,nd_to,low[N],dfn[N],InStack[N],cnt[N];
stack <int> st;
void Tarjan(int now)
{
    low[now]=dfn[now]=++nd_to;
    InStack[now]=true;
    st.push(now);
    for(int i=0;i<int(e[now].size());i++)
        if(dfn[e[now][i]]==0)
        {
            Tarjan(e[now][i]);
            low[now]=min(low[now],low[e[now][i]]);
        }
        else if(InStack[e[now][i]]==true)
            low[now]=min(low[now],low[e[now][i]]);
    if(low[now]==dfn[now])
    {
        nd_tot++;
        while(st.empty()==false)
        {
            int temp=st.top();
            st.pop();
            belong[temp]=nd_tot;
            InStack[temp]=false;
            cnt[nd_tot]++;
            if(temp==now)
                break;
        }
    }
}
int n,m,S,f[N][2];
int dfs(int now,int back)
{
    if(f[now][back]>=0) return f[now][back];
    int t_ans=0;
    bool OK=false;
    for(int i=0;i<int(e2[now].size());i++)
        if(e2[now][i].to!=S and back-e2[now][i].IsBack>=0)
            t_ans=max(t_ans,dfs(e2[now][i].to,back-e2[now][i].IsBack));
        else if(back>=e2[now][i].IsBack)
            OK=true;
    if(t_ans!=0 or OK==true)
        return f[now][back]=t_ans+cnt[now];
    else
        return f[now][back]=0;
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
        e[i].reserve(4),
        e2[i].reserve(4);
    for(int i=1;i<=m;i++)
    {
        int s=read(),t=read();
        e[s].push_back(t);
    }

    for(int i=1;i<=n;i++)
        if(dfn[i]==0)
            Tarjan(i);
    S=belong[1];
    for(int i=1;i<=n;i++)
        for(int j=0;j<int(e[i].size());j++)
            if(belong[i]!=belong[e[i][j]])
            {
                e2[belong[i]].push_back(road(belong[e[i][j]],0));
                e2[belong[e[i][j]]].push_back(road(belong[i],1));
            }

    memset(f,0x80,sizeof f);
    int ans=0;
    for(int i=0;i<int(e2[S].size());i++)
        ans=max(ans,dfs(e2[S][i].to,1-e2[S][i].IsBack));

    printf("%d",ans+cnt[S]);
    return 0;
}
*/
