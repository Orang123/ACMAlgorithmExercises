#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
const int N=200100;
/*
��������ѣ�
C[u]��װ���ǵ������u���������е㵽�������u�ĸ��׵ľ��롣
B[u]��װ���ǵ������u�����ж��ӵ�C�����ֵ��
A��װ��������BB�����ֵ��δ�ֵ֮�͡�
A�ĶѶ����Ǵ𰸡�
����һ��ʼһֱ��Ϊ�����Ѿ��У��Ե������Ա�ʾ�ɻ������������룬һֱ����⡣ǧ���ܷ������밡��
�����Ҵ𰸿��Կ����ҵ�����������ôά����
��Ϊ�����ǵ���������С������ֱ��һ��һ�������������޸�ά��������һЩ������ɾ�ĵ�Ϊxx������һ����uu��xx�Ĺ��״�C[u]��ɾ����Ȼ�����¸���B[u]��A��
���˱���õ�����������Ҵ��볣��̫��
*/
struct que{
    priority_queue<int> x,y;
    inline void push(int a){x.push(a);}
    inline void del(int a){y.push(a);}
    //��ȡ���ֵʱ, �� ����� �� ɾ���� �� �Ѷ�Ԫ����ͬ, ����ζ�����Ԫ���Ѿ���ɾ����, ������˫˫����.
    inline int top(){while(y.size()&&x.top()==y.top())x.pop(),y.pop();return x.top();}
    inline int size(){return x.size()-y.size();}
    inline void pop(){while(y.size()&&x.top()==y.top())x.pop(),y.pop();x.pop();}
    inline int sectop(){int a=top();pop();int b=top();push(a);return b;}
}A,B[N],C[N];
int cnt,head[N];
int light[N],tot,n,m;
int root,size[N],g[N],vis[N],all,f[N];
int dep[N],mn[N*2][24],num,dfn[N];
int Log[N];
struct edge{
    int to,nxt;
}e[N*2];
inline void add_edge(int u,int v){
    cnt++;
    e[cnt].nxt=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}
inline void dfs(int u,int f){
    dfn[u]=++num;
    dep[u]=dep[f]+1;
    mn[num][0]=dep[u];
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==f)continue;
        dfs(v,u);
        mn[++num][0]=dep[u];
    }
}
inline void getroot(int u,int f){
    g[u]=0;size[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==f||vis[v])continue;
        getroot(v,u);
        g[u]=max(g[u],size[v]);
        size[u]+=size[v];
    }
    g[u]=max(g[u],all-size[u]);
    if(g[u]<g[root])root=u;
}
inline int getdep(int x,int y){
    int a=dfn[x];
    int b=dfn[y];
    if(a>b)swap(a,b);
    int len=Log[b-a+1];
    return min(mn[a][len],mn[b-(1<<len)+1][len]);
}
inline int dis(int x,int y){
    return dep[x]+dep[y]-2*getdep(x,y);
}
inline void work(int u,int ff){
    C[root].push(dis(u,f[root]));
    size[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==ff||vis[v])continue;
        work(v,u);
        size[u]+=size[v];
    }
}
inline void pusha(int x){
    if(B[x].size()>=2)A.push(B[x].top()+B[x].sectop());
}
inline void dela(int x){
    if(B[x].size()>=2)A.del(B[x].top()+B[x].sectop());
}
inline void build(int u,int ff){
    f[u]=ff;vis[u]=1;
    B[u].push(0);
    work(u,0);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(vis[v])continue;
        root=0,all=size[v];
        getroot(v,0);
        v=root;
        build(root,u);
        B[u].push(C[v].top());
    }
    pusha(u);
}
inline void on(int x){
    dela(x);
    B[x].del(0);
    pusha(x);
    for(int i=x;f[i];i=f[i]){
        dela(f[i]);
        B[f[i]].del(C[i].top());
        C[i].del(dis(x,f[i]));
        if(C[i].size())B[f[i]].push(C[i].top());
        pusha(f[i]);
    }
}
inline void off(int x){
    dela(x);
    B[x].push(0);
    pusha(x);
    for(int i=x;f[i];i=f[i]){
        dela(f[i]);
        if(C[i].size())B[f[i]].del(C[i].top());
        C[i].push(dis(x,f[i]));
        B[f[i]].push(C[i].top());
        pusha(f[i]);
    }
}
void prework(){
    for(int j=1;j<=Log[num];j++)
        for(int i=1;i+(1<<j)-1<=num;i++)
            mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
}
inline int read(){
    int sum=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){sum=sum*10+ch-'0';ch=getchar();}
    return sum*f;
}
int main(){
    n=read();
    Log[0]=-1;for(int i=1;i<=200000;i++)Log[i]=Log[i>>1]+1;
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add_edge(u,v);add_edge(v,u);
    }
    dfs(1,0);
    prework();
    g[0]=n;root=0;all=n;
    getroot(1,0);build(root,0);
    tot=n;
    m=read();
    char s;
    while(m--){
        s=getchar();
        if(s=='G'){
            if(tot<=1)printf("%d\n",tot-1);
            else printf("%d\n",A.top());
        }
        else{
            int x=read();
            if(light[x]==0)on(x),tot--;
            else off(x),tot++;
            light[x]^=1;
        }
    }
    return 0;
}
