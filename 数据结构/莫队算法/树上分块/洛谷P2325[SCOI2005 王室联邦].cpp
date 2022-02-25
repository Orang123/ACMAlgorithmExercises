#include <cstdio>

const int N=1e3+5,M=2e3+5;
int n,B,sz,cnt,tot,lnk[N],ter[M],nxt[M],st[N],rt[N],bel[N];

void add(int u,int v) {
	ter[++tot]=v,nxt[tot]=lnk[u],lnk[u]=tot;
}
//这个dfs没太看明白
void dfs(int u,int p) {
	int cnr=sz;
	for(int i=lnk[u];i;i=nxt[i]) {
		int v=ter[i];
		if(v==p) continue;
		dfs(v,u);
		if(sz-cnr>=B) {//u点子树的节点个数大于B
			rt[++cnt]=u;//这个省(编号cnt)的省会城市设置为U点
			while(sz>cnr) bel[st[sz--]]=cnt;//将子树节点城市都划分为编号为cnt的省
		}
	}
	st[++sz]=u;//剩余不够B数量的结点都返回给上一层
}
int main() {
	scanf("%d%d",&n,&B);
	for(int i=1;i<n;++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs(1,0);
	if(!cnt) rt[++cnt]=1;
	while(sz) bel[st[sz--]]=cnt;//剩余的节点都划分给cnt这个省,剩余结点下雨B,满足题意省城市数量小于3*B的限制
	printf("%d\n",cnt);
	for(int i=1;i<=n;++i) printf("%d%c",bel[i]," \n"[i==n]);//输出每个城市所属的省编号
	for(int i=1;i<=cnt;++i) printf("%d%c",rt[i]," \n"[i==cnt]);//输出每个省的省会城市的编号
	return 0;
}
