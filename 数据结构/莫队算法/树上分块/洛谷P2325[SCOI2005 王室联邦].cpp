#include <cstdio>

const int N=1e3+5,M=2e3+5;
int n,B,sz,cnt,tot,lnk[N],ter[M],nxt[M],st[N],rt[N],bel[N];

void add(int u,int v) {
	ter[++tot]=v,nxt[tot]=lnk[u],lnk[u]=tot;
}
//���dfsû̫������
void dfs(int u,int p) {
	int cnr=sz;
	for(int i=lnk[u];i;i=nxt[i]) {
		int v=ter[i];
		if(v==p) continue;
		dfs(v,u);
		if(sz-cnr>=B) {//u�������Ľڵ��������B
			rt[++cnt]=u;//���ʡ(���cnt)��ʡ���������ΪU��
			while(sz>cnr) bel[st[sz--]]=cnt;//�������ڵ���ж�����Ϊ���Ϊcnt��ʡ
		}
	}
	st[++sz]=u;//ʣ�಻��B�����Ľ�㶼���ظ���һ��
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
	while(sz) bel[st[sz--]]=cnt;//ʣ��Ľڵ㶼���ָ�cnt���ʡ,ʣ��������B,��������ʡ��������С��3*B������
	printf("%d\n",cnt);
	for(int i=1;i<=n;++i) printf("%d%c",bel[i]," \n"[i==n]);//���ÿ������������ʡ���
	for(int i=1;i<=cnt;++i) printf("%d%c",rt[i]," \n"[i==cnt]);//���ÿ��ʡ��ʡ����еı��
	return 0;
}
