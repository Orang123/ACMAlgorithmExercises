#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 500100

/*
����ı���ʵ�ʾ��Ƕ���Ƚ��б���,�����ý��һ��һ��������,��������2�ı��� �Ӵ���С��,
���������������ܴ���,���Ż�ʱ�䣬�����ǹ�����fa[i][k]����i������ϵ�2^k�����ȵ����ݽṹ��ʵ�ֱ�������Ծ
*/
/*
fa[i][k]��ʾ���i�������2^k�η����������ĸ����
dep[i]��ʾ���i�����
*/
int head[N],fa[N][21],dep[N],n,m,s,cnt;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to]};
    head[to]=cnt++;
}

//O(log(dep[u1])+log(dep[u2])+...+log(dep[un]))=O(log(dep[u1]*dep[u2]*...*dep[un])) Ԥ����ʱ�临�ӶȺ��񻯼�ΪO(NlogN)
void dfs(int u,int fath){
    fa[u][0]=fath;//u�ĵ�2^0�η������Ƚ��,���丸�׽��Ϊfath
    dep[u]=dep[fath]+1;//������+1
    for(int i=1;(1<<i)<=dep[u];i++)//���ݵ�ǰ��������ȹ������2^log2(dep[u])������ O(log(N))
        /*
        u���ĵ�2^i�η������Ƚ��������Ϊ �ȴ�u����ߵ����2^(i-1)�η������Ƚ��,
        �ٴ�������Ƚ��������2^(i-1)�η������Ƚ�����fa[u][i],�������2^i=2^(i-1)+2^(i-1)=2*2(i-1)=2^i
        �ȴӼ������Ͻ�С�����Ƚ��,�ټ������Ͻϴ�����Ƚڵ�,���ε���
        */
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fath)//�����ٻص��丸�ڵ�
            dfs(v,u);
    }
}

//lca(Least Common Ancestors) O(log(dep)) depΪ(x��y)�������������lca֮�����֮�� �ʱ�临�Ӷ�O(logN)
int lca(int x, int y){
    if(dep[x]<dep[y]) swap(x,y);//��Զ��x�����Ϊ��Ƚ�����Ǹ����
    /*
    ��x���������������y���һ��,�����ǴӴ���С��������������ȥ��
    �ٰ�����С��������Ϊ��С��ʼ�������ܻ���֡����塱������
    ��������x��һ������������y��ͬ����ȵ�,��Ϊ��������Ӧ��������һ��
    10�����������Ա�ʾΪ2���Ƶķ�ʽ���׼������x��y�����֮���������
    10�����������ǿ�����2���Ƶ���ʽ��ʾ�����ġ�����5(101)=4(100)+1(1) 8(1000)��.
    ����ΪʲôҪ�Ӵ���С��:
    eg:
    1.��ѻ��ˮ�Ĺ��̣�������ѻ�Ȱ������ģ��������iֵ���Ž�ˮ���
    ���𽥼�С������Ʒ�����ֱ����ˮ����ˮ������������������ɳ������С�����Ķ�����
    �����ΪʲôiֵҪ�Ӵ�С��
    2.��5Ϊ������С�������5��1+2+4,�������ǻ�Ҫ����һ����Ȼ����ܵó�5=1+4,���Ӵ���С����
    ֱ�ӿ��Եó�5=4+1����Ҳ�����ö�����Ϊ��,5(101),�Ӹ�λ���λ��ܼ�,���������λ֮���ԭ������,���ҾͲ���.
    3.����С��ʼ��,�ô�2^0�η���ʼ,��ʵ��x��y����ֻ������Ǹ�ż��,���ﻹ�ò���1ȥ����,��������ͻ����,��Ҫ����
    */
    /*
    2^20�η���10^6 Ҳ����������10^6���������ֻ��50W��������������50W,
    ���ö�ٵ��Ͻ�2^20�η��ǹ��õ�(����fa[N][21]��άҪ��21�±�������ȡ��20)
    ����ö�ٵĲ�������2�ı������μ���ݼ���,������ѡ����������,
    ���Ƕ���һ��ʼx��y��Ȳ�Ϊ5ʱ,ʵ��ѡȡ�Ĳ���Ϊ2^2��2^0,�м�ö�ٵ�2^1�η��Ƕ���Ŀ�����,
    ��lg����Ԥ�����Ż�������������,���ڶ���Ĳ�������ֱ������,�Ż�ѭ����ʱ�临�Ӷ�
    */
    for(int i=20;i>=0;i--){//���ﲽ����ѡ�񲢲��Ǹ���x��y��ʵʱ��ֵȥѡ���,���Ǳ���ö��ÿһ�ֿ����� ��ʵ20������ log N/log 2����� NΪ��ĸ���
        //if(dep[x]-(1<<i)>=dep[y])
        /*
        ��x����������ȱ�y�Ծɴ�ʱ,��x������ǰѡ�������,�ټ��������� �����������������ԭ��һ��Խ��ԽС,
        ���x����������ȱ�yС,��ѡȡ��С�Ĳ��������������Ĳ�����Ϊԭ��һ��.ʵ�ʾ��Ǳ����ֽ����x��y10�������֮��,������2�������ӵ���ʽ��ϳ���,
        ��10��������һ�����Ա�ʾ��2��������,���x��һ��������Ծ����yͬ��ȵ�
        */
        if(dep[fa[x][i]]>=dep[y])
            x=fa[x][i];
    }
    if(x == y) return x;//���֮ǰ��Ƚ�С��y�պ���x������,��ô��ʱ��x����Ϊx��y����lca
    /*
    ������ͬһ��ȵ�x��yͬʱ������,Ҳ���������������ϴ������,��������,�͸���x��yΪ��ǰ���Ƚڵ�,֮������СΪ��һ��
    Ҳ�ǴӴ�С��,һ��������Ծ�����������ܴ��������,���ǲ������,����С��2^0�η���ʼ�����ܻ����,��Ϊ���ǵ�lca��������
    �ľ�������Ǹ�ż��
    */
    for(int i =20;i>=0;i--){//�˴�2^20�η�ͬ��ö���������������Ͻ�
        /*
        eg:1.�����һ��2^0�η����׽�����,���շ���fa[x][0]
           2.��2^1�η����,2^0�η������,x��y���µ��丸�׽��,��֮ǰ��2^1�η����,�������ջ��Ƿ���fa[x][0].
           3.��2^2�η����,2^1�η������,x��y���µ��丸�׽��,2^0�η������,x��y���µ��丸�׽��,��֮ǰ��2^2�η����,�������ջ��Ƿ���fa[x][0]
        */
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];//x��yֻ����������һ�������ǵĸ��׽�����x��y��lca
}

int main(){
    int x,y;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&x,&y);
        /*
        ����������,��Ϊ�����s���ڵ��������,��һ����һ��ʼ�����Ϊ0���Ǹ���,�п������м�ĳ����,
        ������������Ϊ��ȱ�����ıߵĶ˵㣬���Ҫ����˫���,���ܱ����������Ϊ���ڵ�����н��.
        */
        addEdge(x,y);
    }
    dfs(s,0);//����Ĭ�ϸ��ڵ�����Ƚ����0��㣬ʵ��û�����壬ֻ����Ϊ�����Ϊ2ʱ,�����������ĵ�2^1�����Ƚڵ����ǻ��õ�0���
    while(m--){
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x,y));//����x��y����lca
    }
    return 0;
}
/*
��ȡlcaʱ x��y���֮��ͨ��,��10����ת��Ϊ������ �Ա�ÿһλ�ĸ���1���ӽ�С��1��ʼ������
ע�������Ǵ�С�����,����һ����Ҫ��֤��������һ��,��Ӧ�����ת��Ϊ�������Ժ� �Ƿ�����һλ��1,
��Ϊ����֤ ԭ�����Ǹ�ż��,ֱ����1,���վͻ����,������ö�ٳ��Ķ�����1��һ�����������10��������.
#include <bits/stdc++.h>
using namespace std;
#define P pair<int, int>
const int MAXN = 500000 + 5;
int N, M, S;
int head[MAXN], cnt;
vector<P> ask;
int fa[MAXN][20], depth[MAXN];
struct Edge{
	int to, dis, next;
}edge[MAXN << 1];
void add_edge(int u, int v, int dis) {
	edge[++cnt].to = v;
	edge[cnt].dis = 0;
	edge[cnt].next = head[u];
	head[u] = cnt;
}
void init() {
	cnt = 1;
	memset(head, 0, sizeof(head));
	memset(depth, 0 , sizeof(depth));
	memset(fa, 0, sizeof(fa));
	ask.clear();
}
//����ÿ���ڵ�����, ������������
void DFS (int now, int pre) {
	depth[now] = depth[pre] + 1;
	fa[now][0] = pre;
	for (int i = 1; (1 << i) <= depth[now]; ++i) {
		fa[now][i] = fa[fa[now][i - 1]][i - 1];
	}
	for(int i = head[now]; i; i = edge[i].next) {
		if(edge[i].to != pre) {
			DFS(edge[i].to, now);
		}
	}
}
int LCA(int a, int b) {
	//�� a ���ڸ��͵����
	if (depth[a] < depth[b]) swap(a, b);
	//Ȼ���� a ��������������b��ͬ���
	//����a��b�����֮�� �ǽ�10���������ɶ������� ͨ��(1<<i) & dep ��λ������ж�2����λ����һλ��1(ȥ��װ�����������),
	//��������Ծ���ĸ�����,�ӵ�λ�ж�,�ӽϽ������ȿ�ʼ��,��Ϊһ��10��������һ���ܱ�ʾ��2���Ƶ���ʽ�� ��С������ �Ƿ�Ч�ʵ͵� �д���֤
	//ע�������Ǵ�С�����,����һ����Ҫ��֤��������һ��,��Ӧ�����ת��Ϊ�������Ժ� �Ƿ�����һλ��1,��Ϊ����֤ ԭ�����Ǹ�ż��,ֱ����1,���վͻ����,������ö�ٳ��Ķ�����1��һ�����������10��������
	int dep = depth[a] - depth[b];
	for (int i = 0; (1 << i) <= dep; ++i) {
		if ((1 << i) & dep) {
			a = fa[a][i];
		}
	}
	//��� b ������ a ͬһ���ʱ a == b ��ֱ�ӷ��ظýڵ�(�ýڵ����a b��LCA)
	if(a == b) return a;
	//���� a b ͬʱ���ϱ���  ����Զ�Ŀ�ʼ��
	for (int i = log2(depth[a]); i >= 0; --i) {
			//������ײ�ͬ���������� ���������ͬ�ͼ�С�����ٱȽϣ�ֱ������ͬ������
		if (fa[a][i] != fa[b][i]) {
			a = fa[a][i];
			b = fa[b][i];
		}
	}
	return fa[a][0];
	//������� a �� b ���������LCAֻ��һ�� ���Է��� dp[a][0] ����
}
int main() {
	scanf("%d%d%d", &N, &M, &S);
	init();
	int x, y;
	for (int i = 1; i < N; ++i) {
		scanf("%d%d", &x, &y);
		add_edge(x, y, 0);
		add_edge(y, x, 0);
	}
	for (int i = 1; i <= M; ++i) {
		scanf("%d%d", &x, &y);
		ask.push_back(make_pair(x, y));
	}
	DFS(S, 0);
	for(int i = 0; i < ask.size(); ++i) {
		int ans = LCA(ask[i].first, ask[i].second);
		printf("%d\n", ans);
	}
	return 0;
}
*/
/*����Ͻ�log���׹�ʽ���㷨 t=log(n)/log(2);
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 500100
int head[N],fa[N][21],dep[N],n,m,s,cnt,t;
struct Node{
    int to,next;
}edge[N<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to]};
    head[to]=cnt++;
}

void dfs(int u,int fath){
    fa[u][0]=fath;
    dep[u]=dep[fath]+1;
    for(int i=1;(1<<i)<=dep[u];i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fath)
            dfs(v,u);
    }
}

int lca(int x, int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=t;i>=0;i--){
        if(dep[fa[x][i]]>=dep[y])
            x=fa[x][i];
    }
    if(x == y) return x;
    for(int i =t;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

int main(){
    int x,y;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&s);
    t=log(n)/log(2);
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",&x,&y);
        addEdge(x,y);
    }
    dfs(s,0);
    while(m--){
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x,y));
    }
    return 0;
}
*/
