#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 200100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;
//ac 19ms tarjan���pbc+����Բ����+dfs����a-b����СԲ��
//�����ǿ���ݼ���q��ѯ�� ���Կ���lca������st��lca��������������Բ����
//Բ�����ο�����: https://www.cnblogs.com/PinkRabbit/p/10446473.html
/*
����:ĳ������Ϣ�Կ�ʵս��ϰ,����ɹ����������������ڲ�����.
��������������Ϣ����,����ƻ���ĳ̨�м�������ϰ�װһ����̽��,
�Ӷ��ܹ�������������Ϣ���Ļ��ཻ����������Ϣ.��������������
�൱���Ӵ�,���ݰ���һ����Ϣ���Ĵ�����һ����Ϣ���Ŀ��Բ�ֹ��
һ��ͨ·.������Ҫ�㾡��ؽ���������,Ӧ�ð���̽����װ���ĸ�
�м�������ϲ��ܱ�֤���е����ݰ����ܱ�����?
����:n���������ͼ,���Ӱ��a��b������ͨ�Ե���С��ŵĸ��.
����:https://www.luogu.com.cn/problem/P5058
˼·:
Բ����:��ԭͼ��ÿ���㵱��һ��Բ��,��ÿ��pbc����һ������ķ���,
���������pbc�е�Բ��Ͷ�Ӧ�ķ����������,�������ԭͼ����ͨ��,��
Բ��������һ����,���ԭͼ����ͨ,��Բ������ɭ��.
Բ�����з���ĸ�������PBC�ĸ���,��pbc�ĸ���ȡ���ڸ��ĸ���,��
ԭͼ���ĸ���(���ϳ�ʼ���ڵ�,���������֧��)���Ϊn-1��,���Բ����
�еĵ�ĸ���<2N.������Բ�����е�Ҷ�ӽڵ�(Բ��)����ÿ��pbc�г��������Ľڵ�,
��Բ�����жȴ���1��Բ�����ÿ��pbc�еĸ��,��Ϊ�����������2��pbc.
Բ�����з���ĵ�Ķ�Ϊÿ��pbc�е�ĸ���.
tarjan���pbc,����Բ����.dfs��a�����Բ��������СԲ����(����a��b����).
���ﲻ�������Ƿ��Ǹ��,��Ϊ��a-b��·���ϳ���a��b���ܶ�Ϊ1��,�м�ĵ��
��Ȼ�Ǵ���1��,���ֻ���ж��м�ĵ��Ƿ���Բ�㼴��.
*/

int head[N],cnt,a,b;
int n,m,dfn[N],low[N],clock,pbc_cnt,vis[N<<1],ans;
stack<int> s;
vector<int> G[N<<1];

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

//O(V+E)
void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
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
                    //���Բ�� ����pbc����� ����㶼��Բ�����е�Ҷ�ӽڵ�(Բ��)
                    //�����ΪԲ�����еķ���
                    vis[tmp]=1;
                    s.pop();
                    G[pbc_cnt].push_back(tmp);
                    G[tmp].push_back(pbc_cnt);
                }while(tmp!=v);
                vis[u]=1;
                G[pbc_cnt].push_back(u);
                G[u].push_back(pbc_cnt);
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

//O(V+E)
int dfs(int u,int fa){
    for(int v : G[u]){
        if(v == fa) continue;
        //�ҵ�b�����a-b��·���ĵ���
        if(v == b) return 1;//����a b ���˵���м�ķ����� ���Ƚϼ�¼��СԲ����
        if(dfs(v,u)){
            if(vis[v])//����¼����ı��
                ans=min(ans,v);
            return 1;
        }
    }
    return 0;
}

void init(){
    clock=cnt=0;
    pbc_cnt=n;//Բ���� ������Ҫ��n+1��ʼ��
    ans=INF;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    m=n<<1;//Բ������ĸ������Ϊ2n-1
    for(int i=1;i<m;i++) G[i].clear();
}

int main(){
    int u,v;
    scanf("%d",&n);
    init();
    while(scanf("%d%d",&u,&v) && u+v){
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i,-1);
    }
    scanf("%d%d",&a,&b);
    dfs(a,-1);
    if(ans!=INF) printf("%d",ans);
    else printf("No solution");
    return 0;
}

/*
//4ms tarjan�����,����ʱ���dfn�жϸ���Ƿ���a��b֮ǰ��·����
//��������һ�� ������low[u]=min(low[u],low[v]);ֻ����u���Ǹ��ʱ�Ÿ���,�е���� https://www.luogu.com.cn/problem/solution/P5058 ����(����������)
//4ms tarjan�����,����ʱ���dfn�жϸ���Ƿ���a��b֮ǰ��·����
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 200100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;

int head[N],cnt,a,b;
int n,dfn[N],low[N],clock,ans;

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

//O(V+E)
void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v == fa) continue;
        if(!dfn[v]){
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            //dfn[v]<=dfn[b] ˵��b��v�����еĽڵ�,u!=a,��ôɾ��u��Ȼ��ʹ��a��b������ͨ�鲻��ͨ
            if(dfn[u]<=low[v] && u!=a && dfn[v]<=dfn[b])//����u=bʱ,dfn[v]>dfn[b]��ȻҲ������
                ans=min(ans,u);//��¼��С�����
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void init(){
    clock=cnt=0;
    ans=INF;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
}

int main(){
    int u,v;
    scanf("%d",&n);
    init();
    while(scanf("%d%d",&u,&v) && u+v){
        addEdge(u,v);
        addEdge(v,u);
    }
    scanf("%d%d",&a,&b);
    tarjan(a,-1);//ֱ�Ӵ�a�㿪ʼ���� a b���㲻����Ϊ���
    if(!dfn[b]){//��a b���㲻��ͨ ���޽�
        printf("No solution");
        return 0;
    }
    if(ans!=INF)
        printf("%d",ans);
    else
        printf("No solution");
    return 0;
}
*/

/*
//tarjanʱ����жϷ� ��һ����ʽ if(!dfn[i]) tarjan(i,-1);��Ҫͬʱ�ж�a��b��ʱ����ĸ���ǰ���ĸ��ں���
#include <bits/stdc++.h>
using namespace std;

const int N=2e5+10,M=5e5+10;
int vex[N],k,n,m,A,B,ans=1e9;
struct edge {
	int u,v,next;
}e[M*2];

void add(int u,int v){
	k++;
	e[k].u=u;
	e[k].v=v;
	e[k].next=vex[u];
	vex[u]=k;
	return;
}

int dfn[N],low[N],idx;

int check(int u,int v){
	if(dfn[v]<=dfn[A]&&dfn[v]>dfn[B]) return 1;
	if(dfn[v]<=dfn[B]&&dfn[v]>dfn[A]) return 1;
	return 0;
}

void tarjan(int u,int fa){
	dfn[u]=low[u]=++idx;
	for(int i=vex[u];i;i=e[i].next){
		int v=e[i].v;
		if(!dfn[v]) {
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]&&u!=A&&u!=B&&check(u,v)) {
				ans=min(ans,u);
			}
		}
		else if(v!=fa) low[u]=min(low[u],dfn[v]);
	}
	return;
}

int main(){
	cin>>n;
	while(1){
		int u,v;
		cin>>u>>v;
		if(u==0&&v==0) break;
		add(u,v);
		add(v,u);
	}
	cin>>A>>B;
	tarjan(1,0);
	if(ans==1e9) cout<<"No solution";
	else cout<<ans;
	return 0;
}
*/

/*
//ac 20ms tarjan���pbc+����Բ����+bfs����a-b����СԲ��
#include<cstdio>
#include<cstring>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define N 200100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;
int head[N],cnt,a,b;
int n,m,dfn[N],low[N],clock,pbc_cnt,vis[N<<1],ans;
stack<int> s;
vector<int> G[N<<1];
struct Node{
    int u,minv,fa;
    Node(int u=0,int minv=0,int fa=0):u(u),minv(minv),fa(fa){}
};

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
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
                    vis[tmp]=1;
                    s.pop();
                    G[pbc_cnt].push_back(tmp);
                    G[tmp].push_back(pbc_cnt);
                }while(tmp!=v);
                vis[u]=1;
                G[pbc_cnt].push_back(u);
                G[u].push_back(pbc_cnt);
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void bfs(){
    queue<Node> Q;
    Q.push(Node(a,INF,-1));
    int u;
    Node tmp;
    while(!Q.empty()){
        tmp=Q.front();
        Q.pop();
        u=tmp.u;
        for(int v : G[u]){
            if(v == tmp.fa) continue;
            if(v == b){
                ans=tmp.minv;
                return;
            }
            Q.push(Node(v,vis[v]?min(tmp.minv,v):tmp.minv,u));
        }
    }
}

void init(){
    clock=cnt=0;
    pbc_cnt=n;
    ans=INF;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    m=n<<1;
    for(int i=1;i<m;i++) G[i].clear();
}

int main(){
    int u,v;
    scanf("%d",&n);
    init();
    while(scanf("%d%d",&u,&v) && u+v){
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i])
            tarjan(i,-1);
    }
    scanf("%d%d",&a,&b);
    bfs();
    if(ans!=INF) printf("%d",ans);
    else printf("No solution");
    return 0;
}
*/

/*
����q��ѯ��,q�ܴ�,���Կ���lca��������Բ����
��q����,���Կ���st���lca O(1)��ѯ
*/

/*
//ac 18ms tarjan���pbc+����a���Բ����+dfs����a-b����СԲ��
//tarjan������ɭ��,ֻ�������a���Բ����
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<algorithm>
#define N 200100
#define M 500100
#define INF 0x3f3f3f3f
using namespace std;

int head[N],cnt,a,b;
int n,m,dfn[N],low[N],clock,pbc_cnt,vis[N<<1],ans;
stack<int> s;
vector<int> G[N<<1];

struct Edge{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

//O(V+E)
void tarjan(int u,int fa){
    dfn[u]=low[u]=++clock;
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
                    vis[tmp]=1;
                    s.pop();
                    G[pbc_cnt].push_back(tmp);
                    G[tmp].push_back(pbc_cnt);
                }while(tmp!=v);
                vis[u]=1;
                G[pbc_cnt].push_back(u);
                G[u].push_back(pbc_cnt);
            }
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

//O(V+E)
int dfs(int u,int fa){
    for(int v : G[u]){
        if(v == fa) continue;
        if(v == b) return 1;
        if(dfs(v,u)){
            if(vis[v])
                ans=min(ans,v);
            return 1;
        }
    }
    return 0;
}

void init(){
    clock=cnt=0;
    pbc_cnt=n;//������Ҫ��n+1��ʼ��
    ans=INF;
    memset(head,-1,sizeof(head));
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    m=n<<1;
    for(int i=1;i<m;i++) G[i].clear();
}

int main(){
    int u,v;
    scanf("%d",&n);
    init();
    while(scanf("%d%d",&u,&v) && u+v){
        addEdge(u,v);
        addEdge(v,u);
    }
    scanf("%d%d",&a,&b);
    tarjan(a,-1);//ֻ�蹹�����a�����ͨ���Բ����
    if(!dfn[b]){//��a b���㲻��ͨ ���޽�
        printf("No solution");
        return 0;
    }
    dfs(a,-1);
    if(ans!=INF) printf("%d",ans);
    else printf("No solution");
    return 0;
}
*/
