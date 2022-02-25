#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 3100
#define M 9000100
#define INF 0x3f3f3f3f
using namespace std;
//kruskal 1154ms ac
/*
����:n����,m����,���mst,��q��ѯ��,ÿ��ѯ�ʻ��ԭ�ȱ��滻ΪȨֵ�ϴ�ı�,
��q��ѯ���滻���mstȨֵ�͵�ƽ��ֵ.
����:http://acm.hdu.edu.cn/showproblem.php?pid=4126
˼·:q<=10000,��Ȼ��q��kruskal,�����϶���TLE.
����ÿ��ѯ��,���ǽ�a��b֮��ı����ӵ�c,������������:
1.�����Ȩ���ӵ�������ԭ�ȾͲ�����С��������,��ô��ʱ�����С��������ֵ����
2.����ñ���ԭ��С��������,��ô��ʱ�����ӵıߴ�ԭ��С��������ȥ��,
��ʱ���������ͱ��ֳ�������������ͨ�Ĳ���,����֤������,
��ʱ�����С������һ���ǽ�����������ͨ��������С��������.
��kruskal�������������ͼ,��dp���dp[i][j].������ֻ��Ҫ��һ��kruskal.
dp[i][j]��ʾȥ����С�������еı�(i,j)�ֳ�������ͨ���ֺ�,�������ٴ�������������С�������߳�.
http://www.mamicode.com/info-detail-410392.html ����ժ����ƪ����
*/
//ѯ���ж��Ƿ���mst�� ��pre[u]!=v pre[v]!=u��wa,����
//https://blog.csdn.net/qq_36889101/article/details/88789284 ���pre�ж�ǰ����ac��
int mp[N][N],n,m,q,fa[N],sum,head[N],cnt,dp[N][N],vis[N][N];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

struct Node{
    int to,next;
}node[N<<1];

void addEdge(int from,int to){
    node[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void init(){
    sort(edge+1,edge+1+m);
    for(int i=0;i<n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(){
    init();
    int x,y,num=0,a,b;
    for(int i=1;i<=m;i++){
        a=edge[i].u,b=edge[i].v;
        x=find(a),y=find(b);
        if(x!=y){
            fa[x]=y;
            num++;
            sum+=edge[i].w;
            vis[a][b]=vis[b][a]=1;//���u->v v->u������Ϊ�������еı�
            addEdge(a,b);//����mst��ͼ,����dp
            addEdge(b,a);
            if(num == n-1) break;
        }
    }
}

int dfs(int u,int fa,int rt){
    int res=INF;
    for(int i=head[u];i!=-1;i=node[i].next){
        int v=node[i].to;
        if(v == fa) continue;
        int tmp=dfs(v,u,rt);//tmp����v��������rt�������нڵ�(����v)��������С��
        res=min(res,tmp);//res����u������������rt�������нڵ�(����u)��������С��
        /*
        dp[u][v] �ǶϿ�u->v������,��ô���ֿ�����һ����ͨ����v������,����Ҫʹ�÷ֿ���v��������ͨ���ٴ�����,
        rtҪ��v�����ӽڵ����߲���ʹ��mst�ٴ���ͨ.���ܺ�u�������ӽڵ����������,������ʹ���ߵ�ǰv�ڵ������
        ��Ȼ�Ƿ����.
        */
        dp[u][v]=dp[v][u]=min(dp[u][v],tmp);
    }
    //��u�ĸ��ڵ�Ϊrtʱ,dp[rt][u]����ʱ����ȡmp[rt][u],��Ϊrt->u�������Ѿ����жϵ�,������ȡ
    //�������res���rt->u������Ȩȥ�Ƚ�����С
    if(rt!=fa) res=min(res,mp[rt][u]);
    return res;
}

int main(){
    int u,v,w;
    double ans;
    while(scanf("%d%d",&n,&m) && n+m){
        ans=cnt=sum=0;
        memset(head,-1,sizeof head);
        memset(vis,0,sizeof vis);
        memset(mp,0x3f,sizeof mp);//�����ı߲�һ��������ȫͼ,����Ҫ��ʼ��.
        memset(dp,0x3f,sizeof dp);
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&u,&v,&w);
            edge[i]=Edge(u,v,w);
            mp[u][v]=mp[v][u]=w;
        }
        kruskal();
        //��ÿ������Ϊ���ڵ�ͱ��ָ����һ����ͨ������,���¸�С��dp[u][v]
        for(int i=0;i<n;i++)//O(n^2)
            dfs(i,-1,i);
        scanf("%d",&q);
        for(int i=1;i<=q;i++){
            scanf("%d%d%d",&u,&v,&w);
            //u->v����mst��,���ε�Ȩֵ�;��ǳ�ʼmst��Ȩֵ��
            if(!vis[u][v] && !vis[v][u]) ans+=sum;
            else ans+=(sum-mp[u][v]+min(w,dp[u][v]));
        }
        printf("%.4f\n",ans/q);//
    }
    return 0;
}
