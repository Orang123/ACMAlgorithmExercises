#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 110
#define M 5000
#define INF 0x3f3f3f3f
using namespace std;
int n,m,fa[N];
//kruskal 130ms
/*
����:���һ��������������Ȩ����С��Ȩ֮�����Сֵ.
����:https://www.luogu.com.cn/problem/UVA1395
˼·:�ȶԱ���������,ö�ٱ߼���߽�����l,������С��Ȩ,
����߽���㿪ʼkruskal�ӱ�,�������ﵽn-1ʱ,��ʱ��n-1����
�����ұ߽�,��¼������Ȩ����߽��Ȩ,��ȡ��ֵ��Сֵ����.
ʵ�ʵı߼���������ҪС����ȫͼ�ı���,��Ϊ��O(n^2)���Ӷ�
*/

struct Edge{
    int u,v,w;
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

int kruskal(){
    sort(edge+1,edge+1+m);
    int x,y,num,maxd=INF,flag=0;;
    for(int l=1;l<=m;l++){//ö����߽�
        num=0;
        init();
        if(l+n-2>m) break;//����߽����+n-1���߳��������ܺ�ʱ���˳�
        for(int r=l;r<=m;r++){
            x=find(edge[r].u);
            y=find(edge[r].v);
            if(x!=y){
                fa[x]=y;
                num++;
                if(num == n-1){//�����ұ߽�
                    flag=1;
                    maxd=min(maxd,edge[r].w-edge[l].w);//��¼��С��ֵ
                }
            }
        }
    }
    if(!flag) maxd=-1;
    return maxd;
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        printf("%d\n",kruskal());
    }
    return 0;
}

/*
����lca������
*/
