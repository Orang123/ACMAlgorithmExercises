#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<queue>
#include<map>
#include<algorithm>
#define N 400
#define M 100000
#define INF 0x3f3f3f3f
using namespace std;
//ac 47ms dinic 源点->用电器->插座/转换器->汇点
/*
题意:有n个插座,还有m个用电器,每个用电器会选择自己用的插座,
但只有一种,最后有k个转换器,输入a,b代表a插座可转化为b插座,
问最后有几个用电器没有插座可用.
注意;输入用电器关系中,用电器连接的不一定是插座,可能是转换器.
链接:http://poj.org/problem?id=1087
思路:因为存在转换器的问题,不好直接拿二分图匹配来做,转化为网络流问题.
构建源点0,汇点301(插座、用电器、转换器分别最多有100个),源点连向每个
用电器,容量为1,每个用电器连向能配对的插座连边,容量为1,每个插座连向汇点,
容量为1,转换器的关系a b,建a->b的有向边,容量为INF,因为转换器并没有使用次数上限,
跑最大流即是最多有多少个用电器有插座使用,那么m-最大流即是有几个用电器无插座
可用.
*/
int n,m,k,num,st,ed,cnt,head[N],dis[N];
map<string,int> mp;
string str1,str2;
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
    int ans=0;
    while(bfs(st,ed))
        ans+=dfs(st,ed,INF);
    return ans;
}

void init(){
    cnt=0;
    st=0,ed=301;
    memset(head,-1,sizeof(head));
    mp.clear();
}

int main(){
    init();
    scanf("%d",&n);
    while(n--){//n个插座
        cin >> str1;
        mp[str1]=++num;
        addEdge(num,ed,1);//每个插座向汇点建边,容量为1
    }
    scanf("%d",&m);//m个用电器
    for(int i=1;i<=m;i++){
        cin >> str1 >> str2;//str1是用电器 str2是用电器可连接的插座或转换器,转换器要重新定义其编号
        mp[str1]=++num;
        if(!mp.count(str2))//str2可能是转换器,不是n个插座的编号
            mp[str2]=++num;
        addEdge(mp[str1],mp[str2],1);//每个用电器向能直接连接的插座或用电器建边,容量为1
        addEdge(st,mp[str1],1);//源点向所有用电器建边,容量为1
    }
    scanf("%d",&k);//k个转换器
    while(k--){
        cin >> str1 >> str2;
        if(!mp.count(str1))//str1 str2可能会有重复
            mp[str1]=++num;
        if(!mp.count(str2))
            mp[str2]=++num;
        addEdge(mp[str1],mp[str2],INF);//转换器可以将用电器连接的str1转化为连接到str2
    }
    printf("%d",m-max_flow(st,ed));
    return 0;
}

/*
//ac 32ms dinic 源点->插座/转换器->用电器->汇点
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<queue>
#include<map>
#include<algorithm>
#define N 400
#define M 100000
#define INF 0x3f3f3f3f
using namespace std;

int n,m,k,num,st,ed,cnt,head[N],dis[N];
map<string,int> mp;
string str1,str2;
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
    int ans=0;
    while(bfs(st,ed))
        ans+=dfs(st,ed,INF);
    return ans;
}

void init(){
    cnt=0;
    st=0,ed=301;
    memset(head,-1,sizeof(head));
    mp.clear();
}

int main(){
    init();
    scanf("%d",&n);
    while(n--){
        cin >> str1;
        mp[str1]=++num;
        addEdge(st,num,1);//源点->插座
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        cin >> str1 >> str2;
        mp[str1]=++num;
        if(!mp.count(str2))
            mp[str2]=++num;
        addEdge(mp[str2],mp[str1],1);//插座或转换器->用电器
        addEdge(mp[str1],ed,1);//用电器->汇点
    }
    scanf("%d",&k);
    while(k--){
        cin >> str1 >> str2;
        if(!mp.count(str1))
            mp[str1]=++num;
        if(!mp.count(str2))
            mp[str2]=++num;
        //因为源点直接相连的是插座,所以转换器的关系a->b 要反过来 建成b->a,容量为INF(无穷),因为转换器没有使用次数限制
        addEdge(mp[str2],mp[str1],INF);
    }
    printf("%d",m-max_flow(st,ed));
    return 0;
}
*/
