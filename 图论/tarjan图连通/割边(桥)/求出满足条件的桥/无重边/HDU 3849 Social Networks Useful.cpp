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
����:n����֮�����m��˫���ϵ������(���ܲ���ͨ),�ؼ���ϵָ����
������ֹ�ϵ��ȡ�����ٴ���,���ǽ���Զʧȥ�������ĳЩ�˵�
��ϵ����,Ҳ���ǹ�ϵ����ᱻ�Ͽ�����ͨ.������е���Щ��ϵ�����������˳�����.
�������ظ���ϵ(�ر�),���Լ����Լ��Ĺ�ϵ(���Ի�).

����:�������ͼ�е������Ų���������˳���������.ע�����ԭͼ����ͨ�����,
�����ڹؼ���ϵ,��Ϊ����������ǶϿ���,���0.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3849
˼·:tarjan�����.����ת��Ϊ�����mp,������˳������ſ�������ʽǰ���Ǵ��,
���ʱ,��ת���߿����ڴ��ʱ������map��<string,int>mp1,<int,string>mp2��ת��.
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
            if(!mp1.count(str1)){//str1�Ѿ����ù���žͲ�������
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
        if(flag!=1){//���ԭͼ����ͨ ���0 �����ڹؼ���ϵ.
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
//һ��map<string,int> ���intת��stringʱ �õ���������,Ч�ʽϵ�,ÿ�ζ��ñ���һ��hash�� O(n^2)
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
