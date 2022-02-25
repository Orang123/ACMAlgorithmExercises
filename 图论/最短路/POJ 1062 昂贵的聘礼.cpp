#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;
//����wa  ������ԭ��
/*
����:http://poj.org/problem?id=1062  ��������
����:http://poj.org/problem?id=1062
˼·:ÿ����Ʒ�ı���ļ۸�w,����ͨ������Դ��(0)�������Ʒ��Ž�
һ��ȨֵΪw�ı�mp[0][i]=w,һ����Ʒt�һ���һ����Ʒ����Ҫ�ļ�Ǯv,
��ͨ������mp[t][i]=v�ı�.����ע��һ�ʱ�ĵȼ�Ҫ��,������ö��ĳ����Ʒ��
�ȼ����,Ȼ��ѵȼ��������ĺ͵ȼ�������֮���m���˳���,�ٿ�ʼ���·,
dis[1]�Ƚ���Сֵ��Ϊ��.
*/

int n,m,cnt,mp[N][N],vis[N],dis[N],rnk[N];

void init(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int Dijkstra(int s){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int v=1;v<=n;v++){
            if(!mp[u][v]) continue;
            if(dis[v]>dis[u]+mp[u][v]){
                dis[v]=dis[u]+mp[u][v];
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return dis[1];
}

int main(){
    int w,ans=INF,num,t,v;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&w,&rnk[i],&num);
        mp[0][i]=w;
        while(num--){
            scanf("%d%d",&t,&v);
            mp[t][i]=v;
        }
    }
    for(int i=1;i<=n;i++){
        vis[0]=0;
        for(int j=1;j<=n;j++){
            if(rnk[j]>=rnk[i] && rnk[j]<=rnk[i]+m)
                vis[j]=0;
            else
                vis[j]=1;
        }
        ans=min(ans,Dijkstra(0));
    }
    printf("%d",ans);
    return 0;
}

/*
ac
//https://blog.csdn.net/just_sort/article/details/49591481
//����Ĺؼ����ڵȼ����ƵĴ�����õİ취�ǲ���ö�٣������������ȼ�Ϊ5���ȼ�����Ϊ2����ô��Ҫö�ٵȼ���3~5,4~6,5~7
//Ȼ�����dij�ˣ�����ΪʲôҪ��dij��������ϲ�ã��Ͼ�����ȼ�����Ҫ��vis������б��
//�����˵ȼ����⣬�Ϳ���ö�ٵȼ����飬n��dij���걾���ˣ�nlogn0ms�㶨
//����Ϊ�������
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define inf 0x3fffffff
int maze[110][110];
int dis[110],degree[110],val[110],vis[110];
int m,n;
void init()
{
    memset(dis,inf,sizeof(dis));
    for(int i=1;i<=n;i++)
       for(int j=1;j<=n;j++)
          maze[i][j]=inf;
}

int dij()
{
    for(int i=1;i<=n;i++)
        dis[i]=val[i];
    for(int i=1;i<=n;i++)
    {
        int minn=inf,mark=inf;
        for(int j=1;j<=n;j++)
        {
            if(!vis[j]&&dis[j]<minn)
            {
                minn=dis[j];
                mark=j;
            }
        }
        if(minn==inf)break;
        vis[mark]=true;
        for(int j=1;j<=n;j++)
        {
            if(!vis[j]&&dis[j]>dis[mark]+maze[mark][j])
            {
                dis[j]=dis[mark]+maze[mark][j];
            }
        }
    }
    return dis[1];
}
int main()
{
    while(~scanf("%d%d",&m,&n))
    {
        init();
        int x,a,b,tmp;
        int ans=inf;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d%d",&val[i],&degree[i],&x);
            while(x--)
            {
                scanf("%d%d",&a,&b);
                maze[a][i]=b;
            }
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(degree[j]>=degree[i]&&degree[j]<=degree[i]+m)
                {
                    vis[j]=false;
                }
                else
                {
                    vis[j]=true;
                }
            }
            tmp=dij();
            ans=min(ans,tmp);
        }
        cout<<ans<<endl;
    }
    return 0;
}

*/
/*
ac
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
//https://blog.csdn.net/SongBai1997/article/details/83216252
using namespace std;

const int N=105;
const int INF=0x3f3f3f3f;
int dist[N];
int rank[N];//ÿ����Ʒ�ĵȼ�
int g[N][N];
bool vis[N];

struct Node{
	int u,w;
	//Node(){}
	Node(int u,int w):u(u),w(w){}
	bool operator<(const Node &a)const
	{
		return w>a.w;
	}
};

int n,m;
void dijkstra(int l,int h)//ֻ���ǽ��ȼ���[l,h]�еĽ��
{
	memset(dist,INF,sizeof(dist));
	memset(vis,false,sizeof(vis));
	dist[0]=0;
	priority_queue<Node>q;
	q.push(Node(0,0));
	while(!q.empty()){
		Node f=q.top();
		q.pop();
		int u=f.u;
		if(!vis[u]){
			vis[u]=true;
			for(int i=1;i<=n;i++)
			  if(!vis[i]&&g[u][i]!=INF&&l<=rank[i]&&rank[i]<=h&&dist[i]>dist[u]+g[u][i]){
			  		dist[i]=dist[u]+g[u][i];
			  		q.push(Node(i,dist[i]));
			  }
		}
	}
}

int main()
{
	scanf("%d%d",&m,&n);
	int p,l,x,t,v;
	memset(g,INF,sizeof(g));
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&p,&l,&x);
		rank[i]=l;
		g[0][i]=p;//ֱ�ӻ�Ǯ��
		while(x--){
			scanf("%d%d",&t,&v);
			g[t][i]=v;
		}
	}
	int ans=INF;
	for(int i=rank[1]-m;i<=rank[1];i++){
	    dijkstra(i,i+m);
		ans=min(ans,dist[1]);
	}
	printf("%d\n",ans);
	return 0;
}
*/


