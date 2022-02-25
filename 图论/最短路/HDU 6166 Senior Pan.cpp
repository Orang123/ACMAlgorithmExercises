#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//Dijkstra 3338ms
/*
����:n���ڵ��������ͨͼ,m�������,����ѡ��k����,�����k����Լ��
��̾���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=6166
˼·:
��֪����������ϼ����̾���������,������һ����������Ԫ�����,�������ø������disΪ0,
������һ�����·,�Ƚ���һ���������е��dis,�����Сֵ���������ϼ����̾���.
���ڿ��ǽ���k�����Ϊ��������,�������������ϼ����̾����������k��������̾���.
��ô��������ν���k����ָ����������,ʹ���������㶼���Էֱ𱻷ָ,ʹ�����������
���붼���Ա����ǽ�ȥ,������Կ��Ǹ���ÿ�����ŵĶ�����λ,���ݶ�����ÿһλ�Ƿ�����,��
k����ָ����������,�������ĺ�����������Ϊ��������ʮ�������������λ������һλ�ǲ�ͬ��,
����ö��ÿһλ�����Ƶ�����,��������������˵,���Ƕ��ܱ�֤���ָ��ͬ�ļ���.
��������ö�ٶ�����λ��ΪN<=10^5,����ö�ٵ���16λ������λ,��Ϊ2^17=130000,����ö�ٵ���16λ
����.

2019 ICPC �ϲ� Fire-Fighting Hero
������֮ǰ�������k���㵽�������е���������,�Ǹ������ǽ���k������һ������Դ������,��ȨΪ0,�ӳ���Դ�����,
��һ�����·,�Ƚϸ������dis,������ֵ����,���������ֻ���������k���㵽�������е����С����,�޷����
ָ����k��������С����,��Ϊ��k�����dis��ԶΪ0,Ҫȥ���ָ��k��������·������Ҫ��k���㻮�ֳ�2�����ϵ�.
*/

int n,m,cnt,k,head[N],vis[N],a[N],b[N],t;
ll dis[N];
priority_queue<pair<ll,int> >Q;

struct Node{
    int to,next;
    ll w;
}edge[N];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    t=0;
    memset(vis,0,sizeof(vis));
    memset(b,0,sizeof(b));
    memset(dis,0x3f,sizeof(dis));
    while(!Q.empty()) Q.pop();
}

ll Dijkstra(){
    int u,v,num=0;
    ll ans=INF;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        if(b[u]){
            num++;
            ans=min(ans,dis[u]);
            if(num == t) return ans;
        }
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    return ans;
}

int main(){
    int T,u,v,cas=0;
    ll w,ans;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=0;
        ans=INF;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
        }
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d",&a[i]);
        for(int i=0;i<=16;i++){//ö�ٶ�����λ��ÿһλ,��2^i>nʱ,ֻ�ܱ��ָ��һ������,���ⲻӰ����������,ans���ص�ֵ��INF
            init();
            for(int j=1;j<=k;j++){
                if(a[j] & (1<<i)){//��a[j]���Ŷ�����λ��i+1λ��1,�������ĵ㶼���Ի���һ�������ﲢ���
                    dis[a[j]]=0;//��������Ծ���Ϊ0,������µ���һ����ľ���
                    Q.push(make_pair(0,a[j]));
                }
                else{//��a[j]���Ŷ�����λ��i+1λ����1,�������ĵ㶼��ΪĿ��������һ��������
                    b[a[j]]=1;
                    t++;
                }
            }
            ans=min(ans,Dijkstra());//���Ӽ���1������2�����е�Ե���̾���
            init();
            for(int j=1;j<=k;j++){
                if(a[j] & (1<<i)){
                    b[a[j]]=1;
                    t++;
                }
                else{
                    dis[a[j]]=0;
                    Q.push(make_pair(0,a[j]));
                }
            }
            ans=min(ans,Dijkstra());//��Ϊ�ǵ����,���������һ�μ���2������1�����е�Ե���̾���,�ۺϱȽ����k��������̾���
        }
        printf("Case #%d: %lld\n",cas,ans);
    }
    return 0;
}

/*
//spfa 2558ms
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,k,head[N],vis[N],a[N],b[N];
ll dis[N];
queue<int> Q;

struct Node{
    int to,next;
    ll w;
}edge[N];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    memset(vis,0,sizeof(vis));
    memset(b,0,sizeof(b));
    memset(dis,0x3f,sizeof(dis));
}

ll spfa(){
    int u,v;
    ll ans=INF;
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
    for(int i=1;i<=k;i++){
        if(b[a[i]])
            ans=min(ans,dis[a[i]]);
    }
    return ans;
}

int main(){
    int T,u,v,cas=0;
    ll w,ans;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=0;
        ans=INF;
        memset(head,-1,sizeof(head));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
        }
        scanf("%d",&k);
        for(int i=1;i<=k;i++)
            scanf("%d",&a[i]);
        for(int i=0;i<=16;i++){
            init();
            for(int j=1;j<=k;j++){
                if(a[j] & (1<<i)){
                    dis[a[j]]=0;
                    vis[a[j]]=1;
                    Q.push(a[j]);
                }
                else
                    b[a[j]]=1;
            }
            ans=min(ans,spfa());
            init();
            for(int j=1;j<=k;j++){
                if(a[j] & (1<<i))
                    b[a[j]]=1;
                else{
                    dis[a[j]]=0;
                    vis[a[j]]=1;
                    Q.push(a[j]);
                }
            }
            ans=min(ans,spfa());
        }
        printf("Case #%d: %lld\n",cas,ans);
    }
    return 0;
}
*/

