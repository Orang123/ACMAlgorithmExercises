#include <bits/stdc++.h>
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define in inline
#define re register
//f[v]=now;now+=dep[v];这里分配内存没看明白
/*
此题n 10^6次方 正常dp开二维数组是一定开不出来的
长链剖分主要用来优化dp,化简 空间、时间,一般采用指针数组按需分配空间.
我们每个节点的状态直接继承其重儿子的节点状态(O(1))，同时将轻儿子的 DP 状态暴力合并.
*/

using namespace std;
typedef long long ll;
typedef double db;
in int read()
{
    int ans=0,f=1;char c=getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=-1;
    for (;isdigit(c);c=getchar()) ans=(ans<<3)+(ans<<1)+(c^48);
    return ans*f;
}
in int cmin(int &a,int b) {return a=min(a,b);}
in int cmax(int &a,int b) {return a=max(a,b);}
int n;
int buf[1000005];
int *f[1000005],*g[1000005],*now=buf;
int nex[2000005],head[1000005],tail[2000005],tot;
int ans[1000005];
void addedge(int u,int v)
{
    nex[++tot]=head[u];
    head[u]=tot;
    tail[tot]=v;
}
int dep[1000005],son[1000005];
void dfs1(int u,int fa) // 长链剖分
{
    for (int e=head[u];e;e=nex[e])
    {
        int v=tail[e];
        if (v==fa) continue;
        dfs1(v,u);
        if (dep[v]>dep[son[u]]) son[u]=v;
    }
    dep[u]=dep[son[u]]+1;
}
void dfs2(int u,int fa) //做dp
{
    f[u][0]=1;
    if (son[u])
    {
        f[son[u]]=f[u]+1; // 共享内存
        dfs2(son[u],u);
        ans[u]=ans[son[u]]+1; //从长孩子节点继承答案
    }
    for (int e=head[u];e;e=nex[e])
    {
        int v=tail[e];
        if (v==son[u] || v==fa) continue;
        f[v]=now;now+=dep[v]; // 分配内存
        dfs2(v,u);
        for (int i=1;i<=dep[v];i++)
        {
            f[u][i]+=f[v][i-1]; //暴力合并
            if (f[u][i]>f[u][ans[u]] || (f[u][i]==f[u][ans[u]] && i<ans[u])) ans[u]=i; //更新答案
        }
    }
    if (f[u][ans[u]]==1) ans[u]=0;
}
int main()
{
    n=read();
    for (int i=1;i<n;i++)
    {
        int u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0); // 长链剖分
    f[1]=now;now+=dep[1]; // 为根节点的答案分配内存
    dfs2(1,0);
    for (int i=1;i<=n;i++) cout<<ans[i]<<endl;
    return 0;
}

/*
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int gi(){
	int x=0,w=1;char ch=getchar();
	while ((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
	if (ch=='-') w=0,ch=getchar();
	while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return w?x:-x;
}
const int N = 1e6+5;
int n,to[N<<1],nxt[N<<1],head[N],cnt;
int len[N],son[N],tmp[N],*f[N],*id=tmp,ans[N];
void link(int u,int v){
	to[++cnt]=v;nxt[cnt]=head[u];head[u]=cnt;
	to[++cnt]=u;nxt[cnt]=head[v];head[v]=cnt;
}
void dfs(int u,int ff){
	for (int e=head[u];e;e=nxt[e])
		if (to[e]!=ff){
			dfs(to[e],u);
			if (len[to[e]]>len[son[u]]) son[u]=to[e];
		}
	len[u]=len[son[u]]+1;
}
void dp(int u,int ff){
	f[u][0]=1;
	if (son[u]) f[son[u]]=f[u]+1,dp(son[u],u),ans[u]=ans[son[u]]+1;
	for (int e=head[u];e;e=nxt[e]){
		int v=to[e];if (v==ff||v==son[u]) continue;
		f[v]=id;id+=len[v];dp(v,u);
		for (int j=1;j<=len[v];++j){
			f[u][j]+=f[v][j-1];
			if ((j<ans[u]&&f[u][j]>=f[u][ans[u]])||(j>ans[u]&&f[u][j]>f[u][ans[u]]))
				ans[u]=j;
		}
	}
	if (f[u][ans[u]]==1) ans[u]=0;
}
int main(){
	n=gi();
	for (int i=1;i<n;++i) link(gi(),gi());
	dfs(1,0);f[1]=id;id+=len[1];
	dp(1,0);
	for (int i=1;i<=n;++i) printf("%d\n",ans[i]);
	return 0;
}
*/
