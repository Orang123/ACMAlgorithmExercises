/*
����:ժ������
���������ɿո�ָ������, Ҫ������������������������,�����.
��������һ���⼴��. ע��ÿ��������Ҫ��������һ�㴦���ַ���
�����е�һ�������ַ�. ��ÿ��������һ������.
���ʸ���<=100,�������ʳ���<=30.
����:http://poj.org/problem?id=2250
˼·:LCS����.��ע���������еĵ���Ԫ����һ���ַ���,dpʱ�Ƚ���Ҫ�õ�
strcmp�������Ƚ����ַ����Ƿ����.
*/
//ac 0ms ����dp �±��1��ʼ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,m,dp[N][N];
char a[N][35],b[N][35];

void print(int i,int j){
    if(!i || !j)
        return;
    if(!strcmp(a[i],b[j])){
        print(i-1,j-1);
        if(i != 1 && j != 1)
            printf(" ");
        printf("%s",a[i]);
    }
    else{
        if(dp[i-1][j]>dp[i][j-1])
            print(i-1,j);
        else
            print(i,j-1);
    }
}

int main(){
    while(scanf("%s",a[++n])!=EOF){
        while(scanf("%s",a[++n]) && a[n][0]!='#');
        n--;
        while(scanf("%s",b[++m]) && b[m][0]!='#');
        m--;
        //memset(dp,0,sizeof(dp));//�����ʼ��dp����
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(!strcmp(a[i],b[j]))
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        print(n,m);
        printf("\n");
        n=m=0;
    }
    return 0;
}
