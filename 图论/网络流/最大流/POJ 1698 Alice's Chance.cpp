#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 400
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;
//ac 0ms dinic 源点->电影->天->汇点
/*
题意:Alice要拍n部电影,每部电影每星期只有固定的几天可以拍,
每部电影需要拍di天才能完成,并且要求每部电影在前Wi周完成拍摄,
现在问n部电影是否都能在规定时间内完成拍摄.
链接:http://poj.org/problem?id=1698
思路:最多有20部电影,最多有50周,即最多350天,那么构建源点0,
汇点50*7+20+1=371,源点向每部电影i连边,容量为i电影拍摄需要
的天数,每部电影连向每一周内可拍摄的天,容量为1,所有可拍摄电影
的天连向汇点,容量为1.跑最大流,判断结果是否等于所有电影拍摄需要
的天数,是输出"Yes",否则输出"No".
*/
int n,st,ed,film[55][12],week,cnt,head[N],dis[N],sum,vis[N];
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
    week=-1;
    sum=cnt=0;
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=9;j++)
                scanf("%d",&film[i][j]);
            sum+=film[i][8];//统计所有电影拍摄需要的天数
            week=max(week,film[i][9]);//记录所有电影最晚拍摄的周上限
        }
        st=0,ed=week*7+n+1;
        for(int i=1;i<=n;i++){
            addEdge(st,i,film[i][8]);//源点向每部电影i连边,容量为拍摄天数
            for(int j=1;j<=film[i][9];j++){
                for(int k=1;k<=7;k++){
                    if(film[i][k]){
                        addEdge(i,(j-1)*7+k+n,1);//电影向天数连边,容量为1
                        vis[(j-1)*7+k+n]=1;//标记这天
                        //在这里建天到汇点的连边,如果不同的电影都可在这天拍摄,
                        //那这天和汇点就会建多条边,这样最大流结果就会出错,不符合题意
                        //addEdge((j-1)*7+k+n,ed,1);
                    }
                }
            }
        }
        for(int i=1;i<=week;i++){
            for(int j=1;j<=7;j++){
                if(vis[(i-1)*7+j+n])//只有可能拍摄电影的天才连向汇点,容量为1
                    addEdge((i-1)*7+j+n,ed,1);
            }
        }
        printf("%s\n",sum == max_flow(st,ed)?"Yes":"No");
    }
    return 0;
}

/*
//ac 0ms dinic 源点->天->电影->汇点
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 400
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;

int n,st,ed,film[55][12],cnt,head[N],dis[N],sum;
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
    st=sum=cnt=0;
    ed=50*7+20+1;
    memset(head,-1,sizeof(head));
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=9;j++)
                scanf("%d",&film[i][j]);
            sum+=film[i][8];
        }
        for(int i=1;i<=350;i++)
            addEdge(st,i,1);//源点连向天数,容量为1
        for(int i=1;i<=n;i++){
            for(int j=1;j<=film[i][9];j++){
                for(int k=1;k<=7;k++){
                    if(film[i][k])
                        addEdge((j-1)*7+k,i+350,1);//天数连向电影 容量为1
                }
            }
        }
        for(int i=1;i<=n;i++)//电影连向汇点,容量为拍摄需要天数
            addEdge(i+350,ed,film[i][8]);
        printf("%s\n",sum == max_flow(st,ed)?"Yes":"No");
    }
    return 0;
}
*/
