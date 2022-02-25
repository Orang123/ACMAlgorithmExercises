#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 200100
#define INF 0x3f3f3f3f
using namespace std;
//���򽨱�
/*
����:n����,ÿ����i����������i+a[i],i-a[i]����λ��,
����Ҫ�������ÿ��������������ż���ʹ�ż������������Ҫ����С����.
����:https://codeforces.ml/problemset/problem/1272/E
˼·:����������򽨱�,��i->i+a[i],i->i-a[i],�����������·ʱ,
�������a[i]��ż��Ҫ��ż��(i)������,��ôҪ��һ�����Ϊi�����·,
����ÿ���յ�Ϊ�����ĳ��ȶ���Ҫ�Ƚ������̾���,��������ÿ���㶼������һ�����·,
������TLE spfa��ɴ� o(n^3),DijkstraҲ����O(n^2),��n<=2*10^5.
���Կ��Ƿ��򽨱�,��:i+a[i]->i i-a[i]->i,������������Դ�� 0,n+1.�ֱ�ָ�����е�ż������.ȨΪ0.
�������·���ֱ�Ϊ0,n+1.��������ÿ����i��������Ϊ�����յ�,��ʵ����Ϊ�����Ƿ��򽨱ߣ�
���� ���Ծ�����Ϊ��� �ܵ���ż�����෴�ĵ�����·,����ֻ��������һ�����·����.
*/

int n,cnt,head[N],a[N],vis[N],dis1[N],dis2[N];

struct Node{
    int to,next,w;
}edge[N*3];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(int s,int *dis){
    memset(vis,0,sizeof(vis));
    for(int i=0;i<=n+1;i++)
        dis[i]=(i==s?0:INF);
}

void spfa(int s,int *dis){
    init(s,dis);
    queue<int> Q;
    Q.push(s);
    vis[s]=1;
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
}

int main(){
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(a[i]&1) addEdge(n+1,i,0);
        else addEdge(0,i,0);
        if(i+a[i]<=n) addEdge(i+a[i],i,1);
        if(i-a[i]>=1) addEdge(i-a[i],i,1);
    }
    spfa(0,dis1);
    spfa(n+1,dis2);
    for(int i=1;i<=n;i++){
        if(a[i]&1){//a[i]������
            /*
            ���Ǵ�ż�����ܵ�i�����·��,ʵ���Ƿ��򽨱�,���ڴ�i(����)��ż����Ҳ����̿ɴ������.
            ��Ϊi�������,�������0,n+1����Դ�����򽨱� ����ֻ�ܱ�ʾ��ż��������,�������ĸ�ż���ǲ�֪����,
            ��Ϊ�����Ǵ�0�㿪ʼ�ܵ�,������Ϊ������� ʵ�����i�����Ҳ��һ��������̵�
            */
            if(dis1[i]!=INF) printf("%d ",dis1[i]);
            else printf("-1 ");
        }
        else{//a[i]ż��ͬ��
            if(dis2[i]!=INF) printf("%d ",dis2[i]);
            else printf("-1 ");
        }
    }
    return 0;
}
