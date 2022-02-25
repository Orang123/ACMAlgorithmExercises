#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int const N=1e4+10;
int const M=1e8+10;

/*
����:n����,m���ߵ�����ͼ,��ʹ��ͼ��û�л�����Ҫ����ɾ���ı�Ȩ���Ƕ���.
����:http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2224
˼·:ɾ�����ͼû�л�,������ɭ��,Ҫ��ɾ����Ȩ������,ɾ����Ȩ��=�ܱ�Ȩ��-ɭ�ֱ�Ȩ��
��ôɭ�ֱ�Ȩ�����ʱ,ɾ����Ȩ�;���С.
*/

int n,m,fa[N];
double sum;

struct Point{
    double x,y;
}point[N];

double getDis(double x1,double y1,double x2,double y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

struct Edge{
    int u,v;
    double w;
    Edge(int u=0,int v=0,double w=0):u(u),v(v),w(w){}
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

double kruskal(){
    init();
    int x,y,cnt=0;
    double sum=0;
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
    int u,v;
    double w;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf",&point[i].x,&point[i].y);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        w=getDis(point[u].x,point[u].y,point[v].x,point[v].y);
        sum+=w;
        edge[i]=Edge(u,v,w);
    }
    printf("%.3f",sum-kruskal());
    return 0;
}

/*
Sample Input 1
3 3
0 0
3 0
0 4
1 2
2 3
3 1
Output for the Sample Input 1
3.000

Sample Input 2
4 3
0 0
-100 0
100 0
0 100
1 2
1 3
1 4
Output for the Sample Input 2
0.000

Sample Input 3
6 7
2 0
6 0
8 2
6 3
0 5
1 7
1 2
2 3
3 4
4 1
5 1
5 4
5 6
Output for the Sample Input 3
7.236

Sample Input 4
6 6
0 0
0 1
1 0
30 0
0 40
30 40
1 2
2 3
3 1
4 5
5 6
6 4
Output for the Sample Input 4
31.000

*/
