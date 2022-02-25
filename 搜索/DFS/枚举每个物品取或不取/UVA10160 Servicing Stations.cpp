/*
题意:摘自网上
给你一个无向图，有n个结点,m个边,现在要在n个点处建立服务站，
服务站可以覆盖与它链接的点(包括建造点自身)，问最少需要几个
服务站可以覆盖所有结点。
n<=35.
链接:https://www.luogu.com.cn/problem/UVA10160
思路:枚举每个点是否放置服务站,关于点的覆盖采取计数的方式,
当覆盖的点的数目到达n个时,就记录建造服务站最少的个数.
2个剪枝:
剪枝1:当当前所建造服务站数目不小于之前记录的服务站数目时返回.
剪枝2:当前所选定建造服务站的点u前面若还有未覆盖的点i,并且i点
邻接的点的最大编号都比u小,则i点再也不可能被覆盖,即:当前方案
不可能覆盖所有节点,返回.
*/
//ac 1.05s
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
#define INF 0x3f3f3f3f
using namespace std;

int n,m,mp[N][N],vis[N],maxv[N],ans;

//sum为当前覆盖点的个数,num为在几个点建造服务站的数目
void dfs(int u,int sum,int num){
    if(num>=ans)//建造服务站的数目 不小于之前的最小值 返回
        return;
    if(sum == n && num<ans){//覆盖点的数目到达n个 记录答案
        ans=num;
        return;
    }
    if(u == n+1)
        return;
    //若之前点存在未覆盖的点i,并且i的邻接点的最大编号比u还小,
    //则u包括u+1..u+2后面的点也更不可能和i点邻接,即i点不可能被覆盖,当前方案无法覆盖全部点,结束.
    for(int i=1;i<u;i++){
        if(!vis[i] && maxv[i]<u)
            return;
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(mp[u][i] && !vis[i])//只有i点还未覆盖才记录 新覆盖点的个数
            cnt++;
        //当当前i点邻接时,vis[i]++,这里累加是为了方便回溯时,vis[i]-- 不影响vis[i]不为0的判定,
        //因为除了当前点u覆盖i外,还可能有别的点覆盖点i
        if(mp[u][i])
            vis[i]++;
    }
    if(cnt)//在u点建造服务站的前提条件是新覆盖点个数不为0,只有这样num才能保证最少
        dfs(u+1,sum+cnt,num+1);
    for(int i=1;i<=n;i++){
        if(mp[u][i])
            vis[i]--;
    }
    //不在u点建造服务站
    dfs(u+1,sum,num);//这里有可能 新覆盖点的个数本身就为0,也有可能新覆盖点个数不为0
}

int main(){
    int u,v;
    while(scanf("%d%d",&n,&m) && n+m){
        ans=INF;
        memset(vis,0,sizeof(vis));
        memset(mp,0,sizeof(mp));
        for(int i=1;i<=n;i++)
            mp[i][i]=1;//每个点在i点建造服务站,能覆盖自身点
        while(m--){
            scanf("%d%d",&u,&v);
            mp[u][v]=mp[v][u]=1;
        }
        for(int i=1;i<=n;i++){
            maxv[i]=-1;
            for(int j=1;j<=n;j++){
                if(mp[i][j])
                    maxv[i]=max(maxv[i],j);//maxv[i]记录i点本身 邻接的最大的点的编号
            }
        }
        dfs(1,0,0);
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 490ms 不采用邻接矩阵,采用邻接表,不用判断u点未邻接的点
//摘自博客:https://blog.csdn.net/HelloWorld10086/article/details/38659641
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 36;
int n,m;
int edge[N][N];
int vis[N];
int s[N];
int ans;

void dfs(int u,int sum,int cur) {
	if(cur == n && sum < ans) {
		ans = sum;
		return;
	}
	if(u > n || sum >= ans) {
		return;
	}
	for(int i = 1; i < u; i++) {
		if( !vis[i] && edge[i][s[i]-1] < u) {
			return ;
		}
	}
	int cnt = 0;
	for(int i = 0; i < s[u]; i++) {
		if( !vis[edge[u][i]] ) {
			cnt++;
		}
		vis[edge[u][i]]++;
	}
	if(cnt) {
		dfs(u+1,sum+1,cur+cnt);
	}
	for(int i = 0; i < s[u]; i++) {
		vis[edge[u][i]]--;
	}
	dfs(u+1,sum,cur);
}
int main() {
	int u,v;
	while(scanf("%d%d",&n,&m) != EOF && (n || m)) {
		memset(edge,0,sizeof(edge));
		memset(s,0,sizeof(s));
		memset(vis,0,sizeof(vis));

		for(int i = 0; i < m; i++) {
			scanf("%d%d",&u,&v);
			edge[u][s[u]++] = v;
			edge[v][s[v]++] = u;
		}
		for(int i = 1; i <= n; i++) {
			edge[i][s[i]++] = i;
			sort(edge[i],edge[i]+s[i]);
		}
		ans = n;
		dfs(1,0,0);
		printf("%d\n",ans);
	}
	return 0;
}
*/
