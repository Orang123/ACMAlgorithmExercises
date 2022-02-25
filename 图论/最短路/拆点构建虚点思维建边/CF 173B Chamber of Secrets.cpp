#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 2100
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;

/*
����:һ��nxm�ľ�������,����һ���ӵ�һ������Ĺ���,
ÿ�������ϵ�'#'��������,������Ӳ�ʩ��ħ��,����ߵ�
���򲻻ᷢ���ı�,���������ʩ��ħ��,�����ھ�������ʱ,
����ᷢ��90��ת��,������������Ҫ�Լ�������ʩ��ħ��,
����ʹ�ôӵ�һ���������Ĺ��߷���ƫת�ܱ�ֱ����x���Ҳ�
���.
����:https://codeforces.ml/problemset/problem/173/B
˼·:���Խ�������ʩ��ħ������������λ��[i,j]����ӵ�i�к���
ת��Ϊ��j������,��һ��i->j+n,j+n->i��˫���.
*/

int n,m,cnt,head[N],vis[N],dis[N];
struct Node{
    int to,next;
}edge[M<<1];

void addEdge(int from,int to){
    edge[cnt]=(Node){to,head[from]};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
}

void bfs(int s){
    init(s);
    queue<int> Q;
    vis[s]=1;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(!vis[v]){
                dis[v]=dis[u]+1;
                vis[v]=1;
                Q.push(v);
            }
        }
    }
}

int main(){
    char x;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf(" %c",&x);
            if(x == '#'){//������ �Ϳ�������� �����ת�� i��ת��Ϊj��
                addEdge(i,j+n);//�еĵ���Ϊ1~n �еĵ���Ϊj+n ��n+1~n+m
                addEdge(j+n,i);//˫�򽨱��ǻ�ͨ��,���ܴ��е���,Ҳ�ܴ���ת������
            }
        }
    }
    bfs(1);
    if(!dis[n])
        printf("-1");
    else
        printf("%d",dis[n]);
    return 0;
}
