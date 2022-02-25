/*
题意:摘自网上
给出一个n×n的矩阵mp，mp[i][j]表示第i个点和第j个点的流量，
要求将这n个点分为两个集合A和B，定义sum为 集合A中各点到集合
B中各点的流量和，求最大的sum。
n<=20.
链接:http://poj.org/problem?id=2531
思路:枚举每个点留在A集合还是B集合,vis[i]=1表示 i点留在A集合,
vis[i]=0表示i点留在B集合.可以实时更新流量和,一个剪枝是如果i
点分在A集合后,当前流量和减少了,就说明这个决策较差,不在搜索下去,
转而还是将i放置在B集合.
*/
//ac 94ms dfs回溯+剪枝
//不剪枝 250ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 21
using namespace std;

int n,mp[N][N],vis[N],ans;

void dfs(int k,int sum){
    if(k == n+1){
        if(sum>ans)
            ans=sum;
        return;
    }
    int tp=sum;
    vis[k]=1;
    for(int i=1;i<=n;i++){
        if(i!=k && vis[i])//i点本身就在A集合 和k点在同一集合,需要将之前的两点间流量减掉,因为已经在同一集合了
            tp-=mp[k][i];
        else//k i在不同集合
            tp+=mp[k][i];
    }
    if(tp>sum)//剪枝:当k点放在A集合 流量和减少了,就不把k点放在A集合,转而还是放在原先的B集合
        dfs(k+1,tp);//k点放在A集合
    vis[k]=0;
    dfs(k+1,sum);
}

int main(){
    ans=0;
    memset(vis,0,sizeof(vis));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            scanf("%d",&mp[i][j]);
    }
    dfs(1,0);
    printf("%d",ans);
    return 0;
}

/*
//TLE dfs+回溯 不剪枝 可能是因为k == n+1时 要跑两层循环的O(n^2)
//复杂度O(2^20=10^6*400)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 21
using namespace std;

int n,mp[N][N],vis[N],ans;

void dfs(int k){
    if(k == n+1){
        int sum=0;
        for(int i=1;i<=n;i++){
        	for(int j=i+1;j<=n;j++){
        		if(vis[i] != vis[j])
        			sum+=mp[i][j];
			}
		}
		if(sum>ans)
            ans=sum;
        return;
    }
    vis[k]=1;
    dfs(k+1);//k点放在A集合
    vis[k]=0;
    dfs(k+1);
}

int main(){
    ans=0;
    memset(vis,0,sizeof(vis));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            scanf("%d",&mp[i][j]);
    }
    dfs(1);
    printf("%d",ans);
    return 0;
}
*/
