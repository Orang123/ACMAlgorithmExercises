/*
LCS-Longest Common Subsequence(�����������)
����:һ���ַ�������������Ӽ����ַ�������ʹ֮��Ϊ���Ĵ�.
����:http://poj.org/problem?id=1159
˼·:���ַ����������򴮵�����������У�LCS��,����n-���LCS���Ǵ�.
dp[i][j]��ʾ�����е�ǰi��Ԫ�غ������е�ǰj��Ԫ�ص�LCS����
ע��:��Ϊn=5000ʱ��n*n=25M,�ռ临�Ӷ�̫��
���������Ż��ռ临�Ӷ� �����޷����LCS�ַ���
ע�⵽dp[i][j]ֻ��dp[i-1][j-1],dp[i-1][j],dp[i][j-1]����ֵ��أ�
���ǿ���ֻ�������е����ݼ��ɣ�����ʹ����������������㼴�ɡ�
����dp�����˹��������Ż�.

LCS dp��ⲩ��:https://www.cnblogs.com/moomcake/p/9385170.html
*/
/*
����
5
Ab3bd
11
abbdsadsaab

���
2
6
*/
//ac 1532ms
//ʱ�临�Ӷ�O(n^2)
//�ռ临�Ӷ� δ���ù��������Ż�:O(n^2),���ù��������Ż�O(2*n)
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int dp[2][5010];

int main(){
    int n;
    char s[5010],a[5010],b[5010];
    while(scanf("%d",&n)!=EOF){
        scanf("%s",s+1);
        memset(dp,0,sizeof(dp));
        for(int i=1,j=n;i<=n;i++,j--){
            a[i]=s[i];//a������������
            b[j]=s[i];//b���鵹����������
        }
        /*
        iΪż��ʱ i%2=0,i-1��Ϊ���� (i-1)%2Ϊ1,����dp[0][j]��dp[1][j]ת�ƶ���,
        Ȼ��i++����Ϊ����,i%2=1,i-1Ϊż�� (i-1)%2=0,dp[1][j]����dp[0][j]ת�ƶ���,
        ��dp[0][j]������һ��i-1��ת�ƺ��״̬,��������.
        */
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i]==b[j])//a[i] b[j]���ʱ,dp[i][j]=dp[i-1][j-1]+1;
                    dp[i%2][j]=dp[(i-1)%2][j-1]+1;
                else
                    dp[i%2][j]=max(dp[(i-1)%2][j],dp[i%2][j-1]);
            }
        }
        printf("%d\n",n-dp[n%2][n]);
    }
    return 0;
}

/*
�޹��������Ż�
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[5100][5010];//��MLE �ռ䳬������ 25M ���ֻ��1M 1000000

int main(){
    int n;
    char s[5010],a[5010],b[5010];
    while(scanf("%d",&n)!=EOF){
        scanf("%s",s+1);
        memset(dp,0,sizeof(dp));
        for(int i=1,j=n;i<=n;i++,j--){
            a[i]=s[i];
            b[j]=s[i];
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i]==b[j])
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        printf("%d\n",n-dp[n][n]);
    }
    return 0;
}
*/


/*
//���仯����
//���仯�����޷��ù��������Ż��ռ�
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110];
char s[110],a[110],b[110];
int dfs(int i,int j){
    if(!i || !j) return dp[i][j]=0;//�������л������г���Ϊ0ʱ,LCS����0
    if(dp[i][j]!=-1) return dp[i][j];
    if(a[i] == b[j])
        dp[i][j]=dfs(i-1,j-1)+1;
    else
        dp[i][j]=max(dfs(i-1,j),dfs(i,j-1));//��a[i]!=b[j] dp[i][j]ֻȡdp[i-1][j]��dp[i][j-1]�����ֵ
    return dp[i][j];
}

int main(){
    int n;
    while(scanf("%d",&n)!=EOF){
        scanf("%s",s+1);
        memset(dp,-1,sizeof(dp));//0����Ҳ�ǺϷ�״̬,��˳�ʼ״̬����Ϊ-1
        for(int i=1,j=n;i<=n;i++,j--){
            a[i]=s[i];
            b[j]=s[i];
        }
        printf("%d\n",n-dfs(n,n));
    }
    return 0;
}
*/

/*
//��ӡLCS�ַ���
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110],pos[110][110];
char a[110],b[110];
//��ӡLCS�ַ���
void printLCS(int st,int ed){
    if(!st || !ed) return;//��a��b�ַ����ĳ���Ϊ0ʱ,LCS��Ϊ0 ����
    if(pos[st][ed] == 1){//˵��a[st] b[ed]��LCS�е�Ԫ��,�����LCS��һ��Ԫ�ؿ�ʼ���,���Ի��ݺ�����������LCS��Ԫ��.
        printLCS(st-1,ed-1);
        printf("%c",a[st]);
    }
    else if(pos[st][ed] == 2)//����ʵ��LCS(�������)���ڵ��������
        printLCS(st-1,ed);
    else if(pos[st][ed] == 3)
        printLCS(st,ed-1);
}

int main(){
    int len1,len2;
    scanf("%s",a+1);
    scanf("%s",b+1);
    len1=strlen(a+1);
    len2=strlen(b+1);
    for(int i=1;i<=len1;i++){
        for(int j=1;j<=len2;j++){
            if(a[i] == b[j]){
                dp[i][j]=dp[i-1][j-1]+1;
                pos[i][j]=1;//a[i]==a[j] ����a[i]��LCS�е�Ԫ��,����Ҫ���
            }
            else{
                if(dp[i-1][j]>dp[i][j-1]){
                    dp[i][j]=dp[i-1][j];
                    pos[i][j]=2;//[i-1,j]��[i,j-1]LCS�ĳ��ȸ���
                }
                else{
                    dp[i][j]=dp[i][j-1];
                    pos[i][j]=3;//[i,j-1]��[i-1,j]LCS�ĳ��ȸ���
                }
            }
        }
    }
    printLCS(len1,len2);
    return 0;
}
*/
