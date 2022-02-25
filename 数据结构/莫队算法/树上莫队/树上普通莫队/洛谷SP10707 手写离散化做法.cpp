#include<bits/stdc++.h>
using namespace std;
const int maxn=40005,maxm=100005;
int block;
struct Query{
	int id;
	int x,y,z;
	bool operator <(Query i)const{
		return x/block==i.x/block?y<i.y:x<i.x;
	}
}q[maxm];
struct node{
	int id,data;
	bool operator <(node i)const{
		return data<i.data;
	}
}a[maxn];
struct Edge{
	int to;
	int nxt;
}e[2*maxn];
int cnt;
int head[maxn];
int c[maxn];
int dep[maxn],f[maxn][21];
int tp=0;
int s[2*maxn],st[maxn],ed[maxn];
int tot[maxn];
int ans=0;
int ANS[maxm];
bool vis[maxn];
int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*y;
}
void add(int u,int v){
	e[cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt++;
	return ;
}
void dfs(int x,int fa){
	s[++tp]=x;
	st[x]=tp;
	dep[x]=dep[fa]+1;
	f[x][0]=fa;
	for(int i=1;i<=20;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	for(int i=head[x];i!=-1;i=e[i].nxt){
		int tmp=e[i].to;
		if(tmp==fa)continue;
		dfs(tmp,x);
	}
	s[++tp]=x;
	ed[x]=tp;
	return ;
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=20;i>=0;i--)
		if(dep[f[x][i]]>=dep[y])
			x=f[x][i];
	if(x==y)return x;
	for(int i=20;i>=0;i--)
		if(f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	return f[x][0];
}
void modify(int x){
	vis[s[x]]^=1;
	if(!vis[s[x]]){
		tot[c[s[x]]]--;
		if(tot[c[s[x]]]==0)ans--;
	}
	else{
		tot[c[s[x]]]++;
		if(tot[c[s[x]]]==1)ans++;
	}
	return ;
}
int main(){
	int n,m;
	n=read();m=read();
	block=sqrt(2*n);
	for(int i=1;i<=n;i++){
		a[i].id=i;
		a[i].data=read();
	}
	//ÊÖÐ´ÀëÉ¢»¯
	sort(a+1,a+n+1);
	int w=0;
	for(int i=1;i<=n;i++){
		if(a[i].data>a[i-1].data)w++;
		c[a[i].id]=w;
	}
	memset(head,-1,sizeof(head));
	for(int i=1;i<n;i++){
		int u,v;
		u=read();v=read();
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=m;i++){
		int u,v;
		u=read();v=read();
		int p=lca(u,v);
		q[i].id=i;q[i].z=0;
		if(p==u||p==v){
			if(st[v]<st[u])swap(u,v);
			q[i].x=st[u];q[i].y=st[v];
		}
		else{
			if(ed[v]<st[u])swap(u,v);
			q[i].x=ed[u];q[i].y=st[v];q[i].z=p;
		}
	}
	sort(q+1,q+m+1);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		int id=q[i].id,x=q[i].x,y=q[i].y,z=q[i].z;
		while(l<x)modify(l++);
		while(l>x)modify(--l);
		while(r<y)modify(++r);
		while(r>y)modify(r--);
		if(z)modify(st[z]);
		ANS[id]=ans;
		if(z)modify(st[z]);
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ANS[i]);
	return 0;
}
