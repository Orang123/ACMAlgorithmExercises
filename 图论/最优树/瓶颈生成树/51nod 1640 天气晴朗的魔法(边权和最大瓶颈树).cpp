#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 100100
#define M 200100
using namespace std;
typedef long long ll;
//kruskal 437ms ���̰�ĵ�˼ά��prim��̫��ʵ�� ��Ȼ���ǳ���ͼ
/*
����:n����,m���ߵ�ͼ,��ȡһ����ʹ�����ı�Ȩ,
������������������С��,ͬʱʹ�ñ�Ȩ��������.
����:http://www.51nod.com/Challenge/Problem.html#problemId=1640
˼·:��������Ȩ������ƿ��������,����Ȩ��С��������kruskal���
mst������ı�,Ȼ���Ȩ�������Է�����̰��,���ǰ��ձ߼��Ӵ�Сȥ����,
С�ڵ���֮ǰ������Ȩ�ľ����ܼӱ�,��������ı�Ȩ�;�������.����.
*/

int n,m,fa[N];

struct Edge{
    int u,v;
    ll w;
    Edge(int u=0,int v=0,ll w=0):u(u),v(v),w(w){}
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

ll kruskal(){
    init();
    sort(edge+1,edge+1+m);
    int x,y,maxw,num=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[y]=x;
            num++;
            if(num == n-1){
                maxw=edge[i].w;
                break;
            }
        }
    }
    init();
    ll sum=0;
    num=0;
    for(int i=m;i>=1;i--){//��m��ʼ ����Ϊ�п�������Ȩ����ıߺ�����Ȩ���
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y && edge[i].w<=maxw){
            fa[y]=x;
            sum+=edge[i].w;
            num++;
            if(num == n-1) break;
        }
    }
    return sum;
}

int main(){
    int u,v;
    ll w;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d%lld",&u,&v,&w);
        edge[i]=Edge(u,v,w);
    }
    printf("%lld\n",kruskal());
    return 0;
}
