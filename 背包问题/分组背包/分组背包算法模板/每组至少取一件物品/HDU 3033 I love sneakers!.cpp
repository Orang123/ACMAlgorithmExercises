/*
����:һ����Ҫ��Ь��,�ܹ���n˫Ь��,��k��Ʒ�Ƶ�Ь,Ҫ��
ÿ��Ь������һ˫,����ÿ˫Ь�ӵĻ���w�ͼ�ֵval,��mԪǮ
�����򵽵�Ь�ӵ�����ֵ�Ƕ���.
n<=100,m<=10000,0<=w,val<=100000,1<=k<=10.num[k]<=100.
ע��:ÿ˫Ь�ӵĻ��Ѻͼ�ֵ������Ϊ0.
����:��n����Ʒ��һ��������v�ı���.ÿ����Ʒ��num[i]��,
ͬһ���ڵ���ƷҪ������ѡһ��.ÿ����Ʒ�������w[i][j],
��ֵ��val[i][j],����i�����,j�����ڱ��.�������Ʒ��
�����������������������,�ܵõ�������ֵ,����������
ÿ����Ʒ����ȡһ��,���"Impossible",��������ܵõ���
����ֵ.ÿ����Ʒ��Ȼֻ��ѡ��ѡ,ͬһ����Ʒֻ��ѡһ��.
����:http://acm.hdu.edu.cn/showproblem.php?pid=3033
˼·:ÿ��Ʒ�Ƶ�����Ь�ӿ�����Ϊһ����Ʒ,ÿ��Ʒ�Ƶ�Ь��������һ��.
���鱳�� ÿ������ȡһ����Ʒģ����.ǰi�������ֵ������
ǰi-1���ǰi��״̬�����Ž�ת�ƶ���,Ҫע���i���dp[i][j]
����ֱ�Ӽ̳�dp[i-1][j],���������޷���֤ÿ��������һ����Ʒ.
��Ҫ����ǰi-1����һ״̬,���ֻ�ܶ�ά����ʵ��.
ʱ�临�Ӷ�O(k*max(num[k])*m)=1*100*10000=10^6

ע��:�������״̬ת�Ƶ�˳�� ��ʱֻ���ȿ���dp[i][j-w]ת�� �ٿ���dp[i-1][j-w]ת��
,��ʹ��Ʒ����ܱ�֤��Ϊ0,Ҳ�������˳��,HDU 3449������Ʒ���Ѳ�����Ϊ0,���Ǵ���,
�ݲ����ԭ��.
*/
//ac 46ms ÿ������ȡһ����Ʒ
//ʱ�临�Ӷ�O(k*max(num[k])*m)=1*100*10000=10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 10010
using namespace std;

//dp[i][j]����ǰi��ÿ��������һ����Ʒ�ڱ�������Ϊjʱ�ܻ�õ�����ֵ.
int n,m,k,num[N],w[N][110],val[N][110],dp[N][M];

int main(){
    int a,b,c;
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        memset(num,0,sizeof(num));
        while(n--){
            scanf("%d%d%d",&a,&b,&c);//a��Ь�ӵ�Ʒ�ƺ�
            num[a]++;//a����Ʒ�ĸ��� +1
            w[a][num[a]]=b;
            val[a][num[a]]=c;
        }
        //��Ϊdp[i][j]�ĳ�ʼ״̬������dp[i-1][j-w[i][t]]+val[i][t]��dp[i][j-w[i][t]]+val[i][t]ת�ƶ���
        //���dp[i][j]�ĳ�ʼ״̬�����Ǹ�����,���ܱ�֤��dp[i][j]�Ϸ�ʱ��i�����Ʒ����ȡ��һ��.
        //����ʼ��0����Ϊ�п�����Ʒ��ֵ����Ϊ0,�����޷��ж�dp[k][m]�����ǲ��ǺϷ�״̬.
        //�п���ʵ��ÿ����Ʒ��ֵ��Ϊ0,���ж�dp[k][m]=0 �����"Impossible".
        //ע���������ֻ���ڳ�ʼ��-INFΪ�Ƿ�״̬ʱ�ſ��Բ��ж���һ״̬�Ƿ�Ϸ�,
        //�����ʼ��ȫ0(��Ʒ��ֵ�ܱ�֤��Ϊ0)��-1(��Ʒ��ֵ����Ϊ0),��Ҫ�ж���һ״̬dp[i-1][j-w]��dp[i][j-w]�Ƿ�Ϸ�
        //����ĳ����Ʒ����һ��Ҳ����ȡ,������һ����ƷҲ��ͨ���ۼ�ʹ�ò��Ϸ�״̬��úϷ� ��Ӱ�����Ľ��
        memset(dp,-0x3f,sizeof(dp));//�����Ծ����ж��� ��һ״̬�Ƿ�Ϸ�,��˳�ʼ��Ϊ-1Ҳ�����
        for(int i=1;i<=m;i++)
            dp[0][i]=0;//��ʼ״̬,һ����ƷҲ��ȡʱ,�κα���������Ӧ�ļ�ֵ��Ϊ0
        //���ǵ�i����Ʒ
        for(int i=1;i<=k;i++){
            //��i���е�ÿһ����Ʒt��01����
            for(int t=1;t<=num[i];t++){
                for(int j=m;j>=w[i][t];j--){
                    /*
                    ע������dp��˳�����������ǰi����Ʒdp[i][j-w[i][t]]ת��,
                    �ٿ����Ƿ���ǰi-1����Ʒdp[i-1][j-w[i][t]]ת��,��Ϊ�п���
                    ��i����Ʒ��t����Ʒ���Ϊ0,��������ȿ�����ǰi-1��״̬ת��
                    ����,��ôdp[i][j]=dp[i-1][j-0]+val[i][t],�ٿ�����ǰi���
                    ״̬ת�ƶ���,dp[i][j]=dp[i][j-0]+val[i][t],����dp[i][j]����
                    �Ѿ�����t����Ʒȡ����,����������dp[i][j]ȡ����t����Ʒ������,
                    �ظ��ؽ���t����Ʒ��ȡ��һ��.��һ����Ʒֻ��ȡһ����Υ��,���
                    �����.
                    */
                    //dp[i][j-w[i][t]]>=0��֤ ǰ��i��ÿ����Ʒ�Ѿ�����ȡ��һ��
                    if(dp[i][j-w[i][t]]>=0)//���� �ܷ����Ѿ������i����Ʒ�Ļ�����,���������i�����Ʒ�����Ž�
                        dp[i][j]=max(dp[i][j],dp[i][j-w[i][t]]+val[i][t]);
                    //dp[i-1][j-w[i][t]]>=0��֤ǰi-1��ÿ����Ʒ��ȡ��һ�� �ǺϷ�״̬
                    if(dp[i-1][j-w[i][t]]>=0)//���� ��ǰi-1����Ʒ���Ž���������ٷ���һ����i�����Ʒ��õ����Ž�
                        dp[i][j]=max(dp[i][j],dp[i-1][j-w[i][t]]+val[i][t]);
                }
            }
        }
        if(dp[k][m]>=0)
            printf("%d\n",dp[k][m]);
        else
            printf("Impossible\n");
    }
    return 0;
}

/*
//ac 46ms ÿ������ȡһ����Ʒ
//dp[i][j]=max(dp[i][j],max(dp[i-1][j-w[i][t]]+val[i][t],dp[i][j-w[i][t]]+val[i][t]));
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 10010
using namespace std;

//dp[i][j]����ǰi��ÿ��������һ����Ʒ�ڱ�������Ϊjʱ�ܻ�õ�����ֵ.
int n,m,k,num[N],w[N][110],val[N][110],dp[N][M];

int main(){
    int a,b,c;
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        memset(num,0,sizeof(num));
        while(n--){
            scanf("%d%d%d",&a,&b,&c);
            num[a]++;
            w[a][num[a]]=b;
            val[a][num[a]]=c;
        }
        memset(dp,-0x3f,sizeof(dp));
        for(int i=1;i<=m;i++)
            dp[0][i]=0;
        for(int i=1;i<=k;i++){
            for(int t=1;t<=num[i];t++){
                for(int j=m;j>=w[i][t];j--)
                    dp[i][j]=max(dp[i][j],max(dp[i-1][j-w[i][t]]+val[i][t],dp[i][j-w[i][t]]+val[i][t]));
            }
        }
        if(dp[k][m]>=0)
            printf("%d\n",dp[k][m]);
        else
            printf("Impossible\n");
    }
    return 0;
}
*/

/*
//ac 31ms ÿ������ȡһ����Ʒ
//���������Ż� �������� dp[M] tp[M]����
//dp[j]=max(dp[j],max(tp[j-w[i][t]]+val[i][t],dp[j-w[i][t]]+val[i][t]));
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 10010
using namespace std;

//tp[j]����ǰi-1��ÿ��������һ����Ʒ�ڱ�������Ϊjʱ�ܻ�õ�����ֵ.
//dp[j]����ǰi��ÿ��������һ����Ʒ�ڱ�������Ϊjʱ�ܻ�õ�����ֵ.
int n,m,k,num[N],w[N][110],val[N][110],dp[M],tp[M];

int main(){
    int a,b,c;
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        memset(num,0,sizeof(num));
        while(n--){
            scanf("%d%d%d",&a,&b,&c);
            num[a]++;
            w[a][num[a]]=b;
            val[a][num[a]]=c;
        }
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=k;i++){
            //��ǰi-1��״̬��ֵ��tp
            for(int j=0;j<=m;j++)
                tp[j]=dp[j];
            //ǰi��״̬��ʼ�ǲ��Ϸ���
            memset(dp,-0x3f,sizeof(dp));
            for(int t=1;t<=num[i];t++){
                for(int j=m;j>=w[i][t];j--)
                    dp[j]=max(dp[j],max(tp[j-w[i][t]]+val[i][t],dp[j-w[i][t]]+val[i][t]));
            }
        }
        if(dp[m]>=0)
            printf("%d\n",dp[m]);
        else
            printf("Impossible\n");
    }
    return 0;
}
*/

/*
dfs����ö������ ����ģ��ÿ��������ȡһ��,��Ȼ����Ҳ�ǻ�TLE��
���ö��ÿ������ȡһ����Ʒ ��ʣ�µ���Ʒ��Ҫģ��01����,�����ֲ���
���������Ʒ�ǵ�ǰ�黹���Ѿ�������һ����,��˱�������������.
*/
