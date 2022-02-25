//�����������(LPS��Longest Palindromic Subsequence��)
//����dp���� Ҳ����ͨ�����촮������ͨ��LCS���
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110];
char a[110];

int main(){
    int len;
    scanf("%s",a+1);
    len=strlen(a+1);
    for(int i=1;i<=len;i++)
        dp[i][i]=1;
    for(int l=1;l<len;l++){
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            if(a[i] == a[j]) dp[i][j]=dp[i+1][j-1]+2;//�����˵����,�͵�������[i+1,j-1]�����������+2
            else dp[i][j]=max(dp[i][j-1],dp[i+1][j]);//������� ��Ϊ2������[i,j-1]��[i+1,j]��¼���ֵ
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}

/*
���������Ż��ռ� ö���������Ҷ˵� ��Ч,����ö������˵�,��dp[i%2][j]=max(dp[(i+1)%2][j-1],dp[i%2][j]),i+1 i %2λ�øպ��Ƿ�������
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[2][110];//����������Ż��ռ临�Ӷ�,�ɽ��n>1000��MLE����.��Ӱ��pos������������������
char a[110];

int main(){
    int len;
    scanf("%s",a+1);
    len=strlen(a+1);
    //���ֹ��������Ż�ֻ�ʺ�����dpö�����Ҷ˵��״̬ת��,���ʺ�ö�����䳤�Ⱥ���ʼ���״̬ת��,dp[(i+1)%2][j-1]�����״̬�����
    //ֻ��ö�����Ҷ˵��״̬ת��,��һ״̬����һ״̬��˵�Ϊi+1�ĸ���dp[(i+1)%2][j]�йغͱ���״̬dp[i%2][j-1]�й�
    for(int i=len-1;i>=1;i--){
        //������Ϊ�˷��㳤��Ϊ3���������еļ���,�м䵥�����ַ��㳤��Ϊ1�Ļ���������,���״̬����һ����˵�Ϊi+1����[i+1,i+3]ʱ���õ�
        dp[i%2][i]=1;
        for(int j=i+1;j<=len;j++){
            if(a[i]== a[j]) dp[i%2][j]=dp[(i+1)%2][j-1]+2;//i%2����ǰ��״̬,(i+1)%2����һ״̬
            //dp[i%2][j-1]����һ��j-1ѭ�������������,dp[(i+1)%2][j]����һ��״̬��˵�Ϊi+1ʱ��j�������ֵ
            else dp[i%2][j]=max(dp[i%2][j-1],dp[(i+1)%2][j]);
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}
*/

/*
//��������������
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int pos[110][110],dp[110][110];//��¼��������������ڵ�����
char a[110];

void output(int i,int j){
    if(i>j) return;//������������ѱ������
    if(i == j){//ֻʣ��һ���ַ�ʱ,˵������ʱ����,�Ը��ַ�Ϊ���ĶԳ�
        printf("%c",a[i]);
        return;
    }
    if(pos[i][j] == 1){//���˵���Ⱦ����
        printf("%c",a[i]);
        output(i+1,j-1);
        printf("%c",a[j]);
    }
    else if(pos[i][j] == 2)
        output(i,j-1);
    else if(pos[i][j] == 3)
        output(i+1,j);
}

int main(){
    int len;
    scanf("%s",a+1);
    len=strlen(a+1);
    for(int i=1;i<=len;i++)
        dp[i][i]=1;
    for(int l=1;l<len;l++){
        for(int i=1;i+l<=len;i++){
            int j=i+l;
            if(a[i] == a[j]){
                dp[i][j]=dp[i+1][j-1]+2;
                pos[i][j]=1;
            }
            else{
                if(dp[i][j-1]>dp[i+1][j]){
                    dp[i][j]=dp[i][j-1];
                    pos[i][j]=2;
                }
                else{
                    dp[i][j]=dp[i+1][j];
                    pos[i][j]=3;
                }
            }
        }
    }
    output(1,len);
    return 0;
}
*/

/*
���仯���� �����������
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[110][110];
char a[110];

int dfs(int i,int j){
    if(i>j) return 0;
    if(dp[i][j]) return dp[i][j];
    if(a[i] == a[j])
        dp[i][j]=dfs(i+1,j-1)+2;
    else
        dp[i][j]=max(dfs(i,j-1),dfs(i+1,j));
    return dp[i][j];
}

int main(){
    int len;
    scanf("%s",a+1);
    len=strlen(a+1);
    for(int i=1;i<=len;i++)
        dp[i][i]=1;
    printf("%d",dfs(1,len));
    return 0;
}
*/

/*
/*
�������� ��ö�����䳤�Ⱥ�ö����ʼ�������dp������Ч,dp[(i+1)%2][j-1]�����״̬����� ��������Ǵ����
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[2][110];
char a[110];

int main(){
    int len;
    scanf("%s",a+1);
    len=strlen(a+1);
    for(int l=1;l<len;l++){
        for(int i=1;i+l<=len;i++){
            dp[i%2][i]=1;
            int j=i+l;
            if(a[i] == a[j]) dp[i%2][j]=dp[(i+1)%2][j-1]+2;//dp[(i+1)%2][j-1]��ʾ�Ĳ�����dp[i+1][j-1],ʵ�ʱ�ʾ����dp[i-1][j-1]
            else dp[i%2][j]=max(dp[i%2][j-1],dp[(i+1)%2][j]);
        }
    }
    printf("%d",dp[1][len]);
    return 0;
}
*/
