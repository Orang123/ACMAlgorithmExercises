/*
����:���������ַ������ҳ����ǵ�����������к�ʣ�µ�������ƴ�Ӻ�Ĵ�
�ַ�������<=100.
����:http://acm.hdu.edu.cn/showproblem.php?pid=1503
˼·:���������pos[i][j]��¼ʵ�� LCS������λ��,�ݹ����.
*/
//ac 31ms
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110],pos[110][110];
char a[110],b[110];
//��ӡLCS�ַ���
void printLCS(int st,int ed){
    if(!st){//�п���LCS�����a�ַ����������,b�ַ�����ʣ��ǰ���һ����,�����ٶ��������.
        for(int i=1;i<=ed;i++)
            printf("%c",b[i]);
        return;
    }
    if(!ed){//�п���LCS�����b�ַ����������,a�ַ�����ʣ��ǰ���һ����,�����ٶ��������.
        for(int i=1;i<=st;i++)
            printf("%c",a[i]);
        return;
    }

    if(pos[st][ed] == 1){
        printLCS(st-1,ed-1);
        printf("%c",a[st]);//a[st]����LCS������� һ��
    }
    else if(pos[st][ed] == 2){
        printLCS(st-1,ed);
        printf("%c",a[st]);//a[st]û������LCS,�������
    }
    else if(pos[st][ed] == 3){
        printLCS(st,ed-1);
        printf("%c",b[ed]);//a[ed]û������LCS,�������
    }
}
//31ms
int main(){
    int len1,len2;
    while(scanf("%s %s",a+1,b+1)!=EOF){
        len1=strlen(a+1);
        len2=strlen(b+1);
        for(int i=1;i<=len1;i++){
            for(int j=1;j<=len2;j++){
                if(a[i] == b[j]){
                    dp[i][j]=dp[i-1][j-1]+1;
                    pos[i][j]=1;
                }
                else{
                    //���ﵱdp[i-1][j]==dp[i][j-1]ʱ,����a b�ַ���������LCS���ǲ���,������Ⱥ�˳����ܲ�ͬ,��OJ����ͬ����AC��
                    if(dp[i-1][j]>dp[i][j-1]){
                        dp[i][j]=dp[i-1][j];
                        pos[i][j]=2;
                    }
                    else{//dp[i-1][j]==dp[i][j-1]ʱ,��Ӻ���ǰ�������b�ַ���������LCS�ǲ���
                        dp[i][j]=dp[i][j-1];
                        pos[i][j]=3;
                    }
                }
            }
        }
        printLCS(len1,len2);
        printf("\n");
    }
    return 0;
}

/*
//ac 15ms ������pos����
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int dp[110][110];
char a[110],b[110];
//��ӡLCS�ַ���
void printLCS(int st,int ed){
    if(!st){//�п���LCS�����a�ַ����������,b�ַ�����ʣ��ǰ���һ����,�����ٶ��������.
        for(int i=1;i<=ed;i++)
            printf("%c",b[i]);
        return;
    }
    if(!ed){//�п���LCS�����b�ַ����������,a�ַ�����ʣ��ǰ���һ����,�����ٶ��������.
        for(int i=1;i<=st;i++)
            printf("%c",a[i]);
        return;
    }

    if(a[st] == b[ed]){
        printLCS(st-1,ed-1);
        printf("%c",a[st]);//a[st]����LCS������� һ��
    }
    else if(dp[st-1][ed]>dp[st][ed-1]){
        printLCS(st-1,ed);
        printf("%c",a[st]);//a[st]û������LCS,�������
    }
    else if(dp[st-1][ed]<=dp[st][ed-1]){
        printLCS(st,ed-1);
        printf("%c",b[ed]);//a[ed]û������LCS,�������
    }
}
//31ms
int main(){
    int len1,len2;
    while(scanf("%s %s",a+1,b+1)!=EOF){
        len1=strlen(a+1);
        len2=strlen(b+1);
        for(int i=1;i<=len1;i++){
            for(int j=1;j<=len2;j++){
                if(a[i] == b[j])
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                	dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        printLCS(len1,len2);
        printf("\n");
    }
    return 0;
}
*/

/*
//ac 15ms ���仯����
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110],pos[110][110];
char a[110],b[110];
//��ӡLCS�ַ���
void printLCS(int st,int ed){
    if(!st){//�п���LCS�����a�ַ����������,b�ַ�����ʣ��ǰ���һ����,�����ٶ��������.
        for(int i=1;i<=ed;i++)
            printf("%c",b[i]);
        return;
    }
    if(!ed){//�п���LCS�����b�ַ����������,a�ַ�����ʣ��ǰ���һ����,�����ٶ��������.
        for(int i=1;i<=st;i++)
            printf("%c",a[i]);
        return;
    }

    if(pos[st][ed] == 1){
        printLCS(st-1,ed-1);
        printf("%c",a[st]);//a[st]������LCS�������
    }
    else if(pos[st][ed] == 2){
        printLCS(st-1,ed);
        printf("%c",a[st]);//
    }
    else if(pos[st][ed] == 3){
        printLCS(st,ed-1);
        printf("%c",b[ed]);
    }
}

int dfs(int st,int ed){
    if(!st || !ed) return dp[st][ed]=0;
    if(dp[st][ed]!=-1) return dp[st][ed];
    if(a[st] == b[ed]){
        dp[st][ed]=dfs(st-1,ed-1)+1;
        pos[st][ed]=1;
    }
    else{
        dfs(st-1,ed);
        dfs(st,ed-1);
        if(dp[st-1][ed]>dp[st][ed-1]){
            dp[st][ed]=dp[st-1][ed];
            pos[st][ed]=2;
        }
        else{
            dp[st][ed]=dp[st][ed-1];
            pos[st][ed]=3;
        }
    }
    return dp[st][ed];
}

int main(){
    int len1,len2;
    while(scanf("%s %s",a+1,b+1)!=EOF){
        memset(dp,-1,sizeof(dp));
        memset(pos,0,sizeof(pos));
        len1=strlen(a+1);
        len2=strlen(b+1);
        dfs(len1,len2);
        printLCS(len1,len2);
        printf("\n");
    }
    return 0;
}
*/
