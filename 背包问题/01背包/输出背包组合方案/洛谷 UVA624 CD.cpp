#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5100
using namespace std;
//ac 50ms 01���������ܶ��װ��,������Ŀ����˳�������Ʒ��Ϸ���
/*
����:������һ���������г�֮����,����һ���Ŵ���,������
��ϲ����������CD(����)��.����Ҫ�����Ƿ��ڴŴ�����.����
һ�����Դ���N���ӳ��ĴŴ�,�Ŵ�������������,����Ҫѡ��
һ�����ŷ���ʹ��δ�ÿռ���С.
ע��:
1.һƬCD��û�г���20������
2.û�������N���ӳ�
3.���컥���ظ�
4.ÿһ������ĳ�����һ��int��Χ����
5.NͬʱҲ��һ��int��ĳ�����Ҫ�ҵ�һ�����ŷ���(������������),
���Ұ���ԭ����˳����������ʽ:ÿһ����һ��N�����������ʱ��
�����ʽ:һ�״Ŵ���ŵ�����ѡ�� ������ʱ����ܺ�.
����:https://www.luogu.com.cn/problem/UVA624
˼·:����01����¯ͷ,��ΪҪ������˳�������Ϸ���,����
Ҫ�����ȴӵ�n����Ʒ��ʼ��,����Ƿŵ�1����Ʒ,Ȼ���������ʱ
�Ϳ��Դӵ�һ����Ʒ��ʼ����.
*/
//vis[i][j]=1����������Ϊjʱ,���Ž�����˵�i����Ʒ
//vis[i][j]=0����������Ϊjʱ,���Ž�û�з����˵�i����Ʒ
//ע������vis[i][j]ֻ�ǵ����ر�ʾ��i����Ʒ�ڱ�������jʱ���Ž�����Ƿ�װ��,���ܴ���ʵ�ʵĵ��ƹ�ϵ
int n,v,val[N],dp[M],sum,vis[N][M];

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,0,sizeof(dp));
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=n;i>=1;i--){//��ΪҪ��������˳�������Ʒ��ֵ,���������ȷ����n��,���ŵ�1��
            for(int j=v;j>=val[i];j--){
                //����if(dp[j]<=dp[j-val[i]]+val[i])����<= ʵ�ʷ������ܲ�ͬ
                //���һ������45 8 4 10 44 43 12 9 8 2 �ǰ�<=�����,<�������43 2
                if(dp[j]<dp[j-val[i]]+val[i]){//�������ϸ�С��,��Ϊû��PTA L3-001���ְ����ֵ����ֵ���������Ҫ��
                    dp[j]=dp[j-val[i]]+val[i];
                    vis[i][j]=1;//��ǵ�ǰ���Ž� ����Ϊjʱ��������Ʒi
                }
            }
        }
        //ע������ ������j-=val[i],���տ���������Ʒ��������,dp[j]��Ȼ��Ϊ0,
        //��Ϊ������ǡ��װ��������:dp[v]==v,���Բ����ܸ���j��dp[j]Ϊ0���ж�
        //����90 8 10 23 1 2 3 4 5 7 ����ȫ��������,dp[35]=35,��������ж�dp[j]�Ƿ�Ϊ0����ѭ��
        //����ֻ��ǰ0����Ʒ�ĳ�ʼ״̬dp[j]=0,dp��ɺ�,����һ����Ʒ�����Ϊ1,�����dp[0]==0��,����dp[j]������0
        for(int i=1,j=v;i<=n;i++){//�ӱ��Ϊ1����Ʒ�������,��Ϊ���Խ��ǰ����ƷԽ�������뱳����
            if(vis[i][j]){
                //���������������,��Ϊ�ڱ���������ͬʱ���Ž�ķ��������ǲ�ͬ��,
                //�����Ҫ��������Ҫ��ȥ��ǰ��i����Ʒ,����ʹ�õ�ǰʣ�����������������v�µ����Žⷽ��,
                //֮���������жϵ�i+1����Ʒ�Ƿ������Ž���
                j-=val[i];
                printf("%d ",val[i]);
            }
        }
        printf("sum:%d\n",dp[v]);
    }
    return 0;
}

/*
//ac 40ms vis[i][j]��Ǳ�������Ϊjʱ�Ƿ�ѡ�õ�i����Ʒ ǡ��װ������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5100
using namespace std;

int n,v,val[N],dp[M],sum,vis[N][M];

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,-0x3f,sizeof(dp));
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        dp[0]=0;
        for(int i=n;i>=1;i--){
            for(int j=v;j>=val[i];j--){
                if(dp[j]<dp[j-val[i]]+val[i]){
                    dp[j]=dp[j-val[i]]+val[i];
                    vis[i][j]=1;
                }
            }
        }
        for(int i=v;i>=0;i--){
        	if(dp[i]>0){
        		v=i;
        		break;
			}
		}
		int i=1,j=v;
		while(j){
			if(vis[i][j]){
				printf("%d ",val[i]);
				j-=val[i];
			}
			i++;
		}
        printf("sum:%d\n",dp[v]);
    }
    return 0;
}
*/

/*
//ac 40ms ��ά�������01���� �ݹ��������
//�ݹ����������������ֵ���
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5100
using namespace std;

int n,v,val[N],dp[N][M],sum;

void print(int i,int j){
	if(!i)//i=0,������Ʒ�ķ����Ѿ��жϳ���
		return;
	//ǰi����Ʒ��ǰi-1����Ʒ���Ž���ͬ,˵��ûѡ��i����Ʒ
	//���������������ֵ���,��j����ȫ��װ��ǰi����ǰi-1����Ʒ,ʱ������Ϊû��ѡ���i����Ʒ,
    //��ʵ���ֵ��򷽰� ������ѡ���˵�i������Ʒ��,���Եݹ��޷�����ֵ��򷽰�,ֻ��˵�����������һ�ַ���.
	//ת���ݹ���ǰһ��״̬���ж�
	if(dp[i][j] == dp[i-1][j])
		print(i-1,j);
	else{//����i����Ʒ��ǰi-1����Ʒ���Žⲻͬ,˵���϶���dp[i][j]>dp[i-1][j],��:ѡ�˵�i����Ʒ�� ���Žⱻ����
        //j-val[i],��Ϊ����v�Ϳ�����ʣ��,���Դ����Ŀ�ʼ�ݼ��ж�ǰi����ǰi-1���Ƿ���������ͬ���������Ž���ͬ
		print(i-1,j-val[i]);//��ΪҪ��������˳���������,�����ȵݹ��ж�ǰ����Ʒ�������������������Ʒ
		printf("%d ",val[i]);//�����i����Ʒ�ļ�ֵ
	}
}

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;i++){
            for(int j=0;j<=v;j++){
            	if(j>=val[i])
            		dp[i][j]=max(dp[i-1][j],dp[i-1][j-val[i]]+val[i]);
            	else
            		dp[i][j]=dp[i-1][j];
            }
        }
        print(n,v);
        printf("sum:%d\n",dp[n][v]);
    }
    return 0;
}
*/

/*
//ac 50ms ��ά�������01���� ����ѭ���������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
#define M 5100
using namespace std;

int n,v,val[N],dp[N][M],sum;

int main(){
    while(scanf("%d%d",&v,&n)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        //��Ϊѭ��ֻ�����Ŵӵ�1����Ʒ��ʼ�ж�,����01���������n��ʼ���뱳��,����1����Ʒ��Ϊ����״̬
        for(int i=n;i>=1;i--){
            for(int j=0;j<=v;j++){
            	if(j>=val[i])
            		dp[i][j]=max(dp[i+1][j],dp[i+1][j-val[i]]+val[i]);
            	else
            		dp[i][j]=dp[i+1][j];
            }
        }
        int tp=v;
        for(int i=1;i<=n;i++){
        	if(dp[i][tp]!=dp[i+1][tp]){
        		printf("%d ",val[i]);
        		tp-=val[i];
			}
		}
        printf("sum:%d\n",dp[1][v]);
    }
    return 0;
}
*/
