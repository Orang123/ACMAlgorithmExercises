#include<iostream>
#include<cstdio>
#include<vector>
#define N 500005
//预处理st表 没用到dep 感觉思维有问题
using namespace std;
int read(){
    char c=getchar(); int x=0;
    while(c<'0'||c>'9') c=getchar();
    while('0'<=c&&c<='9') x=x*10+c-48,c=getchar();
    return x;
}
int n,m,s,u,v,f[20][N<<1],dfn[N],cc,Log[N<<1];
vector <int> g[N];
void dfs(int x,int fa){
    f[0][dfn[x]=++cc]=x;
    for(int i:g[x]) if(i!=fa) dfs(i,x),f[0][++cc]=x;
}
inline int Min(int x,int y){return dfn[x]<dfn[y]?x:y;}
int ask(int x,int y){
    int l=dfn[x],r=dfn[y]; if(l>r)swap(l,r);
    int k=Log[r-l+1];
    return Min(f[k][l],f[k][r-(1<<k)+1]);
}
int main(){
    n=read(); m=read(); s=read(); Log[0]=-1;
    for(int i=1;i<n;++i){
        u=read(); v=read();
        g[u].push_back(v);
        g[v].push_back(u);
    }dfs(s,0);
    for(int i=1;i<=cc;++i) Log[i]=Log[i>>1]+1;
    for(int i=1;i<=Log[cc];++i)
        for(int j=1;j+(1<<i)-1<=cc;++j)//预处理st表 没用到dep 感觉思维有问题
            f[i][j]=Min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
    while(m--) printf("%d\n",ask(read(),read()));
    return 0;
}
