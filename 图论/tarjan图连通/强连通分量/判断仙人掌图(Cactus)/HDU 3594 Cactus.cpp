#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 20100
using namespace std;
//ac 78ms
//��Ȼ���� ac��,����˵����Ϊ����ˮ,���⻹�д���֤,������ʱ�俴���Ǹ�Cactus��PDF����
//����������취 hdu 3594 UVA 10510��2�ⶼac��
/*
����:�ж�һ��ͼ�Ƿ���������(Cactus)ͼ.������ͼΪ����ͼ.
������ͼ������������:
1.���еı߶��ڻ���.
2.���еı߶�ֻ����1����.
����:�Ƿ���ǿ��ͨͼ,scc�����Ƿ�Ϊ1.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3594
˼·:����1ֻҪ����scc�ĸ���Ϊ1����,����2������tarjan���scc
ʱ,��¼ÿ���ڵ��ǰ���ڵ�,�������ر��ظ�����v��ʱ,�ͽ���ǰ�㲻�ϻ�����
֮ǰ�����Ƚڵ�ֱ�����ص�vʱ����,�����Ծ���̲����ۼ�û������ִ���,
���ĳ���������2�ξ�˵�����������ı� ���ٳ�������2������,�Ϳ��Խ���,
˵������������ͼ.
*/

int n,head[N],cnt;
int dfn[N],low[N],in[N],clock,id,block[N],pre[N],num[N],flag;
stack<int> s;

struct Edge{
    int to,next;
}edge[N*N/2];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++clock;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            pre[v]=u;
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v]){
            low[u]=min(low[u],dfn[v]);
            int tmp=u;
            //�����ر�v���ѷ���ʱ,�����Ƚڵ�������Ծ ֱ���ٴλص�v��,ע������v���ǲ���num[v]++��,�����������������������в���Cactus
            while(tmp!=v){
                num[tmp]++;//��¼�������� ÿ������ִ���
                if(num[tmp]>1){//������1ʱ
                    flag=1;
                    return;
                }
                tmp=pre[tmp];
            }
        }
    }
    if(dfn[u] == low[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            block[v]=id;
        }while(v!=u);
    }
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        flag=id=clock=cnt=0;
        memset(head,-1,sizeof(head));
        //���ﲻ�ܸ�ֵ-1 ����ᵼ������С�����-1,��Ȼ��Ҳ��ȷ ���ǳ����߼��������
        memset(pre,0,sizeof(pre));
        memset(num,0,sizeof(num));
        memset(dfn,0,sizeof(dfn));
        scanf("%d",&n);
        while(scanf("%d%d",&u,&v) && u+v)
            addEdge(u,v);
        for(int i=0;i<n;i++){
            if(!dfn[i])
                dfs(i);
        }
        if(id>1 || flag) printf("NO\n");//��scc��������1��ĳ������������2����ʱ,˵������������ͼ.
        else printf("YES\n");
    }
    return 0;
}
/*
//��������
input
2
5
0 1
1 2
2 0
2 3
3 4
4 2
0 0

5
0 1
1 2
2 3
3 4
3 1
4 0
0 0

4
0 1
1 2
2 3
3 1
3 0
0 0

output
YES
NO
NO
*/

/*
//��һ���ж�������ͼ�İ취
//https://www.cnblogs.com/AOQNRMGYXLMV/p/5353502.html
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;

const int maxn = 10000 + 10;

int n, m;
vector<int> G[maxn];

stack<int> S;
int dfs_clock, pre[maxn], low[maxn];
int scc_cnt, sccno[maxn];

void dfs(int u) {
	pre[u] = low[u] = ++dfs_clock;
	S.push(u);
	for(int v : G[u]) {
		if(!pre[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if(!sccno[v]) low[u] = min(low[u], pre[v]);
	}
	if(low[u] == pre[u]) {
		scc_cnt++;
		for(;;) {
			int x = S.top(); S.pop();
			sccno[x] = scc_cnt;
			if(x == u) break;
		}
	}
}

//Tarjan�㷨��ǿ��ͨ����
void find_scc() {
	dfs_clock = scc_cnt = 0;
	memset(pre, 0, sizeof(pre));
	memset(sccno, 0, sizeof(sccno));
	for(int i = 0; i < n; i++) if(!pre[i])
		dfs(i);
}

//�ڶ���DFS��֤��������ͼ

//color[u]Ϊ0��ʾ��û�з��ʣ�Ϊ1��ʾ���ڷ��ʣ�Ϊ2��ʾ�Ѿ��������
int color[maxn];

bool dfs2(int u, int minBack) {    //minBack��ʾ�������ָ�����С��DFS��
	color[u] = 1;
	int backs = 0;//����ߵĸ���������ֻ����һ��
	for(int v : G[u]) if(color[v] == 1) {    //�ҵ�һ�������
		backs++;
		if(backs > 1) return false;
		if(pre[v] < minBack) return false;    //�����ָ��Ľڵ��DFS��С����Сֵ
	}
	if(backs) minBack = pre[u];
	for(int v : G[u]) {
		if(color[v] == 2) return false;    //ǰ��߻򽻲��
		if(color[v] == 0)    //����
			if(!dfs2(v, minBack)) return false;;
	}
	color[u] = 2;
	return true;
}

int main()
{
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; i++) G[i].clear();
		while(m--) {
			int u, v; scanf("%d%d", &u, &v);
			G[u].push_back(v);
		}

		find_scc();
		if(scc_cnt > 1) { puts("NO"); continue; }

		memset(color, 0, sizeof(color));
		if(!dfs2(0, 0)) puts("NO");
		else puts("YES");
	}

	return 0;

}
*/

/*
//https://www.cnblogs.com/cenariusxz/p/4814504.html
//���ȣ�tarjan������ǿ��ͨ�����Ƿ�ֻ��һ����Ȼ��������б��Ƿ����һ�����ڣ�
//�ҵ������ǣ���һ������ tarjan �� dfs �У�������һ���ߣ����������ָ����
//һ��ʱ�����ϱ�����ĵ㣬��ô�õ�һ���� dfs �������ĺ�̽ڵ㣬��֮ǰ�ض���
//һ��������֮���·������ô������֮����Ѿ�������·���ˣ����Ӻ�̽ڵ�һ���ܷ��ص�
//���Ƚڵ���γɻ���ǿ��ͨ�������Է������Ƚڵ��·��һ��������������·���γ���������
//�Ͳ�����������ͼ�ˡ������������ָ����һ��ʱ�����ϱ���С�ĵ㣬��ô�����Ǹ���
//�����Ȧ�ķ������ȣ������Ǹ���������Ȧ�еĵ㣬��ô��һ��һ������һ��Ȧ�ϣ�
//�ǾͲ��ϱ��������Ƚ���ķ�����+1��������ж��Ƿ�ÿ����ķ�����С�ڵ���1�����ˡ�
#include<stdio.h>
#include<string.h>
#include<stack>
#include<queue>
using namespace std;

const int maxn=2e4+5;
const int maxm=5e4+5;

int head[maxn],point[maxm],nxt[maxm],size;
int n,t,scccnt;
int stx[maxn],low[maxn],scc[maxn];
int fa[maxn];
int vis[maxn];
stack<int>S;
bool f;

void init(){
    memset(head,-1,sizeof(head));
    size=0;
    f=1;
    memset(vis,0,sizeof(vis));
    memset(fa,-1,sizeof(fa));
}

void add(int a,int b){
    point[size]=b;
    nxt[size]=head[a];
    head[a]=size++;
}

void dfs(int s,int pre){
    fa[s]=pre;
    stx[s]=low[s]=++t;
    S.push(s);
    for(int i=head[s];~i;i=nxt[i]){
        int j=point[i];
        if(!stx[j]){
            dfs(j,s);
            low[s]=min(low[s],low[j]);
        }
        else if(!scc[j]){
            if(stx[j]<stx[s]){
                int k=s;
                while(k!=j&&k!=-1){
                    vis[k]++;
                    k=fa[k];
                }
            }
            else f=0;
            low[s]=min(low[s],stx[j]);
        }
    }
    if(low[s]==stx[s]){
        scccnt++;
        while(1){
            int u=S.top();S.pop();
            scc[u]=scccnt;
            if(s==u)break;
        }
    }
}

void setscc(){
    memset(stx,0,sizeof(stx));
    memset(scc,0,sizeof(scc));
    t=scccnt=0;
    for(int i=0;i<n;++i)if(!stx[i])dfs(i,-1);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int m;
        scanf("%d",&n);
        init();
        int a,b;
        while(scanf("%d%d",&a,&b)&&a+b){
            add(a,b);
        }
        setscc();
        for(int i=0;i<n;++i)if(vis[i]>1)f=0;
        if(scccnt>1||!f)printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}
*/
