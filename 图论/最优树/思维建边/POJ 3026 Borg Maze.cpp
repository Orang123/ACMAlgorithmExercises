#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 55
#define M 11000//�Թ������100�������� ��ô��ȫͼ��4950����,���������ڽ���ʱ,ȥ�ر�̫�鷳,��a->b b->a����2��,û̫��Ӱ�� ���4950*2<11000 ��������Խ��
using namespace std;
//63ms kruskal
/*
����:�����˷ֲ����Թ���'A'��,�����˴�'S'������,
������ͬ��������,һ�������˱�ͬ����,����ȥͬ������������,
�����������˱�ͬ�����߹�����С����.
��������:
n*m���Թ�,ֻ����' ','#'������,�����ĸ'S'����
�����е�'A'��������ʹ��'S'������'A'��ͨҪ�ߵ����پ���.
����:http://poj.org/problem?id=3026
˼·:�������ʹ�s�����û�й�ϵ,�������'S'�����е�'A'����
��mst,�Ǿ�����ν��ߵ�����,��Ϊ�Թ�����'#'����ֱ��ͨ�������
������Ȩ,����Ҫ�����е�'A'��'S'����bfs������'A'��'S'����,����
һ��'S'��'A'����ȫͼ.֮������kruskal���������С����.
*/
//fa[N<<1] �Թ������100��������,������ͼ���100����
int n,m,id,fa[N<<1],mp2[N][N],mp3[N][N],cnt,vis[N][N];
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
char mp1[N][N];

struct Node{
    int x,y,dis;
    Node(int x=0,int y=0,int dis=0):x(x),y(y),dis(dis){}
};

struct Edge{
    int u,v,w;
    Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
    bool operator < (const Edge &x)const{
        return w<x.w;
    }
}edge[M];

void bfs(int x,int y){
    queue<Node> Q;
    vis[x][y]=1;
    Q.push(Node(x,y,0));
    Node node;
    int x0,y0;
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        //���� 'A'��'S' �ͽ���
        if(node.dis && mp2[node.x][node.y])//����ÿ���߻Ὠ����,�������Ҫ��2��
            edge[++cnt]=Edge(mp2[x][y],mp2[node.x][node.y],node.dis);
        for(int i=0;i<4;i++){
            x0=node.x+dir[i][0];
            y0=node.y+dir[i][1];
            if(x0<1 || x0>n || y0<1 || y0>m) continue;
            if(vis[x0][y0] || mp1[x0][y0] == '#') continue;
            vis[x0][y0]=1;//������һ��Ҫ�������������,���������pop����ᵼ����ͬ���������2��,����������Ӹ��Ӷ�
            Q.push(Node(x0,y0,node.dis+1));
        }
    }
}

void init(){
    //id ��'S' 'A'���ܸ���
    for(int i=1;i<=id;i++)
        fa[i]=i;
    sort(edge+1,edge+1+cnt);
}

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
    init();
    int x,y,num=0,sum=0;
    for(int i=1;i<=cnt;i++){
        x=find(edge[i].u);
        y=find(edge[i].v);
        if(x!=y){
            fa[x]=y;
            num++;
            sum+=edge[i].w;
            if(num == id-1) break;
        }
    }
    return sum;
}

int main(){
    int T;
    char str[55];
    scanf("%d",&T);
    while(T--){
        id=cnt=0;
        memset(mp2,0,sizeof(mp2));
        scanf("%d%d",&m,&n);
        gets(str);//�������� Ī���ж����' '�ո�,�������getchar()��ȡ����һ�еġ�\n'����
        for(int i=1;i<=n;i++){
            gets(mp1[i]+1);
            for(int j=1;j<=m;j++){
                if(mp1[i][j] == 'S' || mp1[i][j] == 'A')
                    mp2[i][j]=++id;//����'S' 'A'��ı��
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(mp2[i][j]){//��ÿ��'S' 'A'��ʼ������
                    memset(vis,0,sizeof(vis));
                    bfs(i,j);
                }
            }
        }
        printf("%d\n",kruskal());
    }
    return 0;
}
/*
//����һ������
1
50 50
##################################################
#AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#                                               A#
#S                                              A#
##################################################

*/
