#include<cstdio>
#include<algorithm>
#define N 1100
#define M 30000
using namespace std;

/*
����:��һ��ͼG,���������������ͼ�����л�·�б�Ȩ���ı�Ȩ.
����:https://www.luogu.com.cn/problem/UVA11747
˼·:Ҫ�������·������Ȩ,���Կ���kruskal�ӱߵĹ���,�����ӱ�
���ɻ���ʱ��,���ӵ������߾�һ���������������Ȩ,��Ϊkruskal��
̰�Ĵ�С����ӱ�.
*/

int n,m,fa[N];

struct Edge{
    int u,v,w;
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    for(int i=0;i<n;i++)
        fa[i]=i;
    sort(edge+1,edge+1+m);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(){
    init();
    int x,y,flag=0;
    for(int i=1;i<=m;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y)
            fa[y]=x;
        else{
            if(!flag) printf("%d",edge[i].w);
            else  printf(" %d",edge[i].w);
            flag=1;
        }
    }
    if(!flag) printf("forest");
    printf("\n");
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        kruskal();
    }
    return 0;
}
