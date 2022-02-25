#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M0 110
using namespace std;
//ac 51ms ��ά���ñ���(���������Ż�����һά) ���Ż�����άdp[i][j][k]
/*
����:��n����Ʒ��һ��������V�ı���,�����ܳ��ܵ����������M.
ÿ����Ʒֻ����һ��.�����v[i],������m[i],��ֵ��w[i].
��⽫��Щ��Ʒװ�뱳��,��ʹ��Ʒ�������������������,
�����������������ɳ��ܵ��������,�Ҽ�ֵ�ܺ����,
�������ֵ.

����:��ά���õı���������ָ:����ÿ����Ʒ,�������ֲ�ͬ�ķ���,
ѡ�������Ʒ����ͬʱ���������ַ���.����ÿ�ַ��ö���һ���ɸ�
�������ֵ(��������).������ѡ����Ʒ���Եõ����ļ�ֵ.
����:https://www.acwing.com/problem/content/description/8/
˼·:ģ����,������һ��ά��,һ��ά����Ϊ��������,һ��ά����Ϊ
��������,��Ȼ�ǰ���01������˼·,������ö���������ƻ�����ö��
��������,��û������,���ɽ��,����Ҫע��ڶ���ѭ��ö�ٵı���Ҫ
���������ſɱ�֤״̬ת�Ʒ����е�dp[j-v[i]][k-m[i]]��û�з����
i����Ʒ��ǰi-1����Ʒ��״̬.
*/
/*
˵��:
�����������Vǡ��װ��,����M�����ܶ��װ���ͳ�ʼ��dp[0][0..M]=0,
�����������Mǡ��װ��,����V�����ܶ��װ���ͳ�ʼ��dp[0..V][0]=0,
�����������V������M��ǡ��װ���ͳ�ʼ��dp[0][0]=0
�����������V������M�������ܶ��װ���ͳ�ʼ�� memset(dp,0,sizeof(dp))

����������ָ����Ʒ����������ֵ,��������������,���ʾ��Ƕ�ά���ñ���,
��Ʒ�����������һ��ά��,ÿ����Ʒ��һ����Ʒ��������Ϊ1,ÿ����һ״̬���ǵ�ǰ��Ʒ����-1.
*/
int n,V,M,v[N],m[N],w[N],dp[M0][M0];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d",&n,&V,&M);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&v[i],&m[i],&w[i]);
    for(int i=1;i<=n;i++){
        //��ΪӰ����Ʒ���뱳������������ �����������������,����ͬʱö�ٱ���ʣ������ݻ�������
        //�������ܹ������ǰi����Ʒ���Ž������,ÿ����Ʒ1��2��..i-1��i�ķ�����������������
        for(int j=V;j>=v[i];j--){
            for(int k=m[i];k<=M;k++)
                dp[j][k]=max(dp[j][k],dp[j-v[i]][k-m[i]]+w[i]);
        }
    }
    printf("%d",dp[V][M]);
    return 0;
}
/*
//ac 48ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M0 110
using namespace std;

int n,V,M,v[N],m[N],w[N],dp[M0][M0];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d",&n,&V,&M);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&v[i],&m[i],&w[i]);
    for(int i=1;i<=n;i++){
        for(int j=V;j>=v[i];j--){
            for(int k=M;k>=m[i];k--)
                dp[j][k]=max(dp[j][k],dp[j-v[i]][k-m[i]]+w[i]);
        }
    }
    printf("%d",dp[V][M]);
    return 0;
}
*/

/*
//ac 47ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M0 110
using namespace std;

int n,V,M,v[N],m[N],w[N],dp[M0][M0];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d",&n,&V,&M);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&v[i],&m[i],&w[i]);
    for(int i=1;i<=n;i++){
        for(int j=M;j>=m[i];j--){
            for(int k=v[i];k<=V;k++)
                dp[j][k]=max(dp[j][k],dp[j-m[i]][k-v[i]]+w[i]);
        }
    }
    printf("%d",dp[M][V]);
    return 0;
}
*/

/*
//ac 48ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
#define M0 110
using namespace std;

int n,V,M,v[N],m[N],w[N],dp[M0][M0];

int main(){
    memset(dp,0,sizeof(dp));
    scanf("%d%d%d",&n,&V,&M);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&v[i],&m[i],&w[i]);
    for(int i=1;i<=n;i++){
        for(int j=M;j>=m[i];j--){
            for(int k=V;k>=v[i];k--)
                dp[j][k]=max(dp[j][k],dp[j-m[i]][k-v[i]]+w[i]);
        }
    }
    printf("%d",dp[M][V]);
    return 0;
}
*/

/*
������������,���϶�tle
*/
