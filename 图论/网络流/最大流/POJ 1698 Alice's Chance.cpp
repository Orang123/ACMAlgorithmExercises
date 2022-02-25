#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 400
#define M 1000000
#define INF 0x3f3f3f3f
using namespace std;
//ac 0ms dinic Դ��->��Ӱ->��->���
/*
����:AliceҪ��n����Ӱ,ÿ����Ӱÿ����ֻ�й̶��ļ��������,
ÿ����Ӱ��Ҫ��di��������,����Ҫ��ÿ����Ӱ��ǰWi���������,
������n����Ӱ�Ƿ����ڹ涨ʱ�����������.
����:http://poj.org/problem?id=1698
˼·:�����20����Ӱ,�����50��,�����350��,��ô����Դ��0,
���50*7+20+1=371,Դ����ÿ����Ӱi����,����Ϊi��Ӱ������Ҫ
������,ÿ����Ӱ����ÿһ���ڿ��������,����Ϊ1,���п������Ӱ
����������,����Ϊ1.�������,�жϽ���Ƿ�������е�Ӱ������Ҫ
������,�����"Yes",�������"No".
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
            sum+=film[i][8];//ͳ�����е�Ӱ������Ҫ������
            week=max(week,film[i][9]);//��¼���е�Ӱ���������������
        }
        st=0,ed=week*7+n+1;
        for(int i=1;i<=n;i++){
            addEdge(st,i,film[i][8]);//Դ����ÿ����Ӱi����,����Ϊ��������
            for(int j=1;j<=film[i][9];j++){
                for(int k=1;k<=7;k++){
                    if(film[i][k]){
                        addEdge(i,(j-1)*7+k+n,1);//��Ӱ����������,����Ϊ1
                        vis[(j-1)*7+k+n]=1;//�������
                        //�����ｨ�쵽��������,�����ͬ�ĵ�Ӱ��������������,
                        //������ͻ��ͻὨ������,�������������ͻ����,����������
                        //addEdge((j-1)*7+k+n,ed,1);
                    }
                }
            }
        }
        for(int i=1;i<=week;i++){
            for(int j=1;j<=7;j++){
                if(vis[(i-1)*7+j+n])//ֻ�п��������Ӱ�����������,����Ϊ1
                    addEdge((i-1)*7+j+n,ed,1);
            }
        }
        printf("%s\n",sum == max_flow(st,ed)?"Yes":"No");
    }
    return 0;
}

/*
//ac 0ms dinic Դ��->��->��Ӱ->���
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
            addEdge(st,i,1);//Դ����������,����Ϊ1
        for(int i=1;i<=n;i++){
            for(int j=1;j<=film[i][9];j++){
                for(int k=1;k<=7;k++){
                    if(film[i][k])
                        addEdge((j-1)*7+k,i+350,1);//���������Ӱ ����Ϊ1
                }
            }
        }
        for(int i=1;i<=n;i++)//��Ӱ������,����Ϊ������Ҫ����
            addEdge(i+350,ed,film[i][8]);
        printf("%s\n",sum == max_flow(st,ed)?"Yes":"No");
    }
    return 0;
}
*/
