#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 1100 //1����2���� 1000��2000��
#define M 4000400//����ì�ܹ�ϵ ����ȫͼ������ 2000*2000
using namespace std;
//ac 421ms tarjan���scc ���ӱ��x,�ɷ���2x+1
/*
��ظ���:
1.SAT���ʶ���(Satisfiability)����ļ��.һ����ʽΪk-�ʶ�������,��� k-SAT.
����k>2ʱ������ΪNP��ȫ��(�޷��ڶ���ʽʱ�����.O(n^k)).��������ֻ�о�k=2�����.��tarjan����Ϊ����,
����ѵı��Ѱ汾Ҳ����,�������ܽ��һЩ�ض�����,���ֵ������
2.2-SAT,�򵥵�˵���Ǹ���n������,ÿ������������Ԫ�أ���֪���ɸ�<a,b>��ʾa��bì��(����a��b���ڲ�ͬ�ļ���).
Ȼ���ÿ������ѡ��һ��Ԫ��,�ж��ܷ�һ��ѡn��������ì�ܵ�Ԫ��.��Ȼ�����ж���ѡ�񷽰�
(���Լ��о�ֻ��2�ַ��������,һ�������ӳ�ϯ��,һ�����ɷ��ϯ��),һ������ֻ��Ҫ���һ�ּ���.

2-sat�Ͷ���ͼƥ�������:
����Ͷ���ͼƥ�����������,����ͼƥ���Ǿ����ܶ����ƥ��Ķ���,��2-sat����һ������������ֻ��ѡ��һ����
���Ҳ�ͬ���໥֮�仹��ì����,�ܷ���ÿһ�Զ�ѡ��һ��,�����ܶ��ѡ��
˵��:
2-sat����������ѧ�ʶ�������,�Ͳ��������й�,������ʱ���������о�.
*/

/*
����:��n�Է��ޱ�����μ�һ���ۻ�,��Ϊ���ص�����,ÿ�Է�����ֻ��1�˿�����ϯ.
��2n ������,ĳЩ��֮�����źܴ��ì��(��Ȼ����֮����û��ì�ܵ�),��ì�ܵ�2����
�ǲ���ͬʱ�����ھۻ��ϵ�.��û�п��ܻ���n����ͬʱ��ϯ��
����:http://acm.hdu.edu.cn/showproblem.php?pid=3062
˼·:���2-sat����.tarjan���scc.
*/
struct Node{
    int to,next;
}edge[M];
int n,m,head[N<<1],dfn[N<<1],low[N<<1],num,cnt,block[N<<1],id,in[N<<1];
stack<int> s;
void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}
//Tarjan SCC ����  O(V+E)
void dfs(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);

    }
    if(low[u] == dfn[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            block[v]=id;
        }while(v!=u);
    }
}

bool judge(){
    for(int i=0;i<2*n;i++)//�ܹ�n�Է��� 2n���� ���0~(2n-1)
        if(!dfn[i]) dfs(i);
    for(int i=0;i<n;i++)//����ö�ٵ��Ƿ��޵Ķ������
        //�����Ӻ��ɷ�ͬʱ��ϯ,��һ������ì�ܹ�ϵ����Ҳ�����ϯ,��Ϊ�����ɷ�ͬʱ��ϯ����������ì�ܹ�ϵ��ͬʱ��ϯ���µ�
        if(block[2*i] == block[2*i+1]) return false;
    return true;
}

int main(){
    int a1,a2,c1,c2;
    while(scanf("%d",&n)!=EOF){
        id=num=cnt=0;
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(block,0,sizeof(block));
        memset(in,0,sizeof(in));
        scanf("%d",&m);
        while(m--){
            //����2a,2a+1������ ��ı���Ǵ�0��ʼ��,�����Ϊ2n-1.
            scanf("%d%d%d%d",&a1,&a2,&c1,&c2);//a1 a2ֻ���ǶԷ��޵ı��0~n-1 0�������� 1�����ɷ�
            a1=a1*2+c1;//a1*2�ǹ���һ�ѷ��޵ı�� 2����ʱ�����ŵ� ����������,ż�����ɷ�
            a2=a2*2+c2;
            addEdge(a1,a2^1);//ѡ��a1,��һ����Ӧ����a2����ż,��Ϊa1 a2��ì�ܹ�ϵ
            addEdge(a2,a1^1);//ѡ��a2,��һ����Ӧa1����ż,a2 a1��ì�ܹ�ϵ,ͬ��
        }
        if(judge()) printf("YES\n");//n����ͬʱ��ϯ��ʵ�ʽ������Ψһ,����ֻ�ж��Ƿ�����n����ͬʱ��ϯ
        else printf("NO\n");
    }
    return 0;
}

/*
//ac 421ms tarjan���scc+����x,�ɷ�x+n���
#include<cstdio>
#include<stack>
#include<cstring>
#include<algorithm>
#define N 1100 //1����2���� 1000��2000��
#define M 4000400//����ì�ܹ�ϵ ����ȫͼ������ 2000*2000
using namespace std;

struct Node{
    int to,next;
}edge[M];
int n,m,head[N<<1],dfn[N<<1],low[N<<1],num,cnt,block[N<<1],id,in[N<<1];
stack<int> s;
void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}
//Tarjan SCC ����  O(V+E)
void dfs(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);

    }
    if(low[u] == dfn[u]){
        id++;
        do{
            v=s.top();
            s.pop();
            in[v]=0;
            block[v]=id;
        }while(v!=u);
    }
}

bool judge(){
    for(int i=0;i<2*n;i++)//�ܹ�n�Է��� 2n���� ���0~(2n-1)
        if(!dfn[i]) dfs(i);
    for(int i=0;i<n;i++)//����ö�ٵ��Ƿ��޵Ķ������
        //�����Ӻ��ɷ�ͬʱ��ϯ,��һ������ì�ܹ�ϵ����Ҳ�����ϯ,��Ϊ�����ɷ�ͬʱ��ϯ����������ì�ܹ�ϵ��ͬʱ��ϯ���µ�
        if(block[i] == block[i+n]) return false;
    return true;
}

int main(){
    int a1,a2,c1,c2;
    while(scanf("%d",&n)!=EOF){
        id=num=cnt=0;
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(block,0,sizeof(block));
        memset(in,0,sizeof(in));
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d%d",&a1,&a2,&c1,&c2);//a1 a2ֻ���ǶԷ��޵ı��0~n-1 0�������� 1�����ɷ�
            //a1,a1+n�ǹ���һ�ѷ��޵ı�� ����a1��������,a1+n�����ɷ�
            addEdge(a1+c1*n,a2+(1-c2)*n);//ѡ��a1,��һ����Ӧ����a2����ż,��a2��żΪa2+(1-c2)*n,��Ϊa1 a2��ì�ܹ�ϵ
            addEdge(a2+c2*n,a1+(1-c1)*n);//ѡ��a2,��һ����Ӧa1����ż,a1��żΪa1+(1-c1)*n,a2 a1��ì�ܹ�ϵ,ͬ��
        }
        if(judge()) printf("YES\n");//n����ͬʱ��ϯ��ʵ�ʽ������Ψһ,����ֻ�ж��Ƿ�����n����ͬʱ��ϯ
        else printf("NO\n");
    }
    return 0;
}
*/

/*
//ac 436ms ����� dfs���Ѱ汾 ��ʱ��δ���
#include<cstdio>
#include<cstring>
#include<vector>
#define maxn 1000 //1����2���� 1000��2000��
using namespace std;
// ��Դ������ѵİ���� 323 ҳ ���ѵ�Ч�ʺ�tarjanЧ�ʲ�� tarjan405ms ����421ms  ������໹�ǻ�ѡ��tarjan����
struct Twosat {
  int n;
  vector<int> g[maxn * 2];
  bool mark[maxn * 2];
  int s[maxn * 2], c;
  bool dfs(int x) {
    if (mark[x ^ 1]) return false;
    if (mark[x]) return true;
    mark[x] = true;
    s[c++] = x;
    for (int i = 0; i < (int)g[x].size(); i++)
      if (!dfs(g[x][i])) return false;
    return true;
  }
  void init(int n) {
    this->n = n;
    for (int i = 0; i < n * 2; i++) g[i].clear();
    memset(mark, 0, sizeof(mark));
  }
  void add_clause(int x, int y) {  // �������������仯
    g[x].push_back(y ^ 1);         // ѡ�� x �ͱ���ѡ y^1
    g[y].push_back(x ^ 1);
  }
  bool solve() {//O(V*E)
    for (int i = 0; i < n * 2; i += 2)
      if (!mark[i] && !mark[i + 1]) {
        c = 0;
        if (!dfs(i)) {//����Ϊʲôi��� ��ì���˺�,��Ҫ�����ж�i+1����ì�ܲ����ж� ���岻����n����ͬʱ��ϯ��
          while (c > 0) mark[s[--c]] = false;
          if (!dfs(i + 1)) return false;
        }
      }
    return true;
  }
}tmp;

int main(){
    int n,m,a1,a2,c1,c2;
    while(scanf("%d",&n)!=EOF){
        tmp.init(n);
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d%d",&a1,&a2,&c1,&c2);//a1 a2ֻ���ǶԷ��޵ı��0~n-1 0�������� 1�����ɷ�
            a1=a1*2+c1;//a1*2�ǹ���һ�ѷ��޵ı�� 2����ʱ�����ŵ� ����������,ż�����ɷ�
            a2=a2*2+c2;
            tmp.add_clause(a1,a2);
            tmp.add_clause(a2,a1);
        }
        if(tmp.solve()) printf("YES\n");//n����ͬʱ��ϯ��ʵ�ʽ�� ����Ψһ,����ֻ�ж��Ƿ�����n����ͬʱ��ϯ
        else printf("NO\n");
    }
    return 0;
}
*/
