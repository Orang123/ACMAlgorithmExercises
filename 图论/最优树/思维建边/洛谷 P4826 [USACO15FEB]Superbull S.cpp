#include<cstdio>
#include<algorithm>
#define N 2100
#define M 2000000
using namespace std;
typedef long long ll;
//kruskal ac 2.98s
/*
����:n�����������б���,ÿ�λ���̭1��,ÿ�������ĵ÷���2����
id�����ֵ,����α���ʹ���б����ܵ÷����.
����:https://www.luogu.com.cn/problem/P4826
˼·:�ܹ������n-1������,��ÿ���˺ͱ��˵ı������Կ���,
����˺��������������,ÿ�α���ֻ��ʤ�߻���ű���,�����
���ɶ���a-b���bʤ��,��ô��������������bȥ�����aʤ��,������
������aȥ��,��������n-1���������������ɵ�һ����һ����,��ô����
����ת����������ȫͼ�������������������.ÿ���˿ɺ�����������
���б���,�������ȫͼ,��ͼΪ����ͼprim���Щ.
*/

int n,m,fa[N],a[N];

struct Edge{
    int u,v;
    ll w;
    Edge(int u=0,int v=0,ll w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w>x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

ll kruskal(){
    init();
    int x,y,cnt=0;
    ll sum=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            sum+=edge[i].w;
            cnt++;
            if(cnt == n-1) break;
        }
    }
    return sum;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){//��ȨΪ��id�����ֵ
            edge[++m]=Edge(i,j,a[i]^a[j]);
        }
    }
    printf("%lld",kruskal());
    return 0;
}

/*
//prim 573ms
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 2100
using namespace std;
typedef long long ll;

int n,m,a[N],dis[N],vis[N],mp[N][N];

void init(){
    memset(vis,0,sizeof vis);
    memset(dis,0,sizeof dis);
}

ll prim(int s){
    init();
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,num=0;
    ll sum=0;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        num++;
        sum+=dis[u];
        if(num == n) break;
        for(int v=1;v<=n;v++){
            if(!vis[v] && mp[u][v]>dis[v]){
                dis[v]=mp[u][v];
                Q.push(make_pair(dis[v],v));
            }
        }
    }
    return sum;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i!=j)
                mp[i][j]=a[i]^a[j];
        }
    }
    printf("%lld",prim(1));
    return 0;
}
*/
