#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 200100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
//������� Ī��wa����֪ʲôԭ��
/*
����:n����ׯ,��ׯ֮�����˫���·,����Ҫ��һ�鵰���s���͵�t��,
���Ҵ�ׯ��Ϊ3��,��һ�ִ�ׯ���ֻ���������ŵ���,
�ڶ��ִ�ׯ�Ҵ�ֻ���������ŵ���,�����ִ�ׯ�д������������Ҳ��
��������,��֪��һ�鵰������ַŵ����ֻ�����ַŵ�����,
��Ҫ����x,�����ʰѵ����s���ᵽt����Ҫ�����ٻ���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=6805
˼·:�������ִ�����ִ�֮��ĵ�·��Ȩֵ������ľ��ǵ�·Ȩֵ���ϻ��ֵĴ���,
�ɶ����д�������Ҵ���Ƿ���Ҫ�����ǲ������,��Ϊ������д����е����״̬����
�����ֻ�������,���Զ����д���������Ҫ���,��Ϊ2��״̬,�����,�����д�Ͳ�Ϊ2����,
�����д�x,x��ʾҪ�������е���,x+n��ʾҪ�������е���.
Ȼ����������յ��п���ҲΪ�д�,��ô����������һ������Դ��(0)�ͻ��(2n+1)
�������յ���������ͳ���ȥ,��������·��ȡdis[2n+1]����.
*/

int n,m,cnt,head[N<<1],vis[N<<1];
ll dis[N<<1];
char str[N];

struct Node{
    int to,next;
    ll w;
}edge[M<<3];

void addEdge1(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to],w};
    head[to]=cnt++;
}

void addEdge2(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof vis);
    memset(dis,0x3f,sizeof dis);
    dis[0]=0;
}

void Dijkstra(int s){
    priority_queue<pair<ll,int> > Q;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(u == 2*n+1) return;
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int T,u,v,s,t;
    ll w,x;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d%lld",&n,&m,&s,&t,&x);
        init();
        scanf("%s",str+1);
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            //���������˵� �����ֵ����,�������Ƿ��ڱ�Ȩ�Ļ����ϼ��뻻�ֵĴ���x
            if(str[u] == 'L'){
                if(str[v] == 'L')
                    addEdge1(u,v,w);//u->v ���軻�� ֻ�б�Ȩ
                else if(str[v] == 'R')
                    addEdge1(u,v,w+x);//u->v ����v���Ҫ�����ֻ������� ����Ϊw+x
                else{//�����д� ö��2�ֿ�����,�����,�����ִ��ۻ�Ժ��������߲���Ӱ��,��ͬ��״̬���յ����·���ܲ�ͬ
                    addEdge1(u,v,w);//��->�� ����w
                    addEdge1(u,v+n,w+x);//��->�� ����w+x
                }
            }
            else if(str[u] == 'R'){
                if(str[v] == 'L')
                    addEdge1(u,v,w+x);
                else if(str[v] == 'R')
                    addEdge1(u,v,w);
                else{
                    addEdge1(u,v,w+x);
                    addEdge1(u,v+n,w);
                }
            }
            else{//����u��Ϊ�д�,�Ǿ���Ҫ���� u�� ��ǰ��2��״̬ �����ȥ����v��
                if(str[v] == 'L'){
                    addEdge1(u,v,w);//���� w
                    addEdge1(u+n,v,w+x);//���� w+x
                }
                if(str[v] == 'R'){
                    addEdge1(u,v,w+x);
                    addEdge1(u+n,v,w);
                }
                else{//�д�->�д� 2x2 4�ֿ�������
                    addEdge1(u,v,w);
                    addEdge1(u,v+n,w+x);
                    addEdge1(u+n,v,w+x);
                    addEdge1(u+n,v+n,w);
                }
            }
        }
        //����Դ���������
        if(str[s] == 'L' || str[s] == 'R')//��㲻���д� ֻ��һ��״̬
            addEdge2(0,s,0);
        else{//������д� ��2��״̬
            addEdge2(0,s,0);
            addEdge2(0,s+n,0);
        }

        if(str[t] == 'L' || str[t] == 'R')
            addEdge2(t,2*n+1,0);
        else{
            addEdge2(t,2*n+1,0);
            addEdge2(t+n,2*n+1,0);
        }
        Dijkstra(0);
        printf("%lld\n",dis[2*n+1]);
    }
    return 0;
}

/*
����������ac
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 100100
#define M 200100
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N<<1],vis[N<<1],state[N<<1];
ll dis[N<<1],x;
char str[N];

struct Node{
    int to,next;
    ll w;
}edge[M<<4];

void addEdge(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to],w};
    head[to]=cnt++;
}

void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
}

void Dijkstra(int s){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=2*n;i++)
        dis[i]=INF;
    priority_queue<pair<ll,int> > Q;
    dis[s]=0;
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            ll ok=state[u]==state[v]?0:1;//״̬��һ�� ˵�������ֲ�һ��,��Ҫ���ϻ��ֵĴ���
            if(dis[v]>dis[u]+edge[i].w+ok*x){
                dis[v]=dis[u]+edge[i].w+ok*x;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int T,u,v,s,t;
    ll w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d%lld",&n,&m,&s,&t,&x);
        init();
        scanf("%s",str+1);
        for(int i=1;i<=n;i++){
            if(str[i] == 'L') state[i]=0,state[i+n]=0;
            else if(str[i] == 'R') state[i]=state[i+n]=1;
            else state[i]=0,state[i+n]=1;
        }
        //��������������ÿ�����ǲ����д�,��ͳһ����2��״̬���� ����ÿ���߶���Ӧ4��״̬���
        //ʵ�ʶ��ڲ����д�Ľڵ�,�ⲻ�������������Ӱ��,���ܻ�Ӱ��һ��ʱ��Ч��,���𰸲���.
        //����ֻ�����ֵĵ�,��Ȼ�������state����0,��v�����������������ʾ���ǽ��ŵ�,���ܴ��ڽϵ���ϱ�������
        while(m--){//��������
            scanf("%d%d%lld",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(u,v+n,w);
            addEdge(u+n,v,w);
            addEdge(u+n,v+n,w);
        }
        if(str[s] == 'L' || str[s] == 'R'){//�����ֻ��һ��״̬ ����һ��s���������·����
            Dijkstra(s);
            printf("%lld\n",min(dis[t],dis[t+n]));
        }
        else{//��������д�,�������� s,s+n�����·ȡ��Сֵ,�յ����� ��ȥ�ܾ������Ƿ����д� ����dis[t] dis[t+n]��ȡ��Сֵ���ɽ������ȷ��
            ll ans;
            Dijkstra(s);
            ans=min(dis[t],dis[t+n]);
            Dijkstra(s+n);
            ans=min(ans,min(dis[t],dis[t+n]));
            printf("%lld\n",ans);
        }
    }
    return 0;
}

*/

/*
���͵�ַ:https://blog.csdn.net/leoxe/article/details/107704404
���������ac��,�����ҵ�˼·����һ��,Ϊʲôwa
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define inf 0x3f3f3f3f3f3f3f3f
const int maxn = 2e5 + 70;
const int maxm = 2e6 + 7;
// �Ż��������������ȶ���
struct qnode {
    int u;
    LL w;
    qnode(int _u = 0, LL _w = 0) : u(_u), w(_w) {}
    bool operator < (const qnode& b) const {
        return w > b.w;
    }
};
// ������Լ�Ȩֵ
struct Edge {
    int v;
    LL w;
    Edge(int _v = 0, LL _w = 0) : v(_v), w(_w) {}
};
char str[maxn];
struct Dijstra {
    LL dis[maxn];
    int  n, m, S, T;
    int start, end;
    LL cc;
    bool vis[maxn];
    vector<Edge> G[maxn];
    priority_queue<qnode> pq;
    // ��ʼ��
    void init() {
        while(!pq.empty()) {pq.pop();}
        for(int i = 0; i <= n * 2 + 1; ++ i) {
            vis[i] = false;
            dis[i] = inf;
            G[i].clear();
        }
    }
    // �ӱ�
    void add_edge(int u, int v, LL w) {
        G[u].push_back(Edge(v, w));
        G[v].push_back(Edge(u, w));
    }
    // ����
    void read_data() {
        scanf("%d %d %d %d %lld", &n, &m, &S, &T, &cc);
        scanf("%s", str+1);
        start = 0;
        end = n * 2 + 1;
        init();
        if(str[S] == 'L') {
            add_edge(start, S, 0);
        } else if(str[S] == 'R') {
            add_edge(start, S + n, 0);
        } else {
            add_edge(start, S, 0);
            add_edge(start, S + n, 0);
        }
        if(str[T] == 'L') {
            add_edge(end, T, 0);
        } else if(str[T] == 'R') {
            add_edge(end, T + n, 0);
        } else {
            add_edge(end, T, 0);
            add_edge(end, T + n, 0);
        }
        while(m --) {
            int u, v;
            LL w;
            scanf("%d %d %lld", &u, &v, &w);
            if(str[u] == 'L') {
                if(str[v] == 'L') {
                    add_edge(u, v, w);
                } else if(str[v] == 'R') {
                    add_edge(u, v + n, w + cc);
                } else {
                    add_edge(u, v, w);
                    add_edge(u, v + n, w + cc);
                }
            } else if(str[u] == 'R') {
                if(str[v] == 'L') {
                    add_edge(u + n, v, w + cc);
                } else if(str[v] == 'R') {
                    add_edge(u + n, v + n, w);
                } else {
                    add_edge(u + n, v, w + cc);
                    add_edge(u + n, v + n, w);
                }
            } else {
                if(str[v] == 'L') {
                    add_edge(u, v, w);
                    add_edge(u + n, v, w + cc);
                } else if(str[v] == 'R') {
                    add_edge(u, v + n, w + cc);
                    add_edge(u + n, v + n, w);
                } else {
                    add_edge(u, v, w);
                    add_edge(u, v + n, w + cc);
                    add_edge(u + n, v, w + cc);
                    add_edge(u + n, v + n, w);
                }
            }
        }
    }

    void dijstra(int st) {
        S = st;
        dis[st] = 0;
        pq.push(qnode(st, 0));
        qnode tmp;
        while(!pq.empty()) {
            tmp = pq.top();
            pq.pop();
            int u = tmp.u;
            if(vis[u]) {
                continue;
            }
            vis[u] = true;
            int sz = G[u].size();
            for(int i = 0; i < sz; ++ i) {
                int v = G[u][i].v;
                LL w = G[u][i].w;
                if(!vis[v] && dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    pq.push(qnode(v, dis[v]));
                }
            }
        }
        printf("%lld\n", dis[end]);
    }
}res;
void Solve(int& kase) {
    int p;
    scanf("%d",&p);
    while(p--){
        res.read_data();
        res.dijstra(0);
    }
}
int main(){
    int k=1;
    Solve(k);
    return 0;
}
*/

/*
�Լ�д�Ļ���wa
��https://blog.csdn.net/leoxe/article/details/107704404һ��Ϊʲôwa???
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define N 200100
#define M 4001000
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;

int n,m,cnt,head[N<<1],vis[N<<1];
ll dis[N<<1];
char str[N];

struct Node{
    int to,next;
    ll w;
}edge[M];

void addEdge1(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
    edge[cnt]=(Node){from,head[to],w};
    head[to]=cnt++;
}

void addEdge2(int from,int to,ll w){
    edge[cnt]=(Node){to,head[from],w};
    head[from]=cnt++;
}

void init(){
    cnt=0;
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof vis);
    for(int i=0;i<=2*n+1;i++)
        dis[i]=INF;
    //memset(dis,0x3f,sizeof dis);
    dis[0]=0;
}

    priority_queue<pair<ll,int> > Q;
void Dijkstra(int s){
    while(!Q.empty()) Q.pop();
    Q.push(make_pair(0,s));
    int u,v;
    while(!Q.empty()){
        u=Q.top().second;
        Q.pop();
        //if(vis[2*n+1]) return;
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w){
                dis[v]=dis[u]+edge[i].w;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
}

int main(){
    int T,u,v,s,t;
    ll w,x;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d%lld",&n,&m,&s,&t,&x);
        init();
        scanf("%s",str+1);
        if(str[s] == 'L')
            addEdge1(0,s,0);
        else if(str[s] == 'R')
            addEdge1(0,s+n,0);
        else{
            addEdge1(0,s,0);
            addEdge1(0,s+n,0);
        }

        if(str[t] == 'L')
            addEdge1(2*n+1,t,0);
        else if(str[t] == 'R')
            addEdge1(2*n+1,t+n,0);
        else{
            addEdge1(2*n+1,t,0);
            addEdge1(2*n+1,t+n,0);
        }
        while(m--){
            scanf("%d%d%lld",&u,&v,&w);
            if(str[u] == 'L'){
                if(str[v] == 'L')
                    addEdge1(u,v,w);
                else if(str[v] == 'R')
                    addEdge1(u,v+n,w+x);
                else{
                    addEdge1(u,v,w);
                    addEdge1(u,v+n,w+x);
                }
            }
            else if(str[u] == 'R'){
                if(str[v] == 'L')
                    addEdge1(u+n,v,w+x);
                else if(str[v] == 'R')
                    addEdge1(u+n,v+n,w);
                else{
                    addEdge1(u+n,v,w+x);
                    addEdge1(u+n,v+n,w);
                }
            }
            else{
                if(str[v] == 'L'){
                    addEdge1(u,v,w);
                    addEdge1(u+n,v,w+x);
                }
                if(str[v] == 'R'){
                    addEdge1(u,v+n,w+x);
                    addEdge1(u+n,v+n,w);
                }
                else{
                    addEdge1(u,v,w);
                    addEdge1(u,v+n,w+x);
                    addEdge1(u+n,v,w+x);
                    addEdge1(u+n,v+n,w);
                }
            }
        }
        Dijkstra(0);
        printf("%lld\n",dis[2*n+1]);
    }
    return 0;
}
*/
