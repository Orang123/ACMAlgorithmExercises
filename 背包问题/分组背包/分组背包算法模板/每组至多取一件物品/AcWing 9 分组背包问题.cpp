/*
����:��n����Ʒ��һ��������v�ı���.ÿ����Ʒ��num[i]��,
ͬһ���ڵ���Ʒ���ֻ��ѡһ��.ÿ����Ʒ�������w[i][j],
��ֵ��val[i][j],����i�����,j�����ڱ��.�������Ʒ��
�����������������������,�ܵõ�������ֵ.�������ֵ.
ÿ����Ʒ��Ȼֻ��ѡ��ѡ,ͬһ����Ʒֻ��ѡһ��.
0<n,v<=100.
0<num[i]<=100.
0<w[i][j],val[i][j]<=100.
����:https://www.acwing.com/problem/content/description/9/
˼·:���鱳��ģ����.�����ܶ��װ������.
//dp[i][j]����ǰi����ÿ�������һ����Ʒ��������Ϊjʱ�ܻ�õ�����ֵ.
���������ʾΪdp[j].
ʱ�临�Ӷ�O(n*v*max(num[i]))=100*100*100=10^6
*/
//ac 44ms һά����ʵ�ַ��鱳�� ÿ�����ȡһ����Ʒ
//һά����  ������ѭ��˳��,ֻ������ö��ö�ٱ�������,��ö��ÿ����Ʒ,�������ܱ�֤dp[j-w[i][k]]��ǰi-1���״̬
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

//dp[i][j]����ǰi����ÿ�������һ����Ʒ��������Ϊjʱ�ܻ�õ�����ֵ.
int n,v,num[N],w[N][N],val[N][N],dp[M];

int main(){
    //�����ܶ��װ������,����״̬���Ϸ�
    memset(dp,0,sizeof(dp));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++){
        scanf("%d",&num[i]);
        for(int j=1;j<=num[i];j++)
            scanf("%d%d",&w[i][j],&val[i][j]);
    }
    //���ǵ�i�����Ʒ ʱ�临�Ӷ�O(n*v*max(num[i]))
    for(int i=1;i<=n;i++){
        //���������Ż����ﱳ���������뽵��,ע���п�����Ʒ���Ϊ0,���Ա��������½���0
        //������ѭ��˳���ܵߵ�,����ͻ��ɡ�num[i]������Ʒ����01����,ͬ������Ʒ����ȡ�ܶ����
        for(int j=v;j>=0;j--){
            //�ڱ�������Ϊjʱ,������ǰi-1������Ʒ���Ž�����Ϸ����i���ڱ��Ϊk��һ����Ʒ
            //�򲻷����i������Ʒ��:ǰi-1������Ʒ���Ž�
            for(int k=1;k<=num[i];k++){//ö�ٵ�i���ڵ�ÿ����Ʒ����,�Ƚ�����Ǹ�������ֵ������Ʒ��Ϊ���Ž�
                if(j>=w[i][k])//��֤���������ܷŴ��� ��i���ڵ�k����Ʒ
                    //dp[j-w[i][k]]��ǰi-1����Ʒ�ڱ�������Ϊj-w[i][k]ʱ�����Ž� ��֤�˵�i����Ʒ�������ѡȡ,���ֻ��ѡһ��
                    dp[j]=max(dp[j],dp[j-w[i][k]]+val[i][k]);
            }
        }
    }
    printf("%d",dp[v]);
    return 0;
}

/*
//ac 51ms ��ά����ʵ�ַ��鱳�� ������ѭ��˳��,��ö��ö�ٱ�������,��ö��ÿ����Ʒ
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

//dp[i][j]����ǰi����ÿ�������һ����Ʒ��������Ϊjʱ�ܻ�õ�����ֵ.
int n,v,num[N],w[N][N],val[N][N],dp[N][M];

int main(){
    //��ʼ״̬��һ�������ƷҲ����,�����ܶ��װ������,dp[0][1..v]=0 ���ǺϷ�״̬
    memset(dp[0],0,sizeof(dp[0]));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++){
        scanf("%d",&num[i]);
        for(int j=1;j<=num[i];j++)
            scanf("%d%d",&w[i][j],&val[i][j]);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=v;j++){//�������� ����Կ�
            //�п��ܵ�i��һ����ƷҲû��,����Ҫ��ǰת��״̬
            dp[i][j]=dp[i-1][j];//ǰi��ĳ�ʼ״ֱ̬����ǰi-1������Ž�ת�ƶ���
            for(int k=1;k<=num[i];k++){//ö�ٵ�i����ÿ����Ʒ���� ֻ����������ֵ������1����Ʒ��Ϊ���Ž�
                if(j>=w[i][k])
                //k=1ʱ,dp[i][j]���������i������Ʒ��ǰi-1����Ʒ�����Ž�.
                //k>1ʱ,dp[i][j]��֮ǰ�����i���ڱ��Ϊ1~k-1������Ʒ(ֻ��һ��,������)�����Ž���dp[i-1][j]�����Ž�Ľϴ�ֵ
                //dp[i-1][j-w[i][k]]��ǰi-1����Ʒ�ڱ�������Ϊj-w[i][k]ʱ�����Ž�
                    dp[i][j]=max(dp[i][j],dp[i-1][j-w[i][k]]+val[i][k]);
            }
        }
    }
    printf("%d",dp[n][v]);
    return 0;
}
*/

/*
//ac 35ms ��ά����ʵ�� �ߵ�������ѭ��˳��,��ö��ÿ����Ʒ,��ö�ٱ�������
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

//dp[i][j]����ǰi����ÿ�������һ����Ʒ��������Ϊjʱ�ܻ�õ�����ֵ.
int n,v,num[N],w[N][N],val[N][N],dp[N][M];

int main(){
    //��ʼ״̬��һ�������ƷҲ����,�����ܶ��װ������,dp[0][1..v]=0 ���ǺϷ�״̬
    memset(dp[0],0,sizeof(dp[0]));
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++){
        scanf("%d",&num[i]);
        for(int j=1;j<=num[i];j++)
            scanf("%d%d",&w[i][j],&val[i][j]);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=v;j++)//ǰi��״̬�ĳ�ʼ״ֱ̬�Ӽ̳�ǰi-1�����Ž�
            dp[i][j]=dp[i-1][j];
        for(int k=1;k<=num[i];k++){//ö�ٵ�i����Ʒ
            for(int j=v;j>=w[i][k];j--)//ö�ٱ������� ���ﱳ������j ���������Կ�
                //ÿ����Ʒֻ����ǰi-1����Ʒdp[i-1][j-w[i][k]]�����Ϸ����i���е�k����Ʒ
                dp[i][j]=max(dp[i][j],dp[i-1][j-w[i][k]]+val[i][k]);
        }
    }
    printf("%d",dp[n][v]);
    return 0;
}
*/

/*
//TLE 40�� dfs����ö������+��֦
//����dp[i][j]��ǰi��״̬��֦,TLEֻ�ܵ�20��.
//ʱ�临�Ӷ�O(max(num[i])^n)=O(100^100)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 110
#define M 110
using namespace std;

//dp[k][j]������ǰk��ÿ�������һ����Ʒ�������Ϊjʱ�ܻ�õ�����ֵ
int n,v,num[N],w[N][N],val[N][N],dp[N][M],ans;

//ʱ�临�Ӷ�O(max(num[i])^n)=O(100^100)
void dfs(int k,int curV,int sum){
    if(curV>v)//��ǰ��ѡ��Ʒ������ڱ�������
        return;
    //�����ǰǰk-1����ѡ��Ʒ�������ΪcurV��õļ�ֵ���ܱ�֮ǰ��������ͬ״̬�µĽ������,�ͼ�֦,������������ȥ
    //��Ϊ����Ľ׶ζ�����ͬ������,��ǰ�����״̬������,�����״̬��Ȼ�������.
    if(sum<=dp[k-1][curV])
        return;
    dp[k-1][curV]=sum;//����ǰk-1����ѡ��Ʒ�������ΪcurV��õļ�ֵ
    if(sum>ans)//��¼����ֵ
        ans=sum;
    if(k == n+1)//n����Ʒ��������
        return;
    //��k���ڵ���Ʒֻ���Ƿ������е�1��
    for(int i=1;i<=num[k];i++)
        dfs(k+1,curV+w[k][i],sum+val[k][i]);
    //��k���ڵ���Ʒ1��Ҳ������
    dfs(k+1,curV,sum);
}

int main(){
    ans=0;
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++){
        scanf("%d",&num[i]);
        for(int j=1;j<=num[i];j++)
            scanf("%d%d",&w[i][j],&val[i][j]);
    }
    memset(dp,0,sizeof(dp));
    //��ʼ��ǰk����Ʒһ����ƷҲ��ѡʱ��ֵΪ-1,��������ֱ�ӽ����˳�
    for(int k=0;k<=n;k++)
        dp[k][0]=-1;
    dfs(1,0,0);
    printf("%d",ans);
    return 0;
}
*/
