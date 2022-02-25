#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
/*
����:��һ���ַ���,ÿ����ĸ�����ӻ�ɾ�����۲�ͬ,���ַ����е���ĸ����
���ӻ�ɾ����ʹ������ַ�����Ϊ���Ĵ�����С����.
����:http://poj.org/problem?id=3280
dp[i][j]����i~j֮����ַ������ӻ�ɾ����ĸʹ���Ϊ���Ĵ�����С����
*/

char s[2100],c;
int n,m,dp[2100][2100],add[150],del[150];

int main(){
    scanf("%d%d",&n,&m);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++){
        scanf(" %c %d %d",&c,&add[i],&del[i]);
        add[c]=add[i],del[c]=del[i];
    }
    for(int l=1;l<m;l++){
        for(int i=1;i+l<=m;i++){
            int j=i+l;
            if(s[i] == s[j]) dp[i][j]=dp[i+1][j-1];//�����˵���ͬ,����ۻ����м��dp[i+1][j-1]
            else{
                //�ֱ�ö�����˵���ַ����ӻ�ɾ���Ĵ���,��ȡ��С����
                dp[i][j]=min(dp[i+1][j]+add[s[i]],dp[i+1][j]+del[s[i]]);//��s[i]�������ӻ�ɾ��
                dp[i][j]=min(dp[i][j],min(dp[i][j-1]+add[s[j]],dp[i][j-1]+del[s[j]]));//��s[j]�������ӻ�ɾ��
            }
        }
    }
    printf("%d",dp[1][m]);
    return 0;
}


