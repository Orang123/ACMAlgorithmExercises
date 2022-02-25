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
题意:如果两个人互相打电话（直接或者间接），则说他们在同一个电话圈里。
例如，a打给b，b打给c，c打给d，d打给a，则这四个人在同一个圈里；
如果e打给f，而f不打给e，则不能推出e和f在同一个电话圈。
输入n(n≤25n(n≤25 )个人的mm 次电话，找出所有的电话圈。
人名只包含字母，不超过25个字符，且不重复。
链接:https://www.luogu.com.cn/problem/UVA247
思路:tarjan求解强连通分量.
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
        memset(dfn,0,sizeof(dfn));//dfn要初始化 因为dfs之前要判断这个SCC是否被遍历
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
//可采用floyd处理传递闭包,只需修改松弛条件为G[i][j]|=(G[i][k] & G[k][j])
//floyd 传递闭包 ac 10ms
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
