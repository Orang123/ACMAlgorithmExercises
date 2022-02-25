/*
����:��[1,1]������[n,n],ÿ���ߵĲ����ǵ�ǰ�����е�����,ֻ�ܳ��һ�������������,
�ʿ����ߵ��յ�ķ������Ƕ���.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1208
˼·:���仯����
dp[x][y]��ʾ��(x,y)��������(n,n)ʱ�ķ�������
*/
//ac 0ms ���仯����
//dp[x][y]��ʾ��(x,y)��������(n,n)ʱ�ķ�������
#include<cstring>
#include<algorithm>
#define N 40
typedef long long ll;
using namespace std;

int n,dir[2][2]={{1,0},{0,1}};
ll dp[N][N];
char mp[N][N];

ll dfs(int x,int y){
    if(dp[x][y]!=-1)
        return dp[x][y];
    if(mp[x][y] == '0')//�����ֻ�ܴ���ԭ�� ������չ,����������ѭ��
        return 0;
    int nx,ny,k=mp[x][y]-'0';
    ll res=0;
    for(int i=0;i<2;i++){
        nx=x+dir[i][0]*k;
        ny=y+dir[i][1]*k;
        if(nx<1 || nx>n || ny<1 || ny>n)
            continue;
        res+=dfs(nx,ny);
    }
    return dp[x][y]=res;
}

int main(){
    while(scanf("%d",&n) && n!=-1){
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&mp[i][j]);
        }
        dp[n][n]=1;
        printf("%lld\n",dfs(1,1));
    }
    return 0;
}

/*
//ac 0ms ����dp
//dp[x][y]��ʾ��(1,1)��������(x,y)ʱ�ķ�������
#include<cstring>
#include<algorithm>
#define N 40
typedef long long ll;
using namespace std;

int n,dir[2][2]={{1,0},{0,1}};
ll dp[N][N];
char mp[N][N];

int main(){
    while(scanf("%d",&n) && n!=-1){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf(" %c",&mp[i][j]);
        }
        dp[1][1]=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                int nx,ny;
                if(mp[i][j] == '0')
                    continue;
                for(int k=0;k<2;k++){
                    nx=i+dir[k][0]*(mp[i][j]-'0');
                    ny=j+dir[k][1]*(mp[i][j]-'0');
                    if(nx<1 || nx>n || ny<1 || ny>n)
                        continue;
                    dp[nx][ny]+=dp[i][j];
                }
            }
        }
        printf("%lld\n",dp[n][n]);
    }
    return 0;
}
*/
