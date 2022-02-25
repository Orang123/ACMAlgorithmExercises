#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 1100
#define INF -0x3f3f3f3f
using namespace std;
//ac 31ms ��ά01���� �����������ݻ���װ��m����Ʒ�ܻ�õ�����ֵ
//�Ż�,װ�뱳����Ʒ��������ӵ�ǰ��Ʒi��ʼö��,��ǰi����Ʒ,���װ��i��
/*
����:��N����Ӱ��ѡM����,ÿ�����в�ͬ��ʱ���ͼ�ֵ,���Ƿ�
���Կ���M����Ӱ,���ԵĻ����ֵ�����ֵ,�������0.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3496
˼·:��01����ģ�ͻ�����,�ټ�һ��ά��,װ�뱳����Ʒ����,
��ʼ״̬,���ڱ���������˵�Ǿ����ܶ�װ��,���ڱ���������Ʒ������˵��ǡ��װ��,
��ʼ��dp[0][i]=0,����װ�뱳����Ʒ����j��Ҫ������ѭ������ԭ���01����ʣ���ݻ�
������һ����,���Ǳ�֤dp[j-w[i]]����һ״̬��ֵ,�����ǵ�ǰ��i����Ʒ�����ı���,
����i����Ʒ�����ظ��ۼ�.
*/
//dp[j][k] ��������Ϊk�ı���ǡ��װ��j����Ʒ����ܻ�õļ�ֵ,����k��һ��ǡ��װ��,���Ǿ����ܶ��װ
int n,m,l,w[N],val[N],dp[N][M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,INF,sizeof(dp));//�����ܶ��װ�뱳��
        scanf("%d%d%d",&n,&m,&l);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&w[i],&val[i]);
        //���ڱ���������˵�Ǿ����ܶ�װ��,���ڱ���������Ʒ������˵��ǡ��װ��,
        //��Ϊֻ��װ�뱳����Ʒ����Ϊ0����ʼ��Ϊ0,�����Ӧ�������������
        for(int i=0;i<=l;i++)//��ʼ״̬ ��������Ϊ0,���뱳����Ʒ����Ϊ0ʱ
            dp[0][i]=0;
        for(int i=1;i<=n;i++){
            //ö��ǰi����Ʒ��Ӧѡ�񼸸���Ʒ���뱳��,ǰi����Ʒ,
            //������i��,�����Ż�,���Ϻܶ��������j��ʼ�Ͻ���m
            //ͬ����Ҫ����,�������ܱ�֤dp[j-1][k-w[i]]�е�j-1������һ��״̬ǰi-1��״̬ʱ��ֵ,
            //�����ظ���ͬһ��Ʒ�ۼӶ��,�������dp[j-1][k-w[i]]�е�j-1,�����Ѿ�����˵�ǰ״̬ǰi����Ʒ��ֵ,val[i]�ظ����뱳����
            //�����ԭ���01����ʣ�����������ԭ����ͬ
            //װ��j����Ʒ������״̬��װ��j-1����Ʒ ���϶�ά���ñ���������
            for(int j=i;j>=1;j--){
                for(int k=l;k>=w[i];k--)
                    dp[j][k]=max(dp[j][k],dp[j-1][k-w[i]]+val[i]);
            }
        }
        if(dp[m][l]>0)//��ǡ��װ��m����Ʒ,�ǺϷ�ת̬,������
            printf("%d\n",dp[m][l]);
        else
            printf("0\n");
    }
    return 0;
}

/*
//ac 31ms δ�Ż�,װ�뱳����Ʒ���������m��ʼö��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 1100
#define INF -0x3f3f3f3f
using namespace std;
int n,m,l,w[N],val[N],dp[N][M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,INF,sizeof(dp));//�����ܶ��װ�뱳��
        scanf("%d%d%d",&n,&m,&l);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&w[i],&val[i]);
        for(int i=0;i<=l;i++)
            dp[0][i]=0;
        for(int i=1;i<=n;i++){
            for(int j=m;j>=1;j--){
                for(int k=l;k>=w[i];k--)
                    dp[j][k]=max(dp[j][k],dp[j-1][k-w[i]]+val[i]);
            }
        }
        if(dp[m][l]>0)
            printf("%d\n",dp[m][l]);
        else
            printf("0\n");
    }
    return 0;
}
*/

/*
//ac 46ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 1100
#define INF -0x3f3f3f3f
using namespace std;
int n,m,l,w[N],val[N],dp[N][M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,INF,sizeof(dp));//�����ܶ��װ�뱳��
        scanf("%d%d%d",&n,&m,&l);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&w[i],&val[i]);
        for(int i=0;i<=l;i++)
            dp[0][i]=0;
        for(int i=1;i<=n;i++){
            for(int k=l;k>=w[i];k--)
                for(int j=1;j<=i;j++)
                    dp[j][k]=max(dp[j][k],dp[j-1][k-w[i]]+val[i]);
        }
        if(dp[m][l]>0)
            printf("%d\n",dp[m][l]);
        else
            printf("0\n");
    }
    return 0;
}
*/
