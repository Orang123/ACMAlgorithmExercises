#include<cstdio>
#include<queue>
#include<cstring>
#define N 2010
#define INF 0x3f3f3f3f
using namespace std;
//�޷������Ȩͼ���·�͸�Ȩͼ�����·����
/*
����:n������,m���� ���s->t����̾���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1874
˼·:���·����.
*/

struct node{
    int to,w,next;
}edge[N];
int n,m,cnt,dis[N],head[N],num[N],vis[N];

/*
���BF�㷨�ܶ��ɳڲ���dis[u]ʵ�ʻ�û���ɳ�,��������INF,��ʱ����ɳ���û�������,�ܶ�ʱ�����ǲ�����Ҫ��ô�����õ��ɳڲ���
����Ȼ,ֻ����һ�α��ɳڵĽ��,�����ӵıߵĶ˵�,���п���������һ�ε��ɳڲ�����
��ô�����ö�����ά������Щ�����ܻ������ɳڲ�����,����ֻ���ʱ�Ҫ�ı���.
*/

void addEdge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].w=w;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void init(int s){
    for(int i=0;i<n;i++)
        dis[i]=(i==s?0:INF);
}
/*
�ʱ�临�Ӷ� �ﵽBF�㷨���Ͻ�O(VE) �о������ʵ�����ɳ����˳������ ����ÿ��������б߶��ῼ���ܷ��ɳ�,
ֻ���Ƿ���Ը���dis[v] �б�Ҫ�ٴθ�ֵ��ʱ�俪������ ����Ϊ��ʱ�ĵط��Ǹտ�ʼ������ɳڵĵ�,��Ȩ�Ͳ�������С��,�����ɳں��Ȩ�ͻ������С ����ͻ��ظ��ٴζ�dis[v]��ֵ
ʱ�俪��Ӧ������Ҫ������,spfa�ȽϺõ�һ�� ���ڵ�����Ѿ��ڶ��� �򲻻��ظ����,������Dijkstra�Ķ��Ż�,��Ϊ���������ݲ��ɱ�,���º��dis[v]�������������ٴβ������,
���ܵĶ���Dijkstra���ڲ�����̰�ĵĲ���,ÿ�ζ�ȡ�������㵥Դ·��Ȩֵ����С�ĵ���Ϊ�ɳڵ�ȥ����,������ÿ���ֲ�̰�Ĳ�����,�ܽϿ�ﵽһ��ȫ�����ŵĽ��,��:����
����ʱ�̹滮�����·,ʵ����Ч�ĵ����Ѷ�����ֻ��n��,ʣ�µĵ㶼��Ȩֵ�ͽϴ󱻸��¹���,�ɺ���,���ظ������Ȩֵ�ϴ��ĳЩ�� ������Ѿ������������ı��,ֱ�Ӻ��Ա������ı�,
���������������ʲôʱ�俪��,�ܵĶ���spfa�����ʱ�򷢻ӵĺܺ�,����ĳЩǿ������ֻ����Ȩ������,�����ᳫʹ��Dijkstra
*/
//����������ܹ���ӵĽ����� �޷�ȷ��,���ܵĶ����Ǳ�BF�㷨Ч��Ҫ�� ������õ�ʱ����Dijkstra����,�����ܹ���ӵ�Ԫ�ؾ���n����ʱ������ʱ��� O(V+E) ���������ӵ�Ԫ�ؿ���ԶԶ����n,ʱ�临�Ӷ�ȡ���ڽ�ͼ���ߵ�˳�� ��̫�÷���ʱ��
bool spfa(int s){
    queue<int> Q;
    int u,v;
    init(s);
    Q.push(s);
    vis[s]=1;
    while(!Q.empty()){//ÿ����ܿ��ܻ��ظ���Ӻܶ��
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            /*
            ����v�п����Ǹ��ڵ�����,�������÷��ʱ��,��Ϊv�����Ǹ��ڵ�,
            Ҳ�޷������ɳ�,��Ϊ��·��Ȩֵ������ֻ��Խ��Խ��.
            */
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                num[v]++;
                /*
                ��v����ӳ���n-1����˵����������n-2����������µ���v��Ȩ�ͼ���,
                �Լ����������Ѿ�����2Ȧ,Ҳ������ѭ����,˵��ͼ�к�����(��Ȩֵ֮��Ϊ����,ÿ��һȦ,Ȩֵ���ڼ���)
                */
                if(num[v] >= n) return false;//����Ӧ����>=n �ܶ���д���� >n ����
                if(!vis[v]){//�������ڶ�����,�����ظ������,ֻ����dis[v]����
                    Q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
    return true;
}

int main(){
    int s,t,a,b,x;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(head,-1,sizeof(head));
        memset(dis,0,sizeof(dis));
        memset(num,0,sizeof(num));
        cnt=0;
        while(m--){
            scanf("%d%d%d",&a,&b,&x);
            addEdge(a,b,x);
            addEdge(b,a,x);
        }
        scanf("%d%d",&s,&t);
        if(spfa(s)){
            if(dis[t]!=INF)
                printf("%d\n",dis[t]);
            else
                printf("-1\n");
        }
        else
            printf("ԭͼ���и���,���������·\n");
    }
    return 0;
}

/*
���P2850 �и��� dfs�汾,ֻҪĳ���㱻�������� ��˵�����и��� �о�����spfa��˵ dfs bfs��ȡ���· ���𲻴�,
ֻ��dfs�жϸ�����Ч�ʻ���ߵ�,��Ϊbfs��ʹ�и����������һ��·��������̵�ʱ,Ҳ����������ͼ��nȦ�����жϳ���.

�������չ�������֮ǰ�Ѿ���չ���ˣ���˵��һ��·�д��������������
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
struct CZP
{
	int next,to,dis;
}a[1000001];
int n,m,h[100001],b[100001],flag,t,top,dis[100001],w;
void cun(int from,int to,int dis)
{
	a[++top].next=h[from];
	a[top].to=to;
	a[top].dis=dis;
	h[from]=top;
}
void pd(int x)
{
	if (flag)
	return ;
	b[x]=1;
	int k=h[x];
	while (k!=-1)
	{
		if (dis[a[k].to]>dis[x]+a[k].dis)
		{
			dis[a[k].to]=dis[x]+a[k].dis;
			if (b[a[k].to])
			{
				flag=1;
				return ;
			}
			else
			pd(a[k].to);
		}
		k=a[k].next;
		}
	b[x]=0;
}   //����ʹ����dfs����Ȩ������
int main()
{
	scanf("%d",&t);
	for (int k=1;k<=t;k++)
	{
		flag=0;
	    scanf("%d%d%d",&n,&m,&w);
		for (int i=0;i<=n;i++)
		h[i]=-1;
		for (int i=1;i<=m;i++)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			cun(x,y,z);
			cun(y,x,z);
			}     //С·Ϊ˫��ߣ�
		for (int i=1;i<=w;i++)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			cun(x,y,-z);
		}   //�涴��Ϊ��Ȩֵ
		memset(b,0,sizeof(b));
		for (int i=1;i<=n;i++)
		cun(0,i,0);  //��������Դ��0
		for (int i=1;i<=n;i++)
		dis[i]=100000000;
		dis[0]=0;
		b[0]=1;
		pd(0);
		if (flag==1)
		printf("YES\n");
		else
		printf("NO\n");
	}
	return 0;
}
*/
