/*
����:ժ������
����һ���ַ����������ֲ���������λ��ɾ�������ӡ��滻һ���ַ�����
����Ҫ���ٵĲ�������ʹ���Ϊ���Ĵ���
�ַ�������<=1000.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1680
˼·:����dp,���仯����ʵ��.
����ɾ�����������Ӳ���������һ����.
dp[l][r]��ʾҪʹ������[l,r]��Ϊ���Ĵ�����Ҫ�����Ĵ���.
*/
//ac 0ms ���仯����
//ʱ�临�Ӷ�(1000*1000)=10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int dp[N][N];
char str[N];

int dfs(int l,int r){
    if(dp[l][r] != -1)
        return dp[l][r];
    if(l>=r)
        return dp[l][r]=0;
    if(str[l] == str[r])//���������ַ����,�����ٲ���,��������Ϊ����[l+1,r-1]�Ĳ�������.
        dp[l][r]=dfs(l+1,r-1);
    else
        //�������䲻��,�����ֲ�����ʽʹ���Ϊ����
        //1.�޸�str[l]��str[r]ʹ��str[l]==str[r],��:dp[l+1][r-1]+1
        //2.ɾ��str[l],[l+1,r]�����ǻ��Ļ���str[r]�������һ����str[l]��ȵ��ַ�,��:dp[l+1][r]+1
        //3.ɾ��str[r],[l,r-1]�����ǻ��Ļ���str[l]ǰ�����һ����str[r]��ȵ��ַ�,��:dp[l][r-1]+1
        dp[l][r]=min(dfs(l+1,r-1),min(dfs(l+1,r),dfs(l,r-1)))+1;
    return dp[l][r];
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(dp,-1,sizeof(dp));
        scanf("%s",str+1);
        printf("Case %d: %d\n",cas,dfs(1,strlen(str+1)));
    }
    return 0;
}

/*
//ac 0ms ����dp ö�����䳤�ȡ���ʼ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int dp[N][N],len;
char str[N];

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%s",str+1);
        len=strlen(str+1);
        memset(dp,0,sizeof(dp));
        for(int l=1;l<len;l++){
        	for(int i=1;i+l<=len;i++){
        		int j=i+l;
        		if(str[i] == str[j])
        			dp[i][j]=dp[i+1][j-1];
        		else
        			dp[i][j]=min(dp[i+1][j-1],min(dp[i+1][j],dp[i][j-1]))+1;
			}
		}
		printf("Case %d: %d\n",cas,dp[1][len]);
    }
    return 0;
}
*/

/*
//ac 0ms ����dp ö�����Ҷ˵�
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int dp[N][N],len;
char str[N];

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        scanf("%s",str+1);
        len=strlen(str+1);
        memset(dp,0,sizeof(dp));
        for(int i=len-1;i>=1;i--){
        	for(int j=i+1;j<=len;j++){
        		if(str[i] == str[j])
        			dp[i][j]=dp[i+1][j-1];
        		else
        			dp[i][j]=min(dp[i+1][j-1],min(dp[i+1][j],dp[i][j-1]))+1;
			}
		}
		printf("Case %d: %d\n",cas,dp[1][len]);
    }
    return 0;
}
*/
