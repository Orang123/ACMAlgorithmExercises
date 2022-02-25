/*
����:�����UVA10723 Cyborg Genes��ͬһ����
ժ������
���������ַ���a��b���ʴ��ڶ��ٸ��������ַ������������ַ�����ָ
�ַ���a���ַ���b���Ǹ��ַ����������У����������ַ���Ҫ�󳤶���С��
����������ַ����ĳ��Ⱥʹ��ڶ��ٸ�
�ַ�������<=30.
����:http://www.lightoj.com/volume_showproblem.php?problem=1013
˼·:LCS����.ʵ����̵Ĵ�Ҫʹ��a��b����������,��ô��̵Ĵ�����
ab��LCS����a��b�ַ���ʣ��Ĳ���,����̳���Ϊlen(a)+len(b)-LCS(a,b),
��Ϊlen(a)+len(b)��LCS(a,b)�����һ��.
dp[i][j]��ʾa��ǰi���ַ���b��ǰj���ַ�LCS����󳤶�.
num[i][j]��ʾa��ǰi���ַ���b��ǰj���ַ����ܹ���LCS�ĸ���.
*/
//ac 3ms ����dp LCS
//dp[i][j]��ʾa����ǰi��Ԫ�غ�b����ǰj��Ԫ�ص�LCS�ĳ���
//num[i][j]��ʾ��Ӧ����dp[i][j]��LCS�ķ�������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
using namespace std;
typedef long long ll;

int n,m,dp[N][N];
ll num[N][N];
char a[N],b[N];

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%s",a+1);
        scanf("%s",b+1);
        n=strlen(a+1);
        m=strlen(b+1);
        memset(num,0,sizeof(num));
        num[0][0]=1;//��ʼ״̬
        for(int i=1;i<=n;i++)
            num[i][0]=1;
        for(int i=1;i<=m;i++)
            num[0][i]=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i] == b[j]){
                    dp[i][j]=dp[i-1][j-1]+1;
                    num[i][j]=num[i-1][j-1];
                }
                else{
                    if(dp[i-1][j]>dp[i][j-1]){
                        dp[i][j]=dp[i-1][j];
                        num[i][j]=num[i-1][j];
                    }
                    else if(dp[i-1][j]<dp[i][j-1]){
                        dp[i][j]=dp[i][j-1];
                        num[i][j]=num[i][j-1];
                    }
                    else{
                        dp[i][j]=dp[i][j-1];
                        num[i][j]=num[i-1][j]+num[i][j-1];
                    }
                }
            }
        }
        printf("Case %d: %d %lld\n",cas,n+m-dp[n][m],num[n][m]);
    }
    return 0;
}

/*
//ac 4ms ���仯����
//dp[i][j]��ʾa����ǰi��Ԫ�غ�b����ǰj��Ԫ�ص�LCS�ĳ���
//num[i][j]��ʾ��Ӧ����dp[i][j]��LCS�ķ�������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
using namespace std;
typedef long long ll;

int n,m,dp[N][N];
ll num[N][N];
char a[N],b[N];

int dfs(int i,int j){
	if(!i || !j){
		dp[i][j]=0;
		num[i][j]=1;
		return 0;
	}
	if(dp[i][j]!=-1)
		return dp[i][j];
	if(a[i] == b[j]){
		dp[i][j]=dfs(i-1,j-1)+1;
		num[i][j]+=num[i-1][j-1];
	}
	else{
		dfs(i-1,j);
		dfs(i,j-1);
		if(dp[i-1][j]>dp[i][j-1]){
            dp[i][j]=dp[i-1][j];
            num[i][j]=num[i-1][j];
        }
        else if(dp[i-1][j]<dp[i][j-1]){
            dp[i][j]=dp[i][j-1];
            num[i][j]=num[i][j-1];
        }
    	else{
            dp[i][j]=dp[i][j-1];
            num[i][j]+=num[i-1][j]+num[i][j-1];
        }
	}
	return dp[i][j];
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%s",a+1);
        scanf("%s",b+1);
        n=strlen(a+1);
        m=strlen(b+1);
        memset(dp,-1,sizeof(dp));
        memset(num,0,sizeof(num));
        dfs(n,m);
        printf("Case %d: %d %lld\n",cas,n+m-dp[n][m],num[n][m]);
    }
    return 0;
}
*/

/*
//ac 4ms
//dp[i][j]��ʾ���ɵ�Ŀ���ַ�������С����.
//num[i][j]��ʾ���ܹ���Ŀ���ַ����ķ�������.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
using namespace std;
typedef long long ll;

int n,m,dp[N][N];
ll num[N][N];
char a[N],b[N];

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%s",a+1);
        scanf("%s",b+1);
        n=strlen(a+1);
        m=strlen(b+1);
        memset(num,0,sizeof(num));
        num[0][0]=1;//��ʼ״̬
        for(int i=1;i<=n;i++){
        	dp[i][0]=i;//��ʼ״̬,a����ǰi����δƥ��,������ٻ���Ҫi���� ���д�ɼ��仯�������ܺ�����
            num[i][0]=1;//��ʾһ�����з����ĳ�ʼ״̬
		}
        for(int i=1;i<=m;i++){
        	dp[0][i]=i;//��ʼ״̬,b����ǰi����δƥ��,������ٻ���Ҫi����
            num[0][i]=1;
		}
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i] == b[j]){
                    dp[i][j]=dp[i-1][j-1]+1;
                    num[i][j]=num[i-1][j-1];
                }
                else{
                	dp[i][j]=min(dp[i-1][j],dp[i][j-1])+1;//��ȡĿ�괮����С���� �ټ��ϲ���LCS���a[i]��b[j]
                    if(dp[i-1][j]>dp[i][j-1])
                        num[i][j]=num[i][j-1];//��¼��С���ȵ�Ŀ�괮�ķ�����
                    else if(dp[i-1][j]<dp[i][j-1])
                        num[i][j]=num[i-1][j];
                    else
                        num[i][j]=num[i-1][j]+num[i][j-1];
                }
            }
        }
        printf("Case %d: %d %lld\n",cas,dp[n][m],num[n][m]);
    }
    return 0;
}
*/
