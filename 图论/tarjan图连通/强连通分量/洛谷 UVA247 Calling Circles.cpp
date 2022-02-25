#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>
#include<stack>
#include<algorithm>
#define N 30
#define M 700
using namespace std;
//tarjan ac 10ms
/*
����:��������˻����绰��ֱ�ӻ��߼�ӣ�����˵������ͬһ���绰Ȧ�
���磬a���b��b���c��c���d��d���a�������ĸ�����ͬһ��Ȧ�
���e���f����f�����e�������Ƴ�e��f��ͬһ���绰Ȧ��
����n(n��25n(n��25 )���˵�mm �ε绰���ҳ����еĵ绰Ȧ��
����ֻ������ĸ��������25���ַ����Ҳ��ظ���
����:https://www.luogu.com.cn/problem/UVA247
˼·:tarjan���ǿ��ͨ����.
*/

int head[N],cnt,dfn[N],low[N],in[N],n,m,num,id,block[N];
stack<int> s;
map<string,int> mp;
map<string,int>::iterator it;
string str1,str2;

struct Edge{
    int to,next;
}edge[M];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    dfn[u]=low[u]=++num;
    s.push(u);
    in[u]=1;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u]){
        ++id;
        do{
            v=s.top();
            block[v]=id;
            s.pop();
            in[v]=0;
        }while(v!=u);
    }
}

void search(int x,int flag){
    for(it=mp.begin();it!=mp.end();it++){
        if(it->second == x){
            if(!flag)
                cout << it->first;
            else
                cout << ", " << it->first;
        }
    }
}

int main(){
    int k,cas=0;
    while(scanf("%d%d",&n,&m) && n+m){
        num=id=k=cnt=0;
        cas++;
        mp.clear();
        memset(dfn,0,sizeof(dfn));//dfnҪ��ʼ�� ��Ϊdfs֮ǰҪ�ж����SCC�Ƿ񱻱���
        memset(head,-1,sizeof head);
        while(m--){
            cin >> str1 >> str2;
            if(!mp.count(str1))
                mp[str1]=++k;
            if(!mp.count(str2))
                mp[str2]=++k;
            addEdge(mp[str1],mp[str2]);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i])
                dfs(i);
        }
        printf("Calling circles for data set %d:\n",cas);
        for(int i=1;i<=id;i++){
            int flag=0;
            for(int j=1;j<=n;j++){
                if(block[j] == i){
                    search(j,flag);
                    if(!flag) flag=1;
                }
            }
            cout << endl;
        }
    }
    return 0;
}

/*
//�ɲ���floyd�����ݱհ�,ֻ���޸��ɳ�����ΪG[i][j]|=(G[i][k] & G[k][j])
//floyd ���ݱհ� ac 10ms
#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<map>
#include<set>
#include<queue>
#include<algorithm>
#define N 30
#define INF 0x3f3f3f3f
using namespace std;

int n,m,num,G[N][N],vis[N];
map<string,int> mp;
set<string> set0;
map<string,int>::iterator it;

int judge(string s){
    if(!set0.count(s)){
        set0.insert(s);
        mp[s]=++num;
    }
    return mp[s];
}

string searchName(int i){
    for(it=mp.begin();it!=mp.end();it++){
        if(it->second == i)
            return it->first;
    }
}

void dfs(int u){
    vis[u]=1;
    for(int v=1;v<=n;v++){
        if(!vis[v] && G[u][v] && G[v][u]){
            cout << ", " << searchName(v);
            dfs(v);
        }
    }
}

int main(){
    int cas=0;
    string s1,s2;
    while(scanf("%d%d",&n,&m) && n+m){
        num=0;
        mp.clear();
        set0.clear();
        memset(vis,0,sizeof(vis));
        memset(G,0,sizeof(G));
        cas++;
        while(m--){
            cin >> s1 >> s2;
            G[judge(s1)][judge(s2)]=1;
        }
        for(int k=1;k<=n;k++){
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++)
                    G[i][j]|=(G[i][k] & G[k][j]);
            }
        }
        printf("Calling circles for data set %d:\n",cas);
        for(int i=1;i<=n;i++){
            if(vis[i]) continue;
            cout << searchName(i);
            dfs(i);
            cout << endl;
        }
    }
    return 0;
}
*/
