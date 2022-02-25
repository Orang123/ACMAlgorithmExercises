//ac 0ms dfsÿ������һ������· �ڽӾ�����
//��ÿ����������·���ܱ�֤������·ʱ��̵�,Ҳ����������������·���,
//����·�������ܺ��ǲ�ȷ������,���ܻ�ܳ�,����dfs�տ�ʼ�ܿ����ҵ�һ������·
//����·���бߵĲ����������ϼ���Ϊ0,������������·,Ҳ���ظ������������·��,Ч�ʾͻ���.
//��������Ч���ǲ���bfs��
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 210
#define INF 0x3f3f3f3f
using namespace std;
/*
����:m������,n��ˮ��,ÿ��ˮ��ˮ������ֻ����һ������,
ÿ��ˮ���и�ˮ��������,��ˮ���д�1������m��(Ϫ��)��ˮ
�����������.
����:m����,n������ߵ�����,ÿ������һ������,���1��m�������.
ע��:��������ظ���,��1->2 20 1->2 30,����1->2ʵ������Ϊ30,
���Ҫ�ۼ�����.
����:http://poj.org/problem?id=1273
˼·:EK�����㷨dfs��������·��������ģ��.
*/
int net[N][N],n,m;
bool vis[N];

//һ��dfsֻ����һ������·
int dfs(int s,int flow){
    if(s == m) return flow;//���������t�ͷ���
    int incf;
    for(int i=1;i<=m;i++){
        if(!vis[i] && net[s][i]>0){
            //vis[i]����ѷ��ʱ���֮ǰ���������·�������ķ���,�ִ�i������dfs����s��,
            //s���ֽ���i���dfs,�������������ѭ��
            vis[i]=true;//һ������· һ����ֻ�����һ��
            incf=dfs(i,min(net[s][i],flow));//��¼����·����С�Ĳ�������
            if(incf){//����ʱ���� ����·�ϱߵĲ�������
                net[s][i]-=incf;//�������������incf
                net[i][s]+=incf;//�������������incf
                return incf;
            }
        }
    }
    return 0;//û������������·
}

int maxFlow(){
    int sum=0,tmp;
    while(1){
        memset(vis,false,sizeof(vis));
        vis[1]=true;//dfsʱ�½��2��ʼ�����������Դ��1�ѷ���
        tmp=dfs(1,INF);//flow ��ʼ��Ϊ���
        if(tmp) sum+=tmp;//������ۼӵ�ǰ����·��С��������
        else break;//����0û������������·
    }
    return sum;
}

int main(){
    int x,y,cap;
    while(scanf("%d %d",&n,&m)!=EOF){
        memset(net,0,sizeof(net));
        for(int i=1;i<=n;i++){
            scanf("%d %d %d",&x,&y,&cap);
            net[x][y]+=cap;
        }
        printf("%d\n",maxFlow());
    }
    return 0;
}

/*
//ac 0ms dfsÿ������һ������· ��ʽǰ���Ǵ��
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 210
#define INF 0x3f3f3f3f
using namespace std;

int n,m,cnt,head[N],vis[N];
struct Edge{
    int to,next,cf;
}edge[N<<1];//��ΪҪ�淴���,���Ա���*2

void addEdge(int from,int to,int cf){
    edge[cnt].to=to;
    edge[cnt].cf+=cf;//���ظ���,Ҫ�ۼ�����,���ۼ�Ҳ��ac ��֪ɶԭ��
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

//һ��dfsֻ����һ������·
int dfs(int u,int flow){
    if(u == m) return flow;//���������t�ͷ���
    int incf;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(!vis[v] && edge[i].cf>0){
            //vis[i]����ѷ��ʱ���֮ǰ���������·�������ķ���,�ִ�i������dfs����s��,
            //s���ֽ���i���dfs,�������������ѭ��
            vis[v]=1;//һ������· һ����ֻ�����һ��
            incf=dfs(v,min(edge[i].cf,flow));//��¼����·����С�Ĳ�������
            if(incf){//����ʱ���� ����·�ϱߵĲ�������
                edge[i].cf-=incf;//�������������incf
                edge[i^1].cf+=incf;//�������������incf
                return incf;
            }
        }
    }
    return 0;//û������������·
}

int maxFlow(){
    int sum=0,tmp;
    while(1){
        memset(vis,0,sizeof(vis));
        vis[1]=1;//dfsʱ�½��2��ʼ�����������Դ��1�ѷ���
        tmp=dfs(1,INF);//flow ��ʼ��Ϊ���
        if(tmp) sum+=tmp;//������ۼӵ�ǰ����·��С��������
        else break;//����0û������������·
    }
    return sum;
}

int main(){
    int x,y,cap;
    while(scanf("%d %d",&n,&m)!=EOF){
        cnt=0;
        memset(head,-1,sizeof(head));
        memset(edge,0,sizeof(edge));//��ΪҪ�ۼ�����,��������cf��ʼ��Ϊ0
        while(n--){
            scanf("%d %d %d",&x,&y,&cap);
            addEdge(x,y,cap);
            addEdge(y,x,0);
        }
        printf("%d\n",maxFlow());
    }
    return 0;
}
*/

/*
//ac 0ms dfs��stlջstackģ����������· �ڽӾ�����
#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 210
#define INF 0x3f3f3f3f
using namespace std;

int net[N][N],n,m,pre[N],incf[N];//in capacity flow �����������

int dfs(int s,int t){
    int p;
    stack<int> Q;
    incf[s]=INF;
    memset(pre,-1,sizeof(pre));
    Q.push(s);
    while(!Q.empty()){
        p=Q.top();
        Q.pop();
        for(int i=2;i<=m;i++){
            if(net[p][i]>0 && pre[i]==-1){//�ñߵĲ�������Ҫ���� �õ�֮ǰ����δ������ ���ڷ���,������vis �������ַ���s��dfs,��Ϊ��pre[v]����
                incf[i]=min(incf[p],net[p][i]);//��¼������·����С�Ĳ�������
                pre[i]=p;//pre��¼����·�иõ��ǰ���ڵ�
                if(i==t)//������ʱ����һ��������·,����
                    return incf[t];
                Q.push(i);
            }
        }
    }
    return -1;
}


int maxFlow(){
    int sum=0,q;
    while(dfs(1,m)!=-1){
        q=m;
        while(q!=1){
            net[pre[q]][q]-=incf[m];
            net[q][pre[q]]+=incf[m];
            q=pre[q];
        }
        sum+=incf[m];
    }
    return sum;
}

int main(){
    int x,y,cap;
    while(scanf("%d %d",&n,&m)!=EOF){
        memset(net,0,sizeof(net));
        for(int i=1;i<=n;i++){
            scanf("%d %d %d",&x,&y,&cap);
            net[x][y]+=cap;
        }
        printf("%d\n",maxFlow());
    }
    return 0;
}
*/
