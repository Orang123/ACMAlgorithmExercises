#include<cstdio>
#include<functional>
#include<algorithm>
#define N 100100
#define M 100100
using namespace std;
//93ms
/*
����:����һ����ͨ����Ȩ����ͼ��ͼ�в��������Ի����رߣ�
����������Ѱ�ҳ��ж������ߣ���������һ����С�������ͼ��֤��ͨ��
����:http://acm.fzu.edu.cn/problem.php?pid=2087
˼·:kruskal,����ͬȨֵ�ı߷�Ϊһ��,���ղ��鼯�б������������ͬһ����ͨ��,
��ô����+1,��Ϊ���ڴ�ʱ�ӱ߼���һ�����ǿ��Ե�,�����ڲ��ϼӱߵĹ�����,�ᵼ��
����ı߼Ӳ���ȥ��ɻ�,����ֻ��Ҫ��¼�ж�������������Ϊmst�ı߼������Ϊ��
��δ�ɻ�ʱѡ����һ�����ǿ��Ե�,Ȼ������������ЩȨֵ��ͬ�ıߵ�fa[N]����ϲ�.
*/

int n,m,fa[N],sum;

struct Edge{
    int u,v,w;
    bool operator <(const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void init(){
    sum=0;
    sort(edge+1,edge+1+m);
    for(int i=1;i<=n;i++)
        fa[i]=i;
}

int find(int x){
    return fa[x]==x?x:(fa[x]=find(fa[x]));
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        init();
        int x,y,cnt=0;
        for(int i=1,j;i<=m;i=j){//i=j,��Ȩֵ����ȵı߿�ʼ
            for(j=i;edge[j].w==edge[i].w;j++){//j=i���жϱ���i�������ܷ���Ϊmst�ı�,���жϺ����iȨֵ��ȵı�
                x=find(edge[j].u);
                y=find(edge[j].v);
                /*
                ����Ȩֵ��ͬ�ı��Ȳ��ϲ�,�ȼ���,��������� ����һ���߶��ǿ��Ե�,���ǿ��ܺ����ϲ�ʱ,
                ����ֻ�,�����ڻ�û�ɻ��ӱ�ʱ��ЩȨֵ��ȵı�����һ����������Ϊmst�ıߵ�.
                */
                if(x!=y)
                    sum++;
            }
            for(j=i;edge[j].w==edge[i].w;j++){//֮���������ϲ�Ϊһ����ͨ��
                x=find(edge[j].u);
                y=find(edge[j].v);
                if(x!=y){
                    fa[x]=y;
                    cnt++;
                }
            }
            if(cnt == n-1) break;//����һ����ʱ ����
        }
        printf("%d\n",sum);
    }
    return 0;
}
