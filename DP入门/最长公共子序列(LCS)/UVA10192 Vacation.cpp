/*
����:
�������Ϣһ�£���ȥ�ȼ٣�������Ĳ�֪����ȥ�ĸ����С����ԣ�������ĸ�ĸѰ�������
��ĸ��˵�����ҵĶ��ӣ������ȥ���衢������˹�����׶ء��������˳��ȥ����Ȥ��
��Ȼ���㸸��˵�������ӣ������������У���ȥ���裬Ȼ��ȥ��˹������ȥ�׶أ����ȥ����
��֪������˵ʲô�����������е������ˣ���Ϊ��û��Ԥ�ϵ�����������㺦������������㸸��
�Ľ�����˺���ĸ�ס��������������ĸ�׵Ľ��飬��Ҳ�����˺���ĸ��ס���������ܻ��ø��㣬
��Ϊ�����������ǵĽ��飬����˺��������ˣ���ˣ�����������ܵ���ѭ���ǵĽ��顣��ˣ���
��ʶ��������-��˹��-�׶ء����������������ĸ�ĸ��֮�������˵�㲻��ȥ�����������ǳ�ϲ���ġ�
��Ϊ�˲����������ģ���Ҫ�����ܵ��������Ǹ������,�������ȥ�������С�
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1133
˼·:LCS����.
*/
//ac 0ms ����dp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
using namespace std;

int n,m,dp[N][N];
char a[N],b[N];

int main(){
    int cas=0;
    while(gets(a+1) && a[1]!='#'){//���ﲻ����scanf ��TLE ��֪��ԭ��
        cas++;
        gets(b+1);
        n=strlen(a+1);
        m=strlen(b+1);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i] == b[j])
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        printf("Case #%d: you can visit at most %d cities.\n",cas,dp[n][m]);
    }
    return 0;
}
