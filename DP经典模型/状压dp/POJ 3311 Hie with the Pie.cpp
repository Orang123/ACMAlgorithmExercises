/*
����:ժ������
����һ����n��������n���ط������1��n��Ҫ�ӱ��Ϊ0�ĵط���ȥ���������е�
�ط�֮�����������̵�ʱ�䣬����(n+1)*(n+1)�ľ����ʾÿ����֮�䵽������Ҫ��ʱ�䡣
n<=10.
����:http://poj.org/problem?id=3311
˼·:״ѹdp.dp[u][sta]��������Ķ�����λ״̬Ϊsta���Ϊu�����ܷ���0�������ѵ����ʱ��
*/
//ac 0ms ���仯����
//ʱ�临�Ӷ�O(n^2*(1<<n))
//dp[u][sta]��������Ķ�����λ״̬Ϊsta���Ϊu�����ܷ���0�������ѵ����ʱ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define INF 0x3f3f3f3f
using namespace std;

int n,dp[N][1<<N],mp[N][N];

void floyd(){
    for(int k=0;k<=n;k++){
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++)
                mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);
        }
    }
}

int dfs(int u,int cur){
    if(dp[u][cur]!=-1)
        return dp[u][cur];
    if(!cur && !u)//�Ѿ�������n+1����,�����ܻص�0��� ���ǺϷ�״̬,����0
        return dp[u][cur]=0;
    dp[u][cur]=INF;
    for(int i=0;i<n;i++){
        if(cur & 1<<i)
            dp[u][cur]=min(dp[u][cur],dfs(i,cur ^ 1<<i)+mp[u][i]);
    }
    return dp[u][cur];
}


int main(){
    while(scanf("%d",&n) && n){
        memset(dp,-1,sizeof(dp));
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        floyd();
        n++;//�����0Ҳ���ȥ,���Զ�����״̬�е�ĸ���Ϊn+1
        printf("%d\n",dfs(0,(1<<n)-1));//�����������0��ʼ,���������뵱ǰ������״̬
    }
    return 0;
}

/*
//ac 0ms ����
//��ȼ��仯����,������Ƶ�����,������Ҫ����ļ��ɵ�.
//ժ�Բ���;https://blog.csdn.net/m0_46082460/article/details/115916192
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 5;

int n;
int G[505][505];
int dp[1<<15][20];

void floyd(){
	for(int k = 0;k < n;k++){
		for(int i = 0;i < n;i++){
			for(int j = 0;j < n;j++){
				G[i][j] = min(G[i][j],G[i][k]+G[k][j]);
			}
		}
	}
}

int main(){
	while(~scanf("%d",&n)){
		if(n == 0) break;
		memset(G,0x3f3f3f3f,sizeof(G));
		for(int i = 0;i <= n;i++){
			for(int j = 0;j <= n;j++){
				scanf("%d",&G[i][j]);
			}
		}
		n++;
		for(int i = 0;i <=(1<<n);i++)
			memset(dp[i],0x3f3f3f3f,sizeof(dp[i]));
		floyd();
		dp[(1<<n)-1][0] = 0;
		for(int S = (1<<n)-2;S >= 0;S--){
			for(int v = 0;v < n;v++){
				for(int u = 0;u < n;u++){
					if((S&(1 << u)) == 0){
						dp[S][v] = min(dp[S][v],dp[S|(1<<u)][u]+G[v][u]);
					}
				}
			}
		}
		printf("%d\n",dp[0][0]);
	}
	return 0;
}
*/
