#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 210
#define M 40100
#define INF 0x3f3f3f3f
using namespace std;
//ac 218ms Ek�㷨 ���򻷸��� ���
//����ͨ��KM�㷨,��Ȩȡ������СȨƥ��
/*
ժ������
����:����һ��N����M���ߵĴ�Ȩ����ͼ,����Ҫ��������һ��ֵ:
������ͼ�е����ж������ñ�1���������ཻ�����򻷸���.
���ֵ����������Щ���򻷵�Ȩֵ��.Ҫ���ֵԽСԽ��.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1853
˼·:���򻷵���С��������,���ȿ��Ǹ�ͼ�����ж������ñ�1��
�������ཻ�Ļ����ǵĻ�,����ζ��ͼ�е�ÿ��������Ⱥ���Ⱦ�Ϊ1,
��ô����ÿ������Ϳ��԰������������,��ģ����Ⱥ����,Դ����൱
���ܳ���,�����൱�������,��ô�����������ڶ�����Ŀ,��ô�Ϳ�
��˵���պñ�1���������ཻ������,��ô��С���þ��Ǵ���.
i��ʾ��i�ĳ���,i+n��ʾ��i�����,Դ��0,���2*n+1,Դ����ÿ�����ȵ���
����Ϊ1,����Ϊ0�ı�,ÿ����ĳ���i+n����������Ϊ1,����Ϊ0�ı�.
ÿ�������u->v,��u��v+n,����Ϊ1,����Ϊw�ı�.
*/
int n,m,cnt,st,ed,head[N],incf[N],pre[N],vis[N],dis[N];
struct Edge{
    int to,next,cf,w;
}edge[M];

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
    return sum == n?cost:-1;
}

void init(){
    cnt=0;
    st=0,ed=n*2+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int u,v,w;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            addEdge(st,i,1,0);
            addEdge(i+n,ed,1,0);
        }
        while(m--){
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v+n,1,w);
        }
        printf("%d\n",mcmf());
    }
    return 0;
}

/*
ժ�Բ���:https://blog.csdn.net/qq_21057881/article/details/50677187
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 1e9
using namespace std;
const int maxn=100+10;

struct Max_Match
{
    int n,W[maxn][maxn];
    int Lx[maxn],Ly[maxn];
    bool S[maxn],T[maxn];
    int left[maxn];

    bool match(int i)
    {
        S[i]=true;
        for(int j=1;j<=n;j++)if(Lx[i]+Ly[j]==W[i][j] && !T[j])
        {
            T[j]=true;
            if(left[j]==-1 || match(left[j]))
            {
                left[j]=i;
                return true;
            }
        }
        return false;
    }

    void update()
    {
        int a=1<<30;
        for(int i=1;i<=n;i++)if(S[i])
        for(int j=1;j<=n;j++)if(!T[j])
            a=min(a, Lx[i]+Ly[j]-W[i][j]);
        for(int i=1;i<=n;i++)
        {
            if(S[i]) Lx[i] -=a;
            if(T[i]) Ly[i] +=a;
        }
    }

    int solve(int n)
    {
        this->n=n;
        memset(left,-1,sizeof(left));
        for(int i=1;i<=n;i++)
        {
            Lx[i]=Ly[i]=0;
            for(int j=1;j<=n;j++) Lx[i]=max(Lx[i], W[i][j]);
        }
        for(int i=1;i<=n;i++)
        {
            while(true)
            {
                for(int j=1;j<=n;j++) S[j]=T[j]=false;
                if(match(i)) break;
                else update();
            }
        }
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            if(W[left[i]][i]==-INF) return -1; //�Ҳ���
            ans += W[left[i]][i];
        }
        return -ans;//ע�����ﷵ�ص��Ǹ�ֵ
    }
}KM;

int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)==2)
    {
        for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            KM.W[i][j]=-INF;
        while(m--)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            KM.W[u][v]=max(KM.W[u][v],-w);//���ܴ����ر�
        }
        printf("%d\n",KM.solve(n));
    }
    return 0;
}
*/
