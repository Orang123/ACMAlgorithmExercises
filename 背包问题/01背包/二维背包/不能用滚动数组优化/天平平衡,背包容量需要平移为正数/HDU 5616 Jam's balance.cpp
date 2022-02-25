#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define M 4100
using namespace std;
//ac 0ms ��ά�������� ����ɷ�������������,��Ҫ��ȫ������ȥ
//dp[i][j-w[i]]=dp[i-1][j]
//dp[i][j+w[i]]=dp[i-1][j]
/*
����:n������,ÿ��������һ������w[i],ÿ��������Է���
��ƽ�������Ҳ�,�����ƽֻ�ܱ����ƽ�������Ʒ������
�Ƿ����,�����������ƽ�ܷ�������Ϊv����Ʒ������.
˵��:����ʱʵ����ƽ���඼����������,Ҳ������Ʒ���Ժ�
�������ͬһ��.���Ҳ������������붼Ҫ����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=5616
˼·:01����,sum���������������͵�2��.
���ֻ���ж�dp[n][sum/2+v]��dp[n][sum/2-v]�Ƿ�Ϸ�.
���Ϸ���������״̬��,����ƽĳһ�������Ʒ,����
�������+��Ʒ=�Ҳ����� ���������=�Ҳ�����+��Ʒ,
��Ʒ�����Ϳɵ�֪.
*/
//dp[i][j]=1��ʾǰi�����������ƽ�ϵõ�������Ϊ|j-sum/2|��������Ǵ��ڵ�
int n,m,w[N],dp[N][M],sum;

int main(){
    int T,v;
    scanf("%d",&T);
    while(T--){
        sum=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        sum*=2;
        memset(dp,-1,sizeof(dp));
        dp[0][sum/2]=1;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=sum;j++)
                dp[i][j]=dp[i-1][j];
            for(int j=0;j<=sum;j++){
                if(dp[i-1][j] == -1) continue;
                dp[i][j-w[i]]=dp[i-1][j];
                dp[i][j+w[i]]=dp[i-1][j];
            }
        }
        scanf("%d",&m);
        while(m--){
            scanf("%d",&v);
            if(dp[n][sum/2+v] == 1 || dp[n][sum/2-v] == 1)
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    return 0;
}

/*
//ac 0ms һά��������
//dp[j+w[i]]=dp[j]
//dp[j-w[i]]=dp[j]
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define M 4100
using namespace std;

int n,m,w[N],dp[M],vis[M],sum;

int main(){
    int T,v;
    scanf("%d",&T);
    while(T--){
        sum=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        sum*=2;
        memset(dp,-1,sizeof(dp));
        dp[sum/2]=1;
        for(int i=1;i<=n;i++){
            //��i���׶ε�dp[j]��ʾǰi�����������ƽ�ϵõ�������Ϊ|j-sum/2|��������Ǵ��ڵ�
            memset(vis,0,sizeof(vis));
            for(int j=0;j<=sum;j++){
                if(dp[j] == -1) continue;
                vis[j-w[i]]=1;
                vis[j+w[i]]=1;
            }
            for(int j=0;j<=sum;j++)
                if(vis[j])
                    dp[j]=1;
        }
        scanf("%d",&m);
        while(m--){
            scanf("%d",&v);
            if(dp[sum/2+v] == 1 || dp[sum/2-v] == 1)
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    return 0;
}
*/

/*
//ac 0ms ��һ��ת��
//dp[j]=dp[j-w[i]]
//dp[j]=dp[j+w[i]]
//��֪��Ϊɶ��������ж�dp[j-w[i]]�ǺϷ���
//ֱ��vis[j]=dp[j-w[i]]��wa
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define M 4100
using namespace std;

int n,m,w[N],dp[M],vis[M],sum;

int main(){
    int T,v;
    scanf("%d",&T);
    while(T--){
        sum=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        sum*=2;
        memset(dp,0,sizeof(dp));
        dp[sum/2]=1;
        for(int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            for(int j=0;j<=sum;j++){
            	if(j-w[i]>=0){
                    //��֪��Ϊɶ��������ж�dp[j-w[i]]�ǺϷ���
                    //ֱ��vis[j]=dp[j-w[i]]��wa
            		if(dp[j-w[i]]==1)
            			vis[j]=1;
				}
            	if(j+w[i]<=sum){
            		if(dp[j+w[i]]==1)
            			vis[j]=1;
				}
            }
            for(int j=0;j<=sum;j++){
            	if(vis[j])
                    dp[j]=1;
			}
        }
        scanf("%d",&m);
        while(m--){
            scanf("%d",&v);
            if(dp[sum/2+v] == 1 || dp[sum/2-v] == 1)
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    return 0;
}
*/

/*
//TLE ����ö������ O(3^n)
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 25
#define M 2100
using namespace std;

int n,m,w[N],sum,vis[M][M];

void dfs(int k,int l,int r){
    vis[l][r]=1;
    if(k == n+1)
        return;
    dfs(k+1,l+w[k],r);//��i������������
    dfs(k+1,l,r+w[k]);//��i����������Ҳ�
    dfs(k+1,l,r);//���ŵ�i������
}

int main(){
    int T,v;
    scanf("%d",&T);
    while(T--){
        sum=0;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        dfs(1,0,0);
        scanf("%d",&m);
        while(m--){
            scanf("%d",&v);
            int flag=0;
            for(int l=0;l<=sum;l++){
                for(int r=0;r<=sum;r++){
                    if(vis[l][r] && (l+v==r || l==r+v)){
                        flag=1;
                        break;
                    }
                }
                if(flag) break;
            }
            if(flag)
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    return 0;
}
*/
