#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 510
using namespace std;
//ac 31ms 01����������װ����Ʒ�������ķ����� ��ά����ʵ�� �����ܶ��װ������,��Ҫ��ǡ��װ��
//ö��ö�ٱ���ʣ�������ڶ���ѭ������ ��Ʒ����������ѭ������
//����ʾ����ܶ��װk����Ʒǡ��װ����������M�ķ�����,��ô��ʼ���� dp[0..k][0]=1
/*
����:����Ǯ���͸�����Ʒ�ļ۸�,���������������Ʒ�ķ�����.
����:http://acm.hdu.edu.cn/showproblem.php?pid=2126
˼·:��01�����������������������һ��ά��,������ʾ���˼�����Ʒ.
��dp[j][k],��������Ϊj�ı�����k����Ʒ����෽����.��ô״̬ת��
���̾���dp[j][k]=dp[j][k]+dp[j-val[i]][k-1],dp[j][k]ֻ�ͱ����
����������һ��״̬װ��k-1����Ʒ����󷽰����й�,��k-1����Ʒ����
���ٷ����i����Ʒ�ͱ�ʾװ��k����Ʒʱ����󷽰���,�������ۼ�,��ʼ״̬
��dp[j][0]=1,��Ϊһ����ƷҲ����ֻ��һ�ַ���,���ǺϷ�״̬.

�ܽ�:�������ѭ��dp,ע��ڶ���ѭ���ȿ�����ö�ٱ���ʣ������Ҳ������
ö�ٵ�ǰ�����·�����Ʒ����k,������Ҫ������ö��,��Ϊֻ���������ܱ�֤
dp[j-val[i]][k-1]��ǰi-1����Ʒʱ��dpֵ,�������ö�ٻᵼ�µ�i����Ʒ�ظ�
���뱳��,����dp[j-val[i]][k-1]�Ƿ����i����Ʒʱ��ǰi����Ʒʱ��״̬������ǰi-1
����Ʒ��״̬.���������ѭ�������Ǳ����ݻ����Ƿ��뱳����Ʒ����,�ȿ�����Ҳ�ɽ���.

ע��:�����POJ 3093������⾡���ܶ��װ�������ķ�����,����POJ 3093��û��ָ������
��Ʒ����,������Ȼֻ�ܰ���ǡ��װ������������ ö�ٳ�ʣ����Ʒ�������С��Ҳ�Ų���ȥʱ����
����װ���µ����.������ ��һ��ָ����Ʒ������Ҫ��,ʵ��ֻҪ��ʼ����Ʒ����Ϊ0��Ӧ�ĸ�������
����dp[j][0]=1����,����ֻҪ����Ʒ������i������� dp[m][i]�Ƿ��ǺϷ�״̬����,�����ҵ���
���ܷ�����Ʒ�ķ�����. ��Ȼ�������ܵı����ݻ�����Ʒ����Ϊ0ʱ��ʼֵ����1,���������ظ��ۼ�,
��Ϊ��Ʒ�����ǵڶ���ά�����ܱ�֤ǡ��װ����Ʒ����,����Ʒ����Ϊ0,��������Ʒ����Ϊ1��2��...��n
ȥת��,dp[1..n][j]������0(���Ϸ�),����һ��״̬dp[i-1][j-val[i]]���ǺϷ�״̬,�������������
������װ������Ϊm,dp[i][m]�µķ�����,����m��һ����װ����,���Ⲣû��Ҫ��ǡ��װ������,ֻ�󷽰���.
*/
//����ʵ�� �ο�����:https://blog.csdn.net/zhouzi2018/article/details/86564824
//dp[j][k]��������Ϊj�ı���װ��k����Ʒ���ܷ�����,j��һ��װ��,������ʣ��
int n,m,val[N],dp[M][N];//Ҳ����dp[N][M]

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));//�����ܶ��װ�뱳��
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=0;i<=m;i++)
            dp[i][0]=1;//��ʼ״̬��װ����Ʒ����0��,�����ݻ�����,��һ����������
        //��Ҫ��ǡ��װ��ֻ��ʼ��dp[0][0]=1 �����Լ���if(dp[j-val[i]][k-1]) dp[j][k]+=dp[j-val[i]][k-1];
        //ÿ�η������Ʒ����ͬ,��ǰi-1����Ʒ״̬����Ч��,���ܺ͵�ǰ�ĵ�i����Ʒ��Ϲ����µķ���,
        //ÿ����Ʒ�������һ��dp[j][k] j���Ͻ綼��m,i���½綼�Ǵ�1��ʼ,�����п���ֵ,����Ǽӷ�ԭ���ۼӷ�������
        for(int i=1;i<=n;i++){
            //����ڶ���ѭ�� ������ö�ٱ����������Ƿ��뱳����Ʒ���� �������ǽ���,
            //�������ܱ�֤dp[j-val[i]][k-1]��ǰi-1����Ʒ��״̬
            for(int j=m;j>=val[i];j--){
                //���� k,k-1,k+1֮�䲢������״̬ת��,û��ֱ�ӹ�ϵ,dp[i][j][k]����һ��״̬��ǰi-1����Ʒ��dp[i-1][j][k],������Ϊ���������Ż����˵�һά�ȵ�i
                for(int k=1;k<=i;k++)//ö�� ���뼸����Ʒ,ǰi����Ʒ,����i�� k������Ҳ��ȷ
                    //��Ϊ��ǰ��k-1����Ʒdp[j-val[i]][k-1]�������ֱ�͵�i����Ʒ���,�����Ǽӷ�ԭ��
                    dp[j][k]+=dp[j-val[i]][k-1];//����k����Ʒֻ��k-1����Ʒ��״̬�й�
            }
        }
        int flag=0;
        for(int i=n;i>=1;i--){//�����Ƿ��������Ʒ
            if(dp[m][i]){
                printf("You have %d selection(s) to buy with %d kind(s) of souvenirs.\n",dp[m][i],i);
                flag=1;
                break;
            }
        }
        if(!flag)
            printf("Sorry, you can't buy anything.\n");
    }
    return 0;
}

/*
//ac 31ms ö�ٱ���ʣ�������ڶ���ѭ������ ��Ʒ����������ѭ������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 510
using namespace std;
int n,m,val[N],dp[N][M];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));//�����ܶ��װ�뱳��
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=0;i<=m;i++)
            dp[0][i]=1;
        for(int i=1;i<=n;i++){
            for(int j=m;j>=val[i];j--){
                for(int k=i;k>=1;k--)//ö�� ���뼸����Ʒ,ǰi����Ʒ,����i�� k������Ҳ��ȷ
                    dp[k][j]+=dp[k-1][j-val[i]];//����k����Ʒֻ��k-1����Ʒ��״̬�й�
            }
        }
        int flag=0;
        for(int i=n;i>=1;i--){//�����Ƿ��������Ʒ
            if(dp[i][m]){
                printf("You have %d selection(s) to buy with %d kind(s) of souvenirs.\n",dp[i][m],i);
                flag=1;
                break;
            }
        }
        if(!flag)
            printf("Sorry, you can't buy anything.\n");
    }
    return 0;
}
*/

/*
//ac 31ms ö����Ʒ�����ڶ���ѭ������ ����ʣ������������ѭ������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 510
using namespace std;
int n,m,val[N],dp[M][N];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));//�����ܶ��װ�뱳��
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=0;i<=m;i++)
            dp[i][0]=1;
        for(int i=1;i<=n;i++){
            for(int k=i;k>=1;k--){//ö�� ���뼸����Ʒ,ǰi����Ʒ,����i�� ����ֻ�ܽ���,���������
                for(int j=m;j>=val[i];j--)//���ﱳ���ݻ� ������ ����,j��j-val[i]��û��ֱ�ӵ�״̬ת��,��һ��״̬��ǰi-1����Ʒ,��Ϊ�Ƕ�ά����,����j�����ǽ��򲢲�Ӱ����ǰi-1����Ʒ��״̬
                    dp[j][k]+=dp[j-val[i]][k-1];//����k����Ʒֻ��k-1����Ʒ��״̬�й�
            }
        }
        int flag=0;
        for(int i=n;i>=1;i--){//�����Ƿ��������Ʒ
            if(dp[m][i]){
                printf("You have %d selection(s) to buy with %d kind(s) of souvenirs.\n",dp[m][i],i);
                flag=1;
                break;
            }
        }
        if(!flag)
            printf("Sorry, you can't buy anything.\n");
    }
    return 0;
}
*/

/*
//ac 31ms ö����Ʒ�����ڶ���ѭ������ ����ʣ�������ڵ�����ѭ������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 510
using namespace std;
int n,m,val[N],dp[M][N];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));//�����ܶ��װ�뱳��
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=0;i<=m;i++)
            dp[i][0]=1;
        for(int i=1;i<=n;i++){
            for(int k=i;k>=1;k--){//ö�� ���뼸����Ʒ,ǰi����Ʒ,����i�� ����ֻ�ܽ���,���������
                for(int j=val[i];j<=m;j++)//����ʣ����������
                    dp[j][k]+=dp[j-val[i]][k-1];//����k����Ʒֻ��k-1����Ʒ��״̬�й�
            }
        }
        int flag=0;
        for(int i=n;i>=1;i--){//�����Ƿ��������Ʒ
            if(dp[m][i]){
                printf("You have %d selection(s) to buy with %d kind(s) of souvenirs.\n",dp[m][i],i);
                flag=1;
                break;
            }
        }
        if(!flag)
            printf("Sorry, you can't buy anything.\n");
    }
    return 0;
}
*/

/*
//ac 15ms 01����������װ����Ʒ�������ķ����� ��ά����ʵ��dp[j][2]
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define M 510
using namespace std;

//dp[j][0]��ʾ����Ϊj�ı��������װ����Ʒ����
//dp[j][1]��ʾ����Ϊj�ı��������װ����Ʒ�����ķ�����
//����ʵ�ֲο�����:https://blog.csdn.net/know_heng/article/details/53635476
int n,m,val[N],dp[M][2];

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(dp,0,sizeof(dp));//�����ܶ��װ�뱳��
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        //�������ǡ��װ��,ֻ��ʼ��dp[0][1]=1,�������memset(dp)��0,��ôdp[j][0]��ֵ��Ȼ��ʾ���Ǿ����ܶ��װ������Ʒ
        //��dp֮ǰ����if(!dp[j-val[i]][1]) continue;����dp[j][0]��ֵ��ʾ����ǡ��װ��������������Ʒ
        for(int i=0;i<=m;i++)
        //ע�����������������һά����dp[j]�����ظ��ۼӷ���
        //��Ϊ���·�������ת����dp[j][1]=dp[j-val[i]][1] ��һ����Ʒ��ûװ��ʱ,��ֱ�Ӹ�ֵ,�������ۼ�
            dp[i][1]=1;//��ʼ״̬�������������µ�װ����Ʒ�������ķ�����Ϊ1
        for(int i=1;i<=n;i++){
            for(int j=m;j>=val[i];j--){
                //if(!dp[j-val[i]][1]) continue;//ǡ��װ������ ��������Ϊ0,��˵������ǡ��װ��������(���Ǵ�dp[0][1]ת�ƶ���)
                if(dp[j][0] == dp[j-val[i]][0]+1)//��j-val[i]��һ��״̬װ����Ʒ����+1���ʱ,���ۼ���һ��״̬�ķ�����
                    dp[j][1]+=dp[j-val[i]][1];
                if(dp[j][0] < dp[j-val[i]][0]+1){//��һ��״̬j-val[i]װ����Ʒ�����϶�ʱ,���µ�ǰװ����Ʒ���������ֵ��װ����Ʒ�������ֵ�ķ�����
                    dp[j][0]=dp[j-val[i]][0]+1;
                    //�ܱ�֤ dp[j][1] ��һ����Ʒûװ��ʱ,���ۼ��Լ������ ֵ1,�����Ǹ�ֵ
                    dp[j][1]=dp[j-val[i]][1];
                }
            }
        }
        if(dp[m][0])//��dp[m][0]��Ϊ0,��˵��������װ��һ����Ʒ,������dp[m][1]�ж�,��Ϊdp[m][1]�Ѿ���ʼ������
            printf("You have %d selection(s) to buy with %d kind(s) of souvenirs.\n",dp[m][1],dp[m][0]);
        else
            printf("Sorry, you can't buy anything.\n");
    }
    return 0;
}
*/
