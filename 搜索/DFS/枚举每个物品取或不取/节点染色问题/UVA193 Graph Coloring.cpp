/*
题意:请您编写一个程序找到一个给定图的最优染色方案。染色是指对图上的点染色，
并且只有黑白二色可用。最优染色方案要求染成黑色的点最多。染色限制：
禁止由一条边相连的两个点都染黑色。
点的个数<=100.
链接:https://www.luogu.com.cn/problem/UVA193
思路:线性递增枚举每个点染黑色或白色,对于染黑色必须保证与当前点相连的点
的颜色没有一个是染成黑色的.最坏情形的复杂度为2^100,实际因为不能有
黑色黑色的情况,所以复杂度没有这么大.

注意:不能按照图的边连通顺序 遍历整张图,因为实际染成黑色的点的数目与点的遍历
顺序无关,之和每个点染成黑色还是白色这两种情况有关,如果遍历整张图,将访问点的
顺序也作为一种可能去考虑,这样就会过多地回溯,复杂度就过大,就会TLE.
*/
//ac 10ms 线性递增枚举点
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,m,mp[N][N],col[N],ans,vis[N];

void dfs(int u,int num){
    if(u == n+1){
        if(num>ans){
            ans=num;
            memcpy(vis,col,sizeof(col));
        }
        return;
    }
    int flag=0;
    for(int i=1;i<=n;i++){
        if(mp[u][i] && col[i]){//判断和u点邻接的点 是否有染黑色,如果有染黑色 就不能再染黑色,只能染白色
            flag=1;
            break;
        }
    }
    if(!flag){
        col[u]=1;
        dfs(u+1,num+1);
        col[u]=0;
    }
    dfs(u+1,num);
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        ans=0;
        memset(mp,0,sizeof(mp));
        scanf("%d%d",&n,&m);
        while(m--){
            scanf("%d%d",&u,&v);
            mp[u][v]=mp[v][u]=1;
        }
        dfs(1,0);
        printf("%d\n",ans);
        int flag=0;
        for(int i=1;i<=n;i++){
            if(vis[i]){
                if(!flag){
                    printf("%d",i);
                    flag=1;
                }
                else
                    printf(" %d",i);
            }
        }
        printf("\n");
    }
    return 0;
}

/*
//TLE
//不能按照图的边连通顺序 遍历整张图,因为实际染成黑色的点的数目与点的遍历
//顺序无关,之和每个点染成黑色还是白色这两种情况有关,如果遍历整张图,将访问点的
//顺序也作为一种可能去考虑,这样就会过多地回溯,复杂度就过大,就会TLE.
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 110
using namespace std;

int n,m,col[N],ans,vis[N],b[N];
vector<int> G[N];

void dfs(int u,int num,int k){
    if(k == n){
        if(num>ans){
            ans=num;
            int j=0;
            for(int i=1;i<=n;i++){
            	if(col[i])
            		b[++j]=i;
			}
        }
        return;
    }
    vis[u]=1;
    for(int &v : G[u]){
    	if(vis[v]) continue;
    	int flag=0;
    	for(int &tp : G[v]){
    		if(vis[tp] && col[tp]){
    			flag=1;
    			break;
			}
		}
		if(!flag){
			col[v]=1;
			dfs(v,num+1,k+1);
			col[v]=0;
		}
		dfs(v,num,k+1);
	}
	vis[u]=0;
}

int main(){
    int T,u,v;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
        	G[i].clear();
        while(m--){
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        col[1]=1;
        dfs(1,1,1);
        col[1]=0;
        dfs(1,0,1);
        printf("%d\n",ans);
        int flag=0;
        for(int i=1;i<=ans;i++){
            if(!flag){
                printf("%d",b[i]);
                flag=1;
            }
            else
                printf(" %d",b[i]);
        }
        printf("\n");
    }
    return 0;
}
*/
