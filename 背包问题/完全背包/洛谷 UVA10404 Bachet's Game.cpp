/*
//���� ˼·ժ������
����:����n��ʯͷ,��m��ȥ��ʯͷ�ķ�ʽ,ÿ�ַ�ʽ����ȥ��һ������ʯͷ,
����Stan(���S),Ollie(���O),S����,O����,ÿ��ÿ������ѡ��һ��ȥ��
ʯͷ�ķ�ʽ,˭ȥ�����һ��˭��Ӯ��.Ҫ�����ʤ֮����˭.
����:https://www.luogu.com.cn/problem/UVA10404
˼·:������Կ�����һ����ȫ�����ı���,dp[i]ֻ��0��1����״̬,1�Ǵ���
��ǰi��ʯ����ȡ��Ϊ��ʤ,0����ǰi��ʯ����ȡ��Ϊ�ذ�.ת̬ת�Ʒ���
if(dp[i - val[j]] == 0)dp[i] = 1;(��ǰ״̬����ת�������ֱذ�,˵����ǰ
Ϊ���ֱ�ʤ).
*/

//ac 160ms ��ȫ����+����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 1000100
using namespace std;

//dp[i]=true��ʾ��i��ʯ�ӣ�����ѡ���˿��Ի�ʤ��
int n,m,w[N],dp[M];

int main(){
    while(scanf("%d",&n)!=EOF){
        memset(dp,0,sizeof(dp));
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
            scanf("%d",&w[i]);
        for(int i=1;i<=n;i++){//����ģ�ⲩ�Ĺ��� ������ö�ٱ������� ��ö��ÿ��ȥ��ʯͷ�ķ�ʽ
            for(int j=1;j<=m;j++){
                if(i-w[j]>=0 && !dp[i-w[j]]){
                    dp[i]=1;
                    break;
                }
            }
        }
        if(dp[n])//dp[n]=1,stan����ƶ�ʯͷ
            printf("Stan wins\n");
        else
            printf("Ollie wins\n");
    }
    return 0;
}
