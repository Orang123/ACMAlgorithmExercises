#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
#define N 1600
#define M 4000000
#define INF 0x3f3f3f3f
using namespace std;
//ac 360ms 二分连接汇点容量+dinic
/*
题意:要把n个人分到m个组中,每个人只能属于一个组,
问最大组的人数最少是多少.
链接:http://poj.org/problem?id=2289
思路:多重匹配,问组的人数最大值最小化,二分最大组的人数,l=0,r=n,
dinic网络流验证,若最大流等于n,则说明最大组的人数容量还可以再小点,
否则组的人数容量可再大点.
*/
int n,m,id,num,st,ed,cnt,head[N],dis[N];
map<string,int> mp;
vector<int> G[N];
struct Edge{
    int to,next,cf;
}edge[M];

void addEdge(int from,int to,int cf){
    edge[cnt]=(Edge){to,head[from],cf};
    head[from]=cnt++;
    edge[cnt]=(Edge){from,head[to],0};
    head[to]=cnt++;
}

int bfs(int s,int ed){
    queue<int> Q;
    memset(dis,-1,sizeof(dis));
    dis[s]=0;
    Q.push(s);
    int u,v;
    while(!Q.empty()){
        u=Q.front();
        Q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next){
            v=edge[i].to;
            if(edge[i].cf>0 && dis[v] == -1){
                dis[v]=dis[u]+1;
                if(v == ed) return 1;
                Q.push(v);
            }
        }
    }
    return 0;
}

int dfs(int u,int ed,int flow){
    if(u == ed)
        return flow;
    int res=0,incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(edge[i].cf>0 && dis[v] == dis[u]+1){
            incf=dfs(v,ed,min(flow,edge[i].cf));
            if(incf>0){
                edge[i].cf-=incf;
                edge[i^1].cf+=incf;
                flow-=incf;
                res+=incf;
            }
            if(!flow)
                break;
        }
    }
    if(!res)
        dis[u]=-1;
    return res;
}

int max_flow(int st,int ed){
    int sum=0;
    while(bfs(st,ed))
        sum+=dfs(st,ed,INF);
    return sum == n;
}

void build(int cf){
    cnt=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++){
        addEdge(st,i,1);
        int siz=G[i].size();
        for(int j=0;j<siz;j++){
            addEdge(i,G[i][j]+n,1);
        }
    }
    for(int i=1;i<=m;i++)
        addEdge(i+n,ed,cf);
}

void init(){
    num=0;
    st=0,ed=n+m+1;
    mp.clear();
    for(int i=0;i<N;i++) G[i].clear();
}


int main(){
    string str;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        for(int i=1;i<=n;i++){
            cin >> str;
            mp[str]=++num;
            while(1){
                scanf("%d",&id);
                G[num].push_back(id+1);
                if(getchar() == '\n') break;
            }
        }
        int l=0,r=n,mid;
        while(l<r){
            mid=(l+r)/2;
            build(mid);
            if(max_flow(st,ed))
                r=mid;
            else
                l=mid+1;
        }
        printf("%d\n",l);
    }
    return 0;
}

/*
//ac 375ms 二分所有组容纳最多人数+二分图多重匹配
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
#define N 1100
#define M 4000000
#define INF 0x3f3f3f3f
using namespace std;

int n,m,num0,cnt0,id,head[N],vis[510],num[510],link[510][N],cnt[510];
map<string,int> mp;
vector<int> G[N];
struct Edge{
    int to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt0]=(Edge){to,head[from]};
    head[from]=cnt0++;
}

int dfs(int u,int clock){
    int siz=G[u].size();
    for(int i=0;i<siz;i++){
        int v=G[u][i];
        if(vis[v] == clock) continue;
        vis[v]=clock;
        if(cnt[v]<num[v]){
            link[v][++cnt[v]]=u;
            return 1;
        }
        else{
            for(int i=1;i<=cnt[v];i++){
                if(dfs(link[v][i],clock)){
                    link[v][i]=u;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int hungary(){
    int tp=0;
    for(int i=1;i<=n;i++)
        if(dfs(i,i)) tp++;
    return tp == n;
}

void build(int cf){
    cnt0=0;
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=n;i++){
        int siz=G[i].size();
        for(int j=0;j<siz;j++)
            addEdge(i,G[i][j]);
    }
    for(int i=1;i<=m;i++)
        num[i]=cf;
}

void init(){
    num0=0;
    mp.clear();
    for(int i=1;i<=n;i++) G[i].clear();
}

int main(){
    string str;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        for(int i=1;i<=n;i++){
            cin >> str;
            mp[str]=++num0;
            while(1){
                scanf("%d",&id);
                G[num0].push_back(id+1);
                if(getchar() == '\n') break;
            }
        }
        int l=0,r=n,mid;
        while(l<r){
            mid=(l+r)/2;
            build(mid);
            if(hungary())
                r=mid;
            else
                l=mid+1;
        }
        printf("%d\n",l);
    }
    return 0;
}
*/
