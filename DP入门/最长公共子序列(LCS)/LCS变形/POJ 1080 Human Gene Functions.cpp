/*
����:ժ������
������DNA���У���������DNA�����в������ɸ�'-'��ʹ�������г�����ȣ�
ʹ�����������(���ǲ���ʹ��a�Ŀո��Ӧb�Ŀո�λ��).
��Ӧλ�õ��������ŵĵ÷ֹ������������ߵ÷֡�
DNA���г���<=100.
����:http://poj.org/problem?id=1080
˼·:LCS����.Ϊ��ʹ�û�õķ������,����ö��a[i]��b[j]ƥ�����
a[i]��'-'��b[j]��'-'ƥ������,��ȡ���ֵ����.
ע���ʼ������һ�����б�ƥ����,��һ������ȫ����'-'ƥ�����
��ʼ����:
for(int i=1;i<=n;i++)
    dp[i][0]=dp[i-1][0]+score[a[i]]['-'];
for(int i=1;i<=m;i++)
    dp[0][i]=dp[0][i-1]+score['-'][b[i]];
״̬ת�Ʒ���:
dp[i][j]=max(dp[i-1][j-1]+score[a[i]][b[j]],max(dp[i][j-1]+score['-'][b[j]],dp[i-1][j]+score[a[i]]['-']));
*/
//ac 0ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,m,dp[N][N],score['T'+1]['T'+1];
char a[N],b[N];

//��ʼ���÷ֹ���
void init(){
    score['A']['A']=5;
    score['C']['C'] =5;
    score['G']['G'] =5;
    score['T']['T'] =5;
    score['-']['-'] = -10;
    score['A']['C'] = score['C']['A']=-1;
    score['A']['G'] = score['G']['A']=-2;
    score['A']['T'] = score['T']['A']=-1;
    score['A']['-'] = score['-']['A']=-3;
    score['C']['G'] = score['G']['C']=-3;
    score['C']['T'] = score['T']['C']=-2;
    score['C']['-'] = score['-']['C']=-4;
    score['G']['T'] = score['T']['G']=-2;
    score['G']['-'] = score['-']['G']=-2;
    score['T']['-'] = score['-']['T']=-1;
}

int main(){
    init();
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d %s",&n,a+1);
        scanf("%d %s",&m,b+1);
        for(int i=1;i<=n;i++)//b����ƥ����,a���л�ûƥ����,����b����ǰ��'-'����ƥ��
            dp[i][0]=dp[i-1][0]+score[a[i]]['-'];
        for(int i=1;i<=m;i++)//a����ƥ����,b���л�ûƥ����,����a����ǰ��'-'����ƥ��
            dp[0][i]=dp[0][i-1]+score['-'][b[i]];
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)
                //�����п���a[i]��b[j]��ƥ���,����Ϊ�˵÷����,���ܻ����'-'��a[i]��b[j]ƥ��
                //dp[i-1][j-1]+score[a[i]][b[j]] ��ʾa[i]��b[j]ƥ��
                //dp[i][j-1]+score['-'][b[j]]  ��a[i]ǰ����'-',b[j]��'-'ƥ��
                //dp[i-1][j]+score[a[i]]['-'] ��b[j]ǰ����'-',a[i]��'-'ƥ��
                dp[i][j]=max(dp[i-1][j-1]+score[a[i]][b[j]],max(dp[i][j-1]+score['-'][b[j]],dp[i-1][j]+score[a[i]]['-']));
        }
        printf("%d\n",dp[n][m]);
    }
    return 0;
}
