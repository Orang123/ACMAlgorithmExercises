#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 20100
#define M 110
using namespace std;
int head[N],cnt,siz[N],maxn[N],vis[N],sum,rt,dis[N],num[3],ans;

struct Node{
    int to,next,w;
}edge[N<<1];

void addEdge(int from,int to,int w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void getrt(int u,int fa){
    siz[u]=1;
    maxn[u]=0;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa && !vis[v]){
            getrt(v,u);
            siz[u]+=siz[v];
            maxn[u]=max(maxn[u],siz[v]);
        }
    }
    maxn[u]=max(maxn[u],sum-siz[u]);
    if(maxn[u]<maxn[rt]) rt=u;
}

void getdis(int u,int fa){
    num[dis[u]]++;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(v!=fa && !vis[v]){
            dis[v]=(dis[u]+edge[i].w)%3;
            getdis(v,u);
        }
    }
}

int calc(int u,int d){
    num[0]=num[1]=num[2]=0;
    dis[u]=d%3;
    getdis(u,0);
    /*
    num[0]��������Ŀ�ʼ����·������ͱ������3�ı����ĸ��� num[0]*num[0]�ǵ�Եĸ���
    num[1]��������Ŀ�ʼ����·�������ȡģ3��1������·���ĸ���
    num[1]��������Ŀ�ʼ����·�������ȡģ3��2������·���ĸ���
    num[1]*num[2]*2����1��·������2��·��ƴ�ӹ��ɵ�·������Ϊ3�ı����ĵ�Եĸ���
    ���������1����2·��ƴ�ӹ��ɾ���Ϊ3�ı����ĵ��,ĳ�����������,�����Ķ�λ���,
    ���ߵ�����Ҳ����,*2�������Ŀ��.
    */
    return num[0]*num[0]+num[1]*num[2]*2;
}

void divide(int u){
    vis[u]=1;
    ans+=calc(u,0);//��һ�δ����ļ����������ֵ������. �ӵ������Ի���ʼͳ��,����һ��0��Ϊ�˽����һЩ�����ظ�����Ľ��
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!vis[v]){
            ans-=calc(v,edge[i].w);//�ڶ��δ��ӽڵ�v��ʼ,ans�ټ�ȥ�������ֵ ��ȥ�ظ���·������Ϊ3�ı����ĵ���Ի���һ���� �������ݳ�ԭ��
            maxn[rt=0]=sum=siz[v];
            getrt(v,0);
            getrt(rt,0);
            divide(rt);
        }
    }
}

int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}

int main(){
    int n,u,v,w;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    maxn[0]=sum=n;
    getrt(1,0);
    getrt(rt,0);
    divide(rt);
    int k=gcd(ans,n*n);//n*n�������е�� �����ɵ�·������ ������������Ի�
    printf("%d/%d\n",ans/k,n*n/k);
    return 0;
}
