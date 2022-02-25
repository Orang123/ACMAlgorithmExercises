#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 20
#define M 400
using namespace std;
//15ms ���ݱȽ�ˮ,ֻ����������,Ҳ�ܹ�
/*
����:����һ��������,�����=���ϱ�Ȩ��/��Ȩ��,
������n���ڵ����ȫͼ,Ҫѡȡk���ڵ㹹�ɱ�����,����С�ı�����,
���ձ�Ŵ�С��������ڵ���,����ж���������������,
������ֵ�����С���Ǹ��ڵ�����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2489
˼·:��С������,��ѡȡ�ڵ�̶��������,��ȻҪ��Ȩ����С,
����ʹ�ñ�����С,��Ȼ����ö��ѡȡk���ڵ�����µ�����ȡmst,
��¼��С������.
��Ϊn<=15,2<=k<=n
2��˼·:dfs����ö��k���ڵ�Ŀ������(��������ֵ���)����kruskal,���߶�����ö��k���ڵ���Ӽ�
��ѡȡ��k���ڵ���������kruskal,�������stl��������ؽ����ֵ�������.
*/

int n,m,k,fa[N],vis[N];
double val[N],sum1,sum2;//sum1��Ȩ��,sum2��Ȩ��

struct List{
    int id[N];
    double rat;
    bool operator < (const List &x)const{
        if(rat != x.rat) return rat<x.rat;//���ʲ�ͬ,��������
        else{//������ͬ �����������
            for(int i=1;i<=k;i++)//��ǰλ��ͬ���ǱȽ���һλ,����Ͱ���ǰλ��
                if(id[i]!=x.id[i]) return id[i]<x.id[i];
            return 1;
        }
    }
};

vector<List> seq;

struct Edge{
    int u,v;
    double w;
    Edge(int u=0,int v=0,double w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(){
    init();
    int x,y,cnt=0;
    for(int i=1;i<=m;i++){
        if(!vis[edge[i].u] || !vis[edge[i].v]) continue;
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            cnt++;
            sum1+=edge[i].w;
            if(cnt == k-1) break;
        }
    }
}

int judge(int x){
    int cnt=0;
    while(x){
        if(x&1) cnt++;
        x>>=1;
    }
    return cnt;
}

int main(){
    double w;
    while(scanf("%d%d",&n,&k) && n+k){
        m=0;
        seq.clear();
        for(int i=1;i<=n;i++)
            scanf("%lf",&val[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%lf",&w);
                if(j>i) edge[++m]=Edge(i,j,w);
            }
        }
        sort(edge+1,edge+1+m);
        List tmp;
        int num;
        //��Ϊk<=2����ѡ2��,ѡȡ2���Ķ�����λ����С����3 0011
        for(int s=3;s<(1<<n);s++){
            if(judge(s) != k) continue;//�жϵ�ǰ������λ�Ƿ�ѡȡ��k��
            memset(vis,0,sizeof(vis));
            num=sum1=sum2=0;
            for(int i=0;i<n;i++){
                if(s & (1<<i)){
                    vis[i+1]=1;
                    tmp.id[++num]=i+1;
                    sum2+=val[i+1];
                }
            }
            kruskal();
            tmp.rat=sum1/sum2;
            seq.push_back(tmp);//�����������кͱ��ʴ�����
        }
        //��Ϊ���ն�����λ��10����ö�ٳ���״̬,���������Ĳ������ֵ���,���Ҫ����
        sort(seq.begin(),seq.end());
        printf("%d",seq[0].id[1]);
        for(int i=2;i<=k;i++)
            printf(" %d",seq[0].id[i]);
        printf("\n");
    }
    return 0;
}
/*
//dfs����ö��k�������������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
#define M 400
#define INF 1e18
using namespace std;

int n,m,k,fa[N],vis[N];
double val[N];

struct List{
    int id[N];
    double rat;
}tmp,ans;

struct Edge{
    int u,v;
    double w;
    Edge(int u=0,int v=0,double w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

double kruskal(){
    init();
    int x,y,cnt=0;
    double sum=0;
    for(int i=1;i<=m;i++){
        if(!vis[edge[i].u] || !vis[edge[i].v]) continue;
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            cnt++;
            sum+=edge[i].w;
            if(cnt == k-1) break;
        }
    }
    return sum;
}

void dfs(int st,int num,int sum){
    if(n-st+1<k-num) return;//��֦ ��ʣ�µ���С�ڻ���Ҫѡȡ�ĸ���ʱ ����
    if(num == k){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=k;i++)
            vis[tmp.id[i]]=1;
        tmp.rat=kruskal()/sum;
        //��ǰѡȡ������Ϲ�����ı�����С������¼����С��ʱ�Ÿ���,����ʱ��ǰ��¼���ֵ����������С��,������
        if(tmp.rat<ans.rat){
            ans=tmp;
        }
        return;
    }
    tmp.id[num+1]=st;
    dfs(st+1,num+1,sum+val[st]);
    dfs(st+1,num,sum);
}

int judge(int x){
    int cnt=0;
    while(x){
        if(x&1) cnt++;
        x>>=1;
    }
    return cnt;
}

int main(){
    double w;
    while(scanf("%d%d",&n,&k) && n+k){
        m=0;
        for(int i=1;i<=n;i++)
            scanf("%lf",&val[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%lf",&w);
                if(j>i) edge[++m]=Edge(i,j,w);
            }
        }
        sort(edge+1,edge+1+m);
        ans.rat=INF;
        dfs(1,0,0);
        printf("%d",ans.id[1]);
        for(int i=2;i<=k;i++)
            printf(" %d",ans.id[i]);
        printf("\n");
    }
    return 0;
}
*/
