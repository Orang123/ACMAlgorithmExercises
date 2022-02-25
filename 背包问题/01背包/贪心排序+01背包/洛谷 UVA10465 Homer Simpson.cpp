/*
����:ժ������
�����ֺ�����,��һ�ֳ�һ����Ҫ��m����,�ڶ��ֳ�һ����Ҫ��n����.
��������t���ӵ�ʱ��,���������˷Ѽ����Ӳ��ܳԺ���,Ҳ�����óԺ�����ʱ��
�����ܶ�.���Ժ������ѵ�ʱ��ﵽ���ʱ,��������ܳԼ�������?
����:https://www.luogu.com.cn/problem/UVA10465
˼·:ÿ�ֺ������ԳԶ��,���ڶ�άĿ����������ȫ��������.
dp[i][j]��ʾ��ǰi��������ǡ�û���ʱ��j���ܳԵ����ĺ�������.
��ʼ״ֻ̬��dp[0]=0�ǺϷ�״̬.
*/
//ac 80ms ��άĿ����������ȫ����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 3
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;

int t,w[N],dp[M];

int main(){
    while(scanf("%d%d%d",&w[1],&w[2],&t)!=EOF){
        memset(dp,-1,sizeof(dp));
        dp[0]=0;
        for(int i=1;i<=2;i++){
            for(int j=w[i];j<=t;j++){
                if(dp[j-w[i]]!=-1)
                    dp[j]=max(dp[j],dp[j-w[i]]+1);
            }
        }
        int ans=0;
        //�Ժ���ʱ�併���ж��Ƿ�Ϸ�,��һ���Ϸ��ľ�������ܳԺ�����ʱ��,��Ӧ��dp[ans]�������Եĺ�������
        for(int i=t;t>=0;i--){
            if(dp[i]!=-1){
                ans=i;
                break;
            }
        }
        printf("%d",dp[ans]);
        if(ans<t)
            printf(" %d",t-ans);
        printf("\n");
    }
    return 0;
}
