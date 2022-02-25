#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<map>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;
//ac 733ms
/*
题意:n个人之间存在m条双向关系的网络(可能不连通),关键关系指的是
如果这种关系被取消或不再存在,我们将永远失去与社会上某些人的
关系网络,也就是关系网络会被断开不连通.求出所有的这些关系并按照输入的顺序输出.
不存在重复关系(重边),和自己到自己的关系(无自环).

释义:求解无向图中的所有桥并按照输入顺序输出人名.注意对于原图不连通的情况,
不存在关键关系,因为本身网络就是断开的,输出0.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3849
思路:tarjan求解桥.人名转化为点可用mp,按输入顺序输出桥可以用链式前向星存边,
输出时,点转化边可以在存边时用两个map来<string,int>mp1,<int,string>mp2来转化.
*/
int n,m,dfn[N],low[N],clock,cnt,head[N],ans;
map<string,int> mp1;
map<int,string> mp2;

struct Edge{
    int from,to,next,flag;
}edge[M<<1];

void addEdge(int from,int to,int flag){
    edge[cnt]=(Edge){from,to,head[from],flag};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v]){
                ans++;
                edge[i].flag=1;
                edge[i^1].flag=1;
            }
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
}

int main(){
    int T,u,v,id=0;
    string str1,str2;
    scanf("%d",&T);
    while(T--){
        ans=id=clock=cnt=0;
        mp1.clear();
        mp2.clear();
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        scanf("%d%d",&n,&m);
        while(m--){
            cin >> str1 >> str2;
            if(!mp1.count(str1)){//str1已经设置过编号就不再设置
                mp1[str1]=++id;
                mp2[id]=str1;
            }
            if(!mp1.count(str2)){
                mp1[str2]=++id;
                mp2[id]=str2;
            }
            addEdge(mp1[str1],mp1[str2],0);
            addEdge(mp1[str2],mp1[str1],0);
        }
        int flag=0;
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                dfs(i,-1);
                flag++;
            }
        }
        if(flag!=1){//如果原图不连通 输出0 不存在关键关系.
            cout << 0 << endl;
            continue;
        }
        cout << ans << endl;
        for(int i=0;i<cnt;i+=2){
            if(!edge[i].flag) continue;
            u=edge[i].from;
            v=edge[i].to;
            cout << mp2[u] << " " << mp2[v] << endl;
        }
    }
    return 0;
}

/*
//ac 717ms
//一个map<string,int> 输出int转化string时 用迭代器遍历,效率较低,每次都得遍历一遍hash表 O(n^2)
#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<map>
#include<algorithm>
#define N 10100
#define M 100100
using namespace std;

int n,m,dfn[N],low[N],clock,cnt,head[N],ans;
map<string,int> mp;
map<string,int>:: iterator it;

struct Edge{
    int from,to,next,flag;
}edge[M<<1];

void addEdge(int from,int to,int flag){
    edge[cnt]=(Edge){from,to,head[from],flag};
    head[from]=cnt++;
}

void dfs(int u,int fa){
    dfn[u]=low[u]=++clock;
    int v;
    for(int i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].to;
        if(!dfn[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v]){
                ans++;
                edge[i].flag=1;
                edge[i^1].flag=1;
            }
        }
        else if(v!=fa)
            low[u]=min(low[u],dfn[v]);
    }
}

string search_name(int x){
    for(it=mp.begin();it!=mp.end();it++){
        if(it->second == x) return it->first;
    }
}

int main(){
    int T,u,v,id=0;
    string str1,str2;
    scanf("%d",&T);
    while(T--){
        ans=id=clock=cnt=0;
        mp.clear();
        memset(head,-1,sizeof head);
        memset(dfn,0,sizeof(dfn));
        scanf("%d%d",&n,&m);
        while(m--){
            cin >> str1 >> str2;
            if(!mp.count(str1))
                mp[str1]=++id;
            if(!mp.count(str2))
                mp[str2]=++id;
            addEdge(mp[str1],mp[str2],0);
            addEdge(mp[str2],mp[str1],0);
        }
        int flag=0;
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                dfs(i,-1);
                flag++;
            }
        }
        if(flag!=1){
            cout << 0 << endl;
            continue;
        }
        cout << ans << endl;
        for(int i=0;i<cnt;i+=2){
            if(!edge[i].flag) continue;
            u=edge[i].from;
            v=edge[i].to;
            str1=search_name(u);
            str2=search_name(v);
            cout << str1 << " " << str2 << endl;
        }
    }
    return 0;
}
*/
