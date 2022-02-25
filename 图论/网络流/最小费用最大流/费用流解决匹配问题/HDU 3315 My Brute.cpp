#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#define N 220
#define INF 0x3f3f3f3f
using namespace std;
//ac 780ms EK�㷨 ������
/*
//����ժ������
����:��S1��Sn��n����ʿҪ��X1��Xn��n����ʿ����,��ʼʱ,Si�ľ���������Xi.
���SiӮ��Xi,��ô�㽫���Vi��,�����㽫���-Vi��.Si��Xi�Ծ�ʱ,Si�г�ʼ
����Hi,��ʼ����Ai, Xi�г�ʼ����Pi,��ʼ����Bi. ��Si�ȳ���,Ȼ��XiʧȥAi
����,֮�����Xiû��,��ôXi����,SiʧȥBi����. ֱ����һ��������ֵ<=0ʱ,
��������.����Ҫ�����°���S��X�ľ���˳��,ʹ��S1~Sn�ܻ�õķ����.����ж�
�����Ž�,��Ҫѡȡ�Ǹ�ά�ֳ�ʼ����˳�����Ľ�.���S1~Sn���յ÷��ܺʹ���0,
��������÷ֺ�ԭʼ����˳�򲻱���ռ�ı���(�ٷֺű���3λС��),�������
"Oh, I lose my dear seaco!".
����:http://acm.hdu.edu.cn/showproblem.php?pid=3315
˼·:��С������,��Ȩȡ��,����(n+1)��,i==j�ټ�1.
*/
int v[N],h[N],p[N],a[N],b[N];
int n,cnt,st,ed,head[N],incf[N],pre[N],vis[N],dis[N],sum,cost;
struct Edge{
    int to,next,cf,w;
}edge[N*N];

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

void mcmf(){
    while(spfa(st)){
        for(int i=ed;i!=st;i=edge[pre[i]^1].to){
            edge[pre[i]].cf-=incf[ed];
            edge[pre[i]^1].cf+=incf[ed];
        }
        sum+=incf[ed];
        cost+=incf[ed]*dis[ed];
    }
}

int cal(int i,int j){
    int hi=h[i],pj=p[j];
    //Si��Xj�����ķ�ʽ��ÿ��Si����Xjһ��,Xj�ٹ���Siһ��
    //p[j](Xj��Ѫ��)ÿ�μ�a[i],h[i](Si��Ѫ��)ÿ�μ�b[j].
    while(1){
        pj-=a[i];
        if(pj<=0) return v[i];//��XjѪ��С�ڵ���0ʱ,Si�÷�v[i]
        hi-=b[j];
        if(hi<=0) return -v[i];//��SiѪ��С�ڵ���0ʱ,Si�÷�-v[i]
    }
}

void init(){
    sum=cost=cnt=0;
    st=0,ed=2*n+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int w;
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++) scanf("%d",&v[i]);
        for(int i=1;i<=n;i++) scanf("%d",&h[i]);
        for(int i=1;i<=n;i++) scanf("%d",&p[i]);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++) scanf("%d",&b[i]);
        for(int i=1;i<=n;i++){
            addEdge(st,i,1,0);
            addEdge(i+n,ed,1,0);
            for(int j=1;j<=n;j++){
                w=cal(i,j)*(n+1);//��Ȩ����(n+1)��
                if(i == j) w++;//��ʼƥ���Ȩ�ټ�1
                addEdge(i,j+n,1,-w);
            }
        }
        mcmf();
        if(-cost/(n+1)<=0)
            printf("Oh, I lose my dear seaco!\n");
        else
            printf("%d %.3f%%\n",-cost/(n+1),-cost%(n+1)*1.0/n*100);//������Ȩֵ�ͺ����Ȩƥ���г�ʼƥ����ռ�ı���
    }
    return 0;
}

/*
//ac 31ms KM�㷨 slack�ɳ��Ż�
//Ҳ���������������
//ͬHDU 2853
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define INF 0x3f3f3f3f
using namespace std;

int v[N],h[N],p[N],a[N],b[N],ans;
int n,mp[N][N],link[N],visx[N],visy[N],lx[N],ly[N],slack[N],d;

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
        if(visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(!link[v] || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
        else
            slack[v]=min(slack[v],tp);
    }
    return 0;
}

void KM(){
    for(int i=1;i<=n;i++){
        lx[i]=-INF;
        ly[i]=0;
        for(int j=1;j<=n;j++)
            lx[i]=max(lx[i],mp[i][j]);
    }
    for(int i=1;i<=n;i++){
        memset(slack,0x3f,sizeof(slack));
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=n;j++){
                if(!visy[j])
                    d=min(d,slack[j]);
            }
            for(int j=1;j<=n;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
                else slack[j]-=d;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(!link[i]) continue;
        ans+=mp[link[i]][i];
    }
}

int cal(int i,int j){
    int hi=h[i],pj=p[j];
    //Si��Xj�����ķ�ʽ��ÿ��Si����Xjһ��,Xj�ٹ���Siһ��
    //p[j](Xj��Ѫ��)ÿ�μ�a[i],h[i](Si��Ѫ��)ÿ�μ�b[j].
    while(1){
        pj-=a[i];
        if(pj<=0) return v[i];//��XjѪ��С�ڵ���0ʱ,Si�÷�v[i]
        hi-=b[j];
        if(hi<=0) return -v[i];//��SiѪ��С�ڵ���0ʱ,Si�÷�-v[i]
    }
}

void init(){
    ans=0;
    memset(link,0,sizeof(link));
}

int main(){
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++) scanf("%d",&v[i]);
        for(int i=1;i<=n;i++) scanf("%d",&h[i]);
        for(int i=1;i<=n;i++) scanf("%d",&p[i]);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++) scanf("%d",&b[i]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                mp[i][j]=cal(i,j)*(n+1);//��Ȩ����(n+1)��
                if(i == j) mp[i][j]++;//��ʼƥ���Ȩ�ټ�1
            }
        }
        KM();
        if(ans<=0)
            printf("Oh, I lose my dear seaco!\n");
        else
            printf("%d %.3f%%\n",ans/(n+1),ans%(n+1)*1.0/n*100);//������Ȩֵ�ͺ����Ȩƥ���г�ʼƥ����ռ�ı���
    }
    return 0;
}
*/
