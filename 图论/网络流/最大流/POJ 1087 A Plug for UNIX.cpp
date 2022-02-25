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
//ac 47ms dinic Դ��->�õ���->����/ת����->���
/*
����:��n������,����m���õ���,ÿ���õ�����ѡ���Լ��õĲ���,
��ֻ��һ��,�����k��ת����,����a,b����a������ת��Ϊb����,
������м����õ���û�в�������.
ע��;�����õ�����ϵ��,�õ������ӵĲ�һ���ǲ���,������ת����.
����:http://poj.org/problem?id=1087
˼·:��Ϊ����ת����������,����ֱ���ö���ͼƥ������,ת��Ϊ����������.
����Դ��0,���301(�������õ�����ת�����ֱ������100��),Դ������ÿ��
�õ���,����Ϊ1,ÿ���õ�����������ԵĲ�������,����Ϊ1,ÿ������������,
����Ϊ1,ת�����Ĺ�ϵa b,��a->b�������,����ΪINF,��Ϊת������û��ʹ�ô�������,
���������������ж��ٸ��õ����в���ʹ��,��ôm-����������м����õ����޲���
����.
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
    while(n--){//n������
        cin >> str1;
        mp[str1]=++num;
        addEdge(num,ed,1);//ÿ���������㽨��,����Ϊ1
    }
    scanf("%d",&m);//m���õ���
    for(int i=1;i<=m;i++){
        cin >> str1 >> str2;//str1���õ��� str2���õ��������ӵĲ�����ת����,ת����Ҫ���¶�������
        mp[str1]=++num;
        if(!mp.count(str2))//str2������ת����,����n�������ı��
            mp[str2]=++num;
        addEdge(mp[str1],mp[str2],1);//ÿ���õ�������ֱ�����ӵĲ������õ�������,����Ϊ1
        addEdge(st,mp[str1],1);//Դ���������õ�������,����Ϊ1
    }
    scanf("%d",&k);//k��ת����
    while(k--){
        cin >> str1 >> str2;
        if(!mp.count(str1))//str1 str2���ܻ����ظ�
            mp[str1]=++num;
        if(!mp.count(str2))
            mp[str2]=++num;
        addEdge(mp[str1],mp[str2],INF);//ת�������Խ��õ������ӵ�str1ת��Ϊ���ӵ�str2
    }
    printf("%d",m-max_flow(st,ed));
    return 0;
}

/*
//ac 32ms dinic Դ��->����/ת����->�õ���->���
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
        addEdge(st,num,1);//Դ��->����
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        cin >> str1 >> str2;
        mp[str1]=++num;
        if(!mp.count(str2))
            mp[str2]=++num;
        addEdge(mp[str2],mp[str1],1);//������ת����->�õ���
        addEdge(mp[str1],ed,1);//�õ���->���
    }
    scanf("%d",&k);
    while(k--){
        cin >> str1 >> str2;
        if(!mp.count(str1))
            mp[str1]=++num;
        if(!mp.count(str2))
            mp[str2]=++num;
        //��ΪԴ��ֱ���������ǲ���,����ת�����Ĺ�ϵa->b Ҫ������ ����b->a,����ΪINF(����),��Ϊת����û��ʹ�ô�������
        addEdge(mp[str2],mp[str1],INF);
    }
    printf("%d",m-max_flow(st,ed));
    return 0;
}
*/
