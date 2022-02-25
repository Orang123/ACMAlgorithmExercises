#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 1100
#define M 1000100
using namespace std;
//ac 10ms tarjan�������ebc
//�����ϸ���:https://www.luogu.com.cn/problem/solution/UVA10972 û̫��ϸ��,��ʱ���ٿ���.
/*
����:һ������ͼҪ��Ӷ������߲���ʹ���Ϊ��˫��ͨͼ,ԭͼ���ܲ���ͨ.
��һ������:����һ��n����m���ߵ�����ͼ,��һ����ͨ.��������Ҫ��ԭ�е�����߱�Ϊ�����,
������һЩ�µ������.�����ټ�������������ʹ��ͼֻ��һ��ǿ��ͨ����.
ԭӢ������ �е㿴������,�о���˼�ǵڶ�������,�ӵ��������.
����:https://www.luogu.com.cn/problem/UVA10972
˼·:������ԭͼ��ͨ�İ취tarjan�������������,���ڶ�Ϊ1��Ҷ�ӽڵ�,ans+=1,
���ڱ������ĵ��Ϊ0,ans+=2,������ټӱ���=(ans+1)/2.
*/

int n,m,dfn[N],low[N],clock,cnt,ebc_cnt,head[N],block[N],de[N];
stack<int> s;

struct Edge{
    int from,to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Edge){from,to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    s.push(u);
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        ebc_cnt++;
        do{
            v=s.top();
            s.pop();
            block[v]=ebc_cnt;
        }while(v!=u);
    }
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        ebc_cnt=clock=cnt=0;
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        memset(de,0,sizeof(de));
        while(m--){
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }
        for(int i=1;i<=n;i++){//ԭͼ���ܲ���ͨ
            if(!dfn[i])
                dfs(i,-1);
        }
        //��Ϊͼ����ͨ����� Ҫ�ж϶�Ϊ0 +2�����,����ԭͼ������¾���EBG,Ҫ����
        if(ebc_cnt == 1){//ԭͼ������Ǳ�˫��ͨͼ,����Ҫ��ӱ�,���0.
            printf("0\n");
            continue;
        }
        for(int i=0;i<cnt;i+=2){
            u=edge[i].from;
            v=edge[i].to;
            if(block[u]!=block[v]){
                de[block[u]]++;
                de[block[v]]++;
            }
        }
        int ans=0;
        for(int i=1;i<=ebc_cnt;i++){
            if(!de[i]) ans+=2;//ԭͼ����ͨ�������� ��Ϊ0������,+2
            if(de[i] == 1) ans++;//���ڶ�Ϊ1��Ҷ�ӽڵ�+1
        }
        printf("%d\n",(ans+1)/2);
    }
    return 0;
}

/*
//��һ�ָ���д��,�о��е�û��Ҫ
//https://www.cnblogs.com/scau20110726/archive/2013/05/18/3086330.html
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;
#define N 1010

int n,tot;
int dfn[N],low[N],vis[N],de[N],dcnt,bcnt;
vector<int>e[N];

void init()
{
    dcnt = bcnt = 0;
    for(int i=1; i<=n; i++)
    {
        dfn[i] = 0;
        e[i].clear();
        vis[i] = de[i] = 0;
    }
}

void dfs(int u ,int fa)
{
    dfn[u] = low[u] = ++dcnt;
    vis[u] = 1;
    for(int i=0; i<e[u].size(); i++)
    {
        int v = e[u][i];
        if(v == fa) continue;
        if(!vis[v]) //����
        {
            dfs(v,u);
            low[u] = min(low[u] , low[v]);
            if(low[v] > dfn[u]) //�ҵ�һ����,����һ����ͨ����
                bcnt++;
        }
        else if(vis[v] == 1) //�����
            low[u] = min(low[u] , dfn[v]);
    }
}

void solve()
{
    for(int i=1; i<=n; i++)
        if(!vis[i])
        {
            dfs(i,-1);
            bcnt++;
        }
    if(bcnt == 1) //����ͼ������Ǹ�˫��ͨ����
    { cout << 0 << endl; return ; }

    bool used[N];
    memset(used,false,sizeof(used));
    for(int i=1; i<=n; i++)
    {
        if(e[i].size() == 0) //�����㣬�������γ�һ����ͨ����
        { used[low[i]] = true ; continue; }

        for(int j=0; j<e[i].size(); j++)
        {
            int u = i;
            int v = e[i][j];
            used[low[u]] = used[low[v]] = true;
            if(low[u] != low[v]) //��ͬ����ͨ����
                de[low[u]]++;
        }
    }

    int res = 0;
    for(int i=1; i<=n; i++)  //ɨ�������ÿ����Ķ�
        if(used[i] && de[i] == 0) //��Ϊ0��������
            res += 2;
        else if(de[i] == 1) //Ҷ��
            res++;
    cout << (res+1)/2 << endl;
}

int main()
{
    while(cin >> n >> tot)
    {
        init();
        while(tot--)
        {
            int u,v;
            cin >> u >> v;
            e[u].push_back(v);
            e[v].push_back(u);
            //͵��ֱ����vector��ͼ���þ�̬������
        }
        solve();
    }
    return 0;
}
*/

/*
//�������������ǽ�����ͼת��Ϊ����ͼ,������߿��ǵ�.
//https://www.luogu.com.cn/problem/solution/UVA10972
#include <stack>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

const int N = 1010;

int n, m, color, tot;
int col_p[N], dfn[N], low[N];
bool in[N], visit[N];
std::vector <int > link[N];
std::vector <int > new_link[N];
std::stack <int > s;

void tarjan(int wz, int fa)//����ͼ��...��������ͼ
{
	dfn[wz] = low[wz] = ++tot;
	in[wz] = true, s.push(wz);

	for(int k = 0; k < (int )link[wz].size(); k++)
	{
		int to = link[wz][k];

		if(!dfn[to])
		{
			tarjan(to, wz);
			low[wz] = std::min(low[wz], low[to]);
		}
		else if(in[to] && to != fa)
			low[wz] = std::min(low[wz], dfn[to]);
	}

	if(low[wz] == dfn[wz])
	{
		color++;

		while(s.top() != wz)
		{
			col_p[s.top() ] = color;

			in[s.top() ] = false, s.pop() ;
		}

		col_p[wz] = color;

		in[s.top() ] = false, s.pop() ;
	}
}

void build()
{
	for(int k = 1; k <= n; k++)
		for(int i = 0; i < (int )link[k].size() ; i++)
		{
			int to = link[k][i];

			if(col_p[to] != col_p[k])
				new_link[col_p[to]].push_back(col_p[k]);
		}
}

int answ;

int dfs(int wz, int fa)
{
	visit[wz] = true;

	int size1 = (int )new_link[wz].size();

	int size0 = size1 == 0 ? 2 : size1 == 1 ? 1 : 0;

	for(int k = 0; k < (int )new_link[wz].size(); k++)
	{
		int to = new_link[wz][k];

		if(to != fa)
			size0 += dfs(to, wz);
	}

	return size0;
}

void work()
{
	memset(link, 0, sizeof(link));
	memset(new_link, 0, sizeof(new_link));
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(visit, 0, sizeof(visit));
	tot = color = answ = 0;

	for(int k = 1; k <= m; k++)
	{
		int l, r;
		scanf("%d %d", &l, &r);

		link[l].push_back(r);
		link[r].push_back(l);
	}

	//����
	for(int k = 1; k <= n; k++)
		if(!dfn[k])
			tarjan(k, 0);

	//�ؽ�ͼ
	build();

	//��������Ϊ0��1�ĵ�
	for(int k = 1; k <= color; k++)
		if(!visit[k])
			answ += dfs(k, 0);

	if(color!=1)
		printf("%d\n", (int )ceil(answ / 2.0));
	else
		printf("0\n");
}

int main()
{
	while(scanf("%d %d", &n, &m) != EOF)
	{
		work();
	}

	return 0;
}
*/
