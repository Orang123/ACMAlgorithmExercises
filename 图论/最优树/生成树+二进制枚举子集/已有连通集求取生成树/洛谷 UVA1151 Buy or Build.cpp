#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 500100
using namespace std;
//ac kruskal 50ms primʵ�ֽ�Ϊ������ǵ㼯,��һ�λ��ð����������ѱ�ǵ㼯��������prim
//����ö�������Ӽ�Ҳ���Բ��ñ���ö��
/*
����:��������n����(1<=N<=1000),ÿ�����ж�Ӧ����,���������������n������ͨ,
Ϊ��,������½�һЩ��,���õ��������˵��ŷ����þ����ƽ��.
���⻹��q(0<=q<=8)������,���Թ���,����㹺���˵�i������,
�������е����н�㽫����໥��ͨ,��i�������Ļ���Ϊcost[i].
��ʹ���е���ͨ����С����.
����:https://www.luogu.com.cn/problem/UVA1151
˼·:��Ȼ��������ʹ�������ڵĵ㶼��ͨ,����Ҫ����cost[i],
Ҳ����˵����������һ����ֱ�ӹ��������֮���������ߵ�������õ�,
��ô���޷�̰�����,��Ҫö�ٲ����������Լ����������Щ������ϵ����з���,
���������Ŀ�����Ϸ��� ��Ϊq<=8,���Կ��Բ��ö�����λ����ʾ���,��1<<q-1����
���з����ĸ���.��ѡȡ����,��fa[N]�п��ܵı����Ӽ��Ϻϲ�,����kruskal,�Ƚϼ�¼
��С����.
�����и�С�Ż�:ö��������Ϸ��������ڵ�һ�����mst�ó��ı߼��Ļ�����ö��,
��Ϊ��ʹö������,����kruskal,�ӱ�ʱ���ǻ�ѡȡ��Ȩ��С�ӱ�,��ô���������Ѿ�
��ͨ�ĵ���,�ڽ��������mstʱ���ӵı���Ȼ��n-1������ʣ�µı�,�����ῼ�Ǳ�������n-1��
�ߺ�ı�.
���ⲻͬ���� ������ѱ߲�û����ȷָ��,���Ǹ���һ�����ϻ�ͨ���������.�����Ҫ
ö�ٳ���������Ӷ�������С�Ļ���,�޷���ĳ���Ƕ�̰��ѡȡ.
*/

int n,m,q,t,fa[N],cost[8],cnt;
vector<int> G[8];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge1[M],edge2[N];

struct Point{
    int x,y;
}point[N];

int getDis(int x1,int y1,int x2,int y2){
    return (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
}

void init(){
    cnt=0;
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int Union(int a,int b){
    int x=find(a);
    int y=find(b);
    if(x!=y){
        fa[x]=y;
        return 1;
    }
    return 0;
}

int kruskal(int sum){
    for(int i=1;i<=t;i++){
        if(Union(edge2[i].u,edge2[i].v)){
            sum+=edge2[i].w;
            cnt++;
            if(cnt == n-1) break;
        }
    }
    return sum;
}

int main(){
    int T,u,ans;
    scanf("%d",&T);
    while(T--){
        for(int i=0;i<8;i++)
            G[i].clear();
        scanf("%d%d",&n,&q);
        for(int i=0;i<q;i++){//��������
            scanf("%d%d",&m,&cost[i]);
            while(m--){
                scanf("%d",&u);
                G[i].push_back(u);
            }
        }
        m=0;
        for(int i=1;i<=n;i++)//���������
            scanf("%d%d",&point[i].x,&point[i].y);
        for(int i=1;i<=n;i++){//������ȫͼ�ı߼�
            for(int j=i+1;j<=n;j++){
                int w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                edge1[++m]=Edge(i,j,w);
            }
        }
        ans=t=0;
        init();
        sort(edge1+1,edge1+1+m);
        for(int i=1;i<=m;i++){//��ѡ�񲻼����κ����� ���һ��mst,����¼��n-1��
            if(Union(edge1[i].u,edge1[i].v)){
                cnt++;
                ans+=edge1[i].w;
                edge2[++t]=edge1[i];//��mst�ı߼�¼��edge2��
                if(cnt == n-1) break;
            }
        }
        //��edge2 n-1���߻�����ö�������ķ��� eg:01010110 ����ѡ����Ϊ2��3��5��7������
        for(int s=1;s<(1<<q);s++){//s����ÿ������ѡ�����,��1��ʼ,����һ��Ҳ��ѡ,�ܹ���8������,(1<<8-1) �ڵ���������λ������ 8��������״̬(ѡ�벻ѡ)
            init();
            int sum=0;
            for(int i=0;i<q;i++){
                //Ҳ��(s>>i) & 1�ж�
                if(s&(1<<i)){//s& 1<<i������Ϊi������״̬Ϊѡ�� �ͽ�����i�ڵĵ���벢�鼯
                    sum+=cost[i];
                    for(int j=1;j<G[i].size();j++)//����Ҳͬ��Ҫ�ж����ܹ��ɻ�·,��Ϊ��ͬ�������н���,���ɻ�· find����ѭ��
                        if(Union(G[i][0],G[i][j]))//�������еڶ����㿪ʼ ��ѡ��͵�һ������,����find����С��ѯ�Ĳ���,�ﵽ·��ѹ����Ŀ��
                            cnt++;//��������й����mst�еı�+1
                }
            }
            ans=min(ans,kruskal(sum));
        }
        printf("%d\n",ans);
        if(T) printf("\n");//��ͬ�������֮�����п���,���һ��������û�п���
    }
    return 0;
}

/*
//dfs����ö���Ӽ�+kruskal ac 50ms
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define N 1100
#define M 500100
using namespace std;

int n,m,q,t,fa[N],cost[8],cnt,seq[8],ans;
vector<int> G[8];

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge1[M],edge2[N];

struct Point{
    int x,y;
}point[N];

int getDis(int x1,int y1,int x2,int y2){
    return (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
}

void init(){
    cnt=0;
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int Union(int a,int b){
    int x=find(a);
    int y=find(b);
    if(x!=y){
        fa[x]=y;
        return 1;
    }
    return 0;
}

int kruskal(int sum){
    for(int i=1;i<=t;i++){
        if(Union(edge2[i].u,edge2[i].v)){
            sum+=edge2[i].w;
            cnt++;
            if(cnt == n-1) break;
        }
    }
    return sum;
}

void dfs(int st,int num,int res){
    if(q-st<res-num) return;//��֦ ��ʣ�µ���С�ڻ���Ҫѡȡ�ĸ���ʱ ����
    if(num == res){
        int sum=0;
        init();
        for(int i=1;i<=res;i++){
            int j=seq[i];
            sum+=cost[j];
            for(int j=seq[i],k=1;k<G[j].size();k++){
                if(Union(G[j][0],G[j][k]))
                    cnt++;
            }
        }
        ans=min(ans,kruskal(sum));
        return;
    }
    //if(st>=q) return;
    seq[num+1]=st;
    dfs(st+1,num+1,res);
    dfs(st+1,num,res);
}

int main(){
    int T,u;
    scanf("%d",&T);
    while(T--){
        for(int i=0;i<8;i++)
            G[i].clear();
        scanf("%d%d",&n,&q);
        for(int i=0;i<q;i++){//��������
            scanf("%d%d",&m,&cost[i]);
            while(m--){
                scanf("%d",&u);
                G[i].push_back(u);
            }
        }
        m=0;
        for(int i=1;i<=n;i++)//���������
            scanf("%d%d",&point[i].x,&point[i].y);
        for(int i=1;i<=n;i++){//������ȫͼ�ı߼�
            for(int j=i+1;j<=n;j++){
                int w=getDis(point[i].x,point[i].y,point[j].x,point[j].y);
                edge1[++m]=Edge(i,j,w);
            }
        }
        ans=t=0;
        init();
        sort(edge1+1,edge1+1+m);
        for(int i=1;i<=m;i++){//��ѡ�񲻼����κ����� ���һ��mst,����¼��n-1��
            if(Union(edge1[i].u,edge1[i].v)){
                cnt++;
                ans+=edge1[i].w;
                edge2[++t]=edge1[i];//��mst�ı߼�¼��edge2��
                if(cnt == n-1) break;
            }
        }
        for(int i=1;i<=q;i++)
            dfs(0,0,i);
        printf("%d\n",ans);
        if(T) printf("\n");//��ͬ�������֮�����п���,���һ��������û�п���
    }
    return 0;
}
*/
