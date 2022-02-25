/*
����:ժ������
��һ����С��N�����75���ķ���Ҫ��ӣ�1��1���ߵ���n,n����
�����¹�����ֻ�������������ҡ��¡������߳�����һ��
����ֻ����һ�Ρ���Ҫ��֤���·���ϵĸ��ӵĺ���������ֻ
����k(���Ϊ5)����Ȩֵ�ĸ��ӣ�����㵽�յ㡣����ɴ�������ĺͣ�
������ɴ������impossible����
n<=75,k<=5.
����:https://www.luogu.com.cn/problem/UVA10913
˼·:�������������Ĺ����л�����ص�·��,�����Ҫ���仯����.ֻ��
���仯������(x,y)������״̬�ı�ʾ��Ҫ���Ƕ������������,��һ����
�ߵ���ǰ���ӻ�ʣ�����ߵĸ�����������Ŀ,�����ߵ���ǰ(x,y)��ķ���,
�ߵ�(x,y)��ĸ�������ͬ��Ӱ�������·����ѡȡ,�ߵ�(x,y)�㷽��ͬ,
��Ϊһ��һ���ǲ��������ߵ�,���Ҳ��Ӱ������ֵ��ѡȡ.

���dp[x][y][d][s]��ʾ��ʣ��s�����ߵĸ���������,��d���򵽴�(x,y),��
(x,y)�ߵ�(n,n)���ܻ�õ����Ȩֵ��.ע��dp��Ȩֵ��INFҲ��һ���Ϸ�״̬,
����,��Ҫ��״̬�Ƚ϶������һ��vis[x][y][d][s]����,�����TLE.
��Ҫע����ǳ�����(1,1)�п���Ҳ�Ǹ�����,�����Ҫ�����ж�,��ʼ��k�Ƿ�Ҫ��һ.
*/
//ac 0ms ���仯����,vis���鵥�����
//dp[x][y][d][s]��ʾ��ʣ��s�����ߵĸ���������,��d���򵽴�(x,y),��
//(x,y)�ߵ�(n,n)���ܻ�õ����Ȩֵ��.
//ʱ�临�Ӷ�O(75*75*5*3)=84375
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 80
#define INF -0x3f3f3f3f
using namespace std;

int n,k,mp[N][N],dp[N][N][3][6],vis[N][N][3][6],dir[3][2]={{0,-1},{0,1},{1,0}};

int dfs(int x,int y,int d,int s){
    if(vis[x][y][d][s])
        return dp[x][y][d][s];
    if(x == n && y == n)
        return dp[n][n][d][s]=mp[n][n];
    int nx,ny,res;
    for(int i=0;i<3;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>n || ny<1 || ny>n)
            continue;
        if((d==0 && i==1) || (d==1 && i ==0))//����������,һ�����������һ��
            continue;
        if(mp[nx][ny]<0){
            if(s>=1)//���������� s������Ϊ1
                res=dfs(nx,ny,i,s-1);
            else
                continue;
        }
        else
            res=dfs(nx,ny,i,s);
        if(res!=INF)//���Ϸ�ֱ�ӱ��ΪINF,�����ۼ�,��������ж�
            dp[x][y][d][s]=max(dp[x][y][d][s],res+mp[x][y]);
    }
    vis[x][y][d][s]=1;//��ǵ�ǰ״̬��������
    return dp[x][y][d][s];
}

int main(){
    int cas=0;
    while(scanf("%d%d",&n,&k) && n+k){
        cas++;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                for(int t=0;t<=k;t++)
                    dp[i][j][0][t]=dp[i][j][1][t]=dp[i][j][2][t]=INF;
        }
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        if(mp[1][1]<0)//�������п��� ���Ǹ�����,���k��һ
            k--;
        dfs(1,1,2,k);//��ʼ���� Ҫ����(2),�����Ӱ��������������ѡȡ
        if(dp[1][1][2][k]!=INF)
            printf("Case %d: %d\n",cas,dp[1][1][2][k]);
        else
            printf("Case %d: impossible\n",cas);
    }
    return 0;
}

/*
//ac 10ms ���仯����,���ڲ��ɴ��״̬����ΪINF-1,����vis����
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define N 80
#define INF -0x3f3f3f3f
using namespace std;

int n,k,mp[N][N],dp[N][N][3][6],dir[3][2]={{0,-1},{0,1},{1,0}};

int dfs(int x,int y,int d,int s){
    if(dp[x][y][d][s]!=INF)
        return dp[x][y][d][s];
    if(x == n && y == n)
        return dp[n][n][d][s]=mp[n][n];
    int nx,ny,res;
    for(int i=0;i<3;i++){
        nx=x+dir[i][0];
        ny=y+dir[i][1];
        if(nx>n || ny<1 || ny>n)
            continue;
        if((d==0 && i==1) || (d==1 && i ==0))
            continue;
        if(mp[nx][ny]<0){
            if(s>=1)
                res=dfs(nx,ny,i,s-1);
            else
                continue;
        }
        else
            res=dfs(nx,ny,i,s);
        if(res!=INF-1)
            dp[x][y][d][s]=max(dp[x][y][d][s],res+mp[x][y]);
    }
    if(dp[x][y][d][s] == INF)
    	dp[x][y][d][s]=INF-1;
    return dp[x][y][d][s];
}

int main(){
    int cas=0;
    while(scanf("%d%d",&n,&k) && n+k){
        cas++;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                for(int t=0;t<=k;t++)
                    dp[i][j][0][t]=dp[i][j][1][t]=dp[i][j][2][t]=INF;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&mp[i][j]);
        }
        if(mp[1][1]<0)
            k--;
        dfs(1,1,2,k);
        if(dp[1][1][2][k]!=INF-1)
            printf("Case %d: %d\n",cas,dp[1][1][2][k]);
        else
            printf("Case %d: impossible\n",cas);
    }
    return 0;
}
*/
