#include<cstdio>
#include<algorithm>
#define N 250
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;
//78ms
/*
����:http://acm.hdu.edu.cn/showproblem.php?pid=1598
n����,m���ߵ�����ͼ,���s��e������·������������С��֮��
����Сֵ.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1598
ע��:�������prim+dp,��ȡ·����С��Ȩ������Ȩ,������ϵĲ�ֵ��һ������С��,
�п��ܲ������ϵ�·����ֵ������С��.
˼·:ö��ÿ���߿�ʼkruskal����С���Ĺ���,��s��e��һ������ʱ,
��¼��ǰ��Ȩ����ʼ��Ȩ�Ĳ�ֵ,ȡ��С.�������С��ֵ����ʱ��
��һ��������,��Ϊs��e��·���ϵ���С��Ȩ��һ�����ǳ�ʼ��,
����С�߲��ǳ�ʼ��ʱ,���ʱ���ֵ��ƫ���,��������ʼ�ߴ���С�߿�ʼʱ,
���ֵ����¸�С,���Ա���ö�����ܱ�֤���յĽ����ȷ��.
*/

int n,m,q,fa[N],ans;

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
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

void kruskal(int st,int s,int e){
    init();
    int x,y;
    for(int i=st;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y)
            fa[y]=x;
        //���ﻹ����Щ�����,���ǳ�ʼö�ٵ���С��Ȩ��һ������s��e��·����,Ҳ���������ֵ����ʱ����ʵ����ƫ��û�������
        //������Ϊ��ʼ��Ȩö�����б߶��ῼ��,�������տ϶���һ��kruskal�������С��ֵ,����ʵ�ʾ�����Ϊ��֪��ʲôʱ��s��e��
        //edge[i].w-edge[st].w����ȷ�������,��Ҫ����ö�����бߵ�
        if(find(s) == find(e)){
            ans=min(ans,edge[i].w-edge[st].w);
            break;
        }
    }
}

int main(){
    int s,e;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        sort(edge+1,edge+1+m);
        scanf("%d",&q);
        while(q--){
            scanf("%d%d",&s,&e);
            ans=INF;
            for(int i=1;i<=m;i++){
                kruskal(i,s,e);
                if(ans == INF){//ans == INFʱ�����������е����߶�����ʹ��s��e��ͨ,��û��Ҫ��ö����
                    ans=-1;
                    break;
                }
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
