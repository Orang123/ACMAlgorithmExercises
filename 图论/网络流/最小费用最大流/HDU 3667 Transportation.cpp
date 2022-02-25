#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 110
#define M 25100
#define INF 0x3f3f3f3f
using namespace std;
//ac 748ms EK�㷨 ������ ���
/*
����:��N���ڵ�M���ߵ�����ͼ,��������Ҫ��1�Žڵ�����k�����ﵽN�Žڵ�.
ÿ���߶���һ��ai��ciֵ,ciֵ��ָ�ñ��������ci������,��������ڸñ���x
(1<=x<=ci)��������Ҫ����ai*x*x����.����������k���������С�����Ƕ���?
����:http://acm.hdu.edu.cn/showproblem.php?pid=3667
˼·:������Ȼ����С���������������,������ÿ���ߵ�ȨֵΪһ������,��������н�,
�ٸ�����,�����������4�������ô�ڸñ߷ֱ���1,2,3,4������Ĵ��۾���ai*1,ai*4,
ai*9,ai*16,��ô���һ����ai*1,ai*3,ai*5,ai*7,��Ȼ���ͼ�������Ĵ��۾�������Ȳ�
���е�ǰn���,��ô������������c��������c����,ÿ��������Ϊ1,ȨֵΪai*(2*i-1),
������������ʱ���һ�ξͻ�ѡȨֵ��С��������,�ڶ��ξͻ�ѡ��С��������,��Ϊ�����
��С����,���ԵȲ����иպ�ֻ��ѡ��������ǰ����,�ѽ���ۼӾ���ǰn�����,�ǳ�����Ĳ�߽�ͼ.
*/
int n,m,k,cnt,st,ed,head[N],incf[N],pre[N],vis[N],dis[N];
struct Edge{
    int to,next,cf,w;
}edge[M<<1];

void addEdge(int from,int to,int cf,int w){
    edge[cnt]=(Edge){to,head[from],cf,w};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0,-w};
    head[to]=cnt++;
}

void init0(int s){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    incf[s]=INF;
    pre[ed]=0;
    vis[s]=1;
}

int spfa(int s){
    queue<int> Q;
    init0(s);
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        vis[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v]>dis[u]+edge[i].w){
                pre[v]=i;
                dis[v]=dis[u]+edge[i].w;
                incf[v]=min(incf[u],edge[i].cf);
                if(!vis[v]){
                    vis[v]=1;
                    Q.push(v);
                }
            }
        }
    }
    return pre[ed];
}

int mcmf(){
    int sum=0,cost=0;
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed];
        cost+=incf[ed]*dis[ed];
    }
    return sum == k?cost:-1;
}

void init(){
    cnt=0;
    st=0,ed=n;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v,a,c;
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        init();
        addEdge(st,1,k,0);
        while(m--){
            scanf("%d%d%d%d",&u,&v,&a,&c);
            for(int i=1;i<=c;i++)
                addEdge(u,v,1,(2*i-1)*a);
        }
        printf("%d\n",mcmf());
    }
    return 0;
}
