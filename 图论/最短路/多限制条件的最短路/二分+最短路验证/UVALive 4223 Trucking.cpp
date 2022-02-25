#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1100
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;
//UVALive �����ύ��,����ϵͳ������,�������ܹ�
/*
����:n������,m��˫���·,ÿ����·����һ���߶�����h�;���w,
����һ������Ҫ����һ�������s�ص�t��,�������Ļ���������߶�
������,����Ҫ���ڿ�����������Ļ�����,��s�ص�t��,���Ҫ���پ���.
���������ʱ�ĳ���ߺ�s��t�ľ���.�������ݻ������������ߵ�����޶�.s
����:https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2224
˼·:���������Ǳ�������ͼ,����ÿһ����s����t���·��,
��¼ÿ��·���ϵĳ��������޶Ⱥ;���ͱ�������,
����ճ������Ϊ��һҪ�ؽ�������,�������Ϊ�ڶ�Ҫ����������.
������������Ӷ�����s��t��·������,������¼���s��t��50����,ÿ������֮���������5��,
���ݳ˷�ԭ��5^(49)>10^12,ʱ��ռ��Ѿ���ը.
����:���ڳ���߶��������������,���Զ��ֳ���ĸ߶�,�����·ȥ��֤��ǰ�߶��Ƿ��ܵ���t��,
����,��������߶�,�����С�߶�,�����ͱ�����ȥ�������п��ܵ�s��t��·��,�ʱ�临�Ӷ�Ϊ
O(nlog(n)log(h))

*/

int n,m,cnt,head[N],vis[N],dis[N],st,ed;
struct Node{
    int to,next,h,w;
}edge[M<<1];

void addEdge(int from,int to,int h,int w){
    edge[cnt]=(Node){to,head[from],h,w};
    head[from]=cnt++;
}

void init(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
}

int Dijkstra(int s,int h){
    init(s);
    priority_queue<pair<int,int> >Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(u == ed) return 1;
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            if(edge[i].h<h) continue;//����ǰ��·�ĸ߶�С�ڵ�ǰ���ֳ�����򲻿�ͨ��
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return 0;
}

int main(){
    int u,v,h,w,cas=0;
    while(scanf("%d%d",&n,&m) && n+m){
        cas++;
        cnt=0;
        memset(head,-1,sizeof(head));
        while(m--){
            scanf("%d%d%d%d",&u,&v,&h,&w);
            if(h == -1) h=INF;//hΪ-1ʱ,�����·�߶����޴�
            addEdge(u,v,h,w);
            addEdge(v,u,h,w);
        }
        int l=0,r;
        scanf("%d%d%d",&st,&ed,&r);//��ʼ�� Ŀ��� rΪ����ߵ�����
        //���ֳ����,�����·��֤
        while(l<=r){
            int mid=(l+r)/2;
            if(Dijkstra(st,mid)) l=mid+1;//����ǰ������ܵ���t��,������������
            else r=mid-1;//�����С�����
        }
        printf("Case %d:\n",cas);
        if(dis[n]!=INF){
            printf("maximum height = %d\n",r);
            printf("length of shortest route = %d\n",dis[n]);
        }
        else
            printf("cannot reach destination\n");
    }
    return 0;
}
/*
Sample Input
5 6
1 2 7 5
1 3 4 2
2 4 -1 10
2 5 2 4
3 4 10 1
4 5 8 5
1 5 10
5 6
1 2 7 5
1 3 4 2
2 4 -1 10
2 5 2 4
3 4 10 1
4 5 8 5
1 5 4
3 1
1 2 -1 100
1 3 10
0 0

Sample Output
Case 1:
maximum height = 7
length of shortest route = 20
Case 2:
maximum height = 4
length of shortest route = 8
Case 3:
cannot reach destination
*/
