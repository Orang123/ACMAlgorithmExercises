#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 100100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
//ac 284ms tarjan���pbc����Բ�������
/*
����:����һ������ͼ,��ÿ���㱻ɾ��֮���ж��ٸ�������
(x,y)(x!=y,1<=x,y<=n)����ͨ.
����:https://www.luogu.com.cn/problem/P3469
˼·:���ɾ���ĵ�u���Ǹ��,��ֻ��ɾ����u������㲻��ͨ.
���ɾ���ĵ�u�Ǹ��,����˸õ���������е㲻��ͨ��,ɾ�����u
��������ĸ�������ͨ��֧�еĵ��Ҳ�ǲ���ͨ��.
Բ������ɾ��ĳ��Բ����䱾�������游�ڵ�ķ�֧���Զ��׼���,
ÿ��������֧������Ϊһ����ͨ�Ӽ����ָ�.
����tarjan���pbc����Բ����,����Ӧ������dpͳ��ÿ���ڵ�u������
��Բ��ĸ���siz[u].��ɾ��Ҷ�ӽڵ�u(���Ǹ��)��ֻ����u��������
���ɵĵ��2*(n-1),��ɾ���ȴ���1��Բ��u(���),���˼���u��������
���ɵĲ���ͨ�����,�������Ϊ���ĸ�����֧֮�䶼���������ͨ�ĵ��,
ans+=2*siz[u]*siz[v]+(num-siz[u]-1)*siz[u].
��Ϊ�������յ���Եߵ�����1��,����Ҫ��2.
*/

int n,m,head[N],cnt;
int dfn[N],low[N],clock,num,pbc_cnt,vis[N<<1];

ll son[N<<1],ans[N];
stack<int> s;
vector<int> G[N<<1];

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}


void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
    num++;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            s.push(v);
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                pbc_cnt++;
                int tmp;
                do{
                    tmp=s.top();
                    s.pop();
                    G[pbc_cnt].push_back(tmp);//����Բ����
                    G[tmp].push_back(pbc_cnt);
                }while(tmp!=v);
                vis[pbc_cnt]=1;//��Ƿ���
                G[pbc_cnt].push_back(u);
                G[u].push_back(pbc_cnt);
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void dfs(int u,int fa){
    for(int v : G[u]){
        if(v == fa) continue;
        dfs(v,u);
        if(!vis[u])//ɾ���ĵ�ֻ����ʵ�ʴ��ڵ�Բ�� ���ﲻ����u��
            ans[u]+=2*son[u]*son[v];
        son[u]+=son[v];
    }
    if(!vis[u]){
        ans[u]+=2*son[u]*(num-son[u]-1);//�游�ڵ��е�Բ���u�����е�Բ��ṹ�ɲ���ͨ�ĵ��(������u��)
        ans[u]+=2*(num-1);//u���ʣ������Բ�㹹�ɵĲ���ͨ���
    }
    son[u]+=u<=n?1:0;//ֻ��¼Բ�����е�Բ��,������dfs������ʱ�Ȳ�����u��
}

void init(){
    clock=cnt=0;
    pbc_cnt=n;
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
    memset(dfn,0,sizeof(dfn));
    int n2=n<<1;
    for(int i=1;i<n2;i++) G[i].clear();
}

int main(){
    int u,v;
    scanf("%d%d",&n,&m);
    init();
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            num=0;//��¼��Ҫ�����Բ������Բ��ĸ���.
            tarjan(i,-1);
            dfs(i,-1);
        }
    }
    for(int i=1;i<=n;i++)
        printf("%lld\n",ans[i]);
    return 0;
}

/*
//ac 201ms ����Բ�������ּ����Եķ�ʽ,ֻ������������tarjan�����ʱ����
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 100100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,head[N],cnt;
int dfn[N],low[N],clock;

ll son[N],ans[N];

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}


void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
    son[u]=1;
    ll sum=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            tarjan(v,u);
            son[u]+=son[v];//son[u]����u�����ӵ�tarjan��û���ʵĵ�ĸ���,Ҳ�����������������ӵĵ�ĸ���
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                ans[u]+=2*sum*son[v];//��ǰ�ϲ��Ĳ���ͨu��֧(������u��)�뵱ǰ����ͨv�ӷ�֧���ɵĲ���ͨ���
                //ע������sumֻ���� u��Ϊ�������Ĳ���ͨv��֧�ĵ����,u��Ϊ��㲢��������v��֧��Ҫ��Ϊ�Ӳ���ͨ��֧,
                //�п���v��֧��u������ͬһ��pbc��,��ʱv��֧�Ǻ��游�ڵ���Ϊ�游����ͨ��֧ȥ�����
                sum+=son[v];//son[v]��֧�������,��Ҫ�ͺ����v��֧���㲻��ͨ���,�����ۼӵ�sum��
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    ans[u]+=2*(n-1);//u���ʣ��������ɵĲ���ͨ���
    ans[u]+=2*sum*(n-sum-1);//u��Ϊ���ָ���游����ͨ��֧(������u��)�����зָ����v�Ӳ���ͨ��֧���ɵĲ���ͨ���
}

void init(){
    clock=cnt=0;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    scanf("%d%d",&n,&m);
    init();
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i,-1);
    }
    for(int i=1;i<=n;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
*/

/*
//ac 202ms tarjan����� �Ӳ���ͨ�����������в���ͨ�鹹�ɵĲ���ͨ���
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 100100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,head[N],cnt;
int dfn[N],low[N],clock;

ll son[N],ans[N];

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}


void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
    son[u]=1;
    ll sum=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            tarjan(v,u);
            son[u]+=son[v];
            low[u]=min(low[u],low[v]);
            if(dfn[u]<=low[v]){
                //��ǰ�����֧�������֧�Լ��游��֧(������u��)���ɵĲ���ͨ���
                //���������2,���������ÿ��son[v]��֧���˼����Լ���,����ѱ�ķ�֧�ټ���˵�ߵ���һ��
                //���з�֧���������,�����游��ֻ֧������һ����,���౻�ָ���ͨ�鶼������2��.
                ans[u]+=son[v]*(n-son[v]-1);
                sum+=son[v];
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
    ans[u]+=2*(n-1);//u��ָ����ʣ��������ɵĲ���ͨ���
    ans[u]+=sum*(n-sum-1);//ɾ��u���,�游��֧��������ͨ�������ɶ˵�ߵ�����ͨ��
}

void init(){
    clock=cnt=0;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    scanf("%d%d",&n,&m);
    init();
    while(m--){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i,-1);
    }
    for(int i=1;i<=n;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
*/
